#pragma once
#include"common.h"
#include"charactor.h"
#include"huff_tree.h"
#include"encoding.h"
using namespace std;

class Zip
{
private:
	EnCode encode_;
public:
	Zip(const string& src_file);
	void ZipFile(const string& dest_path);
};
