#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "dependencies.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
// #include "Game.h"

// need forward declaration of game so we can use it in gamestate
class Game;

class GameState
{
    protected:
        Game* game;
    public:
        // Constructors and Destructors
        GameState(Game* _game) { this->game = _game; };
        virtual ~GameState();

        // Functions
        virtual std::string update() = 0;
        virtual void render() = 0;

        // states you can get to from this state
        std::unordered_map<std::string, GameState*> adjStates;
};

#endif