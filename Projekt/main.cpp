#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Window.h"
#include "main.h"
#include <string>

int main()
{
#define strzalka_up 72
#define strzalka_down 80
#define enter 13
	int k[4] = { 33,0,0,0 }, co = 1, klawisz = 0, p = 0, c = 0, j = 0;
	std::string opis = "Gra";
	while (p == 0)
	{
		c = 0;
		system("cls");
		std::cout << "\x1b[" << k[0] << "m1. Zacznij gre\n";
		std::cout << "\x1b[" << k[1] << "m2. Kontynuuj gre\n";
		std::cout << "\x1b[" << k[2] << "m3. Opis\n\x1b[0m";
		std::cout << "\x1b[" << k[3] << "m4. Wyjscie\n\x1b[0m";
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
			if (k[3] != 0)
				break;
			j++;
			k[j - 1] = 0;
			k[j] = 33;
			break;
		case enter:
			p = 1;
			for (int i = 0; i < 4; i++)
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
		c = 0;
		system("cls");
		for (int i = 0; i < opis.length(); i++)
		{
			std::cout << opis[i];
			Sleep(30);
		}
		c = _getch();
		return main();
		break;
	case 4:
		std::cout << "Do zobaczenia :)";
		Sleep(2000);
		return 0;
		break;
	}
	return 0;
}
