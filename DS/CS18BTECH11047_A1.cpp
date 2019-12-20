/*
Please refer to readme.md for instructions on usage of certain functions.
*/

#include <iostream>
#include <sstream>
#include <ctype.h>
using namespace std;

struct Node {
    char ch;
    int count;
    Node *next;
};

struct alpha {
    char ch;
    int count;
    int visited;
};

Node* insert(Node **head, Node *curr, char c) {
    if(curr == NULL) {
        Node *newnode = new Node;
        newnode -> ch = c;
        newnode -> next = NULL;
        newnode -> count = 1;
        curr = newnode;
        *head = newnode;
        return curr;
    }
    else if (curr -> ch == c) {
        curr -> count++;
        return curr;
    }
    else {
        Node *newnode = new Node;
        newnode -> ch = c;
        newnode -> next = NULL;
        newnode -> count = 1;
        curr -> next = newnode;
        curr = newnode;
        return curr;
    }
}

void store(string s, Node **head, Node **tail) {
    for(int i = 0;i < s.length();i++) {
        *tail = insert(head, *tail, toupper(s[i]));
    }
}

void build(Node *head, alpha alph[]) {
    Node *newnode = new Node;
    newnode = head;
    for(int i = 0;i < 26;i++) {
        alph[i].count = 0;
    }
    while(newnode != NULL) {
        char c = newnode -> ch;
        alph[c - 65].ch = c;
        alph[c - 65].count += newnode -> count;
        alph[c - 65].visited = 0;
        newnode = newnode -> next;
    }
}

Node* remove(Node *head, int t, alpha alph[]) {
    Node *newnode = new Node;
    newnode = head;
    while(newnode != NULL) {
        if(newnode -> count > t) {
            newnode -> count = t;
            alph[newnode -> ch - 65].count = t;
        }
        newnode = newnode -> next;
    }
    // print(head, alph);
    return head;
}

void printlist(Node *head) {
    Node *newnode = new Node;
    newnode = head;
    while(newnode != NULL) {
        for(int i = 0;i < newnode -> count;i++) {
            cout << newnode -> ch;
        }
        
        newnode = newnode -> next;
    }
    cout << endl;
}


void print(Node *head, alpha alph[]) {
    Node *newnode = new Node;
    newnode = head;
    alpha q[26];
    for(int i = 0;i < 26;i++) {
        q[i] = alph[i];
    }
    while(newnode != NULL) {
        if(q[newnode -> ch - 65].visited == 0) {
            cout << newnode -> ch << " " << q[newnode -> ch - 65].count << " ";
            q[newnode -> ch - 65].visited = 1;
        }
        newnode = newnode -> next;
    }

    cout << endl;
}

void sortcount(alpha alph[]) {
    alpha q[26];
    for(int i = 0;i < 26;i++) {
        q[i] = alph[i];
    }

    for(int j = 0;j < 26;j++) {
        int maxi = 0;
        for(int i = 1;i < 26;i++) {
            if(q[i].count > q[maxi].count) maxi = i;
        }
        if(q[maxi].count > 0) {
            cout << q[maxi].ch;
            q[maxi].count = -1;
        }
        
        
    }
    
    cout << endl;
}

int main() {

    Node *head, *tail;
    head = new Node;
    tail = new Node;
    head = tail = NULL;
    alpha alph[26];

    string str;
    getline(cin, str);
    string f;
    while(getline(cin, f)) {
        if(f.length() == 0)
            break;
        istringstream ss(f);
        string q;
        int a;
        ss >> q;
        if(q[0] == 'S' || q[0] == 's') {
            store(str, &head, &tail);
            build(head, alph);
            cout << head -> ch << " " << tail -> ch << endl;
        } else if (q[0] == 'P' || q[0] == 'p') {
            if(head == NULL) cout << "No string stored, call store first." << endl;
            else print(head, alph);
        } else if (q[0] == 'A' || q[0] == 'a'){
            if(head == NULL) cout << "No string stored, call store first." << endl;
            else sortcount(alph);
        } else if (q[0] == 'R' || q[0] == 'r') {
            if(head == NULL) cout << "No string stored, call store first." << endl;
            else {
                Node *temp = new Node;
                ss >> a;
                temp = remove(head, a, alph);
                printlist(temp);
                build(head, alph);
            }
        }
    }

    return 0;
}