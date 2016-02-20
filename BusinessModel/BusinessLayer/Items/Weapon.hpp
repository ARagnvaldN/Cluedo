#ifndef WEAPON
#define WEAPON

#include "Item.hpp"

namespace cluedo {

	class Weapon : public Item
	{
	public:
		Weapon(std::string, std::string);
		virtual bool use(Player *, std::string &) override;

	};
}
#endif // !WEAPON
