#include "redblack.h"
#include "stddef.h"
#include <iostream>

using namespace std;

IntRBTree::IntRBTree() {
	// RBTree �ʱ�ȭ
	z = new Node(black, 0, 0, 0, 0); // leaf node (NIL)
	z->l = z; z->r = z;
	head = new Node(black, 0, 0, 0, z); // head
}

Node *IntRBTree::search(int search_key)
{
	// search_key ���� ���� ��带 ã�Ƽ� ��ȯ
	Node *x = head->r; // x�� root node�� �ʱ�ȭ
	while (x != z) { // leaf node�� ������ ������
		if (x->key == search_key) return x;
		x = (x->key > search_key) ? x->l : x->r;
	}
	return NULL;
}

void IntRBTree::insert(int v, int index)
{
	cout << endl << endl << "Insert Start!! key = " << v << endl;

	x = head; p = head; g = head;
	cout << "x->b = " << x->b << ", x->key = " << x->key << endl;
	cout << "p->b = " << p->b << ", p->key = " << p->key << endl;
	cout << "g->b = " << g->b << ", g->key = " << g->key << endl;

	int count = 0;
	while (x != z) {
		count++;
		cout << endl << "In Insert-While, count = " << count << endl;

		gg = g; g = p; p = x;
		cout << "gg->b = " << gg->b << ", gg->key = " << gg->key << endl;
		cout << "g->b = " << g->b << ", g->key = " << g->key << endl;
		cout << "p->b = " << p->b << ", p->key = " << p->key << endl;

		if (x->key == v) return;
		x = (x->key > v) ? x->l : x->r;
		cout << "x->b = " << x->b << ", x->key = " << x->key << endl;

		// �ڽ��� ������ �� �� red�� split
		if (x->l->b && x->r->b) this->split(v);
	}
	x = new Node(red, v, index, z, z); // �� ��� ����
	if (p->key > v) p->l = x;
	else p->r = x;
	this->split(v);
	head->r->b = black; // ��Ʈ ���� black

	cout << "Insert End!!" << endl << endl;
}

// ������ ��� ó��
void IntRBTree::split(int v)
{
	cout << endl << "Split Start!!" << endl;
	x->b = red; x->l->b = black; x->r->b = black;
	cout << "x->b = " << x->b << ", x->key = " << x->key << endl;

	cout << "p->b = " << p->b << ", p->key = " << p->key << endl;
	if (p->b) { // �θ��� ������ red��
		g->b = red;
		cout << "g->b = " << g->b << ", g->key = " << g->key << endl;

		if (g->key > v != p->key > v) p = this->rotate(v, g);
		cout << "p->b = " << p->b << ", p->key = " << p->key << endl;

		x = this->rotate(v, gg);
		cout << "x->b = " << x->b << ", x->key = " << x->key << endl;
		x->b = black;
		cout << "x->b = " << x->b << ", x->key = " << x->key << endl;
	}
	cout << "Split End!!" << endl << endl;
}

Node *IntRBTree::rotate(int v, Node *y /*gg*/)
{
	cout << endl << "Rotate Start!!" << endl;

	Node *gc, *c;

	c = (y->key > v) ? y->l : y->r;
	cout << "c->b = " << c->b << ", c->key = " << c->key << endl;

	if (c->key > v) {
		gc = c->l; c->l = gc->r; gc->r = c;
		cout << "c->b = " << c->b << ", c->key = " << c->key << endl;
		cout << "gc->b = " << gc->b << ", gc->key = " << gc->key << endl;
	}
	else {
		gc = c->r; c->r = gc->l; gc->l = c;
		cout << "c->b = " << c->b << ", c->key = " << c->key << endl;
		cout << "gc->b = " << gc->b << ", gc->key = " << gc->key << endl;
	}
	if (y->key > v) y->l = gc;
	else y->r = gc;

	cout << "Rotate End!!" << endl << endl;

	return gc;
}

void IntRBTree::print() {
	cout << "Print Start!!" << endl << endl;
	cout << "head->b = " << head->b << endl;
	print(head->r);
	cout << "Print End!!" << endl;
}

void IntRBTree::print(Node * me) {
	if (me == z)
		return;

	cout << endl;
	cout << "key = " << me->key << ", color = " << me->b << endl;
	cout << "key = " << me->l->key << ", color = " << me->l->b << endl;
	cout << "key = " << me->r->key << ", color = " << me->r->b << endl;
	cout << endl;

	print(me->l);
	print(me->r);
}