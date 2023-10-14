#ifndef LIST_H_
#define LIST_H_

/**
 * @brief A simple list implementation,
 *        providing range-based for loop support
 *
 * @tparam T The type of data to be stored in the list
 */
template <typename T>
class List {
 private:
  /**
   * Node of the list
   */
  struct Node {
    T data;
    Node *next;
    Node(const T &data_) : data{data_}, next{nullptr} {}
  };

  /** pointer to the head node */
  Node *head;

  /** pointer to the tail node */
  Node *tail;

  /** number of nodes in the list */
  int count;

 public:
  /** constructor */
  List() : head{nullptr}, tail{nullptr}, count(0) {}

  /** destructor */
  ~List() {
    Node *cur = head;
    while (cur != nullptr) {
      Node *next = cur->next;
      delete cur;
      cur = next;
    }
  }

  /**
   * @brief Retrives the size of the list
   *
   * @return number of nodes in current list
   */
  int size() { return count; }

  /**
   * @brief Sort the list with a given comparator
   *
   * @param cmp The comparator
   */
  void sort(int (*cmp)(const T &lhs, const T &rhs)) {
    if (count < 2) {
      return;
    }
    // simple in-place insertion sort implementation
    Node *pre = head;
    Node *cur = head->next;
    while (cur != nullptr) {
      Node *insert_pre = nullptr;
      Node *insert_pos = head;

      // find the insert position
      for (; insert_pos != cur && cmp(cur->data, insert_pos->data) <= 0;
           insert_pre = insert_pos, insert_pos = insert_pos->next) {
        ;
      }

      // insert node
      if (insert_pos == cur) {
        pre = cur;  // 'pre' for next iteration
      } else {
        pre->next = cur->next;  // 'pre' is reused for next iteration
        cur->next = insert_pos;
        if (insert_pre != nullptr) {
          insert_pre->next = cur;
        } else {
          head = cur;
        }
      }
      cur = pre->next;  // 'cur' for next iteration
    }
    tail = pre;
  }

  /**
   * @brief Insert a node to the list with a given data
   *
   * @param data The data to be inserted
   */
  void insert(const T &data) {
    Node *pNew = new Node{data};
    if (count == 0) {
      head = pNew;
    } else {
      tail->next = pNew;
    }
    tail = pNew;
    ++count;
  }

  /**
   * @brief Delete a first node if exists from the list with a given data
   *
   * @param data The data to be deleted
   */
  void remove(const T &data) {
    Node *cur = head;
    Node *pre = nullptr;
    for (; cur != nullptr; pre = cur, cur = cur->next) {
      if (cur->data == data) {
        break;
      }
    }

    // node not found with given data
    if (cur == nullptr) {
      return;
    }

    // delete node
    if (cur == tail) {
      tail = pre;
    }
    if (pre == nullptr) {
      head = cur->next;
    } else {
      pre->next = cur->next;
    }
    delete cur;
    --count;
  }

  /**
   * Define a forward Iterator.
   * Provide a range-based for loop support.
   */
  class Iterator {
   private:
    Node *current;

   public:
    Iterator(Node *node) : current{node} {}

    T &operator*() const { return current->data; }

    Iterator &operator++() {  // prefix ++
      current = current->next;
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }
  };

  /** provide begin() and end() for range-based for loop */
  Iterator begin() const { return Iterator{head}; }
  Iterator end() const { return Iterator{nullptr}; }
};

#endif