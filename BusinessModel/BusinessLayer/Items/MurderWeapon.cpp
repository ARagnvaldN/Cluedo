#include "MurderWeapon.hpp"
#include "../Actors/Player.hpp"

namespace cluedo{

	MurderWeapon::MurderWeapon(std::string name, std::string description, Player * p_ptr) : Weapon(name, description), _player(p_ptr)
	{

	}

	std::string MurderWeapon::description() const
	{

		_player->receive_clue(Clue::TOOL, Clue(name(), "This is the murder weapon."));

		return "There is blood on the weapon.";
	}


}