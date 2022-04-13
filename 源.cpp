#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<stdlib.h>
using namespace std;
//为每个工件创建一个对象
class workpiece
{
public:
	int time_cost[500];
	void inite(int m)
	{
		int temp;
			for (int i = 1; i <= m; i++)
			{
				cin >> temp;
				cin >> time_cost[i];
			}
	}
};

int workpiece_num, machine_num;//工件数和机器数
workpiece workpiece_list[500] ;//所有工件的集合

double GetRand()
{
	srand(time(0));
	double r = rand() % 100 / (double)101;
	return r;
}

//动态规划求时间
int dp_time(int* a)
{
	int dp[500][500];
	dp[0][1] = dp[1][0] = 0;
	//初始化第一行
	memset(dp, 0, sizeof(dp));
	//开始动态规划
	for (int i = 1; i <= machine_num; i++)
	{
		for (int j = 1; j <= workpiece_num; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + workpiece_list[a[j]].time_cost[i];
		}
	}
	return dp[machine_num][workpiece_num];
}

int main()
{
	cin >> workpiece_num >> machine_num;
	//初始化workpiece_list
	for (int i = 1; i <= workpiece_num; i++)
	{
		workpiece_list[i].inite(machine_num);
	}
	//随机初始化工件加工的顺序
	srand(time(0));
	int order[500],next[500];
	for (int i = 1; i <= workpiece_num; i++)
	{
		order[i]  = i;
		next[i] = i;
	}
	//温度
	double T=1000;
	//温度下降的速度
	const double rate = 0.999;
	//开始退火
	double E;
	int current_value, next_value;
	int num = 1;
	while (1)
	{
		T *= rate;
		if (T < 0.00001)
		{
			break;
		}
		cout << "try" << num << endl;
		num++;
		//使用随机数交换rand1 和 rand2 两个工件加工的顺序
		int rand1 , rand2;
		while (1)
		{
			rand1 = rand() % workpiece_num + 1;
			rand2 = rand() % workpiece_num + 1;
			if (rand1 != rand2)
				break;
		}
		int temp = next[rand1];
		next[rand1] = next[rand2];
		next[rand2] = temp;
		//得到两种方法的时间
		next_value = dp_time(next);
		current_value = dp_time(order);

		/*cout << "current value is " << current_value<<endl;
		cout << "next:";
		for (int i = 1; i <= workpiece_num; i++)
			cout << next[i]<<"  ";
		cout << endl;*/

		E = -(next_value - current_value);
		if (E > 0)
		{
			for (int i = 1; i <= workpiece_num; i++)
				order[i] = next[i];
		}
		else
		{
			//计算退火的概率
			double probability = exp(E/T);
			double rand3 = rand() % 100 / (double)101;
			if (rand3 <= probability)
			{
				for (int i = 1; i <= workpiece_num; i++)
					order[i] = next[i];
			}
			else
			{
				for (int i = 1; i <= workpiece_num; i++)
					next[i] = order[i];
			}
		}
		cout << endl;
	}
	cout << "the shortest time is :" << dp_time(order) << endl;
}
