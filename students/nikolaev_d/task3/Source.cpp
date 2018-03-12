#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

//Advansed Console Menu
class ACMenu
{
	// Высота пункта меню
	int ITEM_HEIGHT = 30;
	int ITEM_WIDTH = 100;
	int ITEM_BORDER = 3;
	int ITEM_PADDING = 4;
	int mX = 0; // Menu pos X
	int mY = 0; // Menu pos Y
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
	ACMenu(int count = 0, char* _Names[] = {})
	{
		SIZE = count;
		mNames = new char*[SIZE];

		for (int i = 0; i < SIZE; i++)
			mNames[i] = _Names[i];

		TriggerCursor(false);
	}
	void SetPos(int x, int y)
	{
		mX = x;
		mY = y;
	}
	bool SetSize(int _Size)
	{
		//Чтобы не было ошибок
		if (_Size > SIZE)
			return false;

		SIZE = _Size;
		return true;
		
	}
	void SetDrawingSize(int IH = 30, int IW = 100, int IB = 3, int IP = 4 )
	{
		ITEM_HEIGHT = ABS(IH);
		ITEM_WIDTH = ABS(IW);
		ITEM_BORDER = ABS(IB);
		ITEM_PADDING = ABS(IP);
	}
	bool SetItem(int id, char* _Name)
	{
		if (id >= SIZE)
			return false;
		mNames[id] = _Name;
		return true;
	}
	void SetItems(int count, char* _Names[])
	{
		delete[] mNames;
		SIZE = count;
		mNames = new char*[SIZE];

		for (int i = 0; i < SIZE; i++)
			mNames[i] = _Names[i];

		TriggerCursor(false);
	}
	int GetSize()
	{
		return SIZE;
	}
	int GetLastId()
	{
		return LastSelected;
	}
	char* GetLastName()
	{
		return mNames[LastSelected];
	}
	void Close()
	{
		ClearConsole();
	}
	int SelectItem(int selected = 0)
	{
		char c;
		mSelected = selected;
		for (int i = 0; i < 3; i++)// 3 попытки на перерисовку меню
		{
			ClearConsole();
			while (DrawMenu(mSelected))
			{
				c = _getch();
				if (c == -32)
				{
					switch (c = _getch())
					{
						case 72://UP
						{
							--mSelected;
							mSelected = mSelected % SIZE;
							if (mSelected < 0)
								mSelected += SIZE;
							break;
						}
						case 80://DOWN
						{
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
		return -1;
	}
	~ACMenu()
	{
		delete[] mNames;
		TriggerCursor(true);
		DeleteObject(hBrushBlack);
		DeleteObject(hBrushWhite);
		ReleaseDC(hwndConsole, hdcConsole);
	}

	private:
	int ABS(int t)
	{
		return t < 0 ? t *= -1 : t;
	}
	bool DrawMenu(int selected = 0)
	{
		bool tResult = true;

		for (int i = 0; i < SIZE; i++)
			if (!DrawItem(i, selected == i))
				tResult = false;

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
		DWORD written;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(handle, &csbi))
		{
			DWORD nChars = csbi.dwSize.X * csbi.dwSize.Y;
			FillConsoleOutputCharacter(handle, ' ', nChars, COORD{ 0,0 }, &written);
			FillConsoleOutputAttribute(handle, csbi.wAttributes, nChars, COORD{ 0,0 }, &written);
		}
		SetConsoleCursorPosition(handle, COORD{ 0,0 });
	}
};

int main()
{
	ACMenu t;
	t.SetPos(100, 200);

	while (true)
	{
		char *mNames[4] = { "CONTINUE", "SAVE", "LOAD", "EXIT" };
		t.SetItems(4, mNames);
		t.SetDrawingSize(30, 100);

		switch (t.SelectItem())
		{
			case 0:
				std::cout << "You are playing in some game for example" << std::endl;
				system("pause");
				continue;

			case 3:
				t.Close();
				return 0;

			default:
				t.SetDrawingSize(30, 200);
				mNames[0] = "FILE <CryptoWorld.exe>";
				mNames[1] = "FILE <DarkNetStarter.exe>";
				t.SetItems(2, mNames);
				t.SelectItem();
				continue;
		}
	}
}
