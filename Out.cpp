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
	file << "�����趨��׼������ƫ�" << endl;
	file.close();
	return 0;
}
int out::consequece_force(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "�������趨��׼������ƫ�";
	file.close();
	return 0;
}
int out::consequece_act(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "ʵ���쳣END��" << endl;
	file.close();
	return 0;
}
int out::consequece_force_model(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "������ģ��ϵ����׼ȷ��";
	file.close();
	return 0;
}
int out::consequece_set(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "�������趨�����ʵ����һ�£�";
	file.close();
	return 0;
}

int out::consequece_temp(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "�¶�ģ��ϵ����׼ȷ��" << endl;
	file.close();
	return 0;
}


int out::consequece_speed(string* outfile, map<string, double>& current_strip) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "�ٶ��쳣��" << "������Ӱ������" << current_strip["count_speed_to_temp_and_force"]
		<< "���Ӱ����" << current_strip["count_speed_to_temp_and_force"] + current_strip["count_speed_to_temp_and_force"] / parameter_current.gangdu << endl;
	file.close();
	return 0;
}

int out::consequece_water(string* outfile, map<string, double>& current_strip) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "ˮ�쳣��" << "������Ӱ������" << current_strip["count_water_to_temp_and_force"]
		<< "���Ӱ����" << current_strip["count_water_to_temp_and_force"] / parameter_current.gangdu << endl;
	file.close();
	return 0;
}

int out::consequece_heredity(string* outfile, string c) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "�Ŵ�����:" << c << endl;
	file.close();

	return 0;
}

int out::consequece_model(string* outfile) {

	ofstream file;
	file.open(*outfile, ios::out | ios::app);
	file << "��ò�׼" << endl;
	file.close();

	return 0;
}

