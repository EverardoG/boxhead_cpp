// #pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"

/*
    Class for encapsulating game and objects inside it, along with updates and renders
 */

#ifndef GAME_H
#define GAME_H

class Game
{
    private:
        //Variables
        sf::RenderWindow* window; // want to be able to delete this so we want to dynamically allocate it
        sf::VideoMode videomode;
        sf::Event ev;

        Player player;

        // Functions
        void initVariables();
        void initWindow();

    public:
        // Constructors and Destructors
        Game();
        virtual ~Game();

        // Functions
        void pollEvents();
        void update();
        void render();

        //Accessors
        const bool running() const;
};

#endif