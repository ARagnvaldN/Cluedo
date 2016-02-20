#ifndef _ICONSOLE_
#define _ICONSOLE_

namespace cluedo
{ 

	class IConsole 
	{

	public:

		virtual bool prompt() const = 0;
		virtual ~IConsole() {};
	};

}

#endif