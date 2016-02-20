#ifndef _CONSOLE_
#define _CONSOLE_


#include "../Common.hpp"
#include <sstream>
#include "Interfaces/IConsole.hpp"
#include "Interfaces/IControllable.hpp"
#include "../PresentationLayer/Interfaces/IScreen.hpp"
#include "Interfaces/IGame.hpp"

namespace cluedo
{

	class Game;

	template <typename T>
	class Console : public IConsole
	{
	public:

		typedef bool(T::*FuncPtr)(std::vector<std::string>);			
		typedef std::map<std::string, FuncPtr> FuncMap;
		//typedef T::FuncMap FuncMap;

	private:
		std::shared_ptr<T> _game;
		std::shared_ptr<IScreen> _screen;

		FuncMap _function_map;

		std::vector<std::string> get_tokens() const;

		Console(std::shared_ptr<T>, std::shared_ptr<IScreen>);
		virtual ~Console();

	public:
		virtual bool prompt() const;

		static std::unique_ptr<IConsole> make_console(std::shared_ptr<T>,std::shared_ptr<IScreen>);

	};

	template <typename T>
	std::vector<std::string> Console<T>::get_tokens() const
	{
		std::vector<std::string> tokens;
		std::string input;
		std::string token;

		getline(std::cin, input);
		_screen->println(input);
		std::istringstream ss(input);

		while (getline(ss, token, ' '))
			tokens.push_back(token);

		if (tokens.size() < 1)
			throw std::invalid_argument("Too few arguments.");

		return tokens;
	}

	template <typename T>
	Console<T>::Console(std::shared_ptr<T> game, std::shared_ptr<IScreen> screen)
	{
		_game = std::move(game);
		_screen = std::move(screen);

		//Get function map from controllable
		_function_map = _game->map_of_functions();

	}

	template <typename T>
	Console<T>::~Console()
	{
#ifdef _DEBUG
		std::cout << "Console destructed." << std::endl;
#endif
	}
	

	template <typename T>
	bool Console<T>::prompt() const
	{
		if (!_game->player_alive() || _game->game_state() == IGame::WIN)
		{
			_game->game_over();
			return true;
		}
		

		_screen->print("> ");
		_screen->print_scene();

		//Tokenize input
		std::vector<std::string> tokens;
		try
		{
			tokens = get_tokens();
		}
		catch (std::invalid_argument e)
		{
			_screen->println("Too few arguments");
			
			return false;
		}

		if (_game->game_state() == IGame::HELP)
			_game->game_state(IGame::PLAYING);

		try {
			FuncPtr fp = _function_map.at(tokens.front());
			tokens.erase(tokens.begin());

			if (fp != nullptr) {

				bool success = (_game.get()->*fp)(tokens);

				if (success)
					return true;

				_screen->println("Invalid parameter.");

			}

		}
		catch (std::out_of_range e)
		{
			_screen->println("Invalid command.");
			return false;
		}

		

		return false;
	}

	template <typename T>
	std::unique_ptr<IConsole> Console<T>::make_console(std::shared_ptr<T> game, std::shared_ptr<IScreen> screen)
	{
		return std::unique_ptr<IConsole>(new Console(game, screen));
	}
}

#endif