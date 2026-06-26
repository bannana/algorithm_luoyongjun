//本题可以辅助理解前中后序遍历，前后遍历强调了根的位置，中序遍历强调了子树位置
//仅有前后遍历，无法构造确定的树，比如前序AB，后序BA，根都是A但B无法确定在哪个树上
//故如果要找树可能的形态就要找形如以上形式的个数，这是造成差异的原因
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int main(){
    string s1,s2;
    cin>>s1>>s2;
    ll ans=0;
    for(ll i=0;i<s1.size();i++){
        for(ll j=0;j<s2.size();j++){
            if(s1[i]==s2[j+1]&&s1[i+1]==s2[j])ans++;
        }
    }
    cout<<(ll)pow(2,ans)<<endl;
    return 0;
}