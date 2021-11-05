#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <fcntl.h>
#include <io.h>

using namespace std;

void showTableChar(char** tab,  int height, int width)
{
	wcout << L"╔";
	for (int i = 0; i < width*3; i++)
	{
		wcout << L"═";
	}
	wcout << L"╗\n";
	for (int i = 0; i < height; ++i)
	{
		wcout << L"║";
		for (int j = 0; j < width; j++)
		{
			switch (tab[i][j])
			{
			case '*':
			{
				wcout << tab[i][j] << "  ";
				break;
			}
			case ' ':
			{
				wcout << tab[i][j] << "  ";
				break;
			}
			case '1':
			{
				wcout << L"\x1B[31m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '2':
			{
				wcout << L"\x1B[32m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '3':
			{
				wcout << L"\x1B[33m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '4':
			{
				wcout << L"\x1B[34m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '5':
			{
				wcout << L"\x1B[36m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '6':
			{
				wcout << L"\x1B[35m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '7':
			{
				wcout << L"\x1B[35m" << tab[i][j] << "\033[0m  ";
				break;
			}
			case '8':
			{
				wcout << L"\x1B[35m" << tab[i][j] << "\033[0m  ";
				break;
			}
			default:
			{
				wcout << tab[i][j] << "  ";
				break;
			}
			}
		}
		wcout << L"║" << endl;
	}
	wcout << L"╚"; 
	for (int i = 0; i < width*3; i++)
	{
		wcout << L"═";
	}
	wcout << L"╝";
	wcout << endl;
}

void showTableBool(bool** tab, int height, int width)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			wcout << tab[i][j] << L"  ";
		}
		wcout << endl;
	}
}

bool** createTable(int height, int width, int bombs)
{
	bool** tab = new bool* [height];
	for (int i = 0; i < height; ++i)
	{
		tab[i] = new bool[width];
		for (int j = 0; j < width; ++j)
		{
			tab[i][j] = false;
		}
	}
	int bombsPlaced = 0;
	int x;
	int y; 
	while (bombsPlaced < bombs)
	{
		x = rand() % height;
		y = rand() % width;
		if (tab[x][y] == false)
		{
			tab[x][y] = true;
			++bombsPlaced;
		}
	}
	return tab;
}

bool upEndOfTable(int x)
{
	if (x == 0)
	{
		return true;
	}
	return false;
}

bool downEndOfTable(int height,int x)
{
	if (height - 1 == x )
	{
		return true;
	}
	return false;
}

bool leftEndOfTable(int y)
{
	if (y == 0)
	{
		return true;
	}
	return false;
}

bool rightEndOfTable(int width, int y)
{
	if (width - 1 == y )
	{
		return true;
	}
	return false;
}

int bombsAround(bool** bombsMap, int height, int width, int x, int y)
{
	int numberOfBombs = 0;
	int maxH = 1;
	int i = -1;
	if (upEndOfTable(x))
		++i;
	if (downEndOfTable(height, x))
		--maxH;
	while(i <= maxH)
	{
		int j = -1;
		int maxW = 1;
		if (leftEndOfTable(y))
			++j;
		if (rightEndOfTable(width, y))
			--maxW;
		while (j <= maxW)
		{
			if (bombsMap[x + i][y + j] == true)
				++numberOfBombs;
			++j;
		}
		++i;
	}
	return numberOfBombs;
}

bool win(char** tab, bool** bombsMap, int bombs, int height, int width)
{
	int correctFlags = 0;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++)
		{
			if (tab[i][j] == 'F' && bombsMap)
			{
				correctFlags++;
			}
		}
	}
	if (correctFlags == bombs)
	{
		return true;
	}
	return false;
}

void reveal(bool** bombsMap, char** tabForUser, int height, int width, int x, int y)
{
	if (bombsAround(bombsMap, height, width, x, y) == 0)
	{
		tabForUser[x][y] = ' ';
		if(!upEndOfTable(x) && tabForUser[x - 1][y] != ' ')
				reveal(bombsMap, tabForUser, height, width, x - 1, y);
		if(!downEndOfTable(height, x) && tabForUser[x + 1][y] != ' ')
				reveal(bombsMap, tabForUser, height, width, x + 1, y);
		if(!leftEndOfTable(y) && tabForUser[x][y - 1] != ' ')
				reveal(bombsMap, tabForUser, height, width, x, y -1);
		if(!rightEndOfTable(width, y) && tabForUser[x ][y + 1] != ' ')
				reveal(bombsMap, tabForUser, height, width, x, y + 1);
	}
	else
	{
		tabForUser[x][y] = 48 + bombsAround(bombsMap, height, width, x, y);
	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	int height, width, bombs;
	wcout << L"Ile pol szerokosci ma miec twoja tabela: ";
	cin >> height;
	wcout << L"Ile pol wysokosci ma miec twoja tabela: ";
	cin >> width;
	char** tabForUser = new char*[height];
	for (int i = 0; i < height; ++i)
	{
		tabForUser[i] = new char[width];
		for (int j = 0; j < width; ++j)
		{
			tabForUser[i][j] = '*';
		}
	}
	wcout << L"Ile bomb ma byc umieszczonych na planszy: ";
	cin >> bombs;
	bool** bombsMap = createTable(height, width, bombs);
	int* coordinates = new int[2];
	coordinates[0] = 0;
	coordinates[1] = 0;
	char move = 0, prechar = '*';
	tabForUser[0][0] = 'X';
	system("stty raw");
	while (!(bombsMap[coordinates[0]][coordinates[1]] && (int)move == 13 && tabForUser[coordinates[0]][coordinates[1]] != 'F') && !win(tabForUser, bombsMap, bombs, height, width))
	{
		system("CLS");
		showTableChar(tabForUser, height, width);
		wcout << L"X to twoja pozycja na planszy\nUzywaj WASD do poruszania sie po planszy\nW - do gory\nA - w lewo\nS - w dol\nD - w prawo\nUzyj klawisza ENTER aby odslonic pole\nUzyj SPACJI aby postawic flage\n";
		move = _getch();
		switch (move)
		{
			case 'w':
			{
				if (upEndOfTable(coordinates[0]))
				{
					break;
				}
				else
				{
					tabForUser[coordinates[0]][coordinates[1]] = prechar;
					--coordinates[0];
					prechar = tabForUser[coordinates[0]][coordinates[1]];
					tabForUser[coordinates[0]][coordinates[1]] = 'X';
					break;
				}
			}
			case 'a':
			{
				if (leftEndOfTable(coordinates[1]))
				{
					break;
				}
				else
				{
					tabForUser[coordinates[0]][coordinates[1]] = prechar;
					--coordinates[1];
					prechar = tabForUser[coordinates[0]][coordinates[1]];
					tabForUser[coordinates[0]][coordinates[1]] = 'X';
					break;
				}
			}
			case 's':
			{
				if (downEndOfTable(height, coordinates[0]))
				{
					break;
				}
				else
				{
					tabForUser[coordinates[0]][coordinates[1]] = prechar;
					++coordinates[0];
					prechar = tabForUser[coordinates[0]][coordinates[1]];
					tabForUser[coordinates[0]][coordinates[1]] = 'X';
					break;
				}
			}
			case 'd':
			{
				if (rightEndOfTable(width, coordinates[1]))
				{
					break;
				}
				else
				{
					tabForUser[coordinates[0]][coordinates[1]] = prechar;
					++coordinates[1];
					prechar = tabForUser[coordinates[0]][coordinates[1]];
					tabForUser[coordinates[0]][coordinates[1]] = 'X';
					break;
				}
			}
			default:
			{
				break;
			}
		}
		if ((int)move == 13 && !bombsMap[coordinates[0]][coordinates[1]] && tabForUser[coordinates[0]][coordinates[1]] != 'F')
		{
			reveal(bombsMap, tabForUser , height, width, coordinates[0], coordinates[1]);
			prechar = tabForUser[coordinates[0]][coordinates[1]];
		}
		if ((int)move == 32)
		{
			if (tabForUser[coordinates[0]][coordinates[1]] != 'F')
			{
				tabForUser[coordinates[0]][coordinates[1]] = 'F';
				prechar = 'F';
			}
			else
			{
				tabForUser[coordinates[0]][coordinates[1]] = '*';
				prechar = '*';
			}
		}
	}
	system("CLS");
	if (win(tabForUser, bombsMap, bombs, height, width))
	{
		wcout << L"  *♥*´*。.♥¯*♥。♥。*¨`*♥´*。❄¨`*♥。♥。*`*\n";
		wcout << L"*╔════════════              ════════════╗*\n";
		wcout << L"*♥*❄¯*♥♥♫♪♩ W Y G R A L E S !  ♫♫♪♥¯*♥❄\n";
		wcout << L"*╚════════════              ════════════╝*\n";
		wcout << L"  *♥*´*。.♥¯*♥。♥。*¨`*♥´*。♥¨`*♥。♥。*`*\n\n\n\n\n";
		wcout << L"      ▄▀▄     ▄▀▄\n";
		wcout << L"     ▄█░░▀▀▀▀▀░░█▄\n";
		wcout << L" ▄▄  █░░░░░░░░░░░█  ▄▄\n";
		wcout << L"█▄▄█ █░░▀░░┬░░▀░░█ █▄▄█\n\n\n\n";
	}
	else
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; j++)
			{
				if (bombsMap[i][j])
				{
					tabForUser[i][j] = 'X';
				}
			}
		}
		showTableChar(tabForUser, height, width);
		wcout << L"\n\n             P R Z E G R A L E S . . .\n";
		wcout << L"  ___\n";
		wcout << L" (._.)           T R O C H E    S Z K O D A\n";
		wcout << L" < | >\n";
		wcout << L"_ / \\_\n\n\n";
	}
	return 0;
}