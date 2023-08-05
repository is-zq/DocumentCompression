#include"huff_tree.h"
using namespace std;

HTNode::HTNode(const Charactor& msg)
	:data_(msg)
{}



void HuffTree::PreOrder(HT_ptr& new_root, const HT_ptr &src_root)
{
	if (!(src_root->lchild_) && !(src_root->rchild_))
	{
		new_root = new HTNode(*src_root);
        if(new_root == nullptr)
        {
            cerr<<"malloc failed!\n";
            exit(1);
        }
	}
	else
	{
		new_root = new HTNode(*src_root);
        if(new_root == nullptr)
        {
            cerr<<"malloc failed!\n";
            exit(1);
        }
		PreOrder(new_root->lchild_, src_root->lchild_);
		PreOrder(new_root->rchild_, src_root->rchild_);
	}
}
HuffTree::HuffTree(const HuffTree& src)
{
	PreOrder(this->root_, src.root_);
}
void HuffTree::operator=(const HuffTree& src)
{
	PreOrder(this->root_, src.root_);
}

void HuffTree::CreateHuffTree(const CharDict& dict)
{
	priority_queue<HT_ptr,vector<HT_ptr>, HTNode::Comparator> heap;
	for (const auto &entry: dict)
	{
        HT_ptr node = new HTNode(entry.second);
        if(node == nullptr)
        {
            cerr<<"malloc failed!\n";
            exit(1);
        }
		heap.emplace(node);
	}

	//创建哈夫曼树
	if (dict.size() == 1)
	{
		this->root_ = heap.top();
	}
	else
	{
		for (int i = 0; i < dict.size() - 1; i++)//哈夫曼树有N-1个非叶节点
		{
            HT_ptr p1 = nullptr,p2 = nullptr;
            if(heap.empty() == false)
            {
                p1 = heap.top();
			    heap.pop();
            }
            else
            {
                cerr<<"Error!\n";
                exit(1);
            }
            if(heap.empty() == false)
            {
			    p2 = heap.top();
			    heap.pop();
            }
            else
            {
                cerr<<"Error!\n";
                exit(1);
            }

			//创建节点
			this->root_ = new HTNode(Charactor(0, p1->data_.times_ + p2->data_.times_));
            if(this->root_ == nullptr)
            {
                cerr<<"malloc failed!\n";
                exit(1);
            }
			p1->parent_ = this->root_;
			p2->parent_ = this->root_;
			this->root_->lchild_ = p1;
			this->root_->rchild_ = p2;

			heap.emplace(this->root_);
		}
	}
}

HuffTree::~HuffTree()
{
	stack<HT_ptr>s;
	if(root_ == nullptr)
		return;
	s.push(root_);
	while (s.empty() == false)
	{
		HT_ptr cur_ptr = s.top();
		s.pop();
		if (cur_ptr->lchild_ != nullptr)
		{
			s.push(cur_ptr->lchild_);
		}
		if (cur_ptr->rchild_ != nullptr)
		{
			s.push(cur_ptr->rchild_);
		}
		delete cur_ptr;
	}
}
