#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    ll t;
    cin>>t;
    cin.ignore();
    while(t--){
        string str;
        getline(cin,str);
        stack<char> st;
        string oo;
        for(ll i=0;i<=str.size();i++){
            if(str[i]==' '||i==str.size()){
                while(!st.empty()){
                    oo.push_back(st.top());
                    st.pop();
                }
                if(i==str.size())oo.push_back(' ');
            }else st.push(str[i]);
        }
        cout<<oo<<endl;
    }
    return 0;
}