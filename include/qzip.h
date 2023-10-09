#pragma once
#include"common.h"
#include"charactor.h"
#include"huff_tree.h"
#include"encoding.h"
using namespace std;

class QZip
{
private:
	EnCode encode_;
public:
	QZip(const string& src_file);
	void QZipFile(const string& dest_path);
};
