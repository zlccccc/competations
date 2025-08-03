#include <bits/stdc++.h>
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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int ff[17][17][17][17],f[17][17][17],g[17][17][17]; // length; inv; pi>pi+1; ff(last-value)
int G[29][17][17][17]; // 额外用的长度; 段数; inv; pi>pi+1
int A[17],_f[17][17],_g[17][17],_G[17][17][17];
void init() {
    int i,x,y,k,j,_x,_y;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    FOR(i,1,12) { // length
        ff[i][0][0][i]=1; f[i][0][0]=1;
        // all-rigit: to-front
        FOR(x,1,12) FOR(y,0,12) { // j:prev-max
            FOR(k,1,i) FOR(j,1,i-1) { //last-value
                if (y-(j>=k)<0) continue;
                if (x-(i-k)<0) continue;
                add_(ff[i][x][y][k],ff[i-1][x-(i-k)][y-(j>=k)][j]);
                add_(f[i][x][y],ff[i-1][x-(i-k)][y-(j>=k)][j]);
            }
        }
        g[1][0][0]=1;
        FOR(x,1,12) FOR(y,1,12) {
            g[i][x][y]=f[i][x][y];
            FOR(j,1,i) FOR(_x,0,x) FOR(_y,0,y) {//j:lastlength
                add_(g[i][x][y],M-g[j][_x][_y]*f[i-j][x-_x][y-_y]%M);
            }
        }
    }
    G[0][0][0][0]=1;
    FOR(i,1,28) {
        FOR(x,1,12) FOR(y,1,12) {
            FOR(k,1,12) {
                FOR(j,1,min(i,12)) FOR(_x,1,x) FOR(_y,1,y) {//j:lastlength
                    add_(G[i][k][x][y],g[j][_x][_y]*G[i-j][k-1][x-_x][y-_y]%M);
                }
            }
        }
    }
    // FOR(i,1,28) FOR(j,1,12) FOR(x,1,12) FOR(y,1,12) {
    //     if (G[i][j][x][y]) printf("%d %d %d %d: %d\n",i,j,x,y,G[i][j][x][y]);
    // }
    // FOR(i,2,5) {
    //     FOR(k,1,i) A[k]=k;
    //     FOR(x,0,11) FOR(y,0,11) _f[x][y]=_g[x][y]=0;
    //     do {
    //         int cnt1=0,cnt2=0,MAX=0,cnt0=0;
    //         FOR(x,1,i) {max_(MAX,A[x]); if (MAX==x) cnt0++;}
    //         FOR(x,1,i) FOR(y,x+1,i) if (A[x]>A[y]) cnt1++;
    //         FOR(x,1,i-1) if (A[x]>A[x+1]) cnt2++;
    //         // FOR(x,1,i) printf("%d ",A[x]); printf("   %d %d <-A\n",cnt1,cnt2);
    //         _f[cnt1][cnt2]++;
    //         if (cnt0==1) _g[cnt1][cnt2]++;
    //     } while (next_permutation(A+1,A+1+i));
    //     // printf("i=%d\n",i);
    //     // FOR(x,0,11) FOR(y,0,11) printf("%d(%d)%c",f[i][x][y],_f[x][y]," \n"[y==11]);
    //     // FOR(x,0,11) FOR(y,0,11) printf("%d(%d)%c",g[i][x][y],_g[x][y]," \n"[y==11]);
    // }
}
int main() {
    init();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,j;
        int n,k,x; int ans=0;
        scanf("%d%d%d",&n,&k,&x);
        FOR(i,0,28) FOR(j,0,12) {
            if (n<i) continue;
            // C(n-i+j+1,j+1)
            // add_(ans,(ll)C(n-i+j,j)*G[i][j][k][x]%M);
            if (n<100) add_(ans,(ll)C(n-i+j,j)*G[i][j][k][x]%M);
            else {
                int now=inv[j]*G[i][j][k][x]%M,t;
                FOR(t,n-i+1,n-i+j) mul_(now,t);
                add_(ans,now);
            }
        }
        printf("%d\n",ans);
    }
}
/*
*/