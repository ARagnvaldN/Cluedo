#ifndef _LAZYACTOR_
#define _LAZYACTOR_

#include "Actor.hpp"

namespace cluedo {

	class LazyActor : public Actor
	{
	public:
		LazyActor(std::string, std::string, std::string, int, Environment *);
		virtual std::string description() const override;
		virtual void act() override;
		virtual void talk() override;
	};

}

#endif //!_LAZYACTOR_
