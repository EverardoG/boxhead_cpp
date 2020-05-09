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
    // std::cout << "HELLO!!!" << std::endl;
    this->pollEvents();

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

void Game::pollEvents()
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

    while (this->window->pollEvent(this->ev)){
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                // std::cout << "key pressed" << std::endl;
                this->last_event_was_key_released = false;
                switch(this->ev.key.code){
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;
                    case sf::Keyboard::D:
                        // move right
                        std::cout << "D pressed  " << lastD_released  << "  " << silly_count << std::endl;
                        this->player.updateVel(1.0f, 0.0f);
                        this->lastD_released = false;
                        break;
                    case sf::Keyboard::W:
                        //move up
                        this->player.updateVel(0.0f, -1.0f);
                        this->lastW_released = false;
                        break;
                    case sf::Keyboard::S:
                        //move down
                        this->player.updateVel(0.0f, 1.0f);
                        this->lastS_released = false;
                        break;
                    case sf::Keyboard::A:
                        // move left
                        this->player.updateVel(-1.0f, 0.0f);
                        this->lastA_released = false;
                        break;
                    }
            case sf::Event::KeyReleased:
                // std::cout << "key released" << std::endl;
                this->last_event_was_key_released = true;
                switch(this->ev.key.code){
                    case sf::Keyboard::D:
                        std::cout << "D released" << lastD_released << "  " << silly_count << std::endl;
                        if (lastD_released) {
                            // move right
                            this->player.updateVel(0.0f, 0.0f);
                        }
                        this->lastD_released = true;
                        break;
                    case sf::Keyboard::W:
                        //move up
                        if (lastW_released) {
                            this->player.updateVel(0.0f, 0.0f);
                        }
                        this->lastW_released = true;
                        break;
                    case sf::Keyboard::S:
                        //move down
                        if (lastS_released) {
                            this->player.updateVel(0.0f, 0.0f);
                        }
                        this->lastS_released = true;
                        break;
                    case sf::Keyboard::A:
                        // move left
                        if (lastA_released) {
                            this->player.updateVel(0.0f, 0.0f);
                        }
                        this->lastA_released = true;
                        break;

                /* Check if the last event was a KeyReleased event
                   If it was (and we know the current event is a KeyReleased event)
                        then stop moving the player */

                // std::cout << "KEY RELEASED" << std::endl;
                // if (sf::Event::KeyReleased == sf::Keyboard::D || )
                // if (time_since_wasd > time_interval_wasd) {
                //     std::cout << "KEY RELEASED" << std::endl;
                //     this->player.updateVel(0.0f, 0.0f);
                // }
                // std::cout << last_event_was_key_released << std::endl;
                // if (this->last_event_was_key_released) {
                //     // std::cout << " D o u b l e d i g i t s" << std::endl;
                //     this->player.updateVel(0.0f, 0.0f);
                // }

                // this->last_event_was_key_released = true;
                // // std::cout << "key_released - true" << std::endl;

                // break;
            // default:
            //     std::chrono::_V2::high_resolution_clock::time_point now_time = std::chrono::high_resolution_clock::now();
            //     int64_t time_since_wasd = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - this->timelastwasd).count();


            //     if (time_since_wasd > time_interval_wasd) {
            //         this->player.updateVel(0.0f, 0.0f);
            //     }
            //     break;
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