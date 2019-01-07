
class MinStack
{
public:
	MinStack()
	{}

	void push(int x)
		//栈的弹出压入序列
	{
		// 只要是压栈，先将元素保存到_elem中
		_elem.push(x);

		// 如果x小于_min中栈顶的元素，将x再压入_min中
		if (_min.empty() || x <= _min.top())
			_min.push(x);
	}

	void pop()
	{
		// 如果_min栈顶的元素等于出栈的元素，_min顶的元素要移除
		if (_min.top() == _elem.top())
			_min.pop();

		_elem.pop();
	}

	int top()
	{
		return _elem.top();
	}

	int getMin()
	{
		return _min.top();
	}
private:
	// 保存栈中的元素
	std::stack<int> _elem;

	// 保存栈的最小值
	std::stack<int> _min;
};
