#ifndef _PLAYER_
#define _PLAYER_

#include "../../Common.hpp"
#include "Actor.hpp"
#include "../Items/Clue.hpp"

namespace cluedo {

	class Environment;
	class Item;

	class Player : public Actor
	{

		std::map<Clue::ClueType,Clue> _clues;

	public:
		const std::map<Clue::ClueType,Clue> & clues();

		Player(Environment * env_ptr);
		virtual ~Player() {};
		
		void receive_clue(Clue::ClueType, Clue);
		void hallucinate();

		virtual bool go_to(Environment *) override;

		//ACTOR
		virtual void act() override;
		virtual void talk() override;
	};

}
#endif //!_PLAYER_