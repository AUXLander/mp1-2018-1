#include <iostream>
#include <locale>

struct  SDate
{
	char day;
	char mounth;
	int year;
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
	TTrack(char name[] = { '\0' }, char author[] = { '\0' }, char composer[] = { '\0' }, char singer[] = { '\0' }, char album[] = { '\0' }, SDate date = { 0,0,0 })
	{
		mName = setValue(mName, name);
		mAuthor = setValue(mAuthor, author);
		mComposer = setValue(mComposer, composer);
		mSinger = setValue(mSinger, singer);
		mAlbum = setValue(mAlbum, album);

		mDate = date;
	}
	void SetName(char name[] = { '\0' })
	{
		mName = setValue(mName, name);
	}
	char* GetName()
	{
		return mName;
	}
	void SetAuthor(char author[] = { '\0' })
	{
		mAuthor = setValue(mAuthor, author);
	}
	char* GetAuthor()
	{
		return mAuthor;
	}
	void SetComposer(char composer[] = { '\0' })
	{
		mComposer = setValue(mComposer, composer);
	}
	char* GetComposer()
	{
		return mComposer;
	}
	void SetSinger(char singer[] = { '\0' })
	{
		mSinger = setValue(mSinger, singer);
	}
	char* GetSinger()
	{
		return mSinger;
	}
	void SetAlbum(char album[] = { '\0' })
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
public:
	CTList() {}
	void AddTrack(char name[] = { '\0' }, char author[] = { '\0' }, char composer[] = { '\0' }, char singer[] = { '\0' }, char album[] = { '\0' }, SDate date = {0,0,0})
	{
		TTrack track(name, author, composer, singer, album, date);
		AddTrackObj(track);
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
		delete[] temp;
	}
	void GetBySinger(char *singer)
	{
		for (int i = 0; i < mSize; i++)
			if (strcmp(mList[i].GetSinger(), singer) == 0)
				std::cout << mList[i] << std::endl;
	}
	void GetByComposer(char *composer)
	{
		for (int i = 0; i < mSize; i++)
			if (strcmp(mList[i].GetComposer(), composer) == 0)
				std::cout << mList[i] << std::endl;
	}
	void GetByAuthor(char *author)
	{
		for (int i = 0; i < mSize; i++)
			if (strcmp(mList[i].GetAuthor(), author) == 0)
				std::cout << mList[i] << std::endl;
	}
};
std::ostream& operator<<(std::ostream& os, TTrack &c)
{
	return os << c.mSinger << " - " << c.mName;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	TTrack track("умереть", "Azazin Creet", "Azazin Creet", "Azazin Creet", "New");
	TTrack track2("умереть2", "Azazin Creet", "Azazin Creet", "Azazin Creet", "New");
	track.SetName("Миллионер");
	CTList list;

	list.AddTrackObj(track);
	list.AddTrackObj(track2);
	list.AddTrack("умереть3", "Azazin Creet", "Azazin Creet", "Azazin Creet", "New");

	list.GetByAuthor("Azazin Creet");
	return 0;
}