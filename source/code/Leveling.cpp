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
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			f1 >> currentMap[i][j];
		}
	}
}


//0-������ ���� , 1-������ , 2-����� , 3-���� , 4-���� , 5-���, 6-����� ������ 7-����� �������
void LevelManager::DrawMap(){
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			Tile* tile;
			std::cout << currentMap[i][j] << " ";
			switch (currentMap[i][j]) {
			case '0':
				tile = new Tile(image, j * 48, i * 48, 22 * 16, 0, 16, 16, false, true, 0);
				break;
			case '1':
				tile = new Tile(image, j * 48, i * 48, 16 * 16, 0, 16, 16, true, false, 0);
				break;
			case '2':
				tile = new Tile(image, j * 48, i * 48, 16 * 16, 16, 16, 16, false, false, 0);
				break;
			case '3':
				tile = new Tile(image, j * 48, i * 48, 16 * 16, 16 * 2, 16, 16, false, false, 0);
				break;
			case '4':
				tile = new Tile(image, j * 48, i * 48, 17 * 16, 16 * 2, 16, 16, false, true, 1);
				break;
			case '5':
				tile = new Tile(image, j * 48, i * 48, 18 * 16, 16 * 2, 16, 16, false, true, 0);
				break;
			case '6':
				tile = new Tile(image, j * 48, i * 48, 22 * 16, 0, 16, 16, false, true, 0);
				break;
			case '7':
				tile = new Tile(image, j * 48, i * 48, 22 * 16, 0, 16, 16, false, true, 0);
				break;
			}
			tiles.push_back(tile);
		}
		std::cout << std::endl;
	}
}
