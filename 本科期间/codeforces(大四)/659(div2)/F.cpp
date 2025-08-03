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

set<int> S[maxn];
pii T[maxn*4];
int val[maxn*4];
int getleft(int x) {
    set<int> &s=S[x*2];
    if (!s.size()) return 0;
    return (*s.rbegin()+2)/2;
}
int getright(int x) {//should_right
    set<int> &s=S[x*2-1];
    if (!s.size()) return INF;
    return (*s.begin()+1)/2;
}
void update(int x,int pos,int L,int R) {
    if (L==R) {
        pii now=make_pair(getleft(L),getright(L));
        // printf(" solve %d : %d %d\n",L,now.first,now.second);
        T[x]=now;
        if (now.first>now.second) val[x]=1; else val[x]=0;
        return;
    } int mid=L+(R-L)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    if (mid<pos) update(x<<1|1,pos,mid+1,R);
    val[x]=val[x<<1]|val[x<<1|1];
    pii left=T[x<<1],right=T[x<<1|1];
    if (left.second<right.first) val[x]=1;
    T[x]=make_pair(max(left.first,right.first),min(left.second,right.second));
    // printf("update: %d %d %d %d; %d %d\n",x,L,R,pos,T[x].first,T[x].second);
}//query:T[0]
int main() {
    int n,m,q,i;
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n) update(1,i,1,n);
    FOR(i,1,q) {
        int x,y; scanf("%d%d",&x,&y);
        if (S[x].count(y)) {
            S[x].erase(y);
        } else S[x].insert(y);
        int px=(x+1)/2;
        update(1,px,1,n);
        // printf("px=%d\n",px);
        // printf("%d %d\n",getleft(px-1),getright(px-1));
        // printf("%d %d\n",getleft(px),getright(px));
        // printf("%d %d\n",getleft(px+1),getright(px+1));
        if (!val[1]) puts("YES");
        else puts("NO");
    }
}
/*
3 2 7
4 2
6 4
1 3
*/