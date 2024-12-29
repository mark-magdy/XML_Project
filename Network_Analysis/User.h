#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User
{
	long ID;
	string name;
	vector<string> posts_list;
	vector<long> followers_IDs_list;
	vector<long> following_IDs_list;
	vector<long> suggested_friends_IDs_list; // followers of followers
	long number_of_followers;
	long number_of_followings;
	long number_of_connections;
	long number_of_posts;

	// private methods
	void addFollower(long ID);
	void addSuggestedFriend(long ID);

public:
	// constructors
	User();
	User(long ID, const string& name);
	// getters
	long getID() const;
	string getName();
	vector<string> getPostsList();
	vector<long> getFollowersIDsList();
	vector<long> getFollowingIDsList();
	vector<long> getSuggestedFriendsIDsList();
	long getNumOfFollowers();
	long getNumOfFollowings();
	long getNumOfConnections();
	long getNumOfPosts();
	// methods
	void addPost(const string& post);
	void addFollowee(long ID);

	friend class UsersGraph;
};

#endif //USER_H
