#include "Count.h"
#include "Logic.h"
#include "Out.h"
#include "readsql.h"
#include "parameter.h"
#include <iostream>
#include <ctime>
#include <thread>

using namespace std;
extern struct parameter parameter_current;
static float access;

//int size_stuff(string* outfile, onestrip& current_strip, map<string, float>* return_stuff);
//int speed(string* outfile, onestrip& current_strip, map<string, float>* return_speed);
//int water(string* outfile, onestrip& current_strip, map<string, float>* return_speed);

int analysis1780(map<string, double>& current_strip)
{

	string* outfile = new string(parameter_current.outfile);

	try
	{
		read1780(current_strip);
	}
	catch (const std::exception& e)
	{
		cout << "未初始化map" << e.what() << endl;
	}

	count::force_gandu(current_strip);


	thick_cal_judge(current_strip).compare(current_strip);

	if (current_strip["logic_thick_cal"] > 10e-6) {

		out::consequece_model(outfile);
	}

	force_act_cal_judge(current_strip).compare(current_strip);

	if (current_strip["logic_force_act_cal"] < 10e-6) {

		out::consequece_roll(outfile);
		exit(0);
	}

	count::force_act_cal_to_thick(current_strip);

	force_act_cal_to_thick_judge(current_strip).compare(current_strip);

	if (current_strip["logic_force_act_cal_to_thick"] < 10e-6) {

		out::consequece_force(outfile);
	}

	if (current_strip["logic_force_act_cal_to_thick"] > 10e-6) {

		out::consequece_roll(outfile);
		exit(0);
	}

	act_act_judge(current_strip).compare(current_strip);

	if (current_strip["logic_act_act"] < 10e-6) {

		out::consequece_act(outfile);
	}

	force_act_post_judge(current_strip).compare(current_strip);

	if (current_strip["logic_force_act_post"] < 10e-6) {

		out::consequece_force_model(outfile);
		goto LOOP_MODEL;

	}
	else if (current_strip["logic_force_act_post"] > 10e-6)
	{
		out::consequece_set(outfile);
		goto LOOP_SET;


	}

LOOP_MODEL:do {

	cout << "loooop    model" << endl;

	temp_act_post_judge(current_strip).compare(current_strip);

	if (current_strip["logic_temp_act_post"] > 10e-6) {

		count::temp_act_post_to_force(current_strip);
		count::temp_act_post_to_thick(current_strip);

	}
	else
	{
		goto heredity;
	}

	temp_act_post_to_thick_judge(current_strip).compare(current_strip);

	if (current_strip["logic_temp_act_post_to_thick"] > 10e-6) {
		out::consequece_temp(outfile);
		exit(0);
	}
	else
	{
		goto heredity;
	}

heredity:heredity_last_temp_judge(current_strip).compare(current_strip);///////////////

	if (current_strip["heredity_last_null"] > 10e-6) {
		out::consequece_heredity(outfile, "太久未轧制导致轧制系数不适应。");
	}
	if (current_strip["heredity_last_temp"] > 10e-6) {
		out::consequece_heredity(outfile, "上一块钢温度出现问题，辊缝调整不及时。");
	}

} while (0);

LOOP_SET:do {

cout << "loooop  set" << endl;
speed_judge(current_strip).compare(current_strip);

if (current_strip["logic_speed"] > 10e-6) {

	count::speed_to_temp(current_strip);
	count::speed_to_temp_and_force(current_strip);

	out::consequece_speed(outfile, current_strip);
}

water_judge(current_strip).compare(current_strip);

if (current_strip["logic_water"] > 10e-6) {

	count::water_to_temp(current_strip);
	count::water_to_temp_and_force(current_strip);

	out::consequece_water(outfile, current_strip);
}

current_strip["count_speed_to_temp_and_force"] + current_strip["count_speed_to_temp_and_force"] / parameter_current.gangdu;

} while (0);


return 0;
}







/*test
	vector<float> *return_stuff = new vector<float>();


	thread th1(size_stuff, sql, &outfile, ref(current_strip), return_stuff);

	 等待线程 t1 完成
	th1.join();

	cout << return_stuff->at(0) << return_stuff->at(1) << endl;
test*/
/////////////////start____
//thick_cal_judge(current_strip).compare(current_strip);
//if (current_strip["logic_thick_cal"] > 50)
//{
//	cout << "目标厚度瞄得不准，模型计算得到的误差就比较大" << endl;
//	exit(1);
//}

//if (force_act_cal_judge(current_strip).compare(current_strip))
//{
//	if (thickdelta_force_to_thick_judge(current_strip["delta_thick"], count::force_to_roll(current_strip), parameter_current.thickdelta_force_to_thick).compare()) //////a,b
//	{
//		out::consequece_force(&outfile);
//		if (act_act_judge(current_strip["FORCE"], current_strip["FORCE_WS"]).compare()) //////////////给出一个标志位 什么时候测量异常
//		{                                                                               ///////////////
//			if (post_force_act_judge(current_strip["ROLL_FORCE_POST"], current_strip["FORCE"] + current_strip["FORCE_WS"]).compare())
//			{
//				//////轧制力模型准确
//				out::consequece_set_cont(&outfile);
//				map<string, float>* return_stuff = new map<string, float>();
//				map<string, float>* return_speed = new map<string, float>();
//				map<string, float>* return_water = new map<string, float>();

//				thread th1(size_stuff, &outfile, ref(current_strip), return_stuff);
//				thread th2(speed, &outfile, ref(current_strip), return_speed);
//				thread th3(water, &outfile, ref(current_strip), return_water);
//				// 等待线程 t1 完成
//				th1.join();
//				// 等待线程 t2 完成
//				th2.join();
//				// 等待线程 t3 完成
//				th3.join();

//				// access = count::temp_to_force(sql, current_strip, (*return_stuff)["temp"]);
//				// count::force_to_roll(sql, current_strip, access + (*return_stuff)["force"]);

//				access = count::temp_to_force(current_strip, (*return_speed)["temp"]);
//				count::force_to_roll(current_strip, access + (*return_speed)["force"]);

//				access = count::temp_to_force(current_strip, (*return_water)["temp"]);
//				count::force_to_roll(current_strip, access + (*return_water)["force"]);
//			}
//			else
//			{

//				out::consequece_force_model(&outfile);
//				if (post_temp_force_opposite_judge(current_strip["FM_TEMP_ACT"],
//					current_strip["EXIT_TEMP_POST"],
//					current_strip["FORCE"] + current_strip["FORCE_WS"],
//					current_strip["ROLL_FORCE_POST"], parameter_current.posttemp_delta)
//					.compare())

//					/////////////////////getdata  后计算和轧制力抛偏差  轧制力是预计算轧制力还是后计算   后计算
//				{
//					access = count::temp_to_force(current_strip);
//					access = count::force_to_roll(current_strip, access);
//					if (temp_thick_judge(current_strip["delta_thick"], access, parameter_current.posttemp_to_actthick).compare())
//					{
//						out::consequece_temp(&outfile);
//						return 1;

//					}
//					else
//					{
//						////遗传分析
//						cout << "遗传分析" << endl;
//					}
//				}
//				else
//				{
//					////遗传分析
//					cout << "遗传分析" << endl;
//					if (current_strip["CORR_FORCE_STAND_CAL"] == 1.0f)
//						out::consequece_heredity(&outfile, "新钢种,轧制力机架系数为1");
//					if (current_strip["CORR_FORCE_STAND_CAL"] == 1.25f)
//						out::consequece_heredity(&outfile, "轧制力系数调节能力有限,调节范围0-1.25");
//					if (current_strip["CORR_ZEROPOINT_USE"] < 10E-6)
//						out::consequece_heredity(&outfile, "换辊后辊缝学习值置零");
//					////////这里可增加一条新钢种 就写一条sql quary为null
//					onestrip last_strip;

//					if (!query_kind(current_strip)) ////非表示没查到
//					{
//						out::consequece_heredity(&outfile, "该规格第一次轧制,轧制力学习力度不够导致系数设定不准");
//					}
//					else
//					{

//						if (abs(last_strip["FM_TEMP_ACT"] - last_strip["EXIT_TEMP_POST"]) > 20 && (last_strip["FM_TEMP_ACT"] - last_strip["EXIT_TEMP_POST"]) * last_strip["delta_thick"] > 0)
//						{
//							out::consequece_heredity(&outfile, "上一块钢温度出现问题没有表现出来，本块辊缝调整不及时，温度预测不准导致厚度偏差");
//						}

//						//////////感度计算
//						/*float entry_temp, rel_redu, entry_thk, exit_thk, cir_speed, radius, wrdiam, entry_tension, exit_tension, width;*/

//						// float canshu[] = {852.32, 0.1314, 3.7, 3.02, 10.0, 376.0950012, 651.5800171, 16.0, 22.75, 1236.36};
//						// vector<float> bianhualiebiao = {0.41,0.02,0.06,0.04,0.23,2.6,3.21,0.63,0.96,1.32}; ///////////////current_strip    last_strip
//						// ///
//					}
//				}
//			}
//		}
//		else
//		{
//			out::consequece_act(&outfile);

//			return 1;
//		}
//	}
//	else
//	{
//		out::consequece_roll(&outfile);

//		if (current_strip["CORR_ZEROPOINT_USE"] < 10E-6)
//		{
//			out::consequece_heredity(&outfile, "机架换辊，机架相关学习系数归零，需要重新学习才能稳定轧制");
//		}

//		return 1;
//	}
//}
//else
//{
//	out::consequece_roll(&outfile);
//	//////////////遗传
//	onestrip last_strip;

//	if (!query_kind(current_strip)) ////非表示没查到
//	{
//		out::consequece_heredity(&outfile, "该规格第一次轧制,轧制力学习力度不够导致系数设定不准");
//	}
//	else
//	{

//		if (abs(last_strip["FM_TEMP_ACT"] - last_strip["EXIT_TEMP_POST"]) > 20 && (last_strip["FM_TEMP_ACT"] - last_strip["EXIT_TEMP_POST"]) * last_strip["delta_thick"] > 0)
//		{
//			out::consequece_heredity(&outfile, "上一块钢温度出现问题没有表现出来，本块辊缝调整不及时，温度预测不准导致厚度偏差");
//		}
//	}
//	if (current_strip["CORR_ZEROPOINT_USE"] < 10E-6)
//	{
//		out::consequece_heredity(&outfile, "机架换辊，机架相关学习系数归零，需要重新学习才能稳定轧制");
//	}

//	return 1;
//}




//
//int size_stuff(string* outfile, onestrip& current_strip, map<string, float>* return_stuff)
//{
//
//	(*return_stuff)["force"] = 0.5;
//	(*return_stuff)["temp"] = 0.5;
//	if (size_stuff_judge(1, 2, 3, 4).compare())
//	{
//		out::consequece_stuff(outfile);
//		count::size_to_temp(current_strip);
//		access = count::size_to_force(current_strip);
//		count::force_to_roll(current_strip, access); //改成合理的顺序 是不是要温度轧制力累加起来 如果是 要设一个指针指到和
//		return 0;
//	}
//	else
//	{
//		return 1;
//	}
//}
//
//int speed(string* outfile, onestrip& current_strip, map<string, float>* return_speed)
//{
//
//	if (speed_judge(current_strip["CIRC_SPEED_POST"], current_strip["CIRC_SPEED_CAL"], parameter_current.speed_delta).compare())
//	{
//		out::consequece_speed(outfile);
//		(*return_speed)["temp"] = count::speed_to_temp(current_strip);
//		(*return_speed)["force"] = count::speed_to_force(current_strip);
//		return 0;
//	}
//	else
//	{
//		(*return_speed)["temp"] = 0;
//		(*return_speed)["force"] = 0;
//		return 1;
//	}
//}
//
//int water(string* outfile, onestrip& current_strip, map<string, float>* return_water)
//{
//
//	if (water_judge(current_strip["WATER_POST"], current_strip["WATER_CAL"], parameter_current.water_delta).compare())
//	{
//		out::consequece_water(outfile);
//		(*return_water)["force"] = count::water_to_temp(current_strip);
//		// (*return_water)["temp"] = count::water_to_force(sql, current_strip);
//		(*return_water)["temp"] = 0;
//		return 0;
//	}
//	else
//	{
//		(*return_water)["force"] = 0;
//		(*return_water)["temp"] = 0;
//		return 1;
//	}
//}
