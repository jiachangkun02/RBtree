//
// Created by jiachangkun on 24-12-22.
//

#ifndef RBTREE_H
#define RBTREE_H

#endif //RBTREE_H
#pragma once
#include <iostream>
using namespace std;

enum color
{
	black,
	red
};

template<class T>
struct treenode
{
	treenode<T>* _left;
	treenode<T>* _right;
	treenode<T>* _parent;
	color col;
	T _data;

	treenode(const T& data)
		:_data(data)
		,col(red)
		,_left(nullptr)
		,_parent(nullptr)
		,_right(nullptr){};


};


template<class K,class T,class keyoft>
class RBtree
{
	typedef treenode<T> node;
public:
	
	void Rightrotate(node* x)//x是根节点
	{
		node* y=x->_left;
		x->_left=y->_right;
		if (y->_right!=nullptr)
		{
			node* rightnode=y->_right;
			rightnode->_parent=x;
			//将y的右子节点向下移动，其父节点设置为x
		}
		y->_parent=x->_parent;
		//也许x只是一颗子树，x的父节点在移动之后需要重新赋值给y节点

		if (x->_parent==nullptr)
		{
			_root=y;
		}
		else if (x==x->_parent->_right)
		{
			x->_parent->_right=y;
		}
		else
		{
			x->_parent->_left=y;
		}
		y->_right=x;
		x->_parent=y;
	}
	//左旋和右旋中的x都是要被旋下来的点 ！！！
	void leftrotate(node* x)
	{
		node* y=x->_right;
		x->_right=y->_left;
		if (y->_left!=nullptr)
		{
			node* leftnode=y->_left;
			leftnode->_parent=x;
		}
		y->_parent=x->_parent;
		if (x->_parent==nullptr)
		{
			_root=y;
		}
		else if (x==x->_parent->_left)
		{
			x->_parent->_left=y;
		}
		else
		{
			x->_parent->_right=y;
		}
		y->_left=x;
		x->_parent=y;
	}

	void fixinsert(node* k)
	{
		while (k!=_root && k->_parent->col==red)
		{
			if (k->_parent==k->_parent->_parent->_left)
			{
				node* uncle=k->_parent->_parent->_right;
				if (uncle->col==red)
				{
					k->_parent->col=uncle->col=black;
					k->_parent->_parent->col=red;
					k=k->_parent->_parent;
				}
				else
				{
					if (k=k->_parent->_right)
					{
						k=k->_parent;
						leftrotate(k);
					}
					k->_parent->col=black;
					k->_parent->_parent->col=red;
					Rightrotate(k->_parent->_parent);

				}
			}
			else
			{
				node* uncle=k->_parent->_parent->_left;
				if (uncle != nullptr && uncle->col==red)
				{
					k->_parent->col=uncle->col=black;
					k->_parent->_parent->col=red;
					k=k->_parent->_parent;
				}
				else
				{
					if (k==k->_parent->_left)
					{
						k=k->_parent;
						Rightrotate(k);
					}
					k->_parent->col=black;
					k->_parent->_parent->col=red;
					leftrotate(k->_parent->_parent);
				}
			}
		}
		_root->col=black;
	}

	void inorder()
	{
		_inorder(_root);
	}

	void insert(T data)
	{
		keyoft kof;
		node* new_node=new node(data);

		node* parent=nullptr;
		node* cur=_root;

		while (cur!=nullptr)
		{
			parent=cur;
			if (kof(new_node->_data)<kof(cur->_data))
			{
				cur=cur->_left;
			}
			else
			{
				cur=cur->_right;
			}
		}

		new_node->_parent=parent;

		//决定根节点的位置
		if (parent==nullptr)
		{
			_root=new_node;
		}
		else if (new_node->_data<parent->_data)
		{
			parent->_left=new_node;
		}
		else
		{
			parent->_right=new_node;
		}

		if (new_node->_parent==nullptr)
		{
			new_node->col=black;
			return;
		}
		if (new_node->_parent->_parent==nullptr)
		{
			return;
		}
		fixinsert(new_node);
	}
	void deletenode(T data)
	{
		node* z = find(data);
		if (z == nullptr) return; // 找不到节点直接返回

		// 删除逻辑
		node* y = z;          // y 是要删除的节点或其后继
		node* x = nullptr;    // x 是 y 的子节点
		color yOriginalColor = y->col;

		// 处理子节点情况
		if (z->_left == nullptr) {
			x = z->_right;
			transplant(z, z->_right);
		} else if (z->_right == nullptr) {
			x = z->_left;
			transplant(z, z->_left);
		} else {
			// 有两个子节点，找后继
			y = minimum(z->_right);
			yOriginalColor = y->col;
			x = y->_right;

			// 处理后继的链接关系
			if (y->_parent != z) {
				transplant(y, y->_right);
				y->_right = z->_right;
				y->_right->_parent = y;
			}

			transplant(z, y);
			y->_left = z->_left;
			y->_left->_parent = y;
			y->col = z->col;
		}

		delete z;

		// 若删除的是黑色节点，需要修复
		if (yOriginalColor == black) {
			deleteFix(x);
		}
	}


private:
	node* _root=nullptr;

	void _inorder(node* node)
	{
		if (node!=nullptr)
		{
			_inorder(node->_left);
			std::cout << node->_data<<" ";
			_inorder(node->_right);
		}
	}

	void fixdelete(node* x)
	{
		while (x!=_root && (x->col==black || x==nullptr))
		{
			if (x==x->_parent->_left)
			{
				node* uncle=x->_parent->_right;
				if (uncle->col==red)
				{
					uncle->col==black;
					x->_parent->col=red;
					leftrotate(x->_parent);
					uncle=x->_parent->_right;
				}

				if ((uncle->_left==nullptr || uncle->_left->col=black)&& (uncle->_right==nullptr || uncle->_right->col==black))
				{
					uncle->col=red;
					x=x->_parent;
				}
				else
				{
					if (uncle->_right==nullptr || uncle->_right->col==black)
					{
						if (uncle->_left!=nullptr)
						{
							uncle->_left->col=black;
						}
						uncle->col=red;
						Rightrotate(uncle);
						uncle=x->_parent->_right;
					}
					uncle->col=x->_parent->col;
					x->_parent->col=black;
					if (uncle->_right!=nullptr)uncle->_right->col=black;
					Rightrotate(x->_parent);
					x=_root;
				}
			}
			else
			{
				node* uncle=x->_parent->_left;
				if (uncle->col==red)
				{
					uncle->col=black;
					x->_parent->col=red;
					Rightrotate(x->_parent);
					uncle=x->_parent->_left;
				}
				if ((uncle->_right==nullptr || uncle->_right->col==black )&&(uncle->_left==nullptr || uncle->_left->col==black))
				{
					uncle->col=red;
					x=x->_parent;
				}
				else
				{
					if (uncle->_left==nullptr || uncle->_left->col==black)
					{
						if (uncle->_right!=nullptr)
						{
							uncle->_right->col=black;
						}
						uncle->col=red;
						leftrotate(uncle);
						uncle=x->_parent->_left;
					}
				}
			}
			if (x != nullptr) x->col = black;
		}
	}
	node* find()
	{
		keyoft ko;
		node* cur = _root;
		while (cur != nullptr) {
			if (ko(data) == ko(cur->_data)) {
				return cur;
			} else if (ko(data) < ko(cur->_data)) {
				cur = cur->_left;
			} else {
				cur = cur->_right;
			}
		}
		return nullptr;
	}
	void transplant(node* u,node* v)
	{
		if (u->_parent==nullptr)
		{
			_root=v;
		}
		else if (u==u->_parent->_left)
		{
			u->_parent->_left=v;
			v->_parent=u->_parent;
		}
		else
		{
			u->_parent->_right=v;
			v->_parent=u->_parent;
		}

	}
	node* _min(node* n)
	{//红黑树左小右大 所以最小值只用往左边寻找
		while (n->_left!=nullptr)
		{
			n=n->_left;
		}
		return n;
	}

};
