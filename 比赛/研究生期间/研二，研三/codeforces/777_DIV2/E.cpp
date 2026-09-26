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
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

int Ans[maxn];
int A[maxn],B[maxn],ind[maxn];
int kid[maxn],tmp[maxn]; //poww
int newcnt,runcnt;
priority_queue<int,vector<int>,greater<int> > Cnt[maxn];
priority_queue<int,vector<int>,greater<int> > Q;
int main() {
    int n,i; scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]),ind[A[i]]++; //ind=0: remove
    FOR(i,1,n) scanf("%d",&B[i]);
    FOR(i,1,n) if (ind[i]==0) newcnt++;
    FOR(i,1,n) if (B[i]>n) runcnt=max(runcnt,(B[i]-n)/newcnt);
    // if (runcnt==0) {FOR(i,1,n) printf("%d ",B[i]); return 0;} // no operation
    // printf("runcnt=%d; newcnt=%d\n",runcnt,newcnt);
    FOR(i,1,n) kid[i]=A[i],A[i]=i;
    for (;runcnt;runcnt>>=1) { // k times
        int v;
        if (runcnt&1) {
            FOR(v,1,n) tmp[v]=A[kid[v]];
            FOR(v,1,n) A[v]=tmp[v];
        } FOR(v,1,n) tmp[v]=kid[kid[v]];
        FOR(v,1,n) kid[v]=tmp[v];
    }
    // FOR(i,1,n) printf("%d%c",A[i]," \n"[i==n]);
    // A[f(i)] >= B[i]
    FOR(i,1,n) Cnt[B[A[i]]].push(i); Cnt[n+1].push(n+1);
    int nowpos=1; //already_done
    FOR(i,1,n+1) if (Cnt[i].size()) {
        // printf("i=%d; %d; %d\n",i,Cnt[i].size(),Q.size());
        while (nowpos<i) {
            // if (Cnt[i].size()==1||(Q.size()&&Cnt[i].top()>Q.top())) {
            Ans[Q.top()]=nowpos; nowpos++; Q.pop();
            // } else {
            //     Ans[Cnt[i].top()]=nowpos; nowpos++; Cnt[i].pop();
            // }
        } Ans[Cnt[i].top()]=nowpos; nowpos++; Cnt[i].pop();
        while (Cnt[i].size()) Q.push(Cnt[i].top()),Cnt[i].pop();
        // int j; FOR(j,1,n) printf("%d%c",Ans[j]," \n"[j==n]);
    }
    FOR(i,1,n) printf("%d%c",Ans[i]," \n"[i==n]);
    // while () Ans[Q.top()]=nowpos; nowpos++; Q.pop();
}
/*
*/