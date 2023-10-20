#ifndef ASD_LABS_2021_AVLNODE_H
#define ASD_LABS_2021_AVLNODE_H

namespace avl {

    enum Side {
        LEFT = 0,
        RIGHT = 1
    };

    template<typename Key>
    struct Node {
        Key const key;
        std::array<Node *, 2> children;
        unsigned char height;

        inline Node *&left() noexcept { return children[LEFT]; }
        inline Node *const &left() const noexcept { return children[LEFT]; }

        inline Node *&right() noexcept { return children[RIGHT]; }
        inline Node *const &right() const noexcept { return children[RIGHT]; }

        static constexpr std::array<Node *, 2> NO_CHILD{nullptr, nullptr};
    };

    template<typename Key>
    std::istream &parse_stream(std::istream &in, Node<Key> *&out);

    template<typename Key>
    void insert_in_subtree(Node<Key> *&r, Key const &k);

    template<typename Key>
    Node<Key> *copy(const Node<Key> *const &node);

    template<typename Key>
    unsigned char height(const Node<Key> *const &node) noexcept;

    template<typename Key>
    void update_height(Node<Key> *const &r) noexcept;

    template<typename Key>
    void destroy(Node<Key> *&node) noexcept;

    template<typename Key>
    bool contains(const Node<Key> *const &node, Key const &k) noexcept;

    template<typename Key>
    const Node<Key> *const &extremum_node(
            const Node<Key> *const &node,
            Side side
    );

    template<typename Key>
    Key const &extremum_key(const Node<Key> *const &node, Side side);

    template<typename Key>
    Node<Key> *remove_min(Node<Key> *&node) noexcept;

    template<typename Key>
    void erase(Node<Key> *&node, Key const &k) noexcept;

    template<typename Key>
    void rotate(Node<Key> *&node, Side side) noexcept;

    template<typename Key>
    int balance_factor(const Node<Key> *const &node) noexcept;

    template<typename Key>
    void rebalance(Node<Key> *&node) noexcept;

    template<typename Key>
    std::ostream &show_indented(
            const Node<Key> *const &r,
            std::ostream &out = std::cout,
            std::string before = "",
            bool isright = false
    );

    template<typename Key>
    std::ostream &show_inline(
            const Node<Key> *const &r,
            std::ostream &out = std::cout
    );

    template<typename Key>
    std::istream &operator>>(std::istream &in, Node<Key> *&node);
}

#include "avlNodeImplementation.h"

#endif //ASD_LABS_2021_AVLNODE_H
