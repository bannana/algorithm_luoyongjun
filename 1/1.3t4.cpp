#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    string str;
    cin>>str;
    ll a=0,b=0;
    str.push_back(1);
    stack<ll> st;
    ll acc=1;
    ll ans=0;
    for(ll i=0;i<=str.size();i++){
        auto it=str[i];
        ans%=10000;
        acc%=10000;
        a%=10000;
        b%=10000;
        if(it=='+'||i==str.size()-1){
            ans+=(acc*a);
            acc=1;
            a=b=0;
            if(i==str.size())break;
        }else if(it=='*'){
            acc*=a;
            a=b=0;
        }else{
            a=b*10+it-'0';
            b=a;
        }
    }
    cout<<ans<<endl;
    return 0;
}