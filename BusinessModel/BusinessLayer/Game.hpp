#ifndef _GAME_
#define _GAME_

#include "../Common.hpp"

#include "Items/Clue.hpp"
#include "Interfaces/IGame.hpp"
#include "Interfaces/IControllable.hpp"
#include "../PresentationLayer/Interfaces/IScreen.hpp"
#include "Console.hpp"
#include <functional>

namespace cluedo
{
	class Actor;
	class Environment;
	class Item;
	class Player;

	class Game : public IPrintable, public IGame
	{

	private:
		typedef IGame::FuncMap FuncMap;
		FuncMap _func_map;

		struct load_game_exception : public std::runtime_error
		{
			load_game_exception(std::string const & msg) : runtime_error(msg){}
		};

		//Variables
		Player * _player;
		int _boardwidth = 0, 
			_boarddepth = 0,
			_numactors = 5;

		//Vectors
		std::map<std::string, Actor *> _actors;
		std::map<Clue::ClueType, Clue> _clues;
		std::vector<Environment *> _environments;

		//Dependencies
		std::shared_ptr<IScreen> _screen;

		//ctor
		Game(std::shared_ptr<IScreen>);

		const std::string DEFAULT_FILE = "default.txt";

		//State printers
		std::string introduction() const;
		std::string scene() const;
		std::string commands() const;
		std::string choice() const;
		std::string win() const;

		const std::map <IGame::GameState, std::string(Game::*)(void) const> state_text{
			std::make_pair(IGame::INTRO, &Game::introduction),
			std::make_pair(IGame::PLAYING, &Game::scene),
			std::make_pair(IGame::HELP, &Game::commands),
			std::make_pair(IGame::CHOICE, &Game::choice),
			std::make_pair(IGame::WIN, &Game::win)
		};

	public:

		~Game();
		static std::shared_ptr<Game> make_game(std::shared_ptr<IScreen>);

		Environment* get_neighbour_of(const Environment*, int,bool visible = false) const;
		std::vector<Environment *> get_neighbours_of(const Environment *,bool visible = false) const;
		std::vector<Actor *> get_actors_in(const Environment *);
		int no_of_actors_in(const Environment *) const;

		void create_actor(std::string);
		void destroy_actor(Actor *);

		//Loading methods
		void load_game(std::string);
		
		//IGame
		virtual bool exit(std::vector<std::string>) override;
		virtual bool help(std::vector<std::string>) override;
		virtual bool yes(std::vector<std::string>) override;
		virtual bool no(std::vector<std::string>) override;
		virtual bool go(std::vector<std::string>) override;
		virtual bool bag(std::vector<std::string>) override;
		virtual bool pick(std::vector<std::string>) override;
		virtual bool drop(std::vector<std::string>) override;
		virtual bool examine(std::vector<std::string>) override;
		virtual bool use(std::vector<std::string>) override;
		virtual bool clues(std::vector<std::string>) override;
		virtual bool stats(std::vector<std::string>) override;
		virtual bool guess(std::vector<std::string>) override;
		virtual bool is_game_over() const override;
		virtual void step() override;
		virtual void game_over() override;
		virtual bool player_alive() const override;
		virtual GameState game_state() const override;
		virtual void game_state(GameState) override;

		//IPrintable
		virtual std::string print() const override;
		virtual bool is_visible() const override;

		//IControllable
		virtual FuncMap map_of_functions() const override;


	private: //CONSTANTS//

		const std::map<std::string, int> string_to_direction
		{
			std::make_pair("east",0),
			std::make_pair("north",1),
			std::make_pair("west",2),
			std::make_pair("south",3),
			std::make_pair("northeast",4),
			std::make_pair("northwest",5),
			std::make_pair("southwest",6),
			std::make_pair("southeast",7)

		};
		const std::map<int, std::string> direction_to_string
		{
			std::make_pair(0,"east"),
			std::make_pair(1,"north"),
			std::make_pair(2,"west"),
			std::make_pair(3,"south"),
			std::make_pair(4,"northeast"),
			std::make_pair(5,"northwest"),
			std::make_pair(6,"southwest"),
			std::make_pair(7,"southeast")
		};
	};


}

#endif