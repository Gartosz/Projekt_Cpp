#pragma once
struct character_type {
    std::string txt_patch;
    float scale;
    int size[4];
    float Health;
    float Attack;
};

class Character {
public:
    float Health;
    float Attack;
    sf::Texture txt;
    sf::Sprite sprite;
    Character(character_type const& values);
    void player_move(bool* isMoving, sf::Clock& timer);

private:
    float speed = 3;
    sf::IntRect rect;
    void move(sf::Clock& timer, double const& speed_h, double const& speed_v, const int& top, const int& height);
};
