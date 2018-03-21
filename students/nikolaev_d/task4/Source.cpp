#include <iostream>



class TTrack
{
#define _CRT_SECURE_NO_WARNINGS
	struct  SDate
	{
		char day;
		char mounth;
		int year;
	};
	char* mName;
	char* mAuthor;
	char* mComposer;
	char* mSinger;
	char* mAlbum;
	SDate mDate{ 0,0,0 };
private:
	void setValue(char *var, char value[])
	{
		var = new char[strlen(value)];
		strcpy(var, value);
	}
public:
	TTrack(char name[] = {'\0'}, char author[] = { '\0' }, char composer[] = { '\0' }, char singer[] = { '\0' }, char album[] = { '\0' }, SDate date = { 0,0,0 })
	{
		setValue(mName, name);
		setValue(mAuthor, author);
		setValue(mComposer, composer);
		setValue(mSinger, singer);
		setValue(mAlbum, album);

		mDate = date;
	}
	void SetName(char name[] = { '\0' })
	{
		setValue(mName, name);
	}
	void SetAuthor(char author[] = { '\0' })
	{
		setValue(mAuthor, author);
	}
	void SetComposer(char composer[] = { '\0' })
	{
		setValue(mComposer, composer);
	}
	void SetSinger(char singer[] = { '\0' })
	{
		setValue(mSinger, singer);
	}
	void SetAlbum(char album[] = { '\0' })
	{
		setValue(mAlbum, album);
	}
	void SetDate(SDate date)
	{
		mDate = date;
	}
};
class CTList
{

public:
	CTList();
	~CTList();

};
int main()
{
	TTrack track("умереть", "Azazin Creet", "Azazin Creet", "Azazin Creet", "New");

	track.SetName("Миллионер");

	return 0;
}