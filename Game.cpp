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

    this->game_state = new MainMenuState( this->window, std::unordered_map<std::string, GameState*>( { { "MainStage", new MainStageState(this->window, std::unordered_map<std::string, GameState*>()) } }) );
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

        // first update the input_map
        this->pollInputs();

        // this is where it runs the corresponding game state
        std::string next_state = this->game_state->update(this->input_map);

        if (next_state != "") {
            this->game_state = this->game_state->adjStates[next_state];
        }
    }
}

void Game::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    // this->window->clear(sf::Color(244,233,214,255));

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
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //     this->input_map["LCLICK"] = true;
    // }
    // else {
    //     this->input_map["LCLICK"] = false;
    // }

} // end of pollInputs