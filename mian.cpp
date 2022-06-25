#include "Count.h"
#include "Logic.h"
#include "Analysis1780.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>

using namespace std;
int main(int argc, char* argv[]) //
{
	// judge *zhazhili= new force_act_judge(10,20);
	// // judge* a = new force_act_judge(10,20);
	// std::cout<<zhazhili->compare()<<std::endl;
	// string path_db = "";
	// strip_no current = "argv[1]";
	// analysis_1780(&path_db, &current);

	/// current_strip["delta_thick"]<parameter_current.ap_thick
	vector<vector<int>> user_arr;
	ifstream fp("D:/VM/share/badstrip.csv"); //定义声明一个ifstream对象，指定文件路径
	string line;
	vector<string> badstrip;
	getline(fp, line); //跳过列名，第一行不做处理
	while (getline(fp, line)) { //循环读取每行数据

		string number;
		istringstream readstr(line); //string数据流化
		//将一行数据按'，'分割
		badstrip.push_back(line.substr(0, 12));

	}




	cout << argc << "  " << argv[1] << endl;
	for (int i = 0; i < badstrip.size(); i++)
	{

		map<string, double> current_strip;

		auto strip_ll = stoull(badstrip[i]);

		current_strip["STRIPNO"] = double(strip_ll);
		current_strip["STANDNO"] = 7;
		current_strip["SEGNO"] = 3;
		current_strip["MONTHS_BACK"] = 3;
		cout << badstrip[i] << endl;
		analysis1780(current_strip);

	}

	return 0;
}

/// ThickaAnalysis_o