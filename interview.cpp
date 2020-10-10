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
void List<T>::init()
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = NULL;
    trailer->succ = NULL; trailer->pred = header;
    _size = 0;
}
template <typename T>
T& List<T>::operator[] (Rank r) const
{
    ListNodePosi(T) p = first();
    while (0 < r--) p = p->succ;
    return p->data;
}
template <typename T>
ListNodePosi(T) List<T>::insertA (ListNodePosi(T) p, T const& e)
{
    _size++; return p->insertAsSucc(e);
}
// template <typename T>
// ListNodePosi(T) List<T>::insertA ( ListNodePosi(T) p, T const& e)
// {
//     _size++; return p->insertAsSucc(e);
// }
template <typename T>T List<T>::remove(ListNodePosi(T) p)
{
    T e = p->data;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    delete p; _size--;
    return e;
}
ListNodePosi(T) template <typename T> List<T>::search(Rank e)
{

}
template <typename T>List<T>::~List()
{
    int oldsize = _size;
    while (0 < _size) remove(header->succ);
    delete header;
    delete trailer;
}
int main()
{
    sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, t;
    t = 0;
    cin >> n;
    List<int> L;
    for (i = 0; i < n; i++)
    {
        cin >> m;
        t = L.insertA((m % i + t) % i, m);
    }
    for (i = 0; i < n; i++)
        cout << L.remove(t--);
    return 0;
}