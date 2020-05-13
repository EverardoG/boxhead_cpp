#include "Zombie.h"

Zombie::Zombie(int zid) : Character(sf::Color::Green)
{
    // instantiates the character superclass but with the color green

    // also places zombie in random position on screen
    // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // std::default_random_engine generator(seed);
    // std::uniform_int_distribution<int> distribution(0,40);

    this->id = zid;

    float xpos = 0.f;
    float ypos = 0.f;

    if (helper.generateRandomInt(0,1)) {
        // std::cout << "running if" << std::endl;
        if (helper.generateRandomInt(0,1)) {
            ypos = -20;
        }
        else{
            ypos = WINDOW_HEIGHT;
        }
        xpos = helper.generateRandomInt(-20,WINDOW_WIDTH);
    }
    else {
        // std::cout << "running else" << std::endl;
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

    // std::cout << xpos << " | " << ypos << std::endl;
    this->x_pos = xpos;
    this->y_pos = ypos;
    // std::cout << this->x_pos << " | " << this->y_pos << std::endl;
}

void Zombie::goTowards(float x_des, float y_des)
{
    //update the velocities for the zombie so that it goes towards the specified destination
    float x_diff = x_des - this->x_pos;
    float y_diff = y_des - this->y_pos;
    // std::cout << " _____________________________ " << std::endl;
    // std::cout << this->x_pos << " | " << this->y_pos << std::endl;

    // std::cout << x_diff << " | " << y_diff << std::endl;

    float x_dir = 0.0;
    if (abs(x_diff) > 1.0) {
        x_dir = (x_diff)/abs(x_diff);
    }


    float y_dir = 0.0;
    if (abs(y_diff) > 1.0) {
        y_dir = (y_diff)/abs(y_diff);
    }


    float zombie_speed_x = 0.5 * x_dir;
    float zombie_speed_y = 0.5 * y_dir;

    if (abs(y_diff) < zombie_speed_y) {
        zombie_speed_y = y_diff;
    }

    if(abs(x_diff) < zombie_speed_x) {
        zombie_speed_x = x_diff;
    }


    // std::cout << zombie_speed_x<< " | " << zombie_speed_y << std::endl;

    this->updateVel(zombie_speed_x, zombie_speed_y);
}