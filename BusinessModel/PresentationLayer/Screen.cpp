#include "Screen.hpp"
#include <cstdlib>

using namespace std;

namespace cluedo
{
	Screen::Screen() : _buffer(20)
	{
	
	}

	Screen::~Screen()
	{
#ifdef _DEBUG
		cout << "Screen destructed." << endl;
#endif
	}

	void Screen::add_printable(IPrintable * printable)
	{
		_printables.push_back(printable);
	}

	void Screen::remove_printable(IPrintable * printable)
	{
		for (auto i = _printables.begin(); i != _printables.end(); ++i)
			if (printable == *i)
				_printables.erase(i);
	}

	void Screen::clear_printables()
	{
		_printables.clear();
	}

	void Screen::flush() const
	{

#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
		
	}

	void Screen::h_line() const
	{
		cout << "------------------------------------------------------------------------" << endl;
	}

	void Screen::h_line_bold() const
	{
		cout << "=======================================================================" << endl;
	}

	void Screen::print(string s)	
	{	
		_buffer.enque(s);
	}
	void Screen::println(string s)
	{
		_buffer.enque(s+"\n");
	}

	void Screen::print(const IPrintable & p) const
	{
		cout << p.print();
	}

	void Screen::print_scene() const
	{
		flush();

		h_line();
		
		//Print scene
		for (IPrintable * p : _printables)
			if(p->is_visible())
				cout << p->print() << endl;
		
		h_line_bold();

		//Print console:
		for (std::string s : _buffer)
			cout << s;
		
	}

	shared_ptr<IScreen> Screen::make_screen()
	{
		return std::shared_ptr<IScreen>(new Screen());
	}
}