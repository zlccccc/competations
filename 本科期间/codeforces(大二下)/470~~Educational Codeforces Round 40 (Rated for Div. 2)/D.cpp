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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,a,b;
int i,j,k;
int Q[maxn],s,t;
int e[1007][1007];
vector<int> E[maxn];
int S[maxn],T[maxn];
int ans;
int main(){
    scanf("%d%d%d%d",&n,&m,&a,&b);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
        e[u][v]=e[v][u]=1;
    }FOR(i,1,n) S[i]=T[i]=-1;
    s=t=0;Q[t++]=a;S[a]=0;
    while (s<t){
        int x=Q[s++];
        for (int v:E[x]) if (S[v]==-1){
            S[v]=S[x]+1;
            Q[t++]=v;
        }
    }s=t=0;Q[t++]=b;T[b]=0;
    while (s<t){
        int x=Q[s++];
        for (int v:E[x]) if (T[v]==-1){
            T[v]=T[x]+1;
            Q[t++]=v;
        }
    }
//    FOR(i,1,n) printf("%d ",S[i]);puts("");
//    FOR(i,1,n) printf("%d ",T[i]);puts("");
    FOR(i,1,n)
        FOR(j,i+1,n)
            if (!e[i][j]&&S[i]+T[j]+1>=S[b]&&S[j]+T[i]+1>=S[b]) ans++;
    printf("%d\n",ans);
}
/*
*/
