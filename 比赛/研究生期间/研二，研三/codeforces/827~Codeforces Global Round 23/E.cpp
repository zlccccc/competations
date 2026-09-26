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
#include <functional>
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
typedef array<int,4> ar4;

int cnt=0;
char str[3];
int query(basic_string<int> Q) {
    printf("? %d",(int)Q.size());
    for (int v:Q) printf(" %d",v); puts("");
    fflush(stdout);
    scanf("%s",str);
    if (str[0]=='Y') return 1;
    return 0;
}
bool guess(int val) {
    printf("! %d",val);
    puts("");
    fflush(stdout);
    scanf("%s",str);
    if (str[1]=='(') return 0;
    exit(0);
}
void solve(basic_string<int> S) {
    int n=S.size(),i;
    if (n<4) {
        if (n<=2) {
            if (guess(S[0])) return;
            if (guess(S[1])) return;
        } else {
            int a=query({S[0]}),b=query({S[1]});
            if (a&&b) {solve({S[0],S[1]}); return;}
            if (a&&!b) {solve({S[0],S[2]}); return;}
            if (!a&&b) {solve({S[1],S[2]}); return;}
            b=query({S[1]});
            a=query({S[0]});
            if (a&&!b) {solve({S[0],S[2]}); return;}
            if (!a&&b) {solve({S[1],S[2]}); return;}
            return solve({S[0],S[2]});
        }
        return;
    }
    basic_string<int> sub[4],real;
    REP(i,(int)S.size()) sub[i&3].push_back(S[i]);
    int rem=query(sub[0]+sub[1])*2;
    if (rem) real+=sub[0]+sub[1];
    else real+=sub[2]+sub[3];
    int nxt=query(sub[rem]);
    if (nxt) real+=sub[rem]; else real+=sub[rem^1];
    solve(real);
}
int calc(int x) {
    if (x<=3) return 2;
    return 3+calc(x-x/3);
}
int main() {
    int n=100000,i;
    printf("%d\n",calc(n));

    scanf("%d",&n);
    basic_string<int> V;
    FOR(i,1,n) V.push_back(i);
    solve(V);
    printf("%d\n",cnt);
}
/*
10
10
)(())))())
*/