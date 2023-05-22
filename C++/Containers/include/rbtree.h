#ifndef CONTAINERS_INCLUDE_RBTREE_H__
#define CONTAINERS_INCLUDE_RBTREE_H__

#include <cstddef>
#include <iostream>
#include <iterator>

#include "vector.h"

namespace s21_utils {

enum rbColor { kBlack = 0, kRed = 1 };

template <typename T>
struct mapComparator {
  bool operator()(const T &a, const T &b) { return a.first < b.first; }
};

template <class T, typename Comparator>
class rbTree {
  using size_type = std::size_t;

 public:
  using data_type = T;

  /*
  ***************************
  Constructor
  */

  rbTree() {
    std::allocator<rbTreeNode> alloc1;
    header =
        alloc1.allocate(1);  // we create a header node for the simplification
    header->rbColor = kRed;
    header->left = nullptr;
    header->right = nullptr;
    header->parent = nullptr;
    leftmost = nullptr;
    rightmost = nullptr;
    nodesNum = 0;
  };

  /*
  ***************************
  Destructor
  */

  ~rbTree() {
    if (getRoot()) {
      clearTree(getRoot());
      eraseNode(header);
    } else {
      eraseNode(header);
    }
  };

  /*
  ***************************
  Copy constructor
  */

  rbTree(const rbTree &other) {
    if (this != &other) {
      clearTree(getRoot());
      iterator it(this, other.leftmost);
      for (; *it != other.rightmost->data_; ++it) {
        addNode(*it, false);
      }
      addNode(*it, false);
    }
  };

  /*
  ***************************
  Move constructor

  */

  rbTree(rbTree &&other) noexcept {
    this->header->left = other.header->left;
    this->leftmost = other.leftmost;
    this->rightmost = other.rightmost;
    this->nodesNum = other.nodesNum;
    other.header->left = nullptr;
  };

  rbTree &operator=(const rbTree &other) {
    if (this != &other) {
      clearTree(getRoot());
      iterator it(this, other.leftmost);
      for (; *it != other.rightmost->data_; ++it) {
        addNode(*it, false);
      }
      addNode(*it, false);
    }
    return *this;
  }

  rbTree &operator=(rbTree &&other) noexcept {
    this->header->left = other.header->left;
    this->leftmost = other.leftmost;
    this->rightmost = other.rightmost;
    this->nodesNum = other.nodesNum;
    other.header->left = nullptr;
    return *this;
  }

  void copyEqual(const rbTree &other) {
    clearTree(getRoot());
    iterator it(this, other.leftmost);
    for (; *it != other.rightmost->data_; ++it) {
      addNode(*it, true);
    }
    addNode(*it, true);
  }

  /*
  ***************************
  Node structure. Use only key for set/multiset, key-value for map
  */

  struct rbTreeNode {
    rbTreeNode *left;
    rbTreeNode *right;
    rbTreeNode *parent;
    bool rbColor;
    data_type data_;

    template <typename KK>
    explicit rbTreeNode(KK &&data)
        : left(nullptr),
          right(nullptr),
          parent(nullptr),
          data_(std::forward<KK>(data)) {}  // from node.h rbColor?
  };

  /*
  Header is a parent node for the root, which helps
  to avoid checks if root->parent is nullptr. Also root is
  always header->left.

  Leftmost and righmost nodes point to the nodes with
  smallest and largest values in the tree. They provide
  constant complexity for begin() and end() iterators.

  nodesNum holds the number of nodes in the tree.

  */

  rbTreeNode *header;
  rbTreeNode *leftmost;
  rbTreeNode *rightmost;

  size_type nodesNum = 0;

  /*
 ***************************
 Forward Iterator allowing to read values without changing them


 */

  class iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = data_type *;
    using reference = data_type &;
    using self = iterator;

   public:
    iterator() noexcept : ptr_(nullptr), tree_ptr_(nullptr){};

    iterator(const rbTree *Tree, const rbTreeNode *node) noexcept {
      ptr_ = const_cast<rbTreeNode *>(node);
      tree_ptr_ = const_cast<rbTree *>(Tree);
    };

    iterator(const iterator &other) noexcept {
      ptr_ = other.ptr_;
      tree_ptr_ = other.tree_ptr_;
    }

    iterator(iterator &&other) noexcept {
      ptr_ = other.ptr_;
      tree_ptr_ = other.tree_ptr_;
    }

    self &operator=(const iterator &other) noexcept {
      if (this != &other) {
        ptr_ = other.ptr_;
        tree_ptr_ = other.tree_ptr_;
      }
      return *this;
    }

    self &operator=(iterator &&other) noexcept {
      ptr_ = other.ptr_;
      tree_ptr_ = other.tree_ptr_;
      return *this;
    }

    self &operator++() {
      ptr_ = tree_ptr_->getNextNode(ptr_);
      return *this;
    };

    self &operator--() {
      if (ptr_ == nullptr) {
        ptr_ = tree_ptr_->rightmost;
      } else
        ptr_ = tree_ptr_->getPrevNode(ptr_);
      return *this;
    };

    self operator++(int) {
      self tmp = *this;
      ptr_ = tree_ptr_->getNextNode(ptr_);
      return tmp;
    };

    self operator--(int) {
      self tmp = *this;
      if (ptr_ == nullptr) {
        ptr_ = tree_ptr_->rightmost;
      } else
        ptr_ = tree_ptr_->getPrevNode(ptr_);
      return tmp;
    };

    reference operator*() { return ptr_->data_; }

    pointer operator->() { return &ptr_->data_; }

    friend bool operator!=(const self &a, const self &b) noexcept {
      return a.ptr_ != b.ptr_;
    };

    friend bool operator==(const self &a, const self &b) noexcept {
      return a.ptr_ == b.ptr_;
    };

   private:
    rbTreeNode *ptr_;
    rbTree *tree_ptr_;
  };

  /*
 ***************************
 Forward constant iterator allowing to read values without changing them

 */

  class const_iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    typedef const data_type *pointer;
    typedef const data_type &reference;
    using self = const_iterator;
    typedef rbTreeNode *base_ptr;

   public:
    const_iterator() noexcept : ptr_(nullptr), tree_ptr_(nullptr){};

    explicit const_iterator(const iterator &other) noexcept
        : ptr_(other.ptr_), tree_ptr_(other.tree_ptr_){};

    const_iterator(const rbTree *Tree, const rbTreeNode *node) noexcept {
      ptr_ = const_cast<rbTreeNode *>(node);
      tree_ptr_ = const_cast<rbTree *>(Tree);
    };

    reference operator*() const noexcept { return ptr_->data_; }

    pointer operator->() const noexcept { return &ptr_->data_; }

    self &operator++() {
      ptr_ = tree_ptr_->getNextNode(const_cast<base_ptr>(ptr_));
      return *this;
    }

    self operator++(int) {
      self tmp = *this;
      ptr_ = tree_ptr_->getNextNode(ptr_);
      return tmp;
    }

    self &operator--() {
      if (ptr_ == nullptr) {
        ptr_ = tree_ptr_->rightmost;
      } else
        ptr_ = tree_ptr_->getPrevNode(const_cast<base_ptr>(ptr_));
      return *this;
    }

    self operator--(int) {
      self tmp = *this;
      if (ptr_ == nullptr) {
        ptr_ = tree_ptr_->rightmost;
      } else
        ptr_ = tree_ptr_->getPrevNode(const_cast<base_ptr>(ptr_));
      return tmp;
    }

    friend bool operator!=(const self &a, const self &b) noexcept {
      return a.ptr_ != b.ptr_;
    };

    friend bool operator==(const self &a, const self &b) noexcept {
      return a.ptr_ == b.ptr_;
    };

   private:
    rbTreeNode *ptr_;
    rbTree *tree_ptr_;
  };

  /*
  Many funtions depend on the iterator, so it has to be as high
  in the header as possible. But that forces to initialize it with
  tree pointer. Even though it's a tree subclass it doesn't know about
  methods that are declared under. As I understand.
  */

  iterator begin() { return iterator(this, leftmost); }

  iterator end() { return iterator(this, nullptr); }

  const_iterator cbegin() { return const_iterator(this, leftmost); }

  const_iterator cend() { return const_iterator(this, nullptr); }

  /*
  ***************************
  Public methods to work with the tree
  */

  // Erases all existing nodes, but no the header to link new ones later
  void eraseTree() {
    if (header != 0) {
      clearTree(getRoot());
      nodesNum = 0;
    }
  }

  bool isEmpty() const noexcept {
    if (nodesNum == 0)
      return true;
    else
      return false;
  }

  size_type ofSize() const { return static_cast<size_t>(nodesNum); }

  size_type maxSize() const {
    std::allocator<rbTreeNode> alloc1;
    return alloc1.max_size();
  }

  /*
  Adds only new nodes without memory allocation.
  Nodes are just relinked from the other tree.
  */
  void mergeTree(rbTree &other) {
    if (this != &other) {
      for (auto i = other.begin(), e = other.end(); i != e;) {
        auto next = i;
        next++;
        std::pair<int, rbTreeNode *> p = findNode(*i);
        if (p.first != 0) {
          std::pair<int, rbTreeNode *> p2 = other.findNode(*i);
          other.deleteNode(
              p2.second);  // just extracts the node, doesn't affect memory
          rbTreeNode *exstNode = p2.second;
          exstNode->parent = nullptr;
          exstNode->left = nullptr;
          exstNode->right = nullptr;
          insertNode(exstNode, p.second, p.first);
          if (other.nodesNum == 0) break;
        }
        i = next;
      }
    }
  }

  /*
  Adds all nodes without memory allocation.
  Nodes are just relinked from the other tree.
  */
  void mergeTreeEqual(rbTree &other) {
    if (this != &other) {
      for (auto i = other.begin(); i != other.end();) {
        std::pair<int, rbTreeNode *> p = other.findNode(*i);
        rbTreeNode *otherNode = other.getLowerNode(p.second);
        other.deleteNode(
            otherNode);  // just extracts the node, doesn't affect memory
        otherNode->left = nullptr;
        otherNode->right = nullptr;
        otherNode->parent = nullptr;
        std::pair<int, rbTreeNode *> p2 = findNode(*i);
        if (p2.first != 0) {  // the same as in the addNode function
          insertNode(otherNode, p2.second, p2.first);
        } else if (p2.first == 0) {
          addEqual(otherNode, p2.second);
        }
        if (other.nodesNum == 0) break;
        i = other.begin();
      }
      other.header->left = 0;
    }
  }

  iterator findKey(const data_type &data) {
    std::pair<int, rbTreeNode *> p;
    p = findNode(data);
    if (p.first == 0)
      return iterator(this, p.second);
    else
      return end();
  }

  /*
  Only for multiset. If there are more than one equal key,
  we want to find the first/las one.
  */
  rbTreeNode *getLowerNode(rbTreeNode *currentNode) {
    data_type data = currentNode->data_;
    while (currentNode->data_ == data) {
      rbTreeNode *tmp = getPrevNode(currentNode);
      if (tmp && tmp->data_ == data)
        currentNode = tmp;
      else
        break;
    }
    return currentNode;
  }

  rbTreeNode *getUpperNode(rbTreeNode *currentNode) {
    data_type data = currentNode->data_;
    while (currentNode->data_ == data) {
      rbTreeNode *tmp = getNextNode(currentNode);
      if (tmp && tmp->data_ == data)
        currentNode = tmp;
      else
        break;
    }
    return currentNode;
  }

  /*
  Return iterator pointing to the first/last node with the same key.
  */
  iterator lower_bound(const data_type &data) {
    std::pair<int, rbTreeNode *> p = findNode(data);
    if (p.first == 0) {
      rbTreeNode *tempNode = getLowerNode(p.second);
      return iterator(this, tempNode);
    } else {
      rbTreeNode *nextNode = getNextNode(p.second);
      if (nextNode == nullptr)
        return end();
      else
        return iterator(this, nextNode);
    }
  }

  iterator upper_bound(const data_type &data) {
    std::pair<int, rbTreeNode *> p = findNode(data);
    if (p.first == 0) {
      rbTreeNode *tempNode = getUpperNode(p.second);
      rbTreeNode *nextNode = getNextNode(tempNode);
      if (nextNode == nullptr)
        return end();
      else
        return iterator(this, nextNode);
    } else
      return end();
  }

  /*
  Use only for multiset. Inserts all keys in specific algorithm
  */
  std::pair<iterator, bool> addEqual(rbTreeNode *newNode,
                                     rbTreeNode *currNode) {
    rbTreeNode *borderNode = getUpperNode(currNode);
    if (borderNode->right != nullptr) {
      rbTreeNode *tempNode = minNode(borderNode->right);
      if (tempNode->data_ == newNode->data_) {
        insertNode(newNode, tempNode,
                   1);  // we link it as a right node
      } else {
        insertNode(newNode, tempNode,
                   -1);  // we link it as a left node
      }
    } else {
      insertNode(newNode, borderNode,
                 1);  // we link it as a right node
    }
    return std::make_pair(iterator(this, newNode), true);
  }

  /*
  This function setups the process of inserting the node.
  1. Finds the parent with findNode()
  2. Allocates memory with new
  3. Calls insertNode() to start the algorithm
  */
  std::pair<iterator, bool> addNode(data_type data, bool insert_equal) {
    bool status = false;  // status of insertion

    std::pair<int, rbTreeNode *> p = findNode(data);

    auto *newNode = new rbTreeNode{data};

    if (p.first != 0) {  // insertion for set and map. No equal values allowed
      insertNode(newNode, p.second, p.first);
      status = true;
      return std::make_pair(iterator(this, newNode), status);
    } else if (p.first == 0 &&
               insert_equal) {  // insertion for multiset. Equal values allowed
      return addEqual(newNode, p.second);
    }

    eraseNode(newNode);  // we couldn't link it to the tree
    return std::make_pair(end(), status);
  };

  /*
  Removes node on key. Returns number of removed nodes
  */
  size_type removeNode(data_type data) {
    std::pair<int, rbTreeNode *> p;
    p = findNode(data);
    if (p.first == 0) {
      deleteNode(p.second);
      eraseNode(p.second);
      return 1;
    }
    return 0;
  };

  iterator removeNode(iterator iter) {  // removes nodes at itererator pos
    std::pair<int, rbTreeNode *> p = findNode(*iter);
    if (p.first == 0) {
      iterator tmp_iter(this, p.second);
      if (iter == tmp_iter) {
        iterator res_iter(this, getNextNode(p.second));
        deleteNode(p.second);
        eraseNode(p.second);
        return res_iter;
      } else {
        // try from the left side
        rbTreeNode *currNode = getLowerNode(p.second);
        iterator tmp_iter(this, currNode);
        for (; tmp_iter != iter; tmp_iter++) {
          currNode = getNextNode(currNode);
          if (currNode->data_ != *iter) break;
        }
        if (currNode->data_ == *iter) {  // finally delete if found
          iterator res_iter(this, getNextNode(currNode));
          deleteNode(currNode);
          eraseNode(currNode);
          return res_iter;
        } else {
          return end();
        }
      }
    }
    return end();  // no node to delete
  };

  template <class... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> vec;
    (vec.push_back(emplaceUnique(std::forward<Args>(args))), ...);
    return vec;
  }

  template <class... Args>
  s21::vector<std::pair<iterator, bool>> emplaceMulti(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> vec;
    (vec.push_back(emplaceEqual(std::forward<Args>(args))), ...);
    return vec;
  }

  template <typename Type>
  std::pair<iterator, bool> emplaceUnique(Type &&args) {
    bool status = false;
    auto *newNode = new rbTreeNode{std::forward<Type>(args)};
    std::pair<int, rbTreeNode *> p = findNode(newNode->data_);
    if (p.first != 0) {  // insertion for set and map. No equal values allowed
      insertNode(newNode, p.second, p.first);
      return std::make_pair(iterator(this, newNode), status);
    }
    return std::make_pair(end(), status);
  }

  template <typename Type>
  std::pair<iterator, bool> emplaceEqual(Type &&args) {
    bool status = false;
    rbTreeNode *newNode = new rbTreeNode{std::forward<Type>(args)};
    std::pair<int, rbTreeNode *> p = findNode(newNode->data_);
    if (p.first != 0) {
      insertNode(newNode, p.second, p.first);
      return std::make_pair(iterator(this, newNode), status);
    } else {
      return addEqual(newNode, p.second);
    }
  }

  /*
  ***************************
  Debug methods
  */

  void printTree() {
    if (getRoot()) {
      std::cout << "printing tree\n";
      rbTreeNode *currentNode = minNode(getRoot());
      std::cout << currentNode->data_.first << "(" << currentNode->rbColor
                << ") " << currentNode;
      if (currentNode->left) std::cout << currentNode->left->data_.first << "|";
      if (currentNode->right)
        std::cout << currentNode->right->data_.first << " ";
      std::cout << "it's parent:" << currentNode->parent->data_.first << "\n";
      while (currentNode != header && currentNode) {
        currentNode = getNextNode(currentNode);
        if (currentNode) {
          std::cout << currentNode->data_.first << "(" << currentNode->rbColor
                    << ") " << currentNode;
          if (currentNode->left)
            std::cout << currentNode->left->data_.first << "|";
          if (currentNode->right)
            std::cout << currentNode->right->data_.first << " ";
          if (currentNode != header)
            std::cout << "it's parent:" << currentNode->parent->data_.first
                      << "\n";
        }
        if (currentNode == getRoot())
          std::cout << "it's the root" << currentNode->parent << "\n";
      }
    } else {
      std::cout << "The tree is empty\n";
    }
  };

  bool treeCheck() {
    bool check1 = isTreeBalanced();
    bool check2 = false;
    if (getRoot()) {
      check2 = getRoot()->rbColor;
    }
    bool check3 = checkRed(getRoot());
    return check1 && !check2 && check3 ? true : false;
  };

 private:
  /*
  ***************************
  Using std::less to compare keys
  */

  int compareKeys(const data_type &lk, const data_type &rk) const {
    int res = 0;
    if (Comparator{}(lk, rk))
      res = -1;
    else if (Comparator{}(rk, lk))
      res = 1;
    else
      res = 0;
    return res;
  }

  /*
  ***************************
  Private methods to work with nodes
  */

  void eraseNode(rbTreeNode *node) {
    std::allocator<rbTreeNode> alloc1;
    alloc1.deallocate(node, 1);
  };

  rbTreeNode *getRoot() {
    if (header && header->left)
      return header->left;
    else
      return nullptr;
  };

  /*
  ***************************
  Red Black Tree algorithms
  */

  /*
  Find the node by comparing keys. Return the result of comparement.
  */
  std::pair<int, rbTreeNode *> findNode(const data_type &elemX) {
    const rbTreeNode *currentNode = getRoot();
    const rbTreeNode *parentNode;
    rbTreeNode *resNode;

    int compRes = -1;

    if (currentNode == nullptr) {
      parentNode = header;
      // linking to the root
    } else {
      parentNode = currentNode->parent;
    }
    while (currentNode != nullptr) {
      data_type elemY = currentNode->data_;
      compRes = compareKeys(elemX, elemY);
      if (compRes == 0) {  // we found the node
        resNode = const_cast<rbTreeNode *>(currentNode);
        return std::make_pair(compRes, resNode);
      } else if (compRes == -1) {  // search nodes on the left
        parentNode = currentNode;
        currentNode = currentNode->left;
      } else if (compRes == 1) {  // search nodes on the right
        parentNode = currentNode;
        currentNode = currentNode->right;
      }
    }

    resNode = const_cast<rbTreeNode *>(parentNode);
    return std::make_pair(compRes, resNode);
  };

  /*
  Link new node to the parent.
  */
  void insertNode(rbTreeNode *newNode, rbTreeNode *parentNode, int compRes) {
    if (parentNode == header) {
      newNode->rbColor = kBlack;
      header->left = newNode;
      leftmost = newNode;
      rightmost = newNode;
    } else {
      newNode->rbColor = kRed;
    }
    newNode->parent = parentNode;
    if (compRes < 0) {
      parentNode->left = newNode;
      if (parentNode ==
          leftmost) {  // if we are linking a new node to the smallest one, new
        // node is the new smallest
        leftmost = newNode;
      }
    } else if (compRes > 0) {
      parentNode->right = newNode;
      if (parentNode == rightmost) {
        rightmost = newNode;
      }
    }

    nodesNum++;
    balanceNode(newNode);
  };

  /*
  Those are from the Introduction to Algorithms by
  Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest,
  and Clifford Stein.
  */

  void rotateLeft(rbTreeNode *pivotNode) {
    rbTreeNode *childNode = pivotNode->right;
    pivotNode->right = childNode->left;
    if (childNode->left != 0) {
      childNode->left->parent = pivotNode;
    }
    childNode->parent = pivotNode->parent;
    if (pivotNode->parent == header) {
      header->left = childNode;
    } else if (pivotNode == pivotNode->parent->left) {
      pivotNode->parent->left = childNode;
    } else {
      pivotNode->parent->right = childNode;
    }
    childNode->left = pivotNode;
    pivotNode->parent = childNode;
  };

  void rotateRight(rbTreeNode *pivotNode) {
    rbTreeNode *childNode = pivotNode->left;
    pivotNode->left = childNode->right;
    if (childNode->right != 0) {
      childNode->right->parent = pivotNode;
    }
    childNode->parent = pivotNode->parent;
    if (pivotNode->parent == header) {
      header->left = childNode;
    } else if (pivotNode == pivotNode->parent->right) {
      pivotNode->parent->right = childNode;
    } else {
      pivotNode->parent->left = childNode;
    }
    childNode->right = pivotNode;
    pivotNode->parent = childNode;
  }

  void balanceNode(rbTreeNode *pivotNode) {
    while (pivotNode != 0 && pivotNode != getRoot() &&
           pivotNode->parent->rbColor == kRed) {
      // pivotNode parent is a left son
      if (pivotNode->parent == pivotNode->parent->parent->left) {
        rbTreeNode *uncleNode = pivotNode->parent->parent->right;
        // case 1 a.k.a red uncle
        if ((uncleNode != 0) && uncleNode->rbColor == kRed) {
          pivotNode->parent->rbColor = kBlack;
          uncleNode->rbColor = kBlack;
          pivotNode->parent->parent->rbColor = kRed;
          pivotNode = pivotNode->parent->parent;
        } else {
          if (pivotNode == pivotNode->parent->right) {
            pivotNode = pivotNode->parent;
            rotateLeft(pivotNode);
          }
          pivotNode->parent->rbColor = kBlack;
          pivotNode->parent->parent->rbColor = kRed;
          rotateRight(pivotNode->parent->parent);
        }

        // pivotNode parent is a right son
      } else if (pivotNode->parent == pivotNode->parent->parent->right) {
        rbTreeNode *uncleNode = pivotNode->parent->parent->left;

        // case 1 a.k.a red uncle for the right son
        if (uncleNode != 0 && uncleNode->rbColor == kRed) {
          pivotNode->parent->rbColor = kBlack;
          uncleNode->rbColor = kBlack;
          pivotNode->parent->parent->rbColor = kRed;
          pivotNode = pivotNode->parent->parent;
        } else {
          if (pivotNode == pivotNode->parent->left) {
            pivotNode = pivotNode->parent;
            rotateRight(pivotNode);
          }
          pivotNode->parent->rbColor = kBlack;
          pivotNode->parent->parent->rbColor = kRed;
          rotateLeft(pivotNode->parent->parent);
        }
      }
    }

    getRoot()->rbColor = kBlack;
  };

  rbTreeNode *minNode(rbTreeNode *currentNode) {
    while (currentNode && currentNode->left != 0) {
      currentNode = currentNode->left;
    }
    return currentNode;
  };

  rbTreeNode *maxNode(rbTreeNode *currentNode) {
    while (currentNode && currentNode->right != 0) {
      currentNode = currentNode->right;
    }
    return currentNode;
  };

  rbTreeNode *getNextNode(rbTreeNode *currentNode) {
    if (currentNode == rightmost) return nullptr;
    if (currentNode->right) {
      return minNode(currentNode->right);
    } else if (currentNode == currentNode->parent->left) {
      return currentNode->parent;
    } else {
      while (currentNode == currentNode->parent->right) {
        currentNode = currentNode->parent;
      }
      return currentNode->parent;
    }
  };

  rbTreeNode *getPrevNode(rbTreeNode *currentNode) {
    if (currentNode == leftmost) return nullptr;
    if (currentNode->left) {
      return maxNode(currentNode->left);
    } else if (currentNode == currentNode->parent->right) {
      return currentNode->parent;
    } else {
      while (currentNode == currentNode->parent->left) {
        currentNode = currentNode->parent;
      }
      return currentNode->parent;
    }
  };

  void replaceSon(rbTreeNode *currentNode, rbTreeNode *newSon) {
    if (currentNode->parent == header) {
      header->left = newSon;
    }
    if (currentNode == currentNode->parent->left) {
      currentNode->parent->left = newSon;
    } else {
      currentNode->parent->right = newSon;
    }

    if (newSon) newSon->parent = currentNode->parent;
  };

  void checkLeftmost(rbTreeNode *node) {
    if (node == leftmost) {
      if (node->right == 0) {
        leftmost = node->parent;
      } else {
        leftmost = minNode(node->right);
      }
    }
  }

  void checkRightmost(rbTreeNode *node) {
    if (node == rightmost) {
      if (node->left == 0) {
        rightmost = node->parent;
      } else {
        rightmost = maxNode(node->right);
      }
    }
  }

  /*
  nodePtr is going to be deleted from the tree. We need to
  find another node for it's place (usually the next in order)
  and replace them. Then we balance tree as if this node
  'to be deleted' still exists.
  */
  void deleteNode(rbTreeNode *nodePtr) {
    rbTreeNode *deletedNode = 0;
    rbTreeNode *nextNode = nodePtr;
    rbTreeNode *backupNode = 0;
    bool original_rbColor = nextNode->rbColor;

    if (nodePtr->left == nullptr) {
      deletedNode = nodePtr->right;
      backupNode = nodePtr->parent;
      replaceSon(nodePtr, nodePtr->right);
      // one on the left
    } else if (nodePtr->right == nullptr) {
      deletedNode = nodePtr->left;
      backupNode = nodePtr->parent;
      replaceSon(nodePtr, nodePtr->left);
      // one on the right
    } else {
      nextNode = minNode(nodePtr->right);
      original_rbColor = nextNode->rbColor;
      deletedNode = nextNode->right;
      if (nextNode->parent == nodePtr) {
        backupNode = nodePtr;
      } else {
        replaceSon(nextNode, nextNode->right);
        backupNode = nextNode->parent;
        nextNode->right = nodePtr->right;
        nextNode->right->parent = nextNode;
      }
      replaceSon(nodePtr, nextNode);
      nextNode->left = nodePtr->left;
      nextNode->left->parent = nextNode;
      nextNode->rbColor = nodePtr->rbColor;
    }
    nodesNum--;

    checkLeftmost(nodePtr);
    checkRightmost(nodePtr);

    if (nodesNum == 1) {
      getRoot()->rbColor = kBlack;
    } else {
      if (original_rbColor == kBlack) balanceDeletion(deletedNode, backupNode);
    }
    // sometimes header->right points to another node. This can cause troubles
    if (header->right != 0) {
      header->right = 0;
    }
  };

  /*
  pivotNode can be nullptr, so backupNode serves as it's vurtual parent.
  */
  void balanceDeletion(rbTreeNode *pivotNode, rbTreeNode *backupNode) {
    rbTreeNode *siblingNode;
    while (pivotNode != getRoot() &&
           (pivotNode == nullptr || pivotNode->rbColor == kBlack)) {
      if (pivotNode == backupNode->left) {
        siblingNode = backupNode->right;
        if (siblingNode->rbColor == kRed) {
          siblingNode->rbColor = kBlack;
          backupNode->rbColor = kRed;
          rotateLeft(backupNode);
          siblingNode = backupNode->right;
        }
        if ((siblingNode->left == 0 || siblingNode->left->rbColor == kBlack) &&
            (siblingNode->right == 0 ||
             siblingNode->right->rbColor == kBlack)) {
          siblingNode->rbColor = kRed;
          pivotNode = backupNode;
          backupNode = backupNode->parent;
          if (backupNode == header)
            break;  // we can't have any operations with the header node
        } else {
          if (siblingNode->right == 0 ||
              siblingNode->right->rbColor == kBlack) {
            siblingNode->left->rbColor = kBlack;
            siblingNode->rbColor = kRed;
            rotateRight(siblingNode);
            siblingNode = backupNode->right;
          }
          siblingNode->rbColor = backupNode->rbColor;
          backupNode->rbColor = kBlack;
          if (siblingNode->right) {
            siblingNode->right->rbColor = kBlack;
            rotateLeft(backupNode);
            break;
          }
        }
      } else {
        siblingNode = backupNode->left;
        if (siblingNode->rbColor == kRed) {
          siblingNode->rbColor = kBlack;
          backupNode->rbColor = kRed;
          rotateRight(backupNode);
          siblingNode = backupNode->left;
          if (siblingNode == nullptr) break;
        }
        if ((siblingNode->right == 0 ||
             siblingNode->right->rbColor == kBlack) &&
            (siblingNode->left == 0 || siblingNode->left->rbColor == kBlack)) {
          siblingNode->rbColor = kRed;
          pivotNode = backupNode;
          backupNode = backupNode->parent;
          if (backupNode == header) break;
        } else {
          if (siblingNode->left == 0 || siblingNode->left->rbColor == kBlack) {
            siblingNode->right->rbColor = kBlack;
            siblingNode->rbColor = kRed;
            rotateLeft(siblingNode);
            siblingNode = backupNode->left;
          }
          siblingNode->rbColor = backupNode->rbColor;
          backupNode->rbColor = kBlack;
          if (siblingNode->left) {
            siblingNode->left->rbColor = kBlack;
            rotateRight(backupNode);
            break;
          }
        }
      }
    }
    if (pivotNode) pivotNode->rbColor = kBlack;
  }

  void clearTree(rbTreeNode *subRoot) {
    if (subRoot != nullptr) {
      if (subRoot->left != 0) {
        clearTree(subRoot->left);
      }
      if (subRoot->right != 0) {
        clearTree(subRoot->right);
      }
      eraseNode(subRoot);
      leftmost = nullptr;
      rightmost = nullptr;
      header->left = nullptr;
    }
  }

  /*
  ***************************
  Debug private methods

  */
  int isTreeBalanced() {
    if (getRoot()) {
      int bl = numBlack(getRoot()->left);
      int br = numBlack(getRoot()->right);
      return ((bl - br) == 0) ? true : false;
    } else
      return true;
  };

  bool blackChildren(rbTreeNode *node) {
    if (node->left == 0 && node->right == 0) {
      return true;
    } else {
      if (node->right)
        if (node->right->rbColor == kRed) return false;
      if (node->left)
        if (node->left->rbColor == kRed) return false;
    }
    return true;
  };

  int checkRed(rbTreeNode *currentNode) {
    if (getRoot()) {
      currentNode = minNode(getRoot());
      while (currentNode != header && currentNode) {
        if (currentNode->rbColor == kRed) {
          if (blackChildren(currentNode))
            currentNode = getNextNode(currentNode);
          else
            return false;
        } else {
          currentNode = getNextNode(currentNode);
        }
      }
      return true;
    } else
      return true;
  }

  int numBlack(rbTreeNode *subRoot) {
    if (subRoot == 0) return 0;
    int blackleft = numBlack(subRoot->left);
    int blackright = numBlack(subRoot->right);
    if (blackleft != blackright) return -1;
    if (subRoot->rbColor == kBlack) {
      blackleft += 1;
    }
    return blackleft;
  };
};

};  // namespace s21_utils

#endif  // CONTAINERS_INCLUDE_RBTREE_H__
