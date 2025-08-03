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
const LL maxn=1e5+7;
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

typedef unsigned int UI;
struct node{
    UI sum[8],lazy[3];
}T[maxn*4];
void build(int x,int L,int R){
    int mid=(L+R)/2,i;
    REP(i,8) T[x].sum[i]=0;
    REP(i,3) T[x].lazy[i]=0;
    T[x].sum[0]=R-L+1;
    if (L==R) return;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
}vector<int> ids[3];
void change(int x,int k,UI val){
    T[x].lazy[k]+=val;
    for (int i:ids[k]) T[x].sum[i]+=T[x].sum[i^(1<<k)]*val;
}void pushup(int x){
    int i;
    REP(i,8) T[x].sum[i]=T[x<<1].sum[i]+T[x<<1|1].sum[i];
}void pushdown(int x){
    int i;
    REP(i,3) if (T[x].lazy[i]){
        change(x<<1,i,T[x].lazy[i]);
        change(x<<1|1,i,T[x].lazy[i]);
        T[x].lazy[i]=0;
    }
}
void update(int x,int k,UI val,int l,int r,int L,int R){
    int mid=(L+R)/2;
    if (l<=L&&R<=r){
        change(x,k,val);
        return;
    }pushdown(x);
    if (l<=mid) update(x<<1,k,val,l,r,L,mid);
    if (mid<r) update(x<<1|1,k,val,l,r,mid+1,R);
    pushup(x);
}
pair<int,UI> S[6][maxn];
int top[6];
void push(int k,UI val,int i,int n){
    int now=i;
    while (top[k]&&S[k][top[k]].second<val){
        debug("update2: %d %d  %d -> %d  (%u %u)\n",k,val-S[k][top[k]].second,S[k][top[k]].first,now-1,val,S[k][top[k]].second);
        update(1,k%3,val-S[k][top[k]].second,S[k][top[k]].first,now-1,1,n);
        now=S[k][top[k]].first; top[k]--;
    }S[k][++top[k]]=make_pair(now,val);
    val=-val;k+=3;now=i;
    while (top[k]&&S[k][top[k]].second<val){
        debug("update2: %d %d  %d -> %d  (%u %u)\n",k,val-S[k][top[k]].second,S[k][top[k]].first,now-1,val,S[k][top[k]].second);
        update(1,k%3,val-S[k][top[k]].second,S[k][top[k]].first,now-1,1,n);
        now=S[k][top[k]].first; top[k]--;
    }S[k][++top[k]]=make_pair(now,val);
}
UI A[maxn][3];
UI solve(int n){
    UI ret=0;
    int i,k;
    build(1,1,n);
    FOR(i,1,n){
        REP(k,3) push(k,A[i][k],i,n);
        ret+=T[1].sum[7];
        debug("%d: %d\n",i,T[1].sum[7]);
    }return ret;
}
void TaskA(){
    UI ans=0;
    int n,i,j;
    scanf("%d",&n);
    REP(j,3) FOR(i,1,n) scanf("%u",&A[i][j]);
    ans=solve(n);
    printf("%u\n",ans);
}
int main() {
    int T=1,k,i;
    REP(k,3) REP(i,8) if ((i>>k)&1) ids[k].push_back(i);
//    scanf("%d",&T);
    while (T--) TaskA();
}
/*
5
1 3 5 5 5
2 3 2 1 2
3 5 5 3 5
*/
