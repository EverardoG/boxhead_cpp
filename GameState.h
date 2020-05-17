#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "dependencies.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

// need forward declaration of game so we can use it in gamestate
class GameState
{
    protected:
        sf::RenderWindow* window = nullptr; // want to be able to delete this so we want to dynamically allocate it
        std::unordered_map<std::string, bool> input_map; // key is the input, value is True if that input is being pressed/used
        sf::Clock clock;

    public:
        // Constructors and Destructors
        GameState(sf::RenderWindow* _window, std::unordered_map<std::string, GameState*> _adjStates) { this->window = _window; this->adjStates = _adjStates; clock.restart(); };
        virtual ~GameState() {};

        // Functions
        virtual std::string update(std::unordered_map<std::string, bool> _input_map) = 0;
        virtual void render() = 0;

        // states you can get to from this state
        std::unordered_map<std::string, GameState*> adjStates;
};

#endif