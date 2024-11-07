#include <iostream>
#include <string>
#include <map>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	double res;
	double val;

	cout << "Enter expression: ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << postfix.GetInfix() << endl;
	cout << postfix.GetPostfix() << endl;
	vector<string> operands = postfix.GetOperands();
	map<string, double> values;
	for (const auto& op : operands)
	{
		cout << "Enter value of " << op << ": ";
		cin >> val;
		values[op] = val;
	}
	res = postfix.Calculate(values);
	cout << res << endl;

	return 0;
}
