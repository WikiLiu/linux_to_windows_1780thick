#pragma once
#ifndef _OUT_H
#define _OUT_H
#include <string>
#include <iostream>
#include <fstream>
#include<map>
#include<string>
using namespace std;
namespace out {              //////可增加选择追加和清空
	typedef std::string outfile;

	int write_stripno(string* outfile, map<string, double>& current_strip);

	int consequece_model(outfile*);

	int consequece_roll(outfile*);

	int consequece_force(outfile*);

	int consequece_act(outfile*);

	int consequece_set(outfile*);


	int consequece_speed(outfile*, map<string, double>&);

	int consequece_water(outfile*, map<string, double>&);

	int consequece_force_model(outfile*);

	int consequece_temp(outfile*);

	int consequece_heredity(outfile*, string c);/////////////遗传


}

#endif