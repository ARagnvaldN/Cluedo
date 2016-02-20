#include "MurderActor.hpp"
#include "../Environments/Environment.hpp"
#include <random>
#include "../Items/MurderClue.hpp"

namespace cluedo {

	MurderActor::MurderActor(std::string firstname, std::string lastname, std::string type, int weight, Environment * env) : Actor(firstname,lastname,type,weight,env)
	{
	
	}

	void MurderActor::act()
	{
		//Sneaks aroud the mansion, murdering if alone with an actor and no others close by.
		const Environment & this_env = currentroom();

		//If no witnesses
		bool no_witness = true;
		for (Environment * e : this_env.neighbours())
			if(e != nullptr && e->no_of_actors() > 0 )
			{
				no_witness = false;
				break;
			}


		//If alone with actor
		if (this_env.no_of_actors() == 2 && no_witness) {	
				
			//Kill
			bool success = false;
			for (Actor * a : this_env.all_actors())
				if (a != this && a->is_alive()) {
					a->die();
					success = true;
				}
			if(success)
				talk();
		}

		//Else sneak about
		else {

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

		}
		
		


	}

	void MurderActor::talk()
	{
		currentroom().push_event(name() + ": Bleed!");
	}

}
