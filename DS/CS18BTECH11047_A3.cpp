/*
Please refer to readme.md attached with the files for this question.
*/

#include <iostream>
#include <sstream>

using namespace std;

struct tonode {
        int tovertex;
        int weight;
        tonode *next;
};

class graph {
        
        public:
                tonode **list;
                int *matrix;
                int number;
                graph(int n) {
                        number = n;
                        list = (tonode**)malloc(n * sizeof(tonode*));
                        matrix = (int*)malloc(n * n * sizeof(int));

                        for(int i = 0;i < n;i++) {
                                list[i] = new tonode;
                                list[i] -> next = NULL;
                        }
                        for(int i = 0;i < n * n;i++) {
                                matrix[i] = -1;
                        }
                }

                void insert(int e1, int e2, int w) {
                        tonode *newnode = new tonode;
                        newnode -> tovertex = e2;
                        newnode -> weight = w;
                        newnode -> next = NULL;

                        if(list[e1] -> next == NULL) {
                                list[e1] -> next = newnode;
                        } else {
                                tonode *temp = new tonode;
                                temp = list[e1];
                                while(temp -> next != NULL) {
                                        // newnode = newnode -> next;
                                        temp = temp -> next;
                                }
                                temp -> next = newnode;
                        }

                        matrix[e1 * number + e2] = w;
                }

                int givedge(int e1, int e2) {
                        return matrix[e1 * number + e2];
                }

                void neighbors(int a) {
                        tonode *temp = new tonode;
                        temp = list[a] -> next;
                        while(temp != NULL) {
                                cout << temp -> tovertex << " ";
                                temp = temp -> next;
                        }
                        cout << endl;
                }

                bool edgexist(int a, int b) {
                        if (matrix[a * number + b] != -1) return true;
                        else return false;
                }
};

int main() {
        int n;
        string s;
        getline(cin ,s);
        istringstream ss(s);
        ss >> n;
        graph g(n);
        while(getline(cin, s)) {
                if(s.length() == 0)
                        break;
                istringstream ss(s);
                char q;
                int e1, e2, w;
                ss >> q;
                switch(q) {
                        case 'E' : case 'e' :
                                ss >> e1 >> e2 >> w;
                                g.insert(e1, e2, w);
                                g.insert(e2, e1, w);
                                break;
                        case 'N' : case 'n' :
                                ss >> e1;
                                g.neighbors(e1);
                                break;
                        case 'W' : case 'w' :
                                ss >> e1 >> e2;
                                cout << g.givedge(e1, e2) << endl;
                                break;
                        case 'C' : case 'c' :
                                ss >> e1 >> e2;
                                if(g.edgexist(e1, e2) == 1) cout << "YES" << endl;
                                else cout << "NO" << endl;
                                break;
                        case 'V' : case 'v' :
                                ss >> e1;
                                if(e1 >= n) cout << "NO" << endl;
                                else cout << "YES" << endl;
                                break;
                        case 'A' : case 'a' :
                                for(int i = 0;i < n;i++) {
                                        cout << i << " ";
                                }
                                cout << endl;
                                break;
                        default:
                                break;
                }
        }

}