#pragma once
#include <iostream>
#include "BinaryTree.h"

using namespace std;

/*
	★★★
	先序序列+中序序列构造二叉树，递归，思路：
	1.根据先序序列确定树的根结点
	2.根据根结点在中序序列中划分出左右子树包含哪些结点，然后再根据左右子树的结点在先序序列中的次序确定子树的根节点，即回到1
	重复以上步骤，直到每棵子树仅有一个结点
*/
template<typename T>
BinaryTree<T> *pre_in_BuildBT(T pre[], T in[], int pre1, int pre2, int in1, int in2) {
	BinaryTree<T>* root = new BinaryTree<T>(pre[pre1]);
	int i;
	for (i = in1; root->data != in[in1]; ++);
	int llen = i - in1;
	int rlen = in2 - i;
	if (llen)
		root->lchild = pre_in_BuildBT(pre, in, pre1 + 1, pre1 + llen, in1, in1 + llen - 1);
	else
		root->lchild = nullptr;
	if (rlen)
		root->rchild = pre_in_BuildBT(pre, in, pre2 - rlen + 1, pre2, in2 - rlen + 1, in2);
	else
		root->rchild = nullptr;
	return root;
}

//后续+中序确定二叉树
template<class T>
BinaryTree<T>* post_in_BuildBT(T post[], T in[], int post1, int post2, int in1, int in2) {
	BinaryTree<T>* root = new BinaryTree<T>(post[post2]);
	int i;
	for (i = in1; in[i] != root->data; i++);
	int llen = i - in1;
	int rlen = in2 - i;
	if (llen)
		root->lchild = post_in_BuildBT(post, in, post1, post1 + llen - 1, in1, in1 + llen - 1);
	else
		root->lchild = nullptr;
	if (rlen)
		root->rchild = post_in_BuildBT(post, in, post2 - rlen, post2 - 1, in2 - rlen + 1, in2);
	else
		root->rchild = nullptr;
	return root;
}

//层序+中序确定二叉树,关键：通过层序在中序中找根
template<typename T>
BinaryTree<T>* level_in_BuildBT(T level[],T in[],int in1,int in2,int n) {
	if (in1 > in2)
		return nullptr;
	bool find;
	int i, j;
	for (i = 0; i < n; i++) {
		find = false;
		for(j=in1;j<=in2;j++)
			if (level[i] == in[j]) {
				find = true;
				break;
			}
		if (find)
			break;
	}
	BinaryTree<T>* P = new BinaryTree<T>(level[i]);
	P->lchild = level_in_BuildBT(level, in, in1, j - 1, n);//n是什么意思？
	P->rchild = level_in_BuildBT(level, in, j + 1, in2, n);
	return P;
}
/*
//▲，不知道啥意思，层序序列构建二叉树?
template<typename T>
BinaryTree<T>* level_BuildBT(T level[],int n) {
	BinaryTree<T>* root = new BinaryTree<T>(level[0]);
	BinaryTree<T>* tr = root;
	queue<BinaryTree<T>*> q;
	q.push(tr);
	int i = 1;
	while (i < n) {
		tr = q.getfront();
		q.pop();
		if


		tr->lchild = new BinaryTree(level[i++]);
		tr->rchild = new BinaryTree(level[i++]);
	}
}

*/


/*
先序遍历非递归算法（入栈前访问）
思路：
1.沿着根的左孩子，依次访问结点并入栈，直到左孩子为空，说明找到了可以输出的结点
2.栈顶元素出栈：若右孩子为空，继续执行1，若右孩子不为空，转向右子树继续执行1
*/
template<typename T>
void BinaryTree<T>::PreOrder() {
	cout << "前序遍历:";
	stack<BinaryTree<T>*> s;
	BinaryTree<T>* p = this;
	while (p != nullptr || !s.isempty()) {
		if (p != nullptr) {
			visit(p);//先访问再入栈
			s.push(p);
			p = p->lchild;
		}
		else {
			p=s.gettop();
			s.pop();
			p = p->rchild;
		}
	}
	cout << endl;
}

/*
中序遍历（出栈前访问）
思路：
1.沿着根的左孩子依次入栈，直到左孩子为空
2.栈顶元素出栈并访问:若右孩子为空，继续执行2，若右孩子为不空，转向右子树执行1
*/
template<typename T>
void BinaryTree<T>::InOrder() {
	cout << "中序遍历";
	stack<BinaryTree<T>*> s;
	BinaryTree<T>* p = this;
	while (p != nullptr || !s.isempty()) {
		if (p != nullptr) {
			s.push(p);
			p = p->lchild;
		}
		else {
			p = s.gettop();
			s.pop();
			visit(p);//出栈后访问
			p = p->rchild;
		}
	}
	cout << endl;
}

/*
★★★后序遍历
思路：
1.沿着根的左孩子依次入栈，直到左孩子为空
2.读栈顶元素：若右孩子不为空且未被访问，转向右子树执行1，否则栈顶元素出栈并访问
*/
template <typename T>
void BinaryTree<T>::PostOrder() {
	cout << "后序遍历";
	stack<BinaryTree<T>*> s;
	BinaryTree<T>* p = this,r=nullptr;//辅助指针r，指向最近访问过的结点
	while (p != nullptr || !s.isempty()) {
		if (p!=nullptr) {//走到最左
			s.push(p);
			p=p->lchild
		}
		else {//向右
			p=s.gettop();
			if (p->rchild != nullptr && rchild != r)
				p = p->rchild;
			else {
				p = s.gettop();
				s.pop();
				visit(p);
				r = p;
				p = nullptr;
			}
		}
	}
	cout << endl;
}

/*
层序遍历
思路：
1.根节点入队
2.重复{ 第一个结点出队并访问结点，若有左子树，将左子树根节点入队；若有右子树，将右子树根结点入队 }，直到队列为空
*/
template<typename T>
void BinaryTree<T>::LevelOrder() {
	cout << "层序遍历：";
	queue<BinaryTree<T>*> q;
	BinaryTree<T> p = this;
	q.push(this);
	while (!q.isempty()) {
		p = q.getfront();
		q.pop();
		visit(p);
		if (p->lchild != nullptr)
			q.push(p.lchild);
		if (p->rchild != nullptr)
			q.push(p.lchild);
	}
	cout << endl;
}

/*
四个带参数的遍历，暂时不知道什么意思
*/

//给出树的层序遍历及对应节点的度,构造对应的二叉链表树
template<typename T>
BinaryTree<T>* treetoBinarytree(T level[], int garde[], int k) {
	int x = 0, y = 0;
	BinaryTree<T>* root = new BinaryTree<T>(level[x++]);
	BinaryTree<T>* p;
	queue<BinaryTree<T>*> q;
	queue<int> g;
	q.push(root);
	g.push(grade[y++]);
	while (x<k) {
		p = q.getfront();
		q.pop();
		int n = g.getfront();
		g.pop();

	}

}