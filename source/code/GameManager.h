#pragma once
#ifndef GAME_H
#define GAME_H
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "leveling.h"
#include <fstream>
#include <string>
#include "entity.h"
#include "collision.h"
using namespace sf;

class Game {
public:
	void StartGame();
	void Quit();
};

#endif