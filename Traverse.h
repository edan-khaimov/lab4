#ifndef LAB4_MEPHI_TRAVERSE_H
#define LAB4_MEPHI_TRAVERSE_H

#include "Tree.h"

template <typename T>
void PrintKLP(Node<T> *node)
{
    if (node != nullptr)
    {
        std::cout << "(" << node->GetValue() << ") ";
        PrintKLP(node->GetLeft());
        PrintKLP(node->GetRight());
    }
}

template <typename T>
void PrintKPL(Node<T> *node)
{
    if (node != nullptr)
    {
        std::cout << "(" << node->GetValue() << ") ";
        PrintPKL(node->GetRight());
        PrintPKL(node->GetLeft());
    }
}

template <typename T>
void PrintLPK(Node<T> *node)
{
    if (node != nullptr)
    {
        PrintLPK(node->GetLeft());
        PrintLPK(node->GetRight());
        std::cout << "(" << node->GetValue() << ") ";
    }
}

template <typename T>
void PrintPLK(Node<T> *node)
{
    if (node != nullptr)
    {
        PrintPLK(node->GetRight());
        PrintPLK(node->GetLeft());
        std::cout << "(" << node->GetValue() << ") ";
    }
}

template <typename T>
void PrintLKP(Node<T> *node)
{
    if (node != nullptr)
    {
        PrintLKP(node->GetLeft());
        std::cout << "(" << node->GetValue() << ") ";
        PrintLKP(node->GetRight());
    }
}

template <typename T>
void PrintPKL(Node<T> *node)
{
    if (node != nullptr)
    {
        PrintPKL(node->GetRight());
        std::cout << "(" << node->GetValue() << ") ";
        PrintPKL(node->GetLeft());
    }
}

#endif //LAB4_MEPHI_TRAVERSE_H
