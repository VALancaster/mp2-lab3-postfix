#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix postfix("a+b"));
}

TEST(TPostfix, can_create_postfix_with_brackets)
{
	ASSERT_NO_THROW(TPostfix postfix("(a+b)*c"));
}

TEST(TPostfix, can_get_short_postfix)
{
	TPostfix postfix("a+b");

	EXPECT_EQ("ab+", postfix.GetPostfix());
}

TEST(TPostfix, can_get_postfix_with_brackets)
{
	TPostfix postfix("(a+b)*c/d");

	EXPECT_EQ("ab+c*d/", postfix.GetPostfix());
}

TEST(TPostfix, can_get_short_infix)
{
	TPostfix postfix("a+b*c");

	EXPECT_EQ("a+b*c", postfix.GetInfix());
}

TEST(TPostfix, can_get_infix_with_brackets)
{
	TPostfix postfix("(a+b)*c/d");

	EXPECT_EQ("(a+b)*c/d", postfix.GetInfix());
}

TEST(TPostfix, can_get_operands)
{
	TPostfix postfix("(a+b)*c/d");
	vector<string> operands = { "a","b","c","d" };

	EXPECT_EQ(operands, postfix.GetOperands());
}

TEST(TPostfix, can_calculate_simple_expression)
{
	TPostfix postfix("a+b");
	map<string, double> values = { {"a", 1}, {"b", 2}};

	EXPECT_DOUBLE_EQ(3.0, postfix.Calculate(values));
}

TEST(TPostfix, can_calculate_expression_with_brackets) 
{
	TPostfix postfix("(a+b)*c");
	map<string, double> values = { {"a", 1}, {"b", 2}, {"c", 3} };

	EXPECT_DOUBLE_EQ(9.0, postfix.Calculate(values));
}

TEST(TPostfix, can_calculate_expression_with_unary_minus) 
{
	TPostfix postfix("-a+b");
	map<string, double> values = { {"a", 1}, {"b", 3} };

	EXPECT_DOUBLE_EQ(2.0, postfix.Calculate(values));
}

TEST(TPostfix, throws_when_calculating_with_missing_operands) {
	TPostfix postfix("a+b");
	map<string, double> values = { {"a", 1} }; // Значение 'b' не задано

	ASSERT_THROW(postfix.Calculate(values), std::runtime_error);
}

TEST(TPostfix, throws_on_division_by_zero) {
	TPostfix postfix("a/b");
	map<string, double> values = { {"a", 1}, {"b", 0} };

	ASSERT_THROW(postfix.Calculate(values), std::runtime_error);
}
