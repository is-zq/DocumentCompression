#include"decoding.h"
#include<queue>
using namespace std;

DeCode::DeCode(const string& file_name)
	:src_file_(file_name)
{
	AnalyzeFile();//从压缩文件中读取字典
	tree_.CreateHuffTree(dict_);//用字典创建哈夫曼树
}

void DeCode::AnalyzeFile()
{
	ifstream fin;
	fin.open(src_file_, ios::in | ios::binary);
	if (!fin.is_open())
	{
		cout << "文件打开失败!\n";
	}
	assert(fin.is_open());

	FileReadToDict(dict_,fin);

    last_pos_ = fin.tellg();

	fin.close();
}
