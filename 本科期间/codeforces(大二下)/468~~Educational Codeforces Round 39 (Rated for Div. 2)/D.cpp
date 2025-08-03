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

int n,m,K;
int i,j,k;
int ans;
char a[507][507];
int f[507],g[507];
int main(){
    scanf("%d%d%d",&n,&m,&K);
    REP(i,n) scanf("%s",a[i]);
    REP(i,n){
        int all=0;
        REP(j,m) if (a[i][j]=='1') all++;
        FOR(j,0,all) g[j]=0;g[all]=m;
        REP(j,m){
            int now=all;
            rep(k,j,m){
                if (a[i][k]=='1') now--;
                g[now]=max(g[now],m-(k-j+1));//in-class
//                printf("%d->%d %d\n",j,k,now);
            }
        }
//        FOR(j,0,all) printf("%d ",g[j]);puts("");
        rFOR(j,0,K){
            rFOR(k,0,all) f[j+k]=max(f[j+k],f[j]+g[k]);
        }
    }printf("%d\n",n*m-f[K]);
}
/*
*/
