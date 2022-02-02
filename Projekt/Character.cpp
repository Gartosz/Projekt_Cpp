#include <SFML/Graphics.hpp>
#include "Character.h"

Character::Character(const int& type, const character_type& values, const int& map_lvl) // konstruktor klasy - Bartosz
{
    this->type = type;
    rect.left = values.size[0];
    rect.top = values.size[1];
    rect.width = values.size[2];
    rect.height = values.size[3];
    txt.loadFromFile(values.txt_patch);
    sprite.setTexture(txt);
    sprite.setTextureRect(rect);
    sprite.setScale(values.scale, values.scale);
    Health = values.Health;
    stats.max_health = Health;
    stats.attack = values.attack;
    stats.accuracy = values.accuracy;
    stats.intelligence = values.intelligence;
    stats.experience = values.experience;
    for (int i = 0; i < 4; i++)
        stats.lvl[i] = values.lvl[i];
    this->map_lvl = map_lvl;
}

void Character::move(sf::Clock& timer, double const& speed_h, double const& speed_v, const int& top, const int& height) // funkcja poruszaj¹ca postaci¹ w danym kierunku oraz zmieniaj¹ca animacjê - Bartosz
{
    rect.top = top;
    rect.height = height;
    static int frame = 0;
    sprite.move(speed_h * speed, speed_v * speed);
    if (timer.getElapsedTime().asSeconds() > 0.25)
    {
        if (frame > 3) frame = 0;
        rect.left = frame * rect.width;
        sprite.setTextureRect(rect);
        timer.restart();
        frame++;
    }
}

void Character::player_move(bool* isMoving, sf::Clock& timer) // funkcja przekazuj¹ca wartoœci do poruszania siê, zale¿nie od wciœniêtego przycisku - Bartosz
{
    if (isMoving[0])
        this->move(timer, 0, -1, 1840, 560);

    if (isMoving[1])
        this->move(timer, 0, 1, 0, 560);

    if (isMoving[2])
        this->move(timer, 1, 0, 590, 595);

    if (isMoving[3])
        this->move(timer, -1, 0, 1215, 595);
}
