//hdu1003最大字段和问题，以下为贪心解法，注意累计值大于历史最大值时更新左右边界
//也可以使用dp，先赋值为初始值，计算包括当前位置与之前的和，大于当前值则要前面的，否则左边界右移
//若大于历史最大值，更新边界，一定要注意区间不要带上产生最小值位置
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(ll ca){
    ll n;
    cin>>n;
    vector<ll>a(n+2);
    for(ll i=1;i<=n;i++)cin>>a[i];
    ll sum=0;
    ll l=1;
    ll a1=1,a2=1;
    ll ma=a[1];
    ll mi=0;
    for(ll r=1;r<=n;r++){
        sum+=a[r];
        ll cal=sum-mi;
        if(cal>ma){
            ma=cal;
            a1=l;
            a2=r;
        }
        if(sum<mi){
            mi=sum;
            l=r+1;
        }
    }
    cout<<"Case "<<ca<<":"<<endl;
    cout<<ma<<" "<<a1<<" "<<a2<<endl;
}
int main(){
    ll t;
    cin>>t;
    for(ll i=1;i<=t;i++){
        if(i!=1)cout<<endl;
        solve(i);
    }
    return 0;
}