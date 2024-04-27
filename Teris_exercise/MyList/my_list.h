//   A simple impl. of list, mimic the behavier of list in STL. The class 
// list is a template class 'my_list', in which iterator is represent 
// by 'node_iterator'. The list is a double-linked list, i.e. it not only
// contains a 'next' pointer, but also a 'pre' pointer.
//   For convience, an empty list contains one node of type 'node_base'
// to represent 'head'.
//   See the comments below for details.
#include <iostream>
#include <cassert>
using namespace std;

// forward declaration of node_iterator, used in class node_base.
template<typename T>
struct node_iterator;

//   Here we define 'node_base' to represent a empty node (which donot 
// contain a value). We use the inherited class 'node' to represent a 
// real node. A empty list contains a node of type 'node_base'.
//   If we only use 'node' class, it cannot hold a class without 
// non-parametric constructor. For example, suppose we have
// class A{
// public:
//     A(int *p){} 
// };
// then
// my_list<A> l;
// will raise an error. Since class 'A' donot owns a non-parametric 
// constructor, so the variable 'T val' in 'node' can not be initialized.
// 
//
template<typename T>
struct node_base {
    node_base() :pre(nullptr), next(nullptr) {}
    node_iterator<T> pre;
    node_iterator<T> next;
};
// struct node
template<typename T>
struct node : public node_base<T> {
    // default constructor
    node() :val(0), node_base<T>() {}
    // used for constructing a node containing value v
    node(T v) :val(v), node_base<T>() {}
    T val;
};

// struct node_iterator represents a node pointer object.
// Reasons for needing this class:
// The iterator of my_list class is node<T>*, so we 
// must implement ++ and * operator for type node<T>*. However,
// if we write a non-member function with the signature:
// node<T>* operator++(node<T>* );
// the compiler will raise an error. 
template<typename T>
struct node_iterator {
    //   By defining this typedefs, we can directly use our
    // list in the STL algorithm framework.
    // E.g. we can write statement like:
    // std::copy(l.begin(), l.end(), ostream_iterator<int>(std::cout,", "));
    // std::copy(l.begin(), l.end(), vec.begin());
    // Refer to https://cplusplus.com/reference/algorithm/copy/ for more details.
    //   Optionally, we can write the following struct outside of node_iterator
    // to achieve the same effect. 
    // Refer to // https://stdcxx.apache.org/doc/stdlibug/16-3.html and
    // https://stdcxx.apache.org/doc/stdlibug/16-4.html for more details.
    // template<typename T>
    // struct std::iterator_traits<node_iterator<T> >{
    //     typedef bidirectional_iterator_tag iterator_category;
    //     typedef T value_type;
    //     typedef T* pointer;
    //     typedef T& reference;
    //     typedef ptrdiff_t difference_type; 
    // };
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ptrdiff_t difference_type;
    typedef node_iterator<T> self;

    node_base<T>* ptr;
    //constructor
    node_iterator(node_base<T>* p) :ptr(p) {}
    // copy constructor
    node_iterator(const self& p) :ptr(p.ptr) {}
    // operator overload for comparison
    bool operator == (const self& p)const { return ptr == p.ptr; }
    bool operator != (const self& p)const { return ptr != p.ptr; }
    // operator overload for increment
    self operator++() {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        ptr = ptr->next.ptr;

        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        return *this;
    }
    self operator--() {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////

        ptr = ptr->pre.ptr;
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        return *this;
    }
    self operator++(int) {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        self tmp = *this;
        ++*this;
        return tmp;

        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    self operator--(int) {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////

        self tmp = *this;
        --*this;
        return tmp;
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    // operator overload for dereference
    reference operator*() const { return static_cast<node<T>*>(ptr)->val; }
    // operator for ->
    // with this function, node_iterator can behave like normal T*
    pointer operator->() const { return &(operator*()); }
};

// node_const_iterator is almost the same as node_iterator
// except that the 'pointer' and 'reference' type definition in it.
template<typename T>
struct node_const_iterator {
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef ptrdiff_t difference_type;
    typedef node_const_iterator<T> self;

    node_base<T>* ptr;
    //constructor
    node_const_iterator(node_base<T>* p) :ptr(p) {}
    // copy constructor
    node_const_iterator(const self& p) :ptr(p.ptr) {}
    // construct an instance using 'node_iterator'
    node_const_iterator(const node_iterator<T>& p) :ptr(p.ptr) {}

    // operator overload for comparison
    bool operator == (const self& p)const { return ptr == p.ptr; }
    bool operator != (const self& p)const { return ptr != p.ptr; }
    // operator overload for increment
    self operator++() {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        ptr = ptr->next.ptr;

        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        return *this;
    }
    self operator--() {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        ptr = ptr->pre.ptr;

        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        return *this;
    }
    self operator++(int) {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////

        self tmp = *this;
        ++*this;
        return tmp;
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    self operator--(int) {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////

        self tmp = *this;
        --*this;
        return tmp;
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    // operator overload for dereference
    reference operator*() const { return static_cast<node<T>*>(ptr)->val; }
    // operator for ->
    // with this function, node_iterator can behave like normal T*
    pointer operator->() const { return &(operator*()); }
};

// class my_list
template<typename T>
class my_list {
public:
    // nested type 
    typedef T value_type;
    typedef node_iterator<T> iterator;
    typedef node_const_iterator<T> const_iterator;
private:
    // head pointer for my_list
    iterator head;
    // tail pointer for my_list
    iterator tail;
    // num of element in this list
    size_t ele_num;
public:

    // default constructor
    // we construct a new node (dummy node) with no value in this node.
    // with dummy node, the end of list can be appropriately represented.
    // Note: As stated above, a empty list contains a 'node_base' node.
    my_list() :head(new node_base<T>()), tail(head), ele_num(0) {}
    // initializer list constructor
    // with this constructor, we can write like 
    // my_list<int> = {1,2,3};
    my_list(initializer_list<T> il) :head(new node<T>()), tail(head), ele_num(0) {
        for (const T& v : il)
            this->push_back(v);
    }
    // copy constructor
    my_list(const my_list<T>& other) :my_list() {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        head = other.head;
        tail = other.tail;
        ele_num = other.ele_num;

        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    // copy assignment
    my_list<T>& operator=(const my_list<T>& other) {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        if (this != &other)
        {
            clear();
            for (const_iterator it = other.begin(); it != other.end(); ++it)
            {
                push_back(*it);
            }
        }
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        return *this;
    }
    // deconstructor
    // note that, beside clearing the whole list, we
    // must delete the dummy node.
    ~my_list() {
        clear();
        delete head.ptr;
        // for clearness, show the following msg when deconstructing list
        cout << "the list has been destroyed." << endl;
    }

    // head pointer and end pointer to the list
    iterator begin() { return head; }
    const_iterator begin() const { return head; }
    const_iterator cbegin() const { return head; }
    iterator end() { return tail; }
    const_iterator end() const { return tail; }
    const_iterator cend() const { return tail; }

    // insert values in the head and tail of the list
    void push_front(T v) { insert(begin(), v); }
    void push_back(T v) { insert(end(), v); }
    void pop_front() { erase(begin()); }
    void pop_back() { erase(end()); }
    // get the front and back value in the list
    T& back() {
        if (empty()) {
            throw std::runtime_error("Attempt to access back of an empty list.");
        }
        return *(tail.ptr->pre);
    }
    T& front() {
        if (empty()) {
            throw std::runtime_error("Attempt to access back of an empty list.");
        }
        return *head;
    }
    // clear all the values in the list
    void clear() {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        while (!empty())
        {
            node_base<T>* to_delete = head.ptr;
            if (head.ptr != tail.ptr)
            {                          
                head = head.ptr->next; // 移动头指针到下一个节点
            }
            delete to_delete; // 删除当前的节点
            --ele_num;        // 更新元素计数器
        }
        // 重置头尾指针，指向一个新的哑元节点，因为原来的已经被删除
        node_base<T>* new_dummy = new node_base<T>();
        head.ptr = tail.ptr = new_dummy;
        ele_num = 0; // 更新元素计数器为0
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    size_t size() const { return ele_num; }
    bool empty() const { return head == tail; }

    // insert one element BEFORE 'it' and return the 
    // iterator point to the newly added node.
    iterator insert(iterator it, const T& val) {
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////
        node_base<T>* new_node = new node<T>(val);
        new_node->next = it.ptr;
        new_node->pre = it.ptr->pre;
        if (it.ptr->pre != nullptr)
        {
            it.ptr->pre.ptr->next = new_node;
        }
        else
        {
            head.ptr = new_node; // 如果it是头部，更新head
        }
        it.ptr->pre = new_node;
        if (it == end())
        {
            tail.ptr = new_node; // 如果it是尾部，更新tail
        }
        ++ele_num;
        return iterator(new_node);
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
    }
    // remove the element pointed by 'it' and return the
    // iterator point to the next node.
    iterator erase(iterator it) {
        //assert(it != end());
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////

        node_base<T>* toDelete = it.ptr;
        if (it.ptr->pre != nullptr)
        {
            it.ptr->pre.ptr->next = it.ptr->next;
        }
        else
        {
            head.ptr = it.ptr->next.ptr; // 如果删除的是第一个元素，更新head
        }
        if (it.ptr->next != nullptr)
        {
            it.ptr->next.ptr->pre.ptr = it.ptr->pre.ptr;
        }
        else
        {
            tail.ptr = it.ptr->pre.ptr; // 如果删除的是最后一个元素，更新tail
        }
        iterator nextIter(it.ptr->next);
        delete toDelete;
        --ele_num;
        return nextIter;
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        
    }
    bool operator==(const my_list& other) {
        // compare 2 lists, if all the elements in the list
        // are equal, then return true, otherwise return false
        // 
        ///////////////////////////////////////////////////
        // BEGIN OF YOUR CODE
        ///////////////////////////////////////////////////

        if (ele_num != other.ele_num) {
            return false; // 如果元素数量不同，则列表不相等
        }
        iterator it1 = begin();
        const_iterator it2 = other.begin();
        while (it1 != end() && it2 != other.end()) {
            if (*it1 != *it2) {
                return false; // 如果发现不相等的元素，则列表不相等
            }
            ++it1;
            ++it2;
        }
        return true; // 所有元素都相等，列表相等
        ///////////////////////////////////////////////////
        // END OF YOUR CODE
        ///////////////////////////////////////////////////
        
    }
};
