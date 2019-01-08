#include<iostream>
#include<stack>
#include<string>
#include<vector>

using namespace std;
class Solution {

public:
	int evalRPN(vector<string>&tokens)
	{
		stack<int> s;
		for (size_t i = 0; i < tokens.size(); i++)
		{
			string& str = tokens[i];
			if (!(str == "+" || str == "-" || str == "*" || str == "/"))
			{
				s.push(atoi(str.c_str()));
			}
			else
			{
				int right = s.top();
				s.pop();

				int left = s.top();
				s.pop();

				switch (str[0])
				{
				case'+':
					s.push(left + right);
					break;
				case'-':
					s.push(left - right);
					break;
				case'*':
					s.push(left*right);
				case'/':
					s.push(left/right);
					break;
						break;
				}
			}
		}
		return s.top();
	}
};

int main()
{
	vector<string> tab = { "3","2","6","-" ,"+"};
	Solution s;
	cout << s.evalRPN(tab) << endl;
	system("pause");
	return 0;
}