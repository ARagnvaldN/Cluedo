#ifndef MURDERACTOR
#define MURDERACTOR

#include "Actor.hpp"

namespace cluedo {

	class Environment;

	class MurderActor : public Actor
	{

	public:
		MurderActor(std::string, std::string, std::string, int, Environment *);
		virtual void act() override;
		virtual void talk() override;

	};
}
#endif // !MURDERACTOR
