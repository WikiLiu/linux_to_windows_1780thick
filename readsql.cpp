#pragma warning(disable : 4996)
#include <stdio.h>
#include "readsql.h"
#include<string>
using namespace std;


int search_dat(map<string, double>& current_strip, SQLHANDLE& EnvHandle, SQLHANDLE& ConHandle, SQLHANDLE& StmtHandle, string sqlquery, vector<string>& namestack)   //
{
	// Declare The Local Memory Variables 
	/*SQLHANDLE EnvHandle = 0;
	SQLHANDLE ConHandle = 0;
	SQLHANDLE StmtHandle = 0;*/
	SQLRETURN RetCode = SQL_SUCCESS;

	// Allocate An Environment Handle 
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE,
		&EnvHandle);

	// Set The ODBC 应用程序 Version To 3.x 
	if (EnvHandle != 0)
		SQLSetEnvAttr(EnvHandle, SQL_ATTR_ODBC_VERSION,
			(SQLPOINTER)SQL_OV_ODBC3, SQL_IS_UINTEGER);

	// Allocate A Connection Handle 
	if (EnvHandle != 0)
		SQLAllocHandle(SQL_HANDLE_DBC, EnvHandle,
			&ConHandle);

	// Connect To The Appropriate Data Source 
	if (ConHandle != 0)
		RetCode = SQLConnect(ConHandle,
			(SQLCHAR*)"hotmill",
			SQL_NTS,
			(SQLCHAR*)"ap",
			SQL_NTS,
			(SQLCHAR*)"baosight@1780",
			SQL_NTS);

	if (ConHandle != 0 && RetCode == SQL_SUCCESS)
		SQLAllocHandle(SQL_HANDLE_STMT, ConHandle,
			&StmtHandle);


	SQLCHAR  SQLStmt[5000];

	sprintf((char*)SQLStmt, sqlquery.c_str());
	RetCode = SQLPrepare(StmtHandle, SQLStmt, SQL_NTS);

	RetCode = SQLExecute(StmtHandle);

	SQLSMALLINT clonum = 0;
	if (RetCode == SQL_SUCCESS)
	{
		SQLNumResultCols(StmtHandle, &clonum);
		SQLCHAR colname;
		SQLSMALLINT colvaluesize;
		SQLSMALLINT scale;
		SQLSMALLINT nullable;
		SQLULEN colValueSizeUnion;
		SQLSMALLINT colType;
		SQLCHAR t1[32];
		SQLLEN Strlen_or_IndPtr = 0;
		for (int i = 0; i < 100; i++)
		{
			RetCode = SQLFetch(StmtHandle);     //获取结果集
			if (RetCode != SQL_NO_DATA)
			{
				for (int j = 1; j <= clonum; j++)
				{
					//RetCode = SQLDescribeCol(StmtHandle, j, &colname, sizeof(colname), &colvaluesize, &colType, &colValueSizeUnion, &scale, &nullable);
					RetCode = SQLGetData(StmtHandle, j, SQL_C_CHAR, &t1, sizeof(t1), &Strlen_or_IndPtr);
					if (namestack[0] == "TOC")
					{
						cout << reinterpret_cast<char*>(t1);
						vector<string>::iterator k = namestack.begin();
						namestack.erase(k);//删除第一个元素

					}
					else {
						current_strip[namestack[0]] = strtod(reinterpret_cast<char*>(t1), NULL);
						vector<string>::iterator k = namestack.begin();
						namestack.erase(k);//删除第一个元素
					}
				}
			}
			else
			{
				break;
			}
			if (RetCode == SQL_ERROR || RetCode == SQL_SUCCESS_WITH_INFO)
				break;
		}
	}

	// Commit The Transaction 
	RetCode = SQLEndTran(SQL_HANDLE_DBC, ConHandle, SQL_COMMIT);

	// Free The SQL Statement Handle 
	if (StmtHandle != 0)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, StmtHandle);
		StmtHandle = NULL;
	}
	/*-----------------------------------------------------*/
	/* TERMINATION                     */
	/*-----------------------------------------------------*/
	// Terminate The Data Source Connection
	if (ConHandle != 0)
	{
		RetCode = SQLDisconnect(ConHandle);
	}
	// Free The Connection Handle 
	if (ConHandle != 0)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, ConHandle);
		ConHandle = NULL;
	}
	// Free The Environment Handle 
	if (EnvHandle != 0)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, EnvHandle);
		EnvHandle = NULL;
	}
	// Return Control To The Operating System 
	return 0;
}


int read1780(map<string, double>& current_strip)
{


	if (current_strip["STRIPNO"] == 0.0 || current_strip["SEGNO"] == 0.0)
	{
		throw "no ini map";
	}

	string sqlquery = "SELECT pdi.STRIPNO STRIP_NO,pdi.sfc SFC,pdi.QUALITYNO QUAL_NO,fmstrip.THICK_CLASS, fmstrip.WIDTH_CLASS ,fmstrip.TEMP_CLASS ,act.FM_THICK FM_THICK_ACT,pdi.FMOUTTHICK ,pdi.FMOUTTHICKTOLPLUS,PDI.TOC, ACT.FM_TEMP FM_TEMP_ACT,\
		PDI.CARBON,pdi.MANGANESE ,PDI.SILICON ,PDI.NICKEL ,PDI.CHROMIUM ,PDI.VANADIUM ,PDI.MOLYBDENUM ,\
		PDI.NIOBIUM, PDI.TITANIUM, PDI.COPPER, PDI.ALUMINIUM \
		FROM AP.AP_STRIP_PDI  AS PDI\
		JOIN AP.SCC_FMSTRIP AS FMSTRIP ON PDI.STRIPNO = " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + "  AND FMSTRIP.STRIP_NO = PDI.STRIPNO\
		JOIN AP.SCC_ACT_FMSEG AS ACT ON act.SEG_NO = " + std::to_string(current_strip["SEGNO"]).substr(0, std::to_string(current_strip["SEGNO"]).find_first_of(".")) + " AND ACT.STRIP_NO = PDI.STRIPNO ";


	string name[] = { "STRIP_NO","SFC","QUAL_NO","THICK_CLASS","WIDTH_CLASS","TEMP_CLASS","FM_THICK_ACT","FMOUTTHICK","FMOUTTHICKTOLPLUS","TOC","FM_TEMP_ACT",
	"CARBON","MANGANESE","SILICON","NICKEL","CHROMIUM","VANADIUM","MOLYBDENUM","NIOBIUM","TITANIUM","COPPER","ALUMINIUM","EXIT_THICK_CAL","CORR_ZEROPOINT_USE","CORR_ZEROPOINT","SUM_FORCE","ROLL_FORCE_CAL","ROLL_FORCE_POST",
	"CORR_FORCE_STAND_CAL","CORR_FORCE_STAND_POST","EXIT_TEMP_POST","WATER_CAL","WATER_POST","CIRC_SPEED_CAL","CIRC_SPEED_POST","ROLL_DIAM_CAL",
	"ROLL_DIAM_POST","ENTRY_THICK_CAL","ENTRY_THICK_POST","EXIT_THICK_POST","ENTRY_TENSION_CAL","EXIT_TENSION_CAL","ENTRY_TEMP_CAL","ENTRY_TEMP_POST",
	"REL_REDU_CAL","REL_REDU_POST","RF_RADIUS_CAL","RF_RADIUS_POST","STRIP_WIDTH_CAL","STRIP_WIDTH_POST" };
	vector<string> namestack(name, name + sizeof(name) / sizeof(string));

	SQLHANDLE* EnvHandle = new SQLHANDLE(0);
	SQLHANDLE* ConHandle = new SQLHANDLE(0);
	SQLHANDLE* StmtHandle = new SQLHANDLE(0);
	search_dat(current_strip, *EnvHandle, *ConHandle, *StmtHandle, sqlquery, namestack);

	sqlquery = "SELECT calforce.EXIT_THICK EXIT_THICK_CAL,postroll.CORR_ZEROPOINT_USE ,postroll.CORR_ZEROPOINT ,sub.FORCE+sub.FORCE_WS SUM_FORCE,calforce.ROLL_FORCE ROLL_FORCE_CAL,postforce.ROLL_FORCE ROLL_FORCE_POST,\
CALFORCE.CORR_FORCE_STAND AS CORR_FORCE_STAND_CAL,POSTFORCE.CORR_FORCE_STAND AS CORR_FORCE_STAND_POST,POSTTEMP.EXIT_TEMP EXIT_TEMP_POST, \
CALTEMP.WATER_FLOW WATER_CAL,POSTTEMP.WATER_FLOW WATER_POST,\
CALFORCE.CIRC_SPEED CIRC_SPEED_CAL,POSTFORCE.CIRC_SPEED CIRC_SPEED_POST,\
CALFORCE.ROLL_DIAM ROLL_DIAM_CAL,POSTFORCE.ROLL_DIAM ROLL_DIAM_POST,\
CALFORCE.ENTRY_THICK ENTRY_THICK_CAL,POSTFORCE.ENTRY_THICK ENTRY_THICK_POST,\
POSTFORCE.EXIT_THICK EXIT_THICK_POST,\
CALFORCE.ENTRY_TENSION ENTRY_TENSION_CAL,\
CALFORCE.EXIT_TENSION EXIT_TENSION_CAL,\
CALFORCE.ENTRY_TEMP ENTRY_TEMP_CAL,POSTFORCE.ENTRY_TEMP ENTRY_TEMP_POST,\
CALFORCE.REL_REDU REL_REDU_CAL,POSTFORCE.REL_REDU REL_REDU_POST,\
CALFORCE.RF_RADIUS RF_RADIUS_CAL,POSTFORCE.RF_RADIUS RF_RADIUS_POST,\
CALFORCE.STRIP_WIDTH STRIP_WIDTH_CAL,POSTFORCE.STRIP_WIDTH STRIP_WIDTH_POST \
FROM AP.SCC_CALC_ROLLFORCE AS CALFORCE  JOIN \
AP.SCC_POST_ROLLGAP AS postroll ON CALFORCE.STRIP_NO = " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of("."))
+ "  AND CALFORCE.STAND_NO = " + std::to_string(current_strip["STANDNO"]).substr(0, std::to_string(current_strip["STANDNO"]).find_first_of(".")) + " AND postroll.STRIP_NO =  CALFORCE.STRIP_NO AND postroll.STAND_NO = calforce.STAND_NO \
AND postroll.SEG_NO = " + std::to_string(current_strip["SEGNO"]).substr(0, std::to_string(current_strip["SEGNO"]).find_first_of(".")) + "  \
JOIN AP.SCC_POST_ROLLFORCE AS POSTFORCE ON  postforce.STRIP_NO =  CALFORCE.STRIP_NO  AND postforce.SEG_NO = postroll.SEG_NO AND postforce.STAND_NO =calforce.STAND_NO \
JOIN AP.SCC_ACT_FMSEGACT_SUB AS sub ON sub.STRIP_NO =  CALFORCE.STRIP_NO AND sub.SEG_NO =postroll.SEG_NO AND sub.STAND_NO = calforce.STAND_NO \
JOIN AP.SCC_POST_TEMP AS POSTTEMP ON POSTTEMP.STRIP_NO = CALFORCE.STRIP_NO AND POSTTEMP.STAND_NO =CALFORCE.STAND_NO-1  AND POSTTEMP.SEG_NO =postroll.SEG_NO \
JOIN AP.SCC_CALC_TEMP AS CALTEMP ON CALTEMP.STRIP_NO = CALFORCE.STRIP_NO AND CALTEMP.STAND_NO =CALFORCE.STAND_NO-1";

	EnvHandle = new SQLHANDLE(0);
	ConHandle = new SQLHANDLE(0);
	StmtHandle = new SQLHANDLE(0);
	search_dat(current_strip, *EnvHandle, *ConHandle, *StmtHandle, sqlquery, namestack);

	namestack.push_back("LAST_STRIP_NO");
	namestack.push_back("LAST_FM_TEMP_ACT");
	namestack.push_back("LAST_EXIT_TEMP_POST");
	namestack.push_back("LAST_FM_THICK_ACT");
	namestack.push_back("LAST_FMOUTTHICK");
	sqlquery = "SELECT pdi.STRIPNO LAST_STRIP_NO,ACT.FM_TEMP LAST_FM_TEMP_ACT,POSTFORCE.EXIT_TEMP LAST_EXIT_TEMP_POST,act.FM_THICK LAST_FM_THICK_ACT,pdi.FMOUTTHICK LAST_FMOUTTHICK \
			FROM AP.AP_STRIP_PDI   AS pdi, AP.SCC_ACT_FMSEG AS ACT, AP.SCC_POST_ROLLFORCE AS POSTFORCE \
			WHERE pdi.STRIPNO = (select FMSTRIP.STRIP_NO \
				from AP.SCC_FMSTRIP AS FMSTRIP \
		where   FMSTRIP.TOC<(select TOC from AP.SCC_FMSTRIP where AP.SCC_FMSTRIP.STRIP_NO =  " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + ") \
			AND  FMSTRIP.TOC>(select TOC - " + std::to_string(current_strip["MONTHS_BACK"]).substr(0, std::to_string(current_strip["MONTHS_BACK"]).find_first_of(".")) + " MONTHS	 from AP.SCC_FMSTRIP where AP.SCC_FMSTRIP.STRIP_NO =  " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + ") \
			AND FMSTRIP.SFC = (select SFC from AP.SCC_FMSTRIP where AP.SCC_FMSTRIP.STRIP_NO =  " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + ") \
			and FMSTRIP.THICK_CLASS = (select THICK_CLASS from AP.SCC_FMSTRIP where AP.SCC_FMSTRIP.STRIP_NO =  " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + ") \
			and FMSTRIP.WIDTH_CLASS = (select WIDTH_CLASS from AP.SCC_FMSTRIP where AP.SCC_FMSTRIP.STRIP_NO = " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + ") \
			and FMSTRIP.TEMP_CLASS = (select TEMP_CLASS from AP.SCC_FMSTRIP where AP.SCC_FMSTRIP.STRIP_NO =  " + std::to_string(current_strip["STRIPNO"]).substr(0, std::to_string(current_strip["STRIPNO"]).find_first_of(".")) + ") \
			ORDER BY TOC DESC fetch first 1 rows ONLY)\
			AND ACT.STRIP_NO = pdi.STRIPNO AND ACT.SEG_NO = " + std::to_string(current_strip["SEGNO"]).substr(0, std::to_string(current_strip["SEGNO"]).find_first_of(".")) + " AND POSTFORCE.STRIP_NO = pdi.STRIPNO \
AND POSTFORCE.SEG_NO = ACT.SEG_NO	AND POSTFORCE.STAND_NO = " + std::to_string(current_strip["STANDNO"]).substr(0, std::to_string(current_strip["STANDNO"]).find_first_of(".")) + " ";
	EnvHandle = new SQLHANDLE(0);
	ConHandle = new SQLHANDLE(0);
	StmtHandle = new SQLHANDLE(0);
	search_dat(current_strip, *EnvHandle, *ConHandle, *StmtHandle, sqlquery, namestack);
	return 0;
}

int read1780(map<string, double>& current_strip, string sqlquery, string name[])
{


	if (current_strip["STRIPNO"] == 0.0 || current_strip["SEGNO"] == 0.0)
	{
		throw "no ini map";
	}

	vector<string> namestack(name, name + sizeof(name) / sizeof(string));

	SQLHANDLE* EnvHandle = new SQLHANDLE(0);
	SQLHANDLE* ConHandle = new SQLHANDLE(0);
	SQLHANDLE* StmtHandle = new SQLHANDLE(0);
	search_dat(current_strip, *EnvHandle, *ConHandle, *StmtHandle, sqlquery, namestack);

	return 0;
}




