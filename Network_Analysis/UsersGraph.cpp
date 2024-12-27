#include "UsersGraph.h"

// Constructor
UsersGraph::UsersGraph()
{

}

/////////////////////////////////// getters ///////////////////////////////////
vector<User *> UsersGraph::getUsers()
{
	return users_list;
}

User* UsersGraph::getMostInfluencerUser()
{
	return most_influencer_user;
}

User* UsersGraph::getMostActiveUser()
{
	return most_active_user;
}

///////////////////////////////////////////////////////////////////////////////
void UsersGraph::addUser(User* user)
{
	users_list.push_back(user);
}

vector<User*> UsersGraph::getMutualFollowers(const vector<long>& IDs)
{

}
