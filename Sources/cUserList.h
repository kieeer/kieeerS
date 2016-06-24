#pragma once
#include "cUser.h"
#include "cTweet.h"
#include "cWord.h"

class cUserList
{
public:
	map<string, cUser*> mapUser;
	int friendshipRecord;
	int totalTweets;

	map<string, cWord> mapWord;

	cUserList();
	~cUserList();

	void loadUserInfo(char* filename);
	void loadFriendInfo(char* filename);
	void loadWordInfo(char* filename);

	void showDataFiles();
	void displayStatistics();
	void TopMost5TweetedWord();
	void TopMost5TweetedUser();
	void findUserWithWords(string str);
	void findFriend(string screenName);
	void deleteWord(string word);
	void deleteUserByWord(string word);
};

