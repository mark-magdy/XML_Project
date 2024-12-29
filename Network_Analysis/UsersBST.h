#ifndef USERSBST_H
#define USERSBST_H

#include "User.h"

class UserBSTNode
{
public:
	User user;
	UserBSTNode* left;
	UserBSTNode* right;
	UserBSTNode(const User& user);
};

class UsersBST
{
	UserBSTNode* root;

	UserBSTNode* insertNode (UserBSTNode* node, const User& user);
	User* findNodeByID (UserBSTNode* node, long id) const;
	void deleteTree(UserBSTNode* node);

public:
	UsersBST();
	~UsersBST();
	void insert(const User& user);
	User* findByID(long id) const;
};

#endif //USERSBST_H
