#ifndef LAB4_MEPHI_TREE_H
#define LAB4_MEPHI_TREE_H

#include "../Lab2-mephi/MapReduce.h"
#include "../Lab2-mephi/ArraySequence.h"

template <typename T>
class BinaryTree;

template <typename T>
class Node
{
private:
    friend class BinaryTree<T>;

    T data;
    Node<T> *left;
    Node<T> *right;

    void SetLeft(Node<T> *node)
    {
        this->left = node;
    }

    void SetRight(Node<T> *node)
    {
        this->right = node;
    }

    void SetValue(T value)
    {
        this->data = value;
    }
public:
    Node()
    {
        this->data = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    explicit Node(T data)
    {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }

    T GetValue()
    {
        return this->data;
    }

    Node<T> *GetLeft()
    {
        return this->left;
    }

    Node<T> *GetRight()
    {
        return this->right;
    }

    ~Node()
    {
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class BinaryTree {
private:
    Node<T> *root;

    void DeleteTree(Node<T> *node)
    {
        if (node != nullptr)
        {
            DeleteTree(node->GetLeft());
            DeleteTree(node->GetRight());
            delete node;
        }
    }

    void SetToArray(Node<T> *node, MutableArraySequence<T> *arr)
    {
        if (node != nullptr)
        {
            SetToArray(node->GetLeft(), arr);
            arr->Append(node->GetValue());
            SetToArray(node->GetRight(), arr);
        }
    }

    Node<T> *CopyTree(Node<T> *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        auto *newNode = new Node<T>(node->GetValue());
        newNode->SetLeft(CopyTree(node->GetLeft()));
        newNode->SetRight(CopyTree(node->GetRight()));
        return newNode;
    }

    bool AreIdentical(Node<T> *node1, Node<T> *node2)
    {
        if (node1 == nullptr && node2 == nullptr)
        {
            return true;
        }
        if (node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        return node1->GetValue() == node2->GetValue() &&
               AreIdentical(node1->GetLeft(), node2->GetLeft()) &&
               AreIdentical(node1->GetRight(), node2->GetRight());
    }

    Node<T> *Insert(Node<T> *node, const T value)
    {
        if (node == nullptr) {
            return new Node<T>(value);
        }
        if (value < node->GetValue()) {
            node->SetLeft(Insert(node->GetLeft(), value));
        } else if (value > node->GetValue()) {
            node->SetRight(Insert(node->GetRight(), value));
        }
        return node;
    }

    Node<T> *Find(Node<T> *node, const T value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (value == node->GetValue())
        {
            return node;
        }
        if (value < node->GetValue())
        {
            return Find(node->GetLeft(), value);
        }
        else
        {
            return Find(node->GetRight(), value);
        }
    }

    Node<T> *DeleteElement(Node<T> *node, const T value)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (value < node->GetValue())
        {
            root->SetLeft(DeleteElement(node->GetLeft(), value));
        }
        else if (value > node->GetValue())
        {
            node->SetRight(DeleteElement(node->GetRight(), value));
        }
        else
        {
            if (node->GetLeft() == nullptr)
            {
                Node<T> *tmp = node->GetRight();
                delete node;
                return tmp;
            }
            else if (node->GetRight() == nullptr)
            {
                Node<T> *tmp = root->GetLeft();
                delete node;
                return tmp;
            }
            Node<T> *tmp = FindMin(node->GetRight());
            node->SetValue(tmp->GetValue());
            node->SetRight(DeleteElement(node->GetRight(), tmp->GetValue()));
        }
        return node;
    }

    void Map(Node<T> *node, T (*func)(T))
    {
        if (node == nullptr)
        {
            return;
        }
        Map(node->GetLeft(), func);
        Map(node->GetRight(), func);
        node->SetValue(func(node->GetValue()));
    }

    void Where(Node<T> *node, bool (*func)(T))
    {
        if (node == nullptr)
        {
            return;
        }
        Where(node->GetLeft(), func);
        Where(node->GetRight(), func);
        if (!func(node->GetValue())) {
            this->DeleteElement(node->GetValue());
        }
    }

    T Reduce(Node<T> *node, T (*func)(T, T), T init)
    {
        auto *array = new MutableArraySequence<T>();
        SetToArray(node, array);
        T result = reduce(*array, func, init);
        delete array;
        return result;
    }

    bool IsSubTree(Node<T> *node, Node<T> *subNode)
    {
        if (subNode == nullptr) {
            return true;
        }

        if (node == nullptr) {
            return false;
        }

        if (node->GetValue() == subNode->GetValue()) {
            return AreIdentical(node, subNode);
        }

        return IsSubTree(node->GetLeft(), subNode) || IsSubTree(node->GetRight(), subNode);
    }

    Node<T> *FindMax(Node<T> *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->GetRight() == nullptr)
        {
            return node;
        }
        return FindMax(node->GetRight());
    }

    Node<T> *FindMin(Node<T> *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->GetLeft() == nullptr)
        {
            return node;
        }
        return FindMin(node->GetLeft());
    }

public:
    BinaryTree<T>()
    {
        this->root = nullptr;
    }

    explicit BinaryTree<T>(Node<T> *node)
    {
        this->root = node;
    }

    BinaryTree<T>(const BinaryTree<T> &tree)
    {
        this->root = CopyTree(tree.root);
    }

    ~BinaryTree()
    {
        DeleteTree(this->root);
    }

    Node<T> *GetRoot()
    {
        return this->root;
    }

    Node<T> *Insert(const T value)
    {
        this->root = Insert(this->root, value);
        return this->root;
    }

    Node<T> *Find(const T value)
    {
        return Find(this->root, value);
    }

    bool IsElementInTree(const T value)
    {
        return Find(this->root, value);
    }

    Node<T> *FindMin()
    {
        return FindMin(this->root);
    }

    Node<T> *FindMax()
    {
        return FindMax(this->root);
    }

    Node<T> *DeleteElement(const T value) {
        Node<T> *newRoot = DeleteElement(this->root, value);
        this->root = newRoot;
        return newRoot;
    }

    void Map(T (*func)(T))
    {
        Map(this->root, func);
    }

    void Where(bool (*func)(T))
    {
        Where(this->root, func);
    }

    T Reduce(T (*func)(T, T), T init)
    {
        T result = Reduce(this->GetRoot(), func, init);
        return result;
    }

    BinaryTree<T> GetSubTree(const T value) {
        Node<T> *node = Find(value);
        if (node == nullptr) {
            return BinaryTree<T>(nullptr);
        }
        Node<T> *subRoot = CopyTree(node);
        return BinaryTree<T>(subRoot);
    }

    bool IsSubTree(BinaryTree<T> &subTree) {
        return IsSubTree(this->root, subTree.root);
    }
};

#endif //LAB4_MEPHI_TREE_H
