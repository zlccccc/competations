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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
int f[1<<21|7],ans;
inline int lowbit(int x){return x&-x;}
int main(){
    scanf("%d%d",&n,&m);
    REP(i,n) scanf("%d",&k),f[1<<i]=k;
    REP(i,(1<<n)) f[i]=min(m,f[lowbit(i)]+f[i^lowbit(i)]);
    REP(i,(1<<n)) if (f[i]<m){
        int mark=0,flag=0;
        REP(j,n){
            int k=i|(1<<j);if (k==i) continue;
            if (f[i|(1<<j)]>=m) mark=1;
            else flag=1;
        }if (!flag) ans+=mark;
    }if (f[(1<<n)-1]<m) ans++;
    printf("%d\n",ans);
}
/*
*/
