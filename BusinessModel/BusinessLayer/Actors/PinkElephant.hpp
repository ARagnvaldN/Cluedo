#ifndef PINKELEPHANT
#define PINKELEPHANT

#include "Actor.hpp"

namespace cluedo {

	class Game;

	class PinkElephant : public Actor
	{
		static int _id;
		int _timer;
		Game * _game;
	public:
		PinkElephant(Environment *, Game *);
		virtual void act() override;
		virtual void talk() override;

		void fade();

		static std::string generate_name();
	};
}
#endif // !PINKELEPHANT
