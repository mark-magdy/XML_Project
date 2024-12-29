#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
	long ID;
	string name;
	vector<string> posts_list;
	vector<long> followers_IDs_list;
	vector<long> following_IDs_list;
	vector<long> suggested_friends_IDs_list;	// followers of followers
public:	long number_of_followers =0;
	long number_of_followings =0;
    long number_of_connections =0;
	long number_of_posts=0;

	// private methods
	void addFollower(long ID);
	void addSuggestedFriend(long ID);

public:
	// constructor
	User(long ID, const string& name);
    User();
	// getters
	long getID();
	string getName();
	vector<string> getPostsList();
	vector<long> getFollowersIDsList();
	vector<long> getFollowingIDsList();
	vector<long> getSuggestedFriendsIDsList();
	// methods
	void addPost(const string& post);
	void addFollowee(long ID);

	friend class UsersGraph;
};

#endif //USER_H
