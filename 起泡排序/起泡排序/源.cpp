/******************************
	��Ӧ�̲��� 1-3����������
*******************************/
#include <iostream>
#include <ctime>
#include <cmath>
#include <cassert>
using namespace std;

void BubbleSort(int* r, int n);
void QuickSort(int* data, int first, int last);
int Partition(int* data, int first, int last);
int* generateRadomArray(int n, int rangeL, int rangeR);

int main()
{
	int i = 4;
	int n = pow(10, i);                  //����������ݹ�ģ
	clock_t startTime, endTime;
	int* arr = generateRadomArray(n, 0, n);
	startTime = clock();
	BubbleSort(arr, n);
	endTime = clock();
	cout << "data size: " << n << endl;
	cout << "Time cost: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	startTime = clock();
	QuickSort(arr, 0, n - 1);
	endTime = clock();
	cout << "data size: " << n << endl;
	cout << "Time cost: " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	delete[] arr;
	return 0;
}

void BubbleSort(int* r, int n)
{
	int temp, bound, exchange = n - 1;
	while (exchange != 0)
	{
		bound = exchange;
		exchange = 0;
		for (int j = 0; j < bound; j++)  //��������[1,bound] 
			if (r[j] > r[j + 1])
			{
				temp = r[j]; r[j] = r[j + 1];	r[j + 1] = temp;
				exchange = j;
			}
	}
}

int Partition(int* data, int first, int last)
{
	int i = first, j = last, temp;              //��ʼ��һ�λ��ֵ�����
	while (i < j)
	{
		while (i < j && data[i] <= data[j])
			j--;      //�Ҳ�ɨ��
		if (i < j) {
			temp = data[i];	data[i] = data[j]; data[j] = temp;
			i++;
		}
		while (i < j && data[i] <= data[j])
			i++;     //���ɨ��
		if (i < j) {
			temp = data[i]; data[i] = data[j]; data[j] = temp;
			j--;
		}
	}
	return i;           // iΪ��ֵ��¼������λ��
}

void QuickSort(int* data, int first, int last)
{
	if (first >= last)
		return;                            //���䳤��Ϊ1���ݹ����
	else
	{
		int pivot = Partition(data, first, last);     //һ�λ���
		QuickSort(data, first, pivot - 1);         //����������н��п�������
		QuickSort(data, pivot + 1, last);         //���Ҳ������н��п�������	
	}
}

int* generateRadomArray(int n, int rangeL, int rangeR)
{
	assert(n > 0 && rangeL <= rangeR);     	//���Դ��� 
	int* arr = new int[n];                      //���ݹ�ģΪn
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
	}
	return arr;
}








