[Hash table vs STL Map](https://www.geeksforgeeks.org/hash-table-vs-stl-map/)

##### 关键信息
1. 哈希表查询时间复杂度在冲突比较少的情况下可以达到O(1),STL Map所使用的红黑树则是O(LogN).
2. 哈希表设计是需要思考的是表在数量亮与表索引记录比值较大时需要考虑重建。
3. STL Map使用红黑树而非AVL树，原因可能时考虑到re-balance的时间复杂度？
4. 之前一直对感觉红黑树很复杂，感觉还是[维基百科](https://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91)解释得比较清楚
5. 记录一个不错的网站，可以可视化很多的数据结构。[here](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)
