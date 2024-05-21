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
        const std::vector<Node<T> *> &getChildren() const;
        const Node<T> *getParent() const;
        const T &getData() const;
    };
} // namespace DS
