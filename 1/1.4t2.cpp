#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
ll len;
string ans;
vector<ll> num;
ll kuai(ll a,ll b){
    ll ans=1;
    while(b){
        if(b%2)ans*=a;
        b/=2;
        a*=a;
    }
    return ans;
}
char cal(ll l,ll r){
    if(r==l){
        if(num[l])return 'I';
        else return 'B';
    }
    ll mid=(l+r)/2;
    char lres=cal(l,mid);
    ans.push_back(lres);
    char rres=cal(mid+1,r);
    ans.push_back(rres);
    if(lres==rres&&lres=='I')return 'I';
    else if(lres==rres&&lres=='B')return 'B';
    else return 'F';
}
int main(){
    ll n;
    cin>>n;
    len=kuai(2,n);
    num.resize(len+1);
    for(ll i=1;i<=len;i++){
        char c;
        cin>>c;
        num[i]=c-'0';
    }
    ans.push_back(cal(1,len));
    cout<<ans<<endl;
    return 0;
}