#ifndef USERSBST_H
#define USERSBST_H

#include "User.cpp"

class UserBSTNode
{
public:
	User* user;
	UserBSTNode* left;
	UserBSTNode* right;
	UserBSTNode(User* user);
};

class UsersBST
{
	UserBSTNode* root;

	UserBSTNode* insertNode (UserBSTNode* node, User* user);
	User* findNodeByID (UserBSTNode* node, long id) const;
	void deleteTree(UserBSTNode* node);

public:
	UsersBST();
	~UsersBST();
	void insert(User* user);
	User* findByID(long id) const;
    UserBSTNode* getRoot();
};

#endif //USERSBST_H
