#ifndef _SCREEN_
#define _SCREEN_

#include "Interfaces/IScreen.hpp"
#include "Interfaces/IPrinter.hpp"
#include <memory>
#include "PrintBuffer.hpp"

namespace cluedo
{

	class Screen : public IScreen
	{
	private:
		PrintBuffer _buffer;
		std::vector<IPrintable *> _printables;

		Screen();
		void flush() const;
		void h_line() const;
		void h_line_bold() const;
	public:
		virtual ~Screen();

		//IScreen
		virtual void print(std::string) override;
		virtual void println(std::string) override;
		virtual void print(const IPrintable &) const override;
		virtual void print_scene() const override;

		//IPrinter
		virtual void add_printable(IPrintable *);
		virtual void remove_printable(IPrintable *);
		virtual void clear_printables();

		static std::shared_ptr<IScreen> make_screen();
	};



}

#endif