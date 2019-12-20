#include <iostream>
#include <sstream>
using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
    Node *parent;
};

Node* init(int x) {
    Node *newnode = new Node;
    newnode -> value = x;
    newnode -> left = NULL;
    newnode -> right = NULL;
    newnode -> parent = NULL;

    return newnode;
}


Node* search(Node *root, int value) {
    if(root == NULL) {
        return NULL;
    }
    else if(root -> value == value) return root;
    else {
        if(value < root -> value) {
            return search(root -> left, value);
        }
        else {
            return search(root -> right, value);
        }
    }
}

void insert(Node *root, int value, Node *parent) {
    if(root == NULL) {
        Node *node = new Node;
        node = init(value);
        node -> parent = parent;
        if(value < parent -> value) parent -> left = node;
        else parent -> right = node;
        root = node;
    }
    else {
        if(value < root -> value) {
            insert(root -> left, value, root);
        }
        else {
            insert(root -> right, value, root);
        }
    }
}

int succ(Node *root, int a) {
    Node *node = new Node;
    Node *curr = new Node;
    curr = search(root, a);
    if(curr -> right == NULL) {
        node = curr;
        while(node != NULL) {
            if(node -> value > curr -> value) {
                return node -> value;
            }
            node = node -> parent;
        }
        if(node == NULL) return -1;
        else return node -> value;
    }
    else {
        node = curr -> right;
        while(node -> left != NULL) {
            node = node -> left;
        }
        return node -> value;
    }
}

int pred(Node *root, int a) {
    Node *node = new Node;
    Node *curr = new Node;
    curr = search(root, a);
    if(curr -> left == NULL) {
        node = curr;
        while(node != NULL) {
            if(node -> value < curr -> value) {
                return node -> value;
            }
            node = node -> parent;
        }
        if (node == NULL) return -1;
        else return node -> value;
    }
    else {
        node = curr -> left;
        while(node -> right != NULL) {
            node = node -> right;
        }
        return node -> value;
    }
}

int height(Node *root, Node *node) {
    int h = 0;
    Node *newnode = new Node;
    newnode = node;
    while(newnode -> parent != NULL) {
        h++;
        newnode = newnode -> parent;
    }

    return h;
}

int isancestor(Node *root, Node *anc, Node *dec) {
    int flag = 0;
    Node *newnode = new Node;
    newnode = dec;
    while(newnode != NULL) {
        if(newnode == anc) flag = 1;
        newnode = newnode -> parent;
    }

    return flag;
}

int lca(Node *root, int a, int b) {
    Node *node1 = new Node;
    Node *node2 = new Node;
    node1 = search(root, a);
    node2 = search(root, b);
    int h1 = height(root, node1);
    int h2 = height(root, node2);
    Node *newnode = new Node;
    if(h1 <= h2) {
        newnode = node1;
        while(newnode != NULL) {
            if(isancestor(root, newnode, node2)) return newnode -> value;
            newnode = newnode -> parent;
        }
    }
    else {
        return lca(root, b, a);
    }
}

int mini(int a, Node *root) {
    Node *temp = search(root, a);
    if(temp -> left == NULL) {
        return temp -> value;
    }
    else {
        return mini(temp -> left -> value, root);
    }
}

int maxi(int a, Node *root) {
    Node *temp = search(root, a);
    if(temp -> right == NULL) {
        return temp -> value;
    }
    else {
        return maxi(temp -> right -> value, root);
    }
}

Node* input(string s, Node *root) {
    istringstream ss(s);
    int k;
    ss >> k;
    root = init(k);
    while(ss >> k) {
        insert(root, k, NULL);
    }
    return root;
}

int main() {

    Node *root = new Node;
    string str;
    getline(cin, str);
    root = input(str, root);
    while(getline(cin, str)) {
        if(str.length() == 0)
            break;
        istringstream ss(str);
        char q;
        int a, b;
        ss >> q >> a;
        switch (q) {
            case 'M' : case 'm' :
                cout << mini(a, root) << " " << maxi(a, root) << endl;
                break;
            case 'P' : case 'p' :
                cout << pred(root, a) << endl;
                break;
            case 'S' : case 's' :
                cout << succ(root, a) << endl;
                break;
            case 'C' : case 'c' :
                ss >> b;
                cout << lca(root, a, b) << endl;
        }
    }
    return 0;
}