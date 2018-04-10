/*
* WarGame - small 2D game for studies
* Copyright (C) 2018  Bertrand Caplet <bbcorp@chunkz.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "../include/Map.h"
#include <iostream>
#include <fstream>

using namespace std;

engine::Map::Map(const string fileName)
{
	//loadBmp(fileName);
}

void engine::Map::loadBmp(const std::string filename)
{
	std::ifstream dataFile(filename);

	char my_character;
	int number_of_lines = 0;

	while (!dataFile.eof()) {

		dataFile.get(my_character);
		cout << my_character;
		if (my_character == '\n') {
			++number_of_lines;
		}
	}
	cout << "NUMBER OF LINES: " << number_of_lines << endl;
/*


	std::string name;
	std::ifstream dataFile(filename);
	while (!dataFile.fail() && !dataFile.eof())
	{
		dataFile >> name;
		cout << name << endl;
	}*/



	/*FILE* f = fopen(filename.data(), "rb");
	uint8_t info[54];
	fread(info, sizeof(uint8_t), 54, f); // read the 54-byte header

										 // extract image height and width from header
	uint16_t width = *(int*)&info[18];
	uint16_t height = *(int*)&info[22];

	uint16_t size = 3 * width * height;
	uint8_t *m_bmpPixelData = new uint8_t[size]; // allocate 3 bytes per pixel
	fread(m_bmpPixelData, sizeof(uint8_t), size, f); // read the rest of the m_bmpPixelData at once
	fclose(f);

	for (uint16_t i = 0; i < size; i += 3)
	{
		unsigned char tmp = m_bmpPixelData[i];
		m_bmpPixelData[i] = m_bmpPixelData[i + 2];
		m_bmpPixelData[i + 2] = tmp;
	}*/

}