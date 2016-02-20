#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include <string>
#include <vector>

#include "../../Common.hpp"
#include "../Game.hpp"
#include "../../PresentationLayer/Interfaces/IPrintable.hpp"

namespace cluedo 
{

	class Game;

	class Environment : public IPrintable
	{

	protected:
		Game * _game;
		std::vector<std::unique_ptr<Item>> _contents;
		std::vector<std::string> _events;

	public:
		Environment(Game *);
		virtual ~Environment() {};

		Game * current_game() const;

		virtual bool operator==(const Environment &) const;

		//Getters
		virtual std::string name() const = 0;
		virtual std::string description() const = 0;
		virtual bool is_crime_scene() const;

		virtual const std::vector<int> & visible_directions() const = 0;
		virtual const std::vector<int> & possible_directions() const = 0;

		//Events
		virtual void push_event(std::string);
		virtual void clear_events();
		virtual std::vector<std::string> events() const;

		virtual Environment* neighbour(int) const;
		virtual std::vector<Environment *> neighbours() const;

		virtual std::vector<Actor *> all_actors() const;
		int no_of_actors() const;

		std::vector<std::unique_ptr<Item>> & contents();

		virtual void place(std::unique_ptr<Item>);

		virtual void tick();

		//IPrintable
		virtual std::string print() const override = 0;
		virtual bool is_visible() const override;

	};




}

#endif
