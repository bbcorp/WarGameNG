#ifndef LOGGER_H
#define LOGGER_H
#include <string>

namespace engine
{
	class Logger
	{
	public:
		static void log(std::string message, bool messageType);
	};

}

#endif
