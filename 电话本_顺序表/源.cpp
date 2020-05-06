#include<iostream>
#include<string>
using namespace std;
template<class T,int N>
class S
{
private:
	T data[N];
	int length;
public:
	S() { length = 0; }
	S(T a[], int n);
	void printlist();
	int Getlength() { return length; }
	T get(int i);
	T delet(int i);
	void insert(int i, T x);
	int find(T x);
};
template<class T,int N>
S<T,N>::S(T a[],int n)
{
	if (n<1 || n>N)throw"个数错误（过大或过小）";
	for (int i = 0; i < n; i++)
	{
		data[i] = a[i];
	}
	length = n;
}
template<class T,int N>
void S<T, N>::printlist()
{
	for (int i = 0; i < length; i++)
	{
		data[i].print();
		//cout << data[i] << " ";
	}
	cout << endl;
}
template<class T,int N>
T S<T, N>::get(int i)
{
	if (length == 0)throw"下溢异常";
	if (i<1 || i>length)throw"位置错误";
	return data[i - 1];
}
template<class T,int N>
T S<T, N>::delet(int n)
{
	if (n<1 || n>length)throw"删除位置错误";
	T a = data[n - 1];
	for (int i = n; i < length; i++)
	{
		data[i- 1] = data[i];
	}
	length--;
	return a;
}
template<class T,int N>
void S<T, N>::insert(int n, T x)
{
	if (n<1 || n>length+1)throw"插入位置错误";
	if (n == length+1)
	{
		data[length - 1] = x;
		length++;
	}
	else
	{
		for (int i = length; i >= n; i--)
		{
			data[i] = data[i - 1];
		}
		data[n - 1] = x;
		length++;
	}
}
template<class T,int N>
int S<T, N>::find(T x)
{
	for (int i = 0; i < length; i++)
	{
		if (data[i] == x)
			return i + 1;
	}
	return 0;
}
class PHO
{
private:
	int num;
	string name;
	string pho;
	string group;
public:
	PHO() {};
	PHO(int n, const char* q, const char* w, const char* e)
	{
		num = n; name = q;
		pho = w; group = e;
	}
	void print()
	{
		cout << num << " " << name << " " << pho << " " << group << endl;
	}
	bool operator==(PHO& p)
	{
		if (p.num == num)
			return true;
		return false;
	}
};
int main()
{
	int x;
	PHO y;
	PHO book[5] = {
		{2001,"shf","18610787882","sun"},
		{2002,"zhm","18266270278","mum"},
	    {2000,"st","12623217322","bro"},
		{2003,"shh","13562237278","dad"},
		{2004,"lll","15954398115","dau"}
	};
	PHO u = { 2005,"szq","1111111111","gra" };
	S<PHO, 100>list(book, 5);
	list.printlist();
	PHO z = list.delet(3);
	list.printlist();
	z.print();
	x=list.find({ 2004,"zzt","15954398115","dau" });
	cout << x << endl;
	list.insert(4, u);
	list.printlist();
	y = list.get(3);
	y.print();
}