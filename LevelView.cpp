#include "LevelView.h"

// Constructors and Destructors
LevelView::LevelView(sf::RenderWindow* _window) : GameView(_window)
{
    this->initVariables();
}

LevelView::~LevelView()
{
}

// Private Functions

void LevelView::initVariables()
{
    // this->window = nullptr;

    //initialize walls
    wall_vec = std::vector<Wall*>();
    wall_vec.push_back(new Wall(sf::Vector2f(200.f,200.f), sf::Vector2f(400.f, 50.f)));

    // initialize zombies
    zombie_vec = std::vector<Zombie*>();
    for (int i = 0; i < NUM_ZOMBIES; i++) {
        this->spawnZombie(i);
    }

    // reset the player
    player_vec.emplace_back(new Player(sf::Vector2f(PLAYER_SPAWN_X,PLAYER_SPAWN_Y)));
}

void LevelView::spawnZombie(int zid)
{
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

float LevelView::getDistBtnChars(Character* char1, Character* char2)
{
    sf::Vector2f diffpos = char1->getPos() - char2->getPos();
    float distance = sqrt( pow( diffpos.x, 2 ) + pow( diffpos.y, 2 ) );
    return distance;
}

bool LevelView::zombieBulletCollision(Zombie* zombie, Bullet* bullet)
{
    // convert zombie to a rect object for the collision engine
    Rect* zombie_rect = new Rect( new Point(zombie->getPos()) , new Point(zombie->getSize()) );
    Line* bullet_line = new Line( new Point(bullet->start_pos), new Point(bullet->cur_pos) );

    return collisionEngine->isLineRectCollision(bullet_line, zombie_rect);
}

std::vector<InGameObject*> LevelView::getAllBlockingObj()
{
    // return a vector of all zombies, and walls
    std::vector<InGameObject*> all_blocking_objs;

    for (Zombie* zombie : this->zombie_vec) {
        all_blocking_objs.push_back(zombie);
    }
    for (Wall* wall : this->wall_vec) {
        all_blocking_objs.push_back(wall);
    }

    return all_blocking_objs;
    // for (Player* player : this->player_vec) {
    //     all_blocking_objs.push_back(player);
    // }
}

// Public Functions

void LevelView::update()
{
    // check if player is attacking
    this->player_vec[0]->is_attacking = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clock.getElapsedTime().asMilliseconds() - last_weapon_time > weapon_loop_time) {
        this->player_vec[0]->is_attacking = true;
        last_weapon_time = clock.getElapsedTime().asMilliseconds();
    }

    // determine player movement
    float player_x_vel = 0.0f;
    float player_y_vel = 0.0f;

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
        player_y_vel -= this->player_vec[0]->getSpeed();
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
        player_x_vel -= this->player_vec[0]->getSpeed();
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        player_y_vel += this->player_vec[0]->getSpeed();
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
        player_x_vel += this->player_vec[0]->getSpeed();
    }

    // normalize any diagonal movement so you can't go faster
    // by going diagonally
    if (player_x_vel != 0.0 && abs(player_x_vel) == abs(player_y_vel)) {
        player_x_vel = player_x_vel/abs(player_x_vel) * this->player_vec[0]->getSpeed()/sqrt(2);
        player_y_vel = player_y_vel/abs(player_y_vel) * this->player_vec[0]->getSpeed()/sqrt(2);
    }

    this->player_vec[0]->setDesVel(sf::Vector2f(player_x_vel, player_y_vel));

    // organize zombie vector so that zombies closest to player
    // are checked first, moved first, etc
    std::sort( zombie_vec.begin(), zombie_vec.end(), [](Zombie* z1, Zombie* z2) {
        return z1->dist_from_player < z2->dist_from_player;
    } );

    // this->pollInputs();
    if (this->player_vec[0]->is_attacking) {
        sf::Vector2f bullet_start = sf::Vector2f(this->player_vec[0]->getPos().x + this->player_vec[0]->getSize().x/4, this->player_vec[0]->getPos().y + this->player_vec[0]->getSize().y/2);
        bullet_vec.push_back(new Bullet(bullet_start, this->player_vec[0]->angle));
    }

    // iterate through bullets and check if any zombies were hit, delete them if so
    std::vector<Bullet*>::iterator bullet_iter = bullet_vec.begin();
    std::vector<Zombie*>::iterator zombie_iter;

    // go through all bullets
    while (bullet_iter != bullet_vec.end()) {

        // go through all zombies
        zombie_iter = zombie_vec.begin();
        while ( zombie_iter != zombie_vec.end() ) {
            // if the zombie and bullet intersect, destroy the bullet and update the zombie's hp
            // if ( (*zombie_iter)->getRender().getGlobalBounds().intersects( (*bullet_iter)->getRender().getGlobalBounds() ) ) {
            if (this->zombieBulletCollision(*zombie_iter, *bullet_iter)) {
                bullet_iter = bullet_vec.erase(bullet_iter);

                (*zombie_iter)->hp -= 10;
                (*zombie_iter)->is_hit = true;
                (*zombie_iter)->time_since_last_hit = clock.getElapsedTime().asMilliseconds();

                if ( (*zombie_iter)->hp <= 0 ) {
                    zombie_iter = zombie_vec.erase(zombie_iter);
                }
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

    // go through all zombies
    for (Zombie* zombie : zombie_vec) {
        // try to move the zombie towards the player
        zombie->goTowards(this->player_vec[0]->getPos().x, this->player_vec[0]->getPos().y);

        bool x_collision = false;
        bool y_collision = false;
        bool xy_collision = false;

        // check if the zombie wants to move
        if (zombie->des_vel.x != 0 || zombie->des_vel.y != 0) {

            x_collision = false;
            y_collision = false;
            xy_collision = false;

            // collision check this copy with other zombies and walls, negate any x/y part of movement that would cause a collision
            std::vector<InGameObject*> all_blocking_obj = this->getAllBlockingObj();
            for (InGameObject* blocking_obj : all_blocking_obj) {
                // check that blocking_obj not itself
                if (zombie != blocking_obj) {
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
                    if (shape_copy.intersects(blocking_obj->getRender().getGlobalBounds()) )  {
                        // determine if the collision is x, y, and/or xy

                        // reset the shape size as we check each direction
                        shape_copy.width = zombie_shape.width;
                        shape_copy.height = zombie_shape.height;
                        shape_copy.left = zombie_shape.left;
                        shape_copy.top = zombie_shape.top;

                        // check x
                        if (zombie->des_vel.x != 0) {
                            shape_copy.left += zombie->des_vel.x;
                            if (shape_copy.intersects(blocking_obj->getRender().getGlobalBounds())) {
                                x_collision = true;
                            }
                            shape_copy.left -= zombie->des_vel.x;
                        }

                        // check y
                        if (zombie->des_vel.y != 0) {
                            shape_copy.top += zombie->des_vel.y;
                            if (shape_copy.intersects(blocking_obj->getRender().getGlobalBounds())) {
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
                            if (shape_copy.intersects( blocking_obj->getRender().getGlobalBounds() )) {
                                xy_collision = true;
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

        if (zombie->is_hit) {
            zombie->setActVel(sf::Vector2f(0.f, 0.f));

            if (clock.getElapsedTime().asMilliseconds() - zombie->time_since_last_hit > zombie->hit_loop) {
                zombie->is_hit = false;
            }
        }

        zombie->update();
        zombie->dist_from_player = this->getDistBtnChars(this->player_vec[0], zombie);
    }

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

    this->player_vec[0]->setActVel(sf::Vector2f(this->player_vec[0]->des_vel.x, this->player_vec[0]->des_vel.y));
    this->player_vec[0]->update();

    if (this->zombie_vec.size() == 0) {
        for (int i; i < NUM_ZOMBIES; i++) {
            this->spawnZombie(i);
        }
    }

    // check if the player was touched by a zombie
    for (Zombie* zombie : this->zombie_vec) {
        if (zombie->getRender().getGlobalBounds().intersects( this->player_vec[0]->getRender().getGlobalBounds() )){
            this->next_view = "Main Menu";
            break;
        }
    }
}

void LevelView::render()
{
    // auto start = std::chrono::high_resolution_clock::now();
    this->window->clear(sf::Color(244,233,214,255));

    // draw game in here
    this->window->draw(this->player_vec[0]->getRender());

    for (int i = 0; i < zombie_vec.size(); i++) {
        this->window->draw(zombie_vec[i]->getRender());
    }

    for (int i = 0; i < bullet_vec.size(); i++) {
        this->window->draw(bullet_vec[i]->getRender());
    }

    for (int i = 0; i < wall_vec.size(); i++) {
        this->window->draw(wall_vec[i]->getRender());
    }

    // this->window->display();
}