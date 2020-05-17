#include "MenuView.h"

MenuView::MenuView(sf::RenderWindow* _window) : GameView(_window)
{
    this->initVariables();
}

MenuView::~MenuView()
{
}

void MenuView::update()
{
    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
        std::cout << "checking mouse bounds" << std::endl;
        if ( menu_text.getGlobalBounds().contains( sf::Vector2f(sf::Mouse::getPosition( (*this->window) )) ) ) {
            std::cout << "Onwards!" << std::endl;
            next_view = "Main Level";
        }
    }
}

void MenuView::render()
{
    this->window->clear(sf::Color::White);
    this->window->draw(this->menu_text);

}

void MenuView::initVariables()
{

    if (!this->menu_font.loadFromFile("./fonts/pythago0.ttf")) {
        std::cout << "fuck" << std::endl;
    }

    this->menu_text.setFont(menu_font);
    this->menu_text.setString("Play");
    this->menu_text.setCharacterSize(100);
    this->menu_text.setFillColor(sf::Color::Black);
    this->menu_text.setPosition(sf::Vector2f(200,200));

}