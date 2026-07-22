Implement the following two functions such that they are optimal.

void addStocksVolume(string stockSymbol, int volume)
vector<string> topKstocks(int k)

addStocksVolume receives a symbol (INTC, APPL, etc) plus a volume which you cumulate over time.
topKstocks would return the k stocks with the highest volume.

How would you implement this? Using a hash map for addStocksVolume is the first things that comes to mind, but then how would you return the top K (dynamic) without using a heap or sorting?

You could use a set (BST) based on volume, in which case topKstocks becomes O(k), return the first k (begin(), begin() + k) but then addStocksVolume is slow because the lookup is slow.

