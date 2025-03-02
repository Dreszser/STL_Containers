#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "s21_containers.h"

// Тесты на конструкторы
TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), static_cast<s21::vector<int>::size_type>(0));
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor) {
  const size_t size = 5;
  s21::vector<int> v(size);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), size);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.size(), static_cast<s21::vector<int>::size_type>(3));
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), static_cast<s21::vector<int>::size_type>(3));
  EXPECT_EQ(v2[1], 2);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), static_cast<s21::vector<int>::size_type>(3));
  EXPECT_EQ(v1.size(), static_cast<s21::vector<int>::size_type>(
                           0));  // v1 должен быть очищен
  EXPECT_EQ(v2.back(), 3);
}

TEST(VectorTest, Destructor) {
  s21::vector<int>* v = new s21::vector<int>{1, 2, 3};
  delete v;
}

TEST(VectorTest, MoveAssignment) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2{4, 5, 6};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), static_cast<s21::vector<int>::size_type>(3));
  EXPECT_TRUE(v1.empty());
}

// Тесты на методы доступа
TEST(VectorTest, AtMethod) {
  s21::vector<int> my_vector{10, 20, 30};
  std::vector<int> std_vector{10, 20, 30};
  EXPECT_EQ(my_vector.at(1), std_vector.at(1));
  EXPECT_THROW(my_vector.at(5), std::out_of_range);
  EXPECT_THROW(std_vector.at(5), std::out_of_range);
}

TEST(VectorTest, AtMethodValid) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(my_vector.at(0), std_vector.at(0));
  EXPECT_EQ(my_vector.at(1), std_vector.at(1));
  EXPECT_EQ(my_vector.at(4), std_vector.at(4));
}

TEST(VectorTest, OperatorMethod) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(my_vector[0], std_vector[0]);
  EXPECT_EQ(my_vector[2], std_vector[2]);
  EXPECT_EQ(my_vector[4], std_vector[4]);
}

TEST(VectorTest, FrontMethod) {
  const s21::vector<int> my_vector{1, 2, 3, 4, 5};
  const std::vector<int> std_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(my_vector.front(), std_vector.front());
}

TEST(VectorTest, FrontMethod_Empty) {
  const s21::vector<int> my_vector;
  const std::vector<int> std_vector;
  EXPECT_NO_THROW(my_vector.front());
  EXPECT_NO_THROW(std_vector.front());
}

TEST(VectorTest, BackMethod) {
  const s21::vector<int> my_vector{1, 2, 3, 4, 5};
  const std::vector<int> std_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(my_vector.back(), std_vector.back());
}

TEST(VectorTest, BackMethod_Empty) {
  const s21::vector<int> my_vector;
  const std::vector<int> std_vector;
  EXPECT_NO_THROW(my_vector.back());
  EXPECT_NO_THROW(std_vector.back());
}

TEST(VectorTest, DataMethod) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  int* my_dataPtr = my_vector.data();
  int* std_dataPtr = std_vector.data();
  EXPECT_EQ(*my_dataPtr, *std_dataPtr);
  *my_dataPtr = 10;
  *std_dataPtr = 10;
  EXPECT_EQ(my_vector[0], std_vector[0]);
}

// Тесты на методы итерирования
TEST(VectorTest, BeginMethod) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  auto my_it = my_vector.begin();
  auto std_it = std_vector.begin();
  EXPECT_EQ(*my_it, *std_it);
  *my_it = 10;
  *std_it = 10;
  EXPECT_EQ(my_vector[0], std_vector[0]);
}

TEST(VectorTest, EndMethod) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  auto my_end = my_vector.end();
  auto std_end = std_vector.end();
  auto my_begin = my_vector.begin();
  auto std_begin = std_vector.begin();
  EXPECT_NE(my_end, my_begin);
  EXPECT_NE(std_end, std_begin);
}

TEST(VectorTest, ConstBeginMethod) {
  const s21::vector<int> my_vector{1, 2, 3, 4, 5};
  const std::vector<int> std_vector{1, 2, 3, 4, 5};
  auto my_it = my_vector.cbegin();
  auto std_it = std_vector.cbegin();
  EXPECT_EQ(*my_it, *std_it);
}

TEST(VectorTest, ConstEndMethod) {
  const s21::vector<int> my_vector{1, 2, 3, 4, 5};
  const std::vector<int> std_vector{1, 2, 3, 4, 5};
  auto my_end = my_vector.cend();
  auto std_end = std_vector.cend();
  auto my_begin = my_vector.cbegin();
  auto std_begin = std_vector.cbegin();
  EXPECT_NE(my_end, my_begin);
  EXPECT_NE(std_end, std_begin);
}

// Тесты на контроль емкости
TEST(VectorTest, Empty) {
  const s21::vector<int> my_vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(my_vector.empty(), std_vector.empty());
  const s21::vector<int> my_vector1{1, 2, 3};
  const std::vector<int> std_vector1{1, 2, 3};
  EXPECT_EQ(my_vector1.empty(), std_vector1.empty());
}

TEST(VectorTest, Size) {
  const s21::vector<int> my_vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(my_vector.size(), std_vector.size());
  const s21::vector<int> my_vector1{1, 2, 3};
  const std::vector<int> std_vector1{1, 2, 3};
  EXPECT_EQ(my_vector1.size(), std_vector1.size());
}

TEST(VectorTest, MaxSize) {
  const s21::vector<int> my_vector;
  const std::vector<int> std_vector;
  EXPECT_EQ(my_vector.max_size(), std_vector.max_size());
}

TEST(VectorTest, ReserveAndCapacity) {
  s21::vector<int> my_vector;
  std::vector<int> std_vector;
  my_vector.reserve(10);
  std_vector.reserve(10);
  EXPECT_EQ(my_vector.capacity(), std_vector.capacity());
  my_vector.push_back(1);
  std_vector.push_back(1);
  my_vector.push_back(2);
  std_vector.push_back(2);
  EXPECT_EQ(my_vector.size(), std_vector.size());
  my_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  EXPECT_EQ(my_vector.capacity(), std_vector.capacity());
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  size_t my_initCapacity = my_vector.capacity();
  size_t std_initCapacity = std_vector.capacity();
  my_vector.pop_back();
  std_vector.pop_back();
  my_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  EXPECT_EQ(my_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(my_initCapacity, std_initCapacity);
}

// Тесты модификаторов
TEST(VectorTest, ClearModify) {
  s21::vector<int> my_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  my_vector.clear();
  std_vector.clear();
  EXPECT_EQ(my_vector.empty(), std_vector.empty());
  EXPECT_EQ(my_vector.capacity(), std_vector.capacity());
}

TEST(VectorTest, InsertModify) {
  s21::vector<int> my_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  auto my_it = my_vector.insert(my_vector.begin() + 1, 2);
  auto std_it = std_vector.insert(std_vector.begin() + 1, 2);
  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[1], std_vector[1]);
  EXPECT_EQ(*my_it, *std_it);
}

TEST(VectorTest, InsertOutOfRangeException) {
  s21::vector<int> my_vector{1, 2, 3};
  auto invalid_it = my_vector.end() + 1;
  EXPECT_THROW(my_vector.insert(invalid_it, 10), std::out_of_range);
}

TEST(VectorTest, EraseModify) {
  s21::vector<int> my_vector{1, 2, 3, 4};
  std::vector<int> std_vector{1, 2, 3, 4};
  my_vector.erase(my_vector.begin() + 1);
  std_vector.erase(std_vector.begin() + 1);
  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[0], std_vector[0]);
}

TEST(VectorTest, EraseOutOfRangeException) {
  s21::vector<int> my_vector{1, 2, 3};
  auto invalid_it = my_vector.end() + 1;
  EXPECT_THROW(my_vector.erase(invalid_it), std::out_of_range);
}

TEST(VectorTest, PushBack) {
  s21::vector<int> my_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  my_vector.push_back(4);
  std_vector.push_back(4);
  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[3], std_vector[3]);
}

TEST(VectorTest, PopBack) {
  s21::vector<int> my_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  my_vector.pop_back();
  std_vector.pop_back();
  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector.back(), std_vector.back());
}

TEST(VectorTest, PopBackOutOfRangeException) {
  s21::vector<int> my_vector;
  EXPECT_THROW(my_vector.pop_back(), std::out_of_range);
}

TEST(VectorTest, Swap) {
  s21::vector<int> my_vector1{1, 2, 3};
  s21::vector<int> my_vector2{4, 5, 6};
  std::vector<int> std_vector1{1, 2, 3};
  std::vector<int> std_vector2{4, 5, 6};
  my_vector1.swap(my_vector2);
  std_vector1.swap(std_vector2);
  EXPECT_EQ(my_vector1[0], std_vector1[0]);
  EXPECT_EQ(my_vector2[0], std_vector2[0]);
  EXPECT_EQ(my_vector1[2], std_vector1[2]);
  EXPECT_EQ(my_vector2[2], std_vector2[2]);
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> my_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  auto my_it = my_vector.insert_many(my_vector.cbegin() + 1, 10, 20, 30);
  auto std_it = std_vector.insert(std_vector.cbegin() + 1, {10, 20, 30});

  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[0], std_vector[0]);
  EXPECT_EQ(my_vector[1], std_vector[1]);
  EXPECT_EQ(my_vector[2], std_vector[2]);
  EXPECT_EQ(my_vector[3], std_vector[3]);
  EXPECT_EQ(my_vector[4], std_vector[4]);
  EXPECT_EQ(my_vector[5], std_vector[5]);
  EXPECT_EQ(*my_it, *std_it);
}

TEST(VectorTest, InsertManyEmpty) {
  s21::vector<int> my_vector;
  std::vector<int> std_vector;
  my_vector.insert_many(my_vector.cbegin(), 10, 20, 30);
  std_vector.insert(std_vector.cbegin(), {10, 20, 30});

  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[0], std_vector[0]);
  EXPECT_EQ(my_vector[1], std_vector[1]);
  EXPECT_EQ(my_vector[2], std_vector[2]);
}

TEST(VectorTest, InsertManyOutOfBounds) {
  s21::vector<int> my_vector{1, 2, 3};
  EXPECT_THROW(my_vector.insert_many(my_vector.cend() + 1, 10, 20, 30),
               std::out_of_range);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> my_vector{1, 2, 3};
  std::vector<int> std_vector{1, 2, 3};
  my_vector.insert_many_back(4, 5, 6);
  std_vector.insert(std_vector.end(), {4, 5, 6});

  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[0], std_vector[0]);
  EXPECT_EQ(my_vector[1], std_vector[1]);
  EXPECT_EQ(my_vector[2], std_vector[2]);
  EXPECT_EQ(my_vector[3], std_vector[3]);
  EXPECT_EQ(my_vector[4], std_vector[4]);
  EXPECT_EQ(my_vector[5], std_vector[5]);
}

TEST(VectorTest, InsertManyBackEmpty) {
  s21::vector<int> my_vector;
  std::vector<int> std_vector;
  my_vector.insert_many_back(1, 2, 3);
  std_vector.insert(std_vector.end(), {1, 2, 3});

  EXPECT_EQ(my_vector.size(), std_vector.size());
  EXPECT_EQ(my_vector[0], std_vector[0]);
  EXPECT_EQ(my_vector[1], std_vector[1]);
  EXPECT_EQ(my_vector[2], std_vector[2]);
}

TEST(VectorConstIteratorTest, PostfixDecrement) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.cend();
  it--;
  EXPECT_EQ(*it, 3);
  it--;
  EXPECT_EQ(*it, 2);
}

TEST(VectorConstIteratorTest, PrefixIncrementAndDecrement) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.cbegin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(VectorConstIteratorTest, SubtractOperator) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};
  auto it = vec.cend();
  auto result_it = it - 3;
  EXPECT_EQ(*result_it, 3);
}

TEST(VectorIteratorTest, PrefixDecrement) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.end();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(VectorIteratorTest, EqualityOperator) {
  s21::vector<int> vec = {1, 2, 3};
  auto it1 = vec.begin();
  auto it2 = vec.begin();
  EXPECT_TRUE(it1 == it2);
  ++it2;
  EXPECT_FALSE(it1 == it2);
}