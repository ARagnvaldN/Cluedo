#ifndef MURDERWEAPON
#define MURDERWEAPON

#include "Weapon.hpp"

namespace cluedo {

	class MurderWeapon : public Weapon
	{
		Player * _player;

	public:
		MurderWeapon(std::string,std::string,Player *);
		std::string description() const override;
	};
}
#endif // !MURDERWEAPON
