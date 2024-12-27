#ifndef USERSGRAPH_H
#define USERSGRAPH_H

#include "User.h"

class UsersGraph {
	vector<User *> users_list;
	User *most_influencer_user;	// has the most followers
	User *most_active_user;		// connected to lots of users

public:
	UsersGraph();
	// getters
	vector<User *> getUsers();
	User* getMostInfluencerUser();
	User* getMostActiveUser();
	// methods
	void addUser(User *user);
	vector<User *> getMutualFollowers(const vector<long>& IDs);
};

#endif //USERSGRAPH_H
