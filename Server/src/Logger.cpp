#include "../include/Logger.h"
#include <iostream>

using namespace std;


void engine::Logger::log(string message, bool messageType)
{
	if (messageType) // It's an error
		cerr << "[ERROR] " << message << endl;
	else
		cout << "[INFO] " << message << endl;
}