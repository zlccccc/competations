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

ll all=0;
ll A[maxn];
inline int lowbit(int x) {return x&-x;}
void update(int x,int val) {
    for (;x<=200000;x+=lowbit(x)) A[x]+=val;
}
ll query(int x) {
    ll ret=0;
    for (;x;x-=lowbit(x)) ret+=A[x];
    return ret;
}
vector<pair<pii,int> > V[maxn]; // leftpos, id
ll ans[maxn];
vector<int> sub[maxn];
bool mark[maxn];
void solve() {
    int i;
    int count=0;
    FOR(i,1,400000) for (int j=i;j<=400000;j+=i) sub[j].push_back(i);
    // int vx,vy;
    FOR(i,1,200000) {
    // FOR(i,1,20) {
        int a,b;
        REP(a,(int)sub[i*2].size()) if (i%sub[i*2][a]==0) mark[a]=0; else mark[a]=1;
        REP(a,(int)sub[i*2].size()) if (sub[i*2][a]<i) {
            int cnt=0;
            rep(b,a+1,(int)sub[i*2].size()) if (sub[i*2][b]<i) {
                int vx=sub[i*2][a],vy=sub[i*2][b];
                int mrk=mark[a]|mark[b]; // twice?
                if (vx+vy>mrk*i) cnt++,all++;
                count++;
                // if (vx+vy>mrk*i) printf("%d %d %d: lcm=%d not-okay\n",vx,vy,i,(mrk+1)*i);
            }
            update(sub[i*2][a],cnt);
            // if (cnt) printf("update %d %d\n",sub[i*2][a],cnt);
            // count++;
        }
        for (auto p:V[i]) ans[p.second]+=query(p.first.first)*p.first.second;
    }
    // printf("init count %d\n",count);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int l,r;
        scanf("%d%d",&l,&r);
        ans[_]=(ll)(r-l+1)*(r-l)*(r-l-1)/6;
        // V[l-1].push_back(make_pair(make_pair(l-1,-1),_));
        V[r].push_back(make_pair(make_pair(l-1,1),_));
        V[r].push_back(make_pair(make_pair(r,-1),_));
    }
    solve();
    FOR(_,1,T) printf("%lld\n",ans[_]);
}
/* 
1 4
*/