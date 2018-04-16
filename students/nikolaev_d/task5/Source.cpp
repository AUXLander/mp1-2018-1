#include <cstring>;
#include <iostream>;
#include <string>;
#include <vector>;

using namespace std;

class Deposit{

};
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
class ProcCenter {
	struct BankUser {
		short UserID;
		string UserName;
		string UserPass;
		int UserBalance;
		int DepositStart;
		int DepositTime;// В месяцах
		float DepositPerc;
	};

	vector<BankUser> UsersData;
	short IDsCounter = 0;

	

protected:
	ProcCenter() { }
	int GetPerc(int StartBalance, int Time) {

		return 0;
	}
	short AddUser(string UN, string UP, int UB = 0, int DS = 0, int DT = 0) {
	/*	if (UN.length() > 3)
			if (UP.length() > 3)
				UsersData.push_back(BankUser{ IDsCounter, UN, EncryptData(UP, 2), UB, DS, DT, GetPerc(DS,DT) });
			else
				return -2;
		else
			return -1;
		return IDsCounter++;
		*/
	}
	int GetBalance(short ID, string Pass) {
		if (ID >= IDsCounter)
			return -1;

		if (UsersData[ID].UserPass != EncryptData(Pass, 2)) {

		}
	}
};

void main() {
	cout << EncryptData("string", 45);
}