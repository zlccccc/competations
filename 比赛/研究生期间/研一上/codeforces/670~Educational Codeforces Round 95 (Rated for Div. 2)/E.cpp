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

int A[maxn],B[maxn];
ll sleft[maxn],sright[maxn];
int value(int n,int x,int y) {
    int i; ll all=0;
    FOR(i,1,n) B[i]=i;
    do {
        int _x=x,_y=y;
        FOR(i,1,n) {
            if (!_x) {
                if (A[B[i]]>=_y) add_(all,A[B[i]]);
                if (A[B[i]]<_y) add_(all,A[B[i]]);
            } else if (A[B[i]]>=_y) _x--;
        }
        FOR(i,1,n) printf("%d ",B[i]); printf ("<- B: %d\n",all);
    } while (next_permutation(B+1,B+1+n));
    FOR(i,1,n) all=all*powMM(i,M-2)%M;
    return all;
}
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    sort(A+1,A+1+n);
    FOR(i,1,n) sleft[i]=sright[i]=A[i]%M;
    FOR(i,1,n) add_(sleft[i],sleft[i-1]);
    rFOR(i,1,n) add_(sright[i],sright[i+1]);
    FOR(i,1,m) {
        int x,y; scanf("%d%d",&x,&y);
        // printf("bruteforce %d\n",value(n,x,y));
        int pos=lower_bound(A+1,A+1+n,y)-A-1;
        // printf("pos=%d  %d \n",pos,sleft[pos]);
        if (n-pos<x) {puts("0"); continue;}//all defend
        int ans=0;
        add_(ans,sright[pos+1]*(n-pos-x)%M*powMM(n-pos,M-2)%M);
        add_(ans,sleft[pos]*(n-pos+1-x)%M*powMM(n-pos+1,M-2)%M);
        printf("%d\n",ans);
    }
}
/*
4 100
2 4 5 7
1 3
*/