#include "Environment.hpp"
#include "../Items/Item.hpp"
#include "../Actors/Actor.hpp"
#include "../Items/ItemDispencer.hpp"
#include "../Actors/PinkElephant.hpp"

namespace cluedo {

	Environment::Environment(Game * game) : _game(game)
	{
	}

	void Environment::push_event(std::string ev)
	{
		_events.push_back(ev);
	}

	void Environment::clear_events()
	{
		_events.clear();
	}

	std::vector<std::string> Environment::events() const
	{
		return _events;
	}

	bool Environment::is_crime_scene() const
	{
		return false;
	}

	std::vector<Actor*> Environment::all_actors() const
	{
		return _game->get_actors_in(this);
	}

	int Environment::no_of_actors() const
	{
		return _game->no_of_actors_in(this);
	}

	std::vector<std::unique_ptr<Item>>& Environment::contents()
	{
		return _contents;
	}

	void Environment::tick()
	{
		for (Actor * a : _game->get_actors_in(this)) {
			if (!a->is_alive())
				a->cool_down();

			if (PinkElephant * pp = dynamic_cast<PinkElephant *>(a)) {
				pp->fade();
			}
		}

	}

	bool Environment::is_visible() const
	{
		return true;
	}

	Game * Environment::current_game() const
	{
		return _game;
	}

	bool Environment::operator==(const Environment & other) const
	{
		return (other.name() == this->name());
	}

	Environment * Environment::neighbour(int dir) const
	{
		return _game->get_neighbour_of(this, dir);
	}

	std::vector<Environment *> Environment::neighbours() const
	{
		return _game->get_neighbours_of(this);
	}

	void Environment::place(std::unique_ptr<Item> item)
	{
		_contents.push_back(std::move(item));
	}
}