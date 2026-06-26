//小心))((
//一定要确保操作数据结构时，是非空状态，否则RE
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    string str;
    cin>>str;
    stack<char> st;
    for(ll i=0;i<str.size();i++){
        if(str[i]=='(')st.push('(');
        else if(str[i]==')'){
            if(st.empty()){
                cout<<"NO"<<endl;
                return 0;
            }
            st.pop();
        }
    }
    if(!st.empty())cout<<"NO"<<endl;
    else cout<<"YES"<<endl;
    return 0;
}