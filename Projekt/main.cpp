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

int main()
{
#define strzalka_up 72
#define strzalka_down 80
#define enter 13
#define escape 27
	_setmode(_fileno(stdout), _O_U16TEXT);
	int k[5] = { 33,0,0,0,0 }, co = 1, klawisz = 0, p = 0, c = 0, j = 0;
	std::string opis = "Gra";
	while (p == 0)
	{
		c = 0;
		system("cls");
		std::wcout << "\x1b[" << k[0] << L"m1. Zacznij nową grę\n";
		std::wcout << "\x1b[" << k[1] << L"m2. Kontynuuj grę\n";
		std::wcout << "\x1b[" << k[2] << L"m3. Wczytaj grę\n";
		std::wcout << "\x1b[" << k[3] << "m4. Opis\n\x1b[0m";
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
	case 1:
		game(1);
		break;
	case 2:
		game(0);
		break;
	case 3:
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
				if (l[0] != 0)
					break;
				j--;
				l[j + 1] = 0;
				l[j] = 33;
				break;
			case strzalka_down:
				if (l[l.size()-1] != 0)
					break;
				j++;
				l[j - 1] = 0;
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
	case 4:
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
	case 5:
		std::wcout << "Do zobaczenia :)";
		Sleep(2000);
		return 0;
		break;
	}
	return 0;
}