#include <SFML/Graphics.hpp>
#include "Menus.h"
#include "Character.h"
#include "main.h"
#include <filesystem>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

void save(const Character &player)
{
    if (!std::filesystem::is_directory("Saves"))
        std::filesystem::create_directory("Saves");

    time_t now = time(NULL);
    struct tm timeinfo;
    char buffer[80];

    localtime_s(&timeinfo, &now);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H%M%S", &timeinfo);
    std::string str(buffer);

    std::ofstream file("./Saves/" + str + ".txt");
    file << player;
    file.close();
}

int escape_menu(sf::RenderWindow& window, sf::RectangleShape& gui, bool& menu_open, bool* move_menu, bool& choose, sf::CircleShape& option, sf::Font const& font, bool& menu, const Character &player)
{
    sf::Vector2f const options_positions[3] = { {350,200}, {350,300}, {350, 400} };
    static int i = 0;
    static sf::Clock t;
    float wait_time = 0.2;
    sf::Text menu_text[3];
    std::string menu_string[3] = { "Wznow", "Zapisz", "Wyjdz"};

    if (menu)
    {
        menu = false;
        i = 0;
        t.restart();
    }

    if (move_menu[1] && t.getElapsedTime().asSeconds() >= wait_time)
    {
        i++;
        t.restart();
    }

    else if (move_menu[0] && t.getElapsedTime().asSeconds() >= wait_time)
    {
        i--;
        t.restart();
    }

    if (i > 2)
        i = 0;
    else if (i < 0)
        i = 2;

    option.setPosition(options_positions[i]);
    window.draw(gui);
    window.draw(option);
    for (int j = 0; j < 3; j++)
    {
        menu_text[j].setFont(font);
        menu_text[j].setPosition(options_positions[j].x + 20, options_positions[j].y);
        menu_text[j].setCharacterSize(40);
        menu_text[j].setString(menu_string[j]);
        window.draw(menu_text[j]);
    }

    if (i == 0 && choose && t.getElapsedTime().asSeconds() >= wait_time)
        menu_open = false;

    else if (i == 1 && choose && t.getElapsedTime().asSeconds() >= wait_time)
        save(player);

    else if (i == 2 && choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        window.close();
        return main();
    }


}

void fight_menu(sf::RenderWindow& window, Character& player, Character& enemy, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font)
{
    float wait_time = 0.2;
    static sf::Clock t;
    static int i = 0;
    sf::Vector2f const options_positions[4] = { {100,500}, {100,600}, {400,500}, {400,600} };
    sf::Text player_hp;
    sf::Text enemy_hp;
    sf::Text menu_text[4];
    std::string menu_string[4] = { "Atak", "Ekwipunek", "Pomin ture", "Ucieknij" };

    player_hp.setFont(font);
    player_hp.setPosition(0, 0);
    player_hp.setCharacterSize(40);
    player_hp.setString(std::to_string(player.Health).substr(0, int(log10(abs(player.Health))) + 4) + " HP");

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

    sf::Vector2f pos[4] = { player.sprite.getPosition(),enemy.sprite.getPosition() };
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
        enemy.Health -= player.stats.attack;
        t.restart();
        if (enemy.Health <= 0)
        {
            enemy.sprite.setPosition(-100, -100);
            enemy.Health = 0;
        }
        else if (player.Health <= 0)
        {
            player.sprite.setPosition(-200, -200);
            player.Health = 0;
        }
        else
            player.Health -= enemy.stats.attack;

    }

    else if (i == 2 && choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        player.Health -= enemy.stats.attack;
        t.restart();
        if (player.Health <= 0)
        {
            player.sprite.setPosition(-200, -200);
            player.Health = 0;
        }
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

void stats_menu(sf::RenderWindow& window, Character& player, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font)
{
    const sf::Vector2f options_positions[11] = { {50,200}, {50,300}, {50, 400}, {50, 500}, {50,630}, {50,50}, {600,500}, {500,200}, {500,300}, {500, 400}, {500, 500} };
    const sf::Vector2f pos = player.sprite.getPosition();
    static int i = 0;
    static sf::Clock t;
    float wait_time = 0.2;
    sf::Text menu_text[11];
    std::string menu_string[11] = { "Maksymalne zdrowie: " + std::to_string(player.stats.max_health), "Atak: " + std::to_string(player.stats.attack), "Celnosc: " + std::to_string(player.stats.accuracy), "Inteligencja: " + std::to_string(player.stats.intelligence), "Dostepne punkty doswiadczenia: " + std::to_string(player.stats.experience),"Statystyki postaci:      Poziom:", "Aktualne zdrowie: " + std::to_string(player.Health).substr(0, int(log10(abs(player.Health))) + 4), std::to_string(player.stats.lvl[0]), std::to_string(player.stats.lvl[1]), std::to_string(player.stats.lvl[2]), std::to_string(player.stats.lvl[3]) };
    int lvl_up_values[4] = {10,5,5,5};
    int max_lvl_up[4] = {300/lvl_up_values[0] - player.stats.max_health/lvl_up_values[0], 120 / lvl_up_values[1] - player.stats.attack / lvl_up_values[1], 100 / lvl_up_values[2] - player.stats.accuracy / lvl_up_values[2], 40 / lvl_up_values[3] - player.stats.intelligence / lvl_up_values[3]};
    

    static sf::Text message;
    static sf::RectangleShape message_bg;

    player.sprite.setPosition(700,400);

    if (menu)
    {
        menu = false;
        i = 0;
        message.setFont(font);
        message.setCharacterSize(55);
        message.setFillColor(sf::Color::Blue);
        message_bg.setFillColor(sf::Color(113, 218, 113, 180));
        t.restart();
    }

    if (move_menu[1] && t.getElapsedTime().asSeconds() >= wait_time)
    {
        i++;
        t.restart();
    }

    else if (move_menu[0] && t.getElapsedTime().asSeconds() >= wait_time)
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
    window.draw(option);
    for (int j = 0; j < sizeof(menu_text) / sizeof(*menu_text); j++)
    {
        menu_text[j].setFont(font);
        menu_text[j].setPosition(options_positions[j].x + 20, options_positions[j].y);
        menu_text[j].setCharacterSize(40);
        menu_text[j].setString(menu_string[j]);
        window.draw(menu_text[j]);
    }

    if (choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        if (message.getString() == "")
        {
            if (player.stats.experience >= player.stats.lvl[i] + 1 && max_lvl_up[i] > 0)
            {
                switch (i)
                {
                case 0:
                    player.stats.max_health += lvl_up_values[i];
                    break;
                case 1:
                    player.stats.attack += lvl_up_values[i];
                    break;
                case 2:
                    player.stats.accuracy += lvl_up_values[i];
                    break;
                case 3:
                    player.stats.intelligence += lvl_up_values[i];
                    break;
                default:
                    break;
                }

                player.stats.experience -= player.stats.lvl[i] + 1;
                player.stats.lvl[i] ++;
            }
            else if (max_lvl_up[i] == 0)
                message.setString("Nie mozna bardziej ulepszyc\nwybranej statystyki!");
            else
                message.setString("Brakuje ci punktow doswiadczenia!");
            
            if (message.getString() != "")
            {
                message.setPosition(window.getSize().x / 2 - message.getGlobalBounds().width / 2, window.getSize().y / 2 - message.getGlobalBounds().height / 2);
                message_bg.setSize(sf::Vector2f(message.getGlobalBounds().width + 30, message.getGlobalBounds().height + 30));
                message_bg.setPosition(window.getSize().x / 2 - message.getGlobalBounds().width / 2 - 15, window.getSize().y / 2 - message.getGlobalBounds().height / 2);
            }
            
        }
        else
        {
            message.setString("");
            message_bg.setSize(sf::Vector2f(0,0));
        }
        
    }
    
    window.draw(message_bg);
    window.draw(message);

    player.sprite.setPosition(pos);
}