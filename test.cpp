#include<iostream>
#include<vector>
#include<cmath>
#include <iomanip>
using namespace std;
float triple_det(vector<vector<float>> a);
vector<vector<float>> get_lower_det(vector<vector<float>> a, int row, int column);
float get_det_result(vector<vector<float>> a);
void show_det(vector<vector<float>> a);
vector<vector<float>> get_transport_martix(vector<vector<float>> a);
vector<vector<float>> get_inverse_martix(vector<vector<float>> a);
int main()
{
	int line;
	cout << "enter the n to create the det.\nn = ";
	cin >> line;
	vector<vector<float>>det(line, vector<float>(line));
	cout << "enter the det(from line 1 to line " << line << "):" << endl;
	for (int j = 0; j < line; j++)
	{
		for (int i = 0; i < line; i++)
		{
			float a;
			cin >> a;
			det[j][i] = a;
		}
	}
	if (line == 2)
	{
		float result = det[0][0] * det[1][1] - det[0][1] * det[1][0];
		cout << "the resule is " << result << endl;
	}
	else if (line == 3)
		cout << "the result is " << triple_det(det) << endl;
	else
	{
		cout << "the result is " << get_det_result(det) << endl;
		cout << "the transport martix is"<<endl;
		show_det(get_transport_martix(det));
		cout << "the inverse martix is" << endl;
		show_det(get_inverse_martix(det));
	}
	cin.get();
	cin.get();
	return 0;
}
float triple_det(vector<vector<float>> a)
{
	float total = 0;
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
vector<vector<float>> get_lower_det(vector<vector<float>> a, int row, int column)
{
	vector<vector<float>>dett(a.size() - 1, vector<float>(a.size() - 1));
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < column; i++)
		{
			dett[j][i] = a[j][i];
		}
		for (int i = column + 1; i < a.size(); i++)
		{
			dett[j][i - 1] = a[j][i];
		}
	}
	for (int j = row + 1; j < a.size(); j++)
	{
		for (int i = 0; i < column; i++)
		{
			dett[j - 1][i] = a[j][i];
		}
		for (int i = column + 1; i < a.size(); i++)
		{
			dett[j - 1][i - 1] = a[j][i];
		}
	}
	return dett;
}
float get_det_result(vector<vector<float>> a)
{
	float total = 0;
	for (int j = 0; j < a.size(); j++)
	{
		float time = pow((-1.0), 0 + j) * a[0][j];
		vector<vector<float>> lower = get_lower_det(a, 0, j);
		if (lower.size() == 3)
		{
			total += time * triple_det(lower);
		}
		else
		{
			int sum = time * get_det_result(lower);
			total += sum;
		}
	}
	return total;
}
void show_det(vector<vector<float>> a)
{
	for (int j = 0; j < a.size(); j++)
	{
		for (int i = 0; i < a.size(); i++)
		{
			cout.setf(ios::fixed, ios::floatfield);
			cout << a[j][i] << " ";
		}
		cout << endl;
	}
}
vector<vector<float>> get_transport_martix(vector<vector<float>> a)
{
	vector<vector<float>>trans_det(a.size(), vector<float>(a.size()));
	for (int j = 0; j < a.size(); j++)
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a.size() == 4)
			{
				float times = pow((-1.0), i + j);
				trans_det[i][j] = times * triple_det(get_lower_det(a, j, i));
			}
			else
			{
				float times = pow((-1.0), i + j);
				trans_det[i][j] = times * get_det_result(get_lower_det(a, j, i));
			}
		}
	}
	return trans_det;
}
vector<vector<float>> get_inverse_martix(vector<vector<float>> a)
{
	vector<vector<float>>trans_det(a.size(), vector<float>(a.size()));
	trans_det = get_transport_martix(a);
	float det_result = 1 / abs(get_det_result(a));
	vector<vector<float>>inverse_det(a.size(), vector<float>(a.size()));
	for (int j = 0; j < a.size(); j++)
	{
		for (int i = 0; i < a.size(); i++)
		{
			inverse_det[j][i] = det_result * trans_det[j][i];
		}
	}
	return inverse_det;
}
