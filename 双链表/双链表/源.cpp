#include<iostream>
using namespace std;
template<class Data>
struct Node
{
	Data data;
	Node<Data>* frout, * next;
};
template<class Data>
class list
{
private:
	Node<Data>* first;
public:
	list();
	list(Data a[], int n);
	void print();
};
template<class Data>
list<Data>::list()
{
	first = new Node<Data>;
	first->frout = NULL;
	first->next = NULL;
}
template<class Data>
list<Data>::list(Data a[], int n)
{
	first = new Node<Data>;
	first->frout = NULL;
	first->next = NULL;
	for (int i = 0; i < n; i++)
	{
		if (first->next == NULL)
		{
			Node<Data>* s = new Node<Data>;
			s->data = a[i];
			s->next = first->next;
			s->frout = first;
			first->next = s;
		}
		else
		{
			Node<Data>* s = new Node<Data>;
			s->data = a[i];
			s->next = first->next;
			s->frout = first;
			first->next->frout = s;
			first->next = s;
		}
		
	}
}
template<class Data>
void list<Data>::print()
{
	Node<Data>* p = first->next;
	while (p != NULL)
	{
		cout << p->data;
		p = p->next;
	}

}
int main()
{
	int a[5] = { 1,2,3,4,5 };
	list<int>L(a, 5);
	L.print();
}