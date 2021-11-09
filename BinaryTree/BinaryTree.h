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

	//��Ԫ��������������ĺ������ʵ�ǰ���˽�г�Ա�����ǵ�ǰ��ĳ�Ա����
	friend BinaryTree<T>* pre_in_BuildBT(T pre[], T in[], int pre1, int pre2, int in1, int in2);
	friend BinaryTree<T>* post_in_BuildBT(T post[], T in[], int post1, int post2, int in1, int in2);
	friend BinaryTree<T>* level_in_BuildBT(T level[], T in[], int level1, int level2, int in1, int in2);
	friend BinaryTree<T>* level_BuildBT(T A[], int n); //��������ȫ������

	//����
	void visit(BinaryTree<T>* t);

	void PreOrder();
	void InOrder();
	void PostOrder();
	void LevelOrder();

	void PreOrder(T *data);
	void InOrder(T *data);
	void PostOrder(T *data);
	void LevelOrder(T *data);

	friend BinaryTree<T>* treetoBinarytree(T level[], int grade[], int k);//���Ĳ���Ͷȹ��������

	void disp(int deep);

	BinaryTree<T> *findk(BinaryTree<int> t, int k);
	int WPL(int k = 0);
	void swapBinaryTree();//������������
	int generation();//�ݹ���߶�
	int high();//�ǵݹ���߶�
	bool iscomplete();//�Ƿ�����ȫ������
	int dson();//��Ϊ���ڵ�����˫��֧��
	void deletevalue(T x);
	void deleteroot();
	void printroute(T x);//��·��
	BinaryTree<T> *ancestor(BinaryTree<T>* p, BinaryTree<T>* q);//�ҹ�ͬ����
	BinaryTree<T> *find(T x);
	int width();//����
	BinaryTree<T>* linkLeaf();
	bool issame(BinaryTree<T> *tr);
	int level(BinaryTree<T> *p, int n = 1);//���ڲ��
	bool isbalance(int h,bool &balance);
	void lastgen();
	virtual void Insert(int x);
	

protected:
	T data;
	BinaryTree<T>* lchild;
	BinaryTree<T>* rchild;
};

void pretopost(int pre[],int begin,int end);

//��������
template<typename T>
class HufmanTree :public BinaryTree<T> {
public:
	HufmanTree() {
		this->data = 0;
		this->lchild = nullptr;//Ϊʲôû�б�ѡ�
		this->rchild = nullptr;
	}
	HufmanTree(T data) {
		this->data = data;
		this->lchild = nullptr;
		this->rchild = nullptr;
	}

	friend HufmanTree<T>* buildHufmantree(T a[],int n);//�����������

};

//ע�⣬�����е�private��Ա�̳к󲻿ɼ������ܱ�ʹ��
//���ϣ������ĳ�Ա�Ȳ����Ⱪ¶������ͨ��������ʣ�����������������ʹ�ã���ôֻ������Ϊ protected��
//�̳з�ʽһ��ʹ��public
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
	void showk(int k);	//�ɴ�С���BST���ڵ���K�Ľڵ�
};

