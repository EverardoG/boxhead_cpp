#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState : public GameState
{
    private:
        // Functions
        void initVariables();
        sf::Font menu_font;
        sf::Text menu_text;

    public:
        // Constructors and Destructors
        MainMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, GameState*> _adjStates);
        virtual ~MainMenuState();

        // Functions
        std::string update(std::unordered_map<std::string, bool> _input_map);
        void render();

        // states you can get to from this state
        std::unordered_map<std::string, GameState*> adjStates;
};

#endif