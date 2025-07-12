#include <iostream>
#include <vector>
#include <functional>
#include <queue>
using namespace std;
// 堆(以最大堆为例)，可以当优先队列直接使用
class MaxHeap
{
    // STL的优先队列：
    // #include<queue>//including std::priority_queue
    // 最大堆 ​：优先级高的（值大的）先出队 : std::priority_queue<int> max_pq;
    // 最小堆 ​：优先级低的（值小的）先出队 : std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    // 自定义优先级的堆：
    // struct Task
    // {
    //     int priority;
    //     std::string name;
    // };
    // // 自定义比较函数（最小堆）
    // auto cmp = [](const Task &a, const Task &b)
    // {
    //     return a.priority > b.priority;
    // };
    // // 注意：需要指定底层容器和比较函数类型
    // std::priority_queue<Task, std::vector<Task>, decltype(cmp)> task_pq(cmp);

public:
    std::vector<int> heap; // 用数组来存储堆
    // 对于任意结点i，左子结点2i+1，右子结点2i+2，父结点(i-1)/2;(=======前提：索引有效=======)

    // 返回堆顶（最大值）
    int top() const
    {
        if (heap.empty())
        {
            throw std::out_of_range("Heap is empty!");
        }
        return heap[0];
    }

    // 返回堆的大小
    int size() const
    {
        return heap.size();
    }

    // 判断堆是否为空
    bool empty() const
    {
        return heap.empty();
    }

    // 插入元素
    void push(int val)
    {
        heap.push_back(val);        // 添加到末尾
        heapifyUp(heap.size() - 1); // 上浮调整
    }

    // 移除堆顶（最大值）
    void pop()
    {
        if (heap.empty())
        {
            throw std::out_of_range("Heap is empty!");
        }
        heap[0] = heap.back(); // 用末尾元素覆盖堆顶
        heap.pop_back();       // 移除末尾
        if (!heap.empty())
        {
            heapifyDown(0); // 下沉调整
        }
    }

    // 上浮（调整新插入的元素）
    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[parent] >= heap[index])
                break;                            // 父节点 ≥ 当前节点，无需调整
            std::swap(heap[parent], heap[index]); // 否则交换
            index = parent;                       // 继续向上检查
        }
    }

    // 下沉（调整堆顶被移除后的堆）
    void heapifyDown(int index)
    {
        int n = heap.size();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index; // 假设当前节点是最大的

            // 比较左子节点
            if (left < n && heap[left] > heap[largest])
            {
                largest = left;
            }
            // 比较右子节点
            if (right < n && heap[right] > heap[largest])
            {
                largest = right;
            }
            // 如果当前节点已经是最大的，停止下沉
            if (largest == index)
                break;

            std::swap(heap[index], heap[largest]); // 交换
            index = largest;                       // 继续向下检查
        }
    }

    // 堆排序
    void heapSort(vector<int> &vec)
    {
        std::function<void(vector<int> &, int, int)> heapify = [&](vector<int> &vec, int n, int i)
        {
            int left = 2 * i + 1, right = 2 * i + 2, largest = i;
            if (left < n && vec[largest] < vec[left])
                largest = left;
            if (right < n && vec[largest] < vec[right])
                largest = right;
            if (largest != i)
            {
                swap(vec[largest], vec[i]);
                heapify(vec, n, largest);
            }
        };
        for (int i = vec.size() / 2 - 1; i >= 0; i--)
        {
            heapify(vec, vec.size(), i);
        }
        for (int i = vec.size() - 1; i > 0; i--)
        {
            swap(vec[i], vec[0]);
            heapify(vec, i, 0);
        }
    }
};