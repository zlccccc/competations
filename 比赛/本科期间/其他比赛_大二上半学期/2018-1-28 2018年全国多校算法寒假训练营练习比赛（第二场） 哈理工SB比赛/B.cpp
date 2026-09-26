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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,h,i,j,k;
int f[507],ans;
int w[maxn],v[maxn];
int main(){
    while (~scanf("%d%d%d",&n,&m,&h)&&n!=0){
        m+=h;ans=0;
        FOR(i,1,n) scanf("%d%d",&w[i],&v[i]);
        FOR(i,0,m) f[i]=0;
        FOR(j,1,n)
            rFOR(i,0,m) f[i+w[j]]=max(f[i+w[j]],f[i]+v[j]);
        FOR(i,0,m) ans=max(ans,f[i]);
        if (h>0){
            m--;
            FOR(k,1,n){
                ans=max(ans,v[k]);
                FOR(i,0,m) f[i]=0;
                FOR(j,1,n) if (j!=k)
                    rFOR(i,0,m) f[i+w[j]]=max(f[i+w[j]],f[i]+v[j]);
                FOR(i,0,m) ans=max(ans,v[k]+f[i]);
            }
        }
        printf("%d\n",ans);
    }
}
/*
*/
