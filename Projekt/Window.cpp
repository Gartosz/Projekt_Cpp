#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Menus.h"
#include "main.h"
#include <math.h>
#include <vector>
#include "Scenes.h"

#define K sf::Keyboard

void Event(sf::RenderWindow& window, const K::Key* Keys, bool* isMoving, bool& choose, bool& menu_open, bool& menu, bool& stats_open, bool& eq)
{
    sf::Event event;
    static bool escape_release = true;
    static bool enter_release = true;
    static bool tab_release = true;
    static bool i_release = true;
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

        if (!eq && K::isKeyPressed(K::I) && i_release)
        {
            eq = true;
            menu = true;
            i_release = false;
        }
        else if (eq && K::isKeyPressed(K::I) && i_release)
        {
            eq = false;
            i_release = false;
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


        if (!stats_open && K::isKeyPressed(K::Tab) && tab_release)
        {
            stats_open = true;
            menu = true;
            tab_release = false;
        }

        else if (stats_open && K::isKeyPressed(K::Tab) && tab_release)
        {
            stats_open = false;
            tab_release = false;
        }

        if (event.type == sf::Event::KeyReleased && event.key.code == K::Tab)
            tab_release = true;
        if (event.type == sf::Event::KeyReleased && event.key.code == K::I)
            i_release = true;

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
    if (a.getPosition().y > 516) { a.setPosition(a.getPosition().x, 516); std::cout << "to ja"; }
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
    if (a.getPosition().y > 420)a.setPosition(a.getPosition().x, 420);
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

int game(int new_start, const std::string &filename = "")
{
    const int w = 1000, h = 700;
    bool isMoving[4] = { false, false, false, false };
    bool choose = false, menu = true, normal_state = true, menu_open = false, stats_open = false, eq = false;
    K::Key Keys[8] = { K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left };
    sf::RenderWindow window(sf::VideoMode(w, h), "Nasza gra 2D");

    sf::Font font;
    font.loadFromFile("Textures/HannoverMesseSans-dewK.ttf");

    sf::RectangleShape gui(sf::Vector2f(window.getSize()));
    gui.setFillColor(sf::Color(0, 0, 0, 255));

    const character_type Player_type = { "Textures/main_character.png", 0.17, {0, 0, 460, 560}, 100, 100, 15, 50, 40 };
    const character_type Enemies_type[2] = { {"Textures/Enemies/Slime.png", 2, {2, 2, 61, 57}, 50, 50, 10},{ "Textures/Enemies/Manekin.png", 2, {13 , 6, 31, 52}, 30, 0 } };

    std::vector <std::unique_ptr<Character>> Enemies;

    int struct_types[3] = {0,1,0};

    for (int i = 0; i < sizeof(struct_types) / sizeof(*struct_types); i++)
    {
        Enemies.push_back(std::unique_ptr<Character>(new Character(Enemies_type[struct_types[i]], 5)));
    }


    (*Enemies[0]).sprite.setPosition(400, 200);
    (*Enemies[1]).sprite.setPosition(200, 500);
    (*Enemies[2]).sprite.setPosition(600, 300);

    int lvli = 0;

    Character Player(Player_type, lvli);

    if (filename == "")
        Player.sprite.setPosition(785, 231);
    else
    {
        Player << filename;
        lvli = Player.map_lvl;
    }

    sf::CircleShape option(20, 3);
    option.setPosition(100, 100);
    option.rotate(90);

    sf::Texture startmap;
    startmap.loadFromFile("Textures/levels/1lvl.png");
    sf::IntRect rect(0, 0, 228, 181);
    sf::Sprite startmapbackground(startmap, rect);
    startmapbackground.scale(w / 228.0, h / 181.0);

    sf::Texture txt2;
    txt2.loadFromFile("Textures/levels/2lvl.png");
    sf::IntRect rect2(0, 0, 174, 131);
    sf::Sprite lvl2(txt2, rect2);
    lvl2.scale(w / 174.0, h / 131.0);

    sf::Texture txt3;
    txt3.loadFromFile("Textures/levels/3lvl.png");
    sf::IntRect rect3(0, 0, 240, 131);
    sf::Sprite lvl3(txt3, rect3);
    lvl3.scale(w / 240.0, h / 131.0);

    sf::Texture txt4;
    txt4.loadFromFile("Textures/levels/4lvl.png");
    sf::IntRect rect4(0, 0, 240, 131);
    sf::Sprite lvl4(txt4, rect4);
    lvl4.scale(w / 240.0, h / 131.0);

    sf::Texture txt6;
    txt6.loadFromFile("Textures/levels/6lvl.png");
    sf::IntRect rect6(0, 0, 228, 181);
    sf::Sprite lvl6(txt6, rect6);
    lvl6.scale(w / 228.0, h / 181.0);

    sf::Texture txt7;
    txt7.loadFromFile("Textures/levels/7lvl.png");
    sf::IntRect rect7(0, 0, 228, 181);
    sf::Sprite lvl7(txt7, rect7);
    lvl7.scale(w / 228.0, h / 181.0);

    sf::Clock timer;

    window.setFramerateLimit(60);
        
    while (window.isOpen())
    {
        window.clear();
        Event(window, Keys, isMoving, choose, menu_open, menu, stats_open, eq);
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
            if (new_start && Player.sprite.getPosition().x >= 250)
            {
                normal_state = false;
                window.draw(Player.sprite);
                bunker(window, font, new_start);
            }
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

        Player.map_lvl = lvli;

        if (menu_open)
        {
            escape_menu(window, gui, menu_open, isMoving, choose, option, font, menu, Player);
            normal_state = false;
        }

        else if (stats_open)
        {
            stats_menu(window, Player, gui, isMoving, choose, option, menu, font);
            normal_state = false;
        }
        else if (eq)
        {
            ekwipunek(window, Player, gui, isMoving, choose, option, menu, font);
            normal_state = false;
        }

        else
        {
            for (int i = 0; i < Enemies.size(); i++)
            {
                if ((*Enemies[i]).map_lvl == lvli && enemy_player_contact(Player.sprite, (*Enemies[i]).sprite))
                {
                    fight_menu(window, Player, (*Enemies[i]), gui, isMoving, choose, option, menu, font);
                    normal_state = false;
                }
            }
        }

            
        if (Player.Health == 0 and !menu_open)
        {
            window.draw(gui);
            sf::Text death(L"ŚMIERĆ!", font, 100);
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
                else if ((*Enemies[i]).map_lvl == lvli)
                    window.draw((*Enemies[i]).sprite);
            }
            menu = true;
            Player.player_move(isMoving, timer);
            window.draw(Player.sprite);
        }

        if (new_start && new_start < 3)
            new_game(window, font, new_start);

        normal_state = true;
        window.display();
    }
    return 0;
}
