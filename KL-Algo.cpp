#include<bits/stdc++.h>
#define MX 1000
using namespace std;

int NumberOfNode, NumberOfEdge, n1, n2, i = 1, MaxGain = -INT_MAX, FinalPair1, FinalPair2;
vector<int> Graph[MX];
int Group[MX], Ans[MX], Cost[MX];
bool ProcessDone[MX];

void Cost_Generator(){
    for(int i=1; i<=NumberOfNode; i++){
        int NodeCurrentCost = 0;
        for(int j = 0; j<Graph[i].size(); j++){
            if(Group[i] == Group[Graph[i][j]]) NodeCurrentCost--;
            else NodeCurrentCost++;
        }
        Cost[i] = NodeCurrentCost;
    }
}
pair<int, pair<int, int> > MaxGain_AND_Pair_Finder(){
    int Node1Max, Node2Max;
    n1 = n2 = 0;
    Node1Max = Node2Max = -INT_MAX;
    for(int i=1; i<=NumberOfNode; i++){///Max Cost node Find of two groups
        if(Group[i]==1 && ProcessDone[i]==false && Node1Max<Cost[i]) {n1 = i; Node1Max = Cost[i];}
        if(Group[i]==2 && ProcessDone[i]==false && Node2Max<Cost[i]) {n2 = i; Node2Max = Cost[i];}
    }
    bool connected = false;
    for(int i=0; i<Graph[n1].size(); i++) if(Graph[n1][i] == n2) connected = true;
    int gain = Cost[n1] + Cost[n2] - 2*connected;
    return {gain, {n1, n2}};
}
void GroupPrinter(int Group[]){
    cout<<"A: [ ";
    for(int i=1;i<=NumberOfNode; i++) if(Group[i] == 1) cout<<i<<" ";
    cout<<"]\nB: [ ";
    for(int i=1;i<=NumberOfNode; i++) if(Group[i] == 2) cout<<i<<" ";
    cout<<"]\n\n";
}
int main(){
    cout << MaxGain << "\n";
    freopen("KL_input.txt", "r", stdin);
    cin>>NumberOfNode>>NumberOfEdge;
    for(int i = 0; i<NumberOfEdge; i++){
        cin>>n1>>n2;
        Graph[n1].push_back(n2);
        Graph[n2].push_back(n1);
    }
    ///Group init.
    for(int i=1; i<=NumberOfNode; i++){
        if(i <= NumberOfNode/2) Group[i] = 1;
        else Group[i] = 2;
        ProcessDone[i] = false;
    }

    cout<<"Initial Partition: "<<endl;
    GroupPrinter(Group);
    while(1){
        Cost_Generator();
        pair<int, pair<int, int> > Pair = MaxGain_AND_Pair_Finder();
        if(!n1 && !n2) break;
        cout<<"Precess: "<<i<<endl; i++;
        cout<<Pair.first<<" => "<<Pair.second.first<<", "<<Pair.second.second<<"\n";
        swap(Group[Pair.second.first], Group[Pair.second.second]);
        ProcessDone[Pair.second.first] = ProcessDone[Pair.second.second] = true;
        GroupPrinter(Group);
        if(Pair.first>MaxGain) {
            MaxGain = Pair.first;
            FinalPair1 = Pair.second.first;
            FinalPair2 = Pair.second.second;
            for(int j = 1; j <= NumberOfNode; j++) Ans[j] = Group[j];
        }
    }
    cout<<"The Solution of Partition: (MaxGain = "<<MaxGain<<", For Pair <"<<FinalPair1<<","<<FinalPair2<<">)"<<endl;
    GroupPrinter(Ans);
    return 0;
}
