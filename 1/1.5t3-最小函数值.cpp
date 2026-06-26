#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

struct node {
    ll w;
    ll a, b, c;
    ll cntx = 1;
};

struct cmp {
    bool operator()(const node &a, const node &b) const {
        return a.w > b.w;
    }
};

int main() {
    ll n, m;
    cin >> n >> m;
    priority_queue<node, vector<node>, cmp> pq;
    for (ll i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        node po;
        po.a = a, po.b = b, po.c = c;
        po.cntx = 1;
        po.w = a + b + c;
        pq.push(po);
    }
    while (m--) {
        auto f = pq.top();
        pq.pop();
        cout << f.w << " ";
        f.cntx++;
        f.w = f.a * f.cntx * f.cntx + f.b * f.cntx + f.c;
        pq.push(f);
    }
    cout<<endl;
    return 0;
}
