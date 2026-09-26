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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
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

int a,b;
int id[maxn];
int main() {
    int n,k,i,j,t;
    scanf("%d%d",&n,&k);//maximum:k
    REP(i,256) id[i]=-1;
    REP(t,n) {
        int val,now;
        scanf("%d",&val);now=val;
        if (id[val]!=-1){
            printf("%d ",id[val]);
            continue;
        }
        REP(i,k){
            now--;
            if (now==-1||id[now]!=-1) break;
        }if (now!=-1&&id[now]!=-1&&val-id[now]+1<=k){
            id[val]=id[now];
        }else id[val]=now+1;
        FOR(i,id[val],val) id[i]=id[val];
        printf("%d ",id[val]);
    }
    return 0;
}
/*
5 2
3 2 1 255 254
*/
