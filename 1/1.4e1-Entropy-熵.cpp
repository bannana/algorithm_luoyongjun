//能按照树构建的顺序计算出ans的确没想到
//string类不存在访问到边界以外的位置导致内存错误
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    string str;
    while(getline(cin,str)&&str!="END"){
        sort(str.begin(),str.end());
        priority_queue<ll,vector<ll>,greater<ll>> pq;
        ll num=1;
        for(ll i=1;i<=str.size();i++){
            if(str[i]!=str[i-1]){
                pq.push(num);
                num=1;
            }else num++;
        }
        ll ans=0;
        if(pq.size()==1)ans=str.size();
        while(pq.size()>1){
            ll a=pq.top();
            pq.pop();
            ll b=pq.top();
            pq.pop();
            ans+=a+b;
            pq.push(a+b);
        }
        printf("%lld %lld %.1lf\n",str.size()*8,ans,double(str.size())*8/ans);
    }
    return 0;
}