#include <iostream> 
#include <cstdarg> 

using namespace std;
class TVector
{
#define MAXSIZE 20 
	//Количество измерений 
	int SIZE = 3;
	int mArray[MAXSIZE];
private:
	void initial()
	{
		for (int i = 0; i < MAXSIZE; mArray[i++] = 0);
	}
public:
	TVector()
	{
		initial();
	}
	TVector(int count, ...)
	{
		initial();
		SIZE = count;
		va_list argList;
		va_start(argList, count);
		for (int i = 0; i < SIZE; mArray[i++] = va_arg(argList, int));
		va_end(argList);
	}
	TVector(int n[])
	{
		initial();
		SIZE = n[0];
		for (int i = 0; i < SIZE; mArray[i++] = n[i + 1]);
	}
	TVector operator+(const TVector &c)
	{
		if (SIZE != c.SIZE)
			throw "Trobles with sizes";
		//"Trobles with sizes"; 
		TVector tSumm;
		tSumm.SetSize(SIZE);
		for (int i = 0; i < SIZE; i++)
			tSumm.Set(i, mArray[i] + c.mArray[i]);
		return tSumm;
	}
	TVector operator-(const TVector &c)
	{
		if (SIZE != c.SIZE)
			throw "Trobles with sizes";
		//"Trobles with sizes"; 
		TVector tSumm;
		tSumm.SetSize(SIZE);
		for (int i = 0; i < SIZE; i++)
			tSumm.Set(i, mArray[i] - c.mArray[i]);
		return tSumm;
	}
	void SetSize(int value)
	{
		SIZE = value;
	}
	void Set(int X, int Value)
	{
		mArray[X] = Value;
	}
	int Get(int X)
	{
		return mArray[X];
	}
	int GetSize()
	{
		return SIZE;
	}
	int Scalar(TVector b)
	{
		if (SIZE != b.SIZE)
			throw "Trobles with sizes";

		int tResult = 0;
		for (int i = 0; i < SIZE; i++)
		{
			tResult = tResult + mArray[i] * b.mArray[i];
		}
		return tResult;
	}

	int LengthInt()
	{
		return sqrt(Scalar((*this)));
	}
	double LengthDouble()
	{
		return sqrt(Scalar((*this)));
	}
	int LengthSQR()
	{
		return Scalar((*this));
	}
	friend ostream& operator<<(ostream& os, TVector &c);
};
ostream& operator<<(ostream& os, TVector &c)
{
	os << '(';
	for (int i = 0; i < c.SIZE; i++)
	{
		os << c.mArray[i];
		if (i < c.SIZE - 1)
			os << ',';
	}
	os << ')';
	return os;
}

int main()
{
	TVector p({ 3, 1, 1, 1 });
	TVector n(3, 3, 3, 3);
	TVector t(3, 3, 1, 4);

	cout << t << " + " << p << " = " << t + p << endl;
	cout << t << " - " << n << " = " << t - n << endl;
	cout << t << " * " << n << " = " << t.Scalar(n) << endl;

	system("pause");
	return 0;
}