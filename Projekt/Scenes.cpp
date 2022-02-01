#include "Scenes.h"

int new_game(sf::RenderWindow& window, const sf::Font& font, int& start_value) // scenka nowej gry - Bartosz
{
    static sf::RectangleShape fade;
    static sf::SoundBuffer buffer;
    static sf::Text text;
    static sf::Clock timer;
    static sf::Sound sound;
    static int i = 255, start = 0;
    static bool s = false;

    if (start_value == 1) // pierwsza wiadomoœci oraz ³adownie dŸwiêku
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

    window.draw(fade); // t³o

    switch (start)
    {
    case 0: // ustawienie drugiej wiadomoœci
        window.draw(text);

        if (timer.getElapsedTime().asSeconds() >= 4)
        {
            text.setString(L"Budzi Ciê dŸwiêk syreny.");
            start++;
            timer.restart();
        }

        break;
    case 1: // uruchomienie dŸwiêku syreny
        start++;
        sound.play();
        break;
    case 2: // odczekanie sekundy
        if (timer.getElapsedTime().asSeconds() >= 1)
        {
            start++;
            timer.restart();
        }
        break;
    case 3: // wyœwietlenie drugiej wiadomoœci
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

    if (s && i > 0) // rozjaœnianie siê ekranu
    {
        fade.setFillColor(sf::Color(0, 0, 0, i));
        if (timer.getElapsedTime().asMilliseconds() >= 20)
            i--;
    }

    if (i == 0) // zmiana wartoœci, aby poprawnie uruchomiæ nastêpn¹ scenkê
        start_value = 3;

}

// scenka w bunkrze - Bartosz
void bunker(sf::RenderWindow& window, sf::Font const& font, int& start_value, const sf::Sprite &map)
{
    static int i = 0, j = 0;
    static sf::RectangleShape fade(sf::Vector2f(window.getSize())), fade2(sf::Vector2f(window.getSize()));
    static sf::Text text;
    const std::wstring strings[10] = { L"Uda³o ci siê dotrzeæ do bunkra na czas." , L"W œrodku widzisz tylko spore zapasy jedzenia, wody\ni innych potrzebnych do przetrwania rzeczy.", L"Po chwili s³ychaæ wybuch.", L"Przypomina Ci siê, ¿e wczoraj Twoja rodzina\nwyjecha³a na kilka dni.", L"Nie wiesz czy j¹ jeszcze kiedyœ zobaczysz.", L"Starasz siê uspokoiæ myœl¹, ¿e wszystko sie jakoœ u³o¿y...", L" ", L"Po kilku tygodniach spêdzonych samotnie kilkanaœcie metrów\npod ziemi¹, postanawiasz wyjœæ na powierzchniê...", L"Gdy to zrobi³eœ by³eœ w szoku widz¹c to,\njak zmieni³o siê otoczenie."};
    static sf::Clock timer, wait;
    const int time_stamp = 40;

    if (start_value == 3) // inicjowanie wartoœci
    {
        fade.setFillColor(sf::Color(0, 0, 0, 0));
        fade2.setFillColor(sf::Color(255, 255, 255, 100));
        text.setCharacterSize(40);
        text.setFont(font);
        start_value++;
    }

    if (start_value < 5 && timer.getElapsedTime().asMilliseconds() >= 15 && i < 255) // œciemnianie siê obrazu
    {
        ++i;
        fade.setFillColor(sf::Color(0, 0, 0, i));
        timer.restart();
    }

    else if (start_value < 5 && i == 255) // ustawienie wy¿szej wartoœci i, aby przejœæ dalej
    {
        timer.restart();
        ++i;
    }

    window.draw(fade); // rysowanie t³a

    if (i > 255)
    {
        // tekst zmieniaj¹cy siê o jeden znak
        if (start_value <5 && j < strings[i - 256].length() && wait.getElapsedTime().asMilliseconds() >= time_stamp && j <= strings[i - 256].length())
        {
            ++j;
            text.setString(strings[i - 256].substr(0, j));
            text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2, window.getSize().y / 2 - text.getCharacterSize() / 2);
            wait.restart();

        }

        // nastêpna wiadomoœæ po odczekaniu
        else if (start_value < 5 && timer.getElapsedTime().asMilliseconds() >= time_stamp * strings[i - 256].length() + 4000 && i - 256 < int(sizeof(strings) / sizeof(*strings)) - 1)
        {
            ++i;
            j = 0;
            timer.restart();
        }

        else if (start_value < 5 && i >= 256 + int(sizeof(strings) / sizeof(*strings)) - 1) // przejœcie do kolejnego elementu
            start_value = 5;

        if (start_value == 6 && timer.getElapsedTime().asSeconds() >= 5) // ustawienie wartoœci do nastêpnej sceny
        {
            start_value = 7;
            j = 255;
            timer.restart();
        }

        else if (start_value == 7 && timer.getElapsedTime().asMilliseconds() >= 5 && j > 0) // œciemnianie siê mapy
        {
            --j;
            if( j < 255 - 100)
                fade2.setFillColor(sf::Color(j, j, j, 255 - j));
            else 
                fade2.setFillColor(sf::Color(j, j, j, 100));
            timer.restart();
        }

        else if (start_value == 7 && j == 0) // ustawienie do rozjaœniania
        {
            timer.restart();
            i = 255;
            start_value = 8;
        }

        if (start_value < 5) // rysowanie tekstu
            window.draw(text);

        else if (start_value >= 5) // wyœwietlanie mapy z "wybieleniem"
        {
            window.draw(map);
            window.draw(fade2);
            if (start_value == 5)
            {
                timer.restart();
                start_value++;
            }


        }
        
    }

    else if (start_value == 8) // rozjaœnianie obrazu
    {
        if (timer.getElapsedTime().asMilliseconds() >= 10 && i > 0) {
            --i;
            fade.setFillColor(sf::Color(0, 0, 0, i));
            timer.restart();
        }

        else if (i == 0) // koniec scen
            start_value = 0;
    }

    

}