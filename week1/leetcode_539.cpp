/*
*  https://leetcode.com/problems/minimum-time-difference/
*Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum minutes difference between any two time points in the list.
*Example 1:
*Input: ["23:59","00:00"]
*Output: 1
*Note:
*The number of time points in the given list is at least 2 and won't exceed 20000.
*The input time is legal and ranges from 00:00 to 23:59.
*
*/

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        std::vector<uint32_t> timeVec;
        for(auto item: timePoints)
        {
            uint32_t hour=0;
            uint32_t min=0;
            sscanf(item.c_str(),"%u:%u",&hour, &min);
            min += hour * 60;
            timeVec.push_back(min);
        }
        sort(timeVec.begin(), timeVec.end());
        
        uint32_t one_day_min = 24 *60;
        uint32_t ans = one_day_min;
        timeVec.push_back(timeVec[0]+one_day_min);
        for(size_t i = 0 ; i < timeVec.size() -1; i++)
        {
            ans = min(ans, min(timeVec[i+1]- timeVec[i], one_day_min + timeVec[i]- timeVec[i+1]));
        }
        return ans;
    }
};
