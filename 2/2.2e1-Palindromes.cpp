#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
bool solve(){
    string str;
    cin>>str;
    ll len=str.size();
    for(ll i=0;i<len;i++){
        if(str[i]!=str[len-i-1])return false;
    }
    return true;
}
int main(){
    ll t;
    cin>>t;
    while(t--){
        if(solve())cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    }
    return 0;
}