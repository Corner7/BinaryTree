#pragma once

#include <iostream>
#include "..\..\Stack\Stack\Stack.h"
#include "..\..\Queue\Queue\Queue.h"

using namespace std;

const int MaxSize = 100;

template <typename T>
class BinaryTree {
public:
	BinaryTree() {
		data = 0;
		lchild = nullptr;
		rchild = nullptr;
	}

	BinaryTree(T data) {
		this->data = data;
		lchild = nullptr;
		rchild = nullptr;
	}

	//友元函数，是其他类的函数访问当前类的私有成员，不是当前类的成员函数
	friend BinaryTree<T>* pre_in_BuildBT(T pre[], T in[], int pre1, int pre2, int in1, int in2);
	friend BinaryTree<T>* post_in_BuildBT(T post[], T in[], int post1, int post2, int in1, int in2);
	friend BinaryTree<T>* level_in_BuildBT(T level[], T in[], int level1, int level2, int in1, int in2);
	friend BinaryTree<T>* level_BuildBT(T A[], int n); //层序构造完全二叉树

	//操作
	void visit(BinaryTree<T>* t);

	void PreOrder();
	void InOrder();
	void PostOrder();
	void LevelOrder();

	void PreOrder(T *data);
	void InOrder(T *data);
	void PostOrder(T *data);
	void LevelOrder(T *data);

	friend BinaryTree<T>* treetoBinarytree(T level[], int grade[], int k);//树的层序和度构造二叉树

	void disp(int deep);

	BinaryTree<T> *findk(BinaryTree<int> t, int k);
	int WPL(int k = 0);
	void swapBinaryTree();//交换左右子树
	int generation();//递归求高度
	int high();//非递归求高度
	bool iscomplete();//是否是完全二叉树
	int dson();//度为二节点数（双分支）
	void deletevalue(T x);
	void deleteroot();
	void printroute(T x);//求路径
	BinaryTree<T> *ancestor(BinaryTree<T>* p, BinaryTree<T>* q);//找共同祖先
	BinaryTree<T> *find(T x);
	int width();//求宽度
	BinaryTree<T>* linkLeaf();
	bool issame(BinaryTree<T> *tr);
	int level(BinaryTree<T> *p, int n = 1);//所在层次
	bool isbalance(int h,bool &balance);
	void lastgen();
	virtual void Insert(int x);
	

protected:
	T data;
	BinaryTree<T>* lchild;
	BinaryTree<T>* rchild;
};

void pretopost(int pre[],int begin,int end);

//霍夫曼树
template<typename T>
class HufmanTree :public BinaryTree<T> {
public:
	HufmanTree() {
		this->data = 0;
		this->lchild = nullptr;//为什么没有备选项？
		this->rchild = nullptr;
	}
	HufmanTree(T data) {
		this->data = data;
		this->lchild = nullptr;
		this->rchild = nullptr;
	}

	friend HufmanTree<T>* buildHufmantree(T a[],int n);//构造霍夫曼树

};

//注意，基类中的private成员继承后不可见，不能被使用
//如果希望基类的成员既不向外暴露（不能通过对象访问），还能在派生类中使用，那么只能声明为 protected。
//继承方式一般使用public
class BinarySearchTree: public BinaryTree<int> {
public:
	BinarySearchTree() {
		this->data = 0;
		this->lchild = nullptr;
		this->rchild = nullptr;
	}
	BinarySearchTree(int r) {
		this->data = r;
		this->lchild = nullptr;
		this->rchild = nullptr;
	}
	friend BinarySearchTree* buildBinarySearchTree(int A[],int n);
	virtual void insert(int x);
	void showk(int k);	//由大到小输出BST大于等于K的节点
};

