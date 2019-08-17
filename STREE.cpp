
#include <bits/stdc++.h>
using namespace std;

struct graph {
    int v;
    int cost;
    vector< vector< pair<int, int> > > list;
};

vector<graph> st;

// INPUT THE GRAPH FROM THE USER IN ADJACENCY LIST FORM

void InputGraph(graph &G) {
    int i, j, n, v;
    cout<<"Please, Enter the number of Vertices in the Graph : ";
        cin>>G.v;
    G.cost = 0;
    for(i = 0; i < G.v; i++) {
        vector< pair<int,int> > t ;
        G.list.push_back(t);
    }
    cout<<"\nEnter, the Adjacency List-";
    for(i = 0; i < G.v; i++) {
        cout<<"\nEnter the number of adjacent Vertices of "<<i<<" : ";
            cin>>n;
        for(j = 0; j < n; j++) {
            pair<int,int> p;
            cout<<"Adjacent Vertex "<<j+1<<" : ";
                cin>>p.first;
            cout<<"Corresponding Edge Weight : ";
                cin>>p.second;
            G.list[i].push_back(p);
        }
    }
}

// DISPLAYING THE GRAPH IN THE FORM OF ADJACENCY LIST

void Display(graph G) {
    int i, j;
    for(i = 0; i < G.v; i++) {
        cout<<"\n"<<i<<" : ";
        for(j = 0; j < G.list[i].size(); j++) {
            cout<<"("<<i<<","<<G.list[i][j].first<<"->"<<G.list[i][j].second<<") -> ";
        }
    }
}

void func(graph &G, map<int,int> &mp, graph &temp, int i) {
    /*
    *** Base condition when all vertices are covered
    *** and Checking whether this tree has already been added or not
    */
    if(mp.size() == G.v) {
        bool flag;
        int x, y, z;
        for(x = 0; x < temp.v; x++) {
            sort(temp.list[x].begin() , temp.list[x].end());
        }

        // Looping all Trees and checking for repeatition of tree
        for(z = st.size()-1; z >= 0; z--) {
            flag = false;
            for(x=0; x < temp.v; x++){
                for(y=0; y < temp.list[x].size(); y++){
                    if(temp.list[x][y] != st[z].list[x][y]){
                        flag = true;
                        break;
                    }
                }
                if(flag){
                    break;
                }
            }
            if(!flag){
                return;
            }
        }
        temp.cost = 0;
        for(x=0; x < temp.v; x++){
            for(y=0; y < temp.list[x].size(); y++){
                temp.cost += temp.list[x][y].second;
            }
        }
        temp.cost /= 2;

        st.push_back(temp);
        return;
    }
    /*
    *** Else add adjacent vertex to map and call recursion for it
    */

    for(int j = 0; j < G.list[i].size(); j++) {
        if(mp.find( G.list[i][j].first ) != mp.end()) {
            continue;
        }
        pair<int,int> t;

        // These 3 lines add G.list[i][j].first to the temp graph and map
        mp[ G.list[i][j].first ] = G.list[i][j].first ;
        temp.list[i].push_back(G.list[i][j]);
        t.first = i;
        t.second = G.list[i][j].second;
        temp.list[ G.list[i][j].first ].push_back(t);

        func(G, mp, temp, G.list[i][j].first );

        func(G, mp, temp, i);

        // Erasing the element from temp graph and map
        mp.erase( mp.find( G.list[i][j].first ) );
        vector< pair<int,int> > :: iterator it = temp.list[i].begin();
        for(it; it != temp.list[i].end(); it++) {
            if(it->first == G.list[i][j].first) {
                temp.list[i].erase(it);
                break;
            }
        }
        it = temp.list[ G.list[i][j].first ].begin();
        for(it; it != temp.list[ G.list[i][j].first ].end(); it++) {
            if(it->first == i) {
                temp.list[ G.list[i][j].first ].erase(it);
                break;
            }
        }
    }
}


// Function to generate all spanning trees

void GenerateST(graph G) {
    int i = 0, j;
    for(i = 0; i < G.v; i++) {
        map <int,int> mp;
        graph temp;
        temp.v = G.v;
        for(j = 0; j < temp.v; j++) {
            vector<pair<int,int> > t ;
            temp.list.push_back(t);
        }
        mp[i] = i;
        func(G, mp, temp, i);
    }
}


// SORT THE GRAPH ACCORDING TO THEIR INCREASING COST

bool compare_graph(graph g1, graph g2) {
    return g1.cost < g2.cost ;
}

int main() {
    int v, i, j, n, k;
    graph G;
    InputGraph(G);
    GenerateST(G);
    cout<<"\nNo. of spanning trees: "<<st.size();
    sort(st.begin(), st.end(), compare_graph);

    cout<<"\n\nPossible Spanning Trees for the given graph are: ";
    cout<<"\n (Source Vertex): (Edge_1 -> Weight) -> (Edge_2 -> Weight) -> ...";
    for(i = 0; i < st.size(); i++) {
        cout<<"\n\nSpanning Tree "<<i+1<<" is : ";
        Display(st[i]);
        cout<<"\nIt's COST is :"<<st[i].cost;
    }

    // FINDING THE Kth MINIMUM SPANNING TREE
    cout<<endl;
    cout<<"\nPlease, Enter K: ";
        cin>>k;
    cout<<k<<"th Minimum Spanning Tree is : ";
    Display(st[k-1]);
    cout<<endl;
    cout<<"\nThe Cost of the "<<k<<"th Minimum Spanning Tree is : "<<st[k-1].cost;

    return 0;
}
