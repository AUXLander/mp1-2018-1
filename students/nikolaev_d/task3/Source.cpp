#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <locale>
#include <dos.h>
using namespace std;

//Advansed Console Menu
class ACMenu
{
// Высота пункта меню
#define ITEM_HEIGHT 30
#define ITEM_BORDER 3
#define ITEM_PADDING 4
	int mX = 0; // Menu pos X
	int mY = 0; // Menu pos Y
	int SIZE = 0; // Количество пунктов меню


	char **mNames;
	HWND hwndConsole = FindWindow(L"ConsoleWindowClass", NULL);
	HDC hdcConsole = GetDC(hwndConsole);
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
	CONSOLE_CURSOR_INFO structCursorInfo;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
public:

	ACMenu(int count, char **_Names = {}) : mNames(_Names), SIZE(count)
	{
		TriggerCursor();
	}

	int SelectItem(int selected = 0)
	{
		char c;
		while (true)
		{
			c = _getch();
			if (c == -32)
			{
				switch (c = _getch())
				{
					case 72:
					{
						//UP

						break;
					}
					case 80:
					{
						//DOWN
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
				//ENTER
			}
			Sleep(5);// Сбиваем нагрузку на процессор
		}
	}



	~ACMenu()
	{

		delete[] mNames;
		DeleteObject(hBrushWhite);
		ReleaseDC(hwndConsole, hdcConsole);
	}
	bool DrawItem(int number, bool selected = false)
	{
		int padding = number * (ITEM_PADDING + ITEM_HEIGHT);
		SelectObject(hdcConsole, hBrushWhite);
		Rectangle(hdcConsole, mX, mY + padding, mX + 300, mY + padding + ITEM_HEIGHT);
		SelectObject(hdcConsole, hBrushBlack);
		Rectangle(hdcConsole, mX + ITEM_BORDER, mY + ITEM_BORDER + padding, mX + 300 - ITEM_BORDER, mY + ITEM_HEIGHT - ITEM_BORDER + padding);
		SelectObject(hdcConsole, hBrushWhite);
		RECT rect = {0, 0, 400 ,27};
		LPCWSTR buf = Decode(mNames[number]);
		DrawText(hdcConsole, buf , strlen(mNames[number]), &rect, DT_CENTER);
		return true;
	}
private:
	void TriggerCursor()
	{
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = !structCursorInfo.bVisible;
		SetConsoleCursorInfo(handle, &structCursorInfo);
	}
	LPCWSTR Decode(char *c)
	{
		WCHAR *t = new WCHAR[strlen(c)];
		WCHAR *_t = t;
		delete t; // Чтобы не было утечек памяти
		MultiByteToWideChar(0, 0, c, strlen(c), _t, strlen(c));
		return (LPCWSTR)_t;
	}
};

int GraphInConsole(double * x, double * y, int N, int WIDTH, int HEIGHT, int OTSTUP) {
	int i, l, hr, hh, cY;
	double a, b, Max, Min, kx, ky, HH;
	Max = 0;
	Min = 0;
	a = x[0];
	b = x[N - 1];
	for (i = 0; i < N; i++) {
		if (Max < y[i])Max = y[i];
		else if (Min > y[i])Min = y[i];
	}
	hh = 0; // Направление движние графика hh=0 - вправо (при b>a), hh=WIDTH - влево (при b<a)
	if (b < a)hh = WIDTH;
	hr = 14;// Высота текста в консоли
	HH = Max - Min; // Протяженность графика по оси Y
	if (HH < 0)HH *= -1;
	kx = WIDTH / (b - a); // Для нормировки по оси OX
	if (hh > 0)kx *= -1;
	ky = HEIGHT / HH; // Для нормировки по оси OY

					  /* Для определения на какой позиции находиться курсор */
	HANDLE OutputH = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(OutputH, &csbi);
	cY = csbi.dwCursorPosition.Y;

	for (i = 0; i < HEIGHT / hr; i++) {
		cout << endl;
	}

	/* Ищем окно и берем его под контороль для выолнения операций интеpфейса GDI */
	HWND console = FindWindow(L"ConsoleWindowClass", NULL);
	HDC dc = GetDC(console);

	/* Объявляем три цвета которые нам понадобяться */
	HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hBrushRed = CreateSolidBrush(RGB(250, 0, 0));
	HBRUSH hBrushBlueKing = CreateSolidBrush(RGB(65, 105, 225));

	/* Выделяем память под 20 точек для построения графика по отрезочкам в которых в среднем будет по 9 точек */
	POINT *po;
	po = new POINT[20];
	/* Рисуем окошко и координатные оси*/
	SelectObject(dc, hBrushBlueKing);
	Rectangle(dc, x[0] * kx + OTSTUP + hh, cY*hr + HEIGHT + 5, x[N - 1] * kx + OTSTUP + hh, -HH*ky + cY*hr + 1 + HEIGHT - 5);
	SelectObject(dc, hBrushWhite);
	Rectangle(dc, x[0] * kx + OTSTUP + hh, cY*hr + HEIGHT, x[N - 1] * kx + OTSTUP + hh, -HH*ky + cY*hr + 1 + HEIGHT);
	Rectangle(dc, x[0] * kx + OTSTUP + hh, cY*hr + HEIGHT, x[N - 1] * kx + OTSTUP + hh, -HH*ky + cY*hr + 1 + HEIGHT + Max*ky);
	Rectangle(dc, OTSTUP + hh, cY*hr + HEIGHT, x[N - 1] * kx + OTSTUP + hh, -HH*ky + cY*hr + 1 + HEIGHT + Max*ky);
	Rectangle(dc, OTSTUP + hh, cY*hr + HEIGHT + 2 + Min*ky, x[N - 1] * kx + OTSTUP + hh, -HH*ky + cY*hr + 1 + HEIGHT);

	//Рисуем наш график
	SelectObject(dc, hBrushRed);
	for (l = 0; l < N - N % 9 - 1; l += 9) {
		for (i = 0; i < 10; i++) {
			po[i].x = x[l + i] * kx + OTSTUP + hh;
			po[i].y = (Min - y[l + i])*ky + cY*hr + HEIGHT;
		}
		for (i = 0; i < 10; i++) {
			po[10 + i].x = x[l + 9 - i] * kx + OTSTUP + hh;
			po[10 + i].y = (Min - y[l + 9 - i])*ky + cY*hr + 2 + HEIGHT;
		}
		Polygon(dc, po, 20);
	}

	DeleteObject(hBrushRed);
	DeleteObject(hBrushWhite);
	DeleteObject(hBrushBlueKing);
	ReleaseDC(console, dc);
	return (HEIGHT / hr);//возвращает значение = количество строк занятое графиком
}

double f(double x) { return (x*x - 1.); }


int main()
{
	setlocale(LC_ALL, "Rus");

	char **mNames = new char*[4];
	mNames[0] = "Продолжить";
	mNames[1] = "Сохранить";
	mNames[2] = "Загрузить";
	mNames[3] = "EXIT";

	ACMenu t(4, mNames);

	while (true)
	{
		t.DrawItem(3);
		Sleep(50);
	}
	return 0;
}

