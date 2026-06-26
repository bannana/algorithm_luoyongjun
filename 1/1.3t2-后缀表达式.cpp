//直接用ac、bc作为临时数据，出现.完成一次计算
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    string str;
    cin>>str;
    deque<ll> dq;
    ll ac=0,bc=0;
    ll a,b;
    for(ll i=0;i<str.size();i++){
        auto it=str[i];
            switch (it){
            case '@':
                break;
            case '.':
                dq.push_back(ac);
                ac=bc=0;
                break;
            case '+':
                a=dq.back();
                dq.pop_back();
                b=dq.back();
                dq.pop_back();
                dq.push_back(a+b);
                break;
            case '-':
                a=dq.back();
                dq.pop_back();
                b=dq.back();
                dq.pop_back();
                dq.push_back(b-a);
                break;
            case '*':
                a=dq.back();
                dq.pop_back();
                b=dq.back();
                dq.pop_back();
                dq.push_back(a*b);
                break;
            case '/':
                a=dq.back();
                dq.pop_back();
                b=dq.back();
                dq.pop_back();
                dq.push_back(b/a);
                break;
            default:
                ac=bc*10+it-'0';
                bc=ac;
                break;
        }
    }
    cout<<dq.back()<<endl;
    return 0;
}