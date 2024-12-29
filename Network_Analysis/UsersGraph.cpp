#include "UsersGraph.h"
#include <bits/stdc++.h>
// Constructor
UsersGraph::UsersGraph(treeNode* t)
{
	User* zero_user = new User();
	zero_user->number_of_connections = -1;
	zero_user->number_of_followers = -1;

	most_active_user = zero_user;
	most_influencer_user = zero_user;
	bool valid = 1;
	if (t->identifier == "users")
	{
		for (treeNode* tempUser : t->children)
		{
			if (tempUser->identifier != "user")
			{
				valid = 0;
				break;
			}
			User* user;
			for (treeNode* tempId : tempUser->children)
			{
				string data = tempId->identifier; // datafield of user
				if (data == "id")
				{
					long user_id = stol(tempId->content);
					bool found = 0;
					for (User* user1 : users_list)
					{
						if (user1->ID == user_id)
						{
							found = 1;
							user = user1;
						}
					}
					if (!found)
					{
						user = new User();
						user->ID = user_id;
						users_list.insert(user);
					}
				}
				else if (data == "name")
				{
					user->name = tempId->content;
				}
				else if (data == "followers")
				{
					for (treeNode* foll : tempId->children)
					{
						if (foll->identifier == "follower" && foll->children[0]->identifier == "id")
						{
							long fol_id = stol(foll->children[0]->content);
							//update the followers and connections for my user
							user->followers_IDs_list.push_back(fol_id);

							user->number_of_followers++;
							user->number_of_connections++;

							if (most_influencer_user->number_of_followers < user->number_of_followers)
								most_influencer_user = user;
							if (most_active_user->number_of_connections < user->number_of_connections)
								most_active_user = user;

							//update the followings and connections of follower user
							bool found_fol = 0;
							for (User* user2 : users_list)
							{
								if (user2->ID == fol_id)
								{
									found_fol = 1;
									user2->following_IDs_list.push_back(user->ID);
									user2->number_of_followings++;
									user2->number_of_connections++;

									if (most_active_user->number_of_connections < user2->number_of_connections)
										most_active_user = user2;

									//handling suggested friends for my user from followers of my follower if follower found
									for (long suggested_id : user2->followers_IDs_list)
									{
										if (find(user->suggested_friends_IDs_list.begin(),
										         user->suggested_friends_IDs_list.end(),
										         suggested_id) == user->suggested_friends_IDs_list.end() && suggested_id
											!= user->ID)
											user->suggested_friends_IDs_list.push_back(suggested_id);
									}
								}
							}
							if (!found_fol)
							{
								User* user2 = new User();
								user2->ID = fol_id;
								user2->following_IDs_list.push_back(user->ID);
								user2->number_of_followings++;
								user2->number_of_connections++;

								if (most_active_user->number_of_connections < user2->number_of_connections)
									most_active_user = user2;

								users_list.insert(user2);
							}
							//handling suggested friends to the following users if have
							if (!user->following_IDs_list.empty())
							{
								for (long following_id : user->following_IDs_list)
								{
									for (User* following : users_list)
									{
										if (following->ID == following_id)
										{
											if (find(following->suggested_friends_IDs_list.begin(),
											         following->suggested_friends_IDs_list.end(),
											         fol_id) == following->suggested_friends_IDs_list.end() && fol_id !=
												following->ID)
												following->suggested_friends_IDs_list.push_back(fol_id);
										}
									}
								}
							}
						}
						else
						{
							valid = 0;
							break;
						}
					}
				}
				else if (data == "posts")
				{
					for (treeNode* post : tempId->children)
					{
						if (post->identifier == "post")
						{
							user->posts_list.push_back(post->content);
							user->number_of_posts++;
						}
						else
						{
							valid = 0;
							break;
						}
					}
				}
				else
				{
					valid = 0;
				}

				if (valid == 0)break;
			}
			if (valid == 0)break;
		}
	}
	else
	{
		valid = 0;
	}
	if (valid == 0)cout << "INVALID INPUT" << endl;
}

/////////////////////////////////// getters ///////////////////////////////////
UsersBST& UsersGraph::getUsers()
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
	users_list.insert(user);
}


vector<User*> UsersGraph::getMutualFollowers(const vector<long>& IDs)
{
	//TODO: Implementation
}