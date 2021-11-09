#pragma once
#include <iostream>
#include "BinaryTree.h"

using namespace std;

/*
	����
	��������+�������й�����������ݹ飬˼·��
	1.������������ȷ�����ĸ����
	2.���ݸ���������������л��ֳ���������������Щ��㣬Ȼ���ٸ������������Ľ�������������еĴ���ȷ�������ĸ��ڵ㣬���ص�1
	�ظ����ϲ��裬ֱ��ÿ����������һ�����
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

//����+����ȷ��������
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

//����+����ȷ��������,�ؼ���ͨ���������������Ҹ�
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
	P->lchild = level_in_BuildBT(level, in, in1, j - 1, n);//n��ʲô��˼��
	P->rchild = level_in_BuildBT(level, in, j + 1, in2, n);
	return P;
}
/*
//������֪��ɶ��˼���������й���������?
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
��������ǵݹ��㷨����ջǰ���ʣ�
˼·��
1.���Ÿ������ӣ����η��ʽ�㲢��ջ��ֱ������Ϊ�գ�˵���ҵ��˿�������Ľ��
2.ջ��Ԫ�س�ջ�����Һ���Ϊ�գ�����ִ��1�����Һ��Ӳ�Ϊ�գ�ת������������ִ��1
*/
template<typename T>
void BinaryTree<T>::PreOrder() {
	cout << "ǰ�����:";
	stack<BinaryTree<T>*> s;
	BinaryTree<T>* p = this;
	while (p != nullptr || !s.isempty()) {
		if (p != nullptr) {
			visit(p);//�ȷ�������ջ
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
�����������ջǰ���ʣ�
˼·��
1.���Ÿ�������������ջ��ֱ������Ϊ��
2.ջ��Ԫ�س�ջ������:���Һ���Ϊ�գ�����ִ��2�����Һ���Ϊ���գ�ת��������ִ��1
*/
template<typename T>
void BinaryTree<T>::InOrder() {
	cout << "�������";
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
			visit(p);//��ջ�����
			p = p->rchild;
		}
	}
	cout << endl;
}

/*
����������
˼·��
1.���Ÿ�������������ջ��ֱ������Ϊ��
2.��ջ��Ԫ�أ����Һ��Ӳ�Ϊ����δ�����ʣ�ת��������ִ��1������ջ��Ԫ�س�ջ������
*/
template <typename T>
void BinaryTree<T>::PostOrder() {
	cout << "�������";
	stack<BinaryTree<T>*> s;
	BinaryTree<T>* p = this,r=nullptr;//����ָ��r��ָ��������ʹ��Ľ��
	while (p != nullptr || !s.isempty()) {
		if (p!=nullptr) {//�ߵ�����
			s.push(p);
			p=p->lchild
		}
		else {//����
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
�������
˼·��
1.���ڵ����
2.�ظ�{ ��һ�������Ӳ����ʽ�㣬�����������������������ڵ���ӣ����������������������������� }��ֱ������Ϊ��
*/
template<typename T>
void BinaryTree<T>::LevelOrder() {
	cout << "���������";
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
�ĸ��������ı�������ʱ��֪��ʲô��˼
*/

//�������Ĳ����������Ӧ�ڵ�Ķ�,�����Ӧ�Ķ���������
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