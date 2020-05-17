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
    for (std::string input : this->all_inputs) {
        this->input_map.insert(std::pair<std::string, bool>(input, false));
    }

    game_state = new MainStageState(this);
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

        // this is where it runs the corresponding game state
        game_state->update();
    }
}

void Game::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    this->window->clear(sf::Color(244,233,214,255));

    // draw in the stuff from the corresponding game state
    this->game_state->render();

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

    // then update all the inputs that the game state is using


    // get all the keyboard pollInputs - determine charcater movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->input_map["W"] = true;
    }
    else {
        this->input_map["W"] = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->input_map["A"] = true;
    }
    else {
        this->input_map["A"] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->input_map["S"] = true;
    }
    else {
        this->input_map["S"] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->input_map["D"] = true;
    }
    else {
        this->input_map["D"] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->input_map["SPACE"] = true;
    }
    else {
        this->input_map["SPACE"] = false;
    }

    // // normalize any diagonal movement so you can't go faster
    // // by going diagonally
    // if (player_x_vel != 0.0 && abs(player_x_vel) == abs(player_y_vel)) {
    //     player_x_vel = player_x_vel/abs(player_x_vel) * this->player->getSpeed()/sqrt(2);
    //     player_y_vel = player_y_vel/abs(player_y_vel) * this->player->getSpeed()/sqrt(2);
    // }

    // this->player->setDesVel(sf::Vector2f(player_x_vel, player_y_vel));

} // end of pollInputs