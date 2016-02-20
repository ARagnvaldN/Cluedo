#ifndef CRIMESCENE
#define CRIMESCENE

#include "Room.hpp"

namespace cluedo {

	class CrimeScene : public Room
	{
	public:
		CrimeScene(std::string, std::string, Game *);
		virtual bool is_crime_scene() const;
	};
}
#endif // !CRIMESCENE
