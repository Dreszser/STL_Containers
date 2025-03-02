#include <gtest/gtest.h>

#include <iostream>

#include "s21_containers.h"

TEST(multisetTest, DefaultConstructor) {
  s21::multiset<int> miltiset;
  ASSERT_TRUE(miltiset.empty());
  ASSERT_EQ(0U, miltiset.size());
  EXPECT_EQ(miltiset.size(), 0U);
}

TEST(multisetTest, InitializerListConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3, 2, 4, 2};
  ASSERT_FALSE(ms1.empty());
  ASSERT_EQ(6U, ms1.size());
}

TEST(multisetTest, CopyConstructor) {
  s21::multiset<int> set({1, 2, 3, 2});
  s21::multiset<int> copy(set);
  ASSERT_FALSE(set.empty());
  ASSERT_FALSE(copy.empty());
  ASSERT_EQ(set.size(), copy.size());
}

TEST(multisetTest, MoveConstructor) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> move(std::move(multiset));
  ASSERT_TRUE(multiset.empty());
  ASSERT_FALSE(move.empty());
  ASSERT_EQ(3U, move.size());
  EXPECT_EQ(multiset.size(), 0U);
}

TEST(multisetTest, AssignmentOperator1) {
  s21::multiset<int> multiset1({1, 2, 3});
  s21::multiset<int> multiset2;
  multiset2 = multiset1;
  ASSERT_FALSE(multiset1.empty());
  ASSERT_FALSE(multiset2.empty());
  ASSERT_EQ(multiset1.size(), multiset2.size());
}

TEST(multisetTest, AssignmentOperator2) {
  s21::multiset<int> multiset1({1, 2, 3});
  s21::multiset<int> multiset2;
  multiset2 = std::move(multiset1);
  ASSERT_TRUE(multiset1.empty());
  ASSERT_FALSE(multiset2.empty());
  ASSERT_EQ(3U, multiset2.size());
}

TEST(multisetTest, IteratorBegin) {
  s21::multiset<int> multiset({1, 2, 3, 1, 5});
  s21::multiset<int>::iterator iterat;
  iterat = multiset.begin();
  s21::multiset<int>::iterator itFind;
  itFind = multiset.find(1);
  ASSERT_TRUE(iterat == itFind);
  ASSERT_EQ(itFind, iterat);
}

TEST(multisetTest, CapacityEmpty) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> empty;
  ASSERT_FALSE(multiset.empty());
  ASSERT_TRUE(empty.empty());
}

TEST(multisetTest, CapacitySize) {
  s21::multiset<int> multiset({1, 2, 3});
  s21::multiset<int> empty;
  EXPECT_EQ(multiset.size(), 3U);
  EXPECT_EQ(empty.size(), 0U);
}

TEST(multisetTest, CapacityMaxSize) {
  s21::multiset<int> multiset;
  ASSERT_TRUE(multiset.max_size() > 0);
}

TEST(multisetTest, ModifierClear) {
  s21::multiset<int> multiset({1, 2, 3});
  ASSERT_FALSE(multiset.empty());
  multiset.clear();
  ASSERT_TRUE(multiset.empty());
  EXPECT_EQ(multiset.size(), 0U);
}

TEST(multisetTest, ModifierInsert1) {
  s21::multiset<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(1);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  set.insert(5);
  EXPECT_EQ(set.size(), 3U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(5));
}

TEST(multisetTest, ModifierInsert2) {
  s21::multiset<int> set;
  ASSERT_TRUE(set.empty());
  set.insert(10);
  EXPECT_EQ(set.size(), 1U);
  set.insert(5);
  EXPECT_EQ(set.size(), 2U);
  ASSERT_FALSE(set.empty());
  ASSERT_TRUE(set.contains(10));
}

TEST(multisetTest, ModifierErase) {
  s21::multiset<int> set = {1, 2, 3, 2};
  EXPECT_EQ(set.size(), 4U);
  auto it = set.find(2);
  set.erase(it);
  EXPECT_EQ(set.size(), 3U);
  ASSERT_TRUE(set.contains(2));
}

TEST(multisetTest, ModifierSwap) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {4, 5, 6};
  multiset1.swap(multiset2);
  EXPECT_EQ(multiset1.size(), 3U);
  EXPECT_EQ(multiset2.size(), 3U);
  ASSERT_TRUE(multiset1.contains(4));
  ASSERT_TRUE(multiset1.contains(5));
  ASSERT_TRUE(multiset1.contains(6));
  ASSERT_TRUE(multiset2.contains(1));
  ASSERT_TRUE(multiset2.contains(2));
  ASSERT_TRUE(multiset2.contains(3));
}

TEST(multisetTest, ModifierMerge) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {3, 4, 5};
  multiset1.merge(multiset2);
  EXPECT_EQ(multiset1.size(), 6U);
  EXPECT_EQ(multiset2.size(), 0U);
  ASSERT_TRUE(multiset1.contains(1));
  ASSERT_TRUE(multiset1.contains(2));
  ASSERT_TRUE(multiset1.contains(3));
  ASSERT_TRUE(multiset1.contains(4));
  ASSERT_TRUE(multiset1.contains(5));
}

TEST(multisetTest, LookupCount) {
  s21::multiset<int> multiset = {1, 2, 3, 2, 3, 7, 2};
  EXPECT_EQ(multiset.size(), 7U);
  EXPECT_EQ(multiset.count(2), 3U);
  EXPECT_EQ(multiset.count(3), 2U);
  EXPECT_EQ(multiset.count(10), 0U);
}

TEST(multisetTest, LookupEqualRange) {
  s21::multiset<int> multiset = {1, 2, 3, 3, 7};
  EXPECT_EQ(multiset.size(), 5U);
  auto range = multiset.equal_range(3);
  ASSERT_EQ(*range.first, 3);
  ASSERT_EQ(*range.second, 7);
  range = multiset.equal_range(7);
  ASSERT_EQ(*range.first, 7);
  ASSERT_EQ(range.second, multiset.end());
  range = multiset.equal_range(8);
  ASSERT_EQ(range.first, multiset.end());
  ASSERT_EQ(range.second, multiset.end());
}

TEST(multisetTest, LookupLowerBound) {
  s21::multiset<int> multiset = {1, 2, 3, 3, 7};
  EXPECT_EQ(multiset.size(), 5U);
  auto it = multiset.lower_bound(3);
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 7);
}

TEST(multisetTest, LookupUpperBound) {
  s21::multiset<int> multiset = {1, 7, 3, 3, 2};
  EXPECT_EQ(multiset.size(), 5U);
  auto it = multiset.upper_bound(3);
  ASSERT_EQ(*it, 7);
}

TEST(multisetTest, Insert_many) {
  s21::multiset<int> set;
  s21::multiset<int> res = {1, 2, 3, 3, 4, 4, 5, 5};

  set.insert_many(1, 2, 3, 3, 4, 4, 5, 5);
  auto it = set.begin();
  auto it2 = res.begin();

  for (; it != set.end(); ++it, ++it2) {
    EXPECT_EQ(*it, *it2);
  }
}