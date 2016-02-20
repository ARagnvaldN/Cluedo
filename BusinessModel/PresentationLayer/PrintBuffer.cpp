#include "PrintBuffer.hpp"

namespace cluedo {

	PrintBuffer::PrintBuffer(int size)
	{
		_buffer_size = size;
	}

	void PrintBuffer::enque(std::string line)
	{
		if (_buffer.size() > _buffer_size)
			_buffer.pop_front();

		_buffer.push_back(line);
	}

	void PrintBuffer::clear()
	{
		while (!_buffer.empty())
			_buffer.pop_front();
	}

	std::deque<std::string>::iterator PrintBuffer::begin()	{ return _buffer.begin();}
	std::deque<std::string>::const_iterator PrintBuffer::begin() const { return _buffer.begin(); }
	std::deque<std::string>::iterator PrintBuffer::end() { return _buffer.end(); }
	std::deque<std::string>::const_iterator PrintBuffer::end() const { return _buffer.end(); }

}
