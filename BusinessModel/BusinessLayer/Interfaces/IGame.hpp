#ifndef _IGAME_
#define _IGAME_

#include "../../Common.hpp"
#include "IControllable.hpp"

namespace cluedo
{

	class IGame : public IControllable<IGame>
	{
	public:
		typedef bool(IGame::*FuncPtr)(std::vector<std::string>);
		typedef std::map<std::string, FuncPtr> FuncMap;

		virtual ~IGame() {}
		enum GameState { INTRO, PLAYING, GAME_OVER, CHOICE, WIN, HELP };
		GameState _state;

		virtual bool exit(std::vector<std::string>) = 0;
		virtual bool help(std::vector<std::string>) = 0;
		virtual bool yes(std::vector<std::string>) = 0;
		virtual bool no(std::vector<std::string>) = 0;
		virtual bool go(std::vector<std::string>) = 0;
		virtual bool bag(std::vector<std::string>) = 0;
		virtual bool pick(std::vector<std::string>) = 0;
		virtual bool drop(std::vector<std::string>) = 0;
		virtual bool examine(std::vector<std::string>) = 0;
		virtual bool use(std::vector<std::string>) = 0;
		virtual bool clues(std::vector<std::string>) = 0;
		virtual bool stats(std::vector<std::string>) = 0;
		virtual bool guess(std::vector<std::string>) = 0;
		virtual bool is_game_over() const = 0;
		virtual void step() = 0;
		virtual void game_over() = 0;
		virtual bool player_alive() const = 0;
		virtual GameState game_state() const = 0;
		virtual void game_state(GameState) = 0;

		//IControllable
		virtual FuncMap map_of_functions() const = 0;
	};


}

#endif