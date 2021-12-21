#include "Scenes.h"

int new_game(sf::RenderWindow& window, const sf::Font& font, int& start_value)
{
    static sf::RectangleShape fade;
    static sf::SoundBuffer buffer;
    static sf::Text text;
    static sf::Clock timer;
    static sf::Sound sound;
    static int i = 255, start = 0;
    static bool s = false;

    if (start_value == 1)
    {
        text.setString(L"By³ zwyk³y niedzielny poranek. \nŒpisz w najlepsze, gdy nagle...");
        text.setFont(font);
        text.setCharacterSize(40);
        fade.setSize(sf::Vector2f(window.getSize()));
        fade.setFillColor(sf::Color(0, 0, 0, 255));
        if (!buffer.loadFromFile("siren.wav"))
            return -1;
        text.setPosition(150, 200);
        sound.setVolume(10);
        sound.setBuffer(buffer);
        start_value = 2;
    }

    window.draw(fade);

    switch (start)
    {
    case 0:
        window.draw(text);

        if (timer.getElapsedTime().asSeconds() >= 4)
        {
            text.setString(L"Budzi Ciê dŸwiêk syreny...");
            start++;
            timer.restart();
        }

        break;
    case 1:
        start++;
        sound.play();
        break;
    case 2:
        if (timer.getElapsedTime().asSeconds() >= 1)
        {
            start++;
            timer.restart();
        }
        break;
    case 3:
        window.draw(text);

        if (timer.getElapsedTime().asSeconds() >= 4)
        {
            start++;
            s = true;
        }
        break;
    default:
        break;
    }

    if (s && i > 0)
    {
        fade.setFillColor(sf::Color(0, 0, 0, i));
        if (timer.getElapsedTime().asMilliseconds() >= 20)
            i--;
    }

    if (i == 0)
        start_value = 3;

}

void bunker(sf::RenderWindow& window, sf::Font const& font, int& start_value)
{
    static int i = 0, j = 0;
    static sf::RectangleShape fade(sf::Vector2f(window.getSize()));
    static sf::Text text;
    const std::wstring strings[4] = { L"Uda³o ci siê dotrzeæ do bunkra" , L"W œrodku widzisz wiêcej osób", L"Po chwili s³ychac wybuch", L"Uspokajasz siê myœl¹, ze wszystko sie jakoœ u³o¿y..." };
    static sf::Clock timer, wait;
    const int time_stamp = 40;

    if (start_value == 3)
    {
        fade.setFillColor(sf::Color(0, 0, 0, 0));
        text.setCharacterSize(40);
        text.setFont(font);
        start_value++;
    }

    if (timer.getElapsedTime().asMilliseconds() >= 20 && i < 255) {
        ++i;
        fade.setFillColor(sf::Color(0, 0, 0, i));
    }

    window.draw(fade);

    if (i == 255)
    {
        timer.restart();
        ++i;
    }

    else if (i > 255)
    {

        if (j < strings[i - 256].length() && wait.getElapsedTime().asMilliseconds() >= time_stamp && j <= strings[i - 256].length())
        {
            ++j;
            text.setString(strings[i - 256].substr(0, j));
            text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2 - text.getCharacterSize() / 2);
            wait.restart();

        }


        else if (timer.getElapsedTime().asMilliseconds() >= time_stamp * strings[i - 256].length() + 4000)
        {
            ++i;
            j = 0;
            timer.restart();
            if (i >= 256 + sizeof(strings) / sizeof(*strings))
                start_value = 0;
        }
        window.draw(text);
    }

}