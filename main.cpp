#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
    // Window
    // window listens for the event - callbacks for events in sfml - click mouse, key touch, etc
    sf::RenderWindow window(sf::VideoMode(640,480), "my window", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    // Game Loop
    while (window.isOpen()) {
        // quite the Game

        // save clicks, presses, etc to event variable
        while(window.pollEvent(ev)) {
            switch (ev.type)
            {
            case sf::Event::Closed:
                    window.close();
                    break;

            case sf::Event::KeyPressed:
                if(ev.key.code == sf::Keyboard::Escape){
                    window.close();
                    break;
                }
            }
        }

    // Update

    // Render
    window.clear(sf::Color::Blue); // clear old frame

    // Draw new stuff here //


    window.display(); // window is done rendering
    }

    std::cout << "hello again!";
    return 0;
}