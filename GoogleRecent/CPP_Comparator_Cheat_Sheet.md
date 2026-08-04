# C++ Comparator Cheat Sheet

## 1. `sort()`

**Comparator answers:**

> **Should `a` come before `b`?**

``` cpp
struct Comp {
    bool operator()(const T& a, const T& b) const {
        return ...;
    }
};
```

Usage:

``` cpp
sort(v.begin(), v.end(), Comp());
```

Notice **`Comp()`** (an object), not `Comp`.

Example (ascending):

``` cpp
struct Asc {
    bool operator()(int a, int b) const {
        return a < b;
    }
};
```

Example (pair: first DESC, second ASC):

``` cpp
struct Comp {
    bool operator()(const pair<int,int>& a,
                    const pair<int,int>& b) const {
        if (a.first != b.first)
            return a.first > b.first;

        return a.second < b.second;
    }
};
```

------------------------------------------------------------------------

## 2. `priority_queue`

**Comparator answers:**

> **Does `a` have LOWER priority than `b`?**

``` cpp
priority_queue<int, vector<int>, Comp> pq;
```

Notice **`Comp`** (type), not `Comp()`.

### Min Heap

``` cpp
struct MinHeap {
    bool operator()(int a, int b) const {
        return a > b;
    }
};
```

### Max Heap

``` cpp
struct MaxHeap {
    bool operator()(int a, int b) const {
        return a < b;
    }
};
```

(Default `priority_queue<int>` is already a max heap.)

------------------------------------------------------------------------

## 3. `upper_bound` / `lower_bound`

Use a comparator when searching by only part of an object.

Example:

``` cpp
vector<pair<int,int>> history;
```

Search only using `snap_id` (the first field):

``` cpp
struct Comp {
    bool operator()(int snapId,
                    const pair<int,int>& entry) const {
        return snapId < entry.first;
    }
};
```

Usage:

``` cpp
auto it = upper_bound(
    history.begin(),
    history.end(),
    snap_id,
    Comp()
);
```

Notice **`Comp()`** because `upper_bound` expects a comparator object.

------------------------------------------------------------------------

## 4. `lower_bound` vs `upper_bound`

    lower_bound(x)
        -> first element >= x

    upper_bound(x)
        -> first element > x

Example:

    1 3 3 3 5 7

    lower_bound(3) -> first 3
    upper_bound(3) -> 5

------------------------------------------------------------------------

## 5. Why `Comp()` sometimes and `Comp` other times?

### Functions (`sort`, `upper_bound`, etc.)

Need a comparator **object**.

``` cpp
sort(v.begin(), v.end(), Comp());

upper_bound(v.begin(), v.end(), x, Comp());
```

### Template parameters (`priority_queue`, `set`, `map`)

Need the **type**.

``` cpp
priority_queue<int, vector<int>, Comp> pq;

set<int, Comp> s;
```

The container creates the comparator object internally.

------------------------------------------------------------------------

## 6. Mental Models

### sort

    return true
    ↓
    a should come before b

### priority_queue

    return true
    ↓
    a has lower priority than b

### upper_bound / lower_bound

    Comparator only defines the ordering.

    Binary search uses that ordering to find
    the insertion point.

------------------------------------------------------------------------

## 7. Quick Summary

  Algorithm        Comparator Means                Pass
  ---------------- ------------------------------- ----------
  sort             Should `a` come before `b`?     `Comp()`
  lower_bound      Ordering for binary search      `Comp()`
  upper_bound      Ordering for binary search      `Comp()`
  priority_queue   Does `a` have lower priority?   `Comp`
  set/map          Ordering of keys                `Comp`

**Remember:** - `Comp` → type - `Comp()` → object
