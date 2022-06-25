
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
    ifstream fp("D:\\VM\\share\\badstrip.csv"); //定义声明一个ifstream对象，指定文件路径
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
        cout << badstrip[i] << endl;
       

    }

    return 0;
}

/// ThickaAnalysis_o