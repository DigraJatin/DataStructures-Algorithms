// Problem Statement:
// You are given coordinates one by one.
// After each insertion, you need to check whether any four points seen so far can form a square.
// A square can be formed using any subset of 4 points.

struct KeyHas{
	bool operator()(const pair<int,int>& key) const {
		auto h1 = hash<int>{}(key.first);
		auto h1 = hash<int>{}(key.second);
		return h1 ^ (h2 << 1);
	}
};

class SquareDetector {
private:
	unordered_set<int,int>, KeyHash> points;

public:
	bool insert(int x, int y){
		if(points.count({x,y})) return false;

		// curr point = A (x,y)
		// pick second point B = (bx, by)
		for(auto [bx, by] : points){\
			// AB vector
			int dx = bx - x;
			int dy = by - y;
			// let's say they form A--------B

			// +ve 90 rotate
			// D -------- C
			// |          |
			// |          |
			// A -------- B

			// -90 rotate
		     // A -------- B
		     // |          |
		     // |          |
		     // D -------- C

			// (dx,dy) is vector representing AB
			// to get other 2 points we need to rotate

			// Rotate AB(dx,dy) by +90 degrees (counterClockWise)
			// (x,y) on +90 becomes (-y,x) (clockWise)
			// AD vector would be the rotated (-dy, dx) vector
			pair<int,int> d1 = {
				// D = A + AD
				// D = (x,y) + (-dy,dx) 
				// D = (x-dy, y+dx)
				x-dy,
				y+dx
			}

			pair<int,int> c1 = {
				// C = B + BC (same -dy,dx = c)
				// C = (bx, by) + (-dy,dx)
				bx-dy,
				by+dx
			};

            if (points.count(c1) && points.count(d1)) {
                points.insert({x, y});
                return true;
            }

			// Rotate AB by -90 degrees
			// (x,y) on -90 becomes (y,-x)
			// (dx,dy) becomes (dy, -dx)

			pair<int,int> d2 = {
				// D = A + AD
				// D = (x,y) + (dy, -dx)
				x + dy,
				y - dx
			};

			pair<int,int> c2 = {
				// C = B + BC
				// C = (bx, by) + (dy,-dx)
				bx+dy,
				by-dx
			};

            if (points.count(c2) && points.count(d2)) {
                points.insert({x, y});
                return true;
            }
		}

		points.insert({x,y});
		return false;
	}
};

/*
    Time Complexity:
        insert() = O(n) average
        n insertions = O(n^2) average

    Space Complexity:
        O(n)
*/


// Also see Detect Squares leetcode
// https://leetcode.com/problems/detect-squares/description/
// follow up to this is what we solved above