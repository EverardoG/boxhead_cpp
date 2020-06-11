#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "dependencies.h"

// need forward declaration of game so we can use it in GameView
class GameView
{
    protected:
        sf::RenderWindow* window = nullptr; // want to be able to delete this so we want to dynamically allocate it
        sf::Clock clock;
        std::string next_view;

    public:
        // Constructors and Destructors
        GameView(sf::RenderWindow* _window) { this->window = _window; clock.restart(); };
        virtual ~GameView() {};

        // Functions
        virtual void update() = 0;
        virtual void render() = 0;

        // Accessors
        bool switchView() { return !this->next_view.empty(); };
        std::string getNextView() { return this->next_view; };
};

#endif