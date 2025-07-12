#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
struct Node
{
    int tag; // 标签，0是原子(储存data)，1是子表(储存sublist)
    union
    {
        Node *sublist;
        char data;
    } val;      // 指向的内容
    Node *link; // 兄弟结点

    // 默认构造函数
    Node(int tg = 0) : tag(tg), link(NULL)
    {
        if (tag == 0)
        {
            val.data = '\0'; // 初始化原子节点
        }
        else
        {
            val.sublist = NULL; // 初始化子表节点
        }
    }

    // 带初始值的构造函数
    Node(int tg, const char &ini_val) : tag(tg), link(NULL)
    {
        if (tag == 0)
        {
            val.data = ini_val; // 初始化原子节点
        }
        else
        {
            val.sublist = NULL; // 初始化子表节点
        }
    }
};

// 创建广义表 "(a,(b,c,d),(#))"
Node *createGList(const char *&str) // 此处使用C风格字符串，便于移动
{
    // 扫描两个字符，第一次扫描用于判断原子和子表的情况，第二次扫描用于判断兄弟结点的情况
    Node *node;
    char ch = *str++; // 取一个字符，*str++先返回字符然后将str指针后移
    if (ch != '\0')
    {
        // 还没扫描完
        node = new Node;
        if (ch == '(')
        {
            // 创建子表
            node->tag = 1;
            node->val.sublist = createGList(str); // 递归
        }
        else if (ch == ')')
        {
            node = NULL;
        }
        else if (ch == '#')
        {
            // ‘(#)’表示空表
            node = NULL;
        }
        else
        {
            // 原子字符
            node->tag = 0;
            node->val.data = ch;
        }
    }
    else
    {
        // 扫描完毕
        node = NULL;
    }

    ch = *str++; // 取下一个字符
    if (node)
    {
        if (ch == ',')
        {
            // 兄弟结点
            node->link = createGList(str); // 递归
        }
        else
        {
            node->link = NULL;
        }
    }

    return node;
}

// 向下销毁广义表
void clear(Node *head)
{
    if (head == NULL)
        return;

    Node *sub = head->val.sublist;
    while (sub)
    {
        if (sub->tag == 0)
        {
            // 原子结点
            Node *temp = sub->link;
            delete sub;
            sub = temp;
        }
        else
        {
            // 子表结点
            Node *temp = sub->link;
            clear(sub); // 递归向下销毁
            sub = temp;
        }
    }
    delete head;
    head = NULL;
}

// 向下递归输出
void print(Node *head)
{
    if (head == NULL)
        return;
    if (head->tag == 1)
    {
        // 子表
        std::cout << '(';

        if (head->val.sublist == NULL)
        {
            std::cout << '#';
        }
        else
        {
            print(head->val.sublist); // 递归，输出子表
        }

        std::cout << ")";
    }
    else
    {
        std::cout << head->val.data;
    }

    // 输出兄弟结点
    if (head->link)
    {
        std::cout << ',';
        print(head->link); // 递归，输出兄弟
    }
}

// 求长度：就是第一代结点的个数，不多说了

// 求深度
int depth(Node *head)
{
    if (head == NULL)
        return 0;
    if (head->tag == 0)
        return 0;
    if (head->val.sublist == NULL)
        return 1;

    int max_depth = 0, dep;
    Node *sub = head->val.sublist;
    while (sub)
    {
        if (sub->tag == 1)
        {
            dep = depth(sub); // 递归求子表深度
            if (dep > max_depth)
            {
                max_depth = dep;
            }
        }
        sub = sub->link;
    }
    return max_depth + 1;
}

// 求原子个数
size_t atomSize(Node *head)
{
    if (head == NULL)
        return 0;
    if (head->tag == 0)
        return 1;
    if (head->val.sublist == NULL)
        return 0;

    size_t count = 0;
    Node *sub = head->val.sublist;
    while (sub)
    {
        if (sub->tag == 0)
        {
            count++;
        }
        else
        {
            count += atomSize(sub);
        }
        sub = sub->link;
    }
    return count;
}

// 判断相同
bool isSame(Node *head1, Node *head2)
{
    // 处理空指针情况
    if (!head1 || !head2)
        return head1 == head2; // 都为nullptr才返回true

    // 类型不同直接返回false
    if (head1->tag != head2->tag)
        return false;

    // 原子节点比较数据
    if (head1->tag == 0)
        return head1->val.data == head2->val.data;

    // 子表节点处理
    Node *p1 = head1->val.sublist;
    Node *p2 = head2->val.sublist;

    while (p1 && p2)
    {
        if (!isSame(p1, p2)) // 递归比较每个元素
            return false;
        p1 = p1->link;
        p2 = p2->link;
    }

    // 必须同时遍历完所有兄弟节点
    return p1 == nullptr && p2 == nullptr;
}

int main()
{
    const char *gStr = "(a,(b,c,d,(e,f)),(#))";
    Node *glist = createGList(gStr);
    print(glist);

    return 0;
}

// ‘#’的意思：父亲结点father是tag=1,且father->val.sublist=NULL;
// head
//  |
//  a -- @ -- @
//       |    |
//       |    #
//       b -- c -- d