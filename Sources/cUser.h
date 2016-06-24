#pragma once
#include "cTweet.h"

class cUser
{
public:
	string ID;
	string screenName;

	vector<cTweet*> vTweet;
	vector<string> vFriendID;

public:
	cUser();
	~cUser();
};

