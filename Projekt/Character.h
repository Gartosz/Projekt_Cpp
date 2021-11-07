class Character {
public:
    sf::Texture txt;
    sf::Sprite sprite;
    Character(int const& l = 0, int const& t = 0, int const& h = 560);
    void move(sf::Clock& timer, double const& speed_h, double const& speed_v, const int& top, const int& height);
    
private:
    float speed = 3;
    sf::IntRect rect;
    int ch_width = 460;
};
#pragma once