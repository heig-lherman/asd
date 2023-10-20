#ifndef ASD_2021_AVL_H
#define ASD_2021_AVL_H

#include <string>
#include <array>
#include <iostream>

#include "avlNode.h"

template<typename Key> class avlTree;

template <typename Key> std::ostream& operator<<(std::ostream& out, avlTree<Key> const& tree);
template <typename Key> std::istream& operator>>(std::istream& in, avlTree<Key> & tree);

template<typename Key>
class avlTree {
    friend std::ostream &operator<<<>(std::ostream &, avlTree<Key> const &);
    friend std::istream &operator>><>(std::istream &, avlTree<Key> &);

    avl::Node<Key>* root;
public:

    avlTree();
    void insert(Key const &k);
    avlTree(avlTree const &other);
    avlTree(std::initializer_list<Key> const &values);
    avlTree &operator=(avlTree const &other);
    ~avlTree();

    bool contains(Key const& k) const noexcept ;

    Key const& min() const;
    Key const& max() const;

    void erase_min();
    void erase_max();
    void erase(Key const& k) noexcept ;

    [[nodiscard]] unsigned char height() const noexcept;
    std::ostream& show_indented(std::ostream& out = std::cout) const;
};

#include "avlTreeImplementation.h"

#endif //ASD_2021_AVL_H
