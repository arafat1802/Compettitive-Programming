#include<bits/stdc++.h>
#define MX 10
using namespace std;

int NumberOfChar, NumberOfValues;
char ch[MX];
int Numbers[MX];
vector<int>vv;

vector<pair<vector<int>, string> > groups[MX], groups2[MX], FinalAns;
map<string, bool> WorkDone;

int hamming_Calculator(string &s1, string &s2){
    cout<<s1<<" "<<s2<<", harming = ";
    int cnt = 0;
    for(int i=0; i<s1.size(); i++) if(s1[i] != s2[i]) cnt++;
    cout<<cnt<<endl;
    return cnt;
}
string String_Changer(string str1, string &str2){
    for(int i=0; i<str1.size(); i++) {
        if(str1[i] != str2[i]){
            str1[i] = '#';
            break;
        }
    }
    return str1;

}
pair<int, string> HowManyBits(int num){
    int cnt = 0;
    string str = "";
    for(int i=0; i<NumberOfChar; i++) {
        if(num&(1<<i)) {
            cnt++;
            str = "1" + str;
        }else str = "0" + str;
    }
    return {cnt, str};
}
int main(){
    freopen("Quine_McCluskey.txt", "r", stdin);

    cin>>NumberOfChar;
    for(int i=0; i<NumberOfChar; i++) cin>>ch[i];
    cin>>NumberOfValues;
    for(int i=0; i<NumberOfValues; i++){
        cin>>Numbers[i];

        pair<int, string> numberInfo = HowManyBits(Numbers[i]);
        vector<int>temp;
        temp.push_back(Numbers[i]);
        groups[numberInfo.first].push_back({temp, numberInfo.second});
    }

    for(int i=0; i<NumberOfChar; i++){
        cout<<i<<" = "<<endl;
        for(int j=0; j<groups[i].size(); j++) { //group i ekta vector (i'th bit er group), vector er element hosce pair: {}
            vector<int>temp = groups[i][j].first;
            string str = groups[i][j].second;
            cout<<temp[0]<<" "<<str<<endl;
        }
        cout<<endl<<endl;
    }

    ///processing
    for(int i=0; i<NumberOfChar-1; i++){
        cout<<"group: "<<i<<" & "<<(i+1)<<endl;
        int next_group = i+1;
        for(int j = 0; j<groups[i].size(); j++){
            pair<vector<int>, string> oneElement = groups[i][j];
            bool done1 = false;
            for(int k = 0; k<groups[next_group].size(); k++){
                pair<vector<int>, string> OneElement = groups[i][k];
                int hammingDistance = hamming_Calculator(oneElement.second, OneElement.second);
                if(hammingDistance == 1) {
                    done1 = true;
                    string str = String_Changer(oneElement.second, OneElement.second);
                    vv.clear();
                    for(int l = 0;l<oneElement.first.size(); l++) vv.push_back(oneElement.first[l]);
                    for(int l = 0;l<OneElement.first.size(); l++) vv.push_back(OneElement.first[l]);
                    groups2[i].push_back({vv, str});
                    WorkDone.insert({OneElement.second, true});
                }
            }
            if(!done1) FinalAns.push_back(oneElement);
        }
        cout<<endl<<endl;
    }
    return 0;
}

