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
const LL maxn=4e5+7;
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

int xid[57][57][57][57];
int dp[107][maxn],all[107][maxn];
char str[maxn];
int main() {
    int n,L,p,i,j,k,t;
    int tot=0;//0:nothing
    FOR(i,0,50) {
        FOR(j,i,50) {
            FOR(k,j,50) {
                FOR(t,k,50) {
                    xid[i][j][k][t]=tot++;
                }
            }
        }
    }
    // printf("tot=%d\n",tot);
    scanf("%d%d%d",&n,&L,&p);
    scanf("%s",str+1);
    if (p==0) return 0*puts("1");
    all[0][xid[L][L][L][L]]=1;//count
    int o,ans=1;
    FOR(o,0,n) {//L:no this 1
        //nearest four 1
        if (o) {
            FOR(i,1,L) {//next position; choose
                if (i!=L&&p<2) continue;
                // printf("i=%d; o=%d\n",i,o);
                FOR(j,min(i+1,L),L) {
                    if (j!=L&&p<3) continue;
                    FOR(k,min(j+1,L),L) {
                        if (k!=L&&p<4) continue;
                        FOR(t,min(k+1,L),L) {
                            if (t!=L&&p<5) continue;//o+i,o+j,o+k,o+l
                            if (str[o]!='0') {
                                dp[o][xid[i][j][k][t]]=all[o][xid[i][j][k][t]];//o-i:first position
                                add_(ans,dp[o][xid[i][j][k][t]]);//choose it
                                if (o+L-t<=n) {
                                    // if (dp[o][xid[i][j][k][t]]) printf("(%d %d %d %d %d) ;  ",o+L-t,L-t,i,j,k);
                                    add_(all[o+L-t][xid[L-t][i+L-t][j+L-t][k+L-t]],dp[o][xid[i][j][k][t]]);//o~o+L-t(maybe 0)
                                }
                                // if (dp[o][xid[i][j][k][t]]) printf("%d %d %d %d %d:  %d",o,i,j,k,t,dp[o][xid[i][j][k][t]]);
                                // if ((dp[o][xid[i][j][k][t]])) puts("");
                            }
                        }
                    }
                }
            }
        }
        FOR(i,0,L) {//not choose
            FOR(j,i,L) {
                FOR(k,j,L) {
                    FOR(t,k,L) {
                        add_(all[o+1][xid[min(i+1,L)][min(j+1,L)][min(k+1,L)][min(t+1,L)]],all[o][xid[i][j][k][t]]);
                        // if (all[o][xid[i][j][k][t]]) {
                        //     printf("x %d %d %d %d %d:  %d xxx\n",o,i,j,k,t,all[o][xid[i][j][k][t]]);
                        // }
                    }
                }
            }
        }
    }
    printf("%d\n",ans);
}
/*
10 7 5
***************************************************

4 2 3
***


7 3 1
*******

7 7 1
*******

10 2 1
****0*****
*/