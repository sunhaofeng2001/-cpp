#include<iostream>
using namespace std;
struct RESULT {
	char ch;
	int num;
};
void CountChar1(char* s, RESULT r[], int& n)
{
	n = 0;
	while (*s != '\0')
	{
		int i;
		for (i = 0; i < n; i++)
		{
			if (r[i].ch == *s)
			{
				r[i].num++;
				break;
			}
		}
		if (i == n)
		{
			r[n].ch = *s;
			r[n].num = 1;
			n++;
		}
		s++;
	}
}
int main()
{
	RESULT r[128];
	char s[] = "This is a problem which can be solved by data structure method.";
	int n = 0;
	CountChar1(s, r, n);
	for (int i = 0; i < n; i++)
		cout << r[i].ch << ":" << r[i].num << endl;
}