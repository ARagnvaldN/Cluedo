#include "Game.hpp"

#include <fstream>
#include <functional>
#include <string>

#include "Environments/Environment.hpp"
#include "Environments/CrimeScene.hpp"
#include "Environments/Room.hpp"
#include "Environments/TrapRoom.hpp"
#include "Environments/DarkRoom.hpp"
#include "Environments/GardenMaze.hpp"

#include "Actors/Actor.hpp"
#include "Actors/Player.hpp"
#include "Actors/LazyActor.hpp"
#include "Actors/PanicActor.hpp"
#include "Actors/MurderActor.hpp"
#include "Actors/PinkElephant.hpp"
#include "Actors/LooterActor.hpp"

#include "Items/MurderWeapon.hpp"
#include "Items/Weapon.hpp"
#include "Items/LuminolSpray.hpp"
#include "Items/ItemDispencer.hpp"
#include "Items/Spirits.hpp"
#include "Items/MurderClue.hpp"
#include "Items/Clue.hpp"

#include "Console.hpp"

using namespace std;

namespace cluedo
{
	Game::Game(std::shared_ptr<IScreen> screen)
	{
		//Set up IScreen
		_screen = screen;
		_screen->add_printable(this);

		//Initialize variables
		_state = INTRO;
	
		//Fill function map
		_func_map = FuncMap();
			_func_map.insert(make_pair("exit", &IGame::exit));
			_func_map.insert(make_pair("help", &IGame::help));
			_func_map.insert(make_pair("y", &IGame::yes));
			_func_map.insert(make_pair("n", &IGame::no));
			_func_map.insert(make_pair("go", &IGame::go));
			_func_map.insert(make_pair("bag", &IGame::bag));
			_func_map.insert(make_pair("pick", &IGame::pick));
			_func_map.insert(make_pair("drop", &IGame::drop));
			_func_map.insert(make_pair("examine", &IGame::examine));
			_func_map.insert(make_pair("use", &IGame::use));
			_func_map.insert(make_pair("clues", &IGame::clues));
			_func_map.insert(make_pair("guess", &IGame::guess));

		try {

			//Load game from default file
			load_game(DEFAULT_FILE);

		}
		catch (load_game_exception& e)
		{
			std::cout << e.what() << endl;
			_state = GAME_OVER;
		}
	}

	void Game::load_game(std::string file)
	{
		enum InputState {META,ENV,ACT,ITEM};
		InputState current = META;

		std::map<Clue::ClueType, Clue> & clue_ref = _clues;

		//Map of environment constructors
		std::map<std::string, std::function<Environment *(const std::vector<std::string> &)>> ctor_map
		{
			make_pair("ROOM", [this](const std::vector<std::string> & params) 
				{return new Room(params.at(1),params.at(2),this); }),

			make_pair("CRIMESCENE", [this, &clue_ref](const std::vector<std::string> &  params) 
				{
					clue_ref.insert(make_pair(Clue::SCENE,Clue(params.at(1),"Crimescene")));
					return new CrimeScene(params.at(1),params.at(2),this); }),

			make_pair("TRAPROOM", [this](const std::vector<std::string> &  params) 
				{return new TrapRoom(std::stoi(params.at(1)),std::stoi(params.at(2)),params.at(3),params.at(4),this); }),

			make_pair("DARKROOM", [this](const std::vector<std::string> &  params) 
				{return new DarkRoom(params.at(1),params.at(2),this); }),

			make_pair("MAZE",[this](const std::vector<std::string> & params) 
				{return new GardenMaze(std::vector<int>{1,1,1,1,1,1,1,1},std::vector<int>{1,1,1,1,1,1,1,1},this); })
		};

		std::vector<Environment *> environs;

		//Map of actor constructors
		std::map<std::string, std::function<Actor * (const std::vector<std::string> &)>> actor_map
		{
			make_pair("LAZY", [&environs](const std::vector<std::string> & params)
				{
					return new LazyActor(
						params.at(1),params.at(2),params.at(3),std::stoi(params.at(4)), environs.at(std::stoi(params.at(5))));
				}),

			make_pair("LOOTER", [&environs](const std::vector<std::string> & params)
				{
					return new LooterActor(
						params.at(1),params.at(2),params.at(3),std::stoi(params.at(4)),environs.at(std::stoi(params.at(5)))); }),

			make_pair("PANIC", [&environs](const std::vector<std::string> & params)
				{
					return new PanicActor(
						params.at(1),params.at(2),params.at(3),std::stoi(params.at(4)),environs.at(std::stoi(params.at(5)))); }),

			make_pair("MURDER", [&environs, &clue_ref](const std::vector<std::string> & params)
				{
					clue_ref.insert(make_pair(Clue::IDENTITY,Clue(params.at(1),"Murderer")));
					return new MurderActor(
					params.at(1),params.at(2),params.at(3),std::stoi(params.at(4)),environs.at(std::stoi(params.at(5)))); })
		};

		std::map<std::string, Actor *> actors {};


		std::map<std::string, std::function<Item * (const std::vector<std::string> &)>> dispenser_map
		{
			make_pair("ITEM", [](const std::vector<std::string> & params) { return new ItemDispencer<Item>( params.at(4), params.at(5) ); }),
			make_pair("SPIRITS", [](const std::vector<std::string> & params) { return new ItemDispencer<Spirits>(params.at(4), params.at(5)); })
		};

		std::map<std::string, std::function<std::unique_ptr<Item> (const std::vector<std::string> &)>> item_map
		{
			make_pair("MURDERWEAPON", [&actors, &clue_ref](const std::vector<std::string> & params) {
				clue_ref.insert(make_pair(Clue::TOOL,Clue(params.at(3),"Murderweapon")));

				return std::move(std::unique_ptr<Item>(new MurderWeapon(
					params.at(3),params.at(4),static_cast<Player *>(actors.at("PLAYER")))));
			}),
			make_pair("ITEM", [](const std::vector<std::string> & params) {
				return std::move(std::unique_ptr<Item>(new Item(
					params.at(3),params.at(4))));
			}),
			make_pair("WEAPON", [](const std::vector<std::string> & params) {
				return std::move(std::unique_ptr<Item>(new Weapon(
					params.at(3),params.at(4))));
			}),
			make_pair("LUMINOL", [](const std::vector<std::string> & params) {
				return std::move(std::unique_ptr<Item>(new LuminolSpray(
					params.at(3),params.at(4))));
			}),
				make_pair("SPIRITS", [](const std::vector<std::string> & params) {
				return std::move(std::unique_ptr<Item>(new Spirits(params.at(3),params.at(4))));
			}),
				make_pair("DISPENSER", [&dispenser_map](const std::vector<std::string> & params) {
				return std::move(std::unique_ptr<Item>(	dispenser_map.at(params.at(3))(params)));
			}),
				make_pair("MURDERCLUE", [&actors](const std::vector<std::string> & params) {
				return std::move(std::unique_ptr<Item>(new MurderClue(params.at(3),params.at(4),params.at(5), static_cast<Player *>(actors.at("PLAYER")))));
			})
		};

		std::map < std::string, std::function<void(const std::vector<std::string> &)>> placement_map
		{
			make_pair("ENV", std::function<void(const std::vector<std::string> &)>{
			[&environs, &item_map](const std::vector<std::string> & params)
				{
					environs.at(std::stoi(params.at(2)))->
						place(item_map.at(params.at(1))(params));
				}}),

			make_pair("ACT", std::function<void(const std::vector<std::string> &)>{
				[&actors, &item_map](const std::vector<std::string> & params)
				{
					
					actors.at(params.at(2))->
						receive(item_map.at(params.at(1))(params));
						
				}})
		};

		ifstream infile(file);

		//Read file
		int line_nr = 1;
		int no_rooms = 0;
		int no_actors = 0;

		//Read line
		for (std::string line; std::getline(infile, line);)
		{
			istringstream iss(line);
			vector<std::string> tokens;

			//Read tokens
			for (std::string token; std::getline(iss, token, ':');)
				tokens.push_back(token);
			
			try {
				switch (current)
				{
				case META:
					//Read all meta data

					_boarddepth = std::stoi( tokens.at(1) );
					_boardwidth = std::stoi( tokens.at(2) );
					_numactors = std::stoi( tokens.at(3) );

					no_rooms = _boarddepth * _boardwidth+1;
					no_actors = _numactors+1;

					current = ENV;
					break;

				case ENV:
					//Read all environments
					if (--no_rooms > 0) {
						environs.push_back(ctor_map.at(tokens.at(0))(tokens));
					}
					else {
						_environments = environs;
#ifdef _DEBUG
						std::cout << "Loaded " << environs.size() << " rooms." << endl;
#endif
						current = ACT;					
					}
					break;

				case ACT:
					//Read all actors
					if (--no_actors > 0) {
						actors.insert(make_pair(tokens.at(1), actor_map.at(tokens.at(0))(tokens)));
					}
					else {
						Player * pp = new Player(_environments.at(0));
						actors.insert(make_pair("PLAYER", static_cast<Actor *>(pp)));
						_actors = actors;
						_player = pp;
						current = ITEM;
#ifdef _DEBUG
						std::cout << "Loaded " << actors.size() << " actors." << endl;
#endif
					}				
					break;

				case ITEM:
					//Read all items
					placement_map.at(tokens.at(0))(tokens);
#ifdef _DEBUG
					std::cout << "Placed " << tokens.at(0) << "." << endl;
#endif
					break;
				default:
					break;
				}
					
			}
			catch (const std::exception & e)
			{
				infile.close();
				_environments = environs;
				_actors = actors;
				throw load_game_exception("Error while reading section " + std::to_string(current) + " of file. \n\t[" + std::to_string(line_nr) + "] " + line);
			}
			line_nr++;
		}

	}

	void Game::create_actor(std::string type)
	{
		if (type == "PINKELEPHANT")
			_actors.insert(make_pair(PinkElephant::generate_name(), new PinkElephant(&_player->currentroom(),this)));
	}

	void Game::destroy_actor(Actor * a_ptr)
	{
		for (auto it = _actors.begin(); it != _actors.end(); ++it)
			if (it->second == a_ptr) {
				delete it->second;
				_actors.erase(it);
				break;
			}
	}

	Game::~Game()
	{

		//Clean up environments
		while (!_environments.empty())
			delete _environments.back(), _environments.pop_back();

		//Clean up actors
		for (auto it = _actors.begin(); it != _actors.end(); ++it)
			delete it->second;


#ifdef _DEBUG
		std::cout << "Game destructed." << endl;
#endif
	}

	void Game::step()
	{
		switch (_state)
		{
		case INTRO:
			_state = PLAYING;
			break;
		case PLAYING:
			//Refresh all events and tick all rooms
			for (auto e : _environments) {
				e->clear_events();
				e->tick();
			}

			//Let all living actors act
			for (auto a : _actors)
				if (a.second->is_alive())
					a.second->act();
			break;
		case GAME_OVER:
			_screen->println("GAME OVER");

			break;
		default:
			break;
		}
	}

	bool Game::is_game_over() const
	{
		return (_state == GAME_OVER);
	}

	bool Game::player_alive() const
	{
		return _player->is_alive();
	}
	
	bool Game::exit(std::vector<std::string>)
	{
		_state = CHOICE;
		return true;
	}

	bool Game::yes(std::vector<std::string>)
	{
		if (_state == CHOICE) {
			_state = GAME_OVER;
			return true;
		}
		else
			return false;

	}

	bool Game::no(std::vector<std::string>)
	{
		if (_state == CHOICE) {
			_state = PLAYING;
			return true;
		}
		else
			return false;
	}

	bool Game::go(std::vector<std::string> params)
	{
		if (params.empty())
			return false;

		Environment * to_room = get_neighbour_of(&_player->currentroom(), string_to_direction.at(params[0]));

		if (to_room == nullptr)
			return false;

		_player->go_to(to_room);

		_screen->println("Going " + params[0] + "...");
		return true;
	}

	bool Game::bag(std::vector<std::string>)
	{
		const std::vector<unique_ptr<Item>> & inv_ref = _player->inventory();

		if (!inv_ref.empty()) {

			for (auto it = inv_ref.begin(); it != inv_ref.end(); ++it)
				_screen->println((*it)->name()+"\t"+(*it)->description());

		}
		else
			_screen->println("Your bag is empty...");

		return true;
	}

	bool Game::pick(std::vector<std::string> params)
	{
		if (!params.empty()) {
			bool success = _player->pickup(params[0]);
			if (success)
				_screen->println("Picked up " + params[0] + ".");
			else
				_screen->println("Invetory full!");
			return success;
		}

		return false;
	}

	bool Game::drop(std::vector<std::string> params)
	{
		if (!params.empty())
			return _player->drop(params[0]);

		return false;
	}

	bool Game::examine(std::vector<std::string> params)
	{
		if (params.empty())
			return false;

		Actor * actor = nullptr;
		try {
			actor = _actors.at(params[0]);
		}
		catch (out_of_range e)
		{
			//Not a valid actor
		}

		if (actor != nullptr) {
			_screen->println(actor->description());
			return true;
		}
			
		for (auto it = _player->inventory().begin(); it != _player->inventory().end(); ++it)
			if (it->get()->name() == params[0]) {
				_screen->println(it->get()->description());
				return true;
			}


		return false;
	}

	bool Game::use(std::vector<std::string> params)
	{
		if(params.empty())
			return false;

		bool success = false;

		std::string msg = "";

		for (auto it = _player->inventory().begin(); it != _player->inventory().end(); ++it)
			if (it->get()->name() == params[0]) {
				success = it->get()->use(_player, msg);
				break;
			}
				

		if (msg != "")
			_screen->println(msg);

		return success;

	}

	bool Game::clues(std::vector<std::string> params)
	{

		const std::map<Clue::ClueType,Clue> & clue_ref = _player->clues();

		if (!clue_ref.empty()) {

			for (auto it = clue_ref.begin(); it != clue_ref.end(); ++it)
				_screen->println(it->second.name() + " " + it->second.description());

		}
		else
			_screen->println("Your haven't got a clue...");

		return true;
	}

	bool Game::stats(std::vector<std::string>)
	{
		_screen->println("Your stats: ");
		_screen->println("Weight\t" + _player->weight());

		return true;
	}

	bool Game::guess(std::vector<std::string> params)
	{

		if (_player->currentroom().name() != "Dining Room")
			return false;

		

		if (_player->clues().size() == 3) {	//Got all clues
			_state = WIN;
			return true;
		}
		else if (params.size() == 3)
		{

			

			if (_clues.at(Clue::IDENTITY).name() == params[0] &&
				_clues.at(Clue::SCENE).name() == params[1] &&
				_clues.at(Clue::TOOL).name() == params[2])
			{
				_state = WIN;
				return true;
			}

		}

		return false;
	}


	shared_ptr<Game> Game::make_game(shared_ptr<IScreen> screen)
	{
		return shared_ptr<Game>(new Game(screen));
	}

	Game::GameState Game::game_state() const
	{
		return _state;
	}

	void Game::game_state(GameState newState)
	{
		_state = newState;
	}

	std::string Game::win() const
	{
		string win_str =
			"You figured out the identity of the murder and survived the night.\n"
			"The police arrived by noon.\n"
			"Congratulations!\n";

		return win_str;
	}

	std::string Game::introduction() const
	{
		string intro = ""; 

		intro += "You have been invited together with seven other famous people to the\n"
			"mansion of Scrooge McDuck. But the party has barely started before you \n"
			"find the host brutally murdered. All the phone lines are cut and all\n"
			"cars have either flat tires or missing parts.\n"
			"It is now up to you to figure out the identity of the murderer, the\n"
			"location of the murder and the murder weapon before the sun rises at \n"
			"6 am or be killed.\n"
			"Type /'help' for a list of commands.";

		return intro + "\n" +scene();
	}

	std::string Game::commands() const
	{
		return 
			"go\tGo to another environment. (ex. go north)\n"
			"bag\tDisplay contents of your bag.\n"
			"pick\tPick up an item from the floor. (ex. pick ball)\n"
			"drop\tDrop an item from your bag. (ex. drop ball)\n"
			"examine\tExamine an item in your bag or an actor, using their first name.\n\t (ex. examine Scooby)\n"
			"use\tUse an item in your bag. (ex. use Axe)\n"
			"clues\tDisplay all the clues you have deduced so far.\n"
			"guess\tEnd the game by presenting your clues, or guessing freely.\n\tNOTE: You have to be in the Dining Room. (ex. guess Scooby Kitchen Axe)\n";
	}

	std::string Game::choice() const
	{
		return "Quit game\nAre you sure? (y/n)";
	}

	Environment * Game::get_neighbour_of(const Environment * env_ptr, int direction, bool visible) const
	{
		//Use visible flag if only looking for visible neighbours

		for (int i = 0; i < _boardwidth; i++)	{
			for (int j = 0; j < _boarddepth; j++)	{

				if(_environments[i*_boarddepth + j] == env_ptr)
					
					switch (direction)
					{
					case 0:
						if (i < _boardwidth - 1 && (!visible || env_ptr->visible_directions()[0]) )
							return _environments[(i + 1)*_boarddepth + j];
						else
							return nullptr;
						break;
					case 1:
						if (j < _boarddepth - 1 && (!visible || env_ptr->visible_directions()[1]))
							return _environments[i*_boarddepth + (j + 1)];
						else
							return nullptr;
						break;
					case 2:
						if (i > 0 && (!visible || env_ptr->visible_directions()[2]))
							return _environments[(i - 1)*_boarddepth + j];
						else
							return nullptr;
						break;
					case 3:
						if (j > 0 && (!visible || env_ptr->visible_directions()[3]))
							return _environments[i*_boarddepth + (j - 1)];
						else
							return nullptr;
						break;
					case 4:
						if (i < _boardwidth - 1 && j < _boarddepth - 1 && (!visible || env_ptr->visible_directions()[4]))
							return _environments[(i + 1)*_boarddepth + (j + 1)];
						else
							return nullptr;
						break;
					case 5:
						if (i > 0 && j < _boarddepth - 1 && (!visible || env_ptr->visible_directions()[5]))
							return _environments[(i - 1)*_boarddepth + (j + 1)];
						else
							return nullptr;
						break;
					case 6:
						if (i < _boardwidth - 1 && j > 0 && (!visible || env_ptr->visible_directions()[6]))
							return _environments[(i + 1)*_boarddepth + (j - 1)];
						else
							return nullptr;
						break;
					case 7:
						if (i > 0 && j > 0 && (!visible || env_ptr->visible_directions()[7]))
							return _environments[(i - 1)*_boarddepth + (j - 1)];
						else
							return nullptr;
						break;
					default:
						return nullptr;
						break;
					}

			}
		}

		return nullptr;
	}

	std::vector<Environment*> Game::get_neighbours_of(const Environment * current_room, bool visible) const
	{
		std::vector<Environment *> neighbours;

		for (int i = 0; i < 8; ++i) {

			Environment * env_ptr = nullptr;

			env_ptr = get_neighbour_of(current_room, i, visible);

			neighbours.push_back(env_ptr);

		}

		return neighbours;
	}

	std::vector<Actor*> Game::get_actors_in(const Environment * env)
	{
		std::vector<Actor*> actors;

		for (const auto a : _actors)
			if (a.second->currentroom() == *env)
				actors.push_back(a.second);

		if (_player->currentroom() == *env)
			actors.push_back(_player);

		return actors;
	}

	int Game::no_of_actors_in(const Environment * env_ptr) const
	{
		int counter = 0;

		for (const auto pair : _actors)
			if (pair.second->currentroom() == *env_ptr)
				counter++;

		if (_player->currentroom() == *env_ptr)
			counter++;

		return counter;
	}

	void Game::game_over()
	{
		_state = GAME_OVER;
	}

	std::string Game::scene() const
	{
		string state = "";
		const Environment & room = _player->currentroom();

		//Print room description
		state += room.print();

		if (room.is_visible()) {
			//What exits exist?
			state += "\n\nExits:";

			const std::vector<Environment *> neighbouring_rooms = get_neighbours_of(&room, true);

			for (int i = 0; i < 8; i++) {
				if (neighbouring_rooms[i] != nullptr)
					state += "\n" + direction_to_string.at(i) + ":\t" + neighbouring_rooms[i]->name();
			}

			//Who are there?
			if (no_of_actors_in(&room) > 1) {
				state += "\n\nPeople in the room:";
				for (auto it = _actors.begin(); it != _actors.end(); ++it)
					if (it->second->currentroom() == room)
						state += "\n" + it->second->name();
			}

				//What are they doing?
				state += "\nEvents:";
				std::vector<std::string> es = room.events();
				for (auto it = es.begin(); it != es.end(); ++it)
					state += "\n" + *it;

		}
		

#ifdef _DEBUG
		state += "\n\nDEBUG INFO:\n";

		for (auto a : _actors)
			state += a.first + "\t" + a.second->currentroom().name() + "\t" + a.second->description() + "\n";
#endif

		return state;
	}

	bool Game::help(std::vector<std::string>)
	{
		_state = HELP;
		return true;
	}

	//IPrintable
	std::string Game::print() const
	{
		return (this->*state_text.at(_state))();
	}

	bool Game::is_visible() const
	{
		return true;
	}

	//IControllable
	Game::FuncMap Game::map_of_functions() const
	{
		return _func_map;
	}

}