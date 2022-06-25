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
	ifstream fp("D:/VM/share/badstrip.csv"); //��������һ��ifstream����ָ���ļ�·��
	string line;
	vector<string> badstrip;
	getline(fp, line); //������������һ�в�������
	while (getline(fp, line)) { //ѭ����ȡÿ������

		string number;
		istringstream readstr(line); //string��������
		//��һ�����ݰ�'��'�ָ�
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