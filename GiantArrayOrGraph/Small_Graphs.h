#include <vector>
using Graph = std::vector<std::vector<int>>;// 邻接表
using wGraph = std::vector<std::vector<std::pair<int, int>>>; // 带权图,(vertex,weight)

wGraph SuperWeightGraph = {
    {{18, 12}, {13, 16}, {6, 9}, {16, 12}, {14, 6}, {10, 7}},               // 0
    {{8, 14}},               // 1
    {{16, 13}, {6, 10}, {3, 2}, {15, 5}},               // 2
    {{19, 14}, {18, 20}, {15, 2}, {9, 11}, {2, 2}},               // 3
    {{11, 1}, {18, 18}, {5, 2}, {8, 8}},               // 4
    {{15, 2}, {17, 15}, {4, 2}, {9, 4}},               // 5
    {{10, 15}, {11, 7}, {9, 2}, {0, 9}, {15, 20}, {17, 7}, {2, 10}},               // 6
    {{19, 4}, {11, 8}, {18, 16}, {8, 2}},               // 7
    {{1, 14}, {10, 18}, {7, 2}, {4, 8}},               // 8
    {{6, 2}, {14, 20}, {12, 2}, {3, 11}, {16, 17}, {5, 4}, {17, 15}, {19, 4}},               // 9
    {{17, 20}, {6, 15}, {0, 7}, {14, 5}, {8, 18}},               // 10
    {{14, 7}, {6, 7}, {4, 1}, {12, 14}, {15, 10}, {7, 8}},               // 11
    {{9, 2}, {15, 14}, {11, 14}},               // 12
    {{0, 16}, {18, 12}, {14, 4}},               // 13
    {{11, 7}, {0, 6}, {9, 20}, {13, 4}, {16, 13}, {10, 5}},               // 14
    {{5, 2}, {17, 7}, {12, 14}, {11, 10}, {6, 20}, {3, 2}, {16, 9}, {2, 5}},               // 15
    {{18, 6}, {0, 12}, {17, 3}, {2, 13}, {14, 13}, {15, 9}, {9, 17}},               // 16
    {{10, 20}, {5, 15}, {15, 7}, {16, 3}, {6, 7}, {9, 15}},               // 17
    {{0, 12}, {3, 20}, {16, 6}, {13, 12}, {4, 18}, {7, 16}},               // 18
    {{3, 14}, {7, 4}, {9, 4}}               // 19
};

Graph SuperGraph = {
    {18, 13, 6, 16, 14, 10},//0
    {8},//1
    {16, 6, 3, 15},//2
    {19, 18, 15, 9, 2},//3
    {11, 18, 5, 8},//4
    {15, 17, 4, 9},//5
    {10, 11, 9, 0, 15, 17, 2},//6
    {19, 11, 18, 8},//7
    {1, 10, 7, 4},//8
    {6, 14, 12, 3, 16, 5, 17, 19},//9
    {17, 6, 0, 14, 8},//10
    {14, 6, 4, 12, 15, 7},//11
    {9, 15, 11},//12
    {0, 18, 14},//13
    {11, 0, 9, 13, 16, 10},//14
    {5, 17, 12, 11, 6, 3, 16, 2},//15
    {18, 0, 17, 2, 14, 15, 9},//16
    {10, 5, 15, 16, 6, 9},//17
    {0, 3, 16, 13, 4, 7},//18
    {3, 7, 9}//19
};
