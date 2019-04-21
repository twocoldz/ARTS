##[442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)

Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements that appear twice in this array.

Could you do it without extra space and in O(n) runtime?

Example:
Input:
[4,3,2,7,8,2,3,1]

Output:
[2,3]

题意很简单，难度在于O(N)时间复杂度 和 O(1)的空间复杂度。
思路就是在原数组上进行vis标记。有些小地方需要注意，比如nums[index] == index+1 的情况，需要特殊处理等。

    class Solution {
    public:
        vector<int> findDuplicates(vector<int>& nums) {
            vector<int> ans;
            for(size_t i = 0 ; i < nums.size(); ++i)
            {
                auto index = i;
                bool first_vis = true;
                while(index >= 0)
                {
                    //cout << index << ",";
                    auto next_index = nums[index] -1;
                    if(!first_vis)
                        nums[index] = 0;
                    else if(first_vis && nums[index] != 0)
                        nums[index] = -1;
                    first_vis = false;
                    if(next_index < 0||nums[next_index] == 0 || nums[next_index] == -1)
                    {
                        if(next_index >=0 && nums[next_index] == 0)
                            ans.push_back(next_index+1);
                        else if(next_index >= 0 && nums[next_index] == -1)
                            nums[next_index] = 0;
                        break;
                    }
                    index = next_index;
                }
                /*
                cout << endl;
                for(size_t j = 0 ;j < nums.size();++j)
                    cout << nums[j] << ",";
                cout << endl;
                */
            }
            return ans;
        }
    };