#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;
// 排序方法的选择：
// 数据量较小（例如 n ≤ 10）：插入排序
// 数据量中等（例如 10 < n ≤ 1000）：希尔排序/快速排序
// 数据量较大（例如 1000 < n ≤ 10^6）：快速排序/归并排序
// 数据量极大（例如 n > 10^6）：归并排序/堆排序
// 另外：数据范围有限的情况，可以采用计数排序和基数排序。
//     数据分布均匀的情况，可以采用桶排序。
// 1. 冒泡排序
void bubbleSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size() - 1; ++i)
    {
        bool isSort = false;
        for (int j = 0; j < arr.size() - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                isSort = true;
                swap(arr[j], arr[j + 1]);
            }
        }
        if (!isSort)
            return;
    }
}

// 2. 选择排序
void selectionSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size() - 1; ++i)
    {
        int minIdx = i;
        for (int j = i + 1; j < arr.size(); ++j)
        {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}
// 3. 插入排序
void insertionSort(vector<int> &arr)
{
    for (int i = 1; i < arr.size(); ++i)
    {
        int key = arr[i];
        // j从后向前遍历的索引，一边比较一边移动，目标是找到第一个小于等于 key 的位置
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j]; // 将大于key的元素向后移动
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. 希尔排序
void shellSort(vector<int> &arr)
{
    for (int gap = arr.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < arr.size(); ++i)
        {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// 5. 归并排序
// 将两半数组进行合并
void merge(vector<int> &arr, int l, int m, int r)
{
    // 对[l,m],[m+1,r]两边进行归并排序
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= r)
    {
        temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    }
    while (i <= m)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];
    for (int p = 0; p < k; ++p)
        arr[l + p] = temp[p];
}
// 归并排序主函数
void mergeSort(vector<int> &arr, int l, int r)
{
    // 将数组分割为[l,m],[m+1,r]
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);     // 递归对[l,m]排序
    mergeSort(arr, m + 1, r); // 递归对[m+1,r]排序
    merge(arr, l, m, r);      // 合并两半
}
//三路归并排序
class TriplePathMergeSortSolution
{
public:
    void triplePathMerge(vector<int> &vec, int a, int b, int c, int d)
    {
        int i = a, j = b + 1, k = c + 1;
        vector<int> temp(d - a + 1);
        int p = 0;

        while (i <= b && j <= c && k <= d)
        {
            vector<int> arr = {vec[i], vec[j], vec[k]};
            int min = *min_element(arr.begin(), arr.end());
            if (min == vec[i])
                temp[p++] = vec[i++];
            else if (min == vec[j])
                temp[p++] = vec[j++];
            else
                temp[p++] = vec[k++];
        }

        while (i <= b && j <= c)
            temp[p++] = (vec[i] <= vec[j]) ? vec[i++] : vec[j++];
        while (i <= b && k <= d)
            temp[p++] = (vec[i] <= vec[k]) ? vec[i++] : vec[k++];
        while (k <= d && j <= c)
            temp[p++] = (vec[j] <= vec[k]) ? vec[j++] : vec[k++];

        while (i <= b)
            temp[p++] = vec[i++];
        while (j <= c)
            temp[p++] = vec[j++];
        while (k <= d)
            temp[p++] = vec[k++];

        for (int m = 0; m < temp.size(); m++)
            vec[a + m] = temp[m];
    }
    void tripleMergeSort(vector<int> &vec, int l, int r)
    {
        if (l >= r)
            return;
        int quater = (r - l) / 3, a = l, b = l + quater, c = l + 2 * quater, d = r;
        tripleMergeSort(vec, a, b);
        tripleMergeSort(vec, b + 1, c);
        tripleMergeSort(vec, c + 1, d);
        triplePathMerge(vec, a, b, c, d);
    }
};

// 6. 快速排序(Hoare分区改进版)
void quickSort(std::vector<int> &vec, int l, int r)
{
    if (l >= r)
        return;

    // 选择中间元素作为基准
    int pivot = vec[l + (r - l) / 2];
    int i = l, j = r;

    while (i <= j)
    {
        while (vec[i] < pivot)
            i++; // 找到左边 >= pivot 的元素
        while (vec[j] > pivot)
            j--; // 找到右边 <= pivot 的元素
        if (i <= j)
            std::swap(vec[i++], vec[j--]);
    }

    // 递归处理子区间
    quickSort(vec, l, j);
    quickSort(vec, i, r); // 原始Hoare分区：quickSort(vec, j + 1, r);
}

// 7. 堆排序
// 将数组最大堆化：按照堆(完全二叉树且root>childs)的层序遍历(一层一层从左到右存入数，将堆变成一个数组)
void heapify(vector<int> &arr, int n, int i)
{
    // 对于任意一个结点 i ，它的左子节点是 2*i + 1，它的右子节点是 2*i + 2
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // 一旦发生交换，则需要递归调用来保证是最大堆
    }
}
void heapSort(vector<int> &arr)
{
    // 将无序数组最大堆化
    for (int i = arr.size() / 2 - 1; i >= 0; --i) // 完全二叉树最后一个非叶子索引是 arr.size() / 2 - 1
        heapify(arr, arr.size(), i);
    // 不断将堆顶(最大值)取出，直至堆没了
    for (int i = arr.size() - 1; i > 0; --i)
    {
        swap(arr[0], arr[i]); // 将堆顶取出
        heapify(arr, i, 0);
    }
}
// 8. 计数排序
void countingSort(vector<int> &arr)
{
    int maxVal = *max_element(arr.begin(), arr.end());
    vector<int> count(maxVal + 1, 0), output(arr.size());
    for (int num : arr)
        count[num]++;
    for (int i = 1; i <= maxVal; ++i)
        count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; --i)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    arr = output;
}

// 9. 桶排序
void bucketSort(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<float>> buckets(n);
    for (int num : arr)
    {
        int bi = n * num / (1 + *max_element(arr.begin(), arr.end()));
        buckets[bi].push_back(num);
    }
    for (auto &bucket : buckets)
        sort(bucket.begin(), bucket.end());
    int idx = 0;
    for (auto &bucket : buckets)
    {
        for (float num : bucket)
            arr[idx++] = num;
    }
}

// 10. 基数排序
void radixSort(std::vector<int> &arr)
{
    int maxVal = *std::max_element(arr.begin(), arr.end());

    for (int exp = 1; maxVal / exp > 0; exp *= 10)
    {
        std::vector<std::vector<int>> buckets(10);

        for (int num : arr)
            buckets[(num / exp) % 10].push_back(num);

        int idx = 0;
        for (const auto &bucket : buckets)
            for (int num : bucket)
                arr[idx++] = num;
    }
}

// 测试排序算法
int main()
{
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    // 调用任意排序算法，例如：
    quickSort(arr, 0, arr.size() - 1);
    for (int num : arr)
        cout << num << " ";
    return 0;
}