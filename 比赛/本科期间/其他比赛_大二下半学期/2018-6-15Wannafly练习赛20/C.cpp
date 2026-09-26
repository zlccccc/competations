#include <sstream>
#include <fstream>
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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1<<24|7;
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

int nxt[maxn],d[maxn];//nxt=fa
int len[maxn];
queue<int> Q;
int main() {
    int m,i;
    int T=1;
    scanf("%d",&T);
    while (T--){
        int n,m,a,b,c,i;
        scanf("%d%d%d%d",&a,&b,&c,&n);
        REP(i,n) nxt[i]=((LL)a*i%n*i+(LL)b*i+c)%n,d[i]=0;
        REP(i,n) d[nxt[i]]++,len[i]=1;
        REP(i,n) if (!d[i]) Q.push(i);
//        REP(i,n) printf("%d ",nxt[i]);
        int ans=0;
        while(Q.size()){
            int x=Q.front();Q.pop();
            d[nxt[x]]--; if (!d[nxt[x]]) Q.push(nxt[x]);
            len[nxt[x]]=max(len[x]+1,len[nxt[x]]);
            ans=max(ans,len[nxt[x]]);
        }
        REP(i,n) if (d[i]){
            int cnt=0,mx=0;
            for (int j=i;d[j];j=nxt[j]){
                mx=max(mx,len[j]);cnt++;d[j]=0;
            }ans=max(ans,mx+cnt-1);
        }
        printf("%d\n",ans);
    }
}
/*
*/
