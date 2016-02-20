#ifndef PANICACTOR
#define PANICACTOR

#include "Actor.hpp"

namespace cluedo {

	class Environment;

	class PanicActor : public Actor
	{
	public:
		PanicActor(std::string, std::string, std::string, int weight, Environment *);
		virtual void act() override;
		virtual void talk() override;
	};

}

#endif //! PANICACTOR