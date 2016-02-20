#include "Room.hpp"
#include "Environment.hpp"
#include "../Game.hpp"
#include "../Items/Item.hpp"

namespace cluedo {

	Room::Room(std::string name, std::string description, Game * game) : Environment(game), _name(name), _description(description)
	{
		_possible_directions = std::vector<int>{ 1, 1, 1, 1, 0, 0, 0, 0 };
		_visible_directions = std::vector<int>{ 1, 1, 1, 1, 0, 0, 0, 0 };
	}

	std::string Room::name() const
	{
		return _name;
	}

	std::string Room::description() const
	{
		return _description;
	}

	const std::vector<int>& Room::visible_directions() const
	{
		return _visible_directions;
	}

	const std::vector<int>& Room::possible_directions() const
	{
		return _possible_directions;
	}

	

	std::string Room::print() const
	{
		std::string print_str = "";

		print_str += "------------------\n";
		print_str += name()+"\n";
		print_str += "------------------\n";
		print_str += description();
		if (is_visible() && !_contents.empty()) {
			print_str += "\nScattered around on the floor you find:";
			for (auto it = _contents.cbegin(); it != _contents.cend(); ++it)
				print_str += "\n" + (*it)->name();
		}
		return print_str;
	}

	

	bool Room::is_visible() const
	{
		return true;
	}

}