#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(100));
}

TEST(TStack, can_create_stack)
{
	ASSERT_NO_THROW(TStack<char> st);
}

TEST(TStack, can_push)
{
	TStack<int> st;

	ASSERT_NO_THROW(st.push(1));
}

TEST(TStack, can_pop)
{
	TStack<int> st;

	st.push(1);

	ASSERT_NO_THROW(st.pop());
}

TEST(TStack, can_get_size)
{
	TStack<int> st(100);

	st.push(1);
	st.push(2);
	st.push(3);

	EXPECT_EQ(100, st.getSize());
}

TEST(TStack, can_get_size_of_empty_stack)
{
	TStack<int> st;

	EXPECT_EQ(10, st.getSize());
}


TEST(TStack, can_check_empty_stack)
{
	TStack<char> st;

	EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, can_check_full_stack)
{
	TStack<int> st(20);

	for (int i = 0; i < 20; i++)
		st.push(i);

	EXPECT_TRUE(st.IsFull());
}

TEST(TStack, can_get_top)
{
	TStack<int> st;

	st.push(10);
	int top = st.getTop();

	EXPECT_EQ(10, top);
}
