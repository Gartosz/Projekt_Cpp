#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Character.h"
#include "Menus.h"
#include "main.h"
#include <math.h>
#include <vector>


#define K sf::Keyboard

void Event(sf::RenderWindow& window, K::Key* Keys, bool* isMoving, bool& choose, bool& menu_open, bool& menu)
{
    sf::Event event;
    static bool escape_release = true;
    static bool enter_release = true;
    while (window.pollEvent(event))
    {

        if (!menu_open && K::isKeyPressed(K::Escape) && escape_release)
        {
            menu_open = true;
            menu = true;
            escape_release = false;
        }
            
        else if (menu_open && K::isKeyPressed(K::Escape) && escape_release)
        {
            menu_open = false;
            escape_release = false;
        }
            
        if (event.type == sf::Event::KeyReleased && event.key.code == K::Escape)
            escape_release = true;

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (enter_release && K::isKeyPressed(K::Enter))
        {
            choose = true;
            enter_release = false;
            break;
        }
            
        else
            choose = false;
            

        if (event.type == sf::Event::KeyReleased && event.key.code == K::Enter)
            enter_release = true;

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
    if (a.getPosition().y > 700 - 560 * 0.17)a.setPosition(a.getPosition().x, a.getPosition().y - 3);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 1000 - 460 * 0.17)a.setPosition(a.getPosition().x - 3, a.getPosition().y);
    //kolizja z komoda
    if (a.getPosition().y < 213 && a.getPosition().y >= 180 && a.getPosition().x >= 708 && a.getPosition().x <= 708 + 3)a.setPosition(a.getPosition().x - 3, a.getPosition().y);
    if (a.getPosition().y == 210 && a.getPosition().x > 708 && a.getPosition().x < 849)a.setPosition(a.getPosition().x, a.getPosition().y + 3);
    //kolizja z lozkiem
    if (a.getPosition().y < 294 && a.getPosition().y >= 213 && a.getPosition().x >= 800 && a.getPosition().x <= 803) { a.setPosition(800, a.getPosition().y); }
    if (a.getPosition().y == 294 && a.getPosition().x > 800)a.setPosition(a.getPosition().x, a.getPosition().y + 3);
    //kolizja z biorkiem i krzeslem
    if (a.getPosition().y >= 474 && a.getPosition().x >= 770 && a.getPosition().x <= 773)a.setPosition(770, a.getPosition().y);
    if (a.getPosition().y == 474 && a.getPosition().x > 769)a.setPosition(a.getPosition().x, a.getPosition().y - 3);
    //kolizja z pilka
    if (a.getPosition().y >= 528 && a.getPosition().x <= 74 && a.getPosition().x >= 71) { a.setPosition(74, a.getPosition().y); }
    if (a.getPosition().y == 528 && a.getPosition().x < 74)a.setPosition(a.getPosition().x, a.getPosition().y - 3);
    //kolizja z szaf�
    if (a.getPosition().y < 225 && a.getPosition().x <= 204 && a.getPosition().x >= 204 - 3)a.setPosition(a.getPosition().x + 3, a.getPosition().y);
    if (a.getPosition().y == 225 && a.getPosition().x < 204 && a.getPosition().x < 849)a.setPosition(a.getPosition().x, a.getPosition().y + 3);
    
}
void lvl2col(sf::Sprite& a)
{
    //kolizja gornej sciany
    if (a.getPosition().y < 267)a.setPosition(a.getPosition().x, 267); 
    //kolizja dolnej sciany
    if (a.getPosition().y > 516) { a.setPosition(a.getPosition().x, 516); std::cout << "to ja";}
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 935)a.setPosition(935, a.getPosition().y);
}
void lvl3col(sf::Sprite& a)
{
    //kolizja gornej sciany
    if (a.getPosition().y < 309)a.setPosition(a.getPosition().x, 309);
    //kolizja dolnej sciany
    if (a.getPosition().y > 420)a.setPosition(a.getPosition().x,420);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 940)a.setPosition(940, a.getPosition().y);
}
void lvl4col(sf::Sprite& a)
{
    //kolizja gornej sciany
    if (a.getPosition().y < 309)a.setPosition(a.getPosition().x, 309);
    //kolizja dolnej sciany
    if (a.getPosition().y > 420)a.setPosition(a.getPosition().x, 420);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 940)a.setPosition(940, a.getPosition().y);
    //kolizja z drabina
}
void lvl6col(sf::Sprite& a)
{
    //kolizja gornej sciany
    if (a.getPosition().y < 0)a.setPosition(a.getPosition().x, 0);
    //kolizja dolnej sciany
    if (a.getPosition().y > 603)a.setPosition(a.getPosition().x, 603);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 920)a.setPosition(920, a.getPosition().y);
}
void lvl7col(sf::Sprite& a)
{
    //kolizja gornej sciany
    if (a.getPosition().y < 0)a.setPosition(a.getPosition().x, 0);
    //kolizja dolnej sciany
    if (a.getPosition().y > 603)a.setPosition(a.getPosition().x, 603);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 920)a.setPosition(920, a.getPosition().y);
}
int new_game(sf::RenderWindow& window, sf::Sprite const& startmapbackground, sf::Sprite const& main_ch, sf::Font const& font)
{
    sf::RectangleShape fade(sf::Vector2f(window.getSize()));
    fade.setFillColor(sf::Color(0, 0, 0, 255));

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("siren.wav"))
        return -1;

    sf::Text new_game("Byl zwykly niedzielny poranek. \nSpisz w najlepsze, gdy nagle...",font,40);
    new_game.setPosition(150, 200);

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

bool enemy_player_contact(sf::Sprite& player, sf::Sprite& enemy)
{
    sf::FloatRect a = player.getGlobalBounds();
    sf::FloatRect b = enemy.getGlobalBounds();

    if (player.getPosition().x + a.width > enemy.getPosition().x)
        if (player.getPosition().x < enemy.getPosition().x + b.width)
            if (player.getPosition().y + a.height > enemy.getPosition().y)
                if (player.getPosition().y < enemy.getPosition().y + b.height)
                    return true;

    return false;
}

int game(int new_start)
{
    const int w = 1000, h = 700;
    bool isMoving[4] = { false, false, false, false };
    bool choose = false, menu = true, normal_state = true, menu_open = false;
    K::Key Keys[8] = { K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left };
    sf::RenderWindow window(sf::VideoMode(w, h), "Nasza gra 2D");

    sf::Font font;
    font.loadFromFile("Textures/BitPap.ttf");

    sf::RectangleShape gui(sf::Vector2f(window.getSize()));
    gui.setFillColor(sf::Color(0, 0, 0, 255));

    const character_type Player_type = { "Textures/main_character.png", 0.17, {0, 0, 460, 560}, 100, 15 };
    const character_type Enemies_type[2] = { {"Textures/Enemies/Slime.png", 2, {2, 2, 61, 57}, 50, 10},{ "Textures/Enemies/Manekin.png", 2, {13 , 6, 31, 52}, 30, 0 } };

    std::vector <std::unique_ptr<Character>> Enemies;

    int struct_types[3] = { 0,1,0 };

    for (int i = 0; i < sizeof(struct_types) / sizeof(*struct_types); i++)
    {
        Enemies.push_back(std::unique_ptr<Character>(new Character(Enemies_type[struct_types[i]])));
    }

    
    (*Enemies[0]).sprite.setPosition(400, 200);
    (*Enemies[1]).sprite.setPosition(200, 500);
    (*Enemies[2]).sprite.setPosition(600, 300);

    Character Player(Player_type);
    Player.sprite.setPosition(785, 231);

    sf::CircleShape fight_option(20, 3);
    fight_option.setPosition(100, 100);
    fight_option.rotate(90);

    sf::Texture startmap;
    startmap.loadFromFile("Textures/1lvl.png");
    sf::IntRect rect(0, 0, 228, 181);
    sf::Sprite startmapbackground(startmap, rect);
    startmapbackground.scale(w / 228.0, h / 181.0);

    sf::Texture txt2;
    txt2.loadFromFile("Textures/2lvl.png");
    sf::IntRect rect2(0, 0, 174, 131);
    sf::Sprite lvl2(txt2, rect2);
    lvl2.scale(w / 174.0, h / 131.0);

    sf::Texture txt3;
    txt3.loadFromFile("Textures/3lvl.png");
    sf::IntRect rect3(0, 0, 240, 131);
    sf::Sprite lvl3(txt3, rect3);
    lvl3.scale(w / 240.0, h / 131.0);

    sf::Texture txt4;
    txt4.loadFromFile("Textures/4lvl.png");
    sf::IntRect rect4(0, 0, 240, 131);
    sf::Sprite lvl4(txt4, rect4);
    lvl4.scale(w / 240.0, h / 131.0);

    sf::Texture txt6;
    txt6.loadFromFile("Textures/6lvl.png");
    sf::IntRect rect6(0, 0, 228, 181);
    sf::Sprite lvl6(txt6, rect6);
    lvl6.scale(w / 228.0, h / 181.0);

    sf::Texture txt7;
    txt7.loadFromFile("Textures/7lvl.png");
    sf::IntRect rect7(0, 0, 228, 181);
    sf::Sprite lvl7(txt7, rect7);
    lvl7.scale(w / 228.0, h / 181.0);

    sf::Clock timer;

    window.setFramerateLimit(60);

    window.display();

    if (new_start)
        new_game(window, startmapbackground, Player.sprite, font);

    int lvli = 0;
    while (window.isOpen())
    {

        Event(window, Keys, isMoving, choose, menu_open, menu);
        window.clear();
        switch (lvli)
        {
        case 0:
            window.draw(startmapbackground);
            if (Player.sprite.getPosition().x > 344 && Player.sprite.getPosition().x < 419 && Player.sprite.getPosition().y >178 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(0, 402);
            }
            startmapcol(Player.sprite);
            break;

        case 1:
            window.draw(lvl2);
            if (Player.sprite.getPosition().x > 842 && Player.sprite.getPosition().y > 327 && Player.sprite.getPosition().y < 432 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(0, 402);
            }
            lvl2col(Player.sprite);
            break;
        case 2:
            window.draw(lvl3);
            if (Player.sprite.getPosition().x > 936 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(0, 402);
            }
            lvl3col(Player.sprite);
            break;
        case 3:
            window.draw(lvl4);
            if (Player.sprite.getPosition().x > 861 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(0, 402);
            }
            lvl4col(Player.sprite);
            break;
        case 4:
            window.draw(lvl6);
            if (Player.sprite.getPosition().x > 539 && Player.sprite.getPosition().x < 677 && Player.sprite.getPosition().y < 5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(459, 591);
            }
            lvl6col(Player.sprite);
            break;
        case 5:
            window.draw(lvl7);
            if (Player.sprite.getPosition().y > 601 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli--;
                Player.sprite.setPosition(600, 3);
            }
            lvl7col(Player.sprite);
            break;
        }


        if (menu_open)
        {
            escape_menu(window, gui, menu_open, isMoving, choose, fight_option, font, menu);
            normal_state = false;
        }
            

        else
        {
            for (int i = 0; i < Enemies.size(); i++)
            {
                if (enemy_player_contact(Player.sprite, (*Enemies[i]).sprite))
                {
                    fight_menu(window, Player, (*Enemies[i]), gui, isMoving, choose, fight_option, menu, font);
                    normal_state = false;
                }
            }
        }

        
        if (Player.Health == 0 and !menu_open)
        {
            window.draw(gui);
            sf::Text death("SMIERC!", font, 100);
            death.setFillColor(sf::Color::Red);
            death.setPosition(w / 2 - death.getGlobalBounds().width / 2, h / 2 - death.getGlobalBounds().height / 2);
            window.draw(death);
        }

        else if (normal_state)
        {
            for (int i = 0; i < Enemies.size(); i++)
            {
                if ((*Enemies[i]).Health == 0)
                {
                    Enemies.erase(Enemies.begin() + i);
                    i--;
                }
                else
                    window.draw((*Enemies[i]).sprite);
            }
            menu = true;
            Player.player_move(isMoving, timer);
            window.draw(Player.sprite);
        }
        window.display();
        normal_state = true;
        

    }
    return 0;
}
    