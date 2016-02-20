#ifndef _MURDERCLUE_
#define _MURDERCLUE_

#include "Item.hpp"

namespace cluedo {

	class MurderClue : public Item
	{
		Player * _player;
		std::string _murderer;
	public:
		MurderClue(std::string, std::string, std::string, Player *);
		virtual std::string description() const override;
	};
}
#endif // !MURDERCLUE
