#ifndef CLUE
#define CLUE

#include "Item.hpp"

namespace cluedo {

	class Clue : public Item
	{
	public:
		enum ClueType { SCENE, TOOL, IDENTITY };

	public:
		Clue(std::string,std::string);
		
	};
}

#endif // !CLUE
