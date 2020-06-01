#include<iostream>
using namespace std;
const int N = 13;
struct Node//����ͼ���
{
	char name[2];//�����·������
	int col;//����ͼ�����ɫ����
	int url;//����ͼ���Ķ�
};
class TU
{
public:
	TU(int b[][N], int m);//���幹�캯��
	Node S[N];//����ͼ�еĶ���
	int n;//����ĸ���
	int a[N][N];//����ͼ��������
};
TU::TU(int b[][N], int m)//���캯�� 
{
	n = m;//��ֵ�������
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			a[i][j] = b[i][j];//a[][]=b[][]�������
	char l[N][2] = { 'A','B','A','C','A','D','B','A','B','C','B','D','D','A','D','B','D','C','E','A','E','B','E','C','E','D' };
	for (int i = 0; i < N; i++)
	{
		S[i].name[0] = l[i][0];//S[i].name=l[i]��·������
		S[i].name[1] = l[i][1];
		S[i].col = i;
		S[i].url = 0;//�ȸ���ֵ
		for (int j = 0; j < N; j++)
		{
			S[i].url = S[i].url + b[i][j];//���㶥��Ķ�
		}
	}
	//���ն���ȵĴ�С����������Ϊ����ѡ��ȴ�Ķ��㣬������ѯ������ʾ�����ַ����ڴ󲿷�����¿��Եõ����Ž�
	for (int i = 1; i < N; i++)//��������
		for (int j = 1; j < N - i; j++)
			if (S[j].url < S[j + 1].url)
			{
				Node tmp = S[j];
				S[j] = S[j + 1];
				S[j + 1] = tmp;
			}
}
bool OK(int a[N][N], int k, int x[])//�жϵ�ǰ�������ɫ�Ƿ����
{
	for (int i = 0; i < N; i++)
		if ((a[k][i]) && (x[k] == x[i]))
			return false;
	return true;
}
void Co(int b[N][N], int x[], int n, Node No[])//Ⱦɫ����
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
	int x[N] = { 0 };//��AB��ED��·�ڵ���ɫ
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
	TU tu(s,N);//����ͼtu
	Co(tu.a, x, N, tu.S);//����Ⱦɫ
	for (int j = 0; j < N; ++j)
		cout << "·��" << tu.S[j].name[0]<<tu.S[j].name[1] << "����ɫ:" << x[j] <<"ɫ��"<< endl;
	int h = 0;
	for (int i = 0; i < N; i++)
	{
		if (x[i] > h)
			h = x[i];
	}
	cout <<"����"<< h <<"��ͨ��"<< endl;
	for (int i = 0; i < h; i++)
	{
		cout << "��" << i + 1 << "��ͨ�еĵ�·��:" << endl;
		for (int j = 0; j < N; j++)
		{
			if (x[j] == i+1)
				cout << tu.S[j].name[0] << tu.S[j].name[1]<<"  ";
		}
		cout << endl;
	}
}