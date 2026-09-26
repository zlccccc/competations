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
const LL maxn=2e6+7;
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

bool gauss(double A[256][256],double X[256],int n,int m) {
    int i,j,k;
    REP(i,n) {
        int id=i;
        rep(j,i+1,m) if (abs(A[j][i])>abs(A[id][i])) id=j;
        if (abs(A[id][i])<eps) continue;
        if (id!=i)
            {rep(j,i,n) swap(A[i][j],A[id][j]); swap(X[i],X[id]);}
        REP(k,m) if (k!=i) {
            X[k]-=A[k][i]/A[i][i]*X[i];
            rrep(j,i,n) A[k][j]-=A[k][i]/A[i][i]*A[i][j];
        }
    }
    REP(i,n) if (abs(A[i][i])<eps&&abs(X[i])>eps) return 0;
    rep(i,n,m) if (abs(X[i])>eps) return 0;
    REP(i,n) if (abs(A[i][i])<eps||abs(X[i])<eps) X[i]=0;
    else X[i]/=A[i][i];
    return 1;
}
int n;
double val[256];
double trans[256][256];
void doit() {
    int sta;
    REP(sta,256) {
        int leng=8,now=sta,k,val=0;
        // pr2(sta,8); 
        while(1) {
            int cnt=0,p=2;
            REP(k,leng) {
                int o=(now>>k)&1;
                if (o!=p) p=o,cnt=0;
                cnt++; if (cnt>=3) break; 
            } if (k==leng) break;
            int l=k-2,r=k;
            while (r<leng&&p==((now>>r)&1)) r++;
            val+=(r-l)*(r-l);
            int nxt=0,nxtleng=0;
            rrep(k,r,leng) nxt=nxt<<1|((now>>k)&1),nxtleng++;
            rREP(k,l) nxt=nxt<<1|((now>>k)&1),nxtleng++;
            now=nxt; leng=nxtleng;
            // printf("-> "); pr2(now,leng); 
        }
        trans[sta][sta]=1;
        ::val[sta]=val;
        // printf(" val=%d;\n",val);
        int all_more=(1<<(8-leng));
        REP(k,all_more) {
            int nxt=now|(k<<leng);
            trans[sta][nxt]-=1./all_more;
        } if (leng==8) trans[sta][sta]++;
        // if (all_more<4) {
        //     double all=0;
        //     REP(k,256) all+=trans[sta][k];
        //     pr2(sta,8); pr2(now,leng); printf("%f\n",all);
        //     REP(k,256) if (abs(trans[sta][k])>eps) pr2(k),printf(" %f << trans\n",trans[sta][k]);
        // }
    }
    if (!gauss(trans,val,256,256)) puts("Cal Error");
    // REP(sta,256) {pr2(sta,8); printf("%f\n",val[sta]);}
    // REP(sta,256) {pr2(sta,8); printf("%f\n",trans[sta][sta]);}
}
char str[9];
int main() {
    doit();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        scanf("%s",str);
        int i,n=0;
        rREP(i,8) n=n<<1|(str[i]-'0');
        printf("%f\n",val[n]);
    }
}
/*
*/