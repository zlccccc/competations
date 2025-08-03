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


int n,m;
int fa[maxn];
vector<int> edge[maxn];
int root;
vector<int> ans,rev;
int dep[maxn];
void dfs(int x,int len){
    dep[x]=len;
    for (int v:edge[x]) dfs(v,len+1);
}
int id[maxn];
bool cmp(int x,int y){
    return dep[x]>dep[y];
}int d[maxn];
int main() {
    int i,j,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&fa[i]);
    FOR(i,1,n) if (fa[i]==0) root=i;
    FOR(i,1,n) if (fa[i]) edge[fa[i]].push_back(i);
    dfs(root,0);
    FOR(i,1,n) id[i]=i;
    sort(id+1,id+1+n,cmp);
    FOR(j,1,n){
        int i=id[j];
        if (fa[i]){
            if (d[i]==1){
                ans.push_back(i);
            }else{
                d[fa[i]]^=1;
                rev.push_back(i);
            }
        }else{
            if (d[i]==1){
                return 0*puts("NO");
            }else ans.push_back(i);
        }
    }puts("YES");
    for (int v:ans) printf("%d\n",v);
    reverse(rev.begin(),rev.end());
    for (int v:rev) printf("%d\n",v);
    return 0;
}
/*
2 2 3 3
+-++++
*/
