#ifndef GARDENMAZE
#define GARDENMAZE

#include "Environment.hpp"

namespace cluedo {

	class GardenMaze : public Environment
	{
		static int _counter;
		int _id;
		std::string _name;
		std::vector<int> _possible_directions;
		std::vector<int> _visible_directions;

	public:
		GardenMaze(std::vector<int>,std::vector<int>, Game * game);

		int id() const;

		//Getters
		virtual std::string name() const override;
		virtual std::string description() const override;
		virtual bool is_crime_scene() const;

		//Directions
		virtual const std::vector<int> & visible_directions() const override;
		virtual const std::vector<int> & possible_directions() const override;

		//Printing
		virtual std::string print() const override;
		
		//Operators
		virtual bool operator==(const Environment &) const override;

	};
}
#endif // !GARDENMAZE
