
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include<vector>

using namespace std;
int main(int argc, char* argv[]) //
{
    // judge *zhazhili= new force_act_judge(10,20);
    // // judge* a = new force_act_judge(10,20);
    // std::cout<<zhazhili->compare()<<std::endl;
    // string path_db = "";
     char *current = argv[1];
    // analysis_1780(&path_db, &current);

    /// current_strip["delta_thick"]<parameter_current.ap_thick
    vector<vector<int>> user_arr;
    ifstream fp("D:\\VM\\share\\badstrip.csv"); //��������һ��ifstream����ָ���ļ�·��
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
        cout << badstrip[i] << endl;
       

    }

    return 0;
}

/// ThickaAnalysis_o