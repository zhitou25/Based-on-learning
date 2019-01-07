
class MinStack
{
public:
	MinStack()
	{}

	void push(int x)
		//ջ�ĵ���ѹ������
	{
		// ֻҪ��ѹջ���Ƚ�Ԫ�ر��浽_elem��
		_elem.push(x);

		// ���xС��_min��ջ����Ԫ�أ���x��ѹ��_min��
		if (_min.empty() || x <= _min.top())
			_min.push(x);
	}

	void pop()
	{
		// ���_minջ����Ԫ�ص��ڳ�ջ��Ԫ�أ�_min����Ԫ��Ҫ�Ƴ�
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
	// ����ջ�е�Ԫ��
	std::stack<int> _elem;

	// ����ջ����Сֵ
	std::stack<int> _min;
};
