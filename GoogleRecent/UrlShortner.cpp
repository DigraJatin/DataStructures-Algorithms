// We need a class:

// URLShortener(int T)
// string getNext()

// getNext() must return a unique valid string every time.

// A string is valid when:

// Only a-z are used.
// Every character occurs at most T times.
// No string is returned twice.
// Shorter strings must always come first.

// So if T = 2, the beginning looks like:

// a
// b
// c
// ...
// z

// aa
// ab
// ac
// ...
// az
// ba
// bb
// ...
// zz

// aaa  ❌

// aaa is invalid because a occurs 3 times.

class URLShortner {
public :
	int threshold;
	queue<string> q;

	URLShortner(int t) : threshold(t) {
		if(threshold >= 1){
			for(char c = 'a'; c <= 'z'; c++){
				// string ctor allows len, char
				q.push(string(1, c));
				// initially our queue looks like a,b,c,d.....z
			}
		}
	}

	string getNext(){
		if(q.empty()) return;

		string curr = q.front();
		q.pop();

		// insert next formable strings from this into q
		vector<int> fq(26,0);
		for(char c : curr) fq[c]++;

		for(int i = 0; i < 26; i++){
			if(freq[i] < threshold){
				char c = 'a' + i;
				q.push(curr +  c);
			}
		}

		return curr;
	}
};