#define CATCH_CONFIG_FAST_COMPILE

#include "catch.hpp"
#include "../avlTree.h"

#include <sstream>
#include <string>

using namespace std;

avlTree<int>
make_easy_test_tree() { // order of insertion requires AVL no balancing
    avlTree<int> tree;
    for (int i: {6, 3, 9, 2, 4, 7, 10, 1, 5, 8})
        tree.insert(i);
    return tree;
}

TEST_CASE("insert", "[avlTree]") {

    SECTION("Insert into empty tree") {
        avlTree<int> tree;
        tree.insert(42);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "42\n");
    }

    SECTION("Insert smaller to the left") {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(2);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ 2\n"
                             "|_ .\n");
    }

    SECTION("Insert larger to the right") {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(4);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ .\n"
                             "|_ 4\n");
    }

    SECTION("Insert twice has no effect") {
        avlTree<int> tree;
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "3\n"
                             "|_ .\n"
                             "|_ 4\n");
    }

    SECTION("Easy tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "6\n"
                             "|_ 3\n"
                             "|  |_ 2\n"
                             "|  |  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |_ 4\n"
                             "|     |_ .\n"
                             "|     |_ 5\n"
                             "|_ 9\n"
                             "   |_ 7\n"
                             "   |  |_ .\n"
                             "   |  |_ 8\n"
                             "   |_ 10\n");
    }

    SECTION("Inserting causes rebalance") {
        ostringstream oss;
        avlTree<int> tree = {3, 1, 12};

        oss << tree;
        REQUIRE(oss.str() == "3(1(.,.),12(.,.))");
        oss.str("");

        tree.insert(2);
        tree.insert(10);
        tree.insert(13);
        tree.insert(11);
        tree.insert(7);

        oss << tree;
        REQUIRE(oss.str() == "3(1(.,2(.,.)),12(10(7(.,.),11(.,.)),13(.,.)))");
        oss.str("");

        tree.insert(8);

        oss << tree;
        REQUIRE(oss.str() == "3(1(.,2(.,.)),10(7(.,8(.,.)),12(11(.,.),13(.,.))))");
    }
}

TEST_CASE("display_indented", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == ".\n");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE(oss.str() == "6\n"
                             "|_ 3\n"
                             "|  |_ 2\n"
                             "|  |  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |_ 4\n"
                             "|     |_ .\n"
                             "|     |_ 5\n"
                             "|_ 9\n"
                             "   |_ 7\n"
                             "   |  |_ .\n"
                             "   |  |_ 8\n"
                             "   |_ 10\n");
    }
}

TEST_CASE("operator<<", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == ".");
    }

    SECTION("Easy test tree") {
        avlTree<int> tree = make_easy_test_tree();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() ==
                "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("operator>>", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;

        stringstream in(".");
        in >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == ".");
    }

    SECTION("Tree with values") {
        avlTree<int> tree;

        stringstream in("3(2(1(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        in >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "3(2(1(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        REQUIRE(tree.height() == 6);
    }

    SECTION("Tree with values in incorrect order") {
        avlTree<int> tree;

        stringstream in("1(3(2(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        in >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "1(3(2(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        REQUIRE(tree.height() == 6);
    }

    SECTION("Tree with values with space handling") {
        avlTree<int> tree;

        stringstream in(
                "   3 (2(1(., .),.), 5(4(.,.),6(.,12 (9(8(.,.),. ),.)) ))");
        in >> tree;

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "3(2(1(.,.),.),5(4(.,.),6(.,12(9(8(.,.),.),.))))");
        REQUIRE(tree.height() == 6);
    }

    SECTION("Missing left parenthesis") {
        avlTree<int> tree;

        stringstream in("3(2(1(.,.),.),5(4.,.),6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(in >> tree, std::invalid_argument,
                               Catch::Message(
                                       "Expected '(' after parent node"));
    }

    SECTION("Missing node separation") {
        avlTree<int> tree;

        stringstream in("3(2(1(.,.),.),5(4(..),6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(in >> tree, std::invalid_argument,
                               Catch::Message("Expected ',' after left node"));
    }

    SECTION("Missing right parenthesis") {
        avlTree<int> tree;

        stringstream in("3(2(1(.,.),.),5(4(.,.,6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(in >> tree, std::invalid_argument,
                               Catch::Message("Expected ')' after right node"));
    }

    SECTION("Unknown character") {
        avlTree<int> tree;

        stringstream in("3(2(1(.,.),.),5(4(.,?),6(.,12(9(8(.,.),.),.))))");
        REQUIRE_THROWS_MATCHES(in >> tree, std::invalid_argument,
                               Catch::Message(
                                       "Expected '.' if the node is empty"));
    }
}

TEST_CASE("basic constructor", "[avlTree]") {

    avlTree<int> tree;
    REQUIRE(tree.height() == 0);
}

TEST_CASE("copy constructor", "[avlTree]") {

    SECTION("Copy empty tree") {
        avlTree<int> firstTree;
        avlTree<int> secondTree(firstTree);

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() == ".");
    }

    SECTION("Copy tree with values") {
        avlTree<int> firstTree = make_easy_test_tree();
        avlTree<int> secondTree(firstTree);

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() ==
                "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("operator=", "[avlTree]") {

    SECTION("Assign empty tree onto empty tree") {
        avlTree<int> firstTree;
        avlTree<int> secondTree;

        secondTree = firstTree;

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() == ".");
    }

    SECTION("Assign tree onto empty tree") {
        avlTree<int> firstTree = make_easy_test_tree();
        avlTree<int> secondTree;

        secondTree = firstTree;

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() ==
                "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }

    SECTION("Assign tree onto existing tree") {
        avlTree<int> firstTree = make_easy_test_tree();
        avlTree<int> secondTree = {1, 21, 20, 9, 19, 13};

        secondTree = firstTree;

        ostringstream oss;
        oss << secondTree;
        REQUIRE(oss.str() ==
                "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("destructor", "[avlTree]") {

    SECTION("Destroy empty tree") {
        avlTree<int> tree;
        REQUIRE_NOTHROW(tree.~avlTree());
        REQUIRE(tree.height() == 0);
    }

    SECTION("Destroy tree with values") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE_NOTHROW(tree.~avlTree());
        REQUIRE(tree.height() == 0);
    }

    SECTION("Handles multiple calls") {
        avlTree<int> tree = make_easy_test_tree();
        CHECK_NOTHROW(tree.~avlTree());
        REQUIRE_NOTHROW(tree.~avlTree());
        REQUIRE_NOTHROW(tree.~avlTree());
        REQUIRE(tree.height() == 0);
    }
}

TEST_CASE("contains", "[avlTree]") {

    SECTION("Not found in empty tree") {
        avlTree<int> tree;
        CHECK_FALSE(tree.contains(0));
        CHECK_FALSE(tree.contains(42));
    }

    SECTION("Contained in tree") {
        avlTree<int> tree = make_easy_test_tree();
        CHECK(tree.contains(7));
        CHECK(tree.contains(10));
    }

    SECTION("Not contained in tree") {
        avlTree<int> tree = make_easy_test_tree();
        CHECK_FALSE(tree.contains(42));
        CHECK_FALSE(tree.contains(14));
    }
}

TEST_CASE("min", "[avlTree]") {

    SECTION("Throws if empty") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.min(), std::invalid_argument,
                               Catch::Message("Empty tree"));
    }

    SECTION("Returns min value") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.min() == 1);
    }
}

TEST_CASE("max", "[avlTree]") {

    SECTION("Throws if empty") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.max(), std::invalid_argument,
                               Catch::Message("Empty tree"));
    }

    SECTION("Returns max value") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.max() == 10);
    }
}

TEST_CASE("erase_min", "[avlTree]") {

    SECTION("Throws if empty") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.erase_min(), std::invalid_argument,
                               Catch::Message("Empty tree"));
    }

    SECTION("Erases min value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase_min();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(.,.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }
}

TEST_CASE("erase_max", "[avlTree]") {

    SECTION("Throws if empty") {
        avlTree<int> tree;
        REQUIRE_THROWS_MATCHES(tree.erase_max(), std::invalid_argument,
                               Catch::Message("Empty tree"));
    }

    SECTION("Erases max value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase_max();

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),8(7(.,.),9(.,.)))");
    }
}

TEST_CASE("erase", "[avlTree]") {

    SECTION("Handles empty tree") {
        avlTree<int> tree;
        tree.erase(8);

        REQUIRE(tree.height() == 0);
    }

    SECTION("Handles non-existing value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase(2022);

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() ==
                "6(3(2(1(.,.),.),4(.,5(.,.))),9(7(.,8(.,.)),10(.,.)))");
    }

    SECTION("Handles existing value") {
        avlTree<int> tree = make_easy_test_tree();
        tree.erase(7);

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),9(8(.,.),10(.,.)))");
    }

    SECTION("Handles multiple calls") {
        avlTree<int> tree = make_easy_test_tree();
        for (int i: {7, 8, 9, 10, 1, 2, 3, 4, 5, 6}) {
            tree.erase(i);
        }

        REQUIRE(tree.height() == 0);
    }

    SECTION("Handles multiple calls with multiple values") {
        avlTree<int> tree = make_easy_test_tree();
        for (int i: {7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
            tree.erase(i);
        }

        REQUIRE(tree.height() == 0);
    }

    SECTION("Handles case with rebalance") {
        avlTree<int> tree = {3, 1, 12, 2, 10, 13, 7, 11};
        tree.erase(1);

        ostringstream oss;
        oss << tree;
        REQUIRE(oss.str() == "10(3(2(.,.),7(.,.)),12(11(.,.),13(.,.)))");
    }
}

TEST_CASE("height", "[avlTree]") {

    SECTION("Empty tree") {
        avlTree<int> tree;
        REQUIRE(tree.height() == 0);
    }

    SECTION("Updated after parsed") {
        avlTree<int> tree;
        CHECK(tree.height() == 0);

        stringstream ss("10(3(2(.,.),7(.,.)),12(11(.,.),13(.,.)))");
        ss >> tree;

        REQUIRE(tree.height() == 3);
    }

    SECTION("Updated after insert") {
        avlTree<int> tree = {42};
        REQUIRE(tree.height() == 1);

        tree.insert(1);
        REQUIRE(tree.height() == 2);
    }

    SECTION("Updated after remove") {
        avlTree<int> tree = {42};
        REQUIRE(tree.height() == 1);

        tree.erase(42);
        REQUIRE(tree.height() == 0);
    }

    SECTION("Tree with values") {
        avlTree<int> tree = make_easy_test_tree();
        REQUIRE(tree.height() == 4);
    }
}
