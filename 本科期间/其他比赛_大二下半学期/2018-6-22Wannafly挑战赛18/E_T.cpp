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
    UI sum[8],MAX[3],MIN[3],lazy[3];
}T[maxn*4];
void build(int x,int L,int R){
    int mid=(L+R)/2,i;
    T[x].sum[0]=R-L+1;T[x].sum[7]=0;
    REP(i,3) T[x].lazy[i]=T[x].MIN[i]=T[x].MAX[i]=0;
    if (L==R) return;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
}vector<int> ids[3];
void change(int x,int k,UI val){
    T[x].lazy[k]=T[x].MAX[k]=T[x].MIN[k]=val;
    for (int i:ids[k]) T[x].sum[i]=T[x].sum[i^(1<<k)]*T[x].lazy[k];
//    debug("change : %d %d %u\n",x,k,val);
//    for (int i:ids[k]) debug("%d(%u) ",i,T[x].sum[i]);deputs("");
//    for(int i=0;i<8;i++) debug("%d(%u) ",i,T[x].sum[i]);deputs("");
}void pushup(int x){
    int i;
    REP(i,8) {
        T[x].sum[i]=T[x<<1].sum[i]+T[x<<1|1].sum[i];
    }REP(i,3){
        T[x].MAX[i]=max(T[x<<1].MAX[i],T[x<<1|1].MAX[i]);
        T[x].MIN[i]=min(T[x<<1].MIN[i],T[x<<1|1].MIN[i]);
    }
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
//        debug("update: %d %d %u %d %d\n",x,k,val,L,R);
        if (val<=T[x].MIN[k]) return;
        if (val>=T[x].MAX[k]){
            change(x,k,val);
            return;
        }
    }pushdown(x);
    if (l<=mid) update(x<<1,k,val,l,r,L,mid);
    if (mid<r) update(x<<1|1,k,val,l,r,mid+1,R);
    pushup(x);
}
UI A[maxn][3];
UI solve(int n){
    UI ret=0;
    int i,k;
    build(1,1,n);
    FOR(i,1,n){
        REP(k,3) update(1,k,A[i][k],1,i,1,n);
        ret+=T[1].sum[7];
        debug("%d: %d\n",i,T[1].sum[7]);
    }return ret;
}
UI solve2(int n){
    int i,j,k;
    UI ans=0;
    FOR(i,1,n){
        UI MAX[3]={0,0,0};
        UI now=0;
        printf("this: %d %d %d  ",A[i][0],A[i][1],A[i][2]);
        rFOR(j,1,i) {
            REP(k,3) MAX[k]=max(MAX[k],A[j][k]);
            now+=MAX[0]*MAX[1]*MAX[2];
            debug("%d+ ",MAX[0]*MAX[1]*MAX[2]);
        }debug("%d: %d\n",i,now);
        ans+=now;
    }return ans;
}
void TaskA(){
    UI ans=0;
    int n,i,j;
    scanf("%d",&n);
    REP(j,3) FOR(i,1,n) scanf("%u",&A[i][j]);
//    solve(n);
    for (int x=-1;x<=1;x+=2){
        for (int y=-1;y<=1;y+=2){
            for (int z=-1;z<=1;z+=2){
                FOR(i,1,n) A[i][0]*=x;
                FOR(i,1,n) A[i][1]*=y;
                FOR(i,1,n) A[i][2]*=z;
                ans+=solve(n);
                FOR(i,1,n) A[i][0]*=x;
                FOR(i,1,n) A[i][1]*=y;
                FOR(i,1,n) A[i][2]*=z;
            }
        }
    }
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
