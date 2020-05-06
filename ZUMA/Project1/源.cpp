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
	zuma() { front = new Node<T>; num = 0; front->next = NULL; }//�޲ι���
	zuma(T a[], int n);//�вι��죬ʹ�ú���n��Ԫ�ص�����a��ʼ������
	~zuma();//��������
	void Print();//������������Ա��и�������Ԫ��
	Node<T>* Get(int i);//��ȡ���Ա��ϵ�i��λ���ϵ�Ԫ�ؽ���ַ
	void Insert(int i, T x);//�����Ա�ĵ�i��λ���ϲ���ֵΪx����Ԫ��
	void Delete(int i);//ɾ�����Ա��i��Ԫ���Լ�֮������������
	void Search();//�ҵ��������������ϵ���ͬ�����ַ��ĵ�һ����㲢ɾ��֮�����������Ľ��
private:
	Node<T>* front;
	int num;
};
template<typename T>
zuma<T>::zuma(T a[], int n)//��ʼ������
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
zuma<T>::~zuma()//��������
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
void zuma<T>::Print()//�������
{
	Node<T>* p = front->next;
	if (p != NULL) {
		for (int i = 0; i < num; i++)
		{
			cout << p->data;
			p = p->next;
		}
	}
	else cout << "-";//Ϊ�հ���ĿҪ�������-��
	cout << endl;
}
template<typename T>
Node<T>* zuma<T>::Get(int i)//��ȡ���Ա��ϵ�i��λ���ϵ�Ԫ�ؽ���ַ
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
void zuma<T>::Insert(int i, T x)//�����Ա�ĵ�i��λ���ϲ���ֵΪx����Ԫ��
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
		//throw"����λ�ô���";
}
template<typename T>
void zuma<T>::Delete(int i)//ɾ�����Ա��i��Ԫ���Լ�֮������������
{
	Node<T>* p = front;
	if (i != 1)p = Get(i - 1);//���i������1����ѯ��i�����ĵ�ַ
	Node<T>* q = p->next;
	char n = q->data;
	while (q->data == n)//��i�Լ�i�Ժ�����������data����ڵ�i�����Ľ��
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
void zuma<T>::Search()//�ҵ��������������ϵ���ͬ�����ַ��ĵ�һ����㲢ɾ��֮�����������Ľ��
{
	if (num >= 3) {
		int n = 1;
		while (n) {
			n = 0;
			Node<T>* p1 = front;
			Node<T>* p2 = p1->next;
			Node<T>* p3 = p2->next;
			int i = 0;
			while (p3->next != NULL)//����ƽ����ϱ���
			{
				if (p1->data == p2->data && p1->data == p3->data)//�жϣ���������Ӧ�Ĳ���
				{
					Delete(i);
					n = 1;
					break;
				}
				p1 = p2;//�ƽ�
				p2 = p3;
				p3 = p3->next;
				i++;
			}
			if (p3->next == NULL) //�ж���λ
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
	char a[50];//�����ʼ�ַ���
	int n;//�����������
	int s[50] = { 0 };//����ÿ�β����������λ��
	char d[50] = "";//����ÿ�β������������ĸ
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