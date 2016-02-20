#ifndef SPIRITS
#define SPIRITS

#include "Item.hpp"

namespace cluedo {

	class Spirits : public Item
	{
	public:
		Spirits(std::string,std::string);
		virtual bool use(Player *, std::string &) override;

	};
}
#endif // !SPIRITS
