#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(auto &it : a)cin >> it;
    vector<int>suffix(n,0);
    suffix[n-1] = a[n-1];
    
    for(int i = n-2; i >= 0; i--){
        suffix[i] = suffix[i+1] + a[i];
    }
    int CypriotValue = suffix[0];
    for(int i = 1;i < n; i++){
        if(suffix[i] > 0)CypriotValue += suffix[i];
    }
    cout << CypriotValue  << "\n";
}
int32_t main()
{
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--)solve();

    return 0;
}