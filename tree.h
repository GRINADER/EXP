#pragma once
#define RED 0
#define BLACK 1

#include "List.h"
#include <iostream>

#define underlineON "\033[4m"
#define underlineOFF "\033[0m"

using namespace std;

template<typename T>

class Tree
{
    template<typename T>
    class Node
    {
    public:
        Node* parent;
        Node* left;
        Node* right;
        bool color;
        T data;

        Node(T value = T(), Node* parent1 = nullptr, Node* left1 = nullptr, Node* right1 = nullptr, bool color1 = RED)
        {
            data = value;
            parent = parent1;
            left = left1;
            right = right1;
            color = color1;
        }
    };

    Node<T>* root;
    Node<T>* leaf;
    unsigned int size;

    void insert(Node<T>* parent, T data)
    {
        if (data < parent->data)
        {
            if (parent->left != leaf)
                insert(parent->left, data);
            else
            {
                parent->left = new Node<T>(data, parent, leaf, leaf);
                size++;
                if (parent->color == RED)
                    uncleCheck(parent->left);
            }
        }
        else
        {
            if (parent->right != leaf)
                insert(parent->right, data);
            else
            {
                parent->right = new Node<T>(data, parent, leaf, leaf);
                size++;
                if (parent->color == RED) 
                    uncleCheck(parent->right);
            }
        }

    } 
    void uncleCheck(Node<T>* node)
    {
        Node<T>* parent = node->parent;
        Node<T>* grandparent = parent->parent;

        if (grandparent->left == parent)
        {
            Node<T>* uncle = grandparent->right;

            if (uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                if (grandparent == root)
                    return;
                grandparent->color = RED;
                if (grandparent->parent->color == RED)
                    uncleCheck(grandparent);
            }
            else
            {
                if (parent->right == node) 
                {
                    parent->right = node->left;
                    parent->right->parent = parent;
                    parent->parent = node;
                    node->parent = grandparent;
                    node->left = parent;
                    grandparent->left = node;
                    node = parent;
                    parent = parent->parent;
                }

                grandparent->left = parent->right;
                if (grandparent->left != leaf)
                    grandparent->left->parent = grandparent;
                grandparent->left->parent = grandparent;
                parent->right = grandparent;

                parent->parent = grandparent->parent;

                if (grandparent != root) 
                {
                    if (grandparent->parent->left == grandparent) 
                        grandparent->parent->left = parent;
                    else
                        grandparent->parent->right = parent;
                }
                else 
                    root = parent;

                grandparent->parent = parent;

                parent->color = BLACK;
                grandparent->color = RED;


            }
        }
        else 
        {
            Node<T>* uncle = grandparent->left;

            if (uncle->color == RED) 
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                if (grandparent == root)
                    return;
                grandparent->color = RED;
                if (grandparent->parent->color == RED) 
                    uncleCheck(grandparent);
            }
            else 
            {
                if (parent->left == node) 
                {
                    parent->left = node->right;
                    parent->left->parent = parent;
                    parent->parent = node;
                    node->parent = grandparent;
                    node->right = parent;
                    grandparent->right = node;
                    node = parent;
                    parent = parent->parent;
                }

                Node<T>* sibling = parent->left;

                grandparent->right = parent->left;
                if (grandparent->right != leaf)
                    grandparent->right->parent = grandparent;
                parent->left = grandparent;

                parent->parent = grandparent->parent;

                if (grandparent != root) 
                {
                    if (grandparent->parent->right == grandparent) 
                    {
                        grandparent->parent->right = parent;
                    }
                    else 
                        grandparent->parent->left = parent;
                }
                else 
                    root = parent;
                grandparent->parent = parent;

                parent->color = BLACK;
                grandparent->color = RED;


            }
        }
    } //
    void check_remove(Node<T>* node); //
    void repair_remove(Node<T>* child, bool leafs); //
    void clear(Node<T>* node);//
    void fillList(List<T>& lst, Node<T>* current)
    {
        if (current == leaf)
            return;
        fillList(lst, current->left);
        lst.push_back(current->data);
        fillList(lst, current->right);
    }//
    void print(int index, int spaces, Node<T>* q)//
    {
        if (index < size)
        {
            if (q->right != nullptr)
                print(index, spaces + 4, q->right);
            for (int i = 0; i < spaces; i++)
                cout << ' ';
            if (q->color == BLACK)
            {
                cout << underlineON;
                if (q == leaf)
                    cout << "NIL";
                else
                    cout << q->data;
                cout << underlineOFF << endl;
            }
            else
                cout << q->data << endl;

            if (q->left != nullptr)
                print(index, spaces + 4, q->left);
            if (q != leaf)
                index++;
        }
    }
    
public:
    Tree();
    ~Tree();

    void insert(T data);
    void get_data(List<T>& tree)
    {
        tree.clear();
        if (size == 0)
            return;
        fillList(tree, root);
    }
    void remove(T data)
    {
        Node<T>* current = root;
        while (size != 0)
        {
            if (current == leaf);
            return;
            if (data < current->data)
                current = current->left;
            else if (data > current->data)
                current = current->right;
            else
            {
                check_remove(current);
                current = root;
            }
        }
    }
    bool find(T data)
    {
        if (size == 0)
            return false;
        Node<T>* current = root;
        while (current != leaf)
        {
            if (data == current->data)
                return true;
            else if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }
    void clear()
    {
        if (size == 0)
            return;
        clear(root->left);
        clear(root->right);
        delete root;
        size--;
    }
    void print();
};

template<typename T>
void Tree<T>::check_remove(Node<T>* node) // proverka nalichiya detey y yzla kotoriy mi htim ydalit', + checking color
{
    if ((node->left == leaf) && (node->right == leaf))
    {
        if (node == root)
        {
            delete root;
            root = nullptr;
            size--;
        }
        else if (node->color == RED)
        {
            if (node->parent->left == node)
                node->parent->left = leaf;
            else
                node->parent->right = leaf;
            delete node;
            size--;
        }
        else
            repair_remove(node, true);
    }
    else if ((node->left != leaf) && (node->right == leaf))
    {
        if (node == root)
        {
            root = node->left;
            node->left->parent = nullptr;
            node->left->color = BLACK;
            delete node;
            size--;
        }
        else if (node->color == RED)
        {
            if (node->parent->left == node) 
            {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            else
            {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            delete node;
            size--;
        }
    }
    else if ((node->left == leaf) && (node->right != leaf))
    {
        if (node == root) 
        {
            root = node->right;
            node->right->parent = nullptr;
            node->right->color = BLACK;
            delete node;
            size--;
        }
        else if (node->color == RED)
        {
            if (node->parent->left == node) 
            {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }
            else 
            {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            delete node;
            size--;
        }
        else
            repair_remove(node, true);
    }
    if ((node->left != leaf) && (node->right != leaf))
    {
        if (node == root) 
        {
            root = node->left;
            node->left->parent = nullptr;
            node->left->color = BLACK;
            delete node;
            size--;
        }
        else if (node->color == RED)
        {
            if (node->parent->left == node) 
            {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            else 
            {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            delete node;
            size--;
        }
        else
            repair_remove(node, true);
    }
    else 
    {
        Node<T>* current = node->right;
        while (current->left != leaf)
            current = current->left;
        node->data = current->data;
        check_remove(current);
    }
}

template<typename T>
void Tree<T>::repair_remove(Node<T>* node, bool leafs)
{
    Node<T>* parent = node->parent;
    bool nodeLeft;

    if (leafs == true)
    {
        if (node->left != leaf)
        {
            node->left->parent = parent;
            node->left->color = BLACK;
            if (node == parent->left)
                parent->left = node->left;
            else
                parent->right = node->left;
            delete node;
            size--;
            return;
        }
        else if (node->right != leaf)
        {
            node->right->parent = parent;
            node->right->color = BLACK;
            if (node == parent->left)
                parent->left = node->right;
            else
                parent->right = node->right;
            delete node;
            size--;
            return;
        }
        else
        {
            if (node == parent->left)
            {
                nodeLeft = true;
                parent->left = leaf;
            }
            else
            {
                nodeLeft = false;
                parent->right = leaf;
            }
            delete node;
            size--;
        }
    }

    Node<T>* grandparent = parent->parent;
    Node<T>* sibling;
    if (leafs == true)
    {
        if (nodeLeft)
            sibling = parent->right;
        else
            sibling = parent->left;
    }
    else
    {
        if (node == parent->left)
        {
            nodeLeft = true;
            sibling = parent->right;
        }
        else
        {
            nodeLeft = false;
            sibling = parent->left;
        }
    }

    Node<T>* SL = sibling->left;
    Node<T>* SR = sibling->right;

    if (sibling->color == RED)
    {
        parent->parent = sibling;
        SL->parent = parent;


        if (root == parent)
        {
            root = sibling;
            sibling->parent = nullptr;
        }
        else
        {
            if (grandparent->left == parent)
                grandparent->left = sibling;
            else
                grandparent->right = sibling;
            sibling->parent = grandparent;
        }

        if (nodeLeft == true)
        {
            parent->right = SL;
            sibling->left = parent;
        }
        else
        {
            parent->left = SL;
            sibling->right = parent;
        }

        parent->color = RED;
        sibling->color = BLACK;

        sibling = SL;
        SL = sibling->left;
        SR = sibling->right;
    }

    if (parent->color == BLACK && sibling->color == BLACK && SL->color == BLACK && SR->color == BLACK) // case 2, not final, requires checking parent as node
    {
        sibling->color = RED;
        repair_remove(parent, false);
        return;
    }

    if (sibling->color == BLACK && SL->color == BLACK && SR->color == BLACK && parent->color == RED) // case 3, final
    {
        parent->color = BLACK;
        sibling->color = RED;
        return;
    }

    if (nodeLeft == true) 
    {
        if (SL->color == RED && SR->color == BLACK) 
        {
            SL->parent = parent;
            parent->right = SL;
            SL->right->parent = sibling;
            sibling->left = SL->right;
            SL->right = sibling;
            sibling->parent = SL;
            SL->color = BLACK;
            sibling->color = RED;
            sibling = SL;
            SL = SL->left;
            SR = sibling;
        }
    }
    if (SR->color == RED) 
    {
        sibling->color = parent->color;
        parent->color = BLACK;
        SR->color = BLACK;
        parent->right = SL;
        SL->parent = parent;
        sibling->left = parent;
        parent->parent = sibling;
        if (root == parent)
        {
            root = sibling;
            sibling->parent = nullptr;
        }
        else
        {
            sibling->parent = grandparent;
            if (grandparent->left == parent) 
                grandparent->left = sibling;
            else
                grandparent->right = sibling;
        }
    }
    else 
    {
        if (SR->color == RED && SL->color == BLACK) 
        {
            SR->parent = parent;
            parent->left = SR;
            SR->left->parent = sibling;
            sibling->right = SR->left;
            SR->left = sibling;
            sibling->parent = SR;
            SR->color = BLACK;
            sibling->color = RED;
            sibling = SR;
            SL = sibling;
            SR = SR->right;
        }

        if (SL->color == RED) 
        {
            sibling->color = parent->color;
            parent->color = BLACK;
            SL->color = BLACK;
            parent->left = SR;
            SR->parent = parent;
            sibling->right = parent;
            parent->parent = sibling;
            if (root == parent)
            {
                root = sibling;
                sibling->parent = nullptr;
            }
            else
            {
                sibling->parent = grandparent;
                if (grandparent->left == parent) 
                    grandparent->left = sibling;
                else 
                    grandparent->right = sibling;
            }
        }
    }
    leaf->color = BLACK;
    leaf->parent = nullptr;
    leaf->left = nullptr;
    leaf->right = nullptr;
}

template<typename T>
void Tree<T>::clear(Node<T>* node)
{
    if (node == leaf)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
    size--;
}

template<typename T>
 Tree<T>::Tree()
{
    size = 0;
    root = nullptr;
    leaf = new Node<T>(NULL, nullptr, nullptr, nullptr, BLACK);
}

template<typename T>
Tree<T>::~Tree()
{
    clear();
}

template<typename T>
void Tree<T>::insert(T data)
{
    if (size == 0)
    {
        root = new Node<T>(data, nullptr, leaf, leaf, BLACK);
        size++;
        return;
    }
    insert(root, data);
}

template<typename T>
void Tree<T>::print()
{
    int index = 0;
    int spaces = 0;

    if (index < size)
    {
        if (root->right != leaf)
            print(index, spaces + 4, root->right);
        for (int i = 0; i < spaces; i++)
            cout << ' ';
        if (root->color == BLACK)
        {
            cout << underlineON << root->data;
            cout << underlineOFF << endl;
        }
        else
            cout << root->data << endl;
        if (root->left != leaf)
            print(index, spaces + 4, root->left);
        index++;
    }
}