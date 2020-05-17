#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* _window, std::unordered_map<std::string, GameState*> _adjStates) : GameState(_window, _adjStates)
{
    this->initVariables();
}

MainMenuState::~MainMenuState()
{
}

std::string MainMenuState::update(std::unordered_map<std::string, bool> _input_map)
{
    // sf::Vector2i mouse_pos = sf::Mouse::getPosition();
    // sf::FloatRect mouse_box;
    // mouse_box.left = sf::Mouse::getPosition().x;
    // mouse_box.top = sf::Mouse::getPosition().y;
    // mouse_box.width = 1;
    // mouse_box.height = 1;
    if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ){
        std::cout << "checking mouse bounds" << std::endl;
        if ( menu_text.getGlobalBounds().contains( sf::Vector2f(sf::Mouse::getPosition( (*this->window) )) ) ) {
            std::cout << "Onwards!" << std::endl;
            return "MainStage";
        }
    }
    return "";
}

void MainMenuState::render()
{
    this->window->clear(sf::Color::White);
    this->window->draw(this->menu_text);

}

void MainMenuState::initVariables()
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