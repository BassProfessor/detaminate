#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
int triple_det(vector<vector<int>> &a);
vector<vector<int>> get_lower_det(vector<vector<int>> a, int row, int column);
int get_det_result(vector<vector<int>> a);
int main()
{
	int line;
	cout << "enter the n to create the det.\nn = ";
	cin >> line;
	vector<vector<int>>det(line, vector<int>(line));
	cout << "enter the det(from line 1 to line " << line << "):" << endl;
	for (int j = 0; j < line; j++)
	{
		for (int i = 0; i < line; i++)
		{
			int a;
			cin >> a;
			det[j][i] = a;
		}
	}
	if (line == 2)
	{
		int result = det[0][0] * det[1][1] - det[0][1] * det[1][0];
		cout << "the resule is " << result << endl;
	}
	else if (line == 3)
		cout << "the result is " << triple_det(det) << endl;
	else
	{
		cout << "the result is " << get_det_result(det) << endl;
	}
	cin.get();
	cin.get();
	return 0;
}
int triple_det(vector<vector<int>> &a)
{
	int total = 0;
	for (int i = 0; i <= 2; i++)
	{
		total += a[0][i % 3] * a[1][(i + 1) % 3] * a[2][(i + 2) % 3];
	}
	for (int i = 2; i <= 4; i++)
	{
		total -= a[0][i % 3] * a[1][(i - 1) % 3] * a[2][(i - 2) % 3];
	}
	return total;
}
vector<vector<int>> get_lower_det(vector<vector<int>> a, int row, int column)
{
	vector<vector<int>>dett(a.size() - 1, vector<int>(a.size() - 1));
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < column; i++)
		{
			dett[j][i] = a[j][i];
		}
	}
	for (int j = row + 1; j < a.size(); j++)
	{
		for (int i = column + 1; i < a.size(); i++)
		{
			dett[j - 1][i - 1] = a[j][i];
		}
	}
	return dett;
}
int get_det_result(vector<vector<int>> a)
{
	int total = 0;
	for (int j = 0; j < a.size(); j++)
	{
		for (int i = 0; i < a.size(); i++)
		{
			int time = pow((-1.0), i + j) * a[j][i];
			vector<vector<int>> lower = get_lower_det(a, j, i);
			if(lower.size() == 3)
				total += triple_det(lower) * time * get_det_result(a);
		}
	}
	return total;
}
