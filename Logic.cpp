#include "Logic.h"
#include "parameter.h"
#include <iostream>
extern struct parameter parameter_current;

thick_cal_judge::thick_cal_judge(map<string, double>& current_strip)
{
	thick_cal = current_strip["EXIT_THICK_CAL"];
	thick_targ = current_strip["FMOUTTHICK"];
	delta = parameter_current.ap_thick;
}
check_yes_no thick_cal_judge::compare(map<string, double>& current_strip)
{
	if (thick_cal - thick_targ > delta)
	{
		current_strip["logic_thick_cal"] = 100;
		return yes;
	}
	else
	{
		return no;
	}
}

force_act_cal_judge::force_act_cal_judge(map<string, double>& current_strip)
{
	setting = current_strip["ROLL_FORCE_CAL"];
	actual = current_strip["SUM_FORCE"];
	thick_delta = current_strip["FM_THICK_ACT"] - current_strip["FMOUTTHICK"]; ////shiji - shedin
	delta = parameter_current.postforce_act_delta;
}
check_yes_no force_act_cal_judge::compare(map<string, double>& current_strip)
{

	if (abs(actual - setting) * 100 / actual >= delta && (actual - setting) * thick_delta > 0) ////扎制力的方向和厚度方向相同
	{
		current_strip["logic_force_act_cal"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}

force_act_cal_to_thick_judge::force_act_cal_to_thick_judge(map<string, double>& current_strip)
{
	thick = current_strip["FM_THICK_ACT"] - current_strip["FMOUTTHICK"];

	try {
		if (current_strip["count_force_act_cal_to_thick"] < 10e-6) {
			force_to_thick = current_strip["count_force_act_cal_to_thick"];
		}
		else {

			throw "Please count count_force_act_cal_to_thick";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	delta = parameter_current.postforce_act_delta;
}
check_yes_no force_act_cal_to_thick_judge::compare(map<string, double>& current_strip)
{
	////getdata

	if (abs(abs(force_to_thick) - thick) / thick * 100 < delta && force_to_thick * thick > 0) /////相对误差10%
	{
		current_strip["logic_force_act_cal_to_thick"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}
act_act_judge::act_act_judge(map<string, double>& current_strip)
{
	sum_force = current_strip["SUM_FORCE"];
}

check_yes_no act_act_judge::compare(map<string, double>& current_strip)
{
	////getdata

	if ((sum_force) < parameter_current.max_force7 && (sum_force) > parameter_current.min_force7)
	{
		current_strip["logic_act_act"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}

}

force_act_post_judge::force_act_post_judge(map<string, double>& current_strip)
{
	post_force = current_strip["ROLL_FORCE_POST"];
	act_force = current_strip["SUM_FORCE"];
}

check_yes_no force_act_post_judge::compare(map<string, double>& current_strip)
{
	////getdata
	if (abs(post_force - act_force) * 100 / act_force <= parameter_current.postforce_act_delta) ////基本一致
	{
		current_strip["logic_force_act_post"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}

temp_act_post_judge::temp_act_post_judge(map<string, double>& current_strip)
{
	acttemp = current_strip["FM_TEMP_ACT"];
	posttemp = current_strip["EXIT_TEMP_POST"];
	actforce = current_strip["SUM_FORCE"];
	forcepost = current_strip["ROLL_FORCE_POST"];

}
check_yes_no temp_act_post_judge::compare(map<string, double>& current_strip) /////////////20度
{
	////getdata  是实际温度减后计算吗?
	if ((acttemp - posttemp) * (actforce - forcepost) < 0 && abs(acttemp - posttemp) >= parameter_current.posttemp_delta)
	{
		current_strip["logic_temp_act_post"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}

temp_act_post_to_thick_judge::temp_act_post_to_thick_judge(map<string, double>& current_strip)
{

	try {
		if (current_strip["count_temp_act_post_to_thick"] < 10e-6) {
			temp_to_thick = current_strip["count_temp_act_post_to_thick"];
		}
		else {

			throw "Please count count_temp_act_post_to_thick";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	thick_delta = current_strip["FM_THICK_ACT"] - current_strip["FMOUTTHICK"];
}
check_yes_no temp_act_post_to_thick_judge::compare(map<string, double>& current_strip)
{
	////getdata
	if (abs(temp_to_thick - thick_delta) * 100 / thick_delta <= parameter_current.posttemp_to_actthick)
	{
		current_strip["logic_temp_act_post_to_thick"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}

size_stuff_judge::size_stuff_judge(map<string, double>& current_strip)
{
	//chicun_cal = a;
	//chengfen_cal = b;
	//chicun_post = m;
	//chengfen_post = n;
	//delta = c;
}
check_yes_no size_stuff_judge::compare(map<string, double>& current_strip)
{
	////getdata
	//if ((chicun_cal - chicun_post) <= delta && (chicun_post - chengfen_post) <= delta)
	//{
	//	return yes;
	//}
	//else
	//{
	//	return no;
	//}
	return 0;
}

speed_judge::speed_judge(map<string, double>& current_strip)
{
	speed_post = current_strip["CIRC_SPEED_POST"];
	speed_cal = current_strip["CIRC_SPEED_CAL"];

}
check_yes_no speed_judge::compare(map<string, double>& current_strip)
{
	////getdata
	if (abs(speed_post - speed_cal) * 100 <= parameter_current.speed_delta)
	{
		current_strip["logic_speed"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}

water_judge::water_judge(map<string, double>& current_strip)
{
	water_post = current_strip["WATER_CAL"];
	water_cal = current_strip["WATER_POST"];

}
check_yes_no water_judge::compare(map<string, double>& current_strip)
{
	////getdata
	if (abs(water_post - water_cal) * 100 <= parameter_current.water_delta)
	{
		current_strip["logic_water"] = 100.0;
		return yes;
	}
	else
	{
		return no;
	}
}

heredity_last_temp_judge::heredity_last_temp_judge(map<string, double>& current_strip)
{

}
check_yes_no heredity_last_temp_judge::compare(map<string, double>& current_strip)
{
	////getdata
	if (current_strip["LAST_STRIP_NO"] < 10e-6)
	{
		current_strip["heredity_last_null"] = 100.0;
	}
	else
	{

		if (abs(current_strip["LAST_FM_TEMP_ACT"] - current_strip["LAST_EXIT_TEMP_POST"]) > parameter_current.posttemp_delta && (current_strip["LAST_FM_TEMP_ACT"] - current_strip["LAST_EXIT_TEMP_POST"]) * current_strip["LAST_FM_THICK_ACT"] - current_strip["LAST_FMOUTTHICK"] > 0)
		{
			current_strip["heredity_last_temp"] = 100.0;
		}
	}
	return 0;
}
