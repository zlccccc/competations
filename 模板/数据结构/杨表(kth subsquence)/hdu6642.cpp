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

// 
// 杨表构建; RSK插入算法, 插入x=6
// 1 2 4 8 9
// 3 5 7 10
// 11
// 从每一行找是否存在大于x的数字
// 找不到就插到末尾(第一行相当于最大上升子序列)
// 否则与upper_bound(x) swap
// 1 2 4 6 9
// 3 5 7 8
// 10
// 11
// 杨表每一行代表第k个LIS(最长上升/最长下降)长度
// 由Dilworth定理,最长链中元素个数等于最小反链划分中反链个数
// 列代表用不超过k个LDS(decending seq)覆盖的最长子序列长度(LIS长度不超过k)

// 对于给定形状,数字不同的杨氏矩阵的个数为:n!除以每个格子的钩子长度加1的积
// 其中钩子长度定义为该格子右边的格子数和它上边的格子数之和。

//题意: 选5个不相交单调上升子矩阵subsquence和最大
//      然后直接将多出来的往下放即可
//杨表: 单调**(上升/下降)子序列的item个数最大多少个
//杨表做法: 直接替换原数列中比这个大的位置,
//正确性: 可以将这个点后面连的所有东西放下边,
//      相当于连个边,相当于最优选择
ll ans;
map<int,ll> MP[5];//pos,cnts
void update(int x,int y,int dep) {//x,cnt
    if (dep==5) return;
    while (y) {
        map<int,ll>::iterator it=MP[dep].upper_bound(x);
        if (it==MP[dep].end()) {
            ans+=y;
            MP[dep][x]+=y; break;
        } pair<int,int> now=*it;
        MP[dep].erase(it);
        ll down=min(now.second,y);
        y-=down; now.second-=down;
        if (now.second) MP[dep][now.first]+=now.second;
        MP[dep][x]+=down;
        update(now.first,down,dep+1);
    }
}
int main(){
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n;
        scanf("%d",&n); ans=0;
        REP(i,5) MP[i].clear();
        FOR(i,1,n) {
            int k; scanf("%d",&k);
            update(k,k,0); // insert k个k
            printf("%lld%c",ans," \n"[i==n]);
        }
    }
}