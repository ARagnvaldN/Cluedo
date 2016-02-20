#include "PanicActor.hpp"
#include "../Environments/Environment.hpp"
#include <random>

namespace cluedo {

	PanicActor::PanicActor(std::string firstname, std::string lastname, std::string type, int weight, Environment * env_ptr) : Actor(firstname, lastname, type, weight, env_ptr)
	{

	}

	void PanicActor::act()
	{
		//Panicking: running from room to room, screaming.

		std::vector<Environment *> possible_moves = currentroom().neighbours();

		Environment * next_room = nullptr;
		while (true) {
			unsigned int i = std::rand() % 8;
			next_room = possible_moves[i];
			if (next_room != nullptr) {
				go_to(next_room);
				break;
			}
		}

		talk();
				

	}

	void PanicActor::talk()
	{
		currentroom().push_event(name() + ": We're all gonna die!!!");
	}

}


