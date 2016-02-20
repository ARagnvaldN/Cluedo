#ifndef _ISCREEN_
#define _ISCREEN_

#include <iostream>
#include "IPrintable.hpp"
#include "IPrinter.hpp"

namespace cluedo
{

	class IScreen : public IPrinter
	{
	public:
		virtual void print(std::string) = 0;			//Write a string to the screen
		virtual void println(std::string) = 0;		//Write a string followed by newline
		virtual void print(const IPrintable &) const = 0;	//Print an environment
		virtual void print_scene() const = 0;				//Print all observables
		virtual ~IScreen() {}

		//IPrinter
		virtual void add_printable(IPrintable *) = 0;
		virtual void remove_printable(IPrintable *) = 0;
		virtual void clear_printables() = 0;

	};


}

#endif