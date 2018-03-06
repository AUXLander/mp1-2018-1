#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <locale>
#include <dos.h>

//Advansed Console Menu
class ACMenu
{
	// Высота пункта меню
#define ITEM_HEIGHT 30
#define ITEM_WIDTH 100
#define ITEM_BORDER 3
#define ITEM_PADDING 4
	int mX = 50; // Menu pos X
	int mY = 50; // Menu pos Y
	int SIZE = 0; // Количество пунктов меню
	int mSelected = 0; // На чем внимание
	int LastSelected = 0; // Что было выбрано
	char **mNames; // Пункты меню

	HWND hwndConsole = FindWindow(L"ConsoleWindowClass", NULL);
	HDC hdcConsole = GetDC(hwndConsole);
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
	CONSOLE_CURSOR_INFO structCursorInfo;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
public:

	ACMenu(int count, char **_Names = {}) : mNames(_Names), SIZE(count)
	{
		TriggerCursor(false);
	}
	ACMenu operator()(int count, char **_Names)
	{
		mNames = _Names;
		SIZE = count;
		return true;
	}
	void Close()
	{
		ClearConsole();
	}
	int SelectItem(int selected = 0)
	{
		ClearConsole();
		mSelected = selected;
		char c;
		while (DrawMenu(mSelected))
		{
			c = _getch();
			if (c == -32)
			{
				switch (c = _getch())
				{
					case 72:
					{
						//UP
						--mSelected;
						mSelected = mSelected % SIZE;
						if (mSelected < 0)
							mSelected += SIZE;
						break;
					}
					case 80:
					{
						//DOWN
						++mSelected;
						mSelected = mSelected % SIZE;
						break;
					}
				}
			}
			else if (c == 13)
			{
				ClearConsole();
				LastSelected = mSelected;
				return mSelected;
			}
			Sleep(5);// Сбиваем нагрузку на процессор
		}
	}
	~ACMenu()
	{
		TriggerCursor(true);
		delete[] mNames;
		DeleteObject(hBrushBlack);
		DeleteObject(hBrushWhite);
		ReleaseDC(hwndConsole, hdcConsole);
	}


private:
	bool DrawMenu(int selected = 0)
	{
		bool tResult = true;
		for (int i = 0; i < SIZE; i++)
			if (!DrawItem(i, selected == i)) tResult = false;;
		return tResult;
	}
	bool DrawItem(int number, bool selected = false)
	{
		try
		{
			int padding = number * (ITEM_PADDING + ITEM_HEIGHT);
			if (selected)
				SelectObject(hdcConsole, hBrushWhite);
			else
				SelectObject(hdcConsole, hBrushBlack);

			Rectangle(hdcConsole, mX - 2, mY + padding - 2, mX + ITEM_WIDTH + 2, mY + padding + ITEM_HEIGHT + 2);
			SelectObject(hdcConsole, selected ? hBrushBlack : hBrushWhite);
			Rectangle(hdcConsole, mX, mY + padding, mX + ITEM_WIDTH, mY + padding + ITEM_HEIGHT);
			SelectObject(hdcConsole, (selected ? hBrushWhite : hBrushBlack));
			Rectangle(hdcConsole, mX + ITEM_BORDER, mY + ITEM_BORDER + padding, mX + ITEM_WIDTH - ITEM_BORDER, mY + ITEM_HEIGHT - ITEM_BORDER + padding);
			SetBkMode(hdcConsole, TRANSPARENT);
			if (!selected)
				SetTextColor(hdcConsole, RGB(255, 255, 255));
			else
				SetTextColor(hdcConsole, RGB(0, 0, 0));

			RECT rect = { mX + ITEM_BORDER + 4 , mY + ITEM_BORDER + padding + 4,  mX + ITEM_WIDTH - ITEM_BORDER + 4,  mY + ITEM_HEIGHT - ITEM_BORDER + padding + 4 };
			DrawTextA(hdcConsole, mNames[number], strlen(mNames[number]) + 1, &rect, DT_CENTER);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	void TriggerCursor(bool t)
	{
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = t;
		SetConsoleCursorInfo(handle, &structCursorInfo);
	}
	void ClearConsole()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD coord = { 0, 0 };
		DWORD written;

		if (GetConsoleScreenBufferInfo(handle, &csbi))
		{
			DWORD nChars = csbi.dwSize.X * csbi.dwSize.Y;

			FillConsoleOutputCharacter(handle, ' ', nChars, coord, &written);
			FillConsoleOutputAttribute(handle, csbi.wAttributes, nChars, coord, &written);
		}
		SetConsoleCursorPosition(handle, coord);
	}
};

int main()
{
	setlocale(LC_ALL, "Rus");

	char **mNames = new char*[4];
	ACMenu t(4, mNames);
sel:
	t(4, mNames);
	mNames[0] = "CONTINUE";
	mNames[1] = "SAVE";
	mNames[2] = "LOAD";
	mNames[3] = "EXIT";
	
	switch (t.SelectItem())
	{
		case 0:
		{
			t.Close();
			std::cout << "U r plaing the game" << std::endl;
			break;
		}
		case 1:
		{
			mNames[0] = "FILE 1";
			mNames[1] = "FILE 2";
			t(2, mNames);
			t.SelectItem();
			goto sel;
			break;
		}
		case 2:
		{
			mNames[0] = "FILE 1";
			mNames[1] = "FILE 2";
			t(2, mNames);
			t.SelectItem();
			goto sel;
			break;
		}
		case 3:
		{
			t.Close();
			return 0;
		}
	}


	system("pause");
	return 0;
}

