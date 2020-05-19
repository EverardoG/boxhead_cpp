#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <iostream>
#include <chrono>
#include <math.h>
#include <random>
#include "Helper.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define PI 3.14159265

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH  800

#define PLAYER_SPEED 3.0f
#define ZOMBIE_SPEED 1.0f
#define NUM_ZOMBIES 50

#define CHARACTER_SIZE sf::Vector2f(30.f, 40.f)

#define PLAYER_SPAWN_X 400
#define PLAYER_SPAWN_Y 400

#endif