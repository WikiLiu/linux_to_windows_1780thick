#pragma once
#pragma warning(disable : 4996)
#ifndef _SOMEFOUNCTION_H
#define _SOMEFOUNCTION_H

#include <ctime>
#include <string>
#include <string>
#include <memory>
#include "readsql.h"

// class parameters{

// public:
//  thick_plus set_thick_plus=0;
//  date now_date=current_time();
// };


float force_calcular(vector<float> canshuliebiao, map<string, double>& current_strip)
{

	float carbon = current_strip["CARBON"], manganese = current_strip["MANGANESE"],
		silicon = current_strip["SILICON"], nickel = current_strip["NICKEL"],
		chromium = current_strip["CHROMIUM"], vanadium = current_strip["VANADIUM"],
		molybdenum = current_strip["MOLYBDENUM"], niobium = current_strip["NIOBIUM"],
		titanium = current_strip["TITANIUM"], copper = current_strip["COPPER"],
		aluminium = current_strip["ALUMINIUM"];

	float kf = 1; //passData.inherActive.inherVal.force;
	//if (standNo >= 21 && standNo <= 27)
	//{
	//    kf = limitJudge(kf, paramap->getConfig().kRFLimit.at(standNo - 21));
	//}
	//else
	//{
	//    kf = limitJudge(kf, paramap->getConfig().RmRFLimit);
	//}
	//kf
	float entry_temp = canshuliebiao[0], rel_redu = canshuliebiao[1], entry_thk = canshuliebiao[2], exit_thk = canshuliebiao[3], cir_speed = canshuliebiao[4], radius = canshuliebiao[5], wrdiam = canshuliebiao[6],
		entry_tension = canshuliebiao[7], exit_tension = canshuliebiao[8], width = canshuliebiao[9];
	float ak[12] = { 9.55047,2.24723,	1.79067,	1.65026,	0.963662,	0.713756,	4.94787	,3.15128,	8.85264,	3.60935,	1.47319,	0.001 };
	float bk[10] = { 0.066075,	0.313821,	3.14465,	0.178837,	0.136993,	0.001,	0.001,	0.001	,0.001,	0.001 };
	float kChem = ak[0]
		+ ak[1] * carbon
		+ ak[2] * manganese
		+ ak[3] * silicon
		+ ak[4] * nickel
		+ ak[5] * chromium
		+ ak[6] * vanadium
		+ ak[7] * molybdenum
		+ ak[8] * niobium
		+ ak[9] * titanium
		+ ak[10] * copper
		+ ak[11] * aluminium;

	float k_T = exp(bk[0] + bk[1] * carbon + bk[2] * silicon + bk[3] * 1000 / (273 + entry_temp));//对铁素体轧制的温度进行过处理。
	float k_e = std::log(1.0 / (1 - rel_redu));
	float deltaH = entry_thk - exit_thk;
	rel_redu = deltaH / entry_thk;
	float k_er = 1000 * cir_speed / sqrt(radius * deltaH) * k_e;
	radius = wrdiam / 2.0;
	deltaH = entry_thk - exit_thk;

	float km = kChem * k_T * pow(k_e, bk[4]) * pow(k_er, bk[5]);

	km = km * 1; // corrkm

	//tencorr[0] = 1;
	//tencorr[1] = 1;
	//if (paradata.am.size() > 10 && paradata.am.at(10) != 0)
	//{
	//    tencorr[0] = paradata.am.at(10);
	//    tencorr[1] = paradata.am.at(11);
	//};

	// km = km + tencorr[1] * entry_tension + tencorr[0] * exit_tension;

	km = km + entry_tension + exit_tension;

	km = kChem * k_T * pow(k_e, bk[4]) * pow(k_er, bk[5]);

	float am[] = { 0.773, -0.031,	1.19823,	0.0271803,	0.19578 };
	//压扁半径,外摩擦系数
	float cq[10] = { 0 };
	cq[0] = am[0];
	cq[1] = am[1];
	cq[2] = am[2];
	cq[3] = am[3];
	cq[4] = am[4];

	float q1 = cq[0] + cq[1] * rel_redu;
	float q2 = cq[2] + cq[3] * rel_redu + cq[4] * rel_redu * rel_redu;

	float C_R = deltaH; deltaH = entry_thk - exit_thk;
	float Deform = 2.2069e-005f;
	float B_R = Deform * km * q1 * sqrt(radius * C_R);
	float A_R = C_R - Deform * km * q2 * radius * sqrt(rel_redu / (1 - rel_redu));

	float kRadius = (B_R + sqrt(B_R * B_R + 4 * A_R * C_R)) / 2.0 / A_R;
	float Rd = radius * kRadius * kRadius;
	radius = wrdiam / 2.0;
	//if (A_R > 0)
	//{
	//    kRadius = (B_R + sqrt(B_R * B_R + 4 * A_R * C_R)) / 2.0 / A_R;
	//}
	//else
	//{
	//    kRadius = 1.0;
	//}

	q1 = cq[0] + cq[1] * rel_redu;
	q2 = cq[2] + cq[3] * rel_redu + cq[4] * rel_redu * rel_redu;
	/*  if (paradata.am.size() > 5 && paradata.am.at(5) > 0)
	  {
		  cq[0] = paradata.am.at(5);
		  cq[1] = paradata.am.at(6);
		  cq[2] = paradata.am.at(7);
		  cq[3] = paradata.am.at(8);
		  cq[4] = paradata.am.at(9);
	  }*/
	  /*   else
		 {
			 cq[0] = C[0];
			 cq[1] = C[1];
			 cq[2] = C[2];
			 cq[3] = C[3];
			 cq[4] = C[4];
		 }*/

	float Ld = sqrt(Rd * C_R);

	float Q_F = q1 + q2 * sqrt(Rd / exit_thk);

	//bao hu
	if (Q_F <= 0)	Q_F = 0.001;
	Rd = radius * kRadius * kRadius;

	float force = kf * width * km * Ld * Q_F / 1000.0;  //KN

	return force;
};






float temp_calcular();

#endif