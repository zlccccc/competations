#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

vector<pair<int,int> > edge[maxn];
bool mark[maxn];
vector<LL> L;
void dfs(int x,int f,LL len){
    mark[x]=0;//lose
    L.push_back(len);
    for (auto v:edge[x]) if (v.first!=f){
        dfs(v.first,x,len+v.second);
    }
}
int n,p,k;
int main() {
    int i,j,k;
    int T,cnt=0;
    scanf("%d%d%d",&n,&p,&k);
    FOR(i,1,n-1){
        int u,v,k;
        scanf("%d%d%d",&u,&v,&k);
        edge[u].push_back(make_pair(v,k));
        edge[v].push_back(make_pair(u,k));
    }dfs(p,0,0);
    sort(L.begin(),L.end());
    printf("%lld\n",L[k]);
    return 0;
}
/*
3 3 2
1 2 4
2 3 5
*/
