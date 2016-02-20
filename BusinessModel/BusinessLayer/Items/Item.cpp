#include "Item.hpp"
#include "../Actors/Player.hpp"

namespace cluedo {


	Item::Item(std::string name, std::string desc) : _name(name), _description(desc)
	{

	}

	std::string Item::description() const
	{
		return _description;
	}

	std::string Item::name() const 
	{
		return _name;
	}

	bool Item::use(Player *, std::string & msg)
	{
		msg = "Nothing happened.";
		return true;
	}

}