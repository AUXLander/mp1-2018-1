#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <locale>
#include <dos.h>
#include <assert.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "gdiplus.lib")

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
	char **mNames;
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
		TriggerCursor();
	}

	int SelectItem(int selected = 0)
	{
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
						break;
					}
					case 80:
					{
						//DOWN
						++mSelected;
						mSelected = mSelected % SIZE;
						break;
					}
					case 75:
					{
						//LEFT
						break;
					}
					case 77:
					{
						//RIGHT
					}
				}
			}
			else if (c == 13)
			{
				return mSelected;
			}
			Sleep(5);// Сбиваем нагрузку на процессор
		}
	}



	~ACMenu()
	{
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
			SelectObject(hdcConsole, (selected ? hBrushBlack : hBrushWhite));
			Rectangle(hdcConsole, mX, mY + padding, mX + ITEM_WIDTH, mY + padding + ITEM_HEIGHT);
			SelectObject(hdcConsole, (selected ? hBrushWhite : hBrushBlack));
			Rectangle(hdcConsole, mX + ITEM_BORDER, mY + ITEM_BORDER + padding, mX + ITEM_WIDTH - ITEM_BORDER, mY + ITEM_HEIGHT - ITEM_BORDER + padding);
			SetBkMode(hdcConsole, TRANSPARENT);
			if(!selected)
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
	void TriggerCursor()
	{
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = !structCursorInfo.bVisible;
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
	mNames[0] = "CONTINUE";
	mNames[1] = "SAVE";
	mNames[2] = "LOAD";
	mNames[3] = "EXIT";

	ACMenu t(4, mNames);
	t.SelectItem(0);
	

	system("pause");
	return 0;
}

