﻿// ConsoleApplication4.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int gauss(vector < vector<double> > c, int NumOfVector)
{
	double EPS = 1E-9;
	int n = NumOfVector;
	int m = (int)c[0].size();
	vector < vector<double> > a = c; //원 벡터가 변하지 않도록 새 벡터에 Gauss-Jordan 수행.
	int row = 0;
	int col = 0;
	while (row < n && col < m)		//row by row로 col을 pivot으로 left triangle을 제거.
	{
		for (int currentrow = row; currentrow < n; currentrow++) //row 아래 행 중 가장 큰 행을 row로.
		{
			if (abs(a[currentrow][col]) < EPS)
				continue;
			if (abs(a[currentrow][col]) > abs(a[row][col]))
			{
				a[row].swap(a[currentrow]);
			}
		}
		if (abs(a[row][col]) < EPS) {			//나눗셈에 의한 작은 수 방지.
			a[row][col] = 0;
			col++;
			continue;
		}
		for (int currentrow = row + 1; currentrow < n; currentrow++) //row+1행부터 아래로 소거
		{
			double tmp = a[currentrow][col] / a[row][col];
			for (int currentcol = col; currentcol < m; currentcol++) //col열부터 오른쪽으로 소거.
			{
				if (currentcol == col)
				{
					a[currentrow][currentcol] = 0;
					continue;
				}
				a[currentrow][currentcol] -= a[row][currentcol] * tmp;
				if (abs(a[currentrow][currentcol]) < EPS) {		//작은 수 또 방지
					a[currentrow][currentcol] = 0;
				}
			}
		}

		row++;
		col++;
	}

	/*
	printf("---after gauss---\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%f ", a[i][j]);
		printf("\n");
	}*/
	int isindependent = 0;

	for (int i = 0; i < n; i++) //각 row별로 0이 아닌 값이 있는지 체크해 isindependent에 +1.
	{
		int tmp = 0;
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] != 0) //잘 돌아갈까... => 잘 돌아간다
				tmp++;
		}
		if (tmp != 0)
			isindependent++;
	}
	if (isindependent == n) //if all rows have at least one non zero value(isindependent = 1), it is independent. -> return 1
		return 1;
	else
		return 0;

}

void NCR(int N, int K, vector<vector<double>>B)
{
	int NCR = (1 << K) - 1;       // k bit sets
	while (NCR < 1 << N) {

		vector <double> nothing;
		vector <double> temp(B[0].size());

		int B_INDEX = 0;
		vector<double> temp_vector(B[0].size());

		//행렬 만들기
		vector <vector<double>>BB(K, temp);
		for (int i = 0; i < N; ++i) {
			if ((NCR >> i) & 1)
			{
				BB[B_INDEX] = B[i];
				B_INDEX++;
			}

		}


			for (int extra = 0; extra < K; extra++)
			{
				std::cout << "벡터 ";
				for (int z = 0; z < BB[0].size(); z++)
				{
					std::cout << BB[extra][z] << "  ";
				}
				if ((extra + 1) != K)
				{
					std::cout << "와 ";
				}
			}
		if (gauss(BB, (int)BB.size()))
		std::cout << "는 독립이다. \n" << endl;
		else
			std::cout << "는 독립이 아니다. \n" << endl;


		BB.clear();
		int x = NCR & -NCR;
		int y = NCR + x;
		int z = (NCR & ~y);
		NCR = z / x;
		NCR >>= 1;
		NCR |= y;
	}
}


int main()
{

	int NumOfVector ;

	cout << "입력 할 벡터의 개수 \n" << endl;
	cin >> NumOfVector;

	int input;
	vector<vector<double> > v;
	cout << " \n 벡터를 입력 해 주세요 ! \n" << endl;

	for (int i = 0; i < NumOfVector; i++)
	{
		vector<double> temp;
		while (1)
		{
			cin >> input;
			temp.push_back(input);
			if (cin.get() == '\n')
				break;
		}

		v.push_back(temp);
	}


		int NumberOfVectors = 2;
		int numofcycles = 0;

		while (NumberOfVectors <= NumOfVector)
		{
			//nCr 만큼 비교 
			NCR(NumOfVector, NumberOfVectors,v); // params 총 개수 / 비교할 개수 / 이중 벡터

			NumberOfVectors++;
		}

	return 0;
}

