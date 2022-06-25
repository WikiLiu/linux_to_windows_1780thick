#pragma once
#ifndef _READSQL_H_
#define _READSQL_H_
#include <math.h>
#include <iostream>
#include <sqlcli1.h> 
#include<string>
#include <vector>
#include <map>
#include "stdlib.h"
using namespace std;

int search_dat(map<string, double>& current_strip, SQLHANDLE& EnvHandle, SQLHANDLE& ConHandle, SQLHANDLE& StmtHandle, string sqlquery, vector<string>&);
int read1780(map<string, double>&);
int read1780(map<string, double>& current_strip, string sqlquery, string name[]);

#endif // READSQL_H