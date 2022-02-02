#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Window.h"
#include "main.h"
#include <string>
#include <filesystem>
#include <io.h>
#include <fcntl.h>

//Bartosz - menu główne sterowane strzałkami, z podświetleniem wyboru

int main()
{
#define strzalka_up 72
#define strzalka_down 80
#define enter 13
#define escape 27
	_setmode(_fileno(stdout), _O_U16TEXT); //tryb UTF-16
	int k[5] = { 33,0,0,0,0 }, co = 1, klawisz = 0, p = 0, c = 0, j = 0;
	std::wstring opis = L"Gra, w której Twoim zadaniem będzie ucieczka z miasta, które zostało zaatakowane bronią masowego rażenia. Poruszasz się strzałkami lub WSAD, a przez lokacje przechodzisz wciskając Spację.";
	while (p == 0)
	{
		c = 0;
		system("cls"); //opcje zapisane wstringiem w celu wyświetlania polskich znaków(plik zapisany w UTF-16)
		std::wcout << "\x1b[" << k[0] << L"m1. Zacznij nową grę\n";
		std::wcout << "\x1b[" << k[1] << L"m2. Kontynuuj grę\n";
		std::wcout << "\x1b[" << k[2] << L"m3. Wczytaj grę\n";
		std::wcout << "\x1b[" << k[3] << "m4. Opis\n";
		std::wcout << "\x1b[" << k[4] << L"m5. Wyjście\n\x1b[0m";
		c = _getch();
		switch (c)
		{
		case strzalka_up:
			if (k[0] != 0)
				break;
			j--;
			k[j + 1] = 0;
			k[j] = 33;
			break;
		case strzalka_down:
			if (k[4] != 0)
				break;
			j++;
			k[j - 1] = 0;
			k[j] = 33;
			break;
		case enter:
			p = 1;
			for (int i = 0; i < 5; i++)
			{
				if (k[i] == 33)
					co = i + 1;
			}
			break;
		default:
			break;
		}

	}
	p = 0;
	std::string filename;
	switch (co)
	{
	default:
		break;
	case 1: //uruchomienie gry od nowa
		game(1);
		break;
	case 2: //uruchomienie gry od ostatniego dostepnego zapisu
	{
		if (!std::filesystem::is_empty("./Saves/"))
		{
			std::filesystem::path filename = "";
			for (const auto& entry : std::filesystem::directory_iterator("./Saves/")) //iterowanie po plikach
			{

				std::filesystem::path p = entry.path();
				if (filename == "")
					filename = p;
				if (is_regular_file(p) && p.extension() == ".txt")
				{
					if (std::filesystem::last_write_time(p) > std::filesystem::last_write_time(filename)) //sprawdzanie ostatniego zapisu
						filename = p;
				}
			}

			game(0, filename.wstring());
		}
		else
			return main();
		break;
	}
	case 3: //wczytywanie gry - działa tak jak poprzednie menu, ale na punktach skrajnych nastepuje przeskok do początku/końca
	{
		system("cls");
		std::vector<std::wstring> paths;
		for (const auto& entry : std::filesystem::directory_iterator("./Saves/"))
			paths.push_back(entry.path().stem().wstring());

		std::vector<int> l(paths.size(), 0);
		l[0] = 33;
		co = 0, klawisz = 0, p = 0, c = 0, j = 0;
		std::wstring filename;

		std::wcout << L"Wybierz zapis, lub wróć do menu wciskając Esc.\n";

		while (p == 0)
		{
			c = 0;
			system("cls");
			for (int n = 0; n < paths.size(); ++n)
				std::wcout << "\x1b[" << l[n] << L"m" << paths[n] << "\n";
			c = _getch();
			switch (c)
			{
			case strzalka_up:
				l[j] = 0;
				if (j == 0)
					j = paths.size() - 1;
				else
					j--;
				l[j] = 33;
				break;
			case strzalka_down:
				l[j] = 0;
				if (j == paths.size() - 1)
					j = 0;
				else
					j++;
				l[j] = 33;
				break;
			case enter:
				p = 1;
				co = std::distance(l.begin(), std::find(l.begin(), l.end(), 33));
				break;
			case escape:
				return main();
			default:
				break;
			}

		}

		filename = L"./Saves/" + paths[co] + L".txt";

		game(0, filename);
		break;
	}
	case 4: //wyświetlenie opisu
		c = 0;
		system("cls");
		for (int i = 0; i < opis.length(); i++)
		{
			std::wcout << opis[i];
			Sleep(30);
		}
		c = _getch();
		return main();
		break;
	case 5: //wyjście
		std::wcout << "Do zobaczenia :)";
		Sleep(2000);
		return 0;
		break;
	}
	return 0;
}