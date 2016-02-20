#ifndef TRAPROOM
#define TRAPROOM

#include "Room.hpp"

namespace cluedo {

	class TrapRoom : public Room
	{
		int _weightlimit = 30;
		bool _trapsprung;
	public:
		TrapRoom(int, bool, std::string, std::string, Game *);
		virtual void tick() override;
	};
}

#endif //!TRAPROOM