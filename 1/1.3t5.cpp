#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
ll power(char a){
    if(a=='+'||a=='-')return 1;
    if(a=='*'||a=='/')return 2;
    if(a=='^')return 3;
    return 0;
}
bool isop(string it){
    if(it.size()==1&&string{"+-*/^"}.find(it[0])!=string::npos)return true;
    return false;
}
ll kua(ll a,ll b){
    ll ans=1;
    while(b){
        if(b%2)ans*=a;
        b/=2;
        a*=a;
    }
    return ans;
}
ll ca(ll a,ll b,char c){
    if(c=='+')return b+a;
    if(c=='-')return b-a;
    if(c=='*')return b*a;
    if(c=='/')return b/a;
    if(c=='^')return kua(b,a);
}
int main(){
    string str;
    cin>>str;
    vector<string> dq;
    deque<char> cal;
    for(ll i=0;i<str.size();){
        char cnt=str[i];
        if('0'<=cnt&&cnt<='9'){
            string num;
            while(i<str.size()&&('0'<=str[i]&&str[i]<='9'))
                num+=str[i++];
            dq.push_back(num);
            continue;
        }else if(cnt=='('){
            cal.push_back('(');
        }else if(cnt==')'){
            while(!cal.empty()&&cal.back()!='('){
                string tran=string(1,cal.back());
                dq.push_back(tran);
                cal.pop_back();
            }
            if(!cal.empty())cal.pop_back();
        }else{
            while(!cal.empty()&&cal.back()!='('){
                if(power(cnt)<=power(cal.back())&&cnt!='^'){
                    dq.push_back(string(1,cal.back()));
                    cal.pop_back();
                }else break;
            }
            cal.push_back(cnt);
        }
        i++;
    }
    while(!cal.empty()){
        dq.push_back(string(1,cal.back()));
        cal.pop_back();
    }
    for(ll i=0;i<dq.size();i++){
        if(i!=0)cout<<' ';
        cout<<dq[i];
    }
    cout<<endl;
    while(dq.size()>1){
        for(ll j=0;j<dq.size();j++){
            if(isop(dq[j])){
                ll a=stoll(dq[j-1]);
                ll b=stoll(dq[j-2]);
                ll op=dq[j][0];
                dq.erase(dq.begin()+j-2,dq.begin()+j+1);
                dq.insert(dq.begin()+j-2,to_string(ca(a,b,op)));
                break;
            }
        }
        for(ll j=0;j<dq.size();j++){
            if(j!=0)cout<<' ';
            cout<<dq[j];
        }
        cout<<endl;
    }
    return 0;
}
