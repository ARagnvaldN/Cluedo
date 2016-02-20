#include "Actor.hpp"
#include "../Environments/Environment.hpp"
#include "../Items/ItemDispencerBase.hpp"

namespace cluedo
{
	Actor::Actor(std::string firstname, std::string lastname, std::string race, int weight, Environment * env_ptr)
		: _firstname(firstname),
		_lastname(lastname),
		_type(race),
		_weight(weight),
		_bodyheat(38),
		_currentenv(env_ptr)
		
	{
		_alive = true;
	}

	bool Actor::is_alive() const
	{
		return _alive;
	}

	void Actor::die()
	{
		_alive = false;
		while (!_inventory.empty()) {
			_currentenv->place(std::move(_inventory.back()));
			_inventory.pop_back();
		}
		_currentenv->place(std::move(std::unique_ptr<Item>(new Item("Blood","A pint of blood."))));
	}

	bool Actor::pickup(std::string srch_str)
	{
		std::vector < std::unique_ptr < Item >> & content_ref = _currentenv->contents();

		if (_inventory.size() >= INVENTORY_SIZE)
			return false;

		for (auto it = content_ref.begin(); it != content_ref.end(); ++it)

			if ((*it)->name() == srch_str) {

				if (ItemDispenserBase * ip = dynamic_cast<ItemDispenserBase *>(it->get()))
					_inventory.push_back(ip->dispense());
				else {
					_inventory.push_back(std::move(*it));
					content_ref.erase(it);
				}
				
				return true;
			}
				
		return false;
	}

	bool Actor::drop(std::string srch_str)
	{
		
		for (auto it = _inventory.begin(); it != _inventory.end(); ++it)
		{
			if ((*it)->name() == srch_str) {
				_currentenv->place(std::move(*it));
				_inventory.erase(it);
				return true;
			}
		}

		return false;
	}

	bool Actor::go_to(Environment * env_ptr)
	{
		_currentenv->push_event(name() + " left.");
		_currentenv = env_ptr;
		_currentenv->push_event(name() + " entered.");

		return true;
	}

	void Actor::destroy(Item * item)
	{
		auto it = _inventory.begin();
		while (it != _inventory.end()) {
			if (it->get() == item) {
				//THIS DOESNT WORK
				_inventory.erase(it); 
				return;
			}
			else
				++it;
		}
	}

	Environment & Actor::currentroom()
	{
		return *_currentenv;
	}

	const std::vector<std::unique_ptr<Item>> & Actor::inventory() const
	{
		return _inventory;
	}

	void Actor::receive(std::unique_ptr<Item> item)
	{
		_inventory.push_back(std::move(item));
	}

	std::string Actor::type() const
	{
		return _type;
	}

	int Actor::weight() const
	{
		return _weight;
	}

	std::string Actor::name() const
	{
		return _firstname + " " + _lastname;
	}

	void Actor::cool_down()
	{
		_bodyheat--;
	}

	std::string Actor::description() const
	{
		if (is_alive())
			return "You see a " + _type;
		else {
			if (_bodyheat > 30)
				return "You see a gutted " + _type + ", the body is still warm.";
			else
				return "You see a gutted " + _type + ", the body is cold";
		}
	}

}