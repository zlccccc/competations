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
int nxt[maxn][26],tot;
int dep[maxn];
multiset<int> have[maxn];
LL ans;
void ins(char A[]){
    int p=0,i,len=strlen(A);
    REP(i,len){
        int c=A[i]-'a';
        if (!nxt[p][c]) {
            nxt[p][c]=++tot;
            dep[tot]=dep[p]+1;
        }p=nxt[p][c];
    }have[p].insert(len);
}
//char c[maxn];int L;
void dfs(int x){
    int mark=have[x].size(),i;
    REP(i,26) if (nxt[x][i]){
//        c[L]=i+'a';L++;
        int v=nxt[x][i]; dfs(v);
        if (have[x].size()<have[v].size())
            swap(have[x],have[v]);
        for (int t:have[v]) have[x].insert(t);
        have[v].clear();
    }
//    printf("calc: %d: %s\n",x,c);
//    for (int v:have[x]) printf("%d ",v);puts("");
    if (x&&!mark){
        multiset<int>::iterator it=have[x].end();
        it--;have[x].erase(it);
        have[x].insert(dep[x]);
    }
//    for (int v:have[x]) printf("%d ",v);puts("");
//    L--;c[L]=0;
}
char A[maxn];
int main() {
    int i,j,k,t;
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",A);
        ins(A);
    }dfs(0);
    for (int v:have[0]) ans+=v;
//    for (int v:have[0]) printf("%d ",v);
    printf("%I64d\n",ans);
    return 0;
}
/*
*/
