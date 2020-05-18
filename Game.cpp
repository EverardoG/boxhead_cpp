#include "Game.h"

// Constructors and Destructors
Game::Game()
{
    this->initWindow();
    this->initVariables();
}

Game::~Game()
{
    delete this->window;
}

// Initalizing Functions
void Game::initWindow()
{
    this->videomode.height = WINDOW_HEIGHT;
    this->videomode.width = WINDOW_WIDTH;

    this->window = new sf::RenderWindow(this->videomode, "BoxHead", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
    // start the clock
    clock.restart();
    last_update_time = sf::milliseconds(0).asMilliseconds();

    this->game_view = new MenuView(this->window);
}

// Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

// Public Functions
void Game::update()
{
    if ( this->clock.getElapsedTime().asMilliseconds() - this->last_update_time >= this->loop_time)
    {
        loop_count += 1;
        last_update_time = clock.getElapsedTime().asMilliseconds();

        // first check if we ned to switch views
        if (game_view->switchView()) {
            if (game_view->getNextView() == "Main Menu") {
                game_view = new MenuView(this->window);
            }
            else if (game_view->getNextView() == "Main Level") {
                game_view = new LevelView(this->window);
            }
        }

        // first update the input_map
        this->pollInputs();

        // this is where it runs the corresponding game view
        this->game_view->update();
    }
}

void Game::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    // this->window->clear(sf::Color(244,233,214,255));

    // draw in the stuff from the corresponding game state
    this->game_view->render();

    this->window->display();
}

void Game::pollInputs()
{
    // check if the game is supposed to close
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
                } // end of switch through key codes
        } // end of switch through event types
    } // end of while(pollEvent)
} // end of pollInputs