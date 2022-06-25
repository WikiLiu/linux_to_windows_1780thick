#include "Out.h"
#include<iomanip>
#include"parameter.h"
extern struct parameter parameter_current;
int out::write_stripno(string* outfile, map<string, double>& current_strip) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << fixed << setprecision(0) << current_strip["STRIPNO"] << "," << endl;
	file.close();
	return 0;
}

int out::consequece_roll(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "辊缝设定不准引起厚度偏差。" << endl;
	file.close();
	return 0;
}
int out::consequece_force(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "轧制力设定不准引起厚度偏差，";
	file.close();
	return 0;
}
int out::consequece_act(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "实绩异常END。" << endl;
	file.close();
	return 0;
}
int out::consequece_force_model(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "轧制力模型系数不准确，";
	file.close();
	return 0;
}
int out::consequece_set(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "轧制力设定与控制实绩不一致，";
	file.close();
	return 0;
}

int out::consequece_temp(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "温度模型系数不准确。" << endl;
	file.close();
	return 0;
}


int out::consequece_speed(string* outfile, map<string, double>& current_strip) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "速度异常，" << "轧制力影响量：" << current_strip["count_speed_to_temp_and_force"]
		<< "厚度影响量" << current_strip["count_speed_to_temp_and_force"] + current_strip["count_speed_to_temp_and_force"] / parameter_current.gangdu << endl;
	file.close();
	return 0;
}

int out::consequece_water(string* outfile, map<string, double>& current_strip) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "水异常，" << "轧制力影响量：" << current_strip["count_water_to_temp_and_force"]
		<< "厚度影响量" << current_strip["count_water_to_temp_and_force"] / parameter_current.gangdu << endl;
	file.close();
	return 0;
}

int out::consequece_heredity(string* outfile, string c) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "遗传问题:" << c << endl;
	file.close();

	return 0;
}

int out::consequece_model(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "瞄得不准" << endl;
	file.close();

	return 0;
}

