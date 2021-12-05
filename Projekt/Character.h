#pragma once
struct character_type {
    std::string txt_patch;
    float scale;
    int size[4];
    float Health;
    int max_health = Health;
    int attack = 0;
    int accuracy = 0;
    int intelligence = 0;
    int lvl[4] = { 0,0,0,0 };
    int experience = 2;
};

class Character {
public:
    float Health;
    sf::Texture txt;
    sf::Sprite sprite;
    int map_lvl=0;
    struct Stats
    {
        int max_health = 0, attack = 0, accuracy = 0, intelligence = 0;
        int lvl[4] = { 0,0,0,0 };
        int experience = 0;
    };
    Stats stats;
    Character(character_type const& values);
    void player_move(bool* isMoving, sf::Clock& timer);

private:
    float speed = 3;
    sf::IntRect rect;
    void move(sf::Clock& timer, double const& speed_h, double const& speed_v, const int& top, const int& height);
    friend std::ostream& operator<<(std::ostream& os, Character const& x) {
        os << x.map_lvl << " " << x.sprite.getPosition().x << " " << x.sprite.getPosition().y << "\n";
        os << x.Health << "\n" << x.stats.experience << "\n";
        os << x.stats.max_health << " " << x.stats.attack << " " << x.stats.accuracy << " " << x.stats.intelligence << "\n";
        for (int i = 0; i < sizeof(x.stats.lvl)/ sizeof(*x.stats.lvl); i++)
            os << x.stats.lvl[i] << " ";
        return os;
    }
};
