#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<assert.h>
#include<memory>
#include <unordered_map>
#include<queue>
using namespace std;

const string SUF = ".Qzip";//压缩文件后缀
        
using ind_t = char;

inline bool is_file_exist(const string& file_name)
{
	ifstream ifs(file_name);
	return ifs.good();
}
