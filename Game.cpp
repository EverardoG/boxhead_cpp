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
    // std::cout << "HELLO!!!" << std::endl;
    this->pollInputs();
    for (int i = 0; i < 10; i++) {
        this->zombie_vec[i]->goTowards(this->player.x_pos, this->player.y_pos);
        this->zombie_vec[i]->update();
    }
    this->player.update();

    // if (this->player.render.getGlobalBounds().intersects(this->zombie.render.getGlobalBounds())){
    //     std::cout << "Got em!" << std::endl;
    // }
}

void Game::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    this->window->clear(sf::Color(244,233,214,255));

    // draw game in here
    this->window->draw(player.render);

    for (int i = 0; i < 10; i++) {
        this->window->draw(zombie_vec[i]->render);
    }

    if (this->player.is_attacking) {
        sf::RectangleShape attack_render;

        attack_render.setPosition(sf::Vector2f(this->player.x_pos + this->player.width/4,this->player.y_pos + this->player.height/2));
        attack_render.setSize(sf::Vector2f(100.f, 1.f));
        attack_render.setFillColor(sf::Color::Black);
        attack_render.rotate(this->player.angle);

        this->window->draw(attack_render);
    }

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
    silly_count += 1;

    // check if the game is supposed to close
    this->player.is_attacking = false;
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
                    case sf::Keyboard::Space:
                        this->player.is_attacking = true;
                        break;
                } // end of switch through key codes
        } // end of switch through event types
    } // end of while(pollEvent)

    float player_speed = 3.0f;

    float player_x_vel = 0.0f;
    float player_y_vel = 0.0f;

    // get all the keyboard pollInputs - determine charcater movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player_y_vel -= player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player_x_vel -= player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player_y_vel += player_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player_x_vel += player_speed;
    }

    // normalize any diagonal movement so you can't go faster
    // by going diagonally
    if (player_x_vel != 0.0 && abs(player_x_vel) == abs(player_y_vel)) {
        player_x_vel = player_x_vel/abs(player_x_vel) * player_speed/sqrt(2);
        player_y_vel = player_y_vel/abs(player_y_vel) * player_speed/sqrt(2);
    }

    // std::cout << "x vel: " << player_x_vel << std::endl;

    this->player.updateVel(player_x_vel, player_y_vel);

} // end of pollInputs


// Private Functions
void Game::initVariables()
{
    this->window = nullptr;

    // initialize zombies
    for (int i = 0; i < 10; i++) {
        this->zombie_vec.push_back(new Zombie());
    }
}
void Game::initWindow()
{
    this->videomode.height = WINDOW_HEIGHT;
    this->videomode.width = WINDOW_WIDTH;

    this->window = new sf::RenderWindow(this->videomode, "BoxHead", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}