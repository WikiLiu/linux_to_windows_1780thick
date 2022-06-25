#pragma once
#ifndef _LOGIC_H_
#define _LOGIC_H_
#include<map>
#include<string>
#define yes bool(1);
#define no bool(0);

using namespace std;

typedef bool check_yes_no;
class judge
{
public:
	virtual check_yes_no compare(map<string, double>&) = 0;
};

class thick_cal_judge : public judge
{
public:
	thick_cal_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float thick_cal;
	float thick_targ;
	float delta;
};

class force_act_cal_judge : public judge
{
public:
	force_act_cal_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float setting;
	float actual;
	float thick_delta;
	float delta;
};

class force_act_cal_to_thick_judge : public judge
{ ////////通过扎制力误差计算的厚度差 与实际厚度差 公差取多少表示由扎制力引起的呢? 多少可以忽视辊缝
public:
	force_act_cal_to_thick_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float thick;
	float force_to_thick = 0.0;
	float delta;
};

class act_act_judge : public judge /////////////////getdata
{
public:
	act_act_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:

	float sum_force = 0;
};

class force_act_post_judge : public judge
{
public:
	force_act_post_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float post_force;
	float act_force;
};

class size_stuff_judge : public judge
{
public:
	size_stuff_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float chicun_cal;
	float chengfen_cal;
	float chicun_post;
	float chengfen_post;
	float delta;
};
class speed_judge : public judge
{
public:
	speed_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float speed_post;
	float speed_cal;
};

class water_judge : public judge
{
public:
	water_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float water_post;
	float water_cal;
	float delta = 10;
};

class temp_act_post_judge : public judge
{
public:
	temp_act_post_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float acttemp;
	float posttemp;
	float actforce;
	float forcepost;
	float temp_delta = 20;
};

class temp_act_post_to_thick_judge : public judge
{
public:
	temp_act_post_to_thick_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:
	float temp_to_thick = 0.0;
	float thick_delta;
};

class heredity_last_temp_judge : public judge
{
public:
	heredity_last_temp_judge(map<string, double>& current_strip);
	check_yes_no compare(map<string, double>& current_strip);

private:

};
#endif