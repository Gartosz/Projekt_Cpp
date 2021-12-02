#include <SFML/Graphics.hpp>
#include "Menus.h"
#include "Character.h"
#include "main.h"

int escape_menu(sf::RenderWindow& window, sf::RectangleShape& gui, bool& menu_open, bool* move_menu, bool& choose, sf::CircleShape& option, sf::Font const& font, bool& menu)
{
    sf::Vector2f const options_positions[4] = { {350,200}, {350,400} };
    static int i = 0;
    static sf::Clock t;
    float wait_time = 0.2;
    sf::Text menu_text[2];
    std::string menu_string[2] = { "Wznow", "Wyjdz" };

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

    if (i > 1)
        i = 0;
    else if (i < 0)
        i = 1;

    option.setPosition(options_positions[i]);
    window.draw(gui);
    window.draw(option);
    for (int j = 0; j < 2; j++)
    {
        menu_text[j].setFont(font);
        menu_text[j].setPosition(options_positions[j].x + 20, options_positions[j].y);
        menu_text[j].setCharacterSize(40);
        menu_text[j].setString(menu_string[j]);
        window.draw(menu_text[j]);
    }

    if (i == 0 && choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        menu_open = false;
    }
    else if (i == 1 && choose && t.getElapsedTime().asSeconds() >= wait_time)
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
        enemy.Health -= player.Attack;
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
            player.Health -= enemy.Attack;

    }

    else if (i == 2 && choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        player.Health -= enemy.Attack;
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