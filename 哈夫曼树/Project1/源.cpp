#include<iostream>
#include<cstring>
#include<string>
using namespace std;
void Setting(int i);
struct hnode {
	int parent;//���常�ڵ�
	int lchild;//��������
	int rchild;//�����Һ���
	int weight;//����Ȩ��
};
struct hcode {
	char data;//����������
	char code[100];//���崢����뵥λ
};
class Huffman//�����������
{
private:
	hnode* HTree;//��������Ļ�������
	hcode* HCode;//����������ͱ���
	int NUM;//���������
public:
	Huffman();//���캯��
	void Init(char* list);//��ʼ��
	void CreateHTree(int list[], int num);//��������������
	void CreateTable(char dic_list[], int num);//���������
	void Encoding(char* encode, char* decode);//���뺯��
	void Decoding(char* encode, char* decode);//���뺯��
	void SelectMin(int& x, int& y, int begin, int end);//���Ȩֵ��С����������λ��
	void Six(char* encode, char* decode);//����ѹ����
	void Print(char* list);//ͼ�δ�ӡȨֵ
	void print();//��ӡ��������
	~Huffman();//��������
};
Huffman::Huffman()//����
{
	HTree = NULL;//��ʼ��
	HCode = NULL;//��ʼ��
	NUM = 0;//��ʼ��
}
void Huffman::Init(char* list)//
{
	char kinds[1000] = { 0 };//�����ַ������ಢ���г�ʼ��
	int counts[1000] = { 0 };//����ÿ���ַ��ĸ��������г�ʼ�������ڲ�֪���ַ�������������������ô�һ��
	int length = strlen(list);//�õ��ַ����ĳ���
	if (length > 1000)
	{
		throw length;//������󳤶��׳�
	}
	int j = 0;
	for (int i = 0; i < length; i++)//����ÿ����ͬ�ַ���Ȩֵ
	{
		char c = list[i];//ȡ�ַ����е�ÿ���ַ�
		for (j = 0; j < NUM; j++)//�ж��ַ��Ƿ��ظ�
		{
			if (c == kinds[j])//ͳ���ַ�����
			{
				counts[j]++;
				break;
			}
		}
		if (j == NUM)//�������µ��ַ�����¼�ַ�����¼���ִ���+1
		{
			counts[j] = 1;
			kinds[j] = list[i];
			NUM++;
		}
	}
	CreateHTree(counts, NUM);//������������
	CreateTable(kinds, NUM);//���������
}
void Huffman::SelectMin(int& x, int& y, int begin, int end)//����ȫ�α���δ�����Ĵ��룩Ѱ��Ȩ����С����������λ��
{
	x = 0, y = 0;
	while (HTree[x].parent != -1)
	{
		x++;
	}
	for (int i = 1; i < end; i++)
	{
		if (HTree[i].parent != -1)
		{
			continue;//���Ǻ�֮ǰ��һ����������
		}
		if (HTree[i].weight < HTree[x].weight)
		{
			x = i;
		}
	}
	HTree[x].parent = -2;//��x����parent��Ϊ������ȡ����ֵ��ֹ�ظ�
	while (HTree[y].parent != -1)
	{
		y++;
	}
	for (int j = 1; j < end; j++)
	{
		if (HTree[j].parent != -1)//��ֹx��y�ظ�
		{
			continue;
		}
		if (HTree[j].weight < HTree[y].weight)
		{
			y = j;
		}
	}
}
void Huffman::CreateHTree(int list[], int num)//������������
{
	HTree = new hnode[2 * num - 1];//������neicun
	for (int i = 0; i < num; i++)
	{
		HTree[i].weight = list[i];//�õ�Ȩֵ
		HTree[i].lchild = -1;//��ʼ��
		HTree[i].rchild = -1;
		HTree[i].parent = -1;
	}
	int x, y;//��������С��������
	for (int i = num; i < 2 * num - 1; i++)
	{
		SelectMin(x, y, 0, i);//��ȡ�����Сֵ
		HTree[x].parent = HTree[y].parent = i;//���ɹ���������ÿ�����
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].lchild = x;
		HTree[i].rchild = y;
		HTree[i].parent = -1;
	}
}
void Huffman::CreateTable(char list[], int num)//���������
{
	HCode = new hcode[num];//����ռ�
	for (int i = 0; i < num; i++)//���������
	{
		HCode[i].data = list[i];//��ÿ����ͬ���ַ���ֵ��������������
		int CNUM = i;
		int p = HTree[i].parent;
		int k = 0;
		while (p != -1)//���б���(��õ�Ϊ����ĵ���)
		{
			if (CNUM == HTree[p].lchild)//�ж����ӻ����ֺ���
				HCode[i].code[k] = '0';
			else
				HCode[i].code[k] = '1';
			k++;
			CNUM = p;
			p = HTree[CNUM].parent;
		}
		HCode[i].code[k] = '\0';
		int length = strlen(HCode[i].code);
		char temp[1000];
		for (int j = 0; j < length; j++)
			temp[j] = HCode[i].code[length - j - 1];
		for (int j = 0; j < length; j++)
			HCode[i].code[j] = temp[j];
	}
	cout << "�����Ϊ��" << endl;
	for (int i = 0; i < NUM; i++)//��������
		cout << "----" << HCode[i].data << "�ı���Ϊ��" << HCode[i].code << endl;
}
void Huffman::Encoding(char* encode, char* decode)//�û�õı�����ַ������б���
{
	Init(encode);//��ʼ��
	int length = strlen(encode);//��ȡ�ַ�������
	int count = 0;//�Ա��볤�Ƚ��м��㣬�Ա������ӽ�����
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			if (encode[i] == HCode[j].data)
			{
				int counts = 0;
				while (HCode[j].code[counts] != '\0')
				{
					decode[count] = HCode[j].code[counts];//���ձ������ַ����е�ÿ���ַ����б���
					count++;
					counts++;
				}
			}
		}
	}
	decode[count] = '\0';//�������λ����ӽ�����
}
void Huffman::Decoding(char* decode, char* encode)//����
{
	while (*decode != '\0')
	{
		int parent = 2 * NUM - 2;//��
		while (HTree[parent].lchild != -1)
		{
			if (*decode == '0')//�ж�Ϊ���ӻ����Һ���
				parent = HTree[parent].lchild;
			else
				parent = HTree[parent].rchild;
			decode++;
		}
		*encode = HCode[parent].data;//�ѱ������ַ��������е�ÿ�����ݰ��ձ������
		encode++;
	}
	*encode = '\0';//����������������ʱȷ����������
}
void Huffman::Six(char* encode, char* decode)//����ѹ���ȣ��ȽϹ�������ѹ��Ч��
{
	int s1 = strlen(encode);//�����ַ�������ǰ�ĳ���
	int s2 = strlen(decode);//�����ַ��������ĳ��ȣ������������������ȡ��
	if (s2 % 8 != 0)
	{
		s2 = s2 / 8 + 1;
		/*************************************************************
			Ϊ�˱�д��,�����ļ����ʱδ���õı�������ķ�ʽ,
			���������ֽ������ʽ,��ÿ���ֽڴ���һ�����֡�
			��������ļ���С������ֵ��8������˼���ѹ����ʱӦ�ó���8
		*************************************************************/
	}
	else
	{
		s2 = s2 / 8;
	}
	cout << "-----����ǰ����Ϊ��" << s1 << endl;
	cout << "-----����󳤶�Ϊ��" << s2 << endl;
	cout << "-----ѹ����Ϊ��" << double(100 * s2 / s1) << "%" << endl;//���
}
void Huffman::Print(char* list)//
{
	char kinds[1000] = { 0 };//�����ַ������ಢ���г�ʼ��
	int counts[1000] = { 0 };//����ÿ���ַ��ĸ��������г�ʼ�������ڲ�֪���ַ�������������������ô�һ��
	int length = strlen(list);//�õ��ַ����ĳ���
	if (length > 1000)
	{
		throw length;//������󳤶��׳�
	}
	int j = 0;
	for (int i = 0; i < length; i++)//����ÿ����ͬ�ַ���Ȩֵ
	{
		char c = list[i];//ȡ�ַ����е�ÿ���ַ�
		for (j = 0; j < NUM; j++)//�ж��ַ��Ƿ��ظ�
		{
			if (c == kinds[j])//ͳ���ַ�����
			{
				counts[j]++;
				break;
			}
		}
		if (j == NUM)//�������µ��ַ�����¼�ַ�����¼���ִ���+1
		{
			counts[j] = 1;
			kinds[j] = list[i];
			NUM++;
		}
	}
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "��ӡȨֵ��" << endl;
	for (int b = 0; b < NUM; b++)
	{
		cout << kinds[b];
		for (int j = 0; j < counts[b]; j++)
		{
			cout << "-";//��ӡ
		}
		cout << endl;
	}
	for (int i = 0; i < NUM; i++)//��������
	{
		cout << " " << HCode[i].data;
		int j = 0;
		while (HCode[j].code[j] != '\0')
		{
			j++;
			cout << "-";
		}
		cout << endl;
	}
}
void Huffman::print()//��ӡ��������
{
	cout << "��ӡ��������(�����Ϊ��Ҫ����)��" << endl;
	for (int i = 0; i < NUM; i++)//��ӡ����������������ȴ�ӡ
	{
		cout << " " << HCode[i].data;
		int j = 0;
		while (HCode[i].code[j] != '\0')
		{
			j++;
			cout << "-";
		}
		cout << endl;
	}
}
Huffman::~Huffman()//��������
{
	delete[]HTree;
	delete[]HCode;
}
void Setting()//����ʽ�������
{
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------         �˵�         ----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------   A. ���빦�ܲ���    ----------------------------------------------------" << endl;
	cout << "---------------------------------------------   B. ���뽻������    ----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "ѡ����Ҫ���еĲ�����";
}
void j(char* t,char*a,char*b)
{
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "�����ַ���Ϊ��" << t << endl;
	//j(t,a,b);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "������Ϊ��" << a << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "������Ϊ��" << b << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}
int main()
{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "-----------------------------------------------�������㷨��������------------------------------------------------------" << endl;
Function:
	Setting();
	Huffman Test;
	char s[1000] = { '\0' }, a[1000] = { '\0' }, b[1000] = { '\0' };
	char fun;
	cin >> fun;
	cin.ignore();
	if (fun == 'A')
	{
		char text[] = "I love data Structure, I love Computer. I will try my best to study data Structure.";
		char* t = text;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		Test.Encoding(t, a);
		Test.Decoding(a, b);
		j(t, a, b);
		Test.print();
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		Test.Six(t, a);
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl;
	}
	else
	{
		try
		{
			cout << "�������ַ���";
			cin.getline(s, 1000, '\n');
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			Test.Encoding(s, a);
			Test.Decoding(a, b);
			j(s,a,b);
			Test.print();
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			Test.Six(s, a);
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl;
		}
		catch (int m)
		{
			cout << "�ַ�������Ϊ" << m << ">1000 overflow" << endl;//�쳣����
		}
	}
	char WHAT;
	cout << "�Ƿ����ִ�г���(Y or N)��" << endl;
	cin >> WHAT;
	cin.ignore();
	if (WHAT == 'Y')
	{
		goto Function;
	}
}
