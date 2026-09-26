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

ll n,m;
LL C(int n,int m) {
    if (n<m) return 0;
    ll ret=1;
    for (int k=n-m+1;k<=n;k++) ret=ret*k;
    for (int k=1;k<=m;k++) ret=ret/k;
    return ret;
}

ll f[104];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        ll i,k;
        scanf("%lld%lld",&n,&m);
        f[1]=n*C(m,3); // 三连 (不同色)
        f[2]=(n-2)*m; // 同花顺
        f[3]=(C(n,3)-(n-2))*m; // 同花
        f[4]=(n-2)*(m*m*m-m); // 顺子
        f[5]=C(n,2)*2*C(m,2)*m; // 对子
        f[6]=(C(n,3)-(n-2))*(m*m*m-m); // 单牌
        // f[7]=C(n*m,3)-f[1]-f[2]-f[3]-f[4]-f[5]-f[6]; // all
        // printf("%lld %lld %lld %lld %lld %lld %lld\n",f[1],f[2],f[3],f[4],f[5],f[6],f[7]);
        {
            pii t[4];
            REP(k,3) scanf("%d%d",&t[k].first,&t[k].second);
            sort(t,t+3); reverse(t,t+3);
            if (t[1].first==t[2].first) swap(t[0],t[2]); // 对子

            int a=t[0].first,b=t[1].first,c=t[2].first;
            int x=t[0].second,y=t[1].second,z=t[2].second;
            ll ans=0,all=f[1]+f[2]+f[3]+f[4]+f[5]+f[6];
            all-=f[1];
            if (a==b&&a==c) { // 三连
                ans=(a-1)*C(m,3);
                // printf("calc 1 %lld %lld\n",ans,all);
                printf("%lld\n",ans+all);
                continue;
            }
            all-=f[2];
            if (a==b+1&&a==c+2&&x==y&&y==z) { // 同花顺
                ans=(a-3)*m;
                // printf("calc 2 %lld %lld\n",ans,all);
                printf("%lld\n",ans+all);
                continue;
            }
            all-=f[3];
            if (x==y&&y==z) { // 同花
                ans=(C(a-1,3)+C(b-1,2)+C(c-1,1)-(a-3))*m;
                // printf("calc 3 %lld %lld\n",ans,all);
                printf("%lld\n",ans+all);
                continue;
            }
            all-=f[4];
            if (a==b+1&&a==c+2) { // 顺子
                ans=(a-3)*(m*m*m-m);
                // printf("calc 4 %lld %lld\n",ans,all);
                printf("%lld\n",ans+all);
                continue;
            }
            all-=f[5];
            if (a==b) { // 对子
                ans=((a-1)*(n-1)+(c-1)-(a<c))*C(m,2)*m;
                // printf("  --- %lld * %lld",ans/(C(m,2)*m),C(m*2)*m);
                // printf("calc 5 %lld %lld\n",ans,all);
                printf("%lld\n",ans+all);
                continue;
            }
            all-=f[6];
            {
                ans=(C(a-1,3)+C(b-1,2)+C(c-1,1)-(a-3))*(m*m*m-m);
                // printf("calc 6 %lld %lld\n",ans,all);
                printf("%lld\n",ans+all);
                continue;
            }
        }
    }
}
/*
100
4 3
1 1 3 2 4 3
3 5
1 4 2 4 1 3
9 6
3 1 3 2 3 3
87654 9
10245 7 10255 7 10256 7
99999 10
54853 3 45748 6 47831 1
45678 6
11888 2 30294 1 11888 6
75483 8
11111 1 22222 1 33333 1
30999 7
28888 1 28889 2 28890 3
100000 10
100000 1 100000 2 100000 3
*/