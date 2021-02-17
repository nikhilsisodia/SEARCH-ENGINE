#include <bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<direct.h>
#include<windows.h>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define ALPHABET_SIZE (26)
using namespace std;
multimap<string,string> m;
multimap<string,string>:: iterator itr;
pair <multimap<string,string>::iterator, multimap<string,string  >::iterator> ret;
string prefix = "";
void welcome();
void build();
char loc[20];


void gotoxy (int x, int y);
void frame ();
void frame_fix();
char *date_time ();
void scroll_note();
void flow(char *ch);
void main_menu();

COORD coord = {0, 0};

class date;
box(int x1,int y1,int x2,int y2)
{
   int i;
   for(i=x1;i<=x2;i++)
     {
      gotoxy(i,y1);
      printf("%c",196);
      gotoxy(i,y2);
      printf("%c",196);
     }
   for(i=y1;i<=y2;i++)
     {
      gotoxy(x1,i);
      printf("%c",179);
      gotoxy(x2,i);
      printf("%c",179);
     }
      gotoxy(x1,y1);
      printf("%c",218);
      gotoxy(x1,y2);
      printf("%c",192);
      gotoxy(x2,y1);
      printf("%c",191);
      gotoxy(x2,y2);
      printf("%c",217);
}
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isWordEnd;
};
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}
struct TrieNode *root = getNode();
void insert(struct TrieNode *root,  string key)
{
    struct TrieNode *pCrawl = root;

    for (int level = 0; level < key.length(); level++)
    {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->isWordEnd = true;
}
bool search(struct TrieNode *root, const string key)
{
    int length = key.length();
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < length; level++)
    {
        int index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;
        prefix += key[level];
        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isWordEnd);
}
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}
int pos=14;
void suggestionsRec(struct TrieNode* root, string currPrefix)
{

    if (root->isWordEnd)
    {
        gotoxy(20,pos++);
        cout << currPrefix;
        cout << endl;
    }


    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {

            currPrefix.push_back(97 + i);


            suggestionsRec(root->children[i], currPrefix);
        }
    }
}

int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;

    int level;
    int n = query.length();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        if (!pCrawl->children[index]){
            prefix="";
            return 0;
        }

        pCrawl = pCrawl->children[index];
    }

    bool isWord = (pCrawl->isWordEnd == true);

    bool isLast = isLastNode(pCrawl);

    if (isWord && isLast)
    {
        cout << query << endl;
        prefix="";
        return -1;
    }

    if (!isLast)
    {
        string prefix1 = query;
        suggestionsRec(pCrawl, prefix1);
        prefix="";
        return 1;
    }
}
  void printWords(string str)
  {
      transform(str.begin(), str.end(), str.begin(), ::tolower);
      string word;
      stringstream iss(str);
      while (iss >> word){
          m.insert(make_pair(word,str));
        }
  }
  string Color(int color=7, string Message = ""){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return Message;
}
  void printWords1(string str,string key)
  {
      transform(str.begin(), str.end(), str.begin(), ::tolower);
      string word;
      stringstream iss(str);
      while (iss >> word){
        POINT p;
        if(GetCursorPos(&p)){
          if(99-p.x>word.length()){
          if(word == key){
            cout<<Color(4,word)<<" ";
            Color();
            continue;
          }
          cout<<word<<" ";}
          else{
            cout<<endl;
            gotoxy(20,p.y+1);
          }
        }
      }
        cout<<endl;
  }
  void searchword(){
      system("cls");
    string searcht;
    gotoxy(((115)/2)-7,3);
    cout<<"SSP Search"<<endl;
    gotoxy(20,5);
    cout<<"Search anything from anywhere in the database"<<endl;
    gotoxy(20,7);
    cout<<"Input key to search\t";
    cin>>searcht;
    transform(searcht.begin(), searcht.end(), searcht.begin(), ::tolower);
    if(search(root,searcht)){
      gotoxy(20,9);
      ret = m.equal_range(searcht);
      cout<<Color(2,searcht);
      Color();
      cout <<" is present  in the following files excerpts:\n";
      int i=11 ;
      char c = 124;
      for(itr = ret.first; itr != ret.second; ++itr){
        gotoxy(20,i++);
        cout<<c;
        printWords1(itr->second,itr->first);
      }
    }
    else{
      gotoxy(20,11);
      cout<<"There is no keyword corresponding to your search! Please check the following predictions for search."<<endl;
      int comp = printAutoSuggestions(root,prefix);

      gotoxy(20,pos+2);
      cout<<"Sorry no search result found!";
      pos=12;
    }
    getch();
    main_menu();
  }
  void contribute(){
    system("cls");
    box(15,1,100,25);
    gotoxy(((115)/2)-7,3);
    cout<<"SSP Search"<<endl;
    gotoxy(20,5);
    cout<<"Search anything from anywhere in the database"<<endl;
    gotoxy(20,7);
    cout<<"Enter Contributors Passcode.\t";
    string passcode;
    char ch;
    ch = _getch();
    while(ch != 13){
      passcode.push_back(ch);
      cout << '*';
      ch = _getch();
    }
    if(passcode == "nikhil"){
      gotoxy(20,9);
      cout<<"Welcome";
      system("cls");
      box(15,1,100,25);
      gotoxy(((115)/2)-7,3);
      string line;
      fstream fio;
      cout<<"SSP Search"<<endl;
      gotoxy(20,5);
      cout<<"Search anything from anywhere in the database"<<endl;
      gotoxy(20,7);
      fflush(stdin);
      cout<<"Enter text to be stored in database.\n";
      gotoxy(20,9);
      fio.open("sample1.txt", ios::app|  ios::out | ios::in);
      getline(cin, line);
      fio<<line<<"\n";
      fio.close();
      gotoxy(20,11);
      cout<<"Stored in database.";
      Sleep(1000);
      build();
      main_menu();
    }
    else{
      gotoxy(20,9);
      cout<<"Wrong Passcode!";
      Sleep(1000);
      contribute();
    }
  }

  void build(){
    root = getNode();
    fstream fio;
    string line;
    m.clear();
    fio.open("sample1.txt", ios::out | ios::in);
    fio.seekg(0, ios::beg);

    while (fio) {
        getline(fio, line);
          printWords(line);
    }
    fio.close();
    for (multimap<string,string>::iterator it=m.begin();it!=m.end();++it){
         insert(root,it->first);}
  }



class date
{


	public:
		int aday,amonth,ayear,ahour,amin,asec;
	void date_times()
	{
		SYSTEMTIME t;
 		GetLocalTime(&t);
		aday=t.wDay,amonth=t.wMonth,ayear=t.wYear,ahour=t.wHour,amin=t.wMinute,asec=t.wSecond;

	}
};
void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void frame()
{
	int i,j=109;
	for(i = 0;i<110,j>=0;i++,j--)
	{
		gotoxy(i,3);
		Sleep(10);
		cout<<"_";
		gotoxy(j,26);
		Sleep(10);
		cout<<"_";
	}
	gotoxy(56,2);
	char s[20];
	strcpy(s,date_time());
	cout<<s;

}
void frame_fix()
{
	int i,j=79;
	for(i = 0;i<80,j>=0;i++,j--)
	{
		gotoxy(i,3);
		cout<<"_";
		gotoxy(j,20);
		cout<<"_";
	}
	gotoxy(56,2);
	char s[20];
	strcpy(s,date_time());
	cout<<s;
}
char *date_time()
{
	time_t t;
	time(&t);
	char *loc=ctime(&t);
	return loc;
}
void flow(char *ch)
{
	char *str=ch;
	for(int i=0;i<strlen(str);i++)
	{
		Sleep(20);
		cout<<str[i];
	}

	}

void scroll_note()
{
		system("color FC");
	int j,i,x,y;
	for(i=0;i<27;i++)
	{
		gotoxy(i,13);cout<<" ";
		cout<<"SSP SEARCH ENGINE ";
		Sleep(40);
	}

	for(j=67;j>44;j--)
	{
		gotoxy(j,13);
		cout<<"WELCOMES YOU";cout<<"            ";
		Sleep(40);
	}



	gotoxy(27,13);cout<<"SSP SEARCH ENGINE";
	gotoxy(45,13);cout<<"WELCOMES YOU";
	for(int j=78;j>=0;j--)
	{
		gotoxy(j,20);cout<<"|";
		gotoxy(j,4);cout<<"|";
		Sleep(30);
	}
	Sleep(1000);

}

void main_menu()
{
	system("cls");
	//system("COLOR 2F");
	//frame();

	gotoxy(33,10);
	cout<<"SEARCH FOR ANYTHING IN THE DATABASE";
	gotoxy(20,14);
	cout<<"Please press the following options to continue";
	gotoxy(20,16);
	cout<<"1. Search for Something!"<<endl;
    gotoxy(20,18);
    cout<<"2. Contribute to the database[PRIVATE/INVITE ONLY]"<<endl;

	gotoxy(20,21);

    cout<<"Enter your choice.";
    gotoxy(41,11);

    box(52,20,55,22);

	char op;
	gotoxy(1,21);

	gotoxy(5,2);
	cout<<"SSP SEARCH ENGINE ";

	gotoxy(54,21);cout<<"";
	char ch;
    ch= getch();
    if(ch=='1')
        searchword();
    else if(ch=='2')
        contribute();
    else
        main_menu();
}

int main()
{
    build();
	main_menu();
}
