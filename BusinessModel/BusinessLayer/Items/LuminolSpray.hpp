#ifndef LUMINOLSPRAY
#define LUMINOLSPRAY


#include "Item.hpp"

namespace cluedo {


	class LuminolSpray : public Item
	{
	public:
		LuminolSpray(std::string, std::string);

		virtual bool use(Player *, std::string &) override;
	};

}

#endif //!LUMINOLSPRAY