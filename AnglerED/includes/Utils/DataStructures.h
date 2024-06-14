#pragma once

#include <pch.h>
#include <entt/entity/registry.hpp>

/*
FLAG = 0000 0000
dirty  0000 0001
static 0000 0010
hidden 0000 0100
active 0000 1000
flag & (1 << 7);
*/

namespace DS
{
    enum NODE_FLAGS
    {
        DIRTY = (1 << 0),
        STATIC = (1 << 1),
        HIDDEN = (1 << 2),
        ACTIVE = (1 << 3)
    };

    template <typename T> class Node
    {
        std::vector<Node<T> *> m_children;
        Node<T> *m_parent;
        T entity;
        uint8_t flags = 0x00;
        std::string name;

      public:
        Node();
        Node(T);

        const std::vector<Node<T> *> &getChildren() const;
        std::vector<Node<T> *> &getChildren();
        const Node<T> *getParent() const;
        const T &getEntity() const;
        T &getEntity();
        std::string getName() const;
        void setName(std::string &name);
        void setName(const char *);
        void setFlag(NODE_FLAGS);
        bool checkFlag(NODE_FLAGS);
        void addChild(Node<T> *);
        bool isLeaf() const;
    };

    template <typename T> bool Node<T>::checkFlag(NODE_FLAGS flag)
    {
        return flags & flag;
    }

    template <typename T> void Node<T>::setFlag(NODE_FLAGS flag)
    {
        flags |= flag;
    }

    template <typename T> Node<T>::Node()
    {
        m_parent = nullptr;
        // m_children = std::vector<T>();
        name = "Untitled";
    }

    template <typename T> inline Node<T>::Node(T e)
    {
        m_parent = nullptr;
        // m_children = std::vector<T>();
        entity = e;

        name = "Untitled Entity";
    }

    template <typename T> inline const std::vector<Node<T> *> &Node<T>::getChildren() const
    {
        return m_children;
    }

    template <typename T> inline std::vector<Node<T> *> &Node<T>::getChildren()
    {
        return m_children;
    }

    template <typename T> inline const Node<T> *Node<T>::getParent() const
    {
        return m_parent;
    }

    template <typename T> inline const T &Node<T>::getEntity() const
    {
        return entity;
    }

    template <typename T> inline T &Node<T>::getEntity()
    {
        return entity;
    }

    template <typename T> inline std::string Node<T>::getName() const
    {
        return name;
    }

    template <typename T> inline void Node<T>::setName(std::string &name)
    {
        this->name = name;
    }

    template <typename T> inline void Node<T>::setName(const char *name)
    {
        this->name = name;
    }

    template <typename T> inline void Node<T>::addChild(Node<T> *node)
    {
        node->m_parent = this;
        m_children.push_back(node);
    }

    template <typename T> inline bool Node<T>::isLeaf() const
    {
        return m_children.empty();
    }

    typedef Node<entt::entity> ENode;

} // namespace DS

namespace DS
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normals;
        glm::vec2 uv;
    };

    struct Transform
    {
        glm::mat4 transform;
        Transform() : transform(1.0f){};
    };

} // namespace DS
