#pragma once

#include <pch.h>
#include <entt/entity/registry.hpp>

/*
FLAG = 0000 0000
dirty  1000 0000
static 0100 0000
hidden 0010 0000
flag & (1 << 7);
*/

namespace DS
{
    template <typename T> class Node
    {
        std::vector<Node<T> *> m_children;
        Node<T> *m_parent;
        T entity;
        u_int8_t flags = 0x00;
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

        void addChild(Node<T> *);
        bool isLeaf() const;
    };

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

        name = "Untitled";
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
        glm::vec3 Diffuse;
        glm::vec2 uv;
    };

    struct Transform
    {
        glm::mat4 transform;
    };

} // namespace DS
