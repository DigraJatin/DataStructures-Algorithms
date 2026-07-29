#include <iostream>
#include <unordered_map>
#include <queue>
#include <chrono>

using namespace std;

class LRUCache {
public:
    using Clock = std::chrono::steady_clock; // used for measuring intervals, stopwatch type, unaffeted by computer time change
    using TimePoint = Clock::time_point; // represent an exact moment on the clock e.g, right now

    // Head ---------------- Tail
    // LRU                  MRU

    LRUCache(int cap, long long ttlSeconds)
        : capacity(cap), expiryDuration(std::chrono::seconds(ttlSeconds)) {
        // expiryDuration(std::chrono::seconds(ttlSeconds)
        // takes raw long long seconds like 5 seconds, convert to seconds, giving integer meaning
        head = new Node(0, 0, Clock::now());
        tail = new Node(0, 0, Clock::now());

        head->next = tail;
        tail->prev = head;
    }

    int getValueForKey(int key) {
        releaseExpired();

        auto it = cache.find(key);
        if (it == cache.end())
            return -1;

        Node* node = it->second;

        remove(node);
        insertMRU(node);

        return node->value;
    }

    void insertKeyValue(int key, int value) {
        releaseExpired();

        auto now = Clock::now();
        auto expiry = now + expiryDuration;

        auto it = cache.find(key);

        // Key already exists
        if (it != cache.end()) {
            Node* node = it->second;

            node->value = value;
            node->expiry = expiry;

            expiryHeap.push({expiry, node});

            remove(node);
            insertMRU(node);

            return;
        }

        // Cache full
        if (cache.size() == capacity) {
            Node* lru = head->next;

            cache.erase(lru->key);

            remove(lru);

            delete lru;
        }

        // New node
        Node* node = new Node(key, value, expiry);

        cache[key] = node;

        expiryHeap.push({expiry, node});

        insertMRU(node);
    }

private:
    struct Node {
        int key;
        int value;

        TimePoint expiry;

        Node* prev;
        Node* next;

        Node(int k, int v, TimePoint e)
            : key(k),
              value(v),
              expiry(e),
              prev(nullptr),
              next(nullptr) {}
    };

    using HeapEntry = pair<TimePoint, Node*>;

    struct Compare {
        bool operator()(const HeapEntry& a, const HeapEntry& b) const {
            return a.first > b.first;   // Min Heap
        }
    };

    int capacity;
    chrono::seconds expiryDuration;

    unordered_map<int, Node*> cache;

    priority_queue<
        HeapEntry,
        vector<HeapEntry>,
        Compare
    > expiryHeap;

    Node* head;
    Node* tail;

    void remove(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertMRU(Node* node) {
        node->prev = tail->prev;
        tail->prev->next = node;
        tail->prev = node;
        node->next = tail;
    }

    void releaseExpired() {

        auto now = Clock::now();

        while (!expiryHeap.empty()) {

            auto [expiry, node] = expiryHeap.top();

            if (expiry > now)
                break;

            expiryHeap.pop();

            // Stale heap entry (node expiry was refreshed)
            if (node->expiry != expiry)
                continue;

            auto it = cache.find(node->key);

            // Already removed as LRU
            if (it == cache.end())
                continue;

            cache.erase(it);

            remove(node);

            delete node;
        }
    }
};

int main() {

    LRUCache cache(2, 5); // capacity = 2, TTL = 5 seconds

    cache.insertKeyValue(1, 10);
    cache.insertKeyValue(2, 20);

    cout << cache.getValueForKey(1) << "\n"; // 10

    std::this_thread::sleep_for(std::chrono::seconds(6));

    cout << cache.getValueForKey(1) << "\n"; // -1 (expired)

    return 0;
}