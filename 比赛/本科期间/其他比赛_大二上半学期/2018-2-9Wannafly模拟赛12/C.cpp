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
int S[maxn],L[maxn],R[maxn],top;
LL ans,MAX,now;
int main(){
    scanf("%d%d",&Ng,&n);
    FOR(i,1,Ng){
        LL Ns,s,a,b,mod;
        scanf("%lld%lld%lld%lld%lld",&Ns,&s,&a,&b,&mod);
        A[++tot]=s;Ns--;s%=mod;
        while (Ns--){
            LL tmp=((LL)A[tot]*a%mod+b)%mod;
            if (tmp==0) A[++tot]=mod;
            else A[++tot]=tmp;
        }
    }FOR(i,1,n) MAX=max(MAX,(LL)A[i]);
    ans=MAX*n;
    FOR(i,1,n){
        while (top&&A[S[top]]<A[i]) R[S[top--]]=i-1;
        S[++top]=i;
    }while (top) R[S[top--]]=n;
    rFOR(i,1,n){
        while (top&&A[S[top]]<A[i]) L[S[top--]]=i+1;
        S[++top]=i;
    }while (top) L[S[top--]]=1;
//    FOR(i,1,n) printf("%d %d %lld\n",L[i],R[i],A[i]*(R[i]-L[i]+1)+MAX*(n-(R[i]-L[i]+1)));
    FOR(i,1,n) ans=min(ans,A[i]*(R[i]-L[i]+1)+MAX*(n-(R[i]-L[i]+1)));
    int l=1,r=n;
    while (l<=r){
//        printf("%d-%d num=%d:f,s=%lld %lld  %lld\n",l,r,l+n-r+1,f[l],s[r],max(f[l],s[r])*(l+n-r+1)+MAX*(r-l+1));
        ans=min(ans,now*(n-(r-l+1))+MAX*(r-l+1));
        if (A[l]<A[r]) now=max(now,(LL)A[l++]);
        else now=max(now,(LL)A[r--]);
    }
    printf("%lld\n",ans);
}
/*
3 7
3 3 1 0 514
3 7 1 0 514
1 9 1 0 514
*/
