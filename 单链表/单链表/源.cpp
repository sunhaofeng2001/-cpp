#include<iostream>
using namespace std;
template<class Data>
struct Node
{
	Data data;
	Node<Data>* next;
};
template<class Data>
class list
{
private:
	Node<Data>* first;
public:
	list();
	list(Data a[],int n);
	void print();
	void insert(Data a, int i);
	Data delet(int i);
	Data search(int i);
	int Search(Data a);
	~list();
};
template<class Data>
list<Data>::list()
{
	first = new Node<Data>;
	first->next = NULL;
}
template<class Data>
list<Data>::list(Data a[],int n)
{
	first = new Node<Data>;
	first->next = NULL;
	for (int i = 0; i<n; i++)
	{
		Node<Data>* s = NULL;
		s = new Node<Data>;
		s->data = a[i];
		s->next = first->next;
		first->next = s;
	}
}
template<class Data>
void list<Data>::print()
{
	Node<Data>* s = NULL;
	s = new Node<Data>;
	s = first->next;
	while (s != NULL)
	{
		cout << s->data << " ";
		s = s->next;
	}
	cout << endl;
}
template<class Data>
void list<Data>::insert(Data a, int i)
{
	Node<Data>* s = first;
	int count = 0;
	while (count < i - 1 && s != NULL)
	{
		count++;
		s = s->next;
	}
	Node<Data>* x = NULL;
	x = new Node<Data>;
	x->data = a;
	x->next = s->next;
	s->next = x;
}
template<class Data>
Data list<Data>::delet(int i)
{
	Data x;
	Node<Data>* s = first;
	int count = 0;
	while (count < i - 1 && s != NULL)
	{
		count++;
		s = s->next;
	}
	if (s == NULL || s->next == NULL)
		throw"≤Â»ÎŒª÷√¥ÌŒÛ";
	else
	{
		Node<Data>* p = s->next;
		x = p->data;
		s->next = p->next;
		delete p;
		return x;
	}
}
template<class Data>
Data list<Data>::search(int i)
{
	Data x;
	Node<Data>* s = first;
	int count = 0;
	while (count < i && s != NULL)
	{
		count++;
		s = s->next;
	}
	x = s->data;
	return x;
}
template<class Data>
int list<Data>::Search(Data a)
{
	Node<Data>* p = first->next;
	int count = 1;
	while (p != NULL)
	{
		if (p->data == a)
			return count;
		p = p->next;
		count++;
	}
	return 0;
}
template<class Data>
list<Data>::~list()
{
	Node<Data>* p = first;
	while (first != NULL)
	{
		first = first->next;
		delete p;
		p = first;
	}
}
int main()
{
	int r[5] = { 1,2,3,4,5 }, i, x;
	list<int>L{ r,5 };
	L.print();
	i = L.Search(1);
	cout << i;
}