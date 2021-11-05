#include <iostream>
#include <conio.h>

using namespace std;

void showTableChar(char** tab)
{
	for (int i = 0; i < 9; i++)
	{
		cout << "|  ";
		for (int j = 0; j < 8; j++)
		{
			switch (tab[i][j])
			{
				case ' ':
				{
					cout << tab[i][j] << "  |  ";
					break;
				}
				case '*':
				{
					cout << "\x1B[31mO\033[0m  |  ";
					break;
				}
				case '@':
				{
					cout << "\x1B[33mO\033[0m  |  ";
					break;
				}
				default:
				{
					cout << tab[i][j] << "  |  ";
					break;
				}
			}
		}
		cout << endl << endl;
	}
	cout << endl;
}

bool leftEndOfTable(int y)
{
	if (y == 0)
	{
		return true;
	}
	return false;
}

bool rightEndOfTable(int y)
{
	if (7 == y)
	{
		return true;
	}
	return false;
}

void placeCircle(char** tab, int x, int player)
{
	for (int i = 8; i > 0; i--)
	{
		if (tab[i][x] == ' ')
		{
			if (player == 1)
			{
				tab[i][x] = '*';
				break;
			}
			if (player == 2)
			{
				tab[i][x] = '@';
				break;
			}
		}
	}
}

bool win(char** tab)
{
	for (int i = 8; i > 0; i--)
	{
		for (int j = 0; j < 6; j++)
		{
			if (tab[i][j] != ' ')
			{
				char circle = tab[i][j];
				if (tab[i][j + 1] == circle && tab[i][j + 2] == circle && tab[i][j + 3] == circle)
					return true;
			}
		}
	}
	for (int i = 8; i > 3; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j] != ' ')
			{
				char circle = tab[i][j];
				if (tab[i - 1][j] == circle && tab[i - 2][j] == circle && tab[i - 3][j] == circle)
					return true;
			}
		}
	}
	for (int i = 8; i > 3; i--)
	{
		for (int j = 0; j < 5; j++)
		{
			if (tab[i][j] != ' ')
			{
				char circle = tab[i][j];
				if (tab[i - 1][j + 1] == circle && tab[i - 2][j + 2] == circle && tab[i - 3][j + 3] == circle)
					return true;
			}
		}
	}
	for (int i = 1; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (tab[i][j] != ' ')
			{
				char circle = tab[i][j];
				if (tab[i + 1][j + 1] == circle && tab[i + 2][j + 2] == circle && tab[i + 3][j + 3] == circle)
					return true;
			}
		}
	}
	return false;
}

int main()
{
	char** tabForUser = new char* [9];
	for (int i = 0; i < 9; ++i)
	{
		tabForUser[i] = new char[8];
		for (int j = 0; j < 8; ++j)
		{
			tabForUser[i][j] = ' ';
		}
	}
	int* coordinates = new int[2];
	coordinates[0] = 0;
	coordinates[1] = 0;
	char move = 0, prechar = ' ';
	int player = 1, circles = 0;
	tabForUser[0][0] = '*';
	system("stty raw");
	while (!win(tabForUser) && circles < 64)
	{
		system("CLS");
		if (player == 1)
		{
			cout << "\\\\\\\\\\\|||||||||||||GRACZ  1|||||||||||||///////////" << endl;
		}
		if (player == 2)
		{
			cout << "\\\\\\\\\\\|||||||||||||GRACZ  2|||||||||||||///////////" << endl;
		}
		showTableChar(tabForUser);
		cout << "X to twoja pozycja na planszy\nUzywaj AD do poruszania sie po planszy\nA - w lewo\nD - w prawo\nNacisnij ENTER aby postawic kolko\n";
		move = _getch();
		switch (move)
		{
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
				if (player == 1)
					tabForUser[coordinates[0]][coordinates[1]] = '*';
				if (player == 2)
					tabForUser[coordinates[0]][coordinates[1]] = '@';
				break;
			}
		}
		case 'd':
		{
			if (rightEndOfTable(coordinates[1]))
			{
				break;
			}
			else
			{
				tabForUser[coordinates[0]][coordinates[1]] = prechar;
				++coordinates[1];
				prechar = tabForUser[coordinates[0]][coordinates[1]];
				if (player == 1)
					tabForUser[coordinates[0]][coordinates[1]] = '*';
				if (player == 2)
					tabForUser[coordinates[0]][coordinates[1]] = '@';
				break;
			}
		}
		default:
		{
			break;
		}
		}
		if ((int)move == 13 && tabForUser[1][coordinates[1]] == ' ')
		{
			placeCircle(tabForUser, coordinates[1], player);
			if (player == 1)
			{
				player = 2;
				tabForUser[coordinates[0]][coordinates[1]] = '@';
				circles++;
			}
			else if (player == 2)
			{
				player = 1;
				tabForUser[coordinates[0]][coordinates[1]] = '*';
				circles++;
			}
		}
	}
	system("CLS");
	if (circles < 64)
	{
		if (player == 1)
		{
			cout << "\\\\\\\\\\\||||||||||WYGRAL GRACZ  1||||||||||///////////" << endl;
			showTableChar(tabForUser);
		}
		if (player == 2)
		{
		cout << "\\\\\\\\\\\||||||||||WYGRAL GRACZ  2||||||||||///////////" << endl;
			showTableChar(tabForUser);
		}
	}
	else
	{
		cout << "\\\\\\\\\\\|||||||||||||| REMIS ||||||||||||||///////////" << endl;
		showTableChar(tabForUser);
	}
	return 0;
}