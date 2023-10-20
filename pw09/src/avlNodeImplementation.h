#ifndef ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
#define ASD_LABS_2021_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"

namespace avl {

    template<typename Key>
    std::istream &parse_stream(std::istream &in, Node<Key> *&out) {
        if (::isdigit(std::ws(in).peek())) {
            in >> std::skipws >> out;

            if (std::ws(in).get() != '(') {
                throw std::invalid_argument("Expected '(' after parent node");
            }

            parse_stream(in, out->left());

            if (std::ws(in).get() != ',') {
                throw std::invalid_argument("Expected ',' after left node");
            }

            parse_stream(in, out->right());

            update_height(out);

            if (std::ws(in).get() != ')') {
                throw std::invalid_argument("Expected ')' after right node");
            }

            return in;
        }

        if (std::ws(in).get() == '.') {
            return in;
        }

        throw std::invalid_argument("Expected '.' if the node is empty");
    }

    template<typename Key>
    void insert_in_subtree(Node<Key> *&r, Key const &k) {
        if (r == nullptr) {
            r = new Node<Key>{k, Node<Key>::NO_CHILD, 1};
        } else if (k == r->key) {
            return;
        } else {
            Side s = k < r->key ? LEFT : RIGHT;
            insert_in_subtree(r->children[s], k);
            rebalance(r);
        }
    }

    template<typename Key>
    Node<Key> *copy(const Node<Key> *const &node) {
        if (node == nullptr) {
            return nullptr;
        }

        Node<Key> *leftTree = copy(node->left());
        Node<Key> *rightTree = copy(node->right());

        return new Node<Key>{node->key, leftTree, rightTree, node->height};
    }

    template<typename Key>
    unsigned char height(const Node<Key> *const &node) noexcept {
        return node ? node->height : 0;
    }

    template<typename Key>
    void update_height(Node<Key> *const &r) noexcept {
        if (r == nullptr) {
            return;
        }

        r->height = std::max(height(r->left()), height(r->right())) + 1;
    }

    template<typename Key>
    void destroy(Node<Key> *&node) noexcept {
        if (node != nullptr) {
            destroy(node->left());
            destroy(node->right());
            delete node;
            node = nullptr;
        }
    }

    template<typename Key>
    bool contains(const Node<Key> *const &node, Key const &k) noexcept {
        if (node == nullptr) {
            return false;
        }

        if (k == node->key) {
            return true;
        }

        return contains(node->children[k < node->key ? LEFT : RIGHT], k);
    }

    template<typename Key>
    const Node<Key> *const &extremum_node(const Node<Key> *const &node, Side side) {
        if (node == nullptr) {
            throw std::invalid_argument("Empty tree");
        }

        return node->children[side]
               ? extremum_node(node->children[side], side)
               : node;
    }

    template<typename Key>
    Key const &extremum_key(const Node<Key> *const &node, Side side) {
        return extremum_node(node, side)->key;
    }

    template<typename Key>
    Node<Key> *remove_min(Node<Key> *&node) noexcept {
        if (node->left()) {
            return remove_min(node->left());
        }

        Node<Key>* remove = node;
        node = node->right();
        return remove;
    }

    template<typename Key>
    void erase(Node<Key> *&node, Key const &k) noexcept {
        if (node == nullptr) {
            return;
        }

        if (k < node->key) {
            erase(node->left(), k);
            rebalance(node);
            return;
        }

        if (k > node->key) {
            erase(node->right(), k);
            rebalance(node);
            return;
        }

        Node<Key> *tmp = node;
        if (node->left() == nullptr) {
            node = node->right();
        } else if (node->right() == nullptr) {
            node = node->left();
        } else {
            Node<Key> *min = remove_min(node->right());
            min->right() = node->right();
            min->left() = node->left();
            node = min;
        }

        delete tmp;
    }

    template<typename Key>
    void rotate(Node<Key> *&node, Side side) noexcept {
        Node<Key> *tmp = node->children[size_t(side + 1) % 2];
        node->children[size_t(side + 1) % 2] = tmp->children[side];
        tmp->children[side] = node;
        node = tmp;

        update_height(node->children[side]);
        update_height(node);
    }

    template<typename Key>
    int balance_factor(const Node<Key> *const &node) noexcept {
        if (node == nullptr) {
            return 0;
        }

        return height(node->left()) - height(node->right());
    }

    template<typename Key>
    void rebalance(Node<Key> *&node) noexcept {
        if (node == nullptr) {
            return;
        }

        if (balance_factor(node) < -1) {
            if (balance_factor(node->right()) > 0) {
                rotate(node->right(), RIGHT);
            }

            rotate(node, LEFT);
            return;
        }

        if (balance_factor(node) > 1) {
            if (balance_factor(node->left()) < 0) {
                rotate(node->left(), LEFT);
            }

            rotate(node, RIGHT);
            return;
        }

        update_height(node);
    }

    template<typename Key>
    std::ostream &show_indented(
            const Node<Key> *const &r,
            std::ostream &out,
            std::string before,
            bool isright
    ) {
        out << before;
        if (!r) {
            out << ".\n";
        } else {
            if (!before.empty()) {
                before[before.size() - 2] = ' ';
                if (isright) {
                    before[before.size() - 3] = ' ';
                }
            }
            out << r->key << std::endl;
            if (r->children != Node<Key>::NO_CHILD) {
                for (Side s: {LEFT, RIGHT}) {
                    show_indented(r->children[s], out, before + "|_ ", s);
                }
            }
        }
        return out;
    }

    template<typename Key>
    std::ostream &show_inline(
            const Node<Key> *const &r,
            std::ostream &out
    ) {
        if (!r) {
            return out << ".";
        }

        out << r->key << "(";
        show_inline(r->left(), out);
        out << ",";
        show_inline(r->right(), out);
        out << ")";

        return out;
    }

    template<typename Key>
    std::istream &operator>>(std::istream &in, Node<Key> *&node) {
        Key key;
        in >> key;
        insert_in_subtree(node, key);
        return in;
    }

}

#endif //ASD_LABS_2021_AVLNODEIMPLEMENTATION_H
