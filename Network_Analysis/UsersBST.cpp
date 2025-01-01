#include "UsersBST.h"

UserBSTNode::UserBSTNode(User* user) : user(user), left(nullptr), right(nullptr)
{
}

UsersBST::UsersBST()
{
	root = nullptr;
}

UsersBST::~UsersBST()
{
	deleteTree(root);
}

void UsersBST::deleteTree(UserBSTNode* node) {
	if (node == nullptr)
	{
		return;
	}
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

UserBSTNode* UsersBST::insertNode(UserBSTNode* node, User* user)
{
	if (node == nullptr)
	{
		return new UserBSTNode(user);
	}
	else if (user->getID() < node->user->getID())
	{
		node->left = insertNode(node->left, user);
	}
	else
	{
		node->right = insertNode(node->right, user);
	}
	return node;
}

User* UsersBST::findNodeByID(UserBSTNode* node, long id) const
{
	if (node == nullptr)
	{
		return nullptr;
	}
	else if (node->user->getID() == id)
	{
		return node->user;
	}
	else if (id < node->user->getID())
	{
		return findNodeByID(node->left, id);
	}
	return findNodeByID(node->right, id);
}

void UsersBST::insert(User* user)
{
	root = insertNode(root, user);
}

User* UsersBST::findByID(long id) const
{
	return findNodeByID(root, id);
}
UserBSTNode* UsersBST::getRoot() {
    return root;
}
