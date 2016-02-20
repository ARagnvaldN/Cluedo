#include "DarkRoom.hpp"

namespace  cluedo {
	DarkRoom::DarkRoom(std::string name, std::string desc, Game * game) : Room(name, desc, game)
	{
		_visible_directions = std::vector<int>{ 0,0,0,0,0,0,0,0 };
	}

	const std::vector<int> & DarkRoom::visible_directions() const
	{
		return _visible_directions;
	}

	std::string DarkRoom::description() const
	{
		return "The room is pitch black. You can't see a thing.";
	}

	bool DarkRoom::is_visible() const
	{
		return false;
	}

}

