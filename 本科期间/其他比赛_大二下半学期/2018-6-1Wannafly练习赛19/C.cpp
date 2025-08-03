#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5000+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int _x[17],_y[17];
int ans;
int n,m,k;
void dfs(int x,int y,int chosen){
//    printf("%d %d %d\n",x,y,chosen);
    if (chosen==k){
        int i,j;
        FOR(i,1,k) FOR(j,i+1,k){
            if (abs(_x[i]-_x[j])+abs(_y[i]-_y[j])==1)
                return;
        }ans++;
        return;
    }while (1){
        y++;
        if (y==m+1) y=1,x++;
        if (x==n+1) break;
        _x[chosen+1]=x;_y[chosen+1]=y;
        dfs(x,y,chosen+1);
    }
}
int main() {
    int q;
    scanf("%d",&q);
    while (q--){
        scanf("%d%d%d",&n,&m,&k);
        ans=0;
        dfs(1,0,0);
        printf("%d\n",ans%420047);
    }
    return 0;
}
/*
*/
