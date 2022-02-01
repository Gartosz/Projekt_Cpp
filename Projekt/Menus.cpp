#include <SFML/Graphics.hpp>
#include "Menus.h"
#include "Character.h"
#include "main.h"
#include <filesystem>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <vector>

void save(const Character& player, const std::vector <std::unique_ptr<Character>>& Enemies) // zapisywanie - Bartosz
{
    if (!std::filesystem::is_directory("Saves")) // sprawdzenie istnienia folderu
        std::filesystem::create_directory("Saves");


    //tworzenie nazwy jako akutalnej daty i czasu
    time_t now = time(NULL);
    struct tm timeinfo;
    char buffer[80];

    localtime_s(&timeinfo, &now);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H%M%S", &timeinfo);
    std::string filename(buffer);

    //zapsywanie
    std::ofstream file("./Saves/" + filename + ".txt");
    file << player;
    
    for (int i = 0; i < Enemies.size(); i++)
    {
        file << (*Enemies[i]).map_lvl << " " << (*Enemies[i]).sprite.getPosition().x << " " << (*Enemies[i]).sprite.getPosition().y << " " << (*Enemies[i]).type << " " << (*Enemies[i]).Health << "\n";
    }

    file.close();
}

// escape menu - Bartosz
int escape_menu(sf::RenderWindow& window, sf::RectangleShape& gui, bool& menu_open, bool* move_menu, bool& choose, sf::CircleShape& option, sf::Font const& font, bool& menu, const Character& player, const std::vector <std::unique_ptr<Character>>& Enemies)
{
    sf::Vector2f const options_positions[4] = { {350,200}, {350,300}, {350, 400}, {350, 500} }; // pozycje opcji
    static int i = 0;
    static sf::Clock t;
    float wait_time = 0.2;
    sf::Text menu_text[4];
    std::wstring menu_string[4] = { L"Wznów", L"Zapisz", L"Wyjdź do menu głównego", L"Wyjdź do pulpitu"}; // opcje

    if (menu) // inicjowanie wartości po wejściu do menu
    {
        menu = false;
        i = 0;
        t.restart();
    }

    // poruszanie się z ograniczeniem czasowym
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

    if (i > int(sizeof(menu_text) / sizeof(*menu_text)) - 1)
        i = 0;
        
    else if (i < 0)
        i = int(sizeof(menu_text) / sizeof(*menu_text)) - 1;

    // wyświetlania
    option.setPosition(options_positions[i]); // aktualny wybór
    window.draw(gui);
    window.draw(option);
    for (int j = 0; j < sizeof(menu_text)/sizeof(*menu_text); j++)
    {
        menu_text[j].setFont(font);
        menu_text[j].setPosition(options_positions[j].x + 20, options_positions[j].y);
        menu_text[j].setCharacterSize(40);
        menu_text[j].setString(menu_string[j]);
        window.draw(menu_text[j]);
    }

    // obsługa opcji
    if (i == 0 && choose && t.getElapsedTime().asSeconds() >= wait_time) // wznowienie
        menu_open = false;

    else if (i == 1 && choose && t.getElapsedTime().asSeconds() >= wait_time) // zapis
        save(player, Enemies);

    else if (i == 2 && choose && t.getElapsedTime().asSeconds() >= wait_time) // menu główne
    {
        window.close();
        return main();
    }

    else if (i == 3 && choose && t.getElapsedTime().asSeconds() >= wait_time) // wyjście do pulpitu
    {
        window.close();
        return 0;
    }


}

// walka z wrogiem - Bartosz
void fight_menu(sf::RenderWindow& window, Character& player, Character& enemy, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font)
{
    float wait_time = 0.2;
    static sf::Clock t;
    static int i = 0;
    static bool blink[2] = { false, false };
    sf::Vector2f const options_positions[4] = { {100,500}, {100,600}, {400,500}, {400,600} }; // pozycje opcji
    sf::Text player_hp;
    sf::Text enemy_hp;
    sf::Text menu_text[4];
    std::wstring menu_string[4] = { L"Atak", L"Ekwipunek", L"Pomiń turę", L"Ucieknij" }; // opcje

    // wyświetlanie życia
    player_hp.setFont(font);
    player_hp.setPosition(0, 0);
    player_hp.setCharacterSize(40);
    player_hp.setString(std::to_string(player.Health).substr(0, int(log10(abs(player.Health))) + 4) + " HP");

    enemy_hp.setFont(font);
    enemy_hp.setPosition(800, 0);
    enemy_hp.setCharacterSize(40);
    enemy_hp.setString(std::to_string(enemy.Health).substr(0, int(log10(abs(enemy.Health))) + 4) + " HP");

    if (menu) // inicjowanie wartości po wejściu do walki
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

    // pozycja w walce
    sf::Vector2f pos[4] = { player.sprite.getPosition(), enemy.sprite.getPosition() };
    player.sprite.setPosition(300, 250);
    enemy.sprite.setPosition(600, 100);

    // poruszanie się z ograniczeniem czasowym
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

    // wyświetlania
    option.setPosition(options_positions[i]); // aktualny wybór

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

    // przywrócenie pozycji
    player.sprite.setPosition(pos[0]);
    enemy.sprite.setPosition(pos[1]);

    static bool eq = true; // Michał

    if (i == 0 && choose && t.getElapsedTime().asSeconds() >= wait_time) // atak
    {
        if (rand() % 100 + 1 <= player.stats.accuracy) // sprawdzanie celności bohatera
        {
            enemy.Health -= player.stats.attack;
            blink[1] = true;
            enemy.sprite.setColor(sf::Color(220, 100, 150, 255));
        }

        if (enemy.Health <= 0)
        {
            enemy.sprite.setPosition(-100, -100);
            enemy.Health = 0;
        }
        
        else if (rand() % 100 + 1 <= enemy.stats.accuracy) // sprawdzanie celności wroga
        {
            player.Health -= enemy.stats.attack;
            blink[0] = true;
            player.sprite.setColor(sf::Color(220, 100, 150, 255));
        }

        if (player.Health <= 0)
        {
            player.sprite.setPosition(-200, -200);
            player.Health = 0;
        }

        t.restart();
    }
    else if (i == 1 && choose) // ekwipunek
    {
        //Michał
        if (eq) { ekwipunek(window, player, gui, move_menu, choose, option, menu, font); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))eq = false;

    }

    else if (i == 2 && choose && t.getElapsedTime().asSeconds() >= wait_time) // pominięcie tury
    {
        if (rand() % 100 + 1 <= enemy.stats.accuracy) // sprawdzanie celności wroga
        {
            player.Health -= enemy.stats.attack;
            blink[0] = true;
            player.sprite.setColor(sf::Color(220, 100, 150, 255));
        }
        
        if (player.Health <= 0)
        {
            player.sprite.setPosition(-200, -200);
            player.Health = 0;
        }
        

        t.restart();
    }

    else if (i == 3 && choose) // ucieczka
    {
        if (rand() % 100 + 1 > player.stats.intelligence) // sprawdzanie inteligencji bohatera
            player.Health -= enemy.stats.attack;

        if (player.Health <= 0)
        {
            player.sprite.setPosition(-200, -200);
            player.Health = 0;
        }
        else // odsunięcie od wroga, aby dezaktywować tryb walki
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

        enemy.Health = enemy.stats.max_health; // odnowienie życia wroga
    }

    if ((blink[0] || blink[1]) && t.getElapsedTime().asMilliseconds() >= 120) // wyłączenie mignięcia po ataku
    {
        enemy.sprite.setColor(sf::Color::White);
        player.sprite.setColor(sf::Color::White);
        blink[0] = false;
        blink[1] = false;

    }

}
        

// menu statystyk - Bartosz
void stats_menu(sf::RenderWindow& window, Character& player, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font)
{
    const sf::Vector2f options_positions[11] = { {50,200}, {50,300}, {50, 400}, {50, 500}, {50,630}, {50,50}, {600,500}, {500,200}, {500,300}, {500, 400}, {500, 500} }; // pozycje opcji
    const sf::Vector2f pos = player.sprite.getPosition();
    static int i = 0;
    static sf::Clock t;
    float wait_time = 0.2;
    sf::Text menu_text[11];
    // opcje
    std::wstring menu_string[11] = { L"Maksymalne zdrowie: " + std::to_wstring(player.stats.max_health), L"Atak: " + std::to_wstring(player.stats.attack), L"Celność: " + std::to_wstring(player.stats.accuracy), L"Inteligencja: " + std::to_wstring(player.stats.intelligence), L"Dostępne punkty doświadczenia: " + std::to_wstring(player.stats.experience),L"Statystyki postaci:      Poziom:", L"Aktualne zdrowie: " + std::to_wstring(player.Health).substr(0, int(log10(abs(player.Health))) + 4), std::to_wstring(player.stats.lvl[0]), std::to_wstring(player.stats.lvl[1]), std::to_wstring(player.stats.lvl[2]), std::to_wstring(player.stats.lvl[3]) };
    int lvl_up_values[4] = { 10, 5, 10, 5 }; // wartości ulepszania poziomów
    // maksymalne wartości poziomów
    int max_lvl_up[4] = { 300 / lvl_up_values[0] - player.stats.max_health / lvl_up_values[0], 120 / lvl_up_values[1] - player.stats.attack / lvl_up_values[1], 100 / lvl_up_values[2] - player.stats.accuracy / lvl_up_values[2], 100 / lvl_up_values[3] - player.stats.intelligence / lvl_up_values[3] };


    static sf::Text message;
    static sf::RectangleShape message_bg;

    player.sprite.setPosition(700, 400);

    if (menu) // inicjowanie wartości po wejściu do menu
    {
        menu = false;
        i = 0;
        message.setFont(font);
        message.setCharacterSize(55);
        message.setFillColor(sf::Color::Blue);
        message_bg.setFillColor(sf::Color(113, 218, 113, 180));
        t.restart();
    }

    // poruszanie się z ograniczeniem czasowym
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

    // wyświetlanie
    option.setPosition(options_positions[i]); // aktualny wybór
    window.draw(gui);
    window.draw(player.sprite);

    for (int j = 0; j < sizeof(menu_text) / sizeof(*menu_text); j++)
    {
        menu_text[j].setFont(font);
        menu_text[j].setPosition(options_positions[j].x + 20, options_positions[j].y);
        menu_text[j].setCharacterSize(40);
        menu_text[j].setString(menu_string[j]);
        window.draw(menu_text[j]);
    }

    option.setPosition(options_positions[i]);
    window.draw(option);

    if (choose && t.getElapsedTime().asSeconds() >= wait_time) // wciśnięcie entera(wybór)
    {
        if (message.getString() == "") // brak informacji
        {
            if (player.stats.experience >= player.stats.lvl[i] + 1 && max_lvl_up[i] > 0) // sprawdzanie ilości wymaganych punktów
            {
                switch (i) // ulepszanie poszczególnych wartości
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

                // zmiana ilości punktów doświadczenia
                player.stats.experience -= player.stats.lvl[i] + 1;
                player.stats.lvl[i] ++;
            }
            // ustawienie informacji zależnie od sytuacji
            else if (max_lvl_up[i] == 0) 
                message.setString(L"Nie można bardziej ulepszyć\nwybranej statystyki!");
            else
                message.setString(L"Brakuje ci punktów doświadczenia!");

            if (message.getString() != "") // ustawienie pozycji informacji
            {
                message.setPosition(window.getSize().x / 2 - message.getGlobalBounds().width / 2, window.getSize().y / 2 - message.getGlobalBounds().height / 2);
                message_bg.setSize(sf::Vector2f(message.getGlobalBounds().width + 30, message.getGlobalBounds().height + 30));
                message_bg.setPosition(window.getSize().x / 2 - message.getGlobalBounds().width / 2 - 15, window.getSize().y / 2 - message.getGlobalBounds().height / 2);
            }

        }
        else // kasowanie informacji
        {
            message.setString("");
            message_bg.setSize(sf::Vector2f(0, 0));
        }

    }
    // wyświetlanie nowych informacji
    window.draw(message_bg);
    window.draw(message);

    player.sprite.setPosition(pos); // przywrócenie pozycji
}


// Michał
void ekwipunek(sf::RenderWindow& window, Character& player, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font)
{
    sf::Text eq[sizeof(player.items_n) / sizeof(player.items_n[0]) + 1];
    const sf::Vector2f options_positions[6] = {{10,90}, {10,140}, {10, 190}, {10, 240}, {10,290}, {10,340}};
    int xeq = 40, yeq = 10;
    static int i = 0;
    static sf::Clock t;
    float wait_time = 0.2;
    static sf::RectangleShape message_bg;
    static sf::Text message;
    static std::string uzywane;
    window.draw(gui);
    for (int i = 0; i < (sizeof(player.items_n) / sizeof(player.items_n[0])); i++)
    {
        if (i == 0)
        {
            eq[i].setFont(font);
            eq[i].setPosition(xeq, yeq);
            eq[i].setCharacterSize(50);
            eq[i].setString("Ekwipunek:");
            yeq += 80;
            window.draw(eq[i]);
        }
        eq[i].setFont(font);
        eq[i].setPosition(xeq, yeq);
        eq[i].setCharacterSize(30);
        eq[i].setString(player.items_n[i] + " : " + std::to_string(player.items_v[i]));
        yeq += 50;
        
        window.draw(eq[i]);
        window.draw(message_bg);
        
    }
    
    if (menu)
    {
        menu = false;
        i = 0;
        message.setFont(font);
        message.setCharacterSize(40);
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
    
    if (i >= sizeof(player.items_n) / sizeof(player.items_n[0]))
        i = 0;
    else if (i < 0)
        i = sizeof(player.items_n) / sizeof(player.items_n[0]);
    if (choose && t.getElapsedTime().asSeconds() >= wait_time)
    {
        if (message.getString() == "")
        {
            if (player.items_v[i] != 0)
            {
                //"Mala apteczka","Duza apteczka","Jablko","Pistolet","Butelka","Noz"
                switch (i)
                {
                case 0:
                    player.items_v[i]--;
                    player.Health += round(player.stats.max_health * 0.15);
                    if (player.Health > player.stats.max_health)player.Health = player.stats.max_health;
                    break;
                case 1:
                    player.items_v[i]--;
                    player.Health += round(player.stats.max_health * 0.3);
                    if (player.Health > player.stats.max_health)player.Health = player.stats.max_health;
                    break;
                case 2:
                    player.items_v[i]--;
                    player.Health += round(player.stats.max_health * 0.05);
                    if (player.Health > player.stats.max_health)player.Health = player.stats.max_health;
                    break;
                case 3:
                    if (uzywane != "Pistolet")
                    {
                        player.items_n[i] += "(zalozone)";
                        player.stats.attack += 30;
                        uzywane = "Pistolet";
                    }
                    else
                    {
                        uzywane = "";
                        player.stats.attack -= 30;
                        player.items_n[i] = "Pistolet";
                    }

                    break;
                case 4:
                    if (uzywane != "butelka")
                    {
                        player.items_n[i] += "(zalozone)";
                        player.stats.attack += 10;
                        uzywane = "butelka";
                    }
                    else
                    {
                        uzywane = "";
                        player.stats.attack -= 10;
                        player.items_n[i] = "Butelka";
                    }
                    break;
                case 5:
                    if (uzywane != "noz")
                    {
                        player.items_n[i] += "(zalozone)";
                        player.stats.attack += 20;
                        uzywane = "noz";
                    }
                    else
                    {
                        uzywane = "";
                        player.stats.attack -= 20;
                        player.items_n[i] = "Noz";
                    }
                    break;
                }
            }
            else if (player.items_v[i] == 0)message.setString("Nie mozna uzyc przedmiotu \n (ilosc:0) !");
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
            message_bg.setSize(sf::Vector2f(0, 0));
        }
        
    }
    
    option.setPosition(options_positions[i]);
    window.draw(option);
    window.draw(message);
    window.draw(message_bg);
}
