#include"unqzip.h"
using namespace std;

UnQZip::UnQZip(const string& src_file)
	:decode_(src_file)
{}
void UnQZip::UnQZipFile(const string& dest_path)
{

	ifstream ifs_src(decode_.src_file_, ios::in | ios::binary);//打开压缩文件
	if (!ifs_src.is_open())
	{
		cerr << "待压缩文件无效!\n";
        exit(1);
	}
	ofstream ofs_dst(dest_path, ios::out | ios::binary);//打开目标文件
	if (!ofs_dst.is_open())
	{
		cerr << "目标路径无效!\n";
        exit(1);
	}

    ifs_src.seekg(decode_.last_pos_);

	const HuffTree &tree = decode_.tree_;
	HTNode* node = tree.root_;
	bool is_finish = false;//判断是否读取完毕
	int all_alpha = decode_.get_all_alpha();
	char ch = 0;
	while (true)
	{
		if (!(ifs_src.read(&ch, sizeof(ch))))
			break;
		for (int bit = 0; bit < 8; bit++)
		{
			if ((ch & 0x80) == 0)//0x80 = 10000000
			{
				node = node->lchild_;
			}
			else
			{
				node = node->rchild_;
			}
			ch <<= 1;
			if (node->is_leaf() == true)
			{
				char data = node->data_.char_;
				ofs_dst.write(&data, sizeof(data));
				node = tree.root_;
				all_alpha--;
				if (all_alpha == 0)
				{
					is_finish = true;
					break;
				}
			}
		}
		if (is_finish == true)
			break;
	}

	ifs_src.close();
	ofs_dst.close();
}
