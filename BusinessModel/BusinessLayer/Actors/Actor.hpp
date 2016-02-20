#ifndef _ACTOR_
#define _ACTOR_

#include "../../Common.hpp"
#include "../Items/Item.hpp"

namespace cluedo 
{
	class Item;
	class Environment;

	class Actor
	{
	protected:
		
		const size_t INVENTORY_SIZE = 10;
		std::string _firstname;
		std::string _lastname;
		std::string _type;
		int _weight;
		int _bodyheat;
		std::vector<std::unique_ptr<Item>> _inventory;
		std::vector<Item *> _clues;
		bool _alive;

		Environment * _currentenv;

	public:
		Actor(std::string, std::string, std::string, int, Environment *);
		virtual ~Actor() { };

		std::string name() const;
		std::string type() const;
		int weight() const;

		bool is_alive() const;

		bool pickup(std::string);
		bool drop(std::string);
		virtual bool go_to(Environment *);

		void destroy(Item *);

		Environment & currentroom();
		const std::vector<std::unique_ptr<Item>> & inventory() const;
		void receive(std::unique_ptr<Item>);
		
		virtual void act() = 0;
		virtual void die();
		virtual void talk() = 0;
		virtual void cool_down();
		virtual std::string description() const;

	};



}

#endif