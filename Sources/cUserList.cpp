#include "stdafx.h"
#include "cUserList.h"


cUserList::cUserList() : friendshipRecord(0)
{
}


cUserList::~cUserList()
{
	for (auto iter = mapUser.begin(); iter != mapUser.end();)
	{
		delete iter->second;
		iter = mapUser.erase(iter);
	}
}

void cUserList::loadUserInfo(char* filename)
{
	cout << "loading User Info..." << endl;

	FILE* fp;
	fopen_s(&fp, "user.txt", "r");

	cUser* pUser = NULL;
	char buffer[1024];

	while (!feof(fp))
	{
		pUser = new cUser;

		fgets(buffer, 1024, fp);
		if (!strcmp(buffer, "\n"))
		{
			delete pUser;
			break;
		}
		strtok(buffer, "\n");
		pUser->ID = buffer;

		fgets(buffer, 1024, fp);

		fgets(buffer, 1024, fp);
		strtok(buffer, "\n");
		pUser->screenName = buffer;

		mapUser.insert(make_pair(pUser->ID, pUser));
		fgets(buffer, 1024, fp);
	}
}

void cUserList::loadFriendInfo(char* filename)
{
	cout << "loading Friend Info..." << endl;

	FILE* fp;
	fopen_s(&fp, "friend.txt", "r");

	char buffer[128];
	char buffer2[128];

	while (!feof(fp))
	{
		fgets(buffer, 128, fp);
		strtok(buffer, "\n");
		fgets(buffer2, 128, fp);
		strtok(buffer2, "\n");

		if (!strcmp(buffer, "\n"))
		{
			break;
		}

		mapUser[buffer]->vFriendID.push_back(buffer2);
		mapUser[buffer2]->vFriendID.push_back(buffer);
		
		friendshipRecord++;

		fgets(buffer, 128, fp);
	}
}

void cUserList::loadWordInfo(char* filename)
{
	cout << "loading word Info..." << endl;

	FILE* fp;
	fopen_s(&fp, "word.txt", "r");

	char buffer[128];
	char tempBuffer[128];
	char buffer2[1024];

	cTweet* pTweet = NULL;

	while (!feof(fp))
	{
		fgets(buffer, 128, fp);
		fgets(tempBuffer, 128, fp);
		fgets(buffer2, 1024, fp);

		strtok(buffer, "\n");
		strtok(buffer2, "\n");
		
		if (pTweet == NULL || pTweet->date != tempBuffer)
		{
			pTweet = new cTweet;
			pTweet->date = tempBuffer;
			pTweet->str.push_back(buffer2);
			mapUser[buffer]->vTweet.push_back(pTweet);
		}
		else
		{
			pTweet->str.push_back(buffer2);
		}

		auto iter = mapWord.find(buffer2);
		if (iter != mapWord.end())
		{
			iter->second.sID.insert(buffer);
		}
		else
		{
			cWord word;
			word.sID.insert(buffer);
			mapWord.insert(make_pair(buffer2, word));
		}

		fgets(tempBuffer, 128, fp);
	}

	totalTweets = 0;
	for (auto iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		totalTweets += iter->second->vTweet.size();
	}

	cout << "load Fininshed" << endl << endl;
}

void cUserList::showDataFiles()
{
	cout << "Total Users : " << mapUser.size() << endl;
	cout << "Total Friendship Records : " << friendshipRecord << endl;

	totalTweets = 0;
	for (auto iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		totalTweets += iter->second->vTweet.size();
	}

	cout << "Total tweets : " << totalTweets << endl;
}

void cUserList::displayStatistics()
{
	float avgFriend = friendshipRecord * 2 / (float)mapUser.size();
	int minFriend = 10000;
	int maxFriend = 0;

	totalTweets = 0;
	for (auto iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		totalTweets += iter->second->vTweet.size();
	}

	float avgTweets = totalTweets / (float)mapUser.size();
	int minTweets = 10000;
	int maxTweets = 0;

	for (auto iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		if (iter->second->vFriendID.size() < minFriend)
		{
			minFriend = iter->second->vFriendID.size();
		}
		if (iter->second->vFriendID.size() > maxFriend)
		{
			maxFriend = iter->second->vFriendID.size();
		}
		if (iter->second->vTweet.size() < minTweets)
		{
			minTweets = iter->second->vTweet.size();
		}
		if (iter->second->vTweet.size() > maxTweets)
		{
			maxTweets = iter->second->vTweet.size();
		}

	}

	cout << "Average Number of Friends : " << avgFriend << endl;
	cout << "Minimum Friends : " << minFriend << endl;
	cout << "Maximum Friends : " << maxFriend << endl << endl;

	cout << "Average Tweets per user : " << avgTweets << endl;
	cout << "Minimum Tweets per user : " << minTweets << endl;
	cout << "Maximum Tweets per user : " << maxTweets << endl;
}

void cUserList::TopMost5TweetedWord()
{
	int max[5] = { 0, 0, 0, 0, 0 };
	string str[5];

	for (auto iter = mapWord.begin(); iter != mapWord.end(); iter++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (iter->second.sID.size() > max[i])
			{
				for (int j = 4; j > i; j--)
				{
					max[j] = max[j - 1];
					str[j] = str[j - 1];
				}

				max[i] = iter->second.sID.size();
				str[i] = iter->first;
				
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		cout << str[i] << " : " << max[i] << endl;
	}


}

void cUserList::TopMost5TweetedUser()
{
	int max[5] = { 0, 0, 0, 0, 0 };
	string str[5];

	for (auto iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (iter->second->vTweet.size() > max[i])
			{
				for (int j = 4; j > i; j--)
				{
					max[j] = max[j - 1];
					str[j] = str[j - 1];
				}

				max[i] = iter->second->vTweet.size();
				str[i] = iter->second->screenName;

				break;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		cout << str[i] << " : " << max[i] << endl;
	}
}

void cUserList::findUserWithWords(string str)
{
	auto it = mapWord.find(str);

	if (it != mapWord.end())
	{
		for (auto i = it->second.sID.begin(); i != it->second.sID.end(); i++)
		{
			cout << mapUser[*i]->screenName << endl;
		}
	}
	else
	{
		cout << "cannot find word" << endl;
	}
}

void cUserList::findFriend(string screenName)
{
	auto it = mapUser.begin();
	for (it; it != mapUser.end(); it++)
	{
		if (it->second->screenName == screenName)
		{
			break;
		}
	}

	for (int i = 0; i < it->second->vFriendID.size(); i++)
	{
		cout << mapUser[it->second->vFriendID[i]]->screenName << endl;
	}
}

void cUserList::deleteWord(string word)
{
	auto iter = mapWord.find(word);

	if (iter != mapWord.end())
	{
		for (auto it = iter->second.sID.begin(); it != iter->second.sID.end(); it++)
		{
			for (int i = 0; i < mapUser[*it]->vTweet.size(); )
			{
				bool isDeleted = false;
				for (int j = 0; j < mapUser[*it]->vTweet[i]->str.size(); j++)
				{
					if (mapUser[*it]->vTweet[i]->str[j] == word)
					{
						mapUser[*it]->vTweet.erase(mapUser[*it]->vTweet.begin() + i);
						isDeleted = true;
						break;
					}
				}
				if (!isDeleted)
				{
					i++;
				}
			}
		}
		mapWord.erase(iter);
	}
	else
	{
		cout << "cannot find word" << endl;
	}
}

void cUserList::deleteUserByWord(string word)
{
	auto iter = mapWord.find(word);

	if (iter != mapWord.end())
	{
		for (auto it = iter->second.sID.begin(); it != iter->second.sID.end(); it++)
		{
			for (int i = 0; i < mapUser[*it]->vTweet.size();)
			{
				bool isDeleted = false;
				for (int j = 0; j < mapUser[*it]->vTweet[i]->str.size(); j++)
				{
					if (mapUser[*it]->vTweet[i]->str[j] == word)
					{
						mapUser[*it]->vTweet.erase(mapUser[*it]->vTweet.begin() + i);
						isDeleted = true;
						break;
					}
				}
				if (!isDeleted)
				{
					i++;
				}
			}
		}

		for (auto it = iter->second.sID.begin(); it != iter->second.sID.end(); it++)
		{
			mapUser.erase(*it);
		}

		mapWord.erase(iter);
	}
	else
	{
		cout << "cannot find word" << endl;
	}
}