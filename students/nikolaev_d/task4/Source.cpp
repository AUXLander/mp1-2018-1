#include <iostream>
#include <locale>
#include <ctype.h>
#include <fstream>

struct  SDate
{
	int day;
	int mounth;
	int year;
};
struct Bounds
{
	int min;
	int max;
};
class TTrack
{
#define _CRT_SECURE_NO_WARNINGS
	char* mName;
	char* mAuthor;
	char* mComposer;
	char* mSinger;
	char* mAlbum;
	SDate mDate{ 0,0,0 };
private:
	char* setValue(char *var, char value[])
	{
		if (value != NULL)
			strcpy(var = new char[strlen(value)], value);

		return var;
	}
public:
	TTrack(char name[] = "-", char author[] = "-", char composer[] = "-", char singer[] = "-", char album[] = "-", SDate date = { 0,0,0 })
	{
		mName = setValue(mName, name);
		mAuthor = setValue(mAuthor, author);
		mComposer = setValue(mComposer, composer);
		mSinger = setValue(mSinger, singer);
		mAlbum = setValue(mAlbum, album);

		mDate = date;
	}
	void SetName(char name[])
	{
		for (int i = 0; i < strlen(name); i++)
			if (name[i] == '&')
				name[i] = ' ';
		mName = setValue(mName, name);
	}
	char* GetName()
	{
		return mName;
	}
	void SetAuthor(char author[])
	{
		mAuthor = setValue(mAuthor, author);
	}
	char* GetAuthor()
	{
		return mAuthor;
	}
	void SetComposer(char composer[])
	{
		mComposer = setValue(mComposer, composer);
	}
	char* GetComposer()
	{
		return mComposer;
	}
	void SetSinger(char singer[])
	{
		mSinger = setValue(mSinger, singer);
	}
	char* GetSinger()
	{
		return mSinger;
	}
	void SetAlbum(char album[])
	{
		mAlbum = setValue(mAlbum, album);
	}
	char* GetAlbum()
	{
		return mAlbum;
	}
	void SetDate(SDate date)
	{
		mDate = date;
	}
	SDate GetDate()
	{
		return mDate;
	}
	friend std::ostream& operator<<(std::ostream& os, TTrack &c);
};
class CTList
{
	TTrack* mList;
	int mSize = 0;
private:
	void Output(int i)
	{
		if (i >= 0 && i < mSize)
			std::cout << i << ". " << mList[i] << std::endl;
	}
	void SortPartly(int start, int end, int pos)
	{
		for (int i = start; i < end; i++)
			for (int j = start; j < end; j++)
				if (pos < strlen(mList[i].GetName()) && pos < strlen(mList[j].GetName()))
					if (i != j)
						if (static_cast<int>(tolower(mList[i].GetName()[pos])) < static_cast<int>(tolower(mList[j].GetName()[pos])))
						{
							TTrack temp(mList[i]);
							mList[i] = mList[j];
							mList[j] = temp;
						}
	}
	void SortByName()
	{
		int maxLength = 0;

		for (int i = 0; i < mSize; i++)
			if (strlen(mList[i].GetName()) > maxLength)
				maxLength = strlen(mList[i].GetName());

		char t, c;
		int s;
		SortPartly(0, mSize, 0);
		for (int i = 0; i < maxLength - 1; i++)
		{
			s = 0;
			t = tolower(mList[0].GetName()[i]);
			for (int j = 0; j < mSize; j++)
			{
				bool tr = true;
				for (int k = 0; k < i + 1; k++)
				{
					if (t != (c = tolower(mList[j].GetName()[k])))
					{
						t = c;
						SortPartly(s, j, i + 1);
						s = j;
					}
				}
			}
			if (s == 0)
				SortPartly(s, mSize, i + 1);
		}
	}
public:
	CTList() {}
	void DeleteTrack(int _i)
	{
		if (_i < 0 || _i >= mSize)
			return;

		TTrack* temp;
		temp = new TTrack[mSize - 1];
		for (int i = 0, j = 0; i < mSize; i++)
			if (i == _i)
				j = 1;
			else
				temp[i - j] = mList[i];

		delete[] mList;

		mList = new TTrack[mSize - 1];
		for (int i = 0; i < mSize - 1; i++)
			mList[i] = temp[i];

		mSize--;
		delete[] temp;
		SortByName();
	}
	void AddTrack(char name[] = "-", char author[] = "-", char composer[] = "-", char singer[] = "-", char album[] = "-", SDate date = { 0,0,0 })
	{
		TTrack track(name, author, composer, singer, album, date);
		AddTrackObj(track);
		SortByName();
	}
	void AddTrackObj(TTrack track)
	{
		TTrack* temp;
		temp = new TTrack[mSize];
		for (int i = 0; i < mSize; i++)
			temp[i] = mList[i];

		delete[] mList;

		mList = new TTrack[mSize + 1];
		for (int i = 0; i < mSize; i++)
			mList[i] = temp[i];

		mList[mSize] = track;
		mSize++;
		SortByName();
	}
	void GetBySinger(char *singer)
	{
		for (int i = 0; i < mSize; i++)
			if (strcmp(mList[i].GetSinger(), singer) == 0)
				std::cout << i << ". " << mList[i] << std::endl;
	}
	void GetByComposer(char *composer)
	{
		for (int i = 0; i < mSize; i++)
			if (strcmp(mList[i].GetComposer(), composer) == 0)
				std::cout << i << ". " << mList[i] << std::endl;
	}
	void GetByAuthor(char *author)
	{
		for (int i = 0; i < mSize; i++)
			if (strcmp(mList[i].GetAuthor(), author) == 0)
				std::cout << i << ". " << mList[i] << std::endl;
	}
	void GetList()
	{
		for (int i = 0; i < mSize; i++)
			Output(i);
	}
	int GetSize()
	{
		return mSize;
	}
	void SetName(int i, char name[])
	{
		if (i >= 0 && i < mSize)
		{
			mList[i].SetName(name);
			SortByName();
		}
	}
	void SetAuthor(int i, char author[])
	{
		if (i >= 0 && i < mSize)
			mList[i].SetAuthor(author);
	}
	void SetComposer(int  i, char composer[])
	{
		if (i >= 0 && i < mSize)
			mList[i].SetComposer(composer);
	}
	void SetSinger(int i, char singer[])
	{
		if (i >= 0 && i < mSize)
			mList[i].SetSinger(singer);
	}
	void SetAlbum(int i, char album[])
	{
		if (i >= 0 && i < mSize)
			mList[i].SetAlbum(album);
	}
	void SetDate(int i, SDate date)
	{
		if (i >= 0 && i < mSize)
			mList[i].SetDate(date);
	}
	void SaveToFile(char path[])
	{
		std::ofstream playlist;
		playlist.open(path);
		playlist << mSize << std::endl;
		for (int i = 0; i < mSize; i++)
		{
			SDate t = mList[i].GetDate();
			playlist << mList[i].GetAlbum() << '&' << mList[i].GetAuthor() << '&' << mList[i].GetComposer() << '&' << t.day << '/' << t.mounth << '/' << t.year << '&' << mList[i].GetName() << '&' << mList[i].GetSinger() << std::endl;
		}
		playlist.close();
	}
	void LoadFromFile(char path[])
	{
		char r[300];
		std::ifstream playlist;
		playlist.open(path);
		playlist.getline(r, 300, '\n');
		int size = atoi(r);
		for (int i = 0; i < size; i++)
		{
			char t[300];
			char **data = new char*[6];
			playlist.getline(t, 300, '\n');
			for (int j = 0, s = 0, p = 0; j < strlen(t); j++)
			{
				if (t[j] == '&' || j == strlen(t) - 1)
				{
					data[p] = new char[j - s];
					for (int k = 0; k < j - s + (j == strlen(t) - 1); k++)
						data[p][k] = t[s + k];

					data[p][j - s + (j == strlen(t) - 1)] = '\0';
					s = j + 1;
					p++;
				}
			}
			SDate temp;
			char r[10];
			for (int j = 0, k = 0, p = 0; j < strlen(data[3]); j++)
			{
				if (data[3][j] != '/')
				{
					r[k] = data[3][j];
					k++;
				}
				else
				{
					switch (p)
					{
						case 0:
							temp.day = atoi(r);
							break;
						case 1:
							temp.mounth = atoi(r);
							break;
						case 2:
							temp.year = atoi(r);
							break;
					}
					p++;
					k = 0;
				}
			}
			AddTrack(data[4], data[1], data[2], data[5], data[0], temp);
		}
	}
};
std::ostream& operator<<(std::ostream& os, TTrack &c)
{
	return os << c.mSinger << " - " << c.mName;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	
	
	CTList list;
	//list.LoadFromFile("playlist.txt");

	TTrack track("Never Gonna Give You Up", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	TTrack track2("Whenever You Need Somebody", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });

	list.AddTrackObj(track);
	list.AddTrackObj(track2);
	list.AddTrack("Together Forever", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("It Would Take a Strong Strong Man", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("The Love Has Gone", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("Don't Say Goodbye", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("Slipping Away", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("No More Looking for Love", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("You Move Me", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	list.AddTrack("When I Fall in Love", "Rick Astley", "Rick Astley", "Rick Astley", "Whenever You Need Somebody", { 0,0,1987 });
	
	list.GetList();
	system("pause");
	std::cout << std::endl << "Let's del first" << std::endl << std::endl;
	list.DeleteTrack(0);
	list.GetList();
	system("pause");

	list.SaveToFile("playlist.txt");
	return 0;
}