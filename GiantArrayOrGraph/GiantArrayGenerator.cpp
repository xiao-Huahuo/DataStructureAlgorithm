#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#define SIZE 10000
#define FILENAME "Giant_Array.h"
using namespace std;
std::vector<int> generateShuffledArray(int size)
{
    std::vector<int> arr(size);

    // 填充有序序列（0到size-1）
    for (int i = 0; i < size; ++i)
    {
        arr[i] = i;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));

    return arr;
}

int main()
{
    std::vector<int> shuffledArray = generateShuffledArray(SIZE);
    std::ofstream ofs(FILENAME, ios::out | ios::trunc);
    if (!ofs.is_open())
        return 1;
    ofs << "#include<vector>\nstd::vector<int> SuperArray = {";
    for (int i = 0; i < SIZE; ++i)
    {
        ofs << shuffledArray[i];
        if (i < SIZE - 1)
            ofs << ",";
    }
    ofs << "}" << ';';
    ofs.close();
    return 0;
}