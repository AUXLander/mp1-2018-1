#include <iostream>
#include <locale>

using namespace std;

/*********************************************************************************************

 =============================================================================================
|      ___  ________   _________  _______   ________  _______   ________                      |
|     |\  \|\   ___  \|\___   ___\\  ___ \ |\   ____\|\  ___ \ |\   __  \                     |
|     \ \  \ \  \\ \  \|___ \  \_\ \   __/|\ \  \___|\ \   __/|\ \  \|\  \                    |
|      \ \  \ \  \\ \  \   \ \  \ \ \  \_|/_\ \  \  __\ \  \_|/_\ \   _  _\                   |
|       \ \  \ \  \\ \  \   \ \  \ \ \  \_|\ \ \  \|\  \ \  \_|\ \ \  \\  \|                  |
|        \ \__\ \__\\ \__\   \ \__\ \ \_______\ \_______\ \_______\ \__\\ _\                  |
|         \|__|\|__| \|__|    \|__|  \|_______|\|_______|\|_______|\|__|\|__|                 |
|                                                                                             |
|  ___  ___  ________   ___       ___  _____ ______   ___  _________  _______   ________      |
| |\  \|\  \|\   ___  \|\  \     |\  \|\   _ \  _   \|\  \|\___   ___\\  ___ \ |\   ___ \     |
| \ \  \\\  \ \  \\ \  \ \  \    \ \  \ \  \\\__\ \  \ \  \|___ \  \_\ \   __/|\ \  \_|\ \    |
|  \ \  \\\  \ \  \\ \  \ \  \    \ \  \ \  \\|__| \  \ \  \   \ \  \ \ \  \_|/_\ \  \ \\ \   |
|   \ \  \\\  \ \  \\ \  \ \  \____\ \  \ \  \    \ \  \ \  \   \ \  \ \ \  \_|\ \ \  \_\\ \  |
|    \ \_______\ \__\\ \__\ \_______\ \__\ \__\    \ \__\ \__\   \ \__\ \ \_______\ \_______\ |
|     \|_______|\|__| \|__|\|_______|\|__|\|__|     \|__|\|__|    \|__|  \|_______|\|_______| |
|                                                                                             |
 =============================================================================================
| Integer Unlimited                                                                           |
|                                                                                             |
| ����� TUInt ������������ �� ���� ������������ ����� ��� ������, ��������� �����������       |
| ������� �������������� �������� � �������� �������������� �������. ����� ���������������    |
| ����� �������������.                                                                        |
|                                                                                             |
| ������� ����� ���������� 20 ��������, ��� ������� 2^64 ��������.                            |
| � ������ ������� ����� ���������� 50 ��������, ��� ������� ����� 2^163 ��������             |
|                                                                                             |
| ����� �������� ���������� ��������, ��������� �������� �������� ��������� SIZE              |
|                                                                                             |
 =============================================================================================


 *********************************************************************************************/


class TUInt {

#define SIZE 50
	char dArray[SIZE];
	bool isNegative = false;

private:
	void initial()
	{
		for (char i = 0; i < SIZE; i++)
			dArray[i] = '0';
	}
	//����������� ������ � �����
	int atoi(char t)
	{
		switch (t)
		{
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;

		default: return 0;
		}
	}
	//����������� ����� � ������
	char untoi(int t)
	{
		switch (t)
		{
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';

		default: return '0';
		}
	}
	void LevelUp()
	{
		bool originNegative = isNegative;
		for (int i = SIZE; i > 0; i--)
			dArray[i] = dArray[i - 1];
		dArray[0] = '0';
		isNegative = originNegative;
	}
public:

	TUInt()
	{
		initial();
	}

	TUInt(char c)
	{
		initial();
		dArray[0] = untoi(atoi(c));
	}

	TUInt(char c[])
	{
		int sLength = strlen(c);
		initial();

		if (sLength <= SIZE)
		{
			for (int i = 0, j = sLength - 1; i < SIZE && c[j] != '\0'; i++, j--)
			{
				dArray[i] = c[j];
				if (c[j] == '-')
				{
					isNegative = true;
					dArray[i] = '0';
				}
				
			}
		}
	}

	TUInt(int c)
	{
		initial();

		if (c < 0)
		{
			isNegative = true;
			c *= -1;
		}
			

		for (int i = 0; i < SIZE; i++)
		{
			dArray[i] = untoi(c % 10);
			c /= 10;
		}
	}

	TUInt(long c)
	{
		initial();

		if (c < 0)
		{
			isNegative = true;
			c *= -1;
		}

		for (int i = 0; i < SIZE; i++)
		{
			dArray[i] = untoi(c % 10);
			c /= 10;
		}
	}

	TUInt(long long c)
	{
		initial();

		if (c < 0)
		{
			isNegative = true;
			c *= -1;
		}

		for (int i = 0; i < SIZE; i++)
		{
			dArray[i] = untoi(c % 10);
			c /= 10;
		}
	}

	TUInt operator+(const TUInt &c)
	{
		TUInt tResult;
		TUInt tTerm_1(*this);
		TUInt tTerm_2(c);
		int tSumm = 0; // ��������� �����
		int tRemndr; // ��������� �������
		bool NegativeResult = false;
		if (isNegative || c.isNegative)
		{
			if (tTerm_1.isNegative && tTerm_2 > 0 && Abs(tTerm_1)  > Abs(tTerm_2))
			{
				NegativeResult = true;
				tTerm_1.isNegative = false;
				tTerm_2.isNegative = true;
			}
			else if (tTerm_1 > 0 && tTerm_2.isNegative && Abs(tTerm_1) < Abs(tTerm_2))
			{
				NegativeResult = true;
				tTerm_1.isNegative = true;
				tTerm_2.isNegative = false;
			}
			else if (tTerm_1.isNegative && tTerm_2.isNegative)
			{
				NegativeResult = true;
				tTerm_1.isNegative = false;
				tTerm_2.isNegative = false;
			}
		}
		for (int i = 0; i < SIZE; i++)
		{
			// ���������� ����� �������� ������� � �����������
			tSumm = (tTerm_1.isNegative ? -1 : 1)*atoi(tTerm_1.dArray[i]) + (tTerm_2.isNegative ? -1 : 1)*atoi(tTerm_2.dArray[i]) + tSumm;
			tRemndr = tSumm % 10; // ������� �� ���� - ��������� �����
			if (tRemndr < 0)//��� ��������
			{
				tRemndr += 10;
				tSumm -= 10;
			}
			tResult.dArray[i] = untoi(tRemndr);
			tSumm /= 10;
		}
		tResult.isNegative = NegativeResult;
		return tResult;
	}
	TUInt operator-(const TUInt &c)
	{
		TUInt tResult(c);
		tResult.isNegative = !tResult.isNegative;
		return ((*this) + tResult);
	}
	TUInt operator*(const TUInt &c)
	{
		TUInt tSumm;
		TUInt tResult;
		int tRemndr_1 = 0; //�������
		int tRemndr_2 = 0; //������� �� ������ ����

		for (int j = 0; j < SIZE; j++)
		{
			for (int i = 0; i < SIZE - j; i++)
			{
				if (c.dArray[j] == '0') // ���������� 0 ��� ���������
					continue;

				tRemndr_2 = atoi(dArray[i]) * atoi(c.dArray[j]); // ������������ ���� �����
				tSumm.dArray[i + j] = untoi((tRemndr_2 += tRemndr_1) % 10); // ���������� ����� � ������
				tRemndr_1 = tRemndr_2 / 10; // �������� 
			}
			tResult = tResult + tSumm; // ��������� ������������� ������������
			tSumm = "0"; // �������� ��
		}
		tResult.isNegative = (isNegative && !c.isNegative) || (!isNegative && c.isNegative); // ���������� ����
		return tResult;
	}

	bool operator==(const TUInt &c)
	{
		for (int i = 0; i < SIZE; i++)
			if (dArray[i] != c.dArray[i])
				return false;
		return true;
	}
	bool operator<(const TUInt &c)
	{
		for (int i = SIZE; i >= 0; i--)
		{
			//���� ������� ������� ������ , ���������� true
			if (atoi(dArray[i]) < atoi(c.dArray[i]))
				if (*this == (TUInt)c)
					return (isNegative ? true : false);
				else
					return (isNegative ? false : true);
			//���� ������� ������� ������ , ���������� false
			if (atoi(dArray[i]) > atoi(c.dArray[i]))
				return (isNegative ? true : false);
		}
		return (isNegative ? true : false);
	}
	bool operator>(const TUInt &c)
	{
		for (int i = SIZE; i >= 0; i--)
		{
			//���� ������� ������� ������ , ���������� true
			if (atoi(dArray[i]) > atoi(c.dArray[i]))
				if (*this == (TUInt)c)
					return (isNegative ? true : false);
				else
					return (isNegative ? false : true);
			//���� ������� ������� ������ , ���������� false
			if (atoi(dArray[i]) < atoi(c.dArray[i]))
				return (isNegative ? true : false);
		}
		return (isNegative ? true : false);
	}
	bool operator<=(const TUInt &c)
	{
		for (int i = SIZE; i >= 0; i--)
		{
			//���� ������� ������� ������ , ���������� true
			if (atoi(dArray[i]) < atoi(c.dArray[i]))
				return (isNegative ? false : true);
			//���� ������� ������� ������ , ���������� false
			if (atoi(dArray[i]) > atoi(c.dArray[i]))
				return (isNegative ? true : false);
		}
		return (isNegative ? false : true);
	}
	bool operator>=(const TUInt &c)
	{
		for (int i = SIZE; i >= 0; i--)
		{
			//���� ������� ������� ������ , ���������� true
			if (atoi(dArray[i]) > atoi(c.dArray[i]))
				return (isNegative ? false : true);
			//���� ������� ������� ������ , ���������� false
			if (atoi(dArray[i]) < atoi(c.dArray[i]))
				return (isNegative ? true : false);
		}
		return (isNegative ? false : true);
	}

	TUInt operator/(const TUInt &c)
	{
		bool started = false;
		int i = SIZE;
		TUInt tResult;
		TUInt dividendPart;//������������� ������������
		//�������� � �������� �����
		TUInt divider(Abs(c));// ��������
		TUInt dividend(Abs(*this));// �������

		if (divider == (TUInt)0)
		{
			throw "DEVIDE BY ZERO";
			return 0;
		}
		do
		{
			while (dividendPart < divider && i-- > 0)
			{
				dividendPart.LevelUp();
				dividendPart.dArray[0] = dividend.dArray[i];

				int y = 1;

				if (dividend.dArray[i] != '0')
					started = true;

				if (dividendPart < divider && started && i > 0)
					tResult.LevelUp();
			}
			while (dividendPart >= divider)
			{
				dividendPart = dividendPart - divider;
				tResult = tResult + "1";
			}
			if (i <= 0)
				break;

			tResult.LevelUp();
		} while (i > 0);

		//���������� ����
		tResult.isNegative = (isNegative && !c.isNegative) || (!isNegative && c.isNegative);
		return tResult;
	}
	TUInt operator%(const TUInt &c)
	{
		return (*this) - ((*this) / c) * c;
	}

	TUInt operator++()
	{
		return (*this) + 1;
	}
	//���������� ������
	TUInt Length()
	{
		int i = 0;
		for (i = SIZE - 1; i >= 0; i--)
		{
			if (dArray[i] != '0')
				break;
		}
		return i + 1;
	}

	//���������� � �������
	TUInt Power(int c)
	{
		if (c < 0)
			//����� ����� ������ ����� 0
			return 0;

		TUInt tResult(1);
		for (; c > 0; c--)
			tResult = tResult * (*this);
		return tResult;
	}
	//������
	TUInt Abs(const TUInt &c)
	{
		TUInt tResult(c);
		for (int i = 0; i < SIZE; i++)
			if (tResult.dArray[i] == '-')
				tResult.dArray[i] = '0';
		tResult.isNegative = false;
		return tResult;
	}
	friend ostream& operator<<(ostream& os, TUInt &c);
	//friend ostream& operator>>(ostream& os, TUInt &c);
};
ostream& operator<<(ostream& os, TUInt &c)
{
	bool trigger = false;
	if (c.isNegative && !(c == (TUInt)0))
		os << '-';
	for (int i = 0; i < SIZE; i++)
	{
		if (c.dArray[SIZE - 1 - i] != '0')
			trigger = true;

		if (trigger)
			if (c.dArray[SIZE - 1 - i] != '-')
				os << c.dArray[SIZE - 1 - i];
	}
	if (!trigger)
		os << 0;
	return os;
}

int main() {
	setlocale(LC_ALL, "Russian");

	TUInt i = "-25";
	TUInt j = "-5";

	cout << "������� �����: " << endl;
	cout << i << " + " << j << " = " << i + j << endl;
	cout << i << " - " << j << " = " << i - j << endl;
	cout << i << " * " << j << " = " << i * j << endl;
	cout << i << " / " << j << " = " << i / j << endl;
	cout << i << " % " << j << " = " << i % j << endl;
	cout << endl;

	i = "297328756328056327889021782927819427412";
	j = "9841194";

	cout << "������� �����: " << endl;
	cout << i << " + " << j << " = " << i + j << endl;
	cout << i << " - " << j << " = " << i - j << endl;
	cout << i << " * " << j << " = " << i * j << endl;
	cout << i << " / " << j << " = " << i / j << endl;
	cout << i << " % " << j << " = " << i % j << endl;
	cout << endl;

	i = "10";
	j = 10;

	cout << "��������� �����: " << endl;
	cout << i << " < " << j << " = " << (i < j ? "true" : "false") << endl;
	cout << i << " <= " << j << " = " << (i <= j ? "true" : "false") << endl;
	cout << i << " > " << j << " = " << (i > j ? "true" : "false") << endl;
	cout << i << " >= " << j << " = " << (i >= j ? "true" : "false") << endl;
	cout << endl;

	i = "101";
	j = "10";

	cout << i << " < " << j << " = " << (i < j ? "true" : "false") << endl;
	cout << i << " <= " << j << " = " << (i <= j ? "true" : "false") << endl;
	cout << i << " > " << j << " = " << (i > j ? "true" : "false") << endl;
	cout << i << " >= " << j << " = " << (i >= j ? "true" : "false") << endl;
	cout << endl;

	i = 2;

	cout << "������� 2-��: " << endl;
	cout << i << " ^ " << -1 << " = " << i.Power(-1) << endl;
	cout << i << " ^ " << 0 << " = " << i.Power(0) << endl;
	cout << i << " ^ " << 1 << " = " << i.Power(1) << endl;
	cout << i << " ^ " << 2 << " = " << i.Power(2) << endl;
	cout << i << " ^ " << 3 << " = " << i.Power(3) << endl;
	cout << "..." << endl;
	cout << i << " ^ " << 32 << " = " << (j = i.Power(32)) << endl;
	cout << "���-�� ������: " << j.Length() << endl;
	cout << "..." << endl;
	cout << i << " ^ " << 64 << " = " << (j = i.Power(64)) << endl;
	cout << "���-�� ������: " << j.Length() << endl;
	cout << "..." << endl;
	cout << i << " ^ " << 163 << " = " << (j = i.Power(163)) << endl;
	cout << "���-�� ������: " << j.Length() << endl;

	system("pause");
	return 0;
}