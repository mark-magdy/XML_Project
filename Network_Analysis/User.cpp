#include "User.h"

// constructor
User::User(const long ID, const string& name)
{
	this->ID = ID;
	this->name = name;
	number_of_followers = 0;
	number_of_followings = 0;
	number_of_posts = 0;
}
User::User()
{

}

/////////////////////////////////// getters ///////////////////////////////////
long User::getID()
{
	return ID;
}
//long User::getNFollowers()
//{
//    return number_of_followers;
//}

string User::getName()
{
	return name;
}

vector<string> User::getPostsList()
{
	return posts_list;
}

vector<long> User::getFollowersIDsList()
{
	return followers_IDs_list;
}

vector<long> User::getFollowingIDsList()
{
	return following_IDs_list;
}

vector<long> User::getSuggestedFriendsIDsList()
{
	return suggested_friends_IDs_list;
}
///////////////////////////////////////////////////////////////////////////////

void User::addFollower(const long ID)
{
	followers_IDs_list.push_back(ID);
	number_of_followers++;
}

void User::addSuggestedFriend(const long ID)
{
	suggested_friends_IDs_list.push_back(ID);
}

void User::addPost(const string& post)
{
	posts_list.push_back(post);
	number_of_posts++;
}

void User::addFollowee(const long ID)
{
	following_IDs_list.push_back(ID);
	//TODO: search for ID class and get his list of follwers and add this->ID in that list
}
