##K-th Smallest in Lexicographical Order
  Given integers n and k, find the lexicographically k-th smallest integer in the range from 1 to n.
Note: 1 ≤ k ≤ n ≤ 109.

Example:
    Input:
    n: 13   k: 2
    Output:
    10
    Explanation:
    The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.


题意很简单易懂，可以理解为把数字转为字符串比大小排序。
思路：
所有1开头的，小于2开头的，依次类推。那得到一个n之后，首先可以计算出比1小的有多少，比2小的有多少，等等。
数组dig_n[i]表示n的第i为多少。
那以1开头的数字的个数就为

这里是最开始的实现思路，有问题
#####begin
    //max_dig 表示当前的最高位
    small_than_1 = 0
    for(i=0; i < max_dig - 1 ;i++)
        small_than_1 += pow(10,i);
    if( dig_n[max_dig - 1] > 1)
        small_than_1 += pow(10, max_dig - 1);
    else if(dig_n[max_dig - 1] == 1)
        small_than_1 += now_n % pow(10, max_dig-1);
类推，以x为开头的数字个数计算 只需要把比较 > 1 替换为 > x 即可。

那计算出1-9开头的数字个数后，首先就可以定位到第k小的，是以什么开头了。然后再把首位去除之后，继续按此方案计算。
small_than_x[i]表示以i为开头的数字个数。

    void recursion(int max_dig, int dig_n[], int k, int *ans)
    {
        for(i=1; i < 10; i++)
        {
            if(k > small_than_x[i])
            k -= small_than_x[i];
            else
            {
                ans = ans * 10 + i-1;   
                recursion(max_dig-1, dig_n, k);
            }
        }
    }
#####end

先贴上最终AC的代码，后续再来梳理逻辑

    class Solution {
    public:
        
        void recursion(int max_dig, int dig_n[], int k, int *ans, bool begin)
        {
            cout << max_dig << "|" << k << "|" << *ans << endl;
            for(int i = max_dig-1; i >= 0; i--)
                cout << dig_n[i];
            cout << endl;
            if(max_dig < 0 || k <= 0)
                return ;
            int small_than_x[10] = {0};
            int base_num = 0;
            int next_n = 0;
            for(int i = max_dig -2 ; i >= 0 ; i--)
            {    
                base_num = base_num * 10 + 1;
                next_n = next_n * 10 + dig_n[i];
            }
            //small_than_x[0] = next_n % 10 ;
            for(int i = 0 ; i < 10; i++)
            {
                small_than_x[i] = base_num;
                if(dig_n[max_dig-1] > i)
                    small_than_x[i] += pow(10, max_dig -1);
                else if(dig_n[max_dig - 1] == i)
                    small_than_x[i] += next_n +1;
                cout << "small_than_" << i << " num count is " << small_than_x[i] << endl;
            }
            if(begin)
                small_than_x[0] =0;
            for(int i=0; i < 10; i++)
            {
                if(k > small_than_x[i])
                    k -= small_than_x[i];
                /*
                else if(k == small_than_x[i])
                {
                    *ans = *ans * 10 + i;
                    return ;
                }
                */
                else
                {
                    *ans = *ans * 10 + i;
                    k -=  1;
                    cout << "i:" << i << "|dig_n[max_dig-1]:" << dig_n[max_dig-1] <<endl;
                    if(i != dig_n[max_dig-1])
                    {
                        for(int k = max_dig -2 ; k >= 0; k--)
                            dig_n[k] = 10;
                        if(i > dig_n[max_dig-1])
                        {
                            return recursion(max_dig-2, dig_n, k, ans,false);   
                        }
                        else
                        {
                            return recursion(max_dig-1, dig_n, k, ans,false);
                        }
                    }
                    else
                    {
                        return recursion(max_dig-1, dig_n, k, ans, false);
                    }
                }
            }
            return ;
        }
        
        int findKthNumber(int n, int k){
            
            int dig_n[10] = {0};
            int i = 0;
            int tmp = n;
            while(tmp > 0)
            {
                dig_n[i++] = tmp % 10;
                tmp /= 10;
            }
            int ans = 0;
            recursion(i, dig_n, k , &ans, true);
            return ans;
        }
    };