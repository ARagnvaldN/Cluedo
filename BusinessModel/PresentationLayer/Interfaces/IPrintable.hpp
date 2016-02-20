#ifndef _IPRINTABLE_
#define _IPRINTABLE_

#include <string>

namespace cluedo
{

	class IPrintable
	{
	public:
		virtual ~IPrintable() {}
		virtual std::string print() const = 0;
		virtual bool is_visible() const = 0;
	};


}

#endif