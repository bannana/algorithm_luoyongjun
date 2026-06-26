//666模拟了个优先队列，让这个队列头存当前最值
//但队列内存的是位置，便于比较和输出
//超出窗口后自动删掉前面多余部分
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> a;
int main(){
    ll n,k;
    cin>>n>>k;
    vector<ll> a(n);
    for(ll i=0;i<n;i++)cin>>a[i];
    deque<ll> lo;
    bool fla=false;
    for(ll i=0;i<n;i++){
        while(!lo.empty()&&a[lo.back()]>a[i])lo.pop_back();
        lo.push_back(i);
        if(i>=k-1){
            while(!lo.empty()&&i-lo.front()>=k)lo.pop_front();
            if(fla)cout<<" ";
            cout<<a[lo.front()];
            fla=true;
        }
    }
    cout<<endl;
    lo.clear();
    fla=false;
    for(ll i=0;i<n;i++){
        while(!lo.empty()&&a[lo.back()]<a[i])lo.pop_back();
        lo.push_back(i);
        if(i>=k-1){
            while(!lo.empty()&&i-lo.front()>=k)lo.pop_front();
            if(fla)cout<<" ";
            cout<<a[lo.front()];
            fla=true;
        }
    }
    cout<<endl;
    return 0;
}