#include<iostream>
#include<string>
using namespace std;
template<typename T>
struct Node
{
	T data;
	struct Node<T>* next;
};
template<typename T>
class zuma
{
public:
	zuma() { front = new Node<T>; num = 0; front->next = NULL; }//无参构造
	zuma(T a[], int n);//有参构造，使用含有n个元素的数组a初始化链表
	~zuma();//析构函数
	void Print();//按次序遍历线性表中各个数据元素
	Node<T>* Get(int i);//获取线性表上第i个位置上的元素结点地址
	void Insert(int i, T x);//在线性表的第i个位置上插入值为x的新元素
	void Delete(int i);//删除线性表第i个元素以及之后所有连续的
	void Search();//找到三个及三个以上的相同连续字符的第一个结点并删除之后所有连续的结点
private:
	Node<T>* front;
	int num;
};
template<typename T>
zuma<T>::zuma(T a[], int n)//初始化链表
{
	num = n;
	front = new Node<T>;
	front->next = NULL;
	front->data = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		Node<T>* s = new Node<T>;
		s->data = a[i];
		s->next = front->next;
		front->next = s;
	}
}
template<typename T>
zuma<T>::~zuma()//析构函数
{
	Node<T>* p = front;
	while (p)
	{
		front = p;
		p = p->next;
		delete front;
	}
	num = 0;
}
template<typename T>
void zuma<T>::Print()//遍历输出
{
	Node<T>* p = front->next;
	if (p != NULL) {
		for (int i = 0; i < num; i++)
		{
			cout << p->data;
			p = p->next;
		}
	}
	else cout << "-";//为空按题目要求输出“-”
	cout << endl;
}
template<typename T>
Node<T>* zuma<T>::Get(int i)//获取线性表上第i个位置上的元素结点地址
{
	Node<T>* p = front->next;
	int j = 1;
	while (p && j != i)
	{
		p = p->next;
		j++;
	}
	return p;
}
template<typename T>
void zuma<T>::Insert(int i, T x)//在线性表的第i个位置上插入值为x的新元素
{
	Node<T>* p = front;
	if (i != 1)
		p = Get(i - 1);
	if (p)
	{
		Node<T>* s = new Node<T>;
		s->data = x;
		s->next = p->next;
		p->next = s;
		num++;
	}
	//else 
		//throw"插入位置错误";
}
template<typename T>
void zuma<T>::Delete(int i)//删除线性表第i个元素以及之后所有连续的
{
	Node<T>* p = front;
	if (i != 1)p = Get(i - 1);//如果i不等于1，查询第i个结点的地址
	Node<T>* q = p->next;
	char n = q->data;
	while (q->data == n)//将i以及i以后所有连续的data域等于第i个结点的结点
	{
		Node<T>* q2 = q->next;
		p->next = q->next;
		delete q;
		q = q2;
		num--;
		if (q == NULL) break;

	}
}
template<typename T>
void zuma<T>::Search()//找到三个及三个以上的相同连续字符的第一个结点并删除之后所有连续的结点
{
	if (num >= 3) {
		int n = 1;
		while (n) {
			n = 0;
			Node<T>* p1 = front;
			Node<T>* p2 = p1->next;
			Node<T>* p3 = p2->next;
			int i = 0;
			while (p3->next != NULL)//向后推进不断遍历
			{
				if (p1->data == p2->data && p1->data == p3->data)//判断，并作出相应的操作
				{
					Delete(i);
					n = 1;
					break;
				}
				p1 = p2;//推进
				p2 = p3;
				p3 = p3->next;
				i++;
			}
			if (p3->next == NULL) //判断首位
			{
				if (p1->data == p2->data && p1->data == p3->data)
				{
					Delete(1);
					n = 0;

				}
			}
		}
	}
}
int main()
{
	char a[50];//储存初始字符串
	int n;//储存操作次数
	int s[50] = { 0 };//储存每次操作所插入的位置
	char d[50] = "";//储存每次操作所插入的字母
	cin >> a;
	int y = strlen(a);
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
		cin >> d[i];
	}
	zuma<char>list(a, y);
	for (int i = 0; i < n; i++)
	{
		list.Insert(s[i] + 1, d[i]);
		list.Search();
		list.Print();
	}
}