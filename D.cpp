#include<bits/stdc++.h>
#define x first
#define y second

using namespace std;

const int N = 2e5+1, MX = 1e6+1;

vector<int> d[MX];
void init(){
    for(int j = 1; j < MX; ++j)
        for(int i = j; i < MX; i += j)
            d[i].push_back(j);
}

int n, m;
int a[N];
vector<pair<int, int>> queries[N];
int ans[N];

int lst[MX];

set<pair<int, int>> s;
void insert(pair<int, int> p){
    auto it = s.lower_bound({p.x, -1});
    if(it != s.end() && it->y > p.y)
        return;
    it = s.upper_bound({p.x, MX});
    while(it != s.begin() && prev(it)->y < p.y)
        s.erase(prev(it));
    s.insert(p);
}

int main(){
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    init();
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    cin >> m;
    for(int i = 0; i < m; ++i){
        int l, r;
        cin >> l >> r;
        --l; --r;
        queries[r].emplace_back(l, i);
    }
    for(int i = 0; i < MX; ++i)
        lst[i] = -1;
    for(int i = 0; i < n; ++i){
        for(int k : d[a[i]]){
            if(lst[k] != -1)
                insert({lst[k], k});
            lst[k] = i;
        }
        for(auto q : queries[i])
            ans[q.y] = s.lower_bound({q.x, -1})->y;
    }
    for(int i = 0; i < m; ++i)
        cout << ans[i] << "\n";
}
