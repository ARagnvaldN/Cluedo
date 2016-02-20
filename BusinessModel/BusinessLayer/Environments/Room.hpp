#ifndef _ROOM_
#define _ROOM_

#include "../../Common.hpp"
#include "Environment.hpp"
#include "../Game.hpp"


namespace cluedo {

	class Item;

	class Room : public Environment
	{
	private:
		std::vector<int> _visible_directions; 
		std::vector<int> _possible_directions;

	protected:
		std::string _name;
		std::string _description;
		int _num_directions;

	public:
		Room(std::string, std::string, Game * game);

		//Environment
		virtual std::string name() const override;
		virtual std::string description() const override;

		virtual const std::vector<int> & visible_directions() const override;
		virtual const std::vector<int> & possible_directions() const override;

		//IPrintable
		virtual std::string print() const override;
		virtual bool is_visible() const override;


	};



}



#endif //_ROOM_