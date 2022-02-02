#pragma once
#include "Character.h"

int escape_menu(sf::RenderWindow& window, sf::RectangleShape& gui, bool& menu_open, bool* move_menu, bool& choose, sf::CircleShape& option, sf::Font const& font, bool& menu, const Character& player, const std::vector <std::unique_ptr<Character>>& Enemies);


void fight_menu(sf::RenderWindow& window, Character& player, Character& enemy, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font);

void stats_menu(sf::RenderWindow& window, Character& player, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font);

void ekwipunek(sf::RenderWindow& window, Character& player, sf::RectangleShape& gui, bool* move_menu, bool& choose, sf::CircleShape& option, bool& menu, sf::Font const& font);