#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(const int &val = 0) : data(val), next(NULL) {}

    // 增加的可能使用的
    Node *prev;
    int freq;
};

// 链表有头结点

// 创建链表
Node *create()
{
    return new Node();
}
// 打印链表
void print(Node *head)
{
    if (!head)
        return;
    if (!head->next)
        return;
    Node *curr = head->next;
    while (curr)
    {
        std::cout << curr->data << ' ';
        curr = curr->next;
    }
}
// 销毁链表
void clear(Node *&head)
{
    if (!head)
        return;
    Node *curr = head;
    while (curr)
    {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = NULL;
}
// 输出链表大小
size_t size(Node *head)
{
    if (!head)
        return 0;
    Node *curr = head;
    size_t count = 0;
    while (curr->next)
    {
        count++;
        curr = curr->next;
    }
    return count;
}
// 尾插法
void push_back(Node *&head, const int &newval)
{
    if (!head)
        return;
    Node *last = head;
    while (last->next)
        last = last->next;
    last->next = new Node(newval);
}
// 头插法
void push_front(Node *&head, const int &newval)
{
    if (!head)
        return;
    if (!head->next)
    {
        head->next = new Node(newval);
        return;
    }
    Node *newnode = new Node(newval);
    newnode->next = head->next;
    head->next = newnode;
}
// 尾删法
bool pop_back(Node *&head)
{
    if (!head)
        return false;
    if (!head->next)
        return false;
    Node *befLast = head;
    while (befLast->next->next)
        befLast = befLast->next;
    delete befLast->next;
    befLast->next = NULL;
    return true;
}
// 头删法
bool pop_front(Node *&head)
{
    if (!head)
        return false;
    if (!head->next)
        return false;
    Node *temp = head->next;
    head->next = head->next->next;
    delete temp;
    return true;
}
// 找到index处的结点并返回
Node *findIndexNode(Node *head, const size_t &Index)
{
    if (!head)
        return NULL;
    if (Index >= size(head))
        return NULL;
    Node *curr = head;
    for (int i = 0; i <= Index; ++i)
        curr = curr->next;
    return curr;
}
// 寻找某个数值的结点
Node *findValNode(Node *head, int val)
{
    if (!head)
        return NULL;
    Node *curr = head->next;
    while (curr && curr->data != val)
    {
        curr = curr->next;
    }
    if (!curr)
        return NULL;
    else
        return curr;
}
// 在Index前面插入
bool insert(Node *&head, const size_t &Index, const int &newval)
{
    if (!head)
        return false;
    if (Index > size(head))
        return false;
    Node *prenode = head;
    for (int i = 0; i < Index; ++i)
        prenode = prenode->next;
    Node *newnode = new Node(newval);
    newnode->next = prenode->next;
    prenode->next = newnode;
    return true;
}
// 反转链表
void reverse(Node *&head)
{
    if (!head)
        return;
    Node *prev = NULL, *curr = head->next, *next = NULL;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head->next = prev;
}
// 交换双链表的两个结点
void exchange(Node *a, Node *b)
{
    // 七步法:顺顺逆
    // 虚实结合，上实(next)下虚(prev)
    a->prev->next = b;
    b->prev = a->prev;
    a->next = b->next;
    if (b->next) // 别忘了这个if
        b->next->prev = a;
    b->next = a;
    a->prev = b;
    a = b->prev; // 第七步要注意，不是b->prev=a而是a=b->prev
}
// 将<0的结点放在>=0的前面
void sortZero(Node *&head)
{
    if (!head)
        return;
    if (!head->next)
        return;
    // 两个链表，一个存放<0,一个存放>=0
    Node *low = new Node, *high = new Node, *lowCurr = low, *highCurr = high, *curr = head->next;
    while (curr)
    {
        if (curr->data < 0)
        {
            lowCurr->next = curr;
            lowCurr = lowCurr->next;
        }
        else
        {
            highCurr->next = curr;
            highCurr = highCurr->next;
        }
        curr = curr->next;
    }
    // 合并链表
    clear(head);
    head = new Node;
    if (!low->next)
    {
        // 如果low为空，直接跳过
        head->next = high->next;
    }
    else
    {
        head->next = low->next;
        // 此时lowCurr为low的尾结点
        lowCurr->next = high->next;
    }

    delete low;
    delete high;
}
// 找中间结点(靠前的) 0 1 2 3 4 5
Node *mid(Node *head)
{
    if (!head)
        return NULL;
    Node *quick = head, *slow = head; // 若没有头结点则quick=head->next,slow=head;其中head是第一个结点
    while (quick && quick->next)
    {
        quick = quick->next->next;
        slow = slow->next;
    }
    return slow;
}

// 链表插入排序
void insertionSort(Node *head)
{
    // 插入排序：将表划分为有序和未排序两个部分，每次将未排序的一个结点取出插入到已排序的部分
    Node *curr, *next, *preEnd;
    curr = head->next->next; // curr初始指向第 2 个数据结点
    head->next->next = NULL; // curr前结点的next是断开的
    while (curr)
    {
        next = curr->next;
        preEnd = head;
        while (preEnd->next && preEnd->next->data < curr->data)
            preEnd = preEnd->next;
        // 在结点 preEnd 之后插入 curr 结点
        curr->next = preEnd->next;
        preEnd->next = curr;
        curr = next;
    }
}
// 链表归并排序：适合于 !!!没有头结点!!! 的链表
class MergeSortSolution
{
    // 合并两个有序链表
    Node *merge(Node *l1, Node *l2)
    {
        if (!l1)
            return l2; // 若 l1 为空，返回 l2
        if (!l2)
            return l1;         // 若 l2 为空，返回 l1
        Node *head = new Node; // 虚拟头结点
        Node *tail = head;
        while (l1 && l2)
        {
            if (l1->data < l2->data)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        // 将剩余的链表连接到尾部
        if (l1)
            tail->next = l1;
        if (l2)
            tail->next = l2;
        Node *newHead = head->next;
        delete head; // 删掉虚拟头结点
        return newHead;
    }
    // 归并排序主函数
    Node *mergeSort(Node *head)
    {
        if (!head || !head->next)
            return head; // 注意：1.单结点的情况要包括入;2.返回的是首节点head而不是NULL
        // 使用快慢指针找到链表中点(注意是中间靠前的结点)
        Node *slow = head;
        Node *quick = head->next;
        while (quick && quick->next)
        {
            slow = slow->next;
            quick = quick->next->next;
        }
        Node *mid = slow->next; // mid是右边的首结点
        slow->next = nullptr;   // 注意分割链表
        // 递归排序左右两部分
        Node *left = mergeSort(head);
        Node *right = mergeSort(mid);
        // 合并两个有序链表
        return merge(left, right);
    }
};

// 链表的交并差集
class Intersection_Union_Difference_Solution
{
public:
    // 求A+B并集
    Node *set_union(Node *A, Node *B)
    {
        if (!A || !B)
            return NULL;
        Node *newHead = new Node, *precurr = newHead, *pa = A->next, *pb = B->next;
        while (pa && pb)
        {
            if (pa->data < pb->data)
            {
                precurr->next = new Node(pa->data);
                precurr = precurr->next;
                pa = pa->next;
            }
            else if (pa->data > pb->data)
            {
                precurr->next = new Node(pb->data);
                precurr = precurr->next;
                pb = pb->next;
            }
            else
            {
                precurr->next = new Node(pa->data);
                precurr = precurr->next;
                pa = pa->next;
                pb = pb->next;
            }
        }
        while (pa)
        {
            precurr->next = new Node(pa->data);
            precurr = precurr->next;
            pa = pa->next;
        }
        while (pb)
        {
            precurr->next = new Node(pb->data);
            precurr = precurr->next;
            pb = pb->next;
        }
        return newHead;
    }
    // 求A-B差集（二路归并思想）
    Node *set_difference(Node *A, Node *B)
    {
        if (!A || !B)
            return NULL;
        Node *newHead = new Node, *precurr = newHead, *pa = A->next, *pb = B->next;
        while (pa && pb)
        {
            if (pa->data < pb->data)
            {
                // 存入
                precurr->next = new Node(pa->data);
                precurr = precurr->next;
                pa = pa->next;
            }
            else if (pa->data > pb->data)
            {
                // 跳过pb
                pb = pb->next;
            }
            else
            {
                // 一起跳过
                pa = pa->next;
                pb = pb->next;
            }
        }
        while (pa)
        {
            // 继续存入
            precurr->next = new Node(pa->data);
            precurr = precurr->next;
            pa = pa->next;
        }
        // B剩下的结点不要了
        return newHead;
    }
    // 求A B交集
    Node *set_intersection(Node *A, Node *B)
    {
        if (!A || !B)
            return NULL;
        Node *newHead = new Node, *precurr = newHead, *pa = A->next, *pb = B->next;
        while (pa && pb)
        {
            if (pa->data < pb->data)
            {
                pa = pa->next;
            }
            else if (pa->data > pb->data)
            {
                pb = pb->next;
            }
            else
            {
                precurr->next = new Node(pa->data);
                precurr = precurr->next;
                pa = pa->next;
                pb = pb->next;
            }
        }
        return newHead;
    }
};

// 访问频度排序(双链表)
class FrequenceSortSolution
{
    // 设有一个双链表 h，每个结点中除有 prev、data 和 next 三个域外，还有一个访问频度域 freq，在链表被起用之前，其值均初始化为零。每当进行 LocateNode(h，x)运算时，令元素值为 x 的结点中 freq 域的值加 1，并调整表中结点的次序，使其按访问频度的递减 序排列，以便使频繁访问的结点总是靠近表头。试写一符合上述要求的 LocateNode 运算的算法。
    // 解：在 DLinkNode 类型的定义中添加整型 freq 域，给该域初始化为 0。在每次查找到 一个结点 p 时，将其 freq 域增 1，再与它前面的一个结点 pre 进行比较，若 p 结点的 freq域值较大，则两者交换，如此找一个合适的位置。
public:
    bool LocateNode(Node *head, int x)
    {

        Node *p = head->next, *pre;
        while (p && p->data != x)
            p = p->next; // 找 data 域值为 x 的结点 p
        if (!p)          // 未找到的情况
            return false;
        else // 找到的情况
        {
            p->freq++;     // 频度增 1
            pre = p->prev; // 结点 pre 为结点 p 的前驱结点
            while (pre != head && pre->freq < p->freq)
            {
                p->prev = pre->prev;
                p->prev->next = p; // 交换结点 p 和结点 pre 的位置
                pre->next = p->next;
                if (pre->next != NULL) // 若 p 结点不是尾结点时
                    pre->next->prev = pre;
                p->next = pre;
                pre->prev = p;
                pre = p->prev; // pre 重指向结点 p 的前驱结点
            }
            return true;
        }
    }
};

//  链表重排
class ReIndexListSolution
{
public:
    // 【问题描述】
    //    给定一个单链表 L1→L2→⋯→Ln−1→Ln，请编写程序将链表重新排列为 Ln→L1→Ln−1→L2→⋯。例如：给定L为1→2→3→4→5→6，则输出应该为6→1→5→2→4→3。
    // 【输入形式】
    //    每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址和结点总个数，即正整数N(≤105)。结点的地址是5位非负整数，NULL地址用−1表示。
    //    接下来有N行，每行格式为：
    //      Address Data Next
    //    其中Address是结点地址；Data是该结点保存的数据，为不超过105的正整数；Next是下一结点的地址。题目保证给出的链表上至少有两个结点。
    // 【输出形式】
    //    对每个测试用例，顺序输出重排后的结果链表，其上每个结点占一行，格式与输入相同。
    // 【样例输入】
    //  00100 6
    //  00000 4 99999
    //  00100 1 12309
    //  68237 6 -1
    //  33218 3 00000
    //  99999 5 68237
    //  12309 2 33218
    // 【样例输出】
    //  68237 6 00100
    //  00100 1 99999
    //  99999 5 12309
    //  12309 2 00000
    //  00000 4 33218
    //  33218 3 -1

    struct AddrNode
    {
        std::string address;
        int data;
        std::string next;
        AddrNode(const std::string &addr, const int &dat, const std::string &nex = "-1") : address(addr), data(dat), next(nex) {}
    };
    void reindexList()
    {
        std::vector<AddrNode> vec;
        std::string firAddr;
        int TotalNum;
        std::cin >> firAddr >> TotalNum;
        for (int i = 0; i < TotalNum; i++)
        {
            std::string addr, next;
            int data;
            std::cin >> addr >> data >> next;
            vec.push_back(AddrNode(addr, data, next));
        }

        std::vector<AddrNode> sortedVec;
        sortedVec.push_back(*std::find_if(vec.begin(), vec.end(), [&](AddrNode &node)
                                          { return node.address == firAddr; })); // 首结点

        int i = 0;
        AddrNode curr = sortedVec[i];
        while (curr.next != "-1")
        {
            sortedVec.push_back(*std::find_if(vec.begin(), vec.end(), [&](AddrNode &node)
                                              { return node.address == curr.next; }));
            i++;
            curr = sortedVec[i];
        }

        std::vector<AddrNode> finalVec;
        // 此时sortedVec为顺序链表，再利用双指针排序
        int p_pre = 0, p_post = i;
        while (p_pre < p_post)
        {
            finalVec.push_back(sortedVec[p_post]);
            finalVec.push_back(sortedVec[p_pre]);
            p_pre++;
            p_post--;
        }
        if (p_pre == p_post)
        {
            // 奇数结点情况
            finalVec.push_back(sortedVec[p_post]);
        }

        for (int i = 0; i < finalVec.size() - 1; ++i)
        {
            // 打印前面n-1个结点
            AddrNode curr = finalVec[i], next = finalVec[i + 1];
            std::cout << curr.address << ' ' << curr.data << ' ' << next.address << '\n';
        }
        // 打印最后一个结点
        AddrNode last = finalVec[finalVec.size() - 1];
        std::cout << last.address << ' ' << last.data << ' ' << "-1";
    }
};

// LeetCode23:合并K个升序链表
#include <queue>
class mergeKListsSolution
{
    // 题目指的是没有头结点的链表
public:
    // 结点比较结构体
    struct Comparison
    {
        bool operator()(const Node *l1, const Node *l2)
        {
            return l1->data > l2->data;
        }
    };
    Node *mergeKLists(vector<Node *> &lists)
    {
        priority_queue<Node *, vector<Node *>, Comparison> pCurrs; // 存储当前结点的优先队列
        for (auto &lst : lists)
        {
            if (lst)
                pCurrs.push(lst);
        }
        if (pCurrs.empty())
            return NULL;
        Node *newHead = new Node(), *k = newHead;
        while (!pCurrs.empty())
        {
            // 每次取出堆顶并放入新链表
            Node *top = pCurrs.top();
            pCurrs.pop();
            if (top->next)
                pCurrs.push(top->next);
            k->next = top;
            k = k->next;
        }
        k->next = NULL; // 断开尾结点，防止循环
        return newHead->next;
    }
};