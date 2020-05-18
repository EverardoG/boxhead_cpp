#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "GameView.h"

class MenuView : public GameView
{
    private:
        // Functions
        void initVariables();
        sf::Font menu_font;
        sf::Text menu_text;

    public:
        // Constructors and Destructors
        MenuView(sf::RenderWindow* _window);
        virtual ~MenuView();

        // Functions
        void update();
        void render();
};

#endif