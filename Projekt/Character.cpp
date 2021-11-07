#include <SFML/Graphics.hpp>
#include "Character.h"

    Character::Character(int const& l, int const& t, int const& h)
    {
        rect.left = l;
        rect.top = t;
        rect.width = ch_width;
        rect.height = h;
        sprite.setTexture(txt);
        sprite.setTextureRect(rect);
    }

    void Character::move(sf::Clock& timer, double const& speed_h, double const& speed_v, const int& top, const int& height)
    {
        rect.top = top;
        rect.height = height;
        static int frame = 0;
        sprite.move(speed_h*speed, speed_v*speed);
        if (timer.getElapsedTime().asSeconds() > 0.25)
        {
            if (frame > 3) frame = 0;
            rect.left = frame * ch_width;
            sprite.setTextureRect(rect);
            timer.restart();
            frame++;
        }
    }
