#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"

#define K sf::Keyboard

void Event(sf::RenderWindow &window, K::Key *Keys, bool *isMoving)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed || K::isKeyPressed(K::Escape))
            window.close();

        for (int i = 0; i < 4; i++)
        {
            if (K::isKeyPressed(Keys[2 * i]) || K::isKeyPressed(Keys[2 * i + 1]))
                isMoving[i] = true;
            else
                isMoving[i] = false;
        }

    }
}


int main()
{
    bool isMoving[4] = { false, false, false, false };
    K::Key Keys[8] = {K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left};
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML works!");
    Character main_ch;
    sf::Texture background;
    main_ch.txt.loadFromFile("Textures/main_character.png");
    background.loadFromFile("Textures/bg.jpg");
    sf::RectangleShape shape_bg(sf::Vector2f(1000,700));
    shape_bg.setTexture(&background);
    main_ch.sprite.scale(0.15, 0.15);
    window.setFramerateLimit(60);

    sf::Clock timer;

    while (window.isOpen())
    {
        Event(window, Keys, isMoving);
        if (isMoving[0])
            main_ch.move( timer, 0, -1, 1840, 560);

        if (isMoving[1])
            main_ch.move( timer, 0, 1, 0, 560);

        if (isMoving[2])
            main_ch.move( timer, 1, 0, 590, 595);
            
        if (isMoving[3])
            main_ch.move( timer, -1, 0,  1215, 595);

        window.draw(shape_bg);
        window.draw(main_ch.sprite);
        window.display();
    }

    return 0;
}