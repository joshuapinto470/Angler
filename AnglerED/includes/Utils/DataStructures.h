#pragma once

#include <pch.h>

namespace DS
{
    template <typename T> class Node
    {
        std::vector<Node<T> *> m_children;
        Node<T> *m_parent;
        T enitiy;

      public:
        Node();
        const std::vector<Node<T> *> &getChildren() const;
        const Node<T> *getParent() const;
        const T &getData() const;
        T &getData();

        void addChild(Node<T> *);
    };

    template <typename T> Node<T>::Node()
    {
        m_parent = nullptr;
        m_children = std::vector<T>();
    }

    template <typename T> inline const std::vector<Node<T> *> &Node<T>::getChildren() const
    {
        return m_children;
    }

    template <typename T> inline const Node<T> *Node<T>::getParent() const
    {
        return m_parent;
    }

    template <typename T> inline const T &Node<T>::getData() const
    {
        return T;
    }

    template <typename T> inline T &Node<T>::getData()
    {
        return T;
    }

    template <typename T> inline void Node<T>::addChild(Node<T> *node)
    {
        m_children.push_back(node);
    }

} // namespace DS
