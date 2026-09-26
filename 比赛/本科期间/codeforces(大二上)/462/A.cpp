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
#include <bitset>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int a[maxn];
int pre[maxn],suf[maxn];//pre_1,suf_2
int f[maxn][2];
int ans;
int main(){
    int i,j,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,n){
        pre[i]=pre[i-1];
        if (a[i]==1) pre[i]++;
    }rFOR(i,1,n){
        suf[i]=suf[i+1];
        if (a[i]==2) suf[i]++;
    }FOR(i,0,n) ans=max(ans,pre[i]+suf[i+1]);
    FOR(i,1,n){
        FOR(j,1,i+1) f[j][0]=f[j][1]=0;
        rFOR(j,1,i){
            f[j][1]=f[j+1][1];
            f[j][0]=f[j+1][0];
            if (a[j]==1) f[j][0]++;
            if (a[j]==2) f[j][1]++;
            f[j][1]=max(f[j][1],f[j][0]);
            ans=max(ans,f[j][1]+pre[j-1]+suf[i+1]);
//            printf("%d->%d %d %d\n",i,j,f[j][0],f[j][1]);
        }
    }
    printf("%d\n",ans);
}
/*
*/
