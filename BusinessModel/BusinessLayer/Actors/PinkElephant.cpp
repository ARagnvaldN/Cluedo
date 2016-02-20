#include "PinkElephant.hpp"
#include "../Environments/Environment.hpp"

namespace cluedo {

	int PinkElephant::_id;

	PinkElephant::PinkElephant(Environment * env_ptr, Game * game_ptr)
		: Actor("Pink", "Elephant", "elephant(?)", 0, env_ptr), _timer(5), _game(game_ptr)
	{
	}

	void PinkElephant::act()
	{
		//Wanders around the mansion until it fades

		std::vector<Environment *> possible_moves = currentroom().neighbours();

		Environment * next_room = nullptr;

		unsigned int i = std::rand() % 8;
		next_room = possible_moves[i];

		if (next_room != nullptr)
			go_to(next_room);
		else
			talk();

	}
	void PinkElephant::talk()
	{
		currentroom().push_event(name() + ":Excuse me, do you know where I am?");
	}

	void PinkElephant::fade()
	{
		if (_timer-- < 0)
			_game->destroy_actor(this);
	}

	std::string PinkElephant::generate_name()
	{
		return "Pink:" + std::to_string(_id++);
	}


}
