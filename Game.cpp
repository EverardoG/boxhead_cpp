#include "Game.h"
#include <chrono>


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
    // auto start = std::chrono::high_resolution_clock::now();
    this->window->clear(sf::Color::White);

    // draw game in here
    this->window->draw(player.render);

    this->window->display();

    std::cout << this->player.x_pos << std::endl;
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    // std::cout << "took an estimated: " << duration.count() << " microseconds!" << std::endl;

}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev)){
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                switch(this->ev.key.code){
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;
                    case sf::Keyboard::D:
                        // move right
                        this->player.update(10.0f, 0.0f);
                        break;
                    case sf::Keyboard::W:
                        //move up
                        this->player.update(0.0f, -10.0f);
                        break;
                    case sf::Keyboard::S:
                        //move down
                        this->player.update(0.0f, 10.0f);
                        break;
                    case sf::Keyboard::A:
                        // move left
                        this->player.update(-10.0f, 0.0f);
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
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}