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
#include <unordered_map>
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
const LL maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=32) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

int value[maxn];
void back(int x) {
    int i;
    FOR(i,0,x) value[i]=0; value[x]=1;
    rFOR(i,32,x) if (value[i]) {
        value[i-6]^=1; value[i-17]^=1;
        value[i-25]^=1; value[i-32]^=1;
    }
    REP(i,32) if (value[i]) printf("%d ",i); puts("");
}
const unsigned xo=(1<<0)|(1<<7)|(1<<15)|(1<<26);
unsigned nxt(unsigned x) {
    if (x&(1<<31)) x=((x^(1<<31))<<1)^xo;
    else x=x<<1;
    // int i;
    // REP(i,32) if ((x>>i)&1) printf("%d ",i); puts(" <- getnxt");
    return x;
}
unsigned noww;
unsigned tmp[32];
unsigned nxt(unsigned x,unsigned y) {//multi y
    tmp[0]=x; unsigned ret=0; int i;
    if (noww!=x) {
        rep(i,1,32) tmp[i]=nxt(tmp[i-1]);
        noww=x;
    }
    REP(i,32) if ((y>>i)&1) ret^=tmp[i];
    return ret;
}
char str[maxn]="x^31+x^25+x^14+x^6";
unordered_map<unsigned,unsigned> MP;
int main() {
    // int k=clock();
    ll i;
    // back(64);
    value[0]=1;
    FOR(i,1,65536) value[i]=nxt(value[i-1]);
    // pr2(value[64]); puts("");
    // pr2(value[80]); puts("");
    // pr2(value[64+80]);
    // pr2(nxt(value[64],value[80]));
    unsigned tmp=value[65535];
    REP(i,65536) {
        MP[tmp]=i*65536+65535;
        tmp=nxt(tmp,value[65536]);
        // pr2(tmp); puts("");
        // printf("%lld %lld\n",value[i*80],tmp);
    }
    // printf("%d\n",clock()-k);
    // pr2(value[65536]);
    // pr2(tmp);
    // printf("%lld\n",MP[1]);
    int k;
    // int t=clock();
    REP(k,203) {
        scanf("%s",str);
        if (str[0]=='0') break;
        int len=strlen(str); unsigned noww=0;
        REP(i,len) {
            if ('0'<=str[i]&&str[i]<='9') {
                int now=str[i]-'0';
                if ('0'<=str[i+1]&&str[i+1]<='9') now=now*10+str[i+1]-'0',i++;
                noww|=1<<now;
            }
        }
        // pr2(noww); puts("<- query");
        // pr2(value[65535]); pr2(value[65535]); puts("");
        // pr2(nxt(noww,value[i])); pr2(value[65535]);
        ll ans=INFF;
        REP(i,65536) {
            if (MP.count(noww)) ans=min(ans,MP[noww]-i);
            noww=nxt(noww);
            // break;
        }
        printf("%lld\n",ans);
    }
    // printf("%d\n",clock()-t);
}
/*
x^0
x^1
x^26+x^15+x^7+x^0
x^26+x^21+x^15+x^13+x^7+x^6+x^0
x^31+x^25+x^14+x^6
0
*/