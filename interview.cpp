
#include<iostream>
using namespace std;


#define ListNodePosi(T) ListNode<T>*
template <typename T> struct ListNode {
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ;
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        :data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};
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

template <typename T> class List
{
private:
    int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;
protected:
    void init();
public:
    List() { init(); }
    ~List();
    ListNodePosi(T) first() const { return header->succ; }
    ListNodePosi(T) last() const { return trailer->pred; }
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
    T remove(ListNodePosi(T) &p);
};

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
ListNodePosi(T) List<T>::insertA (ListNodePosi(T) p, T const& e)//后插入
{
    _size++; return p->insertAsSucc(e);
}

template <typename T> 
T List<T>::remove(ListNodePosi(T) &p)//删除
{
    T e = p->data;
    ListNodePosi(T) temp = p;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    p = p->pred;
    delete temp; _size--;
    return e;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, ID;
    int temp = -2, insertPosi = -1;
    cin >> n >> m;
    List<int> L;
    ListNodePosi(int) pos = L.last();
    //cin >> ID;
    //pos = L.insertA(pos, ID);
    for (int i = 0; i < n; i++)
    {
        if(temp < insertPosi - 1)
            for(int j = 0; j < insertPosi - 1 - temp; j++)
                pos = pos->succ;
        else if(temp >= insertPosi)
            for(int j = 0; j < temp - insertPosi + 1; j++)
                pos = pos->pred;  
        cin >> ID;
        pos = L.insertA(pos, ID);
        temp = insertPosi;
        insertPosi = (temp + m) % (i + 1);
    }
    while(n--){
        if (pos->pred == NULL)
            pos = L.last();
        cout << L.remove(pos) << ' ';

    }
        
    return 0;
}