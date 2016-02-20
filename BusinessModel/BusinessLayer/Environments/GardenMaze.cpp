#include "GardenMaze.hpp"

namespace cluedo {

	int GardenMaze::_counter;

	GardenMaze::GardenMaze(std::vector<int> possDirections, std::vector<int> visDirections, Game * game)
		: Environment(game), _id(_counter++),_possible_directions(possDirections), _visible_directions(visDirections)
	{
	}

	bool GardenMaze::operator==(const Environment & env) const
	{
		if (const GardenMaze * gp = dynamic_cast<const GardenMaze *>(&env))
			return gp->id() == this->id();
		else
			return false;
	}

	int GardenMaze::id() const
	{
		return _id;
	}

	std::string GardenMaze::name() const
	{
		return "Garden Maze";
	}
	std::string GardenMaze::description() const
	{
		return "Three meter tall hedges surround you in the maze.";
	}

	const std::vector<int> & GardenMaze::visible_directions() const
	{
		return _visible_directions;
	}

	const std::vector<int> & GardenMaze::possible_directions() const
	{
		return _possible_directions;
	}

	bool GardenMaze::is_crime_scene() const
	{
		return false;
	}

	std::string GardenMaze::print() const
	{
		std::string print_str = "";

		print_str += "------------------\n";
		print_str += "Garden Maze \n";
		print_str += "------------------\n";
		print_str += description();
		if (is_visible() && !_contents.empty()) {
			print_str += "\nScattered around on the floor you find:";
			for (auto it = _contents.cbegin(); it != _contents.cend(); ++it)
				print_str += "\n" + (*it)->name();
		}
		return print_str;
	}

}
