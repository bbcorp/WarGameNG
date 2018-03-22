#ifndef PROTOBUF_TEST_H
#define PROTOBUF_TEST_H
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

std::string flatbuffEncode(void);
void flatbuffDecode(std::string buffer, size_t receiveLength);

#endif