#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H

#include <vector>
#include <memory>
#include <string>

template<typename K, typename V>
class BPlusTree {
private:
    static const int MAX_KEYS = 4; // Maximum number of keys in a node

    struct Node {
        bool is_leaf;
        std::vector<K> keys;
        std::vector<std::shared_ptr<Node>> children;
        std::vector<V> values;  // Only used in leaf nodes
        std::shared_ptr<Node> next_leaf;  // For leaf nodes

        Node(bool leaf = true) : is_leaf(leaf) {}
    };

    std::shared_ptr<Node> root;

public:
    BPlusTree() : root(std::make_shared<Node>()) {}

    void insert(const K& key, const V& value);
    bool remove(const K& key);
    bool find(const K& key, V& value) const;
    void clear();

private:
    void split_child(std::shared_ptr<Node> parent, int index, std::shared_ptr<Node> child);
    void insert_non_full(std::shared_ptr<Node> node, const K& key, const V& value);
};

#endif // BPLUS_TREE_H 