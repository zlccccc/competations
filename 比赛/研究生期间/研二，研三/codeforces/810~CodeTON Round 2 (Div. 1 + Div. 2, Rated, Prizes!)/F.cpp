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

int sg[maxn],cnt[maxn];
void init() {
    int i,j;
    FOR(i,2,1000000) {
        if (i>200) {sg[i]=sg[i-34]; continue;}
        int nowsg=0;
        FOR(j,0,i*2) cnt[j]=0;
        FOR(j,1,i-1) cnt[sg[j-1]^sg[i-j-1]]++;
        while (cnt[nowsg]) nowsg++;
        sg[i]=nowsg;
        // printf("%d : %d,%d\n",i,nowsg,cnt[nowsg-1]);
    }
}
char str[maxn];
int main() {
    init();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i,k;
        scanf("%d",&n);
        scanf("%s",str+1);
        int r=0,b=0;
        FOR(i,1,n) if (str[i]=='R') r++; else b++;
        if (r>b) {puts("Alice"); continue;}
        if (r<b) {puts("Bob"); continue;}
        int ans=0,cnt=0;
        FOR(i,1,n+1) {
            if (i==n+1||str[i]==str[i-1]) {
                ans^=sg[cnt];
                // printf("cnt=%d; ans=%d\n",cnt,ans);
                cnt=0;
            } cnt++;
        }
        if (ans) puts("Alice");
        else puts("Bob");
    }
}