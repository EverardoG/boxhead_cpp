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
void Game::spawnZombie(int zid)
{
    //TODO: Make it so that this function avoids placing zombies
    // in collision / on top of eachother upon spawn


    bool new_zombie_in_collision = true;
    sf::Vector2f spawn_pos;

    // determine where to place the zombie
    // based on a psuedo random uniform distribution
    while (new_zombie_in_collision) {
        float xpos = 0.f;
        float ypos = 0.f;

        if (helper.generateRandomInt(0,1)) {
            if (helper.generateRandomInt(0,1)) {
                ypos = -20;
            }
            else{
                ypos = WINDOW_HEIGHT;
            }
            xpos = helper.generateRandomInt(-20,WINDOW_WIDTH);
        }
        else {
            if (helper.generateRandomInt(0,1)) {
                xpos = -20;
            }
            else {
                xpos = WINDOW_WIDTH;
            }
            ypos = helper.generateRandomInt(-20, WINDOW_HEIGHT);
        }

        xpos += helper.generateRandomInt(0,20);
        ypos += helper.generateRandomInt(0,20);

        spawn_pos = sf::Vector2f(xpos, ypos);

        // check if spawning the zombie here would create a collision
        sf::FloatRect new_zombie;
        new_zombie.left = xpos;
        new_zombie.top = ypos;
        new_zombie.width = CHARACTER_SIZE.x;
        new_zombie.height = CHARACTER_SIZE.y;

        new_zombie_in_collision = false;
        for (Zombie* zombie : this->zombie_vec) {
            if (new_zombie.intersects( zombie->getRender().getGlobalBounds() ) ) {
                new_zombie_in_collision = true;
            }
        }

    }

    // create the new zombie and place it in the zombie vector
    zombie_vec.push_back(new Zombie(zid, spawn_pos));
}

void Game::update()
{
    this->pollInputs();
    if (this->player->is_attacking) {
        bullet_vec.push_back(new Bullet(this->player->getPos().x + this->player->getSize().x/4, this->player->getPos().y + this->player->getSize().y/2, this->player->angle));
        // TODO: Make it so that the bullet object when shot diagonally is a diagonal line instead of a giant rectangle (in terms of collisions with zombies)
    }

    // iterate through bullets and check if any zombies were hit, delete them if so
    std::vector<Bullet*>::iterator bullet_iter = bullet_vec.begin();
    std::vector<Zombie*>::iterator zombie_iter;

    // go through all bullets
    while (bullet_iter != bullet_vec.end()) {

        // go through all zombies
        zombie_iter = zombie_vec.begin();
        while ( zombie_iter != zombie_vec.end() ) {

            // if the zombie and bullet intersect, delete both and update the pointers
            if ( (*zombie_iter)->getRender().getGlobalBounds().intersects( (*bullet_iter)->getRender().getGlobalBounds() ) ) {
                bullet_iter = bullet_vec.erase(bullet_iter);
                zombie_iter = zombie_vec.erase(zombie_iter);
                break; // stop checking the zombies for this bullet
            }
            else {
                ++zombie_iter;
            }

        }
        if (bullet_iter != bullet_vec.end()) {
            ++bullet_iter;
        }
    }


    // iterate through all zombies
        // have the zombie set its desired Velocity
        // check if the zombie will collide with anything
        // set its actual Velocity accordingly

    // go through all zombies
    for (Zombie* zombie : zombie_vec) {
        // try to move the zombie towards the player
        zombie->goTowards(this->player->getPos().x, this->player->getPos().y);

        // make a copy of the zombie's render to move in that direction
        // sf::FloatRect zombie_shape = zombie->getRender().getGlobalBounds();
        // sf::FloatRect zombie_shape_copy;
        // zombie_shape_copy.left = zombie_shape.left + zombie->des_vel.x;
        // zombie_shape_copy.top = zombie_shape.top + zombie->des_vel.y;
        // zombie_shape_copy.width = zombie_shape.width;
        // zombie_shape_copy.height = zombie_shape.height;

        bool x_collision = false;
        bool y_collision = false;
        bool xy_collision = false;

        // check if the zombie wants to move
        if (zombie->des_vel.x != 0 || zombie->des_vel.y != 0) {

            x_collision = false;
            y_collision = false;
            xy_collision = false;

            // collision check this copy with other zombies, negate any x/y part of movement that would cause a collision
            for (Zombie* zombie2 : zombie_vec) {
                // check that zombie2 is not itself
                if (zombie != zombie2) {
                    // check if there would be a collision in x,y, or xy with zombie2

                    // make a copy of the zombie's collision shape
                    sf::FloatRect zombie_shape = zombie->getRender().getGlobalBounds();
                    sf::FloatRect shape_copy;

                    // increase it by the desired velocity so it shows any collision in x, y, or xy
                    shape_copy.width = zombie_shape.width + zombie->des_vel.x;
                    shape_copy.height = zombie_shape.height + zombie->des_vel.y;

                    // place that shape accordingly
                    if ( zombie->des_vel.x >= 0 ) {
                        shape_copy.left = zombie_shape.left;
                    }
                    else {
                        shape_copy.left = zombie_shape.left + zombie->des_vel.x;
                    }

                    if ( zombie->des_vel.y >= 0 ) {
                        shape_copy.top = zombie_shape.top;
                    }
                    else {
                        shape_copy.top = zombie_shape.top + zombie->des_vel.y;
                    }
                    // end shape placement

                    // check for a collision in all directions (x, y, xy)
                    if (shape_copy.intersects(zombie2->getRender().getGlobalBounds()) )  {
                        // determine if the collision is x, y, and/or xy

                        // reset the shape size as we check each direction
                        shape_copy.width = zombie_shape.width;
                        shape_copy.height = zombie_shape.height;
                        shape_copy.left = zombie_shape.left;
                        shape_copy.top = zombie_shape.top;

                        // check x
                        if (zombie->des_vel.x != 0) {
                            shape_copy.left += zombie->des_vel.x;
                            if (shape_copy.intersects(zombie2->getRender().getGlobalBounds())) {
                                x_collision = true;
                            }
                            shape_copy.left -= zombie->des_vel.x;
                        }

                        // check y
                        if (zombie->des_vel.y != 0) {
                            shape_copy.top += zombie->des_vel.y;
                            if (shape_copy.intersects(zombie2->getRender().getGlobalBounds())) {
                                y_collision = true;
                            }
                            shape_copy.top -= zombie->des_vel.y;
                        }

                        // check xy
                        if (zombie->des_vel.y != 0 && zombie->des_vel.x != 0) {
                            // this only checks the corner, so it's a bit different from checking x or y independently from each other
                            // make corner box
                            shape_copy.width = abs(zombie->des_vel.x);
                            shape_copy.height = abs(zombie->des_vel.y);

                            // place corner box accordingly
                            if (zombie->des_vel.x < 0) {
                                shape_copy.left = zombie->getPos().x + zombie->des_vel.x;
                            }
                            else {
                                shape_copy.left = zombie->getPos().x + zombie->getSize().x;
                            }

                            if (zombie->des_vel.y < 0) {
                                shape_copy.top = zombie->getPos().y + zombie->des_vel.y;
                            }
                            else {
                                shape_copy.top = zombie->getPos().y + zombie->getSize().y;
                            }
                            // end placemnt of corner box

                            // check corner collision
                            if (shape_copy.intersects( zombie2->getRender().getGlobalBounds() )) {
                                xy_collision = true;
                                // x_collision = true;
                                // y_collision = true;
                            }
                        }
                        // end checking x, y, xy separately
                    } // end if there's a collision detected
                } // end if zombie != zombie2
            } //end looping through other zombies
        } // end if zombie wants to move

        // update the actual Velocity of the zombie
        if (x_collision && !y_collision) {
            zombie->act_vel.x = 0.0;
            zombie->act_vel.y = zombie->des_vel.y;
        }
        else if (!x_collision && y_collision) {
            zombie->act_vel.y = 0.0;
            zombie->act_vel.x = zombie->des_vel.x;
        }
        else if ( (x_collision && y_collision) || xy_collision) {
            zombie->act_vel.y = 0.0;
            zombie->act_vel.x = 0.0;
        }
        else {
            zombie->setActVel(zombie->des_vel);
        }
        zombie->update();
    }

    // this->checkCollisions();

    // for (int i = 0; i < zombie_vec.size(); i++) {
    //     if (zombie_vec[i]->in_collision) {
    //         this->zombie_vec[i]->setActVel( sf::Vector2f(0.f, 0.f) );
    //         this->zombie_vec[i]->in_collision = false;
    //     }
    //     else {
    //         this->zombie_vec[i]->goTowards(this->player->getPos().x, this->player->getPos().y);
    //         this->zombie_vec[i]->setActVel(this->zombie_vec[i]->des_vel);
    //     }
    //     this->zombie_vec[i]->update();
    // }

    // std::vector<Bullet*>::iterator bullet_iter = bullet_vec.begin();
    bullet_iter = bullet_vec.begin();
    while (bullet_iter != bullet_vec.end()) {
        if ( (*bullet_iter)->finished ) {
            bullet_iter = bullet_vec.erase(bullet_iter);
        }
        else {
            (*bullet_iter)->update();
            ++bullet_iter;
        }
    }

    this->player->setActVel(sf::Vector2f(this->player->des_vel.x, this->player->des_vel.y));
    this->player->update();
}

void Game::checkCollisions()
{
    // loop through all the zombies and see if any is hit by a bullet
    std::vector<Zombie*>::iterator zombie_iter = zombie_vec.begin();
    std::vector<Bullet*>::iterator bullet_iter;
    while (zombie_iter != zombie_vec.end() ) {

        sf::FloatRect zombie_shape = (*zombie_iter)->getRender().getGlobalBounds();
        sf::FloatRect player_shape = this->player->getRender().getGlobalBounds();

        // check if the zombie collided with the player and reset the game if so
        if ( zombie_shape.intersects(player_shape) ) {
            this->initVariables();
            break;
        }

        // see if the zombie was hit by any bullet
        bullet_iter = bullet_vec.begin();
        while ( bullet_iter != bullet_vec.end() ) {

            // int dummy;
            // dummy = 10;

            // if the zombie was hit by a bullet
            if ( (*zombie_iter)->getRender().getGlobalBounds().intersects( (*bullet_iter)->getRender().getGlobalBounds() ) ) {
                // delete the zombie and the bullet
                // std::cout << " deleting zombie: " << (*zombie_iter)->id << std::endl;
                // if ( (*zombie_iter)->id == 9 ) {
                //     int dummy;
                //     dummy = 10;
                // }

                bullet_iter = bullet_vec.erase(bullet_iter);
                zombie_iter = zombie_vec.erase(zombie_iter);
                // std::cout << zombie_vec.size() << " zombies left!" << std::endl;

                // break the loop so we can check the next zombie
                break;
            }
            // else keep checking bullets
            else {
                // std::cout << "Next bullet!" << std::endl;
                ++bullet_iter;
            }
        } // end bullet while

        // create a copy of the zombie shape, but one frame in the future
        // (*zombie_iter)->goTowards(this->player->x_pos, this->player->y_pos);

        sf::FloatRect zombie_shape_copy;
        zombie_shape_copy.left = zombie_shape.left + (*zombie_iter)->des_vel.x;
        zombie_shape_copy.top = zombie_shape.top + (*zombie_iter)->des_vel.y;
        zombie_shape_copy.width = zombie_shape.width;
        zombie_shape_copy.height = zombie_shape.height;

        // loop through zombies (excluding itself)
        // set colliding to true if this future zombie shape would be in collision with another zombie

        std::vector<Zombie*>::iterator zombie_iter2 = zombie_vec.begin();
        while (zombie_iter2 != zombie_vec.end()) {
            // if the zombie is colliding with a zombie that isn't itself
            if (zombie_iter != zombie_iter2 && zombie_shape_copy.intersects( (*zombie_iter2)->getRender().getGlobalBounds() ) ){

                // only set colliding to true if the 1st zombie is moving in the direction of the 2nd zombie

                // check if the zombie will continue to collide on its current trajectory
                // make a copy of the zombie's render and place it where the zombie will be next
                // check if this new render will still collide with zombie 2

                (*zombie_iter)->in_collision = true;

                // if (zombie_shape_copy.intersects( (*zombie_iter2)->getRender().getGlobalBounds() ) ) {
                //     // if it does, set the zombie's collision to true so it stops moving
                //     (*zombie_iter)->colliding_with_zombie = true;
                // }
                // else {
                //     int dummy;
                //     dummy =2;
                // }
            }
            ++zombie_iter2;
        } // end of checking collisions between zombies


        // move on to the next zombie
        if (zombie_iter != zombie_vec.end()) {
            ++zombie_iter;
        }

    }// end zombie while
    // std::cout << "finished collisions" << std::endl;
}

void Game::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    this->window->clear(sf::Color(244,233,214,255));

    // draw game in here
    this->window->draw(this->player->getRender());

    for (int i = 0; i < zombie_vec.size(); i++) {
        this->window->draw(zombie_vec[i]->getRender());
    }

    for (int i = 0; i < bullet_vec.size(); i++) {
        this->window->draw(bullet_vec[i]->getRender());
    }

    // if (this->player->is_attacking) {
    //     sf::RectangleShape attack_render;

    //     attack_render.setPosition(sf::Vector2f(this->player->x_pos + this->player->width/4,this->player->y_pos + this->player->height/2));
    //     attack_render.setSize(sf::Vector2f(100.f, 1.f));
    //     attack_render.setFillColor(sf::Color::Black);
    //     attack_render.rotate(this->player->angle);

    //     this->window->draw(attack_render);
    // }

    this->window->display();

    // // timing
    // auto timestamp = std::chrono::high_resolution_clock::now();
    // auto timestamp_ms = std::chrono::duration_cast<std::chrono::microseconds>(timestamp);

    // std::cout << "Position: " << this->player->x_pos << "  Velocity: " << this->player->x_vel << std::endl;
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    // std::cout << "took an estimated: " << duration.count() << " microseconds!" << std::endl;

}

void Game::pollInputs()
{
    silly_count += 1;

    // check if the game is supposed to close
    this->player->is_attacking = false;
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
                        this->player->is_attacking = true;
                        break;
                } // end of switch through key codes
        } // end of switch through event types
    } // end of while(pollEvent)

    // float player_speed = 0.75f;

    float player_x_vel = 0.0f;
    float player_y_vel = 0.0f;

    // get all the keyboard pollInputs - determine charcater movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player_y_vel -= this->player->getSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player_x_vel -= this->player->getSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player_y_vel += this->player->getSpeed();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player_x_vel += this->player->getSpeed();
    }

    // normalize any diagonal movement so you can't go faster
    // by going diagonally
    if (player_x_vel != 0.0 && abs(player_x_vel) == abs(player_y_vel)) {
        player_x_vel = player_x_vel/abs(player_x_vel) * this->player->getSpeed()/sqrt(2);
        player_y_vel = player_y_vel/abs(player_y_vel) * this->player->getSpeed()/sqrt(2);
    }

    this->player->setDesVel(sf::Vector2f(player_x_vel, player_y_vel));

} // end of pollInputs

// Private Functions
void Game::initVariables()
{
    // this->window = nullptr;

    // initialize zombies


    zombie_vec = std::vector<Zombie*>();
    for (int i = 0; i < NUM_ZOMBIES; i++) {
        this->spawnZombie(i);
    }

    // reset the player
    player = new Player(sf::Vector2f(PLAYER_SPAWN_X,PLAYER_SPAWN_Y));
}

void Game::initWindow()
{
    this->videomode.height = WINDOW_HEIGHT;
    this->videomode.width = WINDOW_WIDTH;

    this->window = new sf::RenderWindow(this->videomode, "BoxHead", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}