#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// choose direction
	if(start->data<newnodePtr->data){
		if(start->right==nullptr){ 
			start->right=newnodePtr;
			newnodePtr->parent=start;
			fixup(newnodePtr);
			return;
		}
		insert(start->right,newnodePtr);
	} else {
		if(start->left==nullptr){
			start->left=newnodePtr;
			newnodePtr->parent=start;
			fixup(newnodePtr);
			return;
		}
		insert(start->left,newnodePtr);
	}
	// recurse down the tree

	return;
}

// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{	
	if(loc->parent->left==loc){
		auto tmp = loc->parent;
		if(tmp==root) root = loc;
		loc->parent = tmp->parent;
		if(loc->parent!=nullptr) loc->parent->left = loc;
		tmp->parent = loc;
		if(loc->right!=nullptr) loc->right->parent=tmp;
		tmp->left = loc->right;
		loc->right = tmp;
		std::swap(loc->color,tmp->color);
		root->color=0;
		return;
	}	
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	if(loc->parent->right==loc){
		auto tmp = loc->parent;
		if(tmp==root) root = loc;
		loc->parent=tmp->parent;
		if(loc->parent!=nullptr) loc->parent->right = loc;
		tmp->parent = loc;
		if(loc->left!=nullptr) loc->left->parent=tmp;
		tmp->right = loc->left;
		loc->left = tmp;
		std::swap(loc->color,tmp->color);
		root->color=0;
		return;
	}
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{	if(loc==nullptr || loc->color==0) return;
	if(loc==root){
		loc->color=0; return;
	}	
	if(loc->parent->color==0) return;
	if(loc->parent==root){root->color=0; return;}
	auto g = loc->parent->parent, p=loc->parent, u=p;
	if(p==g->right) u = g->left;
	else u = g->right;
	if(u!=nullptr && u->color==1){
		g->color=1; u->color=0; p->color=0;
		fixup(g);
		return;
	}
	if(p==g->right && loc==p->left){
		rightrotate(loc);
		std::swap(p,loc);
	} else if(p==g->left && loc == p->right){
		leftrotate(loc);
		std::swap(p,loc);
	}
	if( g->right!=nullptr && loc==g->right->right){
		leftrotate(p);
		return;
	} else if( g->left!=nullptr && loc==g->left->left){
		rightrotate(p);
		return;
	}
	return;
}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}


