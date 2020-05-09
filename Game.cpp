#include "Game.h"
#include <chrono>
#include <math.h>


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
    // std::cout << "HELLO!!!" << std::endl;
    this->pollInputs();

    // int64_t time_interval_wasd = 500;
    // std::chrono::_V2::high_resolution_clock::time_point now_time = std::chrono::high_resolution_clock::now();
    // int64_t time_since_wasd = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - this->timelastwasd).count();

    // std::cout << time_since_wasd << std::endl;
    // if (time_since_wasd > time_interval_wasd) {
    //     this->player.updateVel(0.0f, 0.0f);
    // }

    this->player.update();
}

void Game::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    this->window->clear(sf::Color::White);

    // draw game in here
    this->window->draw(player.render);

    this->window->display();

    // // timing
    // auto timestamp = std::chrono::high_resolution_clock::now();
    // auto timestamp_ms = std::chrono::duration_cast<std::chrono::microseconds>(timestamp);

    // std::cout << "Position: " << this->player.x_pos << "  Velocity: " << this->player.x_vel << std::endl;
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    // std::cout << "took an estimated: " << duration.count() << " microseconds!" << std::endl;

}

void Game::pollInputs()
{

    // factor out the update into updating the velocity and updating the Position
    // have the poll events update the velocity but not the Position
    // because hte position should continue to update... maybe...

    // this->timelastpolled = std::chrono::high_resolution_clock::now();

    // int64_t time_interval_wasd = 100;
    // std::chrono::_V2::high_resolution_clock::time_point now_time = std::chrono::high_resolution_clock::now();
    // int64_t time_since_wasd = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - this->timelastwasd).count();

    // std::cout << time_since_wasd << std::endl;

    silly_count += 1;

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


    // check first that only one out of the 4 wasd keys is being pressed
    // if multiple are being pressed, check which one was pressed most recently
    // attach a timestamp to each key?
    // check if the player is supposed to move
    // if w is being KeyPressed
        // move right
    // ditto for other keys

    // int64_t time_interval_wasd = 500;
    // std::chrono::_V2::high_resolution_clock::time_point now_time = std::chrono::high_resolution_clock::now();
    // int64_t time_since_wasd = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - this->timelastwasd).count();

    // std::cout << time_since_wasd << std::endl;
    // if (time_since_wasd > time_interval_wasd) {
    //     this->player.updateVel(0.0f, 0.0f);
    // }

    float player_speed = 3.0f;

    float player_x_vel = 0.0f;
    float player_y_vel = 0.0f;

    // get all the keyboard pollInputs
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // this->timelast_W = std::chrono::high_resolution_clock::now();
        // this->player.updateVel(0.0f, -player_speed);
        player_y_vel -= player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        // this->player.updateVel(-player_speed, 0.0f);
        // this->timelast_A = std::chrono::high_resolution_clock::now();
        player_x_vel -= player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        // this->player.updateVel(0.0f, player_speed);
        // this->timelast_S = std::chrono::high_resolution_clock::now();
        player_y_vel += player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // this->timelast_D = std::chrono::high_resolution_clock::now();
        // this->player.updateVel(player_speed, 0.0f);
        player_x_vel += player_speed;
    }

    if (player_x_vel != 0.0 && abs(player_x_vel) == abs(player_y_vel)) {
        player_x_vel = player_x_vel/abs(player_x_vel) * player_speed/sqrt(2);
        player_y_vel = player_y_vel/abs(player_y_vel) * player_speed/sqrt(2);
    }

    std::cout << "x vel: " << player_x_vel << std::endl;

    this->player.updateVel(player_x_vel, player_y_vel);



    // determine

} // end of pollInputs


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