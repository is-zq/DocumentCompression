#include"charactor.h"
using namespace std;

Charactor::Charactor(char ch, int times)
	:char_(ch), times_(times)
{}
bool Charactor::operator==(const Charactor& msg)
{
	return (msg.char_ == this->char_ && msg.code_ == this->code_ && msg.times_ == this->times_ && msg.code_len_ == this->code_len_);
}

void DictWriteToFile(const CharDict &dict,ofstream &ofs)
{
    if(ofs.is_open() == false)
    {
        cerr<<"Error!"<<endl;
        exit(1);
    }

    size_t size = dict.size();
    ofs.write(reinterpret_cast<const char*>(&size),sizeof(size));

    for(const auto &entry : dict)
    {
        ofs.write(const_cast<const char*>(&entry.first),sizeof(entry.first));
        ofs.write(reinterpret_cast<const char*>(&entry.second),sizeof(entry.second));
    }
}

void FileReadToDict(CharDict &dict,ifstream &ifs)
{
    if(ifs.is_open() == false)
    {
        cerr<<"Error!"<<endl;
        exit(1);
    }

    size_t size;
    ifs.read(reinterpret_cast<char*>(&size),sizeof(size));

    for(int i=0;i<size;i++)
    {
        char key;
        Charactor val;
        ifs.read(&key,sizeof(key));
        ifs.read(reinterpret_cast<char*>(&val),sizeof(val));
        dict.emplace(key,val);
    }
}
