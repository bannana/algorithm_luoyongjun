#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef pair<char,char> pll;
unordered_map<char,pll> mp;
void fid(char pos){
    char l=mp[pos].first,r=mp[pos].second;
    cout<<pos;
    if(l!='*')fid(l);
    if(r!='*')fid(r);
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll n;
    cin>>n;
    char root;
    for(ll i=0;i<n;i++){
        char a,b,c;
        cin>>a>>b>>c;
        if(i==0)root=a;
        mp[a]={b,c};
    }
    fid(root);
    cout<<endl;
    return 0;
}