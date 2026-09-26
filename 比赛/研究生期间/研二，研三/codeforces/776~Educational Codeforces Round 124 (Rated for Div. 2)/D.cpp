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

map<pii,int> S;
void ins(int x,int y,int id) {
    auto now=make_pair(x,y);
    if (S[now]==0) S[now]=id;
}
inline int lowbit(int x) {return x&-x;}
pii MAX[maxn];
inline void update(int x,int y) {
    for (int now=x;now<=1000000;now+=lowbit(now))
        if (MAX[now].first+MAX[now].second<x+y) MAX[now]=make_pair(x,y);
}
inline pii query(int x) {
    pii ret=make_pair(0,0);
    for (;x;x-=lowbit(x))
        if (ret.first+ret.second<MAX[x].first+MAX[x].second) ret=MAX[x];
    return ret;
}
pii Ans[maxn];
map<pii,int> MP;
void solve(int px,int py) {
    memset(MAX,0,sizeof(MAX));
    MP.clear();
    for (auto now:S) MP[make_pair(250000+px*now.first.first,250000+py*now.first.second)]=now.second;
    for (auto now:MP) {
        pii pos=now.first; int id=now.second;
        pii ini=make_pair((pos.first-250000)*px,(pos.second-250000)*py);
        // if (id==0) printf("update %d %d\n",(pos.first-250000)*px,(pos.second-250000)*py);
        if (id==0) update(pos.second,pos.first); //y,x
        else {
            auto q=query(pos.second); swap(q.first,q.second);
            q.first=(q.first-250000)*px; q.second=(q.second-250000)*py;
            if (abs(q.first-ini.first)+abs(q.second-ini.second)<abs(Ans[id].first-ini.first)+abs(Ans[id].second-ini.second))
                Ans[id]=q;
            // printf("id=%d; pos=%d %d; q=%d %d\n",id,(pos.first-250000)*px,(pos.second-250000)*py,q.first,q.second);
        }
    }
}
int main() {
    int i;
    int n; scanf("%d",&n);
    FOR(i,1,n) {
        int x,y;
        scanf("%d%d",&x,&y);
        ins(x,y,i); int dx,dy;
        ins(x-1,y,0);
        ins(x,y-1,0);
        ins(x+1,y,0);
        ins(x,y+1,0);
        // FOR(dx,-1,1) FOR(dy,-1,1) ins(x+dx,y+dy,0);
    }
    solve(1,1); solve(-1,1); solve(1,-1); solve(-1,-1);
    FOR(i,1,n) printf("%d %d\n",Ans[i].first,Ans[i].second);
    // printf("%lld\n",ans);
}
/*
*/