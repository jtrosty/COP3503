#include "../main.cpp"

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

TEST_CASE("4 Test of rotate right left", "[insert]") {
    TreeNode treeForTest;
    treeForTest.insert("small", 1);
    treeForTest.insert("big", 3);
    treeForTest.insert("middle", 2);
    REQUIRE(treeForTest.root->left->name == "small");
    REQUIRE(treeForTest.root->name == "middle");
    REQUIRE(treeForTest.root->right->name == "big");
    REQUIRE(treeForTest.testTreeBalance());
}

TEST_CASE("5 Test of rotate left right", "[insert]") {
    TreeNode treeForTest;
    treeForTest.insert("big", 3);
    treeForTest.insert("small", 1);
    treeForTest.insert("middle", 2);
    REQUIRE(treeForTest.root->left->name == "small");
    REQUIRE(treeForTest.root->name == "middle");
    REQUIRE(treeForTest.root->right->name == "big");
    REQUIRE(treeForTest.testTreeBalance());
}

TEST_CASE("6 Test of search id and name", "[insert]") {
    TreeNode treeForTest;
    Node* result1;
    Node* result2;
    for (int i = 10000000; i < 10000010; i++) {
        treeForTest.insert("test", i);
    }
    treeForTest.insert("name", 10000020);
    result1 = treeForTest.search(10000020);

    REQUIRE(result1->gatorID == 10000020);
    REQUIRE(result1->name == "name");
    REQUIRE(treeForTest.testTreeBalance());
}

/*
TEST_CASE("Vector sum modulo n is computed correctly", "[vector][modulo]") {
}
*/