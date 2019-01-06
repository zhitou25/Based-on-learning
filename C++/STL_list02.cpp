//list带头节点的双向循环链表;
//部分接口的模拟实现

#include<iostream>

using namespace std;


template<class T>
class List {
	typedef ListNode<T> Node;
	typedef Node* pNode;

public:
	typedef ListIterator < T, T*, T&> Iterator;
	typedef ListIterator< T, const T&, const T&>ConstIterator;
public:
	List()
	{
		CreatHeadNode();
	}
	List(size_t count, const T& val = T())
	{
		CreatHeadNode();
		while (count)
		{
			PushBack(val);
			--count;
		}
	}
	template<class Iterator>
	List(Iterator* tail, Iterator* rear)
	{
		CreatHeadNode();
		whiel(tail != rear)
		{
			PushBack(*tail);
			++tail;
		}
	}
	Iterator begin()
	{
		return Iterator(_pHead->_pNext);
	}
	Iterator end()
	{
		return Iterator(_pHead);
	}
	//获取首值
	T& GetTailVal()
	{
		return _pHead->_pNext->_val;
	}
	//获取尾值
	T& GetRearVal()
	{
		pNode rear = _pHead->_pNext;
		while (rear ->_pNext!= _pHead)
		{
			rear = rear->_pNext;
		}
		return rear->_val;
	}
	//头插
	void PushFront(const T& val)
	{
		pNode pNewnode = new Node(val);

		pNewnode->_pPrev = _pHead;
		pNewnode->_pNext = _pHead->_pNext;
		_pHead->_pNext = pNewnode;
		pNewnode->_pNext->_pPrev = pNewnode;
	}
	//尾插
	void PushBack(const T& val)
	{
		pNode pNewnode = new Node(val);
		//先链接新的结点
		pNewnode->_pNext = _pHead;
		pNewnode->_pPrev = _pHead->_pPrev;
		//在调整剩余的两个指针
		_pHead->_pPrev = pNewnode;
		pNewnode->_pPrev->_pNext = pNewnode;
	}
	size_t size()
	{
		size_t count = 0;
		pNode pcur = _pHead->_pNext;
		while (pcur != _pHead)
		{
			pcur = pcur->_pNext;
			++count;
		}
		return count;
	}
	bool Empty()
	{
		return _pHead->_pNext == _pHead;
	}
	//头删
	void PopFront()
	{
		pNode del = _pHead->_pNext;
		if (del != _pHead)
		{
			_pHead->_pNext = del->_pNext;
			del->_pNext->_pPrev = _pHead;
			delete del;
			del = nullptr;
		}
	}
	//尾删
	void PopBack()
	{
		pNode del = _pHead->_pPrev;
		if (del != _pHead)
		{
			_pHead->_pPrev = del->_pPrev;
			del->_pPrev->_pNext = _pHead;
			delete del;
			del = nullptr;
		}
	}
	void printList()
	{
		pNode ptr = _pHead->_pNext;
		while (ptr != _pHead)
		{
			cout << ptr->_val <<" ";
			ptr = ptr->_pNext;
		}
	}
	
private:
	void CreatHeadNode()
	{
		_pHead = new Node;
		_pHead->_pPrev = _pHead;
		_pHead->_pNext = _pHead;
	}
private:
	pNode _pHead;
};





int main()
{
	List<int>l2(8,8);

	l2.printList();
	List<int> l;
	l.PushFront(1);
	l.PushFront(2);
	l.PushFront(3);
	l.PushBack(3);
	l.PushBack(2);
	l.PushBack(1);
	l.PopFront();
	l.PopBack();
	l.printList();
	cout << endl;
	cout << l.GetTailVal() <<" " ;
	cout<<l.GetRearVal();
	return 0;
}