##980. Unique Paths III

On a 2-dimensional grid, there are 4 types of squares:

1 represents the starting square.  There is exactly one starting square.
2 represents the ending square.  There is exactly one ending square.
0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.

本质上就是一个dfs，不过一段时间没写 还是有点生疏了。dfs的关键就是结束条件和递归策略，这两个想清楚了，基本就搞定了。

    class Solution {
    public:
        const int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
        void dfs(vector<vector<int>>& grid, int height, int width,int now_x,int now_y, int left, int *ans)
        {
            //cout << "(" << now_x << "," << now_y << ") " << left << endl;  
            if(left < 0)
            {
                return ;
            }
            for(int i =0 ; i < 4; i++)
            {
                int new_x = now_x + dir[i][0];
                int new_y = now_y + dir[i][1];
                if(new_x >= height || new_x < 0 || new_y >= width || new_y < 0)
                    continue;
                if(grid[new_x][new_y] == 0 )
                {
                    grid[new_x][new_y] = -1;
                    dfs(grid, height, width, new_x, new_y, left -1, ans);
                    grid[new_x][new_y] = 0;
                }
                else if(grid[new_x][new_y] == 2)
                {
                    //cout << "++(" << now_x << "," << now_y << ") " << left << endl;
                    if(left == 0)
                        (*ans)++;
                }
            }
            return ;
        }
        int uniquePathsIII(vector<vector<int>>& grid) {
            int ans = 0;
            int walk_count =0;
            int height = grid.size();
            int width = grid[0].size();
            int begin_x = -1;
            int begin_y = -1;
            for(size_t i = 0; i < height; i++)
            {
                for(size_t j = 0 ; j < width ;j++)
                {
                    if(grid[i][j]==0)
                        ++walk_count;
                    if(grid[i][j]==1)
                        begin_x = i, begin_y = j;
                }
            }
            dfs(grid, height, width,begin_x, begin_y , walk_count, &ans);
            return ans;
        }
    };
