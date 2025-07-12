#include <iostream>
#include <sstream>
using namespace std;
class SqList
{
public:
    int *data;
    int reserve;
    int size;
    SqList(const int &sz = 1) : size(0), reserve(sz)
    {
        data = new int[reserve];
    }
    SqList(const int *&initArr, const int &sz) : size(sz), reserve(sz)
    {
        data = new int[reserve];
        for (int i = 0; i < size; i++)
        {
            data[i] = initArr[i];
        }
    }
    SqList(const SqList &other)
    {
        data = new int[other.reserve];
        size = other.size;
        reserve = other.reserve;
        for (int i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
        }
    }
    ~SqList()
    {
        delete[] data;
        data = NULL;
    }
    // 调节大小
    void resize(const int &newSize)
    {
        if (newSize == reserve)
            return;
        else if (newSize > reserve)
        {
            // 扩容
            int *newdata = new int[newSize];
            for (int i = 0; i < size; i++)
            {
                newdata[i] = data[i];
            }
            delete[] data;
            data = newdata;
            reserve = newSize;
        }
        else
        {
            // 缩容
            size = reserve = newSize;
        }
    }
    // 尾插
    void push_back(const int &newval)
    {
        if (size >= reserve)
        {
            // 扩容
            resize(2 * size);
        }
        data[size++] = newval;
    }
    // 尾删
    void pop_back()
    {
        if (!size)
            return;
        size--;
    }
    // 索引
    int &operator[](const size_t &Index)
    {
        if (Index >= size)
            throw std::out_of_range("Index out of range");
        return data[Index];
    }
    // 在Index前面插入
    void insert(const size_t &Index, const int &newval)
    {
        if (Index >= size)
            throw std::out_of_range("Index out of range");
        if (size == reserve)
            resize(2 * reserve);
        int i = size++;
        for (; i > Index; i--)
        {
            // 移动后序的数
            data[i] = data[i - 1];
        }
        data[i] = newval;
    }
};

void print(const SqList &list)
{
    for (int i = 0; i < list.size; i++)
    {
        std::cout << list.data[i] << ' ';
    }
}
void bubbleSort(SqList &list)
{
    for (int i = 0; i < list.size - 1; i++)
    {
        bool isSorted = false;
        for (int j = 0; j < list.size - i - 1; j++)
        {
            if (list[j + 1] < list[j])
            {
                std::swap(list[j + 1], list[j]);
                isSorted = true;
            }
        }
        if (!isSorted)
            return;
    }
}
SqList mergeSort(const SqList &A, const SqList &B)
{
    SqList C(A.size + B.size), a(A), b(B);
    int i = 0, j = 0, k = 0;
    // 保证a，b都是有序序列
    bubbleSort(a);
    bubbleSort(b);
    while(i<a.size&&j<b.size){
        if(a[i]<b[j]){
            C[k++] = a[i++];
        }
        else if(a[i]>b[j]){
            C[k++] = b[j++];
        }
        else
        {
            C[k++] = a[i];
            i++;
            j++;
        }
    }
    while(i<a.size)
        C[k++] = a[i++];
    while(j<b.size)
        C[k++] = b[j++];
    return C;
}
SqList set_difference(const SqList&A,const SqList&B){
    SqList C(std::max(A.size,B.size)), a(A), b(B);
    int i = 0, j = 0;
    // 保证a，b都是有序序列
    bubbleSort(a);
    bubbleSort(b);
    //求A-B
    while (i < a.size && j < b.size)
    {
        if (a[i] < b[j])
        {
            C.push_back(a[i++]);
        }
        else if (a[i] > b[j])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }
    while (i < a.size)
        C.push_back(a[i++]);
    return C;
}

int main()
{
    SqList A(1000), B(1000);
    int inputNum;
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss1(line);
    while(ss1>>inputNum){
        A.push_back(inputNum);
    }
    std::getline(std::cin, line);
    std::stringstream ss2(line);
    while (ss2 >> inputNum)
    {
        B.push_back(inputNum);
    }
    SqList dif = set_difference(A, B);
    print(dif);
    return 0;
}