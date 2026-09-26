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
 
#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e4+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[maxn];
int R[maxn][17][37];
int Merge[maxn][17][37];//ST
int Log2[maxn];
int now[37];//k-integer-r-max
inline int GetValue(int l,int r,int k) {
    int e=Log2[r-l+1];
    // if (k<4) printf("V0: %d->%d: %d\n",l,r,max(Merge[l][e][k],Merge[r-(1<<e)+1][e][k]));
    return max(Merge[l][e][k],Merge[r-(1<<e)+1][e][k]);
}
inline int GetValueMore(int l,int A[],int k) {
    int ret=0,_k;
    FOR(_k,0,k) ret=max(ret,GetValue(l,A[_k],k-_k));//left-lastchoose
    return ret;
}
pair<pii,int> Q[maxn];
int ans[maxn],q_ans[maxn][37];
int main() {
    int i,j,n,m,o,_k,_;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,2,n) Log2[i]=Log2[i>>1]+1;
    // FOR(i,1,n) printf("%d(%d) ",i,Log2[i]); puts("<-");
    // FOR(i,0,n) printf("%d:(%d) ",i,Log2[i]); puts("<-L");
    FOR(i,1,n) FOR(_k,0,30) R[i][0][_k]=min(i+A[i]+_k,n);
    REP(o,16) {//length
        rFOR(i,1,n) {
            FOR(_k,0,30) Merge[i][0][_k]=R[i][o][_k];
            REP(j,16) FOR(_k,0,30) Merge[i][j+1][_k]=max(Merge[i][j][_k],Merge[min(n,i+(1<<j))][j][_k]);
            FOR(_k,0,30) R[i][o+1][_k]=GetValueMore(i,R[i][o],_k);
        }
    }
    // REP(j,6) FOR(_k,0,2) {
    //     printf("calc %d %d\n",j,_k);
    //     FOR(i,1,n) printf("%d%c",R[i][j][_k]," \n"[i==n]);
    // }
    FOR(_,1,m) scanf("%d%d%d",&Q[_].first.first,&Q[_].first.second,&Q[_].second);
    FOR(_,1,m) if (Q[_].first.first!=Q[_].first.second) ans[_]=1;
    FOR(_,1,m) FOR(_k,0,30) q_ans[_][_k]=Q[_].first.first;
    rREP(o,16) {//length
        rFOR(i,1,n) {
            FOR(_k,0,30) Merge[i][0][_k]=R[i][o][_k];
            REP(j,16) FOR(_k,0,30) Merge[i][j+1][_k]=max(Merge[i][j][_k],Merge[min(n,i+(1<<j))][j][_k]);
        }
        FOR(_,1,m) {
            int l=Q[_].first.first,r=Q[_].first.second,k=Q[_].second;
            // FOR(_k,0,30) printf("%d ",GetValueMore(l,q_ans[_],_k)); printf("<- _k; i=%d; o=%d; ans=%d\n",_,o,ans[_]);
            // FOR(_k,0,30) printf("%d ",q_ans[_][_k]); puts("<- q-ans");
            if (GetValueMore(l,q_ans[_],k)<r) {
                ans[_]+=1<<o;
                rFOR(_k,0,30) q_ans[_][_k]=GetValueMore(l,q_ans[_],_k);
            }
        }
    }
    FOR(i,1,m) printf("%d%c\n",ans[i]," \n"[i==m]);
}
/*
20 1
1 1 3 2 1 1 1 1 2 2 2 3 1 2 1 3 2 3 1 3
2 20 1


20 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 20 1
*/