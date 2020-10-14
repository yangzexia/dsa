#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct Node* head = NULL;

void push(int x){
    Node* temp = new Node;
    temp->data = x;
    temp->next = head;
    head = temp;
}

void pop(){
    if(head == NULL) return;
    Node* del = head;
    head = head->next;
    delete del;
}

int top(){
    if(head == NULL) return -1;
    return head->data;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    int len = 0;
    int temp;
    
    cin >> n >> m;

    int* out = new int[2*n];
    int count = 1;
    int num = 0;

    for(int i = 0; i < n; i++){
        cin >> temp;
        while (count <= n) {
            
            if (top() == temp) {
                pop();
                out[num++] = 1;
                len--;
                break;
            }
            push(count++);
            out[num++] = 0;
            len++;
            if (len > m) {
                cout << "No\n"; return 0;
            }
            if (top() == temp) {
                pop();
                out[num++] = 1;
                len--;
                break;
            }
        }

        if (count > n && top() == temp){ 
            out[num++] = 1;
            pop();
            len--;
        }
    }

 
    if (head != NULL) {
        cout << "No\n";
        return 0;
    }
    for (int i = 0; i < 2*n; i++){
        out[i] == 1 ? cout << "pop\n" : cout << "push\n";
    }
    delete[] out;
    return 0;
}