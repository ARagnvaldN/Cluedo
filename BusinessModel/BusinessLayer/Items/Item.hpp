#ifndef _ITEM_
#define _ITEM_

#include <string>

namespace cluedo
{
	class Player;

	class Item
	{

	private:
		std::string _name;
		std::string _description;

	public:
		Item(std::string, std::string);
		virtual ~Item() {}

		std::string name() const;
		virtual std::string description() const;
		virtual bool use(Player *, std::string &);

	};


}

#endif