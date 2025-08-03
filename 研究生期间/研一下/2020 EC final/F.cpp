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

vector<int> V;
int getid(int x) {return lower_bound(V.begin(),V.end(),x)-V.begin()+1;}
set<pii> S[maxn];
int A[maxn][2],B[maxn][2];
char SA[maxn],SB[maxn];
void solve(int n1,int n2) {
    int i;
    V.clear();
    FOR(i,1,n1) V.push_back(A[i][0]);
    FOR(i,1,n2) V.push_back(B[i][0]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(), V.end()),V.end());
    FOR(i,0,n1+n2) S[i].clear();
    FOR(i,1,n1) A[i][0]=getid(A[i][0]);
    FOR(i,1,n2) B[i][0]=getid(B[i][0]);
    FOR(i,1,n1) S[A[i][0]].insert(make_pair(A[i][1],0));
    FOR(i,1,n2) S[B[i][0]].insert(make_pair(B[i][1],1));
    FOR(i,1,n1) {
        auto it=S[A[i][0]].lower_bound(make_pair(A[i][1],0));
        it++; if (it!=S[A[i][0]].end()&&(*it).second==1) SA[i]='1'; it--;
        if (it!=S[A[i][0]].begin()) {it--; if ((*it).second==1) SA[i]='1'; it++;}
    }
    FOR(i,1,n2) {
        auto it=S[B[i][0]].lower_bound(make_pair(B[i][1],0));
        it++; if (it!=S[B[i][0]].end()&&(*it).second==0) SB[i]='1'; it--;
        if (it!=S[B[i][0]].begin()) {it--; if ((*it).second==0) SB[i]='1'; it++;}
    }
}
int main() {
    int n1,n2;
    int i;
    scanf("%d%d",&n1,&n2);
    FOR(i,1,n1) scanf("%d%d",&A[i][0],&A[i][1]),SA[i]='0';
    FOR(i,1,n2) scanf("%d%d",&B[i][0],&B[i][1]),SB[i]='0';
    solve(n1,n2);
    FOR(i,1,n1) swap(A[i][0],A[i][1]);
    FOR(i,1,n2) swap(B[i][0],B[i][1]);
    solve(n1,n2);
    // FOR(i,1,n1) printf("  %d %d\n",A[i][0],A[i][1]);
    // FOR(i,1,n2) printf("  %d %d\n",B[i][0],B[i][1]);
    printf("%s\n",SA+1);
    printf("%s\n",SB+1);
}
/*
*/