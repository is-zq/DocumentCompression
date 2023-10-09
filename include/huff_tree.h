#pragma once
#include"common.h"
#include"charactor.h"
#include<stack>
using namespace std;

struct HTNode
{
	Charactor data_;
	HTNode* lchild_ = nullptr;
	HTNode* rchild_ = nullptr;
	HTNode* parent_ = nullptr;
	HTNode(const Charactor& msg);
	inline bool is_leaf()
	{
		return !(this->lchild_ || this->rchild_);
	}

	class Comparator
	{
	public:
		bool operator()(HTNode* p1, HTNode* p2)
		{
			return p1->data_.times_ > p2->data_.times_;
		}
	};
};

using HT_ptr = HTNode*;

class HuffTree
{
	friend class QZip;
	friend class UnQZip;
private:
	HT_ptr root_ = nullptr;
public:
	inline HT_ptr get_root()
	{
		return root_;
	}
	void PreOrder(HT_ptr& new_root, const HT_ptr& src_root);
	HuffTree() = default;
	HuffTree(const HuffTree& src);//深拷贝构造
	void operator=(const HuffTree& src);//深拷贝赋值
	void CreateHuffTree(const CharDict& dict);
	~HuffTree();
};
