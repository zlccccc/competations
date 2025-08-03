#include <sstream>
#include <fstream>
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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
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

queue<int> Q;
int d[maxn];
vector<int> edge[maxn];
int fa[maxn],cntfa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
char SA[100],SB[100];
int A[maxn],B[maxn];
int solve(){
    int n,i;
    scanf("%d",&n);
    scanf("%s",SA);
    FOR(i,1,n) scanf("%d",&A[i]);
    scanf("%s",SB);
    FOR(i,1,n) scanf("%d",&B[i]);
    if (SA[0]=='C'&&SB[0]=='C'){
        FOR(i,1,n) if (A[i]!=B[i]) return 0*puts("-1");
        return 0*puts("0");
    }else{
        int ans=0;
        FOR(i,1,100000) fa[i]=i,cntfa[i]=1,edge[i].clear();
        FOR(i,1,n){
            int x=getfa(A[i]),y=getfa(B[i]);
            if (x==y) continue;
            ans++; fa[x]=y;
        }
        if (SA[0]!=SB[0]){
            FOR(i,1,n) if (A[i]!=B[i]) edge[A[i]].push_back(B[i]),d[B[i]]++;
            FOR(i,1,100000) if (!d[i]) Q.push(i);
            while (Q.size()){
                int x=Q.front();Q.pop();
                cntfa[x]=0;
                for (int v:edge[x]){
                    d[v]--;
                    if (!d[v]) Q.push(v);
                }
            }
            FOR(i,1,100000) cntfa[getfa(i)]|=cntfa[i];
            FOR(i,1,100000) if (fa[i]==i) ans+=cntfa[i];
        }
        printf("%d\n",ans);
    }
    return 0;
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) solve();
}
/*
2
Constant 111 222
Variable 222 111
*/
