// https://leetcode.com/problems/pyramid-transition-matrix/

class Solution {
public:
    bool check(int currIndex, string currBase, string prevBase, 
    std::unordered_multimap<std::string, char>& mp,
    std::unordered_map<string,bool>& dp){
        if(prevBase.size()==1){
            return true;
        }

        if(currIndex == prevBase.size()-1){
            if(dp.find(currBase) != dp.end()){
                return dp[currBase];
            }
            dp[currBase] = check(0, "", currBase, mp, dp);
            return dp[currBase];
        }

        string toFind = prevBase.substr(currIndex,2);
        if(mp.find(toFind) == mp.end()){
            return false;
        }

        auto range = mp.equal_range(toFind);
        for(auto it = range.first; it != range.second; ++it){
            if(check(currIndex+1, currBase + it->second, prevBase, mp,dp)){
                return true;
            }
        }
        return false;
    }

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        std::unordered_multimap<std::string, char> mp;
        std::unordered_map<string,bool> dp;
        for(const auto &str : allowed){
            mp.emplace(str.substr(0,2), str[2]);
        }
        return check(0, "", bottom, mp, dp);
    }
};