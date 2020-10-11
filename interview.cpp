#include
<iostream>
using namespace std;

#typedef int Rank;
#define ListNodePosi(T) listNode<T>*
template <typename T> struct ListNode{
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ;
    ListNode() {}
    ListNode( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        :data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
}
template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x; pred = x;
    return x;
}
template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x; succ = x;
    return x;
}
template <typename T> class <T> List
{
private:
    int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;
protected:
    void init();
public:
    List() {init();}
    List( List<T> const& L);
    ~List();
    int insertA(<T> const& e);
    remove(ListNodePosi<T> p);
    search(Rank e);
}
template <typename T>
void List<T>::init()//初始化
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->succ = NULL; trailer->pred = header;
    _size = 0;
}
template <typename T>List<T>::~List()//析构
{
    int oldsize = _size;
    while (0 < _size) remove(header->succ);
    delete header;
    delete trailer;
}
template <typename T>
T& List<T>::operator[] (Rank r) const//重载[]运算符
{
    ListNodePosi(T) p = first();
    while (0 < r--) p = p->succ;
    return p->data;
}
template <typename T>
ListNodePosi(T) List<T>::insertA (ListNodePosi(T) p, T const& e)//后插入
{
    _size++; return p->insertAsSucc(e);
}

template <typename T> T List<T>::remove(ListNodePosi(T) p)//删除
{
    T e = p->data;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    delete p; _size--;
    return e;
}

int main()
{
    sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, ID;
    cin >> n >> m;
    List<int> L;
    ListNodePosi(int) pos = new ListNode<int>;
    for (i = 0; i < n; i++)
    {
        cin >> ID;
        pos = L.insertA(pos, ID);
        
    }
    for (i = 0; i < n; i++)
        cout << L.remove(t--);
    return 0;
}
