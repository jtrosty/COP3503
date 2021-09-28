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

TEST_CASE("7 Test large amount of insertion print height, min would be 16. Max expected to be 17. Delete all units and verify root is nullptr", "[insert]") {
    TreeNode treeForTest;
    int height = 0;
    // 10131071
    for (int i = 10000000; i < 10131071; i++) {
        treeForTest.insert("test", i);
    }

    REQUIRE(treeForTest.getHeight() == 17);
    REQUIRE(treeForTest.testTreeBalance());
    for (int i = 10000000; i < 10131071; i++) {
        treeForTest.remove(i);
    }
    REQUIRE(treeForTest.root == nullptr);
}


TEST_CASE("8 Tests removeInorder.", "[insert]") {
    TreeNode treeForTest;
    treeForTest.insert("big", 3);
    treeForTest.insert("small", 1);
    treeForTest.insert("middle", 2);
    treeForTest.removeInorder(0);
    REQUIRE_FALSE(treeForTest.search(1));
    REQUIRE(treeForTest.removeInorder(1));
    REQUIRE_FALSE(treeForTest.search(3));
    REQUIRE(treeForTest.search(2));
    REQUIRE(treeForTest.removeInorder(0));
    REQUIRE_FALSE(treeForTest.removeInorder(1));
}

TEST_CASE("9 Tree heights. Follow the format of fig 1 in Gator AVL", "[insert]") {
    TreeNode treeForTest;
    REQUIRE(treeForTest.getHeight() == 0);
    treeForTest.insert("test", 5);
    REQUIRE(treeForTest.getHeight() == 1);
    treeForTest.insert("test", 3);
    REQUIRE(treeForTest.getHeight() == 2);
    treeForTest.insert("test", 7);
    REQUIRE(treeForTest.getHeight() == 2);
    treeForTest.insert("test", 2);
    REQUIRE(treeForTest.getHeight() == 3);
    treeForTest.insert("test", 8);
    REQUIRE(treeForTest.getHeight() == 3);
    treeForTest.insert("test", 4);
    REQUIRE(treeForTest.getHeight() == 3);
    treeForTest.insert("test", 6);
    REQUIRE(treeForTest.getHeight() == 3);
    treeForTest.insert("test", 1);
    REQUIRE(treeForTest.getHeight() == 4);
}

TEST_CASE("10 Test sarches with large amounts of insertions and deletions.", "[insert]") {
    TreeNode treeForTest;
    int height = 0;
    // 10131071

    for (int i = 10000000; i < 10131071; i++) {
        treeForTest.insert("test", i);
    }
    REQUIRE(treeForTest.testTreeBalance());
    for (int i = 10000000; i < 10131071; i += 2) {
        treeForTest.remove(i);
    }
    REQUIRE_FALSE(treeForTest.search(10000010));
    REQUIRE(treeForTest.search(10000009));
    REQUIRE_FALSE(treeForTest.search(10100010));
    REQUIRE(treeForTest.search(10100009));
}

TEST_CASE("11 Test user input.", "[insert]") {
    TreeNode treeForTest;
    /// Test ID input
    REQUIRE_FALSE(treeForTest.isValidID("9999999"));
    REQUIRE(treeForTest.isValidID("00000000"));
    REQUIRE(treeForTest.isValidID("00200000"));
    REQUIRE(treeForTest.isValidID("58042030"));
    REQUIRE(treeForTest.isValidID("99999999"));
    REQUIRE_FALSE(treeForTest.isValidID("100000000"));
    REQUIRE_FALSE(treeForTest.isValidID("1000000:0"));
    REQUIRE_FALSE(treeForTest.isValidID("1000000/0"));
    /// Test Name input
    REQUIRE_FALSE(treeForTest.isNameValid("'"));
    REQUIRE_FALSE(treeForTest.isNameValid("{"));
    REQUIRE_FALSE(treeForTest.isNameValid("@"));
    REQUIRE_FALSE(treeForTest.isNameValid("["));
    REQUIRE(treeForTest.isNameValid("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}