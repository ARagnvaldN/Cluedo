#include "TrapRoom.hpp"
#include "../Actors/Actor.hpp"

namespace cluedo {

	TrapRoom::TrapRoom(int weight_limit,bool sprung, std::string name, std::string desc, Game * g_ptr) 
		: Room(name, desc, g_ptr), _weightlimit(weight_limit), _trapsprung(sprung)
	{

	}

	void cluedo::TrapRoom::tick()
	{
		if(!_trapsprung)	//Trap can only spring once

			for (Actor * a : _game->get_actors_in(this))
				if (a->weight() > _weightlimit) {
					push_event("A trap door opens underneath " + a->name() + ".");
					a->die();
					push_event(a->name() + " died.");
					_trapsprung = true;
					break;
				}

	}

}