#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp> 
#include "leveling.h"
#include <fstream>
#include <string>

using namespace sf;

void LevelManager::ReadMap(int n) {
	std::string str = "source/map/" + std::to_string(n) + ".txt";
	std::ifstream f1(str);
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			f1 >> currentMap[i][j];
		}
	}
}


//0-пустой тайл , 1-кирпич , 2-сталь , 3-вода , 4-куст , 5-лед, 6-спавн врагов 7-спавн плейира
void LevelManager::DrawMap(){
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			Tile* tile;
			std::cout << currentMap[i][j] << " ";
			switch (currentMap[i][j]) {
			case '0':
				tile = new Tile(image, j * 24, i * 24, 22 * 16, 0, 8, 8, false, true, 0);
				break;
			case '1':
				tile = new Tile(image, j * 24, i * 24, 16 * 16, 16 * 4, 8, 8, true, false, 0);
				break;
			case '2':
				tile = new Tile(image, j * 24, i * 24, 16 * 16, 16 * 4 + 8, 8, 8, false, false, 0);
				break;
			case '3':
				tile = new Tile(image, j * 24, i * 24, 16 * 16, 16 * 4+8, 8, 8, false, false, 0);
				break;
			case '4':
				tile = new Tile(image, j * 24, i * 24, 16 * 16+8, 16 * 4, 8, 8, false, true, 1);
				break;
			case '5':
				tile = new Tile(image, j * 24, i * 24, 17 * 16, 16 * 4, 8, 8, false, true, 0);
				break;
			case 'a':
				tile = new Tile(image, j * 24, i * 24, 19 * 16, 16 * 2, 8, 8, false, false, 0);
				break;
			case 'b':
				tile = new Tile(image, j * 24, i * 24, 19 * 16 + 8, 16 * 2, 8, 8, false, false, 0);
				break;
			case 'c':
				tile = new Tile(image, j * 24, i * 24, 19 * 16, 16 * 2 + 8, 8, 8, false, false, 0);
				break;
			case 'd':
				tile = new Tile(image, j * 24, i * 24, 19 * 16 + 8, 16 * 2 + 8, 8, 8, false, false, 0);
				break;
			}
			tiles.push_back(tile);
		}
		std::cout << std::endl;
	}
}
