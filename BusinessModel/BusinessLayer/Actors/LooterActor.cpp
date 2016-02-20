#include "LooterActor.hpp"

cluedo::LooterActor::LooterActor(std::string firstname, std::string lastname, std::string type, int weight, Environment * env_ptr)
	: Actor(firstname,lastname,type,weight,env_ptr)
{
}

void cluedo::LooterActor::act()
{
	//If can carry more
	if (!currentroom().contents().empty() && inventory().size() < INVENTORY_SIZE) {
		_inventory.push_back(std::move(currentroom().contents().back()));
		currentroom().contents().pop_back();

		talk();
	}
	//Go to another room
	else
	{
		std::vector<Environment *> possible_moves = currentroom().neighbours();

		Environment * next_room = nullptr;
		while (true) {
			unsigned int i = std::rand() % 4;
			next_room = possible_moves[i];
			if (next_room != nullptr) {
				go_to(next_room);
				break;
			}
		}
	}

}

void cluedo::LooterActor::talk()
{
	currentroom().push_event(name() + ": So terrible, all of this.");
}

