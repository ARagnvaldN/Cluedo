#include "LuminolSpray.hpp"
#include "../Actors/Player.hpp"
#include "../Environments/Environment.hpp"
#include "Clue.hpp"

namespace cluedo {

	LuminolSpray::LuminolSpray(std::string name, std::string desc) : Item(name, desc)
	{

	}

	bool cluedo::LuminolSpray::use(Player * user, std::string & msg)
	{

		if (user->currentroom().is_crime_scene()) {
			user->receive_clue(Clue::SCENE,Clue(user->currentroom().name(), "This is the scene of crime."));
			msg = "You spray Luminol, it reveals traces of blood.";
		}
		else
			msg = "You spray Luminol, no traces of blood.";



		return true;
	}

}