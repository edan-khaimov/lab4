#ifndef LAB4_MEPHI_UI_H
#define LAB4_MEPHI_UI_H

#include <vector>
#include <string>
#include <sstream>
#include "MapReduceFunctions.h"

void help()
{
    std::cout << "To get this menu type <help>" << std::endl;
    std::cout << "To finish program type <quit>" << std::endl;
    std::cout << "Available functions for tree:" << std::endl;
    std::cout << "print, insert, delete, is_sub_tree, get_sub_tree, find_min, find_max, map, where, reduce" << std::endl;
    std::cout << "Available traverses for tree:" << std::endl;
    std::cout << "KPL, KLP, LKP, LPK, PKL, PLK" << std::endl;
    std::cout << "Available types of values: double, int, complex" << std::endl;
    std::cout << "To do action type <type> <function> or <type> <traverse>" << std::endl;
}

std::vector<std::string> splitString(const std::string& str)
{
    std::istringstream iss(str);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

template <typename T>
void printTree(const std::string& prefix, Node<T>* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "L--" );

        std::cout << node->GetValue() << std::endl;

        printTree( prefix + (isLeft ? "|   " : "    "), node->GetLeft(), true);
        printTree( prefix + (isLeft ? "|   " : "    "), node->GetRight(), false);
    }
}

template <typename T>
void setTree(BinaryTree<T>& tree)
{
    int amount;
    std::cout << "Enter amount of elements:" << std::endl;
    std::cin >> amount;

    for (int i = 0; i < amount; i++)
    {
        T value;
        std::cout << "Enter value:" << std::endl;
        std::cin >> value;
        tree.Insert(value);
    }
}

template <typename T>
void treeInterface(BinaryTree<T>& tree, const std::string& command)
{
    if (command == "print")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        printTree("", tree.GetRoot(), false);
    }
    else if (command == "insert")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        T value;
        std::cout << "Enter value:" << std::endl;
        std::cin >> value;
        tree.Insert(value);
        printTree(tree);
    }
    else if (command == "delete")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        T value;
        std::cout << "Enter value:" << std::endl;
        std::cin >> value;
        tree.Delete(value);
        printTree(tree);
    }
    else if (command == "is_sub_tree")
    {
        std::cout << "Create main tree:" << std::endl;
        setTree(tree);
        std::cout << "Create sub tree:" << std::endl;
        BinaryTree<T> subTree;
        setTree(subTree);
        tree.IsSubTree(subTree) == 1 ? std::cout << "True" << std::endl : std::cout << "False" << std::endl;
    }
    else if (command == "get_sub_tree")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Enter value:" << std::endl;
        T value;
        std::cin >> value;
        std::cout << "Sub tree:" << std::endl;
        printTree("", tree.GetSubTree(value), false);
    }
    else if (command == "find_min")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Min value: " << tree.FindMin() << std::endl;
    }
    else if (command == "find_max")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Max value: " << tree.FindMax() << std::endl;
    }
    else if (command == "map")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "function: i -> i * i" << std::endl;
        tree.Map(&MapFunc);
        printTree("", tree.GetRoot(), false);
    }
    else if (command == "where")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "function: i -> i % 2 == 0" << std::endl;
        tree.Where(&WhereFunc);
        printTree("", tree.GetRoot(), false);
    }
    else if (command == "reduce")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "function: i, j -> i + j" << std::endl;
        std::cout << "Result: " << tree.Reduce(&ReduceFunc, 0) << std::endl;
    }
    else if (command == "KPL")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Result: " << printKPL(tree) << std::endl;
    }
    else if (command == "LPK")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Result: " << printLPK(tree) << std::endl;
    }
    else if (command == "PKL")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Result: " << printPKL(tree) << std::endl;
    }
    else if (command == "PLK")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Result: " << printPLK(tree) << std::endl;
    }
    else if (command == "LKP")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Result: " << printLKP(tree) << std::endl;
    }
    else if (command == "KLP")
    {
        std::cout << "Create tree:" << std::endl;
        setTree(tree);
        std::cout << "Result: " << printKLP(tree) << std::endl;
    }
    else
    {
        throw std::invalid_argument("Unknown command");
    }
}

#endif //LAB4_MEPHI_UI_H