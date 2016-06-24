#include "stdafx.h"
#include "cUserList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cUserList userList;
	userList.loadUserInfo("user.txt");
	userList.loadFriendInfo("friend.txt");
	userList.loadWordInfo("word.txt");
	
	int action;
	cout << "0. Read data files                                        "<<	endl;
	cout << "1. display statistics                                     "<<	endl;
	cout << "2. Top 5 most tweeted words                               "<<	endl;
	cout << "3. Top 5 most tweeted users                               "<<	endl;
	cout << "4. Find users who tweeted a word(e.g., ¡¯¿¬¼¼´ë¡¯)           "<<	endl;
	cout << "5. Find all people who are friends of the above users     "<<	endl;
	cout << "6. Delete all mentions of a word                          "<<	endl;
	cout << "7. Delete all users who mentioned a word                  "<<	endl;
	cout << "8. Find strongly connected components                     "<<	endl;
	cout << "9. Find shortest path from a given user                   "<<	endl;
	cout << "99. Quit                                                  "<<	endl;
	
	
	string inputStr;
	while (true)
	{
		cout << endl;
		cout << "Select Menu : ";
		cin >> action;
		cout << endl;
		switch (action)
		{
		case 0:
			userList.showDataFiles();
			break;
		case 1:
			userList.displayStatistics();
			break;
		case 2:
			userList.TopMost5TweetedWord();
			break;
		case 3:
			userList.TopMost5TweetedUser();
			break;
		case 4:
			cout << "input Word: ";
			cin >> inputStr;
			userList.findUserWithWords(inputStr);
			break;
		case 5:
			cout << "input ScreenName: ";
			cin >> inputStr;
			userList.findFriend(inputStr);
			break;
		case 6:
			cout << "input Word: ";
			cin >> inputStr;
			userList.deleteWord(inputStr);
			break;
		case 7:
			cout << "input Word: ";
			cin >> inputStr;
			userList.deleteUserByWord(inputStr);
			break;
		case 8:
			break;
		case 9:
			break;
		case 99:
			return 0;
		}

	}

	return 0;
}

