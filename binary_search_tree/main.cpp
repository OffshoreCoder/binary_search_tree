#include <iostream>

struct Tree {
    struct Node {
        int key = 0;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };


    Node *root = nullptr;

    //Поиск миимального элемента в дереве
    Node* min (Node* x) {
        if (x->left == nullptr) {
            return x;
        }

        return min(x->left);
    }

    //Поиск максимального элемента в дереве
    Node* max (Node* x) {
        if (x->right == nullptr) {
            return x;
        }
        return max(x->right);
    }

    //Проверка на пустоту
    bool empty () {
        return root == nullptr;
    }

    //Поиск элемента по ключу
    Node *search (Node* x, int num) {
        if (x == nullptr || num == x->key) {
            return x;
        }

        if (num < x->key) {
            return search(x->left, num);
        }

        if (num > x->key) {
            return search(x->right, num);
        }
    }

    //Поиск следующего элемента
    Node* next (Node* x) {
        if (x->right != nullptr) {
            return min(x->right);
        }
        Node* y = x->parent;

        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    //Поиск предыдущего элемента
    Node* prev (Node* x) {
        if (x->left != nullptr) {
            return max(x->left);
        }
        Node* y = x->parent;

        while (y != nullptr && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // Вставка
    void insert (int num) {
        if (search(root, num) != nullptr) return;

        Node *new_node = new Node;
        new_node->key = num;

        if (empty()) {
            root = new_node;
            return;
        }

        if (search(root, num) == nullptr) {
            Node *help_node = root;

            while (help_node != nullptr) {
                if (new_node->key > help_node->key) {
                    if (help_node->right != nullptr) {
                        help_node = help_node->right;
                    } else {
                        new_node->parent = help_node;
                        help_node->right = new_node;
                        return;
                    }
                } else if (new_node->key < help_node->key) {
                    if (help_node->left != nullptr) {
                        help_node = help_node->left;
                    } else {
                        new_node->parent = help_node;
                        help_node->left = new_node;
                        return;
                    }
                }
            }
        }

        else return;
    }

    // Удаление узла
    void del (int num) {
        Node *node = search(root, num);

        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            if (node->parent == nullptr) {
                root = nullptr;
            } else {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            }
            delete node;
        }

        else if (node->left == nullptr || node->right == nullptr) {
            if (node->left != nullptr) {
                if (node->parent == nullptr) {
                    root = node->left;
                    root->parent = nullptr;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = node->left;
                    } else {
                        node->parent->right = node->left;
                    }
                    node->left->parent = node->parent;
                }
            } else {
                if (node->parent == nullptr) {
                    root = node->right;
                    root->parent = nullptr;
                } else {
                    if (node->parent->left == node) {
                        node->parent->left = node->right;
                    } else {
                        node->parent->right = node->right;
                    }
                    node->right->parent = node->parent;
                }
            }
            delete node;
        }

        else {
            Node *help_node = next(node);
            node->key = help_node->key;
            del(help_node->key);
        }
    }

};



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int num = 0;
    std::string str;

    Tree My_Tree;

    while (std::cin >> str) {
        std::cin >> num;

        if (str == "insert") {
            My_Tree.insert(num);
        }

        else if (str == "delete") {
            My_Tree.del(num);
        }

        else if (str == "next") {
            if (My_Tree.search(My_Tree.root, num) != nullptr) {
                if (My_Tree.next(My_Tree.search(My_Tree.root, num)) != nullptr) {
                    std::cout << My_Tree.next(My_Tree.search(My_Tree.root, num))->key << "\n";
                }
                else {
                    std::cout << "none" << "\n";
                }
            }

            else {
                My_Tree.insert(num);
                if (My_Tree.next(My_Tree.search(My_Tree.root, num)) != nullptr) {
                    std::cout << My_Tree.next(My_Tree.search(My_Tree.root, num))->key << "\n";
                }
                else {
                    std::cout << "none" << "\n";
                }
                My_Tree.del(num);
            }
        }

        else if (str == "prev") {
            if (My_Tree.search(My_Tree.root, num) != nullptr) {
                if (My_Tree.prev(My_Tree.search(My_Tree.root, num)) != nullptr) {
                    std::cout << My_Tree.prev(My_Tree.search(My_Tree.root, num))->key << "\n";
                }
                else {
                    std::cout << "none" << "\n";
                }
            }

            else {
                My_Tree.insert(num);
                if (My_Tree.prev(My_Tree.search(My_Tree.root, num)) != nullptr) {
                    std::cout << My_Tree.prev(My_Tree.search(My_Tree.root, num))->key << "\n";
                }
                else {
                    std::cout << "none" << "\n";
                }
                My_Tree.del(num);
            }
        }

        else if (str == "exists") {
            if (My_Tree.search(My_Tree.root, num)) {
                std::cout << "true" << "\n";
            } else {
                std::cout << "false" << "\n";
            }
        }
    }

    return 0;
}
