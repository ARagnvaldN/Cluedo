#include "Weapon.hpp"
#include "../Actors/Player.hpp"
#include "../Environments/Environment.hpp"

namespace cluedo {
	cluedo::Weapon::Weapon(std::string name, std::string desc) : Item(name, desc)
	{

	}

	bool cluedo::Weapon::use(Player * player_ptr, std::string & msg)
	{
		//Kill the closest person
		Actor * actor_to_die = nullptr;
		for (Actor * a : player_ptr->currentroom().all_actors())
			if (a != player_ptr) {
				actor_to_die = a;
				break;
			}

		if(actor_to_die != nullptr && actor_to_die->is_alive()){
			actor_to_die->die();
				msg = "You swing your " + name() + ", and kill " + actor_to_die->name();
				return true;
			}
		else {
			msg = "You swing your " + name() + ", nothing happened.";
			return true;
		}


	}

}