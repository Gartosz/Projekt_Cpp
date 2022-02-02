#include <SFML/Graphics.hpp>
#include "Item.h"


item::item(float xp, float yp, float heightt, float widthh, std::string txt_path, float scalee)
{
	rect.left = xp;
	rect.top = yp;
	rect.height = heightt;
	rect.width = widthh;
	scale = scalee;
	width = widthh;
	height = heightt;
	txt.loadFromFile(txt_path);
	sprite.setTexture(txt);
	sprite.setTextureRect(rect);
	sprite.setScale(scalee, scalee);


}