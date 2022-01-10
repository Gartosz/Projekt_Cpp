#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int new_game(sf::RenderWindow& window, const sf::Font& font, int& start_value);
void bunker(sf::RenderWindow& window, sf::Font const& font, int& start_value, const sf::Sprite& map);