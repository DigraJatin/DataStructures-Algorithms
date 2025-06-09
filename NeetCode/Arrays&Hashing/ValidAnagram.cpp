#include <bits/stdc++.h>

using std::vector;
using std::string;

class Solution {
public:
    bool isAnagram(string s, string t) {
        // Aproach 1 - sorting should result in exact match
        // sort(s.begin(), s.end());
        // sort(t.begin(), t.end());
        // return s == t;

        // Aproach 2 - using map to store frequecy of each element
        vector<int> dataSet(26,0);
        for(const auto &c : s){
        	dataSet[c-'a']++;
        }
        for(const auto &c : t){
        	dataSet[c-'a']--;
        }
        for(const auto &i : dataSet){
        	if(i!=0)
        		return false;
        }
        return true;
    }
};

int main(){
	std::string s = "anagram", t = "nagaram";
	bool result = Solution{}.isAnagram(s,t);
	std::cout<<result;
}