#include "Spirits.hpp"
#include "../Actors/Player.hpp"

namespace cluedo {

	Spirits::Spirits(std::string name, std::string desc) : Item(name,desc)
	{
	}

	bool Spirits::use(Player * p_ptr, std::string & msg)
	{
		p_ptr->hallucinate();
		msg = "You feel a bit tipsy.";
		p_ptr->destroy(this);
		

		return true;
	}

}
