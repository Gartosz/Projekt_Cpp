﻿#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Character.h"
#include "main.h"
#include <math.h>
#include <vector>

#define K sf::Keyboard

int Event(sf::RenderWindow& window, K::Key* Keys, bool* isMoving, bool &choose)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed || K::isKeyPressed(K::Escape))
        { 
            window.close();
            return main();
        }
            

        if (K::isKeyPressed(K::Enter))
            choose = true;

        else
            choose = false;

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

int new_game(sf::RenderWindow &window, sf::Sprite const &startmapbackground, sf::Sprite const & main_ch, sf::Font const &font)
{
    sf::RectangleShape fade(sf::Vector2f(window.getSize()));
    fade.setFillColor(sf::Color(0, 0, 0, 255));

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("siren.wav"))
        return -1;

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

bool enemy_player_contact(sf::Sprite &player, sf::Sprite &enemy)
{
    sf::FloatRect a = player.getGlobalBounds();
    sf::FloatRect b = enemy.getGlobalBounds();
    
    if (player.getPosition().x + a.width > enemy.getPosition().x)
        if (player.getPosition().x < enemy.getPosition().x + b.width)
            if (player.getPosition().y +a.height > enemy.getPosition().y)
                if (player.getPosition().y < enemy.getPosition().y + b.height)
                    return true;

    return false;
}

void fight(sf::RenderWindow &window, Character &player, Character& enemy, sf::RectangleShape &gui, bool *move_menu, bool &choose, sf::CircleShape &option, bool & menu, sf::Font const & font)
{
    float wait_time=0.2;
    static sf::Clock t;
    static int i = 0;
    sf::Vector2f const options_positions[4] = { {100,500}, {100,600}, {400,500}, {400,600} };
    sf::Text player_hp;
    sf::Text enemy_hp;
    sf::Text menu_text[4];
    std::string menu_string[4] = {"Atak", "Ekwipunek", "Pomin ture", "Ucieknij"};

    player_hp.setFont(font);
    player_hp.setPosition(0, 0);
    player_hp.setCharacterSize(40);
    player_hp.setString(std::to_string(player.Health).substr(0,int(log10(abs(player.Health))) + 4) + " HP");
    
    enemy_hp.setFont(font);
    enemy_hp.setPosition(800, 0);
    enemy_hp.setCharacterSize(40);
    enemy_hp.setString(std::to_string(enemy.Health).substr(0, int(log10(abs(enemy.Health))) + 4) + " HP");

    if (menu)
    {
        i = 0;
        menu = false;
        sf::IntRect rect = player.sprite.getTextureRect();
        rect.top = 0;
        rect.left = 460;
        rect.height = 560;
        player.sprite.setTextureRect(rect);
        t.restart();
    }
       
    sf::Vector2f pos[4] = {player.sprite.getPosition(),enemy.sprite.getPosition()};
    player.sprite.setPosition(300, 250);
    enemy.sprite.setPosition(600, 100);

    if (move_menu[2] && t.getElapsedTime().asSeconds() >= wait_time)
    { 
        i++;
        t.restart();
    }
        
    else if (move_menu[3] && t.getElapsedTime().asSeconds() >= wait_time)
    {
        i--;
        t.restart();
    }

    if (i > 3)
        i = 0;
    else if (i < 0)
        i = 3;

    option.setPosition(options_positions[i]);

    window.draw(gui);
    window.draw(player.sprite);
    window.draw(enemy.sprite);
    window.draw(option);
    window.draw(player_hp);
    window.draw(enemy_hp);
    for (int j = 0; j < 4; j++)
    {
        menu_text[j].setFont(font);
        menu_text[j].setPosition(options_positions[j].x + 20, options_positions[j].y);
        menu_text[j].setCharacterSize(40);
        menu_text[j].setString(menu_string[j]);
        window.draw(menu_text[j]);
    }

    player.sprite.setPosition(pos[0]);
    enemy.sprite.setPosition(pos[1]);

    if (i == 0 && choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        enemy.Health -= player.Attack;
        t.restart();
        if (enemy.Health <= 0)
        {
            enemy.sprite.setPosition(-100, -100);
            enemy.Health = 0;
        }

        player.Health -= enemy.Attack;

    }

    else if (i == 2 && choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        player.Health -= enemy.Attack;
        t.restart();
    }

    else if (i == 3 && choose)
    {
        int x = 0, y = 0;
        if (player.sprite.getPosition().x > enemy.sprite.getPosition().x)
            x += 30;
        else
            x -= 30;

        if (player.sprite.getPosition().y > enemy.sprite.getPosition().y)
            y += 30;
        else
            y -= 30;

        player.sprite.setPosition(player.sprite.getPosition().x + x, player.sprite.getPosition().y + y);
    } 
}

int game(int new_start)
{
    const int w = 1000, h = 700;
    bool isMoving[4] = { false, false, false, false };
    bool choose = false, fight_menu = true, normal_state = true;
    K::Key Keys[8] = { K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left };
    sf::RenderWindow window(sf::VideoMode(w, h), "Nasza gra 2D");

    sf::Font font;
    font.loadFromFile("Textures/BitPap.ttf");

    sf::RectangleShape fight_gui(sf::Vector2f(window.getSize()));
    fight_gui.setFillColor(sf::Color(0, 0, 0, 255));

    const character_type Player_type = { "Textures/main_character.png", 0.17, {0, 0, 460, 560}, 100, 15 };
    const character_type Enemies_type[2] = { {"Textures/Enemies/Slime.png", 2, {2, 2, 61, 57}, 50, 10},{ "Textures/Enemies/Manekin.png", 2, {13 , 6, 31, 52}, 30, 0 } };

    std::vector <std::unique_ptr<Character>> Enemies;

    int struct_types[3] = {0,1,0};

    for(int i =0;i<sizeof(struct_types)/sizeof(*struct_types);i++)
    { 
        Enemies.push_back(std::unique_ptr<Character>(new Character(Enemies_type[struct_types[i]])));
    }

    Character Player(Player_type);
    Player.sprite.setPosition(785, 231);

    (*Enemies[0]).sprite.setPosition(400,200);
    (*Enemies[1]).sprite.setPosition(200, 500);
    (*Enemies[2]).sprite.setPosition(600, 300);

    sf::CircleShape fight_option(20, 3);
    fight_option.setPosition(100, 100);
        fight_option.rotate(90);

    sf::Texture startmap;
    startmap.loadFromFile("Textures/floor.png");
    sf::IntRect rect(0, 0, 228, 181);
    sf::Sprite startmapbackground(startmap, rect);
    startmapbackground.scale(w/228.0, h/181.0);

    sf::Clock timer;
    
    window.setFramerateLimit(60);

    window.display();

    if(new_start)
        new_game(window,startmapbackground, Player.sprite, font);


    while (window.isOpen())
    {
        Event(window, Keys, isMoving, choose);
        window.clear();
        window.draw(startmapbackground);
        for (int i = 0; i < Enemies.size(); i++)
        {
            if (enemy_player_contact(Player.sprite, (*Enemies[i]).sprite))
            {
                fight(window,Player, (*Enemies[i]), fight_gui, isMoving, choose, fight_option, fight_menu, font);
                normal_state = false;
            }

        }

        if(normal_state)
        {
            for (int i = 0; i < Enemies.size(); i++)
            {
                if ((*Enemies[i]).Health == 0)
                    Enemies.erase(Enemies.begin()+i);
                window.draw((*Enemies[i]).sprite); 
            }   
            fight_menu = true;
            Player.player_move(isMoving, timer);
            window.draw(Player.sprite);
        }
        
        startmapcol(Player.sprite);
        window.display();
        normal_state = true;
        
    }

    return 0;
}