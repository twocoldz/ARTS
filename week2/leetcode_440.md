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

    //max_dig 表示当前的最高位
    begin_with_1 = 0
    //首先数字位数小于当前数字的一定有完整的以1开头的数字个数。如n=103时，1开头的数字中，1，10～19在各自的位数上是完整的，且个数为pow(10,i); 0为个位
    for(i=0; i < max_dig - 1 ;i++)
        begin_with_1 += pow(10,i);
    //当最高位大于1时，那以1为开头的100～199一定也是完整的
    //而如果时等于时，那就只有当前除去最高位之后的剩余部分+1（一定别忘了（100-103） 是4个数）
    if( dig_n[max_dig - 1] > 1)
        begin_with_1 += pow(10, max_dig - 1);
    else if(dig_n[max_dig - 1] == 1)
        begin_with_1 += now_n % pow(10, max_dig-1) + 1;
类推，以x为开头的数字个数计算 只需要把比较 > 1 替换为 > x 即可。

那计算出1-9开头的数字个数后，首先就可以定位到第k小的，是以什么开头了。然后再把首位去除之后，继续按此方案计算。
begin_with_x[i]表示以i为开头的数字个数。

    void recursion(int max_dig, int dig_n[], int k, int *ans)
    {
        for(i=1; i < 10; i++)
        {
            if(k > begin_with_x[i])
                k -= begin_with_x[i];
            else
            {
                ans = ans * 10 + i-1;   
                recursion(max_dig-1, dig_n, k);
            }
        }
    }
现在问题就来了（第一天晚上脑子不转了，没有考虑到的地方），首次不会出现以0开头的数字，但是后续就有可能出现了。比如case n=103，k=3；通过上述算法计算出首位为1，那将1除去之后，剩余部分为  [1]0, [1]00, [1]01, [1]02, [1]03.
这时候就需要计算已0开头的数字个数了。逻辑其实和前面是一样的。但首次如果按统一的方案计算，一定会有问题。所以需要特殊处理

    if(begin)
        begin_with_x[0] = 0;
但还存在别的问题。 比如case n=102，k=20. 那首位确定是2之后，除去2本身之外。 剩余的数字为20-29，那这个时候再实用初始的dig_n[]来计算begin_with_x[]就一定是有问题的。所以在本次迭代定位到的开头数字不等于当前最高位的时候，就需要对dig_n[]进行修正。

    if(i != dig_n[max_dig-1])
    {
        for(int k = max_dig -2 ; k >= 0; k--)
            dig_n[k] = 10;  //为何是10不是9呢， 因为9是数字大小，然而个数是10
        if(i > dig_n[max_dig-1])
        {
            return recursion(max_dig-2, dig_n, k, ans,false);   
        }
        else
        {
            return recursion(max_dig-1, dig_n, k, ans,false);
        }
    }
另外上面的代码也可以发现，当当前确认的数字开头大于当前最高位上的数字时，迭代下去的最高位时减2，而非减1.这里因为选中的数字开头的所有数字最大也是比当前数字少一位的。

所以最终AC的代码就这样了（懒得改变量名了）：

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

周六晚整体的思路时没问题的，但是确实有很多细节问题没考虑到。果然还是不能在没脑子的时候强行写题。。。