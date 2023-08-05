#include"encoding.h"
using namespace std;

EnCode::EnCode(const string &file_name)
	:src_file_(file_name)
{
	AnalyzeFile();//根据文件得出字典
	tree_.CreateHuffTree(dict_);//根据字典创建哈夫曼树
    unsigned int tmp_code = 0;
	CreateHuffCode(tree_.get_root(),tmp_code,0);//编码
}

void EnCode::AnalyzeFile()
{
	ifstream fin;
	fin.open(src_file_, ios::in|ios::binary);
	if (!fin.is_open())
	{
		cout << "文件打开失败!\n";
	}
	assert(fin.is_open());
	char ch = 0;
	while (fin.read(&ch, sizeof(char)))
	{
        auto it = dict_.find(ch);
        if(it != dict_.end())
            it->second.times_++;
        else
            dict_.emplace(ch,Charactor(ch,1));
	}
	fin.close();
}

void EnCode::CreateHuffCode(HTNode* root,unsigned int tmp_code,ind_t code_len)
{
	if (root->is_leaf())
	{
		root->data_.code_ = tmp_code;
		dict_[root->data_.char_].code_ = tmp_code;
		dict_[root->data_.char_].code_len_ = code_len;
		return;
	}
	else
	{
		CreateHuffCode(root->lchild_, tmp_code<<1, code_len+1);//往左走编码为'0'
		CreateHuffCode(root->rchild_, (tmp_code<<1)+1, code_len+1);//往右走编码为'1'
	}
}
