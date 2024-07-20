#include "gtest/gtest.h"
#include "ListOfStrings.h"

TEST(TestGetSizeAndCapacity, OrdinaryCase)
{
	size_t size, capacity;
	GetSizeAndCapacity("40 30", size, capacity);

	ASSERT_EQ(40, size);
	ASSERT_EQ(30, capacity);
}

TEST(TestAddString, OrdinaryCase)
{
	char** list = nullptr;
	StringListInit(list);

	StringListAdd(list, (char*)"b");
	StringListAdd(list, (char*)"a");
	StringListAdd(list, (char*)"b");
	StringListAdd(list, (char*)"");
	StringListAdd(list, (char*)"c");
	StringListAdd(list, (char*)"a");

	size_t size, capacity;
	GetSizeAndCapacity(list[0], size, capacity);

	EXPECT_EQ(6, size);
	EXPECT_EQ(8, capacity);

	EXPECT_STREQ("b", list[1]);
	EXPECT_STREQ("a", list[2]);
	EXPECT_STREQ("b", list[3]);
	EXPECT_STREQ("", list[4]);
	EXPECT_STREQ("c", list[5]);
	EXPECT_STREQ("a", list[6]);

	StringListDestroy(list);
}

class ListTest : public testing::Test
{
protected:
	ListTest()
	{
		StringListInit(list);

		StringListAdd(list, "b");
		StringListAdd(list, "a");
		StringListAdd(list, "b");
		StringListAdd(list, "");
		StringListAdd(list, "c");
		StringListAdd(list, "a");
	}

	~ListTest()
	{
		StringListDestroy(list);
	}

	char** list = nullptr;
};

TEST_F(ListTest, RemoveTest)
{
	StringListRemove(list, "b");

	EXPECT_STREQ("a", list[1]);
	EXPECT_STREQ("", list[2]);
	EXPECT_STREQ("c", list[3]);
	EXPECT_STREQ("a", list[4]);

	StringListRemove(list, "bac");

	StringListRemove(list, "");

	EXPECT_STREQ("a", list[1]);
	EXPECT_STREQ("c", list[2]);
	EXPECT_STREQ("a", list[3]);

}

TEST_F(ListTest, SizeTest)
{
	StringListRemove(list, "b");

	size_t size = StringListSize(list);

	EXPECT_EQ(4, size);

	StringListRemove(list, "bac");
	size = StringListSize(list);

	EXPECT_EQ(4, size);

	StringListRemove(list, "");
	size = StringListSize(list);

	EXPECT_EQ(3, size);
}

TEST_F(ListTest, TestIndexOf)
{
	int index_of_a = StringListIndexOf(list, "a");
	int not_in_list = StringListIndexOf(list, "abc");
	int index_of_c = StringListIndexOf(list, "c");

	ASSERT_EQ(2, index_of_a);
	ASSERT_EQ(5, index_of_c);
	ASSERT_EQ(-1, not_in_list);
}

TEST_F(ListTest, RemoveDuplicates)
{
	StringListRemoveDuplicates(list);

	ASSERT_EQ(4, StringListSize(list));

	EXPECT_STREQ("b", list[1]);
	EXPECT_STREQ("a", list[2]);
	EXPECT_STREQ("", list[3]);
	EXPECT_STREQ("c", list[4]);
}

TEST(ReplacementSubstringCount, EmptyCase)
{
	size_t replacements = CalculateReplacementsCount("word", "a");

	ASSERT_EQ(0, replacements);
}

TEST(ReplacementSubstringCount, OrdinaryCase)
{
	size_t replacements = CalculateReplacementsCount("aa aa", "a");

	ASSERT_EQ(4, replacements);

	replacements = CalculateReplacementsCount("banana", "a");

	ASSERT_EQ(3, replacements);
}

TEST(ReplaceSubstring, EmptyCase)
{
	char* str = ReplaceSubstring(nullptr, "a ", "b ");

	ASSERT_EQ(nullptr, str);

	str = ReplaceSubstring(" ", nullptr, "b ");
	ASSERT_EQ(nullptr, str);

	str = ReplaceSubstring("asd ", "asd ", nullptr);
	ASSERT_EQ(nullptr, str);
}

TEST(ReplaceSubstring, BeforeLongerAfter)
{
	char* str = ReplaceSubstring("hear near sear", "ear", "o");

	ASSERT_STREQ("ho no so", str);
}

TEST(ReplaceSubstring, AfterLongerBefore)
{
	char* str = ReplaceSubstring("ho no so", "o", "ear");

	ASSERT_STREQ("hear near sear", str);
}

TEST_F(ListTest, ReplaceInStrings)
{
	StringListReplaceInStrings(list, "a", "qwery");

	ASSERT_EQ(6, StringListSize(list));

	EXPECT_STREQ("b", list[1]);
	EXPECT_STREQ("qwery", list[2]);
	EXPECT_STREQ("b", list[3]);
	EXPECT_STREQ("", list[4]);
	EXPECT_STREQ("c", list[5]);
	EXPECT_STREQ("qwery", list[6]);
}

TEST_F(ListTest, SortList)
{
	StringListSort(list);

	ASSERT_EQ(6, StringListSize(list));

	EXPECT_STREQ("", list[1]);
	EXPECT_STREQ("a", list[2]);
	EXPECT_STREQ("a", list[3]);
	EXPECT_STREQ("b", list[4]);
	EXPECT_STREQ("b", list[5]);
	EXPECT_STREQ("c", list[6]);
}
