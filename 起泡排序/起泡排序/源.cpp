/******************************
	对应教材例 1-3，排序问题
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
	int n = pow(10, i);                  //待排序的数据规模
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
		for (int j = 0; j < bound; j++)  //排序区间[1,bound] 
			if (r[j] > r[j + 1])
			{
				temp = r[j]; r[j] = r[j + 1];	r[j + 1] = temp;
				exchange = j;
			}
	}
}

int Partition(int* data, int first, int last)
{
	int i = first, j = last, temp;              //初始化一次划分的区间
	while (i < j)
	{
		while (i < j && data[i] <= data[j])
			j--;      //右侧扫描
		if (i < j) {
			temp = data[i];	data[i] = data[j]; data[j] = temp;
			i++;
		}
		while (i < j && data[i] <= data[j])
			i++;     //左侧扫描
		if (i < j) {
			temp = data[i]; data[i] = data[j]; data[j] = temp;
			j--;
		}
	}
	return i;           // i为轴值记录的最终位置
}

void QuickSort(int* data, int first, int last)
{
	if (first >= last)
		return;                            //区间长度为1，递归结束
	else
	{
		int pivot = Partition(data, first, last);     //一次划分
		QuickSort(data, first, pivot - 1);         //对左侧子序列进行快速排序
		QuickSort(data, pivot + 1, last);         //对右侧子序列进行快速排序	
	}
}

int* generateRadomArray(int n, int rangeL, int rangeR)
{
	assert(n > 0 && rangeL <= rangeR);     	//断言处理 
	int* arr = new int[n];                      //数据规模为n
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
	}
	return arr;
}








