#pragma once
#include <fstream>

struct character_type { //zmienne potrzebne do stworzenia obiektu - Bartosz
    std::string txt_patch;
    float scale;
    int size[4];
    int Health = 10;
    int experience = 2;
    int attack = 0;
    int accuracy = 0;
    int intelligence = 0;
    int max_health = Health;
    int lvl[4] = { 0,0,0,0 }; 
};

class Character { // klasa postaci(bohater oraz wrogowie) - Bartosz
public:
    int type;
    float Health;
    sf::Texture txt;
    sf::Sprite sprite;
    int map_lvl = 0;
    struct Stats
    {
        int max_health = 0, attack = 0, accuracy = 0, intelligence = 0;
        int lvl[4] = { 0,0,0,0 };
        int experience = 0;
    };
    Stats stats;
    std::string items_n[6] ={ "Mala apteczka","Duza apteczka","Jablko","Pistolet","Butelka","Noz" }; // Micha³
    int items_v[6] = { 0,0,0,0,0,0 }; // Micha³
    Character(const int &type, const character_type& values, const int& map_lvl);
    void player_move(bool* isMoving, sf::Clock& timer);

private:
    float speed = 3;
    sf::IntRect rect;
    void move(sf::Clock& timer, double const& speed_h, double const& speed_v, const int& top, const int& height);

    friend std::ostream& operator<<(std::ostream& os, Character const& x) { // wartoœci g³ownego bohatera zwracane podczas zapisu - Bartosz
        os << x.map_lvl << " " << x.sprite.getPosition().x << " " << x.sprite.getPosition().y << "\n";
        os << x.Health << "\n" << x.stats.experience << "\n";
        os << x.stats.max_health << " " << x.stats.attack << " " << x.stats.accuracy << " " << x.stats.intelligence << "\n";
        for (int i = 0; i < sizeof(x.stats.lvl) / sizeof(*x.stats.lvl); i++)
            os << x.stats.lvl[i] << " ";
        os << "\n\n";
        return os;
    }

    friend Character& operator<<(Character& x, const std::wstring& filename) { // wartoœci g³ównego bohatera ustawiane podczas wczytywania - Bartosz

        std::ifstream file(filename);
        int values[13];
        for (int i = 0; i < sizeof(values) / sizeof(*values); i++)
            file >> values[i];

        file.close();

        x.map_lvl = values[0];
        x.sprite.setPosition(values[1], values[2]);
        x.Health = values[3];
        x.stats.experience = values[4];
        x.stats.max_health = values[5];
        x.stats.attack = values[6];
        x.stats.accuracy = values[7];
        x.stats.intelligence = values[8];
        for (int i = 0; i < 4; i++)
            x.stats.lvl[i] = values[i + 9];

        return x;
    }
};