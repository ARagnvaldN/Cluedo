#ifndef ITEMDISPENCER
#define ITEMDISPENCER

#include "ItemDispencerBase.hpp"

namespace cluedo {

	template <typename T>
	class ItemDispencer : public ItemDispenserBase
	{
	public:
		ItemDispencer(std::string name, std::string desc) : ItemDispenserBase(name, desc) {}
		virtual std::unique_ptr<Item> dispense() override
		{
			return std::move(std::unique_ptr<Item>(new T(name(), description())));
		}
	};
}

#endif // !ITEMDISPENCER
