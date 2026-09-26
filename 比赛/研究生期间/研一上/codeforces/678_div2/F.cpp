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

ll kth[maxn];
ll freq[maxn];
int main() {
	int i,n; scanf("%d",&n);
    FOR(i,1,n) {
        int a,f; scanf("%d%d",&a,&f);
        freq[a]+=f;
    }
    kth[1]=1; int ans=0;
    FOR(i,1,100000) {
        ll a1=0,a2=0; ll cnt=0;
        for (int j=i;j<=100000;j+=i) {
            if (j!=i) add_(kth[j],M-kth[i]);
            add_(a1,freq[j]%M*j%M);
            add_(a2,freq[j]%M*j%M*j%M);
            cnt+=freq[j];
        } if (cnt<=1) continue;
        ll axy=(a1*a1%M-a2+M)%M;
        // printf("a2, axy = %lld %lld  < a\n",a2,axy);
        // ll base=(powMM(2ll,cnt-1)+M-1)%M;
        ll nowval=0;
        ll base1=(cnt-1)%M*powMM(2,cnt-2)%M;
        ll base2=(powMM(2,cnt-2));
        if (cnt>=3) base2+=(cnt-2)%M*powMM(2,cnt-3)%M;
        add_(nowval,a2*base1%M);
        add_(nowval,axy*base2%M);
        // printf("%d : %lld\n",i,nowval);
        add_(ans,nowval*kth[i]%M);
    }
	printf("%d\n",ans);
}
/*
*/