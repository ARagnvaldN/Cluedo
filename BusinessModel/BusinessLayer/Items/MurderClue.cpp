#include "MurderClue.hpp"
#include "../Actors/Player.hpp"

namespace cluedo {
	MurderClue::MurderClue(std::string name, std::string desc, std::string m, Player * p) 
		: Item(name, desc), _player(p), _murderer(m)
	{

	}

	std::string cluedo::MurderClue::description() const
	{
		_player->receive_clue(Clue::IDENTITY, Clue(_murderer,"This is the murderer."));

		return "This is critical evidence";
	}
}