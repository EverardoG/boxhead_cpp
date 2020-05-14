#include "Zombie.h"

Zombie::Zombie(int zid, sf::Vector2f spawn_pos) : Character(spawn_pos, sf::Color::Green)
{
    // instantiates the character superclass but with the color green

    // also places zombie in random position on screen
    // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // std::default_random_engine generator(seed);
    // std::uniform_int_distribution<int> distribution(0,40);

    this->max_speed = ZOMBIE_SPEED;

    this->id = zid;

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

    this->pos.x = xpos;
    this->pos.y = ypos;

    this->render.setPosition(this->pos.x, this->pos.y = ypos);
}

void Zombie::goTowards(float x_des, float y_des)
{
    //update the velocities for the zombie so that it goes towards the specified destination
    float x_diff = x_des - this->pos.x;
    float y_diff = y_des - this->pos.y;

    float x_dir = 0.0;
    if (abs(x_diff) > 1.0) {
        x_dir = (x_diff)/abs(x_diff);
    }


    float y_dir = 0.0;
    if (abs(y_diff) > 1.0) {
        y_dir = (y_diff)/abs(y_diff);
    }


    float zombie_speed_x = this->speed * x_dir;
    float zombie_speed_y = this->speed * y_dir;

    if (abs(y_diff) < zombie_speed_y) {
        zombie_speed_y = y_diff;
    }

    if(abs(x_diff) < zombie_speed_x) {
        zombie_speed_x = x_diff;
    }

    this->updateVel(zombie_speed_x, zombie_speed_y);
}