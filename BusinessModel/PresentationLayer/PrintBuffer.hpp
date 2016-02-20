#ifndef PRINTBUFFER
#define PRINTBUFFER

#include <queue>
#include "../Common.hpp"

namespace cluedo {

	class PrintBuffer
	{
		size_t _buffer_size;
		std::deque<std::string> _buffer;

	public:
		PrintBuffer(int);
		void enque(std::string);
		void clear();
		std::deque<std::string>::iterator begin();
		std::deque<std::string>::const_iterator begin() const;
		std::deque<std::string>::iterator end();
		std::deque<std::string>::const_iterator end() const;
	};

}

#endif // !PRINTBUFFER
