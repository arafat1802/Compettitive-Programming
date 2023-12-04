#include<bits/stdc++.h>
using namespace std;
#define MX 100 // total number of node or endpoing of every circuit.

struct Node{
    int nodeNo;
    int FirstPosition, SecondPosition;
};
bool custom(Node node1, Node node2){
    return node1.FirstPosition<=node2.FirstPosition;
}
vector<int> PreProcess(vector<int>&ParentNaiNode, vector<pair<int, int> >&Position){
    vector<int>finalVector;
    vector<Node> tempVector;
    Node node;
    vector<Node>NullAncestorNode;
    for(int i=0; i<ParentNaiNode.size(); i++){
        node.nodeNo = ParentNaiNode[i];
        node.FirstPosition = Position[ParentNaiNode[i]].first;
        node.SecondPosition = Position[ParentNaiNode[i]].second;
        NullAncestorNode.push_back(node);
    }
    sort(NullAncestorNode.begin(), NullAncestorNode.end(), custom);

    for(int i=0; i<NullAncestorNode.size(); i++){
        node = NullAncestorNode[i];
        if(!tempVector.size()) tempVector.push_back(node);
        else{
            if(tempVector[tempVector.size() - 1].SecondPosition <= node.FirstPosition) tempVector.push_back(node);
        }
    }
    for(int i=0; i<tempVector.size(); i++) finalVector.push_back(tempVector[i].nodeNo);
    return finalVector;
}
int main(){
    freopen("Left_Edge_inp_sir.txt", "r", stdin);

    int how_many, how_many2, num;
    char ch;
    vector<int> Columns;
    vector<char> Nets, Top_row, Bottom_row, Left_Nets, Right_Nets;
    vector< pair<int, int> > Position{MX};

//    cout<<"How many columns: "<<endl;
    cin>>how_many;
    for(int i = 0; i< how_many; i++){
        cin>>num;
        Columns.push_back(num);
    }
//    cout<<"How many Nets: "<<endl;
    cin>>how_many2;
    for(int i =0; i<how_many2; i++){
        cin>>ch;
        Nets.push_back(ch);
//        cout<<Position[0].first<<endl;
        Position[ch - 'A'].first = INT_MAX;
        Position[ch - 'A'].second = -INT_MAX;
    }
//    cout<<"Input "<<how_many<<" values of Top row: ";
    for(int i=0; i<how_many; i++){
        cin>>ch;
        Top_row.push_back(ch);
        Position[ch - 'A'].first = min(Position[ch - 'A'].first, i+1);
        Position[ch - 'A'].second = max(Position[ch - 'A'].first, i+1);
    }
//    cout<<"Input "<<how_many<<" values of Bottom row: ";

    for(int i=0; i<how_many; i++){
        cin>>ch;
        Bottom_row.push_back(ch);
        Position[ch - 'A'].first = min(Position[ch - 'A'].first, i+1);
        Position[ch - 'A'].second = max(Position[ch - 'A'].first, i+1);
    }
    cin>>how_many;
    for(int i = 0; i< how_many; i++){
        cin>>ch;
        Left_Nets.push_back(ch);
        Position[ch - 'A'].first = min(Position[ch - 'A'].first, -INT_MAX);
    }
    cin>>how_many;
    for(int i = 0; i< how_many; i++){
        cin>>ch;
        Right_Nets.push_back(ch);
        Position[ch - 'A'].second = max(Position[ch - 'A'].second, INT_MAX);
    } ///Input Done.

    ///Graph Making:
    vector<int>graphConnectivity[MX];
    int ParentCount[MX];
    bool NodeExist[MX];
    for(int i=0; i<MX; i++) {
        ParentCount[i] = 0;
        NodeExist[i] = false;
    }
    for(int i=0; i<Columns.size(); i++){
        if(Top_row[i] == '#' || Bottom_row[i] == '#') continue;
        graphConnectivity[Top_row[i] - 'A'].push_back(Bottom_row[i] - 'A');
        ParentCount[Bottom_row[i] - 'A']++;
        NodeExist[Top_row[i] - 'A'] = NodeExist[Bottom_row[i] - 'A'] = true;
    } /// Graph Making Done.

    ///Graph Processing:
    bool ProcessDone[MX];
    bool AllWorkFinished = false;
    for(int i=0; i<MX; i++) ProcessDone[i] = false;

    vector<int> ParentNaiNode, ChosenNode;
    int track = 0;
    while(!AllWorkFinished && track<100){
        track++;
        for(int i=0; i<MX; i++){
            if(NodeExist[i] == true && ParentCount[i] == 0 && ProcessDone[i] == false)
                ParentNaiNode.push_back(i);
        }
        ///node process:
        ChosenNode = PreProcess(ParentNaiNode, Position);
        ///graph Update:
        cout<<"Track "<<track<<": ";
        for(int i=0; i<ChosenNode.size(); i++){
            cout<<(char)(ChosenNode[i] + 'A')<<" ";
            ProcessDone[ChosenNode[i]] = true;
            for(int j = 0; j < graphConnectivity[ChosenNode[i]].size(); j++) {
                ParentCount[graphConnectivity[ChosenNode[i]][j]]--;
            }
        }
        cout<<endl;
        ChosenNode.clear();
        ParentNaiNode.clear();
        ///Loop Break korar code:
        AllWorkFinished = true;
        for(int i=0; i<MX; i++) { /// i node.
            if(NodeExist[i] == 1 && (ParentCount[i]!=0 || ProcessDone[i] == 0)) AllWorkFinished = false;
        }
    }
    return 0;
}
