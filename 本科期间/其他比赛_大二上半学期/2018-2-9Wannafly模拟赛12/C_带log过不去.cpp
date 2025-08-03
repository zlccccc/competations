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
const LL M=998244353;
const LL maxn=7e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int Ng,n,i,j,k;
int A[maxn];
int tot;
int nxt[maxn],pre[maxn],id[maxn];
LL ans,MAX;int len;
bool cmp(int i,int j){
    return A[i]<A[j];
}
int main(){
    scanf("%d%d",&Ng,&n);
    FOR(i,1,Ng){
        LL Ns,s,a,b,mod;
        scanf("%lld%lld%lld%lld%lld",&Ns,&s,&a,&b,&mod);
        A[++tot]=s;Ns--;s%=mod;
        while (Ns--){
            LL tmp=(1ll*A[tot]*a%mod+b)%mod;
            if (tmp==0) A[++tot]=mod;
            else A[++tot]=tmp;
        }
    }
    FOR(i,0,n+1) pre[i]=i-1,nxt[i]=i+1,id[i]=i,MAX=max(MAX,1ll*A[i]);
    sort(id+1,id+n+1,cmp);
//    FOR(i,1,n) printf("%d ",A[i]);puts("");
//    FOR(i,1,n) printf("%d ",id[i]);puts("");
    ans=MAX*n;
    FOR(i,1,n-1){
        int x=id[i];
        nxt[pre[x]]=nxt[x];
        pre[nxt[x]]=pre[x];
        len=max(len,nxt[x]-pre[x]+1);
        len=max(len,nxt[0]-1+n-pre[n+1]);
//        printf("%d %d %d; %lld\n",i,x,len,len*A[x]+(n-len)*MAX),
        ans=min(ans,1ll*len*A[x]+(n-len)*MAX);
    }
    printf("%lld\n",ans);
}
/*
3 7
3 3 1 0 514
3 7 1 0 514
1 9 1 0 514
*/
