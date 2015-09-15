// Apriori.cpp : �������̨Ӧ�ó������ڵ㡣
/*
������������:
9 5
0 1 4 -1
1 3 -1
1 2 -1
0 1 3 -1
0 2 -1
1 2 -1
0 2 -1
0 1 2 4 -1
0 1 2 -1
2
*/
//

#include "stdafx.h"
#include<cstdio>
#include<iostream>
#include<Windows.h>
#include<algorithm>
#include<queue>
#include<fstream>
#define MAX_SET 1000
using namespace std;

struct STATUS//��ʾһ������
{
	int sum;//��ʾ�������ж��ٸ�Ԫ��
	DWORD set;
	int support;
}status_total[MAX_SET];
int sumStu = 0;//ĿǰƵ����ĸ���
priority_queue<STATUS>status;

bool data[500][32] = { 0 };
int N, sumElement,minSupport;
/*
bool sortCmp(STATUS a, STATUS b)//����sort�����ıȽϣ���status��������
{
	if (a.sum != b.sum)
	{
		return a.sum<b.sum;
	}
	return a.set > b.set;
}
*/
bool operator < (STATUS a, STATUS b)//�������ȶ��е�����
{
	if (a.sum != b.sum)
	{
		return a.sum < b.sum;
	}
	return a.set>b.set;
}

void copyToArray()//�����ȶ������Ԫ�ظ��ƽ�����Ƶ���������status_total��
{
	while (!status.empty())
	{
		status_total[sumStu++] = status.top();
		status.pop();
	}
}

void initStatus()
{
	int i, j;
	int tempArray[32] = { 0 };
	STATUS temp;
	temp.sum = 1;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < sumElement; j++)
		{
			if (data[i][j])
			{
				tempArray[j]++;

			}
		}
	}
	for (i = 0; i < sumElement; i++)
	{
		if (tempArray[i] >= minSupport)
		{
			temp.set = 1 << i;
			temp.support = tempArray[i];
			status.push(temp);
		}
	}
	copyToArray();
}

void printStatus()
{
	/*
	STATUS temp;
	while (!status.empty())
	{
		temp = status.top();
		status.pop();
		cout << temp.sum<<':';
		for (int i = 0; i < 32; i++)
		{
			if (temp.set & (1 << i))
				cout << i << ' ';
		}
		cout << endl;
	}
	*/
	
	for (int i = 0; i < sumStu; i++)
	{
		cout << "sum:" << status_total[i].sum << " support:" << status_total[i].support<<" member:";
		for (int j = 0; j < sumElement; j++)
		{
			if (status_total[i].set&(1 << j))
			{
				cout << j << ' ';
			}
		}
		cout << endl;
	}
}

bool checkSubset(DWORD set)//��鼯��set�Ƿ�����ڵ�ǰ��֪��Ƶ�����
{
	for (int i = 0; i < sumStu; i++)
	{
		if (status_total[i].set == set)
			goto exist;
	}
	return false;
exist:
	return true;
}

int createSubset(DWORD originalSet, DWORD currentSet, int offset)//offset��ʾ�����������ɵ�offsetλԪ�ص��Ӽ�,����ݹ�Ĺ������к�������1�����ʾ�Ӽ�������Apriori����
{
	if (offset == sumElement)
	{
		if (originalSet == currentSet||currentSet==0)
		{
			return 0;
		}
		else
		{
			if (checkSubset(currentSet))
				return 0;
			else
				return 1;
		}
	}
	if (originalSet&(1 << offset))
	{
		if (createSubset(originalSet, currentSet, offset + 1))
			return 1;
		if (createSubset(originalSet, currentSet ^ (1 << offset), offset + 1))
			return 1;
	}
	else 
		if (createSubset(originalSet, currentSet, offset + 1))
			return 1;
	return 0;
}

bool checkLink(DWORD set1, DWORD set2, int n)//����l1[n]=l2[n],l1[n-1]=l2[n-1]����l1[1]>l2[1]�򼯺Ͽ�����
{
	int i,cur=0;
	for (i = sumElement - 1; i >= 0; i++)
	{
		if ((set1&(1 << i)) ^ (set2&(1 << i)))//��鼯�ϵ�iλ��ֵ�Ƿ����
		{//��������
			if (cur != n - 1)
			{
				return false;
			}
			else return true;
		}
		if (set1&(1 << i))
		{
			cur++;
		}
	}
}

int calcSupport(DWORD set)//����set���ϵ�֧�ֶ�
{
	int support = 0, i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < sumElement; j++)
		{
			//if (!(set&(1 << j) && data[i][j]))
			if (set&(1 << j))
			{
				if (!data[i][j])
					break;
			}
		}
		if (j == sumElement)
			support++;
	}
	return support;
}

bool apriori(int n)//ͨ��nƵ�������n+1Ƶ���
{
	int i,j;
	STATUS temp;
	for (i = sumStu - 1; i >= 0; i--)
	{
		if (status_total[i].sum != n)
			break;
		for (j = i - 1; j >= 0; j--)
		{
			if (status_total[j].sum != n)
				break;
			if (checkLink(status_total[i].set, status_total[j].set, n))
			{
				temp.set = status_total[i].set | status_total[j].set;
				temp.sum = n + 1;
				if (!createSubset(temp.set, temp.set, 0))
				{
					temp.support = calcSupport(temp.set);
					if (temp.support >= minSupport)
						status.push(temp);
				}
			}
		}
	}
	if (status.empty())
		return false;
	copyToArray();
	return true;
}

bool compare(STATUS a, STATUS b)//����sort������Ƶ�����֧�ֶȽ�������
{
	return a.support > b.support;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//ifstream cin("F:\\D�̱���\\���й�������\\���ݽṹ���㷨 ������ҵ\\Apriori�㷨\\Apriori\\testdata.txt");
	//ofstream cout("D:\\1.txt");
	int i, j, k, temp, n;
	cout << "�����뼯���Լ�����Ԫ�ص��ܸ���"<<endl;
	cin >> N >> sumElement;
	cout << "�����뼯�ϣ���0-31�����ֱ�ʾ��ͬ�ļ���Ԫ�أ�ͬһ�����ϲ�ͬԪ���ÿո����������-1��ʾ�ü��Ͻ�������" << endl;
	for (i = 0; i < N; i++)
	{
		while (1)
		{
			cin >> temp;
			if (temp == -1)
			{
				break;
			}
			data[i][temp] = true;
		}
	}
	cout << "��������С֧����ֵ" << endl; 
	cin >> minSupport;

	initStatus();

	for (i = 1; 1; i++)
	{
		if (!apriori(i))
			break;
	}

	sort(status_total, status_total + sumStu, compare);
	printStatus();
	return 0;
}

