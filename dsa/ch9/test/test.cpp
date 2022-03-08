#include "../intAdd.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1 insert works, unable to insert same", "[insert]"){
    TreeNode treeForTest;
    REQUIRE(treeForTest.insert("Jon", 1234));
    REQUIRE_FALSE(treeForTest.insert("Jon", 1234));
}

TEST_CASE("2 Right Balance of 3 nodes", "[insert]") {
    TreeNode treeForTest;
    treeForTest.insert("small", 1);
    treeForTest.insert("middle", 2);
    treeForTest.insert("big", 3);
    REQUIRE(treeForTest.root->left->name == "small");
    REQUIRE(treeForTest.root->name == "middle");
    REQUIRE(treeForTest.root->right->name == "big");
    REQUIRE(treeForTest.testTreeBalance());
}

TEST_CASE("3 Left Balance of 3 nodes", "[insert]") {
    TreeNode treeForTest;
    treeForTest.insert("big", 3);
    treeForTest.insert("middle", 2);
    treeForTest.insert("small", 1);
    REQUIRE(treeForTest.root->left->name == "small");
    REQUIRE(treeForTest.root->name == "middle");
    REQUIRE(treeForTest.root->right->name == "big");
    REQUIRE(treeForTest.testTreeBalance());
}