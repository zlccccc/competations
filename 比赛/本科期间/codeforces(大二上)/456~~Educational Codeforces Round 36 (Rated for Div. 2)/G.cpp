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
const LL M=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
int p[maxn],mark[maxn],tot;
int mu[maxn];
int f[maxn],g[maxn];
int ans;
int main(){
    scanf("%d%d",&n,&k);
    mu[1]=1;
    FOR(i,2,k){
        if (!mark[i]) p[tot++]=i,mu[i]=-1;
        REP(j,tot){
            if (i*p[j]>k) break;
            mark[i*p[j]]=1;
            if (i%p[j]==0) break;
            else mu[i*p[j]]=-mu[i];
        }
    }FOR(i,1,k) f[i]=powMM(i,n);
    FOR(i,1,k) if (mu[i])
        for (j=i;j<=k;j+=i) (g[j]+=(mu[i]*(f[j/i]-f[j/i-1])%M+M)%M)%=M;
//    FOR(i,1,k) printf("%d ",f[i]);puts("");
//    FOR(i,1,k) printf("%d ",g[i]);puts("");
    FOR(i,1,k) (g[i]+=g[i-1])%=M;
    FOR(i,1,k) (ans+=g[i]^i)%=M;
    printf("%d\n",ans);
}
/*
*/
