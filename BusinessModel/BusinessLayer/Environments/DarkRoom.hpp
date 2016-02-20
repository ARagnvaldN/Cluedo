#ifndef DARKROOM
#define DARKROOM

#include "Room.hpp"

namespace cluedo {

	class DarkRoom : public Room
	{
		std::vector<int> _visible_directions;
	public:
		DarkRoom(std::string, std::string, Game *);
		virtual const std::vector<int> & visible_directions() const override;
		
		virtual std::string description() const;
		virtual bool is_visible() const;
	};
}
#endif // !DARKROOM
