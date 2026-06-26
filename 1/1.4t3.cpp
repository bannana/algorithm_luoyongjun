#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
void fid(string fr,string be){
    if(fr.size()>0){
        char root=be.back();
        cout<<root;
        ll gap=fr.find(root),siz=fr.size();
        fid(fr.substr(0,gap),be.substr(0,gap));
        fid(fr.substr(gap+1,siz-gap),be.substr(gap,siz-gap-1));
    }
}
int main(){ 
    string fr,be;
    cin>>fr>>be;
    fid(fr,be);
    cout<<endl;
    return 0;
}