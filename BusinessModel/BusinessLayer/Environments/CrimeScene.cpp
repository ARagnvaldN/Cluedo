#include "CrimeScene.hpp"


cluedo::CrimeScene::CrimeScene(std::string name, std::string desc, Game * game_ptr) : Room(name, desc, game_ptr)
{
}

bool cluedo::CrimeScene::is_crime_scene() const
{
	return true;
}
