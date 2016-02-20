#ifndef _ICONTROLLABLE_
#define _ICONTROLLABLE_

#include "IConsole.hpp"

namespace cluedo
{

	template <typename T>
	class IControllable
	{
	public:
	
		typedef bool(T::*FuncPtr)(std::vector<std::string>);
		typedef std::map<std::string, FuncPtr> FuncMap;

		virtual FuncMap map_of_functions() const = 0;
		virtual ~IControllable() {}
		
	};

}

#endif