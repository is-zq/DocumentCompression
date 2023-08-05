#include"zip.h"
using namespace std;

Zip::Zip(const string& src_file)
	:encode_(src_file)
{}

void Zip::ZipFile(const string& dest_path)
{
	//将编码组合成8位的位运算,最后编码不足8位填0即可
	//循环读取源文件字节，找到huff_code，凑齐8位写入dest_path文件中

	ifstream ifs_src(encode_.src_file_, ios::in | ios::binary);//打开待压缩文件
	if (!ifs_src.is_open())
	{
		cerr << "待压缩文件无效!\n";
        exit(1);
	}
	ofstream ofs_dst(dest_path, ios::out | ios::binary);//打开压缩目标文件
	if (!ofs_dst.is_open())
	{
		cerr << "目标路径无效!\n";
        exit(1);
	}

    DictWriteToFile(encode_.dict_,ofs_dst);//把字典写入文件

	char ch = 0;
	bool is_end = false;//是否读取完毕
	ind_t index_huff_code = -1;//记录处理的哈弗曼编码的左移位数
	ind_t index_data_bit = 0;//记录处理到第几位
	unsigned int tmp_huff_code = 0;//临时存储某个字符的哈夫曼编码
	while (true)
	{
		if (index_huff_code == -1)//若某个字符哈夫曼编码存储完毕
		{
			if (ifs_src.read(&ch, 1))
			{
				auto it = encode_.dict_.find(ch);
                if(it == encode_.dict_.end())
                {
                    cerr<<"Error!"<<endl;
                    exit(1);
                }
                tmp_huff_code = it->second.code_;
                index_huff_code = it->second.code_len_ - 1;
			}
			else//文件读取完毕
			{
				is_end = true;
				break;
			}
		}
		index_data_bit = 0;
		char data = 0;//要写入的数据
		for (int bit = 0; bit < 8; bit++)//每8比特写入一个数据
		{
			if (index_huff_code > -1)//该字符还没读取完
			{
				if ((tmp_huff_code & (1<<index_huff_code)) == 0)//将对应位设置为0
					data &= ~(1 << (7 - index_data_bit));
				else//将对应位设置为1
					data |= (1 << (7 - index_data_bit));
				++index_data_bit;
				--index_huff_code;
			}
			else//该字符读取完毕
			{
				if (ifs_src.read(&ch, 1))
				{
					auto it = encode_.dict_.find(ch);
                    if(it == encode_.dict_.end())
                    {
                        cerr<<"Errir!"<<endl;
                        exit(1);
                    }
                    tmp_huff_code = it->second.code_;
                    index_huff_code = it->second.code_len_ - 1;
					bit--;
				}
				else//文件读取完毕
				{
					is_end = true;
					break;
				}
			}
		}
		ofs_dst.write(&data, sizeof(data));//将这块数据写入文件中

		if (is_end == true)
		{
			break;
		}
	}

	ifs_src.close();
	ofs_dst.close();
}
