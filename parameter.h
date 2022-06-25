#pragma once
#pragma once

#ifndef _PARAMETER_H_

#define _PARAMETER_H_

#include <string>
#include<map>
using namespace std;

typedef float thick_plus;
typedef int sfc;
typedef int qual_no;
typedef int thick_class;
typedef int width_class;
typedef int temp_class;
typedef std::string date;

struct parameter
{
	float ap_thick = 0.1;
	char strip_no[20] = "220170102200";
	string outfile = "result.csv";
	string db_path = "/mnt/hgfs/share/threemonth.db";

	float max_force7 = 20000;
	float min_force7 = 2100;

	float thick_delta_percentage = 10;
	float thickdelta_force_to_thick = 10;
	float postforce_act_delta = 10;
	float gangdu = 700;
	float posttemp_delta = 20;
	float posttemp_to_actthick = 10;
	float speed_delta = 10;
	float water_delta = 10;
	////扎制力相对误差  ab偏差  刚度  后计算温度20
	/* data */
};

#endif