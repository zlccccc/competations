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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
LL A[maxn],B[maxn];//A*i+B
inline int lowbit(int x){return x&-x;}
void Add(int x,LL val,LL VAL){
    for (;x<=n;x+=lowbit(x)) (A[x]+=val)%=M,(B[x]+=VAL)%=M;
}
void add(int l,int r,LL val){
    Add(l,val,-((l-1)*val%M)+M);
    Add(r+1,M-val,r*val%M);
}
LL query(int x){
    LL ret=0;for (int i=x;x;x-=lowbit(x)) (ret+=A[x]*i+B[x])%=M;
    return ret;
}
LL query(int l,int r){
    return (query(r)-query(l-1)+M)%M;
}
int m,q,i,j,k;
int T,len;
vector<int> edge[maxn];
int fa[maxn],ls[maxn],rs[maxn],id[maxn];
int val[maxn];
int Q[maxn];
int mark[maxn];
int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }int front=0,end=0;
    Q[++end]=1;mark[1]=1;
    while (front<end){
        int x=Q[++front];id[x]=front;
        for (int v:edge[x]) if (!mark[v]){
            Q[++end]=v;
            if (!ls[x]) ls[x]=end;
            rs[x]=end;fa[v]=x;
            mark[v]=1;
        }
    }
//    FOR(i,1,n) printf("%d ",i);puts("<  i");
//    FOR(i,1,n) printf("%d ",fa[i]);puts("<  FA");
//    FOR(i,1,n) printf("%d ",ls[i]);puts("<   ls");
//    FOR(i,1,n) printf("%d ",rs[i]);puts("<   rs");
    while(q--){
        int x;
        scanf("%d",&x);
        if (ls[x]) add(ls[x],rs[x],1);
        if (fa[x]) add(id[fa[x]],id[fa[x]],1);
        val[x]++;val[x]-=edge[x].size();
        LL ans=val[x];
        ans+=query(id[x],id[x]);
        if (ls[x]) ans+=query(ls[x],rs[x]);
        if (fa[x]) ans+=query(id[fa[x]],id[fa[x]]);
        printf("%lld\n",ans);
    }
}
/*
4 10
1 2
1 3
3 4
1
2
3
4
1
2
*/
