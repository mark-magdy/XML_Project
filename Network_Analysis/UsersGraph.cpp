#include "UsersGraph.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
//#include <utility>
//#include <memory>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <unordered_set>

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
			User* user= zero_user;
			for (treeNode* tempId : tempUser->children)
			{
				string data = tempId->identifier; // datafield of user
				if (data == "id")
				{
					long user_id = stol(tempId->content);

                   User *user1=users_list.findByID(user_id);
					if (user1==nullptr)
					{
						user = new User();
						user->ID = user_id;
						users_list.insert(user);
					}
                    else user=user1;
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

                               User *user2=users_list.findByID(fol_id);
								if (user2!= nullptr)
								{
									//found_fol = 1;
									user2->following_IDs_list.push_back(user->ID);
									user2->number_of_followings++;
									user2->number_of_connections++;
                                    //erase the following from the suggested list
                                    auto i=find(user2->suggested_friends_IDs_list.begin(),user2->suggested_friends_IDs_list.end(),user->ID);
                                    if(i!=user2->suggested_friends_IDs_list.end())
                                        user2->suggested_friends_IDs_list.erase(i);

									if (most_active_user->number_of_connections < user2->number_of_connections)
										most_active_user = user2;

									//handling suggested friends for my user from followers of my follower if follower found
									for (long suggested_id : user2->followers_IDs_list)
									{
										if (find(user->suggested_friends_IDs_list.begin(),
										         user->suggested_friends_IDs_list.end(),
										         suggested_id) == user->suggested_friends_IDs_list.end() && suggested_id
											!= user->ID&&find(user->following_IDs_list.begin(),
                                                              user->following_IDs_list.end(),
                                                              suggested_id) == user->following_IDs_list.end())
											user->suggested_friends_IDs_list.push_back(suggested_id);
									}
								}
							//}
							else
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
//									for (User* following : users_list)
//									{
                                        User *following =users_list.findByID(following_id);
										if (following!= nullptr)
										{
											if (find(following->suggested_friends_IDs_list.begin(),
											         following->suggested_friends_IDs_list.end(),
											         fol_id) == following->suggested_friends_IDs_list.end() && fol_id !=
												following->ID&&find(following->following_IDs_list.begin(),
                                                                    following->following_IDs_list.end(),
                                                                    fol_id) == following->following_IDs_list.end())
												following->suggested_friends_IDs_list.push_back(fol_id);
										}
//									}
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
					for (treeNode* pos : tempId->children)
					{
						if (pos->identifier == "post")
						{
                            string content;
                            vector<string>topics;

                            for (treeNode* cont : pos->children)

                            {
                                if(cont->identifier=="body")
                                {
                                    content =cont->content;
                                }
                                else if(cont->identifier=="topics")
                                {
                                    for (treeNode* top : cont->children)
                                    {
                                        if(top->identifier=="topic")
                                        {
                                            topics.push_back(top->content);
                                        }
                                        else{
                                            valid =0;break;
                                        }
                                    }
                                    if (valid==0)break;
                                }
                                else
                                {
                                    valid=0;break;
                                }
                            }
                            if(valid==0)break;
                            post p= post(topics,content,user->ID);
                            user->posts_list.push_back(p);
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


vector<long> UsersGraph::getMutualFollowers(const vector<long>& IDs)
{
	int size = IDs.size() ,i = 1;
	vector<long> result,empty;
	unordered_map<long,int> freq;
	bool increased;

	if(IDs.empty())return result;
	
	for (long x: IDs){
		increased =false;
		User* temp;
		temp = users_list.findByID(x);
		if(temp == nullptr){
			return empty;			//exceptaaaaaaaaaaaaaaaaaaan
		}
		for (long folower: temp->getFollowersIDsList()){
			freq[folower]++;
			if(freq[folower]==i)increased=true;
		}
		if(!increased){
			return empty;
		}
		i++;
	}
	for (const auto& map_it: freq){
		if (map_it.second == size){
			result.push_back(map_it.first);
		}
	}
	return result;
}