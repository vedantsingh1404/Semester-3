/*
Please refer to readme.md for instructions on usage of certain functions.
*/

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Node {
        int value;
        int rank;
        Node *parent;
};

struct edge {
        int weight;
        int end1;
        int end2;
};

class DS {
        Node** array;

        public:
                DS(int n) {
                        array = (Node**)malloc((n) * sizeof(Node*));
                        for(int i = 0;i < n;i++) {
                                array[i] = new Node;
                                makeset(i);
                        }
                }

                void makeset(int x) {
                        array[x] -> value = x;
                        array[x] -> rank = 1;
                        array[x] -> parent = NULL;
                }

                Node* findSet(int x) {
                        Node *newnode = new Node;
                        newnode = array[x];
                        while(newnode -> parent != NULL) {
                                newnode = newnode -> parent;
                        }
                        return newnode;
                }

                void uni(int x, int y) {
                        Node* node1;
                        Node* node2;
                        node1 = new Node;
                        node2 = new Node;
                        node1 = findSet(x);
                        node2 = findSet(y);
                        if(node1 == node2) return;
                        if(node1 -> rank < node2 -> rank) {
                                array[node1 -> value] -> parent = array[node2 -> value];
                                array[node2 -> value] -> rank += array[node1 -> value] -> rank;
                        } else {  
                                array[node2 -> value] -> parent = array[node1 -> value];
                                array[node1 -> value] -> rank += array[node2 -> value] -> rank;
                        }
                }
};

void sortedge(vector <edge> &e) {
        for(int i = 0;i < e.size();i++) {
                for(int j = 0;j < e.size() - 1 - i;j++) {
                        if(e[j].weight > e[j + 1].weight) {
                                edge temp;
                                temp = e[j];
                                e[j] = e[j + 1];
                                e[j + 1] = temp;
                        }
                }
        }
}

int main() {
        int n;
        string str;
        getline(cin, str);
        istringstream ss(str);
        ss >> n;
        DS ds(n);
        vector <edge> e;
        vector <edge> mst;
        while(getline(cin, str)) {
                edge t;
                if(str.length() == 0)
                        break;
                istringstream ss(str);
                char q;
                ss >> q;
                ss >> t.end1 >> t.end2 >> t.weight;
                e.push_back(t);
        }
        sortedge(e);
        for(int i = 0;i < e.size();i++){
                int e1 = e[i].end1;
                int e2 = e[i].end2;
                if(ds.findSet(e1) != ds.findSet(e2)) {
                        mst.push_back(e[i]);
                        ds.uni(e1, e2);
                }
        }

        if(mst.size() != n - 1) {
                cout << "No MST exists for the given graph." << endl;
        } else {
                cout << "W : E1 , E2" << endl;
                for(int i = 0;i < mst.size();i++) {
                        cout << mst[i].weight << " : " << mst[i].end1 << " , " << mst[i].end2 << endl;
                }
        }
}