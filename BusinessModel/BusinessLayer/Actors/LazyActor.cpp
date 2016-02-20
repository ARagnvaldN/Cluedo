#include "LazyActor.hpp"
#include "../Environments/Environment.hpp"

namespace cluedo {

	LazyActor::LazyActor(std::string firstname, std::string lastname, std::string race, int weight, Environment * env_ptr) : Actor(firstname, lastname, race, weight, env_ptr)
	{

	}

	std::string cluedo::LazyActor::description() const
	{
		if (is_alive())
			return name() + " is fast asleep.";
		else
			return name() + " seems to have fallen asleep for the last time.";
	}

	void cluedo::LazyActor::act()
	{
		talk();

	}

	void cluedo::LazyActor::talk()
	{
		currentroom().push_event(name() + ": zzZZZzz");
	}

}