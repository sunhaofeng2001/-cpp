#include<iostream>
using namespace std;
const int N = 13;
struct Node//定义图结点
{
	char name[2];//定义道路的名称
	int col;//定义图结点颜色数量
	int url;//定义图结点的度
};
class TU
{
public:
	TU(int b[][N], int m);//定义构造函数
	Node S[N];//定义图中的顶点
	int n;//顶点的个数
	int a[N][N];//定义图定点连接
};
TU::TU(int b[][N], int m)//构造函数 
{
	n = m;//赋值顶点个数
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i][j] = b[i][j];//a[][]=b[][]结点连接
	char l[N][2] = { 'A','B','A','C','A','D','B','A','B','C','B','D','D','A','D','B','D','C','E','A','E','B','E','C','E','D' };
	for (int i = 0; i < N; i++)
	{
		S[i].name[0] = l[i][0];//S[i].name=l[i]道路的名字
		S[i].name[1] = l[i][1];
		S[i].col = i;
		S[i].url = 0;//度赋初值
		for (int j = 0; j < N; j++)
		{
			S[i].url = S[i].url + b[i][j];//计算顶点的度
		}
	}
	//按照顶点度的大小给顶点排序，为的是选择度大的顶点，经过查询资料显示，这种方法在大部分情况下可以得到最优解
	for (int i = 1; i < N; i++)//起泡排序
		for (int j = 1; j < N - i; j++)
			if (S[j].url < S[j + 1].url)
			{
				Node tmp = S[j];
				S[j] = S[j + 1];
				S[j + 1] = tmp;
			}
}
bool OK(int a[N][N], int k, int x[])//判断当前顶点的颜色是否可用
{
	for (int i = 0; i < N; i++)
		if ((a[k][i]) && (x[k] == x[i]))
			return false;
	return true;
}
void Co(int b[N][N], int x[], int n, Node No[])//染色函数
{
	x[No[0].col] = 1;
	for (int k = 0; k < N; k++)
	{
		x[No[k].col] = 1;
		while (!OK(b, No[k].col, x))
			x[No[k].col] = x[No[k].col] + 1;
	}
}
int main()
{
	int x[N] = { 0 };//从AB到ED各路口的颜色
	int s[N][N] = {{0,0,0,0,1,1,1,0,0,1,0,0,0},
		           {0,0,0,0,0,1,1,1,0,1,1,0,0},
		           {0,0,0,0,0,0,0,0,0,1,1,1,0},
		           {0,0,0,0,0,0,0,0,0,0,0,0,0},
		           {1,0,0,0,0,0,0,1,0,0,1,0,0},
		           {1,1,0,0,0,0,1,0,0,0,1,1,0},
		           {1,1,0,0,0,1,0,0,0,0,1,1,0},
		           {0,1,0,0,1,0,0,0,0,0,0,0,1},
		           {0,0,0,0,0,0,0,0,0,0,0,0,0},
				   {1,1,1,0,0,0,0,0,0,0,0,0,0},
		           {0,1,1,0,1,1,1,0,0,0,0,0,0},
		           {0,0,1,0,0,1,1,1,0,0,0,0,0},
		           {0,0,0,0,0,0,0,0,0,0,0,0,0}};
	TU tu(s,N);//构造图tu
	Co(tu.a, x, N, tu.S);//进行染色
	for (int j = 0; j < N; ++j)
		cout << "路口" << tu.S[j].name[0]<<tu.S[j].name[1] << "的颜色:" << x[j] <<"色号"<< endl;
	int h = 0;
	for (int i = 0; i < N; i++)
	{
		if (x[i] > h)
			h = x[i];
	}
	cout <<"共分"<< h <<"次通过"<< endl;
	for (int i = 0; i < h; i++)
	{
		cout << "第" << i + 1 << "次通行的道路有:" << endl;
		for (int j = 0; j < N; j++)
		{
			if (x[j] == i+1)
				cout << tu.S[j].name[0] << tu.S[j].name[1]<<"  ";
		}
		cout << endl;
	}
}