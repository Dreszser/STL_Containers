#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "s21_containers.h"

TEST(set, ConstructorDefaultSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  EXPECT_TRUE(my_it == my_set.end());
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
    my_set_copy.print();
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, CapacitySet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, ClearSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, InsertSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(set, EraseSet) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_set.size();
  my_set.erase(my_set.end());
  auto new_size = my_set.size();
  EXPECT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SwapSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3U);
  EXPECT_EQ(my_swap_set.size(), 1U);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(set, MergeSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(set, FindSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, ContainsSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<int> test;
  for (int i = 0; i < 20; ++i) {
    test.insert(i);
  }
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

TEST(Group_exmple, example1) { ASSERT_TRUE(1 == 1); }

TEST(S21setTest, DefaultConstructor) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  ASSERT_EQ(0U, set.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, InitializerListConstructor) {
  s21::set<int> s1({1, 2, 3});
  ASSERT_FALSE(s1.empty());
  ASSERT_EQ(3U, s1.size());
}

TEST(S21setTest, CopyConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(S21setTest, MoveConstructor) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> move(std::move(set));
  ASSERT_TRUE(set.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, AssignmentOperator1) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = set1;
  ASSERT_FALSE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(set1.size(), set2.size());
}

TEST(S21setTest, AssignmentOperator2) {
  s21::set<int> set1({1, 2, 3});
  s21::set<int> set2;
  set2 = std::move(set1);
  ASSERT_TRUE(set1.empty());
  ASSERT_FALSE(set2.empty());
  ASSERT_EQ(3U, set2.size());
}

TEST(S21setTest, IteratorBegin) {
  s21::set<int> set({1, 2, 3});
  s21::set<int>::iterator iterat;
  iterat = set.begin();
  s21::set<int>::iterator itFind;
  itFind = set.find(1);
  ASSERT_TRUE(iterat == itFind);
  ASSERT_EQ(itFind, iterat);
}

TEST(S21setTest, CapacityEmpty) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(S21setTest, CapacitySize) {
  s21::set<int> set({1, 2, 3});
  s21::set<int> empty;
  EXPECT_EQ(set.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

TEST(S21setTest, ModifierClear) {
  s21::set<int> set({1, 2, 3});
  ASSERT_FALSE(set.empty());
  set.clear();
  ASSERT_TRUE(set.empty());
  EXPECT_EQ(set.size(), 0U);
}

TEST(S21setTest, ModifierInsert1) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(S21setTest, ModifierInsert2) {
  s21::set<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(S21setTest, ModifierErase) {
  s21::set<int> set = {1, 2, 3};
  EXPECT_EQ(set.size(), 3U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.contains(2));
}

TEST(S21setTest, ModifierSwap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};
  set1.swap(set2);
  EXPECT_EQ(set1.size(), 3U);
  EXPECT_EQ(set2.size(), 3U);
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
  ASSERT_TRUE(set1.contains(6));
  ASSERT_TRUE(set2.contains(1));
  ASSERT_TRUE(set2.contains(2));
  ASSERT_TRUE(set2.contains(3));
}

TEST(S21setTest, ModifierMerge) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};
  set1.merge(set2);
  EXPECT_EQ(set1.size(), 5U);
  EXPECT_EQ(set2.size(), 0U);
  ASSERT_TRUE(set1.contains(1));
  ASSERT_TRUE(set1.contains(2));
  ASSERT_TRUE(set1.contains(3));
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
}

TEST(S21setTest, ModifierErase1) {
  s21::set<int> set;
  for (int i = 0; i < 100; ++i) {
    set.insert(i);
  }
  for (int i = 0; i < 100; ++i) {
    auto it = set.find(99 - i);
    set.erase(it);
    EXPECT_EQ(set.size(), 99 - i);
  }
}

TEST(S21setTest, ModifierErase2) {
  s21::set<int> set;
  std::set<int> orig_set;
  for (int i = 0; i < 100; ++i) {
    orig_set.insert(i);
    set.insert(i);
  }
  EXPECT_EQ(set.size(), orig_set.size());
  for (int i = 0; i < 100; ++i) {
    auto it1 = set.find(i);
    auto it2 = orig_set.find(i);
    set.erase(it1);
    orig_set.erase(it2);
    EXPECT_EQ(set.size(), orig_set.size());
  }
}

TEST(S21setTest, ModifierConst) {
  const s21::set<int> set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const std::set<int> set_std = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::set<int>::const_iterator it1 = set.begin();
  s21::set<int>::const_iterator it;
  it = it1;
  auto it2 = set_std.begin();
  for (; it != set.end(); it++, it2++) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(S21setTest, ModifierConst1) {
  const s21::set<int> set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const std::set<int> set_std = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21::set<int>::const_iterator it1 = set.end();
  s21::set<int>::const_iterator it = it1;
  it = --it1;
  auto it2 = set_std.end();
  --it2;
  for (; it != set.begin(); it--, it2--) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(set_constructor, case1) {
  s21::set<int> s21_set_int;
  s21::set<double> s21_set_double;
  s21::set<std::string> s21_set_string;

  EXPECT_EQ(s21_set_int.size(), 0U);
  EXPECT_EQ(s21_set_double.size(), 0U);
  EXPECT_EQ(s21_set_string.size(), 0U);
}

TEST(set_constructor, case2) {
  s21::set<int> s21_set_int{1, 2, 3, 4, 5};
  s21::set<double> s21_set_double{1.30359, 2847.4925, 923.39281};
  s21::set<std::string> s21_set_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_set_int.size(), 5U);
  EXPECT_EQ(s21_set_double.size(), 3U);
  EXPECT_EQ(s21_set_string.size(), 4U);
}

TEST(set_constructor, case3) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  EXPECT_EQ(s21_set_ref_int.size(), s21_set_res_int.size());
  EXPECT_EQ(s21_set_ref_double.size(), s21_set_res_double.size());
  EXPECT_EQ(s21_set_ref_string.size(), s21_set_res_string.size());
}

TEST(set_constructor, case4) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case5) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int;
  s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double;
  s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string;
  s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case7) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281, 1.23};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  auto it_res_int = s21_set_res_int.begin();
  for (auto it_ref_int = s21_set_ref_int.begin();
       it_ref_int != s21_set_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(*it_res_int, *it_ref_int);
    it_res_int++;
  }

  auto it_res_double = s21_set_res_double.begin();
  for (auto it_ref_double = s21_set_ref_double.begin();
       it_ref_double != s21_set_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(*it_res_double, *it_ref_double);
    it_res_double++;
  }

  auto it_res_string = s21_set_res_string.begin();
  for (auto it_ref_string = s21_set_ref_string.begin();
       it_ref_string != s21_set_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(*it_res_string, *it_ref_string);
    it_res_string++;
  }
}

TEST(set_insert, case1) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case2) {
  s21::set<double> s21_set;

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = s21_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = s21_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = s21_set.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = s21_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case3) {
  s21::set<std::string> s21_set;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      s21_set.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      s21_set.insert("hola");
  EXPECT_EQ(*insert4.first, "hola");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      s21_set.insert("hello");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case4) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, false);
  EXPECT_EQ(insert3.second, false);

  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set_insert, case5) {
  s21::set<double> s21_set = {21};

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_insert, case6) {
  s21::set<std::string> s21_set = {"hello"};

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert1.first, "hi");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_begin, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*s21_set.begin(), 2);
}

TEST(set_begin, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*s21_set.begin(), 2.77);
}

TEST(set_begin, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hi-hi", "hola",
                                   "hello, there"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_begin, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*s21_set.begin(), 1.4);
}

TEST(set_begin, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_end, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*(--s21_set.end()), 23);
}

TEST(set_end, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 11.400000001, 3.9};

  EXPECT_EQ(*(--s21_set.end()), 11.400000001);
}

TEST(set_end, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
}

TEST(set_end, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*(--s21_set.end()), 1.4);
}

TEST(set_end, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*(--s21_set.end()), "hello");
}

TEST(set_balance, case1) {
  s21::set<int> s21_set = {1, 15, 5};

  EXPECT_EQ(*(--s21_set.end()), 15);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*(--s21_set.end()), 11.4);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case4) {
  s21::set<int> s21_set = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*(--s21_set.end()), 1543);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case5) {
  s21::set<int> s21_set = {30, 5, 43, 1, 20, 40, 60, 35, 32};

  EXPECT_EQ(*(--s21_set.end()), 60);
  EXPECT_EQ(*s21_set.begin(), 1);
  EXPECT_EQ(s21_set.size(), 9U);
}

TEST(set_erase, case2) {
  s21::set<int> s21_set = {30, 1543};

  auto it = s21_set.begin();
  it++;
  s21_set.erase(it);
  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_erase, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  auto it = (--s21_set.end());
  s21_set.erase(it);
  EXPECT_EQ(*(--s21_set.end()), "hola");
  EXPECT_EQ(s21_set.size(), 4U);

  it = (--s21_set.end());
  s21_set.erase(it);
  EXPECT_EQ(*(--s21_set.end()), "hi");
  EXPECT_EQ(s21_set.size(), 3U);

  s21_set.insert("hola-hola");
  s21_set.insert("hola");
  it = (--s21_set.end());
  s21_set.erase(it);
  EXPECT_EQ(*(--s21_set.end()), "hola");
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case4) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = (--s21_set.end());
  it--;
  s21_set.erase(it);
  it = (--s21_set.end());
  EXPECT_EQ(*it, 941.44);
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(--s21_set.end()), 44.48);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case5) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case6) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 6.84, 1.44};

  auto it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case7) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case8) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 22.2);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case9) {
  s21::set<double> s21_set = {22.2,  44.48, 12.4457, 32.45,
                              65.12, 66.32, 40.54,   6.4};

  auto it = (--s21_set.end());
  it--;
  it--;
  it--;
  it--;
  it--;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 40.54);
  EXPECT_EQ(s21_set.size(), 7U);
}

TEST(set_erase, case10) {
  s21::set<double> s21_set = {22.2};

  auto it = (--s21_set.end());
  it--;
  ++it;
  s21_set.erase(it);
  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_empty, case1) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.empty(), 0);
}

TEST(set_empty, case2) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.empty(), 1);
}

TEST(set_MaxSize, case1) {
  s21::set<double> s21_set;
  std::set<double> std_set;

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set_MaxSize, case2) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  std::set<double> std_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(set_swap, case1) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_swap, case4) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_contains, case1) {
  s21::set<double> s21_set = {22.2, 44.48};

  EXPECT_EQ(s21_set.contains(22.2), true);
  EXPECT_EQ(s21_set.contains(44.48), true);
}

TEST(set_contains, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_ref.contains(22.2), false);
  EXPECT_EQ(s21_set_ref.contains(44.48), false);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(s21_set_res.contains(22.2), true);
  EXPECT_EQ(s21_set_res.contains(44.48), true);
}

TEST(set_contains, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(s21_set_ref.contains(12.4457), true);
  EXPECT_EQ(s21_set_ref.contains(1.44), true);
  EXPECT_EQ(s21_set_ref.contains(22.2), true);

  EXPECT_EQ(s21_set_res.size(), 0U);
  EXPECT_EQ(s21_set_res.contains(12.4457), false);
  EXPECT_EQ(s21_set_res.contains(1.44), false);
  EXPECT_EQ(s21_set_res.contains(22.2), false);
}

TEST(set_contains, case4) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.size(), 0U);
  EXPECT_EQ(s21_set.contains(12.4457), false);
}

TEST(set_find, case2) {
  s21::set<double> s21_set = {12.4457, 1.44, 22.2};

  auto it = s21_set.begin();
  ++it;
  EXPECT_EQ(*s21_set.find(12.4457), *it);

  it--;
  EXPECT_EQ(*s21_set.find(1.44), *it);

  it++;
  it++;
  EXPECT_EQ(*s21_set.find(22.2), *it);
}

TEST(S21setTest, ConstSet) {
  const s21::set<int> set({1, 2, 3});
  const std::set<int> orig({1, 2, 3});

  auto it = set.begin();
  auto it_orig = orig.begin();

  for (; it != set.end(); ++it, ++it_orig) {
    EXPECT_EQ(*it, *it_orig);
  }
}

TEST(S21setTest, ConstSetEmpty) {
  const s21::set<int> set;
  const std::set<int> orig;

  auto it = set.begin();
  auto it_orig = orig.begin();

  EXPECT_EQ(*it, *it_orig);
}

TEST(S21setTest, Insert_many) {
  s21::set<int> set;
  s21::set<int> res = {1, 2, 3};

  set.insert_many(3, 2, 1);
  auto it = set.begin();
  auto it2 = res.begin();

  for (; it != set.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}

TEST(setEraseTest, EraseLeafNode) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);
  set.insert(15);

  auto it = set.find(5);
  set.erase(it);

  size_t n = 2;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(5), set.end());
}

TEST(setEraseTest, EraseNodeWithOneChild) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);
  set.insert(1);

  auto it = set.find(5);
  set.erase(it);

  size_t n = 2;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(5), set.end());
  ASSERT_NE(set.find(1), set.end());
}

TEST(setEraseTest, EraseNodeWithTwoChildren) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);
  set.insert(15);
  set.insert(12);
  set.insert(18);

  auto it = set.find(15);
  set.erase(it);

  size_t n = 4;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(15), set.end());
  ASSERT_NE(set.find(12), set.end());
}

TEST(setEraseTest, EraseRootNode) {
  s21::set<int> set;
  set.insert(10);

  auto it = set.find(10);
  set.erase(it);
  set.print();
  size_t n = 0;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(10), set.end());
}

TEST(setEraseTest1, EraseRootNode) {
  s21::set<int> set;

  auto it = set.begin();
  set.erase(it);

  size_t n = 0;
  ASSERT_EQ(set.size(), n);
}

TEST(setEraseTest2, EraseRootNode) {
  s21::set<int> set;
  set.insert(5);
  set.insert(10);

  auto it = set.begin();
  set.erase(it);

  size_t n = 1;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(5), set.end());
}

TEST(setEraseTest3, EraseRootNode) {
  s21::set<int> set;
  set.insert(10);
  set.insert(5);

  auto it = set.find(10);
  set.erase(it);

  size_t n = 1;
  ASSERT_EQ(set.size(), n);
  ASSERT_EQ(set.find(10), set.end());
}

TEST(setEraseTest4, EraseNodeWithRightChild) {
  s21::set<int> set;

  set.insert(10);
  set.insert(5);
  set.insert(15);
  set.insert(20);

  auto it = set.find(15);
  set.erase(it);

  ASSERT_EQ(set.find(15), set.end());
  ASSERT_NE(set.find(20), set.end());
  size_t n = 3;
  ASSERT_EQ(set.size(), n);
}
