#include <gtest/gtest.h>

#include "s21_containers.h"

TEST(ExtraTreeTests, InitializerList) {
  s21::Tree<char> tree = {'x', 'b', 'z', 'y'};
  tree.printBT(tree.getRoot());
  ASSERT_EQ(tree.size(), 4);
  ASSERT_EQ(tree.maximum(tree.getRoot())->value, 'z');
}

TEST(ExtraTreeTests, Iterator1) {
  const s21::Tree<int> tree;
  auto it = tree.begin();
  ASSERT_EQ(it, tree.end());
}
