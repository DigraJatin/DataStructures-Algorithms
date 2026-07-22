Implement the following two functions such that they are optimal.

void addStocksVolume(string stockSymbol, int volume)
vector<string> topKstocks(int k)

addStocksVolume receives a symbol (INTC, APPL, etc) plus a volume which you cumulate over time.
topKstocks would return the k stocks with the highest volume.

How would you implement this? Using a hash map for addStocksVolume is the first things that comes to mind, but then how would you return the top K (dynamic) without using a heap or sorting?

You could use a set (BST) based on volume, in which case topKstocks becomes O(k), return the first k (begin(), begin() + k) but then addStocksVolume is slow because the lookup is slow.


// we need to add stocks and their volume update too
// hashmap can help in stock - volume mapping and updating it
// getting top K stocks suggests of heap, but heap does not allow to remove stale entries after volume is updated

// use Balanced BST (set)
// maintains element in sorted order
// allows - insert, erase, count, find - LogN operations

// query O(k)
// addition O(log N)

class Solution {
public :
	void addStocksVolume(string name, int volume){
		auto it = mp.find(name);
		if(it == mp.end()){
			mp[name] = volume;
			ranking.insert({volume, name});
		} else {
			ranking.erase({it->second, name});
			// iterator is of map not set
			it->second += volume;
			ranking.insert({it->second, name});
		}
	}

	vector<string> getTopKStocks(int k){
		vector<string> ans;
		auto it = ranking.begin();
		while(it != ranking.end() && k--){
			ans.push_back(it->second);
			it++;
		}
		return ans;
	}

	Solution(){

	}

private :
	unordered_map<string, long long> mp;
	set<pair<long long, string>, greater<pair<long long, string>>> ranking;
};