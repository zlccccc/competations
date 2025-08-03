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
const LL M=998244353;
const LL maxn=1e5+107;
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

int getfa(int x,int A[]) {
    if (x==A[x]) return x;
    return A[x]=getfa(A[x],A);
}
void merge(int x,int y,int A[]) {
    x=getfa(x,A); y=getfa(y,A);
    if (x==y) return;
    A[x]=y;
}
int A[maxn],B[maxn];
vector<pii> ans,chk;
// set<int> SA[maxn],SB[maxn];
// set<pii> used;
void merge_all() {
    for (auto now:chk) {
        int i=now.first,j=now.second;
        if (getfa(i,A)!=getfa(j,A)&&getfa(i,B)!=getfa(j,B)) {
            merge(i,j,A);
            merge(i,j,B);
            ans.push_back(make_pair(i,j));
        }
    }
    chk.clear();
}
int main() {
    int n,m1,m2,i;
    scanf("%d%d%d",&n,&m1,&m2);
    FOR(i,1,n) A[i]=B[i]=i;
    FOR(i,1,m1) {
        int x,y;
        scanf("%d%d",&x,&y);
        merge(x,y,A);
    }
    FOR(i,1,m2) {
        int x,y;
        scanf("%d%d",&x,&y);
        merge(x,y,B);
    }
    // 错在while了, merge会update
    FOR(i,2,n) chk.push_back(make_pair(1,i));
    merge_all();
    int z=1;
    FOR(i,2,n) {
        while (getfa(z,A)==getfa(1,A)&&z<n) z++;
        chk.push_back(make_pair(z,i)); merge_all();
    }
    z=1;
    FOR(i,2,n) {
        while (getfa(z,B)==getfa(1,B)&&z<n) z++;
        chk.push_back(make_pair(z,i)); merge_all();
    }
    printf("%d\n",(int)ans.size());
    for (auto now:ans) printf("%d %d\n",now.first,now.second);
}
/*
8 1 2
4 5
7 8
5 6
*/