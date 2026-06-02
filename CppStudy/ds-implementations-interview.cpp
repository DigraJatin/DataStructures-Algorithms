// ============================================================================
// Interview-Level Data Structure Implementations in C++
// No std:: containers — raw pointers, C-style arrays, new/delete
// ============================================================================
#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

// ============================================================================
// 1. SINGLY LINKED LIST
// ============================================================================
class SinglyLinkedList {
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }

    void pushFront(int val) {
        Node* n = new Node(val);
        n->next = head;
        head = n;
    }

    void pushBack(int val) {
        Node* n = new Node(val);
        if (!head) { head = n; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }

    bool remove(int val) {
        if (!head) return false;
        if (head->data == val) {
            Node* tmp = head; head = head->next; delete tmp; return true;
        }
        Node* cur = head;
        while (cur->next && cur->next->data != val) cur = cur->next;
        if (!cur->next) return false;
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        return true;
    }

    Node* find(int val) {
        Node* cur = head;
        while (cur) { if (cur->data == val) return cur; cur = cur->next; }
        return nullptr;
    }

    // ---- Classic interview: Reverse a linked list ----
    void reverse() {
        Node* prev = nullptr;
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        head = prev;
    }

    // ---- Detect cycle (Floyd's) ----
    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }

    void print() {
        for (Node* c = head; c; c = c->next) cout << c->data << " -> ";
        cout << "null\n";
    }
};

// ============================================================================
// 2. DOUBLY LINKED LIST
// ============================================================================
class DoublyLinkedList {
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }

    void pushFront(int val) {
        Node* n = new Node(val);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
    }

    void pushBack(int val) {
        Node* n = new Node(val);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
    }

    void popFront() {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
    }

    void popBack() {
        if (!tail) return;
        Node* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
    }

    bool remove(int val) {
        Node* cur = head;
        while (cur && cur->data != val) cur = cur->next;
        if (!cur) return false;
        if (cur->prev) cur->prev->next = cur->next;
        else head = cur->next;
        if (cur->next) cur->next->prev = cur->prev;
        else tail = cur->prev;
        delete cur;
        return true;
    }

    void printForward() {
        for (Node* c = head; c; c = c->next) cout << c->data << " <-> ";
        cout << "null\n";
    }

    void printBackward() {
        for (Node* c = tail; c; c = c->prev) cout << c->data << " <-> ";
        cout << "null\n";
    }
};

// ============================================================================
// 3. DYNAMIC ARRAY (Vector)
// ============================================================================
class Vector {
    int* arr;
    int sz;
    int cap;

    void grow() {
        cap = (cap == 0) ? 4 : cap * 2;
        int* newArr = new int[cap];
        for (int i = 0; i < sz; i++) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Vector() : arr(nullptr), sz(0), cap(0) {}
    ~Vector() { delete[] arr; }

    void pushBack(int val) {
        if (sz == cap) grow();
        arr[sz++] = val;
    }

    void popBack() {
        if (sz > 0) sz--;
    }

    int& operator[](int idx) {
        if (idx < 0 || idx >= sz) throw out_of_range("Index out of bounds");
        return arr[idx];
    }

    void removeAt(int idx) {
        if (idx < 0 || idx >= sz) return;
        for (int i = idx; i < sz - 1; i++) arr[i] = arr[i + 1];
        sz--;
    }

    int size() const { return sz; }
    int capacity() const { return cap; }
    bool empty() const { return sz == 0; }

    void print() {
        cout << "[";
        for (int i = 0; i < sz; i++) { if (i) cout << ", "; cout << arr[i]; }
        cout << "] (size=" << sz << ", cap=" << cap << ")\n";
    }
};

// ============================================================================
// 4. STACK (Array-based)
// ============================================================================
class Stack {
    int* arr;
    int topIdx;
    int cap;

public:
    Stack(int capacity = 100) : cap(capacity), topIdx(-1) {
        arr = new int[cap];
    }
    ~Stack() { delete[] arr; }

    void push(int val) {
        if (topIdx == cap - 1) throw overflow_error("Stack overflow");
        arr[++topIdx] = val;
    }

    int pop() {
        if (topIdx == -1) throw underflow_error("Stack underflow");
        return arr[topIdx--];
    }

    int top() const {
        if (topIdx == -1) throw underflow_error("Stack empty");
        return arr[topIdx];
    }

    bool empty() const { return topIdx == -1; }
    int size() const { return topIdx + 1; }
};

// ============================================================================
// 5. QUEUE USING TWO STACKS
// ============================================================================
class QueueUsingStacks {
    // Using simple internal stacks to avoid dependency on the Stack class above
    struct SimpleStack {
        int* arr;
        int topIdx;
        int cap;
        SimpleStack(int c = 1000) : cap(c), topIdx(-1) { arr = new int[cap]; }
        ~SimpleStack() { delete[] arr; }
        void push(int v) { arr[++topIdx] = v; }
        int pop() { return arr[topIdx--]; }
        int top() { return arr[topIdx]; }
        bool empty() { return topIdx == -1; }
    };

    SimpleStack inStack;
    SimpleStack outStack;

    void transfer() {
        while (!inStack.empty())
            outStack.push(inStack.pop());
    }

public:
    void enqueue(int val) { inStack.push(val); }

    int dequeue() {
        if (outStack.empty()) transfer();
        if (outStack.empty()) throw underflow_error("Queue empty");
        return outStack.pop();
    }

    int front() {
        if (outStack.empty()) transfer();
        if (outStack.empty()) throw underflow_error("Queue empty");
        return outStack.top();
    }

    bool empty() { return inStack.empty() && outStack.empty(); }
};

// ============================================================================
// 6. CIRCULAR QUEUE (Ring Buffer)
// ============================================================================
class CircularQueue {
    int* arr;
    int frontIdx, rearIdx, sz, cap;

public:
    CircularQueue(int capacity) : cap(capacity), frontIdx(0), rearIdx(-1), sz(0) {
        arr = new int[cap];
    }
    ~CircularQueue() { delete[] arr; }

    void enqueue(int val) {
        if (sz == cap) throw overflow_error("Queue full");
        rearIdx = (rearIdx + 1) % cap;
        arr[rearIdx] = val;
        sz++;
    }

    int dequeue() {
        if (sz == 0) throw underflow_error("Queue empty");
        int val = arr[frontIdx];
        frontIdx = (frontIdx + 1) % cap;
        sz--;
        return val;
    }

    int front() const {
        if (sz == 0) throw underflow_error("Queue empty");
        return arr[frontIdx];
    }

    int rear() const {
        if (sz == 0) throw underflow_error("Queue empty");
        return arr[rearIdx];
    }

    bool empty() const { return sz == 0; }
    bool full() const { return sz == cap; }
    int size() const { return sz; }
};

// ============================================================================
// 7. DEQUE (Double-Ended Queue — Circular Array)
// ============================================================================
class Deque {
    int* arr;
    int frontIdx, rearIdx, sz, cap;

public:
    Deque(int capacity) : cap(capacity), frontIdx(0), rearIdx(capacity - 1), sz(0) {
        arr = new int[cap];
    }
    ~Deque() { delete[] arr; }

    void pushFront(int val) {
        if (sz == cap) throw overflow_error("Deque full");
        frontIdx = (frontIdx - 1 + cap) % cap;
        arr[frontIdx] = val;
        sz++;
    }

    void pushBack(int val) {
        if (sz == cap) throw overflow_error("Deque full");
        rearIdx = (rearIdx + 1) % cap;
        arr[rearIdx] = val;
        sz++;
    }

    int popFront() {
        if (sz == 0) throw underflow_error("Deque empty");
        int val = arr[frontIdx];
        frontIdx = (frontIdx + 1) % cap;
        sz--;
        return val;
    }

    int popBack() {
        if (sz == 0) throw underflow_error("Deque empty");
        int val = arr[rearIdx];
        rearIdx = (rearIdx - 1 + cap) % cap;
        sz--;
        return val;
    }

    int front() const { if (!sz) throw underflow_error("empty"); return arr[frontIdx]; }
    int back()  const { if (!sz) throw underflow_error("empty"); return arr[rearIdx]; }
    bool empty() const { return sz == 0; }
    int size() const { return sz; }
};

// ============================================================================
// 8. HASH MAP (Separate Chaining)
// ============================================================================
class HashMap {
    struct Entry {
        int key;
        int value;
        Entry* next;
        Entry(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    Entry** buckets;
    int numBuckets;
    int sz;

    int hash(int key) {
        return ((key % numBuckets) + numBuckets) % numBuckets;  // handles negatives
    }

public:
    HashMap(int capacity = 16) : numBuckets(capacity), sz(0) {
        buckets = new Entry*[numBuckets];
        for (int i = 0; i < numBuckets; i++) buckets[i] = nullptr;
    }

    ~HashMap() {
        for (int i = 0; i < numBuckets; i++) {
            Entry* cur = buckets[i];
            while (cur) { Entry* tmp = cur; cur = cur->next; delete tmp; }
        }
        delete[] buckets;
    }

    void put(int key, int value) {
        int idx = hash(key);
        Entry* cur = buckets[idx];
        while (cur) {
            if (cur->key == key) { cur->value = value; return; }  // update
            cur = cur->next;
        }
        Entry* n = new Entry(key, value);
        n->next = buckets[idx];
        buckets[idx] = n;
        sz++;
    }

    int get(int key) {
        int idx = hash(key);
        Entry* cur = buckets[idx];
        while (cur) {
            if (cur->key == key) return cur->value;
            cur = cur->next;
        }
        throw runtime_error("Key not found");
    }

    bool contains(int key) {
        int idx = hash(key);
        Entry* cur = buckets[idx];
        while (cur) {
            if (cur->key == key) return true;
            cur = cur->next;
        }
        return false;
    }

    bool remove(int key) {
        int idx = hash(key);
        Entry* cur = buckets[idx];
        Entry* prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next;
                else buckets[idx] = cur->next;
                delete cur;
                sz--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    int size() const { return sz; }
};

// ============================================================================
// 9. BINARY SEARCH TREE
// ============================================================================
class BST {
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = remove(node->left, val);
        else if (val > node->data) node->right = remove(node->right, val);
        else {
            // Found node to delete
            if (!node->left) {
                Node* tmp = node->right; delete node; return tmp;
            }
            if (!node->right) {
                Node* tmp = node->left; delete node; return tmp;
            }
            // Two children: replace with inorder successor
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    int height(Node* node) {
        if (!node) return -1;
        int lh = height(node->left);
        int rh = height(node->right);
        return 1 + (lh > rh ? lh : rh);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int val) { root = insert(root, val); }
    void remove(int val) { root = remove(root, val); }

    bool search(int val) {
        Node* cur = root;
        while (cur) {
            if (val == cur->data) return true;
            cur = (val < cur->data) ? cur->left : cur->right;
        }
        return false;
    }

    int height() { return height(root); }

    void inorder()   { inorder(root);   cout << "\n"; }
    void preorder()  { preorder(root);  cout << "\n"; }
    void postorder() { postorder(root); cout << "\n"; }

    // ---- Interview classic: Level-order (BFS) without std::queue ----
    void levelOrder() {
        if (!root) return;
        // Simple array-based queue
        Node** q = new Node*[1000];
        int front = 0, back = 0;
        q[back++] = root;
        while (front < back) {
            Node* cur = q[front++];
            cout << cur->data << " ";
            if (cur->left)  q[back++] = cur->left;
            if (cur->right) q[back++] = cur->right;
        }
        cout << "\n";
        delete[] q;
    }
};

// ============================================================================
// 10. TRIE (Prefix Tree)
// ============================================================================
class Trie {
    static const int ALPHA_SIZE = 26;

    struct Node {
        Node* children[ALPHA_SIZE];
        bool isEnd;

        Node() : isEnd(false) {
            for (int i = 0; i < ALPHA_SIZE; i++) children[i] = nullptr;
        }
    };

    Node* root;

    void destroy(Node* node) {
        if (!node) return;
        for (int i = 0; i < ALPHA_SIZE; i++) destroy(node->children[i]);
        delete node;
    }

public:
    Trie() { root = new Node(); }
    ~Trie() { destroy(root); }

    void insert(const char* word) {
        Node* cur = root;
        for (int i = 0; word[i]; i++) {
            int idx = word[i] - 'a';
            if (!cur->children[idx])
                cur->children[idx] = new Node();
            cur = cur->children[idx];
        }
        cur->isEnd = true;
    }

    bool search(const char* word) {
        Node* cur = root;
        for (int i = 0; word[i]; i++) {
            int idx = word[i] - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return cur->isEnd;
    }

    bool startsWith(const char* prefix) {
        Node* cur = root;
        for (int i = 0; prefix[i]; i++) {
            int idx = prefix[i] - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return true;
    }

    bool remove(const char* word) {
        return removeHelper(root, word, 0);
    }

private:
    bool removeHelper(Node* node, const char* word, int depth) {
        if (!node) return false;
        if (!word[depth]) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return isEmpty(node);
        }
        int idx = word[depth] - 'a';
        bool shouldDelete = removeHelper(node->children[idx], word, depth + 1);
        if (shouldDelete) {
            delete node->children[idx];
            node->children[idx] = nullptr;
            return !node->isEnd && isEmpty(node);
        }
        return false;
    }

    bool isEmpty(Node* node) {
        for (int i = 0; i < ALPHA_SIZE; i++)
            if (node->children[i]) return false;
        return true;
    }
};

// ============================================================================
// 11. MIN HEAP (Priority Queue)
// ============================================================================
class MinHeap {
    int* arr;
    int sz;
    int cap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void swap(int& a, int& b) { int t = a; a = b; b = t; }

    void heapifyUp(int i) {
        while (i > 0 && arr[parent(i)] > arr[i]) {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i), r = right(i);
        if (l < sz && arr[l] < arr[smallest]) smallest = l;
        if (r < sz && arr[r] < arr[smallest]) smallest = r;
        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int capacity) : cap(capacity), sz(0) { arr = new int[cap]; }
    ~MinHeap() { delete[] arr; }

    void push(int val) {
        if (sz == cap) throw overflow_error("Heap full");
        arr[sz] = val;
        heapifyUp(sz);
        sz++;
    }

    int pop() {
        if (sz == 0) throw underflow_error("Heap empty");
        int top = arr[0];
        arr[0] = arr[--sz];
        heapifyDown(0);
        return top;
    }

    int peek() const {
        if (sz == 0) throw underflow_error("Heap empty");
        return arr[0];
    }

    bool empty() const { return sz == 0; }
    int size() const { return sz; }
};

// ============================================================================
// 12. GRAPH (Adjacency List — raw pointers)
// ============================================================================
class Graph {
    struct AdjNode {
        int dest;
        AdjNode* next;
        AdjNode(int d) : dest(d), next(nullptr) {}
    };

    AdjNode** adjList;
    int V;
    bool directed;

public:
    Graph(int vertices, bool isDirected = false)
        : V(vertices), directed(isDirected) {
        adjList = new AdjNode*[V];
        for (int i = 0; i < V; i++) adjList[i] = nullptr;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            AdjNode* cur = adjList[i];
            while (cur) { AdjNode* tmp = cur; cur = cur->next; delete tmp; }
        }
        delete[] adjList;
    }

    void addEdge(int u, int v) {
        AdjNode* n = new AdjNode(v);
        n->next = adjList[u]; adjList[u] = n;
        if (!directed) {
            AdjNode* m = new AdjNode(u);
            m->next = adjList[v]; adjList[v] = m;
        }
    }

    // BFS using raw array as queue
    void bfs(int start) {
        bool* visited = new bool[V]();
        int* queue = new int[V];
        int front = 0, back = 0;

        visited[start] = true;
        queue[back++] = start;

        cout << "BFS: ";
        while (front < back) {
            int u = queue[front++];
            cout << u << " ";
            for (AdjNode* cur = adjList[u]; cur; cur = cur->next) {
                if (!visited[cur->dest]) {
                    visited[cur->dest] = true;
                    queue[back++] = cur->dest;
                }
            }
        }
        cout << "\n";
        delete[] visited;
        delete[] queue;
    }

    // DFS iterative using raw array as stack
    void dfs(int start) {
        bool* visited = new bool[V]();
        int* stack = new int[V];
        int top = -1;

        stack[++top] = start;

        cout << "DFS: ";
        while (top >= 0) {
            int u = stack[top--];
            if (visited[u]) continue;
            visited[u] = true;
            cout << u << " ";
            for (AdjNode* cur = adjList[u]; cur; cur = cur->next) {
                if (!visited[cur->dest])
                    stack[++top] = cur->dest;
            }
        }
        cout << "\n";
        delete[] visited;
        delete[] stack;
    }
};

// ============================================================================
// 13. LRU CACHE (HashMap + Doubly Linked List)
// ============================================================================
class LRUCache {
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    struct MapEntry {
        int key;
        Node* node;
        MapEntry* next;
        MapEntry(int k, Node* n) : key(k), node(n), next(nullptr) {}
    };

    Node* head;  // most recent
    Node* tail;  // least recent
    MapEntry** buckets;
    int numBuckets;
    int cap;
    int sz;

    int hash(int key) { return ((key % numBuckets) + numBuckets) % numBuckets; }

    void addToFront(Node* node) {
        node->next = head; node->prev = nullptr;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
    }

    void removeNode(Node* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;
        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;
    }

    void moveToFront(Node* node) {
        removeNode(node);
        addToFront(node);
    }

    void mapPut(int key, Node* node) {
        int idx = hash(key);
        MapEntry* e = new MapEntry(key, node);
        e->next = buckets[idx];
        buckets[idx] = e;
    }

    Node* mapGet(int key) {
        int idx = hash(key);
        for (MapEntry* e = buckets[idx]; e; e = e->next)
            if (e->key == key) return e->node;
        return nullptr;
    }

    void mapRemove(int key) {
        int idx = hash(key);
        MapEntry* cur = buckets[idx]; MapEntry* prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next;
                else buckets[idx] = cur->next;
                delete cur;
                return;
            }
            prev = cur; cur = cur->next;
        }
    }

public:
    LRUCache(int capacity) : cap(capacity), sz(0), head(nullptr), tail(nullptr) {
        numBuckets = capacity * 2;
        buckets = new MapEntry*[numBuckets];
        for (int i = 0; i < numBuckets; i++) buckets[i] = nullptr;
    }

    ~LRUCache() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
        for (int i = 0; i < numBuckets; i++) {
            MapEntry* cur = buckets[i];
            while (cur) { MapEntry* tmp = cur; cur = cur->next; delete tmp; }
        }
        delete[] buckets;
    }

    int get(int key) {
        Node* node = mapGet(key);
        if (!node) return -1;
        moveToFront(node);
        return node->value;
    }

    void put(int key, int value) {
        Node* node = mapGet(key);
        if (node) {
            node->value = value;
            moveToFront(node);
            return;
        }
        if (sz == cap) {
            // Evict LRU (tail)
            mapRemove(tail->key);
            Node* old = tail;
            removeNode(old);
            delete old;
            sz--;
        }
        Node* newNode = new Node(key, value);
        addToFront(newNode);
        mapPut(key, newNode);
        sz++;
    }
};

// ============================================================================
// DEMO / TEST
// ============================================================================
int main() {
    cout << "=== Singly Linked List ===\n";
    SinglyLinkedList sll;
    sll.pushBack(1); sll.pushBack(2); sll.pushBack(3); sll.pushFront(0);
    sll.print();              // 0 -> 1 -> 2 -> 3 -> null
    sll.reverse();
    sll.print();              // 3 -> 2 -> 1 -> 0 -> null
    sll.remove(2);
    sll.print();              // 3 -> 1 -> 0 -> null

    cout << "\n=== Doubly Linked List ===\n";
    DoublyLinkedList dll;
    dll.pushBack(1); dll.pushBack(2); dll.pushBack(3); dll.pushFront(0);
    dll.printForward();       // 0 <-> 1 <-> 2 <-> 3 <-> null
    dll.printBackward();      // 3 <-> 2 <-> 1 <-> 0 <-> null
    dll.popFront(); dll.popBack();
    dll.printForward();       // 1 <-> 2 <-> null

    cout << "\n=== Vector ===\n";
    Vector vec;
    for (int i = 0; i < 10; i++) vec.pushBack(i * 10);
    vec.print();
    vec.removeAt(3);
    vec.print();

    cout << "\n=== Stack ===\n";
    Stack stk;
    stk.push(10); stk.push(20); stk.push(30);
    cout << "Top: " << stk.top() << "\n";
    cout << "Pop: " << stk.pop() << "\n";
    cout << "Pop: " << stk.pop() << "\n";

    cout << "\n=== Queue Using Two Stacks ===\n";
    QueueUsingStacks qus;
    qus.enqueue(1); qus.enqueue(2); qus.enqueue(3);
    cout << "Dequeue: " << qus.dequeue() << "\n";  // 1
    cout << "Dequeue: " << qus.dequeue() << "\n";  // 2
    qus.enqueue(4);
    cout << "Dequeue: " << qus.dequeue() << "\n";  // 3
    cout << "Dequeue: " << qus.dequeue() << "\n";  // 4

    cout << "\n=== Circular Queue ===\n";
    CircularQueue cq(5);
    cq.enqueue(1); cq.enqueue(2); cq.enqueue(3); cq.enqueue(4); cq.enqueue(5);
    cout << "Front: " << cq.front() << ", Rear: " << cq.rear() << "\n";
    cq.dequeue(); cq.dequeue();
    cq.enqueue(6);  // wraps around
    cout << "Front: " << cq.front() << ", Size: " << cq.size() << "\n";

    cout << "\n=== Deque ===\n";
    Deque dq(10);
    dq.pushBack(1); dq.pushBack(2); dq.pushFront(0); dq.pushFront(-1);
    cout << "Front: " << dq.front() << ", Back: " << dq.back() << "\n";
    cout << "PopFront: " << dq.popFront() << "\n";
    cout << "PopBack: " << dq.popBack() << "\n";

    cout << "\n=== HashMap ===\n";
    HashMap hm;
    hm.put(1, 100); hm.put(2, 200); hm.put(17, 1700);  // 1 and 17 may collide
    cout << "get(1): " << hm.get(1) << "\n";
    cout << "get(17): " << hm.get(17) << "\n";
    hm.put(1, 999);
    cout << "get(1) after update: " << hm.get(1) << "\n";
    hm.remove(2);
    cout << "contains(2): " << hm.contains(2) << "\n";

    cout << "\n=== BST ===\n";
    BST bst;
    bst.insert(50); bst.insert(30); bst.insert(70);
    bst.insert(20); bst.insert(40); bst.insert(60); bst.insert(80);
    cout << "Inorder:    "; bst.inorder();
    cout << "Preorder:   "; bst.preorder();
    cout << "Postorder:  "; bst.postorder();
    cout << "Level-order: "; bst.levelOrder();
    cout << "Height: " << bst.height() << "\n";
    cout << "Search 40: " << bst.search(40) << "\n";
    bst.remove(30);
    cout << "After removing 30: "; bst.inorder();

    cout << "\n=== Trie ===\n";
    Trie trie;
    trie.insert("apple"); trie.insert("app"); trie.insert("bat");
    cout << "search(apple): " << trie.search("apple") << "\n";
    cout << "search(app): " << trie.search("app") << "\n";
    cout << "search(ap): " << trie.search("ap") << "\n";
    cout << "startsWith(ap): " << trie.startsWith("ap") << "\n";
    trie.remove("app");
    cout << "After remove(app), search(app): " << trie.search("app") << "\n";
    cout << "search(apple) still: " << trie.search("apple") << "\n";

    cout << "\n=== Min Heap ===\n";
    MinHeap heap(20);
    heap.push(30); heap.push(10); heap.push(50); heap.push(5); heap.push(20);
    cout << "Pop order: ";
    while (!heap.empty()) cout << heap.pop() << " ";
    cout << "\n";

    cout << "\n=== Graph ===\n";
    Graph g(6);
    g.addEdge(0,1); g.addEdge(0,2); g.addEdge(1,3); g.addEdge(2,4); g.addEdge(3,5);
    g.bfs(0);
    g.dfs(0);

    cout << "\n=== LRU Cache ===\n";
    LRUCache lru(3);
    lru.put(1, 10); lru.put(2, 20); lru.put(3, 30);
    cout << "get(1): " << lru.get(1) << "\n";   // 10 — moves 1 to front
    lru.put(4, 40);  // evicts key 2 (LRU)
    cout << "get(2): " << lru.get(2) << "\n";   // -1 (evicted)
    cout << "get(3): " << lru.get(3) << "\n";   // 30
    cout << "get(4): " << lru.get(4) << "\n";   // 40

    return 0;
}
