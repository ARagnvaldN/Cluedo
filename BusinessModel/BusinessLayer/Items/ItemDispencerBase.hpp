#ifndef ITEMDISPENSERBASE
#define ITEMDISPENSERBASE

#include "Item.hpp"
#include <memory>

namespace cluedo {

	class ItemDispenserBase : public Item
	{
	public:
		ItemDispenserBase(std::string name, std::string desc) : Item(name, desc) {}
		virtual ~ItemDispenserBase() {}
		virtual std::unique_ptr<Item> dispense() = 0;
	};
}
#endif // !ITEMDISPENSERBASE
