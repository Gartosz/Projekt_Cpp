#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Character.h"
#include "main.h"


#define K sf::Keyboard

int Event(sf::RenderWindow& window, K::Key* Keys, bool* isMoving)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed || K::isKeyPressed(K::Escape))
        { 
            window.close();
            return main();
        }
            

        for (int i = 0; i < 4; i++)
        {
            if (K::isKeyPressed(Keys[2 * i]) || K::isKeyPressed(Keys[2 * i + 1]))
                isMoving[i] = true;
            else
                isMoving[i] = false;
        }

    }
}

void player_move(bool *isMoving, Character &ch, sf::Clock &timer)
{
    if (isMoving[0])
        ch.move(timer, 0, -1, 1840, 560);

    if (isMoving[1])
        ch.move(timer, 0, 1, 0, 560);

    if (isMoving[2])
        ch.move(timer, 1, 0, 590, 595);

    if (isMoving[3])
        ch.move(timer, -1, 0, 1215, 595);
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

int new_game(sf::RenderWindow &window, sf::Sprite const &startmapbackground, sf::Sprite const & main_ch)
{
    sf::RectangleShape fade(sf::Vector2f(window.getSize()));
    fade.setFillColor(sf::Color(0, 0, 0, 255));

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("siren.wav"))
        return -1;

    sf::Font font;
    font.loadFromFile("Textures/BitPap.ttf");

    sf::Text new_game;
    new_game.setFont(font);
    new_game.setPosition(150, 200);
    new_game.setCharacterSize(40);
    new_game.setString("Byl zwykly niedzielny poranek. \nSpisz w najlepsze, gdy nagle...");

    sf::Clock timer;

    sf::Sound sound;
    sound.setVolume(10);
    sound.setBuffer(buffer);

    int i = 255;
    bool s = false;
    int start = 0;

    while (window.isOpen())
    {
        window.draw(startmapbackground);
        window.draw(main_ch);
        window.draw(fade);

        switch (start)
        {
        case 0:
            window.draw(new_game);

            if (timer.getElapsedTime().asSeconds() >= 4)
            {
                new_game.setString("Budzi Cie dzwiek syreny...");
                start++;
                timer.restart();
            }

            break;
        case 1:
                start++;
                sound.play();
            break;
        case 2:
            if (timer.getElapsedTime().asSeconds() >= 1)
            {
                start++;
                timer.restart();
            }
            break;
        case 3:
            window.draw(new_game);

            if (timer.getElapsedTime().asSeconds() >= 4)
            {
                start++;
                s = true;
            }
            break;
        default:
            break;
        }

        if (s && i > 0)
        {
            fade.setFillColor(sf::Color(0, 0, 0, i));
            if (timer.getElapsedTime().asMilliseconds() >= 20)
                i--;
        }

        if (i == 0)
            break;

        window.display();
    }
}

int game(int new_start)
{
    const int w = 1000, h = 700;
    bool isMoving[4] = { false, false, false, false };
    K::Key Keys[8] = { K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left };
    sf::RenderWindow window(sf::VideoMode(w, h), "Nasza gra 2D");

    Character main_ch;
    main_ch.txt.loadFromFile("Textures/main_character.png");
    main_ch.sprite.scale(0.17, 0.17);
    main_ch.sprite.setPosition(785, 231);

    sf::Texture startmap;
    startmap.loadFromFile("Textures/floor.png");
    sf::IntRect rect(0, 0, 228, 181);
    sf::Sprite startmapbackground(startmap, rect);
    startmapbackground.scale(w/228.0, h/181.0);

    sf::Clock timer;
    
    window.setFramerateLimit(60);

    window.display();

    if(new_start)
        new_game(window,startmapbackground,main_ch.sprite);


    while (window.isOpen())
    {
        Event(window, Keys, isMoving);
        player_move(isMoving, main_ch, timer);
        
        startmapcol(main_ch.sprite);
        window.clear();
        window.draw(startmapbackground);
        window.draw(main_ch.sprite);
        window.display();
    }

    return 0;
}