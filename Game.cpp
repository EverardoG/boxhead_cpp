#include "Game.h"

// Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

// Public Functions
void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear(sf::Color(255,0,0,255));

    // draw game in here

    this->window->display();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev)){
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape){
                    this->window->close();
                break;
                }
        }
    }
}

// Private Functions
void Game::initVariables()
{
    this->window = nullptr;
}
void Game::initWindow()
{
    this->videomode.height = 600;
    this->videomode.width = 800;

    this->window = new sf::RenderWindow(this->videomode, "BoxHead", sf::Style::Titlebar | sf::Style::Close);
}