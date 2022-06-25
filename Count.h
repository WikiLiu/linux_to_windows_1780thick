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
	int force_act_cal_to_thick(onestrip&);///////������ƫ��Թ���Ӱ��
	int size_to_temp(onestrip&);  ///
	int size_to_force(onestrip&); //
	int speed_to_temp(onestrip&);  ///////�����ٶȶ��¶�
	int speed_to_temp_and_force(onestrip&);//////�����ٶȶ������� �����¶ȵ�
	int water_to_temp(onestrip&);  ///////����ˮ���¶�
	int water_to_temp_and_force(onestrip&);  ///////����ˮ���¶ȴ�����������
	int temp_act_post_to_force(onestrip&);   ////���������¶ȶ���������Ӱ��
	int temp_act_post_to_thick(onestrip&);    ////���������¶ȶ����������ĺ��Ӱ��
	int heredity(onestrip&);
}

#endif