#include "Count.h"
#include "somefounction.h"
extern struct parameter parameter_current;
int count::force_act_cal_to_thick(onestrip& current_strip) {   //////刚度
	////getdata
	//////刚度问题
	current_strip["count_force_act_cal_to_thick"] = (current_strip["FORCE"] + current_strip["FORCE_WS"] - current_strip["ROLL_FORCE_CAL"]) / 700;

	return  0;
}


int count::temp_act_post_to_force(onestrip& current_strip) {
	////getdata   感度计算
	//current_strip["count_temp_act_post_to_force"] = (current_strip["EXIT_TEMP_ACT"] - current_strip["EXIT_TEMP_POST"]) * 0.001 - 2.7;
	current_strip["count_temp_act_post_to_force"] = (current_strip["EXIT_TEMP_ACT"] - current_strip["EXIT_TEMP_POST"]) * current_strip["dfEXIT_TEMP_ACT"];
	return 0;
}


int count::temp_act_post_to_thick(onestrip& current_strip) {
	////getdata   扎制力对厚度

	try {
		if (current_strip["count_temp_act_post_to_force"] < 10e-6) {

			throw "Please count count_temp_act_post_to_force";
		}
		else {

			current_strip["count_temp_act_post_to_thick"] = current_strip["count_temp_act_post_to_force"] / 7000;
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}

	return 0;
}


int count::size_to_force(onestrip& current_strip) {
	////getdata   尺寸对扎制力

	return  (current_strip["FORCE"] + current_strip["FORCE_WS"] - current_strip["ROLL_FORCE_CAL"]) / 700;
}


int count::size_to_temp(onestrip& current_strip) {
	////getdata   尺寸对温度

	return  (current_strip["FORCE"] + current_strip["FORCE_WS"] - current_strip["ROLL_FORCE_CAL"]) / 700;
}


int count::speed_to_temp(onestrip& current_strip) {
	////getdata   ////////////////////////////////saysaysaysaysaysay
	current_strip["count_speed_to_temp"] = (current_strip["CIRC_SPEED_POST"] - current_strip["CIRC_SPEED_CAL"]) * 0.1;
	return  0;
}

int count::speed_to_temp_and_force(onestrip& current_strip) {
	////getdata   
	try {
		if (current_strip["count_speed_to_temp"] < 10e-6) {

			throw "Please count count_speed_to_temp";
		}
		else {

			current_strip["count_speed_to_temp_and_force"] = (current_strip["CIRC_SPEED_POST"] - current_strip["CIRC_SPEED_CAL"]) * current_strip["dfCIRC_SPEED_POST"]
				+ current_strip["count_speed_to_temp"] * current_strip["dfEXIT_TEMP_ACT"];
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	return  0;
}

int count::water_to_temp(onestrip& current_strip) {
	////getdata   
	current_strip["count_water_to_temp"] = (current_strip["WATER_POST"] - current_strip["WATER_CAL"]) * 1;
	return  0;
}

int count::water_to_temp_and_force(onestrip& current_strip) {
	////getdata   
	try {
		if (current_strip["count_water_to_temp_and_force"] < 10e-6) {

			throw "Please count count_water_to_temp_and_force";
		}
		else {

			current_strip["count_water_to_temp_and_force"] = (current_strip["count_water_to_temp"]) * current_strip["dfEXIT_TEMP_ACT"];
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}



	// return  (current_strip["FORCE"] + current_strip["FORCE_WS"]-current_strip["ROLL_FORCE_CAL"])/600/3  ;
	return 0;
}


int count::force_gandu(onestrip& current_strip)
{
	/*float entry_temp, rel_redu, entry_thk, exit_thk, cir_speed, radius, wrdiam, entry_tension, exit_tension, width;*/
	float canshu[] = { current_strip["EXIT_TEMP_ACT"],
		current_strip["REL_REDU_POST"],
		current_strip["ENTRY_THICK_POST"],
		current_strip["EXIT_THICK_POST"],
		current_strip["CIRC_SPEED_POST"],
		current_strip["RF_RADIUS_POST"],
		current_strip["ROLL_DIAM_POST"],
		current_strip["ENTRY_TENSION_CAL"],
		current_strip["EXIT_TENSION_CAL"],
		current_strip["STRIP_WIDTH_POST"] };
	string canshuname[] = { "dfEXIT_TEMP_ACT",
		"dfREL_REDU_POST",
		"dfENTRY_THICK_POST",
		"dfEXIT_THICK_POST",
		"dfCIRC_SPEED_POST",
		"dfRF_RADIUS_POST",
		"dfROLL_DIAM_POST",
		"dfENTRY_TENSION_CAL",
		"dfEXIT_TENSION_CAL",
		"dfSTRIP_WIDTH_POST" };
	vector<float> canshuliebiao(canshu, canshu + sizeof(canshu) / sizeof(float));
	float init_force = force_calcular(canshuliebiao, current_strip);

	int canshu_num = canshuliebiao.size();
	for (int i = 0; i < canshu_num; i++)
	{
		canshuliebiao[i] += 0.1;
		current_strip[canshuname[i]] = ((force_calcular(canshuliebiao, current_strip) - init_force) * 10);
		canshuliebiao[i] -= 0.1;
	}

	return 0;
}







