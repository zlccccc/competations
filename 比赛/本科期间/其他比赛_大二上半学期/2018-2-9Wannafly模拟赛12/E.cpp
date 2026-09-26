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

int n,m;
int i,j,k;
int a[maxn],b[maxn],id[maxn],MAX,MIN;
char ans[maxn];
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]),b[i]=a[i];
    FOR(i,1,n) scanf("%d",&k),id[k]=i;
    FOR(i,1,n) a[i]=id[a[i]];
//    FOR(i,1,n) printf("%d ",a[i]);puts("");
    FOR(i,1,n) ans[i]='1';
    FOR(i,1,n){
        MAX=max(MAX,a[i]);
        if (i<=a[i]&&MAX<=a[i]) ans[b[i]]='0';
    }MIN=n;
    rFOR(i,1,n){
        MIN=min(MIN,a[i]);
        if (i>=a[i]&&MIN>=a[i]) ans[b[i]]='0';
    }ans[n+1]=0;
    puts(ans+1);
}
/*
*/
