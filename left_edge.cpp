#include<bits/stdc++.h>
using namespace std;
vector<int>nets;
vector<vector<int>>vcg;
vector<bool> visited;
vector<int> ans;
map<int,int>ancestor;
map<int, pair<int,int>>range;
int net;

#define bug(x) cerr << #x << " = "  << x << "\n"

bool cmp(pair<pair<int,int>, int>a, pair<pair<int,int>, int>b){
    return a.first.first <= b.first.first;
}
void create_vcg(vector<int>a, vector<int>b){
    for(int i = 0; i < a.size(); i++){
        if(a[i] == -1 or b[i] == -1)continue;
        else {
            vcg[a[i]].push_back(b[i]);
            ancestor[b[i]] = a[i];
        }
    }
    for(int i = 1; i <= net; i++){
        if(!ancestor.count(i)){
            //cout << "i = " << i << "\n";
            vcg[0].push_back(i);
        }
    }
}
vector<vector<int>>res;
void bfs(int s){
    visited.resize(net+1,false);
    int cnt = 0;
    deque<int>Q;
    visited[s] = true;
    Q.push_back(s);
    while(!Q.empty()){
        vector<int>baicha_jaoa;

        int size = Q.size();
        vector<int> noAncestor;
        bug(size);
        for(int i = 0; i < size; i++){
            int u = Q.front();
            bug(u);
            noAncestor.push_back(u);
            Q.pop_front();
            for(auto v : vcg[u]){
                if(!visited[v]){
                    Q.push_back(v);
                    visited[v] = true;
                }
            }
        }
        
        vector<pair<pair<int,int>, int>>sorted;
        for(auto it : noAncestor){
            sorted.push_back({{range[it].first, range[it].second},it});
            // bug(it);
            // bug(range[it].first);
            // bug(range[it].second);
        }
        sort(sorted.begin(), sorted.end(), cmp);
        // for(auto it : sorted){
        //     bug(it.second);
        
        //     bug(it.first.first);
        //     bug(it.first.second);
        // }
        int prevNode = 0;
        //res[cnt].push_back(sorted[0].second);
        int j = 0;
        bug(sorted[j].second);
        res[cnt].push_back(sorted[j].second);
        
        for(int i = 1; i < noAncestor.size(); i++){
            int node = sorted[i].second;
            int x1 = sorted[i].first.first;
            int y1 = sorted[i].first.second;
            int x2 = sorted[j].first.first;
            int y2 = sorted[j].first.second;
            if(x1 >= y2){
                res[cnt].push_back(node);
                if(node == 4){
                    bug(y1);
                    bug(x2);
                }
                j = i;
            }
            else{
                Q.push_front(node);
                // bug(Q.front());
                // bug(node);
                // baicha_jaoa.push_back(node);
            }
            prevNode = node;

        }
        cnt++;
        noAncestor.clear();
        sorted.clear();
    }
    for(auto it : res){
        for(auto i : it){
            cout << i << " ";
        }
        cout << "\n";
    }
    
}

int main()
{
    
    cin >> net;
    nets.resize(net);
    res.resize(net+1);
    for(int i = 0; i < net; i++){
        cin >> nets[i];
    }
    // for(auto it : nets){
    //     cout << it << " ";
    // }
    // cout << endl;
    vcg.resize(net+10);
    int n;
    cin >> n;

    vector<int>a(n),b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    
    range[0] = {0,0};
    // bug(net);
    for(int i = 0; i < net; i++){
        // bug(nets[i]);
        for(int j = 0; j < n; j++){
            if(a[j] == nets[i] or b[j] == nets[i]){
                range[nets[i]] = {j,n+1};
                break;
            }
            //range[nets[i]] = {-1,n+1};
        }
    }
    
    for(int i = 0; i < net; i++){
        for(int j = n-1; j >= 0; j--){
            if(a[j] == nets[i] or b[j] == nets[i]){
                range[nets[i]] = {range[nets[i]].first,j};
                break;
            }
            //range[]
        }
    }
    
    create_vcg(a,b);
    bfs(0);
    
}