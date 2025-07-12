#include<iostream>
#include<vector>
#include<string>
using namespace std;
// 线索二叉树
class ThreadBTree
{
public:
    // 线索二叉树结点
    struct TNode
    {
        char data;
        TNode *lchild, *rchild;
        int ltag, rtag; // ltag=0指向左孩子，1指向前驱结点；rtag=0指向右孩子，1指向后继结点
        TNode(char dt = '\0') : data(dt), lchild(NULL), rchild(NULL) {}
    };
    // 中序线索二叉树的建立
    TNode *pre; // 临时头结点
    void Thread(TNode *&root)
    {
        if (!root)
            return;
            
        //先序：ifif->Thread->Thread
        //中序：Thread->ifif->Thread
        //后序：Thread->Thread->ifif

        Thread(root->lchild); // 1. 递归线索化左子树

        // 2. 处理当前结点的前驱线索
        if (!root->lchild)
        {                       // 如果左孩子为空
            root->lchild = pre; // 左指针指向前驱
            root->ltag = 1;     // 标记为线索
        }
        else
            root->ltag = 0; // 否则标记为孩子

        // 3. 处理前驱结点的后继线索
        if (!pre->rchild)
        {                       // 如果前驱的右孩子为空
            pre->rchild = root; // 前驱的右指针指向当前结点(后继)
            pre->rtag = 1;      // 标记为线索
        }
        else
            pre->rtag = 0; // 否则标记为孩子

        //容易忘
        pre = root; // 更新前驱为当前结点

        Thread(root->rchild); // 4. 递归线索化右子树
    }
    // 中序线索化二叉树
    TNode *createThread(TNode *root)
    {
        //三序线索化二叉树的代码完全一样
        TNode *head = new TNode; // 创建头结点
        head->ltag = 0;
        head->rtag = 1;
        head->rchild = head; // 右指针初始指向自己

        if (!root)
            head->lchild = head; // 空树时左指针也指向自己
        else
        {
            head->lchild = root; // 头结点的左指针指向根结点
            pre = head;          // 初始化前驱为头结点
            Thread(root);        // 线索化二叉树

            // 处理最后一个结点
            pre->rchild = head; // 最后一个结点的后继指向头结点
            pre->rtag = 1;
            head->rchild = pre; // 头结点的右指针指向最后一个结点
        }
        return head;
    }
    // 遍历线索二叉树
    void traval(TNode *head) // tb是中序线索二叉树的头结点
    {
        TNode *curr = head->lchild;
        while (curr != head)
        {
            while (curr->ltag == 0)
                curr = curr->lchild;
            std::cout << curr->data << ' ';
            while (curr->rtag == 1 && curr->rchild != head)
            {
                curr = curr->rchild;
                std::cout << curr->data << ' ';
            }
            curr = curr->rchild;
        }
    }
};
