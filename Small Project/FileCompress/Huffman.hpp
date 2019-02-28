#pragma once
#include<queue>
#include<vector>


template <class W>
struct HTNode
{
	HTNode(const W& weight)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _weight(weight)
	{}

	HTNode<W>* _pLeft;
	HTNode<W>* _pRight;
	HTNode<W>* _pParent;
	W _weight;
};

template<class W>
struct Compare
{
	bool operator()(HTNode<W>* pLeft, HTNode<W>* pRight)
	{
		if (pLeft->_weight > pRight->_weight)
			return true;
		return false;
	}
};
template <class W>
class HuffmanTree
{
	typedef HTNode<W>Node;
	typedef Node* pNode;
public:
	HuffmanTree()
		:_pRoot(nullptr)
	{}
	~HuffmanTree()
	{
		Destroy(_pRoot);
	}
	void CreatHuffmanTree(const std::vector<W>& v, const W& invalid)
	{
		if (v.empty())
			return;
		//小堆--创建二叉树的森林
		std::priority_queue<pNode, vector<pNode>, Compare<W>> hp;//小堆
		for (size_t i = 0; i < v.size(); i++)
		{
			if (v[i] != invalid)
			{
				hp.push(new Node(v[i]));
			}
		}

		while (hp.size() > 1)
		{
			//获取堆中权值最小的两个二叉树
			pNode pLeft = hp.top();
			hp.pop();

			pNode pRight = hp.top();
			hp.pop();

			//创建一个新的结点并重新加入到集合
			pNode pParent = new Node(pLeft->_weight + pRight->_weight);
			pParent->_pLeft = pLeft;
			pLeft->_pParent = pParent;

			pParent->_pRight = pRight;
			pRight->_pParent = pParent;

			hp.push(pParent);
		}
		_pRoot = hp.top();
	}
	pNode GetRoot()
	{
		return _pRoot;
	}
private:
	void Destroy(pNode& pRoot)
	{
		if (pRoot)
		{
			Destroy(pRoot->_pLeft);
			Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
private:
	pNode _pRoot;
};