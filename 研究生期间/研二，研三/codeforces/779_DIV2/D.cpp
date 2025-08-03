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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
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

int ALL=(1<<20)-1;
vector<int> value[18];
pii solve(int l,int r,int depth) {//return: must-0, must-1;
    int k,c0=0,c1=0,n1=0,o=0;
    pii ret={ALL,0};
    if (l>r||depth==-1||!value[depth].size()) return ret;
    int l0=r+1,r0=l-1,l1=r+1,r1=l-1;
    FOR(k,l,r) {
        int o=(k>>depth)&1;
        if (o) c1++; else c0++;
        if (o==0) min_(l0,k),max_(r0,k);
        if (o==1) min_(l1,k),max_(r1,k);
    }
    if (c0!=c1) {
        for (int k:value[depth]) if (((k>>depth)&1)==1) n1++;
        if (n1==c1) ret.first^=1<<depth,o=0; //must-zero
        else ret.second^=1<<depth,o=1;
    }
    if (depth==0) return ret;
    value[depth-1].clear();
    for (int k:value[depth]) {
        int _k=k&~(1<<depth);
        if (((k>>depth)&1)==o) value[depth-1].push_back(_k);
        // else downr.push_back(_k);
    }
    pii pl=solve(l0,r0,depth-1);
    ret.first&=pl.first; ret.second|=pl.second;
    value[depth-1].clear();
    for (int k:value[depth]) {
        int _k=k&~(1<<depth);
        if (((k>>depth)&1)==o) continue; // value[depth-1].push_back(_k);
        else value[depth-1].push_back(_k);
    }
    pii pr=solve(l1,r1,depth-1);
    ret.first&=pr.first; ret.second|=pr.second;
    // printf("c0,c1,n1=%d %d %d\n",c0,c1,n1);
    // printf("solve %d %d; ans=%d %d; depth=%d\n",l,r,ret.first,ret.second,depth);
    // for (int k:v) printf("%d ",k); puts("<- k");
    return ret;
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int l,r,i; scanf("%d%d",&l,&r);
        // vector<int> V;
        value[16].clear();
        FOR(i,l,r) {
            int x; scanf("%d",&x);
            value[16].push_back(x);
        }
        // int MAXk=0;
        // while ((1<<MAXk)<=r) MAXk++;
        pii ans=solve(l,r,16);
        printf("%d\n",ans.second&ans.first);
    }

}
/*
*/