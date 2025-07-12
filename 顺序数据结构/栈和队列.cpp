#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include<cmath>
using namespace std;
#define Find find;
//栈
class Stack
{
private:
    static const int MAX_SIZE = 100; // 定义栈的最大容量
    int stack[MAX_SIZE];             // 使用数组存储栈元素
    int top;                         // 栈顶指针

public:
    // 构造函数，初始化栈
    Stack() : top(-1) {}

    // 将元素压入栈顶
    void push(int item)
    {
        if (top >= MAX_SIZE - 1)
        {
            throw overflow_error("Stack overflow");
        }
        stack[++top] = item;
    }

    // 弹出栈顶元素
    int pop()
    {
        if (is_empty())
        {
            throw underflow_error("Stack underflow");
        }
        return stack[top--];
    }

    // 查看栈顶元素，但不弹出
    int peek()
    {
        if (is_empty())
        {
            throw underflow_error("Stack is empty");
        }
        return stack[top];
    }

    // 判断栈是否为空
    bool is_empty()
    {
        return top == -1;
    }

    // 返回栈中元素的个数
    int size()
    {
        return top + 1;
    }

    // 打印栈的内容
    void print()
    {
        cout << "Stack: ";
        for (int i = 0; i <= top; i++)
        {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};
//队列
class Queue
{
private:
    static const int MAX_SIZE = 100; // 定义队列的最大容量
    int queue[MAX_SIZE];             // 使用数组存储队列元素
    int front;                       // 队列头部指针
    int rear;                        // 队列尾部指针

public:
    // 构造函数，初始化队列
    Queue() : front(-1), rear(-1) {}

    // 将元素加入队列尾部
    void enqueue(int item)
    {
        if (is_full())
        {
            throw overflow_error("Queue is full");
        }
        if (is_empty())
        {
            front = 0; // 如果队列为空，初始化 front
        }
        queue[++rear] = item;
    }

    // 移除并返回队列头部的元素
    int dequeue()
    {
        if (is_empty())
        {
            throw underflow_error("Queue is empty");
        }
        int item = queue[front];
        if (front == rear)
        {
            // 如果队列中只有一个元素，重置队列
            front = rear = -1;
        }
        else
        {
            front++;
        }
        return item;
    }

    // 查看队列头部的元素，但不移除
    int _front_()
    {
        if (is_empty())
        {
            throw underflow_error("Queue is empty");
        }
        return queue[front];
    }

    // 判断队列是否为空
    bool is_empty()
    {
        return front == -1 && rear == -1;
    }

    // 判断队列是否已满
    bool is_full()
    {
        return rear == MAX_SIZE - 1;
    }

    // 返回队列中元素的个数
    int size()
    {
        if (is_empty())
        {
            return 0;
        }
        return rear - front + 1;
    }

    // 打印队列的内容
    void print()
    {
        if (is_empty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue: ";
        for (int i = front; i <= rear; i++)
        {
            cout << queue[i] << " ";
        }
        cout << endl;
    }
};
//循环队列
class RoundQueue
{
private:
    static const int MAX_SIZE = 100; // 队列的最大容量
    int queue[MAX_SIZE];             // 存储队列元素的数组
    int front;                       // 队头指针
    int rear;                        // 队尾指针

public:
    RoundQueue() : front(-1), rear(-1) {}

    // 判空
    bool isEmpty() const
    {
        return front == -1 && rear == -1;
    }
    // 判满
    bool isFull() const
    {
        return (rear + 1) % MAX_SIZE == front;
    }
    // 入队
    bool enqueue(int value)
    {
        if (isFull())
        {
            return false; // 队列已满，无法入队
        }
        if (isEmpty())
        {
            front = rear = 0; // 队列为空时初始化队头和队尾
        }
        else
        {
            rear = (rear + 1) % MAX_SIZE; // 队尾指针循环移动
        }
        queue[rear] = value; // 将元素添加到队尾
        return true;
    }

    // 出队
    bool dequeue()
    {
        if (isEmpty())
        {
            return false; // 队列为空，无法出队
        }
        if (front == rear)
        {
            front = rear = -1; // 队列只有一个元素，出队后队列为空
        }
        else
        {
            front = (front + 1) % MAX_SIZE; // 队头指针循环移动
        }
        return true;
    }

    // 获取队头元素
    int _front_() const
    {
        if (isEmpty())
        {
            return 0; // 队列为空，无法获取队头元素
        }
        return queue[front];
    }

    // 获取队列大小
    int size() const
    {
        if (isEmpty())
        {
            return 0;
        }
        if (front <= rear)
        {
            return rear - front + 1;
        }
        else
        {
            return MAX_SIZE - front + rear + 1;
        }
    }
    // 打印
    void print() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << "Queue elements: ";
        int index = front;  // 从队头开始遍历
        for (int i = 0; i < size(); i++)
        {
            cout << queue[index] << " ";
            index = (index + 1) % MAX_SIZE; // 循环移动指针
        }
        cout << endl;
    }
};
// 栈的算法

// 计算后缀表达式
string calculatePostExpr(string postExpr)
{
    stack<string> stk;
    string ch;
    stringstream ss(postExpr);
    while (ss >> ch)
    {
        if (ch == "+" || ch == "-" || ch == "*" || ch == "/"||ch=="^")
        {
            // op,弹出top和subtop,按照“次顶op顶”计算并再次压栈
            double top = stod(stk.top());
            stk.pop();
            double subtop = stod(stk.top());
            stk.pop();

            double newVal;
            if (ch == "+")
                newVal = subtop + top;
            else if (ch == "-")
                newVal = subtop - top;
            else if (ch == "*")
                newVal = subtop * top;
            else if (ch == "/")
                newVal = subtop * 1.0 / top;
            else if(ch=="^")
                newVal = pow(subtop, top);

            stk.push(to_string(newVal));
        }
        else
        {
            // 数字
            stk.push((string)ch);
        }
    }
    return stk.top();
}
// 中缀表达式转换为后缀表达式
string turnIntoPostExpr(string midExpr)
{
    stack<string> stk;
    stringstream ss(midExpr);
    string ch;
    string res = "";

    // 定义运算符优先级
    map<string, int> precedence = {
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2},
        {"^",3}};

    while (ss >> ch)
    {
        if (ch == "(")
            stk.push(ch);
        else if (ch == ")")
        {
            // 依次将top弹出放入Res直到遇到左括号,弹出左括号
            while (!stk.empty() && stk.top() != "(")
            {
                res += stk.top() + " ";
                stk.pop();
            }
            if (!stk.empty() && stk.top() == "(")
                stk.pop();
        }
        else if (ch == "+" || ch == "-" || ch == "*" || ch == "/"||ch=="^")
        {
            //op和stack.top比较优先级，一直弹出栈顶存入Res，直到遇到"("或op>top，最后将op压栈
            while (!stk.empty() && stk.top() != "(" && precedence[ch] <= precedence[stk.top()])
            {
                res += stk.top() + " ";
                stk.pop();
            }
            stk.push(ch);
        }
        else
            res += ch + " "; // 数字直接存入结果字符串
    }

    while (!stk.empty())
    {
        res += stk.top() + " ";
        stk.pop();
    }

    // 去掉最后一个空格
    if (!res.empty() && res.back() == ' ')
        res.pop_back();

    return res;
}
//计算中缀表达式
class MidFixSolution
{
    //整个字符串是有的连起来有的有空格的，数字有多位，数字还可以是字母（按照ASCII），数字还可能是负数。
public:
    bool inOPs(string op)
    {
        if (op == "+" || op == "-" || op == "*" || op == "/")
            return true;
        else
            return false;
    }

    string deleteSpace(string s)
    {
        string result = "";
        for (char ch : s)
        {
            if (isspace(ch))
                continue;
            result.push_back(ch);
        }
        return result;
    }

    string turnAlphaIntoNum(string s)
    {
        string temp;
        int i = 0;
        while (i < s.size())
        {
            if (isalpha(s[i]))
            {
                int num = s[i];//字符隐式转换为int
                string str = std::to_string(num);
                str.append(" ");
                temp.append(str);
                i++;
            }
            else if (inOPs(string(1, s[i])) || s[i] == '(' || s[i] == ')')
            {
                string op = string(1, s[i]);
                op.append(" ");
                temp.append(op);
                i++;
            }
            else
            {
                int j = i;
                // 判断是否为负数
                //负数的判断：如果在字符串头部，或者 负号前面是'('或者运算符
                if (s[j] == '-' && (j == 0 || s[j - 1] == '(' || inOPs(string(1, s[j - 1]))))
                {
                    j++; // 跳过负号
                }
                // 解析多位数字
                while (j < s.size() && s[j] >= '0' && s[j] <= '9')
                    j++;
                if (j == i)
                {
                    string num(1, s[i]);
                    num.append(" ");
                    temp.append(num);
                }
                else
                {
                    string num = s.substr(i, j - i);
                    num.append(" ");
                    temp.append(num);
                }
                i = j;
            }
        }
        return temp;
    }

    string turnIntoPost(string mid)
    {
        stack<string> stk;
        string result = "";
        std::stringstream ss(mid);
        string ch;
        map<string, int> precedence = {
            {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}};
        while (ss >> ch)
        {
            if (inOPs(ch))
            {
                while (!stk.empty() && precedence[ch] <= precedence[stk.top()])
                {
                    result.append(stk.top());
                    result.append(" ");
                    stk.pop();
                }
                stk.push(ch);
            }
            else if (ch == "(")
            {
                stk.push(ch);
            }
            else if (ch == ")")
            {
                while (!stk.empty() && stk.top() != "(")
                {
                    result.append(stk.top());
                    result.append(" ");
                    stk.pop();
                }
                if (!stk.empty() && stk.top() == "(")
                    stk.pop();
            }
            else
            {
                result.append(ch);
                result.append(" ");
            }
        }
        while (!stk.empty())
        {
            result.append(stk.top());
            result.append(" ");
            stk.pop();
        }
        return result;
    }

    int calculate_(string s)
    {
        string delSpace = deleteSpace(s);
        string turnAlpha = turnAlphaIntoNum(delSpace);
        string postfix = turnIntoPost(turnAlpha);
        stack<string> stk;
        stringstream ss(postfix);
        string ch;
        while (ss >> ch)
        {
            if (inOPs(ch))
            {
                int top = stoi(stk.top());
                stk.pop();
                int subtop = stoi(stk.top());
                stk.pop();
                int res;
                if (ch == "+")
                    res = subtop + top;
                else if (ch == "-")
                    res = subtop - top;
                else if (ch == "*")
                    res = subtop * top;
                else if (ch == "/")
                    res = subtop / top;
                stk.push(to_string(res));
            }
            else
            {
                stk.push(ch);
            }
        }
        return stoi(stk.top());
    }

    void pmain()
    {
        int dataNum;
        string datastr;
        getline(cin, datastr);
        dataNum = stoi(datastr);
        vector<pair<string, string>> vec;
        for (int i = 0; i < dataNum; i++)
        {
            string fir, sec;
            getline(cin, fir);
            getline(cin, sec);
            vec.push_back({fir, sec});
        }
        for (auto pr : vec)
        {
            int fir = calculate_(pr.first), sec = calculate_(pr.second);
            string res = (fir == sec) ? "TRUE" : "FALSE";
            std::cout << res << '\n';
        }
        return;
    }
};
// 括号匹配问题
bool match(string str)
{
    stack<char> stk;
    map<char, char> matchs = {{')', '('},
                              {']', '['},
                              {'}', '{'}};
    for (char ch : str)
    {
        if (ch == '(' || ch == '[' || ch == '{')
            stk.push(ch); // 左括号直接压栈
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            // 右括号，检查栈顶是否匹配
            if (stk.empty() || stk.top() != matchs[ch])
                return false; // 不匹配直接返回
            stk.pop(); // 匹配则弹出栈顶
        }
    }
    // 如果栈为空，说明所有括号都匹配
    return stk.empty();
}

// I-O序列合法问题
bool isIOallowed(string ioSeq,int size)
{
    // 设以I和O分别表示进栈和出栈操作，栈的初态和终态均为空,称可以实现的栈操作序列为合法序列（例如IIOO为合法序列，IOOI为非法序列）。试给出区分给定序列为合法序列或非法序列的一般准则？
    //  对于序列的任意的前缀序列，O的操作数<=I的操作数，而且总的I=O，则合法
    for (int i = 0; i < size; i++)
    {
        int itimes = 0, otimes = 0;
        for (int j = 0; j <= i; j++)
        {
            if (ioSeq[j]=='I')
                itimes++;
            else
                otimes++;
        }
        if(otimes>itimes)
            return false;
        if (i == size - 1 && itimes != otimes) // 总数I=O则合法
            return false;
    }
    return true;
}

//  合并栈操作
class MergeStackSolution
{
    //  栈是一种具有后进先出的数据结构。可合并栈是支持“merge”操作的栈。三种操作的说明如下：
    //  ① push A x：将x插入栈A中。
    //  ② pop A：删除栈A的顶部元素。
    //  ③ merge A B：合并栈A和B。
    //  其中，“merge A B”操作后栈A包含A和B之前的所有元素，B变为空，新栈中的元素根据先前的进栈时间重新排列，就像在一个栈中重复"push"操作一样。给定两个可合并栈A和B，请执行上述操作。
    //  【输入形式】
    //     测试用例的第一行包含一个整数n（0<n≤10^5）表示操作个数，接下来的n行每行包含一条指令push、pop或merge，栈元素是32位整数。A和B最初都是空的，且保证不会对空栈执行pop操作。n=0表示输入结束。
    //  【输出形式】
    //     对于每个pop操作，在一行中输出对应的出栈元素。
    //  【样例输入】
    //   9
    //   push A 0
    //   push A 1
    //   push B 3
    //   pop A
    //   push A 2
    //   merge A B
    //   pop A
    //   pop A
    //   pop A
    //  【样例输出】
    //   1
    //   2
    //   3
    //   0
    //  【样例说明】
    //     测试数据的文件名为in.txt
public:
    // 定义全局的 history 记录所有元素的进栈时间
    static std::vector<int>
        history;

    // 从 history 中删除指定值
    void RemoveFromHistory(int val)
    {
        auto it = std::find(history.begin(), history.end(), val);
        if (it != history.end())
            history.erase(it);
    }

    void mergeStack()
    {
        std::stack<int> A, B;
        std::ifstream ifs("in.txt", ios::in);

        int operNum = 0;
        ifs >> operNum;
        ifs.ignore(); // 忽略换行符

        std::string oper;
        for (int i = 0; i < operNum; i++)
        {
            std::getline(ifs, oper);
            std::stringstream ss(oper);
            std::string firWord = "", secWord = "", thirdWord = "";
            ss >> firWord;

            if (firWord == "push")
            {
                ss >> secWord >> thirdWord;
                int newval = stoi(thirdWord);
                history.push_back(newval); // 登记进栈时间
                if (secWord == "A")
                    A.push(newval);
                else
                    B.push(newval);
            }
            else if (firWord == "pop")
            {
                ss >> secWord;
                if (secWord == "A")
                {
                    std::cout << A.top() << '\n';
                    RemoveFromHistory(A.top()); // 从 history 中删除
                    A.pop();
                }
                else
                {
                    std::cout << B.top() << '\n';
                    RemoveFromHistory(B.top()); // 从 history 中删除
                    B.pop();
                }
            }
            else if (firWord == "merge")
            {
                ss >> secWord >> thirdWord;
                // 将 A 和 B 的元素按进栈时间重新排列
                std::vector<int> merged;
                while (!A.empty())
                {
                    merged.push_back(A.top());
                    A.pop();
                }
                while (!B.empty())
                {
                    merged.push_back(B.top());
                    B.pop();
                }
                // 按 history 的顺序重新压入栈
                for (int val : history)
                {
                    if (std::find(merged.begin(), merged.end(), val) != merged.end())
                    {
                        if (secWord == "A")
                            A.push(val);
                        else
                            B.push(val);
                    }
                }
            }
        }
    }
};

// 队列算法

// 倒置环形队列
void reverseRQueue(RoundQueue &qu)
{
    // 使用一个临时栈 stk，先将 qu 队列中所有元素出队并将其进栈 stk, 然后清空队列，再出栈 stk 的所有元素并将其进队
    stack<int> stk;
    while (!qu.isEmpty())
    {
        stk.push(qu._front_());
        qu.dequeue();
    }
    while (!stk.empty())
    {
        qu.enqueue(stk.top());
        stk.pop();
    }
}

// 约瑟夫环
class JosephRoundSolution
{
    // 【问题描述】
    // n个人围成一个圈，按顺时针方向一次编号1、2、3、……、n，从第一个人开始顺时针方向依次报数1、2、3、……，报数m的人被淘汰，然后下一个人再从1开始报数，一直重复该过程。由于人数是有限的，因此最后一定只会剩下一个人，求这个人的编号。

    // 【输入形式】
    // 文件输入，文件名是"in.txt"
    // 输入两个整数 n,m。（均为1到500的整数）

    // 【输出形式】
    // 输出一行 n 个整数，按顺序输出每个出圈人的编号。

    // 【样例输入】
    // 10 3
    // 【样例输出】
    // 3 6 9 2 7 1 8 5 10 4
public:
    void josephRound()
    {
        ifstream ifs("in.txt", ios::in);
        if (!ifs.is_open())
        {
            cerr << "Failed to open file!" << endl;
            return;
        }

        int n, m;
        ifs >> n >> m;
        ifs.close();

        vector<int> round(n);
        for (int i = 0; i < n; ++i)
        {
            round[i] = i + 1; // 初始化编号为 1 到 n
        }

        vector<int> result;
        int curr = 0;

        while (!round.empty())
        {
            // 计算被淘汰的人的位置
            curr = (curr + m - 1) % round.size();
            result.push_back(round[curr]);
            round.erase(round.begin() + curr);
        }

        // 输出结果
        for (int i = 0; i < result.size(); ++i)
        {
            cout << result[i] << " ";
        }
        cout << endl;
    }
};

// string str = "5 2 1 6 + * + 8 2 / -";
// cout << calculatePostExpr(str);
// string midExpr = "9 + ( 3 - 1 ) * 3 + 10 / 2";
// cout << turnIntoPostExpr(midExpr);
// string str = "({[][()]}[])";
// cout << match(str);