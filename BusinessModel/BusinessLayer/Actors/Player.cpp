#include "Player.hpp"
#include "Actor.hpp"
#include "../Items/Clue.hpp"
#include "../Environments/Environment.hpp"
#include <random>

namespace cluedo {
	const std::map<Clue::ClueType,Clue>& Player::clues()
	{
		return _clues;
	}
	Player::Player(Environment * env_ptr) : Actor("You","", "This is you.", std::rand()%100 + 1, env_ptr)
	{

	}

	void Player::receive_clue(Clue::ClueType type,Clue clue)
	{

		_clues.insert(std::make_pair(type, clue));
	}

	void Player::hallucinate()
	{
		currentroom().current_game()->create_actor("PINKELEPHANT");
	}

	bool Player::go_to(Environment * next_room)
	{
		_currentenv = next_room;
		return true;
	}

	void Player::act()
	{
		//Player does not act
	}

	void Player::talk()
	{
		//Player is a fan of Gordon Freeman
	}

}