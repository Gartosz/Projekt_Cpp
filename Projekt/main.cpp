#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"

#define K sf::Keyboard

void Event(sf::RenderWindow& window, K::Key* Keys, bool* isMoving)
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
void startmapcol(sf::Sprite& a)
{
    //kolizja gornej sciany
    if (a.getPosition().y < 180)a.setPosition(a.getPosition().x, 180);
    //kolizja dolnej sciany
    if (a.getPosition().y > 700- 560 * 0.17)a.setPosition(a.getPosition().x, a.getPosition().y-3);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x >1000 - 460*0.17)a.setPosition(a.getPosition().x-3, a.getPosition().y);
    //kolizja z komoda
    if (a.getPosition().y < 213 && a.getPosition().y >= 180 && a.getPosition().x>=708 && a.getPosition().x <= 708+3)a.setPosition(a.getPosition().x - 3, a.getPosition().y);
    if (a.getPosition().y == 210 && a.getPosition().x > 708 && a.getPosition().x < 849)a.setPosition(a.getPosition().x, a.getPosition().y +3);
    //kolizja z lozkiem
    if (a.getPosition().y < 294 && a.getPosition().y >= 213 && a.getPosition().x >=800 && a.getPosition().x <= 803) {a.setPosition(800, a.getPosition().y); }
    if (a.getPosition().y == 294 && a.getPosition().x > 800)a.setPosition(a.getPosition().x, a.getPosition().y + 3);
    //kolizja z biorkiem i krzeslem
    if (a.getPosition().y >=474 && a.getPosition().x >= 770 && a.getPosition().x <=773)a.setPosition(770, a.getPosition().y); 
    if (a.getPosition().y == 474 && a.getPosition().x > 769)a.setPosition(a.getPosition().x, a.getPosition().y - 3);
    //kolizja z pilka
    if (a.getPosition().y >=528 && a.getPosition().x <= 74 && a.getPosition().x>=71) {a.setPosition(74, a.getPosition().y); }
    if (a.getPosition().y == 528 && a.getPosition().x < 74)a.setPosition(a.getPosition().x, a.getPosition().y - 3);
    //kolizja z szafą
    if (a.getPosition().y < 225 && a.getPosition().x <= 204 && a.getPosition().x >= 204 - 3)a.setPosition(a.getPosition().x + 3, a.getPosition().y);
    if (a.getPosition().y == 225 && a.getPosition().x < 204 && a.getPosition().x < 849)a.setPosition(a.getPosition().x, a.getPosition().y + 3);
}
int main()
{
    const int w = 1000, h = 700;
    bool isMoving[4] = { false, false, false, false };
    K::Key Keys[8] = { K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left };
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!");

    Character main_ch;
    main_ch.txt.loadFromFile("Textures/main_character.png");
    main_ch.sprite.scale(0.17, 0.17);
    main_ch.sprite.setPosition(785, 231);

    sf::Texture startmap;
    startmap.loadFromFile("Textures/floor.png");
    sf::IntRect rect(0, 0, 228, 181);
    sf::Sprite startmapbackground(startmap, rect);
    startmapbackground.scale(w/228.0, h/181.0);

    window.setFramerateLimit(60);

    sf::Clock timer;

    while (window.isOpen())
    {
        Event(window, Keys, isMoving);
        if (isMoving[0])
            main_ch.move(timer, 0, -1, 1840, 560);

        if (isMoving[1])
            main_ch.move(timer, 0, 1, 0, 560);

        if (isMoving[2])
            main_ch.move(timer, 1, 0, 590, 595);

        if (isMoving[3])
            main_ch.move(timer, -1, 0, 1215, 595);
        startmapcol(main_ch.sprite);
        window.clear();
        window.draw(startmapbackground);
        window.draw(main_ch.sprite);
        window.display();
    }

    return 0;
}