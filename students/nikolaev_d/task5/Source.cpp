#include <cstring>;
#include <iostream>;
#include <string>;
#include <vector>;
#include <locale>

#define PC (*pCenter)

using namespace std;

class Date {
	int day;
	int mounth;
	int year;

public:
	Date(int d = 0,int m = 0, int y = 0) {
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
	friend ostream& operator<<(ostream& os, Date &c);
};
ostream& operator<<(ostream& os, Date &c)
{
	return os << c.day << '.' << c.mounth << '.' << c.year;;
}

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
	Date currentTime;
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
public:
	ProcCenter(Date curdat):currentTime(curdat){}
	void Update(Date newTime = { 1,1,1970 }) {
		if (newTime < currentTime) {
			if(newTime == Date(1,1,1970))
				newTime = currentTime + Date(1, 2, 0);
			else
				newTime = currentTime + newTime;
		}
		int cMonth;
		for (int i = 0; i < UsersData.size(); i++) {
			if (UsersData[i].DepositEnd < newTime) {
				cMonth = currentTime.GetDifferenceOfMounth(UsersData[i].DepositEnd);
				UsersData[i].DepositBalance = 0;
				UsersData[i].DepositEnd = Date(1, 1, 0);
				UsersData[i].DepositStart = Date(1, 1, 0);
			}
			else
				cMonth = currentTime.GetDifferenceOfMounth(newTime);

			UsersData[i].UserBalance += UsersData[i].DepositPerc / 12 * UsersData[i].DepositBalance * cMonth;
		}
		currentTime = newTime;
	}
	short AddUser(string UN, string UP, int UB = 0, int DB = 0, Date DS = { 1, 1, 0 }, Date DE = { 1, 1, 0 }, float DP = 0)
	{
		if (UN.length() > 3)
			if (UP.length() > 3)
				UsersData.push_back(BankUser{ IDsCounter, UN, EncryptData(UP, IDsCounter), UB, DB, DS, DE, DP });
			else
				return -2;
		else
			return -1;
		return IDsCounter++;
	}
	bool UserAccess(short ID, string Pass) {
		if (ID >= IDsCounter || UsersData[ID].UserPass != EncryptData(Pass, ID))
			return false;
		return true;
	}
	int GetBalance(short ID, string Pass)
	{
		if (UserAccess(ID, Pass))
			return UsersData[ID].UserBalance;
		else return -1;
	}
	int GetDepositBalance(short ID, string Pass) {
		if (UserAccess(ID, Pass))
			return UsersData[ID].DepositBalance;
		else return -1;
	}
	bool AddBalance(short ID, string Pass, int value) {
		if (UserAccess(ID, Pass))
			if (UsersData[ID].UserBalance - UsersData[ID].DepositBalance >= -value)
			{
				UsersData[ID].UserBalance += value;
				return true;
			}
		return false;
	}
	bool SetDepositBalance(short ID, string Pass, int value) {
		if (UserAccess(ID, Pass)) {
			if (value >= 0)
				UsersData[ID].DepositBalance = value;
			else
				return false;
			return true;
		}
		else return false;
	}
	string GetName(short ID, string Pass) {
		if (UserAccess(ID, Pass))
			return UsersData[ID].UserName;
		else return "Access Denied!";
	}
	float GetPercent(short ID, string Pass) {
		if (UserAccess(ID, Pass))
			return UsersData[ID].DepositPerc;
		else return -1;
	}
	Date GetDepositStart(short ID, string Pass)
	{
		if (UserAccess(ID, Pass))
			return UsersData[ID].DepositStart;
		else return -1;
	}
	Date GetDepositEnd(short ID, string Pass)
	{
		if (UserAccess(ID, Pass))
			return UsersData[ID].DepositEnd;
		else return -1;
	}
	bool SetDepositStart(short ID, string Pass, Date newDate) {
		if (UserAccess(ID, Pass))
		{
			UsersData[ID].DepositStart = newDate;
			return true;
		}
		else return false;
	}
	bool SetDepositEnd(short ID, string Pass, Date newDate) {
		if (UserAccess(ID, Pass))
		{
			UsersData[ID].DepositEnd = newDate;
			return true;
		}
		else return false;
	}
};

class Deposit {
	const string BankName = "000 RasmanBank";
	ProcCenter *pCenter;
	string sPassword;
	short ID = -1;
public:
	Deposit(ProcCenter *Center):pCenter(Center){}
	bool LogIn(short _id, string password)
	{
		if ((*pCenter).UserAccess(_id, password)) {
			sPassword = password;
			ID = _id;
			return true;
		}
		return false;
	}
	void LogOut()
	{
		sPassword = " ";
		ID = -1;
	}
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
	short AddNewUser(string UN, string UP, int UB = 0, int DB = 0, Date DS = { 1, 1, 0 }, Date DE = { 1, 1, 0 }, float DP = 0) {
		if (DE > Date(1, 1, 0) && DP == 0) 
			DP = GetPercentPerYear(DB, DS, DE);
		return (*pCenter).AddUser(UN, UP, UB, DB, DS, DE, DP);
	}
	int GetUserBalance(short _id = 0, string Pass = " ") {
		if (ID < 0)
			return PC.GetBalance(_id, Pass);
		else
			return PC.GetBalance(ID, sPassword);
	}
	Date GetDepositStart(short _id = 0, string Pass = " ") {
		if (ID < 0)
			return PC.GetDepositStart(_id, Pass);
		else
			return PC.GetDepositStart(ID, sPassword);
	}
	Date GetDepositEnd(short _id = 0, string Pass = " ") {
		if (ID < 0)
			return PC.GetDepositEnd(_id, Pass);
		else
			return PC.GetDepositEnd(ID, sPassword);
	}
	float GetPercent(short _id = 0, string Pass = " ") {
		if (ID < 0)
			return PC.GetPercent(_id, Pass);
		else
			return PC.GetPercent(ID, sPassword);
	}
	bool TakeMoney(int money, short _id = 0, string Pass = " ") {
		if (ID < 0)
			return PC.AddBalance(_id, Pass, -money);
		else
			return PC.AddBalance(ID, sPassword, -money);
	}
};



void main() {
	setlocale(LC_ALL, "Russian");
	ProcCenter *pCenter = new ProcCenter(Date(30,12,1999));
	Deposit dep(pCenter);
	int answer;
	short ID = dep.AddNewUser("Александр Сысоев", "qwerty", 1000000, 1000000, { 1,1,2000 }, { 1,1,2005 });
	
	if (!dep.LogIn(ID, "Qwerty")) {
		cout << "Попробуем другой пароль!" << endl;
		dep.LogIn(ID, "qwerty");
	}
	cout << dep.GetUserBalance() << " руб." << endl << "Сколько у меня денежек!" << endl << endl << "Прошло 3 года..." << endl << endl ;

	PC.Update(Date(2, 1, 2001));

	cout << dep.GetUserBalance() << " руб." << endl << "Сколько у меня денежек! Сниму пару тыщ" << endl;
	
	while(!dep.TakeMoney(81000)) {
		cout << "Депозит же еще не закрыт, а сумма списания больше начисленных процентов! Подождем еще пару лет!" << endl;
		PC.Update(Date(1, 1, 2));
	}
	cout << "Наконец-то я снял деньги!" << endl;
	cout << "Теперь у меня в кармане 81000, а на счету " << dep.GetUserBalance() << endl;
	cout << "Оформляйте депозиты в 000 RasmanBank!" << endl;
	system("pause");
}