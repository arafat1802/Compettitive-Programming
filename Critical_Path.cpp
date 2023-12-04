#include<bits/stdc++.h>
using namespace std;

vector<int>Graph[1000];
int Weight[1000][1000];
int ES[1000], TF[1000];

void ProcessGraph_ES(int node, int cost){
    ES[node] = max(ES[node], cost);
    cout<<(char)(node+'0')<<"=> ES = "<<ES[node]<<endl;
    for(int i=0; i<Graph[node].size(); i++){
        int NextNode = Graph[node][i];
        int weight = Weight[node][NextNode];
        ProcessGraph_ES(NextNode, ES[node] + weight);
    }
}
int ProcessGraph_TF(int node){
    if(Graph[node].size() == 0) TF[node] = ES[node];
    for(int i=0; i<Graph[node].size(); i++){
        int NextNode = Graph[node][i];
        int weight = Weight[node][NextNode];
        int cost = ProcessGraph_TF(NextNode);
        TF[node] = min(TF[node], cost - weight);
    }
    cout<<(char)(node+'0')<<"=> TF = "<<TF[node]<<endl;
    return TF[node];
}
void FindCriticalPath(int node){
    if(ES[node] != TF[node]) return;
    cout<<(char)(node + '0')<<" ";
    for(int i=0; i<Graph[node].size(); i++) FindCriticalPath(Graph[node][i]);
}
int main(){
    // tf = finish time
    // es = earliest start time
    freopen("Critical_Path.txt", "r", stdin);
    int HowManyEdge, weight;
    char StartNode, Node1, Node2;

    cin>>HowManyEdge;
    for(int i = 0; i < HowManyEdge; i++){
        cin>>Node1>>Node2>>weight;
        Graph[Node1 - '0'].push_back(Node2- '0');
        Weight[Node1 - '0'][Node2 - '0'] = weight;
    }
    cin>>StartNode;

    for(int i=0;i<1000;i++) TF[i] = INT_MAX;
    ES[StartNode-'0'] = 0;
    ProcessGraph_ES(StartNode - '0', 0);
    cout<<endl;
    int TF_cost = ProcessGraph_TF(StartNode - '0');
    FindCriticalPath(StartNode - '0');
    return 0;
}
