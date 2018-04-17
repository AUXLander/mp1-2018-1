#include <cstring>;
#include <iostream>;
#include <string>;
#include <vector>;

using namespace std;

class Date {
	unsigned int day;
	unsigned int mounth;
	int year;

public:
	Date(unsigned int d = 0, unsigned int m = 0, int y = 0) {
		m -= 1;
		d -= 1;
		year = y + m / 12;
		mounth = m % 12 + d / GetDaysByMounth(m % 12);
		day = d % GetDaysByMounth(mounth);
	}
	int GetDifferenceOfMounth(Date end) {
		Date tmp(end - *this);
		return tmp.mounth + tmp.year * 12;
	}
	int GetDaysByMounth(int m) {
		m %= 12;
		switch (m) {
			case 0: case 2: case 4: case 6: case 7: case 9: case 11:
				return 31;

			case 1:
				return 28;

			default:
				return 30;
		}
	}
	Date operator+(Date t) {
		int y = t.year + year;
		unsigned int m = t.mounth + mounth;
		unsigned int d = t.day + day;
		unsigned int cM;

		do {
			if (m >= 12)
				y += m / 12;

			m %= 12;

			cM = GetDaysByMounth(m);

			if (d > cM) {
				m += d / cM;
				d %= cM;
			}

		} while (m >= 12);

		return Date(d + 1, m + 1, y);
	}
	Date operator-(Date t) {
		int y = year - t.year;
		unsigned int m = mounth;
		unsigned int d = day;

		if (t.day > day) {
			m--;
			d += GetDaysByMounth(m);
		}
		d -= t.day;

		if (t.mounth > mounth) {
			y--;
			m += 12;
		}
		m -= t.mounth;

		return Date(d + 1, m + 1, y);
	}
	bool operator>(Date t) {
		Date tmp(*this - t);
		if (tmp.year > 0)
			return true;
		else if (tmp.year == 0)
			if (tmp.mounth > 0)
				return true;
			else if (tmp.mounth == 0)
				if (tmp.day > 0)
					return true;

		return false;
	}
	bool operator<(Date t) {
		Date tmp(*this - t);
		if (tmp.year < 0)
			return true;
		else if (tmp.year == 0)
			if (tmp.mounth < 0)
				return true;
			else if (tmp.mounth == 0)
				if (tmp.day < 0)
					return true;

		return false;
	}
	bool operator>=(Date t) {
		Date tmp(*this - t);
		if (tmp.year > 0)
			return true;
		else if (tmp.year == 0)
			if (tmp.mounth > 0)
				return true;
			else if (tmp.mounth == 0)
				if (tmp.day >= 0)
					return true;

		return false;
	}
	bool operator<=(Date t) {
		Date tmp(*this - t);
		if (tmp.year < 0)
			return true;
		else if (tmp.year == 0)
			if (tmp.mounth < 0)
				return true;
			else if (tmp.mounth == 0)
				if (tmp.day <= 0)
					return true;

		return false;
	}
	bool operator==(Date t) {
		Date tmp(*this - t);
		if (tmp.year == 0)
			if (tmp.mounth == 0)
				if (tmp.day == 0)
					return true;

		return false;
	}
};

class Deposit:ProcCenter {



public:
	Deposit() {}

	float GetPercentPerYear(int balance, Date start, Date end)
	{
		float percent = 0;

		if (balance < 100000)
			percent += 0.009;
		if (balance >= 100000)
			percent += 0.009;
		if (balance >= 500000)
			percent += 0.009;
		if (balance >= 1000000)
			percent += 0.009;

		switch (start.GetDifferenceOfMounth(end)) {
			case 36: percent += 0.009;
			case 24: percent += 0.009;
			case 12: percent += 0.009;
			case 6: percent += 0.009;
			case 3: percent += 0.009;
		}

		return percent;
	}
};

class ProcCenter {
	struct BankUser {
		short UserID;
		string UserName;
		string UserPass;
		int UserBalance;
		int DepositBalance;
		Date DepositStart;
		Date DepositEnd;
		float DepositPerc;
	};

	vector<BankUser> UsersData;
	short IDsCounter = 0;

private:
	string EncryptData(string data, int seed) {
		string Encrypted = "";

		for (int i = 0; i < data.length(); i++)
			Encrypted += to_string((int)(data.at(i) >> 1) + seed % 32);

		Encrypted += to_string(seed) + Encrypted.at(seed % Encrypted.length());

		data = "";

		for (int i = 0; i < Encrypted.length(); i++)
			data += Encrypted.at(i % Encrypted.length()) << 3;

		return data;
	}
protected:
	ProcCenter() { }
	short AddUser(string UN, string UP, int UB = 0, int DB = 0, Date DS = { 1, 1, 0 }, Date DE = { 1, 1, 0 }, float DP = 0)
	{
		if (UN.length() > 3)
			if (UP.length() > 3)
				UsersData.push_back(BankUser{ IDsCounter, UN, EncryptData(UP, 2), UB, DB, DS, DE, DP });
			else
				return -2;
		else
			return -1;
		return IDsCounter++;
	}
	int GetBalance(short ID, string Pass)
	{
		if (ID >= IDsCounter)
			return -1;

		if (UsersData[ID].UserPass != EncryptData(Pass, 2)) {

		}
	}
};

void main() {
	Date s(17, 4, 2018);
	Date e(17, 10, 2018);

	Deposit dep();
	cout << dep.GetPercentPerYear(100000, s, e);

	system("pause");
}