#ifndef _IPRINTER_
#define _IPRINTER_

#include <vector>
#include "IPrintable.hpp"

namespace cluedo {

	class IPrinter
	{

	public:
		virtual void add_printable(IPrintable *) = 0;
		virtual void remove_printable(IPrintable *) = 0;
		virtual void clear_printables() = 0;

	};

}


#endif