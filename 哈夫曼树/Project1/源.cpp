#include<iostream>
#include<cstring>
#include<string>
using namespace std;
void Setting(int i);
struct hnode {
	int parent;//定义父节点
	int lchild;//定义左孩子
	int rchild;//定义右孩子
	int weight;//定义权重
};
struct hcode {
	char data;//定义数据域
	char code[100];//定义储存编码单位
};
class Huffman//定义哈夫曼类
{
private:
	hnode* HTree;//定义树类的基本属性
	hcode* HCode;//定义数据域和编码
	int NUM;//定义结点个数
public:
	Huffman();//构造函数
	void Init(char* list);//初始化
	void CreateHTree(int list[], int num);//建立哈夫曼树；
	void CreateTable(char dic_list[], int num);//创建编码表
	void Encoding(char* encode, char* decode);//编码函数
	void Decoding(char* encode, char* decode);//解码函数
	void SelectMin(int& x, int& y, int begin, int end);//获得权值最小的两个结点的位置
	void Six(char* encode, char* decode);//计算压缩比
	void Print(char* list);//图形打印权值
	void print();//打印哈夫曼树
	~Huffman();//析构函数
};
Huffman::Huffman()//构造
{
	HTree = NULL;//初始化
	HCode = NULL;//初始化
	NUM = 0;//初始化
}
void Huffman::Init(char* list)//
{
	char kinds[1000] = { 0 };//储存字符的种类并进行初始化
	int counts[1000] = { 0 };//储存每个字符的个数并进行初始化，由于不知道字符种类数，所以数组最好大一点
	int length = strlen(list);//得到字符串的长度
	if (length > 1000)
	{
		throw length;//超出最大长度抛出
	}
	int j = 0;
	for (int i = 0; i < length; i++)//计算每个不同字符的权值
	{
		char c = list[i];//取字符串中的每个字符
		for (j = 0; j < NUM; j++)//判断字符是否重复
		{
			if (c == kinds[j])//统计字符个数
			{
				counts[j]++;
				break;
			}
		}
		if (j == NUM)//若出现新的字符，记录字符并记录出现次数+1
		{
			counts[j] = 1;
			kinds[j] = list[i];
			NUM++;
		}
	}
	CreateHTree(counts, NUM);//创建哈夫曼树
	CreateTable(kinds, NUM);//创建编码表
}
void Huffman::SelectMin(int& x, int& y, int begin, int end)//（补全课本中未给出的代码）寻找权重最小的两个数的位置
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
			continue;//若是和之前的一样，则跳过
		}
		if (HTree[i].weight < HTree[x].weight)
		{
			x = i;
		}
	}
	HTree[x].parent = -2;//将x结点的parent设为不可能取到的值防止重复
	while (HTree[y].parent != -1)
	{
		y++;
	}
	for (int j = 1; j < end; j++)
	{
		if (HTree[j].parent != -1)//防止x和y重复
		{
			continue;
		}
		if (HTree[j].weight < HTree[y].weight)
		{
			y = j;
		}
	}
}
void Huffman::CreateHTree(int list[], int num)//创建哈夫曼树
{
	HTree = new hnode[2 * num - 1];//申请结点neicun
	for (int i = 0; i < num; i++)
	{
		HTree[i].weight = list[i];//得到权值
		HTree[i].lchild = -1;//初始化
		HTree[i].rchild = -1;
		HTree[i].parent = -1;
	}
	int x, y;//数据中最小的两个数
	for (int i = num; i < 2 * num - 1; i++)
	{
		SelectMin(x, y, 0, i);//获取结点最小值
		HTree[x].parent = HTree[y].parent = i;//生成哈夫曼树的每个结点
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].lchild = x;
		HTree[i].rchild = y;
		HTree[i].parent = -1;
	}
}
void Huffman::CreateTable(char list[], int num)//建立编码表
{
	HCode = new hcode[num];//申请空间
	for (int i = 0; i < num; i++)//建立编码表
	{
		HCode[i].data = list[i];//将每个不同的字符赋值到编码表的数据域
		int CNUM = i;
		int p = HTree[i].parent;
		int k = 0;
		while (p != -1)//进行编码(获得的为编码的倒序)
		{
			if (CNUM == HTree[p].lchild)//判断左孩子还是又孩子
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
	cout << "编码表为：" << endl;
	for (int i = 0; i < NUM; i++)//输出编码表
		cout << "----" << HCode[i].data << "的编码为：" << HCode[i].code << endl;
}
void Huffman::Encoding(char* encode, char* decode)//用获得的编码对字符串进行编码
{
	Init(encode);//初始化
	int length = strlen(encode);//获取字符串长度
	int count = 0;//对编码长度进行计算，以便对其添加结束符
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			if (encode[i] == HCode[j].data)
			{
				int counts = 0;
				while (HCode[j].code[counts] != '\0')
				{
					decode[count] = HCode[j].code[counts];//按照编码表对字符串中的每个字符进行编码
					count++;
					counts++;
				}
			}
		}
	}
	decode[count] = '\0';//编码结束位置添加结束符
}
void Huffman::Decoding(char* decode, char* encode)//解码
{
	while (*decode != '\0')
	{
		int parent = 2 * NUM - 2;//从
		while (HTree[parent].lchild != -1)
		{
			if (*decode == '0')//判断为左孩子还是右孩子
				parent = HTree[parent].lchild;
			else
				parent = HTree[parent].rchild;
			decode++;
		}
		*encode = HCode[parent].data;//把编码后的字符串数组中的每个数据按照编码表反译
		encode++;
	}
	*encode = '\0';//译码结束，方便调用时确定结束条件
}
void Huffman::Six(char* encode, char* decode)//计算压缩比，比较哈夫曼的压缩效果
{
	int s1 = strlen(encode);//计算字符串编码前的长度
	int s2 = strlen(decode);//计算字符串编码后的长度，如果不能整除则向上取整
	if (s2 % 8 != 0)
	{
		s2 = s2 / 8 + 1;
		/*************************************************************
			为了编写简单,编码文件输出时未采用的比特输出的方式,
			而采用了字节输出方式,即每个字节代表一个码字。
			这样输出文件大小是理论值的8倍。因此计算压缩率时应该除以8
		*************************************************************/
	}
	else
	{
		s2 = s2 / 8;
	}
	cout << "-----编码前长度为：" << s1 << endl;
	cout << "-----编码后长度为：" << s2 << endl;
	cout << "-----压缩比为：" << double(100 * s2 / s1) << "%" << endl;//输出
}
void Huffman::Print(char* list)//
{
	char kinds[1000] = { 0 };//储存字符的种类并进行初始化
	int counts[1000] = { 0 };//储存每个字符的个数并进行初始化，由于不知道字符种类数，所以数组最好大一点
	int length = strlen(list);//得到字符串的长度
	if (length > 1000)
	{
		throw length;//超出最大长度抛出
	}
	int j = 0;
	for (int i = 0; i < length; i++)//计算每个不同字符的权值
	{
		char c = list[i];//取字符串中的每个字符
		for (j = 0; j < NUM; j++)//判断字符是否重复
		{
			if (c == kinds[j])//统计字符个数
			{
				counts[j]++;
				break;
			}
		}
		if (j == NUM)//若出现新的字符，记录字符并记录出现次数+1
		{
			counts[j] = 1;
			kinds[j] = list[i];
			NUM++;
		}
	}
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "打印权值：" << endl;
	for (int b = 0; b < NUM; b++)
	{
		cout << kinds[b];
		for (int j = 0; j < counts[b]; j++)
		{
			cout << "-";//打印
		}
		cout << endl;
	}
	for (int i = 0; i < NUM; i++)//输出编码表
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
void Huffman::print()//打印哈夫曼树
{
	cout << "打印哈夫曼树(以深度为主要依据)：" << endl;
	for (int i = 0; i < NUM; i++)//打印哈夫曼树；根据深度打印
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
Huffman::~Huffman()//析构函数
{
	delete[]HTree;
	delete[]HCode;
}
void Setting()//交互式界面设计
{
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------         菜单         ----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "---------------------------------------------   A. 代码功能测试    ----------------------------------------------------" << endl;
	cout << "---------------------------------------------   B. 进入交互界面    ----------------------------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "选择需要进行的操作：";
}
void j(char* t,char*a,char*b)
{
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "测试字符串为：" << t << endl;
	//j(t,a,b);
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "编码结果为：" << a << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "解码结果为：" << b << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}
int main()
{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "-----------------------------------------------哈夫曼算法编译码器------------------------------------------------------" << endl;
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
			cout << "请输入字符：";
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
			cout << "字符串长度为" << m << ">1000 overflow" << endl;//异常处理
		}
	}
	char WHAT;
	cout << "是否继续执行程序(Y or N)？" << endl;
	cin >> WHAT;
	cin.ignore();
	if (WHAT == 'Y')
	{
		goto Function;
	}
}
