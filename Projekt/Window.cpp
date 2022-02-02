#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.h"
#include "Menus.h"
#include "main.h"
#include <math.h>
#include <vector>
#include "Scenes.h"
#include "Item.h"
#include <cstdlib>
#include <ctime>
#include <fstream>


#define K sf::Keyboard

void Event(sf::RenderWindow& window, const K::Key* Keys, bool* isMoving, bool& choose, bool& menu_open, bool& menu, bool& stats_open, bool& eq) // obsługa zdarzeń sfml - Bartosz
{
    sf::Event event;
    // stany zwolnienia przycisków odpowiadających za menu - Bartosz
    static bool escape_release = true;
    static bool enter_release = true;
    static bool tab_release = true;
    static bool i_release = true; // Michał
    while (window.pollEvent(event)) // pętla podczas eventu - Bartosz
    {

        if (event.type == sf::Event::Closed) // poprawne zamknięcie okna
        {
            window.close();
        }

        //obsługa otwierania/zamykania menu w grze (aby uniknąć migającego okna)- Bartosz
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

        if (event.type == sf::Event::KeyReleased && event.key.code == K::Escape) // obsługa escape - Bartosz
            escape_release = true;

        //obsługa wyboru (aby następowało to jednokrotnie podczas wciśnięcia) - Bartosz
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

        // obsługa menu statystyk - Bartosz
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

        for (int i = 0; i < 4; i++) // sprawdzanie kierunku ruchu - Bartosz
        {
            if (K::isKeyPressed(Keys[2 * i]) || K::isKeyPressed(Keys[2 * i + 1]))
                isMoving[i] = true;
            else
                isMoving[i] = false;
        }

        //Michał
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

        if (event.type == sf::Event::KeyReleased && event.key.code == K::I)
            i_release = true;

    }
}

void startmapcol(sf::Sprite& a) //Michał
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
    if (a.getPosition().y > 516)a.setPosition(a.getPosition().x, 516);
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
    if (a.getPosition().y < 165)a.setPosition(a.getPosition().x, 165);
    //kolizja dolnej sciany
    if (a.getPosition().y > 603)a.setPosition(a.getPosition().x, 603);
    //kolizja lewej sciany
    if (a.getPosition().x < 0)a.setPosition(0, a.getPosition().y);
    //kolizja prawej sciany
    if (a.getPosition().x > 920)a.setPosition(920, a.getPosition().y);
}
void lvl5col(sf::Sprite& a)
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
    //kolizna z lewymi dolnymi budynkami
    if (a.getPosition().x < 248 && a.getPosition().y > 301 && a.getPosition().y < 305)a.setPosition(a.getPosition().x, 301);
    if (a.getPosition().x <= 248 && a.getPosition().x > 244 && a.getPosition().y > 304)a.setPosition(248, a.getPosition().y);
    if (a.getPosition().x > 247 && a.getPosition().x < 270 && a.getPosition().y > 378 && a.getPosition().y < 382)a.setPosition(a.getPosition().x, 378);
    if (a.getPosition().x < 270 && a.getPosition().y > 378)a.setPosition(270, a.getPosition().y);
    if (a.getPosition().x >= 270 && a.getPosition().x <= 399 && a.getPosition().y > 403)a.setPosition(a.getPosition().x, 403);
    if (a.getPosition().x > 396 && a.getPosition().x < 400 && a.getPosition().y > 378)a.setPosition(396, a.getPosition().y);
    if (a.getPosition().x > 400 && a.getPosition().x < 477 && a.getPosition().y > 360)a.setPosition(a.getPosition().x, 360);
    if (a.getPosition().x > 491 && a.getPosition().x < 495 && a.getPosition().y > 360)a.setPosition(495, a.getPosition().y);
    if (a.getPosition().x < 513 && a.getPosition().y > 432 && a.getPosition().y < 436)a.setPosition(a.getPosition().x, 432);
    if (a.getPosition().x <= 513 && a.getPosition().y > 432)a.setPosition(513, a.getPosition().y);
    //kolizja z lewym górnym budynkiem
    if (a.getPosition().x < 213 && a.getPosition().y < 261 && a.getPosition().y > 257)a.setPosition(a.getPosition().x, 261);
    if (a.getPosition().x < 213 && a.getPosition().y < 261)a.setPosition(213, a.getPosition().y);
    //kolizja z fontanna
    if (a.getPosition().x > 354 && a.getPosition().x < 358 && a.getPosition().y < 252 && a.getPosition().y > 77)a.setPosition(354, a.getPosition().y);
    if (a.getPosition().x >= 354 && a.getPosition().x < 591 && a.getPosition().y>78 && a.getPosition().y < 82)a.setPosition(a.getPosition().x, 78);
    if (a.getPosition().x < 603 && a.getPosition().x >599 && a.getPosition().y < 252 && a.getPosition().y > 77)a.setPosition(603, a.getPosition().y);
    if (a.getPosition().x >= 354 && a.getPosition().x < 591 && a.getPosition().y>248 && a.getPosition().y < 252)a.setPosition(a.getPosition().x, 252);
    //kolizja z budynkiem po prawej
    if (a.getPosition().x > 884 && a.getPosition().y <= 21)a.setPosition(884, a.getPosition().y);
    if (a.getPosition().x <= 887 && a.getPosition().x >= 761 && a.getPosition().y > 18 && a.getPosition().y < 22)a.setPosition(a.getPosition().x, 18);
    if (a.getPosition().x < 764 && a.getPosition().x>760 && a.getPosition().y < 21 && a.getPosition().y>9)a.setPosition(764, a.getPosition().y);
    if (a.getPosition().x < 764 && a.getPosition().x>668 && a.getPosition().y > 9 && a.getPosition().y < 13)a.setPosition(a.getPosition().x, 9);
    if (a.getPosition().x > 665 && a.getPosition().x < 669 && a.getPosition().y>9 && a.getPosition().y <= 57)a.setPosition(665, a.getPosition().y);
    if (a.getPosition().x > 642 && a.getPosition().x <= 665 && a.getPosition().y > 54 && a.getPosition().y < 58)a.setPosition(a.getPosition().x, 54);
    if (a.getPosition().x > 642 && a.getPosition().x < 646 && a.getPosition().y > 54 && a.getPosition().y < 240)a.setPosition(642, a.getPosition().y);
    if (a.getPosition().x > 642 && a.getPosition().y < 240 && a.getPosition().y>236)a.setPosition(a.getPosition().x, 240);
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
void lvl8col(sf::Sprite& a)
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
void lvl9col(sf::Sprite& a)
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

bool enemy_player_contact(sf::Sprite& player, sf::Sprite& enemy) // sprawdzanie kontaktu międzi postaciami - Bartosz
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

void enemy_load(std::vector <std::unique_ptr<Character>>& Enemies, const std::wstring& filename, const character_type* Enemies_type) // załadowanie wrogów - Bartosz
{
    std::ifstream file(filename);
    bool a = true;
    int values[4];
    std::string check;
    while (!file.eof())
    {
        if (a)
            std::getline(file, check);
        else
        {
            for (int i = 0; i < sizeof(values) / sizeof(*values); i++)
                file >> values[i];

            Enemies.push_back(std::unique_ptr<Character>(new Character(values[3], Enemies_type[values[3]], values[0])));

            sf::Sprite& last_s = Enemies.back()->sprite;
            float& last_h = Enemies.back()->Health;

            file >> last_h;

            last_s.setPosition(values[1], values[2]);
        }

        if (check.empty())
            a = false;

    }

}

int game(int new_start, const std::wstring& filename = L"") // główna funkcja zarządzająca grą - Bartosz
{
    const int w = 1000, h = 700;
    bool isMoving[4] = { false, false, false, false };
    bool choose = false, menu = true, normal_state = true, menu_open = false, stats_open = false, eq = false;
    K::Key Keys[8] = { K::W,K::Up,K::S,K::Down,K::D,K::Right,K::A,K::Left };
    int count = 0;
    sf::Clock respawn_timer;

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(w, h), "Nasza gra 2D"); // głowne okno

    sf::Font font;
    font.loadFromFile("Textures/HannoverMesseSans-dewK.ttf"); // czionka - Bartosz

    sf::RectangleShape gui(sf::Vector2f(window.getSize()));
    gui.setFillColor(sf::Color(0, 0, 0, 255)); // tło menu - Bartosz

    const character_type Player_type = { "Textures/main_character.png", 0.17, {0, 0, 460, 560}, 100, 1, 15, 60, 40, 100 }; // wartości początkowe bohatera - Bartosz
    const character_type Enemies_type[6] = { { "Textures/Enemies/Manekin.png", 2, {13 , 6, 31, 52}, 30, 1, 0 }, {"Textures/Enemies/Slime.png", 2, {2, 2, 61, 57}, 50, 2, 10, 80}, { "Textures/Enemies/Kleszcz.png", 2, {25, 2, 45, 64}, 100, 2, 20, 85}, { "Textures/Enemies/Poczwara.png", 2, {19, 3, 28, 31}, 120, 3, 8, 75}, { "Textures/Enemies/Kot.png", 2, {15, 12, 51, 21}, 100, 3, 25, 100 }, { "Textures/Enemies/Nietoperz.png", 2, {9, 17, 44, 43}, 55, 3, 30, 95 } }; // wartości początkowe wrogów - Bartosz

    int lvli = 0;

    Character Player(-1, Player_type, lvli); // obiekt bohatera - Bartosz

    std::vector <std::unique_ptr<Character>> Enemies; // wektor unikalnych wskaźników obiektów wrogów - Bartosz

    if (filename == L"") // domyślne ustawienie wartości - Bartosz
    {
        Player.sprite.setPosition(785, 231);

        int struct_types[7] = { 0, 1, 1, 2, 3, 4, 5 };

        for (int i = 0; i < sizeof(struct_types) / sizeof(*struct_types); i++)
        {
            Enemies.push_back(std::unique_ptr<Character>(new Character(struct_types[i], Enemies_type[struct_types[i]], 5)));
        }

        (*Enemies[0]).sprite.setPosition(550, 500);
        (*Enemies[1]).sprite.setPosition(400, 60);
        (*Enemies[2]).sprite.setPosition(600, 300);
        (*Enemies[3]).sprite.setPosition(800, 300);
        (*Enemies[4]).sprite.setPosition(700, 500);
        (*Enemies[5]).sprite.setPosition(200, 300);
        (*Enemies[6]).sprite.setPosition(700, 500);
        (*Enemies[0]).map_lvl = 3;
        (*Enemies[5]).map_lvl = 6;
        (*Enemies[6]).map_lvl = 6;
    }

    else // wczytywanie z pliku - Bartosz
    {
        Player << filename; // wartości bohatera
        lvli = Player.map_lvl; // aktualny poziom

        enemy_load(Enemies, filename, Enemies_type); // wrogowie
    }

    sf::CircleShape option(20, 3); // trójkąt wyboru - Bartosz
    option.setPosition(100, 100);
    option.rotate(90);

    //Michał - importowanie map oraz itemów
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
    sf::IntRect rect4(0, 0, 228, 181);
    sf::Sprite lvl4(txt4, rect4);
    lvl4.scale(w / 228.0, h / 181.0);

    sf::Texture txt5;
    txt5.loadFromFile("Textures/levels/5lvl.png");
    sf::IntRect rect5(0, 0, 240, 131);
    sf::Sprite lvl5(txt5, rect5);
    lvl5.scale(w / 240.0, h / 131.0);

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

    sf::Texture txt8;
    txt8.loadFromFile("Textures/levels/8lvl.png");
    sf::IntRect rect8(0, 0, 228, 181);
    sf::Sprite lvl8(txt8, rect8);
    lvl8.scale(w / 228.0, h / 181.0);

    sf::Texture txt9;
    txt9.loadFromFile("Textures/levels/9lvl.png");
    sf::IntRect rect9(0, 0, 240, 131);
    sf::Sprite lvl9(txt9, rect9);
    lvl9.scale(w / 240.0, h / 131.0);

    sf::Texture txti1;
    txti1.loadFromFile("Textures/items/Apteczka_d.png");
    sf::IntRect recti1(5, 2, 155, 157);
    std::vector <sf::Sprite> apteczkid;

    std::vector <std::unique_ptr<item>>Apteczka_d;
    for (int i = 0; i < 2; i++)
    {
        Apteczka_d.push_back(std::unique_ptr<item>(new item(16, 21, 22, 31, "Textures/items/Apteczka_d.png", 1.5)));
    }
    std::vector <std::unique_ptr<item>>Apteczka_m;
    for (int i = 0; i < 2; i++)
    {
        Apteczka_m.push_back(std::unique_ptr<item>(new item(21, 24, 15, 22, "Textures/items/Apteczka_m.png", 1.5)));
    }
    std::vector <std::unique_ptr<item>>jablko;
    for (int i = 0; i < 2; i++)
    {
        jablko.push_back(std::unique_ptr<item>(new item(22, 19, 27, 21, "Textures/items/jablko.png", 1.5)));
    }
    item noz = item(22, 19, 27, 21, "Textures/items/noz.png", 1.5);
    item maska = item(0, 0, 28, 23, "Textures/items/Maska.png", 1.5);

    sf::Clock timer;

    window.setFramerateLimit(60); // stała liczba klatek
    bool winn = false;
    bool nozi = true;
    bool maskai = true;
    while (window.isOpen()) // pętla otwartego okna
    {
        count = 0; // licznik wrogów na poziomie 6 - Bartosz
        window.clear();
        Event(window, Keys, isMoving, choose, menu_open, menu, stats_open, eq); // uruchamianie funkcji zdarzeń
        switch (lvli) //Michał - poruszanie sie po poziomach oraz tworzenie obiektów na nich
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
            if (Player.sprite.getPosition().x > 900 && Player.sprite.getPosition().y > 375 && Player.sprite.getPosition().y < 490 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(0, 402);
            }
            for (int i = 0; i < Apteczka_d.size(); i++)
            {
                (*Apteczka_d[i]).sprite.setPosition(625 + i * (Apteczka_d[i].get()->scale) * (10 + Apteczka_d[i].get()->width), 171 - Apteczka_d[i].get()->height);
                window.draw((*Apteczka_d[i]).sprite);
                if (enemy_player_contact(Player.sprite, (*Apteczka_d[i]).sprite) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    Player.items_v[1]++;
                    Apteczka_d.erase(Apteczka_d.begin() + i);
                }
            }
            for (int i = 0; i < Apteczka_m.size(); i++)
            {
                (*Apteczka_m[i]).sprite.setPosition(735 + i * (Apteczka_m[i].get()->scale) * (10 + Apteczka_m[i].get()->width), 171 - Apteczka_m[i].get()->height);
                window.draw((*Apteczka_m[i]).sprite);
                window.draw((*Apteczka_m[i]).sprite);
                if (enemy_player_contact(Player.sprite, (*Apteczka_m[i]).sprite) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    Player.items_v[0]++;
                    Apteczka_m.erase(Apteczka_m.begin() + i);
                }
            }
            for (int i = 0; i < jablko.size(); i++)
            {
                (*jablko[i]).sprite.setPosition(837 + i * (jablko[i].get()->scale) * (10 + jablko[i].get()->width), 171 - jablko[i].get()->height);
                window.draw((*jablko[i]).sprite);
                window.draw((*jablko[i]).sprite);
                if (enemy_player_contact(Player.sprite, (*jablko[i]).sprite) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    Player.items_v[2]++;
                    jablko.erase(jablko.begin() + i);
                }
            }
            if (nozi)
            {
                noz.sprite.setPosition(200, 200);
                window.draw(noz.sprite);
            }
            if (enemy_player_contact(Player.sprite, noz.sprite) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                Player.items_v[5] += 1;
                noz.sprite.setPosition(-100, -100);
                nozi = false;
            }
            lvl4col(Player.sprite);
            if (new_start && Player.sprite.getPosition().x >= 250) // scenka w bunkrze - Bartosz
            {
                normal_state = false;
                window.draw(Player.sprite);
                window.draw((*Enemies[0]).sprite);
                bunker(window, font, new_start, lvl6);
            }
            break;
        case 4:
            window.draw(lvl5);
            if (Player.sprite.getPosition().x > 880 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli++;
                Player.sprite.setPosition(9, 279);
            }
            lvl5col(Player.sprite);
            break;
        case 5:
            window.draw(lvl6);
            if (Player.sprite.getPosition().x > 539 && Player.sprite.getPosition().x < 677 && Player.sprite.getPosition().y < 5 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli=6;
                Player.sprite.setPosition(0, 591);
            }
            if (Player.sprite.getPosition().x > 795 && Player.sprite.getPosition().x < 840 && Player.sprite.getPosition().y > 594 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli = 7;
                Player.sprite.setPosition(459, 7);
            }
            if (Player.sprite.getPosition().y > 237 && Player.sprite.getPosition().y <297  && Player.sprite.getPosition().x > 908 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Player.toxic_immune == true)
            {
                Player.sprite.setPosition(10, 603);
                lvli = 8;
            }
            lvl6col(Player.sprite);
            break;
        case 6:
            window.draw(lvl7);
            if (Player.sprite.getPosition().y > 601 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli--;
                Player.sprite.setPosition(600, 7);
            }
            lvl7col(Player.sprite);
            break;
        case 7:
            window.draw(lvl8);
            if (Player.sprite.getPosition().y < 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                lvli=lvli-2;
                Player.sprite.setPosition(819,562);
            }
            if (maskai)
            {
                maska.sprite.setPosition(483, 327);
                window.draw(maska.sprite);
            }
            if (enemy_player_contact(Player.sprite, maska.sprite) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                Player.items_v[6] += 1;
                maska.sprite.setPosition(-100, -100);
                maskai = false;
            }
            lvl8col(Player.sprite);
            break;
        case 8:
            Player.sprite.setPosition(10, 400);
            if (Player.sprite.getPosition().x > 939 )
            {   
                lvli=9;
            }
            window.draw(lvl9);
            lvl9col(Player.sprite);
            
        case 9:
            Player.sprite.setPosition(-100, -100);
            window.draw(gui);
            sf::Text win(L"WYGRAŁEŚ!", font, 100);
            win.setFillColor(sf::Color::Green);
            win.setPosition(w / 2 - win.getGlobalBounds().width / 2, h / 2 - win.getGlobalBounds().height / 2);
            window.draw(win);

            break;

        }

        Player.map_lvl = lvli; //poziom, na którym jest gracz ma być taki jak aktualnie wyświetlany

        // obsługa menu, która nie może kolidować z ruchem postaci, bądź sprawdzaniem kolizji z wrogami; pętla za każdym razem sprawdza warunek, żeby okno się nie freezowało - Bartosz
        if (menu_open) // menu escape
        {
            escape_menu(window, gui, menu_open, isMoving, choose, option, font, menu, Player, Enemies);
            normal_state = false;
        }

        else if (stats_open) // menu statystyk
        {
            stats_menu(window, Player, gui, isMoving, choose, option, menu, font);
            normal_state = false;
        }
        else if (eq) //Michał-ekwipunek podczas walki
        {
            ekwipunek(window, Player, gui, isMoving, choose, option, menu, font);
            normal_state = false;
        }

        else // uruchomienie walki oraz ustawienia z nią związane - Bartosz
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


        if (Player.Health <= 0 and !menu_open) // informacja o śmierci - Bartosz
        {
            window.draw(gui);
            sf::Text death(L"ŚMIERĆ!", font, 100);
            death.setFillColor(sf::Color::Red);
            death.setPosition(w / 2 - death.getGlobalBounds().width / 2, h / 2 - death.getGlobalBounds().height / 2);
            window.draw(death);
        }

        else if (normal_state) // jeśli nie jest otwarte żadne menu to usuwani są nieżywi wrogowie z wektora oraz resetowany jest wygląd bohatera, a także nastepuje rysowanie - Bartosz
        {
            Player.sprite.setColor(sf::Color::White);
            for (int i = 0; i < Enemies.size(); i++)
            {
                if ((*Enemies[i]).Health == 0)
                {
                    Player.stats.experience += (*Enemies[i]).stats.experience;
                    Enemies.erase(Enemies.begin() + i);
                    i--;
                }
                else if ((*Enemies[i]).map_lvl == lvli)
                    window.draw((*Enemies[i]).sprite);
                if (i >= 0 && (*Enemies[i]).map_lvl == 6)
                    count++;
            }
            menu = true;
            Player.player_move(isMoving, timer);
            window.draw(Player.sprite);
        }

        if (new_start && new_start < 3) // nowa gra - Bartosz
            new_game(window, font, new_start);

        if (count < 4 && respawn_timer.getElapsedTime().asSeconds() >= 35) // reset czasu do nowego wroga - Bartosz
        {
            respawn_timer.restart();
        }

        else if (count < 4 && respawn_timer.getElapsedTime().asSeconds() >= 30) // tworzenie wroga na 'arenie' - Bartosz
        {
            int type = rand() % 5 + 1;
            Enemies.push_back(std::unique_ptr<Character>(new Character(type, Enemies_type[type], 6)));
            sf::Sprite& last = Enemies.back()->sprite;
            while (type)
            {
                last.setPosition(rand() % (w - int(std::floor(last.getGlobalBounds().width))), rand() % (h - int(std::floor(last.getGlobalBounds().height))));
                for (int i = 0; i < Enemies.size() - 1; i++)
                {
                    if ((*Enemies[i]).map_lvl == 6 && enemy_player_contact((*Enemies[i]).sprite, last))
                        break;
                    if (i == Enemies.size() - 2)
                        type = 0;
                }

            }
            respawn_timer.restart();
        }


        normal_state = true; // ustawienie zwykłego stanu - Bartosz
        window.display(); // wyświetlanie wszystkiego


    }
    return 0;
}
