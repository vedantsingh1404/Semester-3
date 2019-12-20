#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

struct edge {
        int e1;
        int e2;
        int weight;
};

struct toedge {
        int tovertex;
        int weight;
};

void components(vector <int> undir[], int n) {
        int set[n];
        int distinct[n];
        for(int i = 0;i < n;i++) {
                distinct[i] = 0;
                set[i] = i;
        }
        for(int i = 0;i < n;i++) {
                int min = set[i];
                for(int j = 0;j < undir[i].size();j++) {
                        min = set[undir[i][j]] < min ? set[undir[i][j]] : min; 
                }
                for(int j = 0;j < undir[i].size();j++) {
                        set[undir[i][j]] = min;
                }
                set[i] = min;

        }
        for(int i = 0;i < n;i++) {
                distinct[set[i]] = 1;

        }
        int count = 0;
        for(int i = 0;i < n;i++) {
                count += distinct[i];
        }
        cout << count << " components" << endl;
        for(int i = 0;i < n;i++) {
                if(distinct[i] == 1) {
                        for(int j = 0;j < n;j++) {
                                if(set[j] == i) {
                                        cout << j << " " ;
                                }
                        }
                        cout << endl;
                }
                
        }
}

void dijk(int source, vector< pair<int, int> > dir[], int n) {
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int,int>, vector< pair<int, int> >, greater<pair<int,int> > > q;
        dist[source] = 0; int count=1;
        q.push(make_pair(0, source));

        while(!q.empty()) {

            int u = q.top().second;
            q.pop();

            for(vector<pair<int, int> >::iterator it = dir[u].begin(); it!= dir[u].end(); it++) {
                
                if(dist[(*it).first] > dist[u] + (*it).second) {
                    dist[(*it).first] = dist[u] + (*it).second;
                    q.push(make_pair(dist[(*it).first],(*it).first));

                }
            }
        }
        int i = 0;
        while(i < n) {
                if(dist[i] != INT_MAX) {
                        cout << source << " " << i << " " << dist[i] << endl;
                }
                i++;
        }
}

int main() {
        int n;
        string s;
        getline(cin, s);
        istringstream ss(s);
        ss >> n;
        vector <edge> e;
        vector < pair<int, int> > dir[n];
        vector <int> undir[n];
        while(getline(cin, s)) {
                if(s.length() == 0)
                        break;
                istringstream ss(s);
                string q;
                int a;
                ss >> q;
                if(q[0] == 'E' || q[0] == 'e') {
                        edge t;
                        ss >> t.e1 >> t.e2 >> t.weight;
                        undir[t.e1].push_back(t.e2);
                        undir[t.e2].push_back(t.e1);
                        dir[t.e1].push_back(make_pair(t.e2, t.weight));
                        e.push_back(t);
                } else if(q[0] == 'F' || q[0] == 'f') {
                        components(undir, n);
                } else if(q[0] == 'S' || q[0] == 's') {
                        ss >> a;
                        dijk(a, dir, n);
                }
        }
        return 0;
}