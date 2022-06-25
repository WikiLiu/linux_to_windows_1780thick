#pragma once
#ifndef _COUNT_H
#define _COUNT_H
#include <cmath>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<string, double> onestrip;
typedef vector<map<string, double>> somestrip;
namespace count
{
	int force_gandu(onestrip&);
	int force_act_cal_to_thick(onestrip&);///////轧制力偏差对辊缝影响
	int size_to_temp(onestrip&);  ///
	int size_to_force(onestrip&); //
	int speed_to_temp(onestrip&);  ///////量化速度对温度
	int speed_to_temp_and_force(onestrip&);//////量化速度对轧制力 叠加温度的
	int water_to_temp(onestrip&);  ///////量化水对温度
	int water_to_temp_and_force(onestrip&);  ///////量化水对温度带来的轧制力
	int temp_act_post_to_force(onestrip&);   ////量化整体温度对轧制力的影响
	int temp_act_post_to_thick(onestrip&);    ////量化整体温度对轧制力来的厚度影响
	int heredity(onestrip&);
}

#endif