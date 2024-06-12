#ifndef LAB4_MEPHI_TREE_H
#define LAB4_MEPHI_TREE_H

#include "../Lab2-mephi/MapReduce.h"
#include "../Lab2-mephi/ArraySequence.h"

template <typename T>
class Node
{
private:
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

    template<typename>
    friend class BinaryTree;
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
class BinaryTree
{
private:
    Node<T> *root;

    void deleteTree(Node<T> *node)
    {
        if (node != nullptr)
        {
            deleteTree(node->GetLeft());
            deleteTree(node->GetRight());
            delete node;
        }
    }

    void SetToArray(Node<T> *node, MutableArraySequence<T> *arr) const
    {
        if (node != nullptr)
        {
            SetToArray(node->GetLeft(), arr);
            arr->Append(node->GetValue());
            SetToArray(node->GetRight(), arr);
        }
    }

    Node<T>* CopyTree(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        auto* newNode = new Node<T>(node->GetValue());
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

    Node<T> *GetRoot() const
    {
        return this->root;
    }

    int GetNodesCount(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int count = 1;
        count += GetNodesCount(node->GetLeft());
        count += GetNodesCount(node->GetRight());
        return count;
    }

    int GetNodesCount()
    {
        return GetNodesCount(root);
    }

    Node<T> *Insert(Node<T> *node, const T value)
    {
        if (node == nullptr)
        {
            return new Node<T>(value);
        }
        if (value < node->GetValue())
        {
            node->SetLeft(Insert(node->GetLeft(), value));
        }
        else if (value > node->GetValue())
        {
            node->SetRight(Insert(node->GetRight(), value));
        }
        return node;
    }

    Node<T> *Insert(const T value)
    {
        this->root = Insert(this->root, value);
        return this->root;
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

    Node<T> *Find(const T value)
    {
        return Find(this->root, value);
    }

    bool IsElementInTree(Node<T> *node, const T value)
    {
        return Find(node, value) != nullptr;
    }

    bool IsElementInTree(const T value)
    {
        return IsElementInTree(this->root, value);
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

    Node<T> *FindMin()
    {
        return FindMin(this->root);
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

    Node<T> *FindMax()
    {
        return FindMax(this->root);
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
            if (node->GetLeft() == nullptr) {
                Node<T>* tmp = node->GetRight();
                delete node;
                return tmp;
            }
            else if (node->GetRight() == nullptr)
            {
                Node<T>* tmp = root->GetLeft();
                delete node;
                return tmp;
            }
            Node<T>* tmp = FindMin(node->GetRight());
            node->SetValue(tmp->GetValue());
            node->SetRight(DeleteElement(node->GetRight(), tmp->GetValue()));
        }
        return node;
    }

    Node<T> *DeleteElement(const T value)
    {
        Node<T> *newRoot = DeleteElement(this->root, value);
        this->root = newRoot;
        return newRoot;
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

    void Map(T (*func)(T))
    {
        Map(this->root, func);
    }

    void Where(Node<T> *node, bool (*func)(T))
    {
        if (node == nullptr)
        {
            return;
        }
        Where(node->GetLeft(), func);
        Where(node->GetRight(), func);
        if (!func(node->GetValue()))
        {
            this->DeleteElement(node->GetValue());
        }
    }

    void Where(bool (*func)(T))
    {
        Where(this->root, func);
    }

    T Reduce(Node<T> *node, T (*func)(T, T), T init)
    {
        auto *array = new MutableArraySequence<T>();
        SetToArray(node, array);
        T result = reduce(*array, func, init);
        delete array;
        return result;
    }

    T Reduce(T (*func)(T, T), T init)
    {
        T result = Reduce(this->GetRoot(), func, init);
        return result;
    }

    BinaryTree<T> GetSubTree(const T value)
    {
        Node<T> *node = Find(value);
        if (node == nullptr)
        {
            return BinaryTree<T>(nullptr);
        }
        Node<T> *subRoot = CopyTree(node);
        return BinaryTree<T>(subRoot);
    }

    bool IsSubTree(Node<T> *node, Node<T> *subNode)
    {
        if (subNode == nullptr) {
            return true;
        }

        if (node == nullptr)
        {
            return false;
        }

        if (node->GetValue() == subNode->GetValue())
        {
            return AreIdentical(node, subNode);
        }

        return IsSubTree(node->GetLeft(), subNode) || IsSubTree(node->GetRight(), subNode);
    }

    bool IsSubTree(BinaryTree<T> &subTree)
    {
        return IsSubTree(this->root, subTree.root);
    }

    int GetHeightOfTree(Node<T> *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = GetHeightOfTree(node->GetLeft());
        int rightHeight = GetHeightOfTree(node->GetRight());
        return 1 + std::max(leftHeight, rightHeight);
    }

    int GetHeightOfTree()
    {
        return GetHeightOfTree(this->root);
    }

    ~BinaryTree()
    {
        deleteTree(this->root);
    }
};

#endif //LAB4_MEPHI_TREE_H
