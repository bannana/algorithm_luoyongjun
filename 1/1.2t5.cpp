//单调栈问题注意2个stack与a[n]哨兵
//前一个确保top可访问，并且初始位置可被计算
//第二个确保最后全部位置都被清算，这里设计的很棒
//注意要在本轮res计算完成后push
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll n;
    cin>>n;
    vector<ll> a(n+2,0),sum(n+2,0),res(n+2,0);
    for(ll i=1;i<=n;i++)cin>>a[i];
    n++;
    stack<ll> st;
    st.push(0);
    ll ans=0;
    for(ll i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
        while(!st.empty()&&a[st.top()]>a[i]){
            ll tp=st.top();
            st.pop();
            res[tp]+=(sum[i-1]-sum[tp]);
        }
        res[i]=(sum[i]-sum[st.top()]);
        st.push(i);
    }
    for(ll i=1;i<=n;i++){
        ans=max(ans,res[i]*a[i]);
    }
    cout<<ans<<endl;
    return 0;
}