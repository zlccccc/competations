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
const LL maxn=2e5+107;
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

namespace ACM{
    const int maxn=2e5+7;
    int next[maxn][27],cnt[maxn];
    int fail[maxn],len[maxn],tot;
    void init() {
        tot=0; len[0]=fail[0]=cnt[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    int insert(char s[]) {
        int i,n=strlen(s),p=0;
        REP(i,n) {
            int c=s[i]-'A';
            if (!next[p][c]) {
                next[p][c]=++tot; len[tot]=len[p]+1;
                fail[tot]=cnt[tot]=0;
                memset(next[tot],0,sizeof(next[tot]));
            } p=next[p][c];
        } return p;
    }
    int Q[maxn],ST,ED;
    void buildAC() {
        ST=0; ED=-1; Q[++ED]=0;
        while (ST<=ED) {
            int p=Q[ST++],c;
            REP(c,26) {
                if (next[p][c]) {
                    fail[next[p][c]]=p?next[fail[p]][c]:0;
                    Q[++ED]=next[p][c];
                } else next[p][c]=p?next[fail[p]][c]:0;//否则可能fail=self
            }
        }
    }
    void solve(){
        int i;
        // FOR(i,1,tot) printf("%d ",Q[i]);
        rFOR(i,1,tot) cnt[fail[Q[i]]]+=cnt[Q[i]];
    }
}
char str[507][507],s[maxn];
int id[maxn];
int main() {
    int i,j,k,n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    ACM::init();
    FOR(i,1,n) scanf("%s",str[i]+1);
    FOR(i,1,q) {
        scanf("%s",s);
        id[i]=ACM::insert(s);
    } ACM::buildAC();
    FOR(i,1,n) {
        int p=0;
        FOR(j,1,m) {
            int t=p,r=0;
            FOR(k,i,n) {
                r=ACM::next[r][str[k][j]-'A'];
                t=ACM::next[t][str[k][j]-'A'];
                // printf("t=%d\n",t);
                ACM::cnt[t]++; ACM::cnt[r]--;
                if (i==1) ACM::cnt[r]++;//row
            } p=ACM::next[p][str[i][j]-'A'];
        }
    } ACM::solve();
    FOR(i,1,q) printf("%d\n",ACM::cnt[id[i]]);
}
/*
*/
