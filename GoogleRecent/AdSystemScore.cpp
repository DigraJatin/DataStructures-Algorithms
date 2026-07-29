
class Solution {
	public : 
		Solution (int k)
		{	
			gap = k;
		}

		insertAd(string content, int score){
			maXHeap.push({score, content, ++nextId});
		}

		// should alwasy return the highest scored ad
		// after returning decrease the ad score
		// same ad cannot appear consecutively
		// This is done using max heap + lastShown Tracking O(LogN) both add and getAd

		// Follow up - cooldown of k calls to getAd
		// ad returned at t, it cannot be returned unless k calls to getAd are made

		string getAd() {
			currentTime++;

			releaseExpireAds();

			if(maXHeap.empty()) return "";

			Ad ad = maXHeap.top();
			maXHeap.pop();

			string result = ad.content;
			ad.score--;

			if(ad.score > 0){
				q.push({ad, currentTime + gap + 1});
			}

			return result;

			// older approach before follow up, was a special case of cooldown with value 1
			// if(maXHeap.empty()) return "";
			// auto first = maXHeap.top();
			// maXHeap.pop();

			// if(!hasLastShown || first.content != lastShownAd) {
			// 	string result = first.content;
			// 	first.score--;

			// 	if(first.score > 0) maXHeap.push(first);

			// 	lastShownAd = result;
			// 	hasLastShown = true;
			// 	return result;
			// }

			// // no 2nd best ad exists
			// if(maXHeap.empty()){
			// 	maXHeap.push(first);
			// 	return "";
			// }

			// Ad second = maXHeap.top();
			// maXHeap.pop();

			// string result = second.content;
			// second.score--;
			// if(second.score >0) maXHeap.push(second);
			// maXHeap.push(first);
			// lastShownAd = result
			// hasLastShown = true;
			// return result;
		}

	private : 
		struct Ad {
			int score;
			string content;
			int id;
		};

		struct CoolDownEntry {
			int readyTime;
			Ad ad;
		};

		struct compare {
			bool operator()(const Ad& a, const Ad& b){
				if(a.score != b.score) return a.score < b.score; // low priority if score is less, high priority if high score (towards heap's top)
				return a.id > b.id; // earlier inserted ad gets more priority
			}
		};

		// move expired ads from waiting queue to heap
		void releaseExpireAds() {	
			while(!q.empty() && q.front().readyTime <= currentTime){
				maXHeap.push(q.front().ad);
				q.pop();
			}
		}

		priority_queue<Ad, vector<Ad>, compare> maXHeap; // ad with most score on top
		queue<CoolDownEntry> q;

		string lastShownAd;
		bool hasLastShown = false;
		int nextId = 0;
		int gap;
		int currentTime = 0;

};

// moved from general max heap + lastSeen tracking to genric time tracker and queue based maintaince
// if score lies in small range like 1...100, can use bucket sort to do better