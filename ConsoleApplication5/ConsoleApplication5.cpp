// ConsoleApplication4.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <vector>

#include <limits>

using namespace std;


int gauss(vector < vector<double> > a, vector<double> & ans) {
	double EPS = 1E-15;
	int n = (int)a.size();
	int m = (int)a[0].size() - 1;

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; ++col) {
		int currentROW = row;
		for (int i = row; i < n; ++i)
			if (abs(a[i][col]) > abs(a[currentROW][col]))
				currentROW = i;
		if (abs(a[currentROW][col]) < EPS)
			continue;
		for (int i = col; i <= m; ++i)
			swap(a[currentROW][i], a[row][i]);
		where[col] = row;

		for (int i = 0; i < n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j = col; j <= m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	ans.assign(m, 0);
	for (int i = 0; i < m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i = 0; i < n; ++i) {
		double sum = 0;
		for (int j = 0; j < m; ++j)
			sum += ans[j] * a[i][j];
		if (abs(sum - a[i][m]) > EPS)
			return 0;
	}

	for (int i = 0; i < m; ++i)
		if (where[i] == -1)
		{
			//printf("%f \n", where[i]);
			return std::numeric_limits<int>::max();;
		}
	return 1;
}


int main()
{

	printf("입력할 벡터의 개수를 미리 입력해주세요 (m)\n");
	int NumOfVector;
	cin >> NumOfVector;
	int vector_space;
	printf("입력할 벡터의 공간을 미리 입력해주세요 (n)\n");
	cin >> vector_space;

	printf("확인할 벡터를 한칸씩 띄워서 입력해 주세요\n");


	//벡터 초기화
	vector <double> a(vector_space);
	//행렬 만들기
	vector <vector<double>>B(NumOfVector, a);

	for (int i = 0; i < NumOfVector; i++)
	{
		for (int j = 0; j < vector_space; j++)
			cin >> B[i][j];
	}
	vector_space = a.size();

	double tiny = 1E-15;
	vector <double> answer(vector_space);
	int infinity = std::numeric_limits<int>::max();
	int isdependent;


	if (vector_space >= NumOfVector)
	{
		bool check;
		bool checking = false;
		int NumOfVectors = 2;
		isdependent = gauss(B, answer);
		if (isdependent == infinity || isdependent == 1)
			check = false;
		else
			check = true;

		if (check == false)
		{
			for (int j = 0; j < NumOfVector; j++)
			{
				for (int i = 0; i < NumOfVector; i++)
				{
					if (B[i] == B[j])
						continue;

					cout << "벡터 ";
					for (int z = 0; z < vector_space; z++)
					{
						cout << B[i][z] << " ";
					}
					cout << "와 ";
					cout << "벡터 ";
					for (int z = 0; z < vector_space; z++)
					{
						cout << B[j][z] << " ";
					}
					cout << "는 독립이다."<< endl;
				}

			}

		}
		else
		{
			for (int j = 0; j < NumOfVector; j++)
			{
				for (int i = 0; i < NumOfVector; i++)
				{
					if (B[i] == B[j])
						continue;

					cout << "벡터 ";
					for (int z = 0; z < vector_space; z++)
					{
						cout << B[i][z] << " ";
					}
					cout << "와 ";
					cout << "벡터 ";
					for (int z = 0; z < vector_space; z++)
					{
						cout << B[j][z] << " ";
					}
					cout << "는 독립이 아니다." << endl;

				
				}
			}
		}
	}

	else
	{
		int NumberOfVectors = 2;

		while (NumberOfVectors < NumOfVector)
		{

			int index = 0;
			for (int ii = 0; ii < NumberOfVectors; ii++)
			{
				for (int jj = 0; jj < NumberOfVectors; jj++)
				{
					vector <double> temp(a.size());
					//행렬 만들기
					vector <vector<double>>BB(NumberOfVectors, temp);
					if (B[ii+jj] == B[index])
						continue;
					BB[jj] = B[ii+jj];
					BB[ii] = B[index];
					if (NumberOfVectors > 2)
					{
						for (int extra = 2; extra < NumberOfVectors; extra++)
						{
							if (BB[extra] != BB[ii] || BB[extra] != BB[jj])
								BB[extra] = B[extra];
						}
					}

					isdependent = gauss(BB, answer);

					bool check;
					if (isdependent == infinity || isdependent == 1)
					{
						printf("----check==true----\n");

						for (int z = 0; z < vector_space; z++)
						{
							printf("[jj][z] %f \n", BB[jj][z]);
							printf("[ii][z] %f \n", BB[ii][z]);
						}
						printf("-------------");
						check = true;
					}
					else
					{
							printf("----check==false----\n");
						for (int z = 0; z < vector_space; z++)
						{
							printf("[jj] %f \n", BB[jj][z]);
							printf("[ii] %f \n", BB[ii][z]);
						}
						printf("-------------");
						check = false;
					}
				
					
					if (check == true)
					{

						cout << "벡터 ";
						for (int z = 0; z < vector_space; z++)
						{
							cout << BB[ii][z] << " ";
						}
						cout << "와 ";
						cout << "벡터 ";
						for (int z = 0; z < vector_space; z++)
						{
							cout << BB[jj][z] << " ";
						}
						cout << "와 ";
						if (NumberOfVectors > 2)
						{
							for (int extra = 2; extra < NumberOfVectors; extra++)
							{
								if (BB[extra] != BB[ii] || BB[extra] != BB[jj])
								{

									for (int z = 0; z < vector_space; z++)
									{
										cout << BB[extra][z] << " ";
									}
									cout << "와 ";
									cout << "벡터 ";

								}

							}
						}
						cout << "는 독립이다. \n"<< endl;
					}
					else
					{
						cout << "벡터 ";
						for (int z = 0; z < vector_space; z++)
						{
							cout << BB[ii][z] << " ";
						}
						cout << "와 ";
						cout << "벡터 ";
						for (int z = 0; z < vector_space; z++)
						{
							cout << BB[jj][z] << " ";
						}
						cout << "와 ";
						if (NumberOfVectors > 2)
						{
							for (int extra = 2; extra < NumberOfVectors; extra++)
							{
								if (BB[extra] != BB[ii] || BB[extra] != BB[jj])
								{
									for (int z = 0; z < vector_space; z++)
									{
										cout << BB[extra][z] << " ";
									}
									cout << "와 ";
									cout << "벡터 ";

								}

							}
						}
						cout << "는 독립이 아니다. \n";
					}
					index++;

				}
			}
			NumberOfVectors++;
		}


	}
	return 0;
}


