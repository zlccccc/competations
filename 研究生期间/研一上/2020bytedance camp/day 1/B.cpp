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
const LL maxn=1007+107;
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
    const int maxn=1e5+7;
    int next[maxn][27],fail[maxn],len[maxn],tot;
    bool mark[maxn];
    void init(){
        tot=0; len[0]=0; fail[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void insert(char s[]) {
        int i,n=strlen(s),p=0;
        REP(i,n) {
            int c=s[i]-'a';
            if (!next[p][c]) {
                next[p][c]=++tot; len[tot]=len[p]+1; fail[tot]=0;
                memset(next[tot],0,sizeof(next[tot]));
            } p=next[p][c];
        } mark[p]=1;
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
                } else next[p][c]=p? next[fail[p]][c]:0;
            } mark[p]|=mark[fail[p]];
        }
    }
}
int n;
struct mat{
    int A[107][107];
    mat() {memset(A,0,sizeof(A));}
}base;
mat multi(const mat &A,const mat &B) {
    mat ret; int i,j,k;
    REP(i,n) REP(j,n) REP(k,n) {
        add_(ret.A[i][k],(ll)A.A[i][j]*B.A[j][k]%M);
    } return ret;
}
mat poww(mat a,int b) {
    mat ret; int i;
    // puts("???");
    REP(i,n) ret.A[i][i]=1;
        // int j;
        // REP(i,n) {
        //     // REP(j,n) printf("%d ",base.A[i][j]); puts("");
        //     REP(j,n) printf("%d ",ret.A[i][j]); puts("");
        // }
    for (; b; b>>=1,a=multi(a,a)) {
        if (b&1) ret=multi(a,ret);

    }
    return ret;
}
char str[maxn];
int main() {
    int len,i,c;
    scanf("%d%d",&n,&len);
    ACM::init();
    REP(i,n) {
        scanf("%s",str);
        ACM::insert(str);
    } n=ACM::tot+1;
    ACM::buildAC();
    REP(i,n) {
        // printf("i=%d ",i);
        REP(c,26) {
            // printf("%d ",ACM::next[i][c]);
            if (!ACM::mark[ACM::next[i][c]])
                base.A[i][ACM::next[i][c]]++;
        }
        // puts("");
    } mat noww=poww(base,len);
    // int j;
    // REP(i,n) {
    //     // REP(j,n) printf("%d ",base.A[i][j]); puts("");
    //     REP(j,n) printf("%d ",noww.A[i][j]); puts("");
    // }
    int ans=0;
    REP(i,n) add_(ans,noww.A[0][i]);
    printf("%d\n",ans);
}
/*
3 1
a
c
m

4 2
i
cp
pc
cc
*/