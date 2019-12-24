#ifndef LList_H
#define LList_H

#include<iostream>
#include <fstream>
#include<string>
#include <time.h>
using namespace std;

class node {
public:
	string data;
	node* next;
	node(string new_s, node* n = NULL)
	{
		data = new_s;

		next = n;
	}

};

class SLL {
public:
	node* head;
	node* tail;

	SLL() {
		head = NULL;
		tail = NULL;
	}

	void add_to_tail(string new_s)
	{
		if (tail == NULL)
		{
			head = tail = new node(new_s);
		}
		else
		{
			tail->next = new node(new_s);
			tail = tail->next;
		}
	}


	void swap(int a, int  b)
	{
		if (a == b) { return; }
		else {
			//		if (a==1){swap_head(a,b);return;}
			//		if (b==1){swap_head(b,a);return;}
			a--; b--;
			int count = 1;
			node* temp1 = NULL, * temp2 = NULL;
			node* temp = head;
			while (temp != NULL)
			{
				if (a == count) { temp1 = temp; }
				else if (b == count) { temp2 = temp; }
				count++;
				temp = temp->next;
			}

			if (temp1 == NULL || temp2 == NULL) { cout << "position to swap nodes is out of bound" << endl; return; }

			temp = temp1->next;
			temp1->next = temp2->next;
			temp2->next = temp;

			temp1 = temp1->next;
			temp2 = temp2->next;

			temp = temp1->next;
			temp1->next = temp2->next;
			temp2->next = temp;
		}

	}

	void print()
	{
		for (node* temp = head; temp != NULL; temp = temp->next)
		{
			cout << temp->data << endl;
		}
		cout << "\n\n\n________ENDING___________\n";

	}


};
#endif
