#include "Common.hpp"
#include "BusinessLayer/Game.hpp"
#include "BusinessLayer/Interfaces/IConsole.hpp"
#include "BusinessLayer/Console.hpp"
#include "PresentationLayer/Interfaces/IScreen.hpp"
#include "PresentationLayer/Screen.hpp"

using namespace std;
using namespace cluedo;

int main()
{
	shared_ptr<IScreen> screen = Screen::make_screen();							//VIEW
	shared_ptr<IGame> game = Game::make_game(screen);							//MODEL
	unique_ptr<IConsole> console = Console<IGame>::make_console(game, screen);	//CONTROLLER

	//GAME LOOP
	while (!game->is_game_over())
	{
		//Print scene
		screen->print_scene();

		//Console prompt
		while(!console->prompt());

		//Step game
		game->step();
	}
	//!GAME LOOP

	return 0;
}