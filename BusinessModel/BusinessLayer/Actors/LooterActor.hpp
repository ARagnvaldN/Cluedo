#ifndef _LOOTERACTOR_
#define _LOOTERACTOR_

#include "Actor.hpp"
#include "../Environments/Environment.hpp"

namespace cluedo {

	class LooterActor : public Actor
	{

	public:
		LooterActor(std::string, std::string, std::string, int, Environment *);
		virtual void act() override;
		virtual void talk() override;
	};

}

#endif // !_LOOTERACTOR_
