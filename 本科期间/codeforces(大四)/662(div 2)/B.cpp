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

int cnt[maxn];
int more[10];
void update(int x,int k,int val) {
    if (cnt[x]>=k) more[k]--;
    cnt[x]+=val;
    if (cnt[x]>=k) more[k]++;
}
void update(int x,int val) {
    update(x,2,val); cnt[x]-=val;
    update(x,4,val); cnt[x]-=val;
    update(x,6,val); cnt[x]-=val;
    update(x,8,val); cnt[x]-=val;
    cnt[x]+=val;
}
char s[3];
bool check() {
    // printf("%d %d %d %d   %d %d\n",more[2],more[4],more[6],more[8],cnt[1],cnt[2]);
    if (more[8]>=1) return 1;
    if (more[6]>=1&&more[2]>=2) return 1;
    if (more[4]>=1&&more[2]>=3) return 1;
    if (more[4]>=2) return 1;
    return 0;
}
int main() {
    // int i; FOR(i,31,46) solve(i);
    int _T,_; _T=1;
    // scanf("%d",&_T);
    FOR(_,1,_T){
        int i;
    	int n; scanf("%d",&n);
        FOR(i,1,n) {
            int v; scanf("%d",&v);
            update(v,1);
        } int m,k; scanf("%d",&m);
        FOR(i,1,m) {
            scanf("%s%d",s,&k);
            if (s[0]=='+') update(k,1);
            else update(k,-1);
            if (check()) puts("YES");
            else puts("NO");
        }
    }
}
/*

*/