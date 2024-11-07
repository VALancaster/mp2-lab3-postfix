#include "postfix.h"
#include "stack.h"
#include <stdexcept>

#include "postfix.h"
#include "stack.h"
#include <stdexcept>
#include <cctype>

void TPostfix::Parse()
{
	lexems.clear();
	for (size_t i = 0; i < infix.size(); ++i)
	{
		char c = infix[i];
		if (isdigit(c)) // Проверка на числа (теперь только целые)
		{
			lexems.push_back('N'); // Метка числа
			operands[string(1, c)] = c - '0'; // Сохранение числа в карту операндов (ключ - строка с одним символом)
		}
		else if (isalpha(c)) // Проверка на односимвольные операнды
		{
			lexems.push_back('V'); // Метка переменной
			operands[string(1, c)]; // Сохранение переменной в карту операндов
		}
		else if (c == '(' || c == ')' || priority.find(c) != priority.end()) // Проверка на символ скобки или операции
		{
			lexems.push_back(c);
		}
		else
		{
			throw std::invalid_argument("Недопустимый символ в инфиксном выражении");
		}
	}
}

void TPostfix::ToPostfix()
{
	Parse();
	TStack<char> st; // Стек для операторов
	for (size_t i = 0; i < lexems.size(); ++i)
	{
		char item = lexems[i];
		if (item == 'N') // Если метка числа
			postfix += infix[i]; // Добавляем само число (символ) в постфиксную строку
		else if (item == 'V') // Если метка переменной
			postfix += infix[i];
		else if (item == '(')
			st.push(item);
		else if (item == ')')
		{
			while (!st.IsEmpty() && st.getTop() != '(')
				postfix += st.pop();
			st.pop();  // Удаляем '('
		}
		else if (item == '-' && (postfix.empty() || postfix.back() == '('))
		{
			st.push('_');  // Унарный минус
		}
		else
		{
			while (!st.IsEmpty() && priority[st.getTop()] >= priority[item])
				postfix += st.pop();
			st.push(item);
		}
	}
	while (!st.IsEmpty())
	{
		if (st.getTop() == '(')
			throw std::invalid_argument("Несбалансированные скобки в выражении");
		postfix += st.pop();
	}
}

vector<string> TPostfix::GetOperands() const
{
	vector<string> op;
	for (const auto& item : operands)
	{
		if (!isdigit(item.first[0]))   // Только переменные
			op.push_back(item.first);
	}
	return op;
}

double TPostfix::Calculate(const map<string, double>& values)
{
	// Заполняем значения операндов
	for (const auto& val : values)
	{
		operands[val.first] = val.second;
	}

	// Проверяем, что все операнды, упомянутые в выражении, имеют заданные значения
	for (const char& lexem : postfix)
	{
		if (isalpha(lexem)) // Проверяем операнд
		{
			std::string operand(1, lexem);
			if (operands.find(operand) == operands.end() || operands[operand] == 0.0) // Проверка на отсутствие значения
			{
				throw std::runtime_error("Операнд не инициализирован: " + operand);
			}
		}
	}

	TStack<double> st; // стек для операндов (их числовых значений)
	for (size_t i = 0; i < postfix.size(); ++i)
	{
		char lexem = postfix[i];
		if (isalpha(lexem)) // Обработка переменных
		{
			string operand(1, lexem);
			st.push(operands.at(operand));
		}
		else if (isdigit(lexem)) // Обработка чисел
		{
			st.push(lexem - '0');
		}
		else if (lexem == '_') // Унарный минус
		{
			double rightOperand = st.pop();
			st.push(-rightOperand);
		}
		else if (lexem == '+' || lexem == '-' || lexem == '*' || lexem == '/') // Бинарные операции
		{
			double rightOperand = st.pop();
			double leftOperand = st.pop();
			switch (lexem)
			{
			case '+':
				st.push(leftOperand + rightOperand);
				break;
			case '-':
				st.push(leftOperand - rightOperand);
				break;
			case '*':
				st.push(leftOperand * rightOperand);
				break;
			case '/':
				if (rightOperand == 0)
					throw std::runtime_error("Division by zero");
				st.push(leftOperand / rightOperand);
				break;
			default:
				throw std::runtime_error("Unknown operator: " + std::string(1, lexem));
			}
		}
	}
	return st.pop();
}


