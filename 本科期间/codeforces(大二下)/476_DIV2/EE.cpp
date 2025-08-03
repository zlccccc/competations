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
const LL maxn=4e5+7;
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

//tree->update
int n,m,q;
int f[maxn];
int nxt[maxn][26],tot;
int fa[maxn],dep[maxn],id[maxn];
vector<int> have[maxn];
LL ans;int L;
void ins(char A[],int k){
    int p=0,i,len=strlen(A);
    REP(i,len){
        int c=A[i]-'a';
        if (!nxt[p][c]) {
            nxt[p][c]=++tot;
            fa[tot]=p;
//            if (!id[p]) fa[tot]=p;
//            else fa[tot]=fa[p];
            dep[tot]=dep[p]+1;
        }p=nxt[p][c];
    }id[p]=k;ans+=len;
    have[len].push_back(p);
//    printf("%d - > %d \n",len,p);
    L=max(L,len);
}
inline int getfa(int x){
    if (!x||!id[x]) return x;
    return fa[x]=getfa(fa[x]);
}
char A[maxn];
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",A);
        ins(A,i);
    }rFOR(i,1,L){
        for (int v:have[i]){
            int t=getfa(v);
//            printf("%d -> %d(%d,dep=%d)\n",v,t,id[v],dep[v]);
            if (t) {
                ans+=dep[t]-dep[v];
                have[dep[t]].push_back(t);
                id[t]=id[v];id[v]=0;
            }
        }
    }
//    FOR(i,1,tot) printf("%d:(%d,id=%d) ",i,dep[i],id[i]);
    printf("%I64d\n",ans);
    return 0;
}
/*
*/
