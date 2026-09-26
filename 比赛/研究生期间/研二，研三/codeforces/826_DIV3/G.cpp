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

vector<int> edge[maxn];
int dis[maxn];
set<int> mask[maxn];
int cnt[maxn],val[maxn];
int h[maxn];

bool NOW[67],NXT[67];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) {
            edge[i].clear(),dis[i]=-1,cnt[i]=val[i]=0;
            mask[i].clear();
        }
        memset(NOW,0,sizeof(NOW));
        memset(NXT,0,sizeof(NXT));
        FOR(i,1,m) {
            int x,y;
            scanf("%d%d",&x,&y);
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        int f; scanf("%d",&f);
        FOR(i,1,f) {
            scanf("%d",&h[i]);
            cnt[h[i]]++;
        }
        int k; scanf("%d",&k);
        FOR(i,1,k) {
            int p; scanf("%d",&p);
            cnt[h[p]]--;
            val[h[p]]|=1<<(i-1);
        }
        queue<int> Q;
        Q.push(1); dis[1]=0;
        mask[1].insert(val[1]);
        NOW[0]=1;
        int ans=k;
        while (Q.size()) {
            int x=Q.front(); Q.pop();
            for (int v:edge[x]) if (dis[v]==-1)
                dis[v]=dis[x]+1,Q.push(v);
            for (int v:edge[x]) if (dis[v]==dis[x]+1)
                for (auto t:mask[x]) mask[v].insert(t|val[v]);
            // printf("x=%d; cnt=%d\n",x,cnt[x]);
            // for (auto now:mask[x]) pr2(now,k);
            // puts("");
            while (cnt[x]--) {
                int sta;
                for (auto now:mask[x])
                    REP(sta,(1<<k)) NXT[sta|now]|=NOW[sta];
                memcpy(NOW,NXT,sizeof(NOW));
                REP(sta,(1<<k)) if (NOW[sta]) ans=min(ans,k-__builtin_popcount(sta));
                // for (auto now:mask[x]) printf("now=%d\n",now);
                // REP(sta,(1<<k)) if (NOW[sta]) printf("now sta=%d; ",sta);
                // REP(sta,(1<<k)) if (NXT[sta]) printf("nxt sta=%d; ",sta);
            }
        }
        printf("%d\n",ans);
    }
}
/*
3
2 1
1 2
3
2 2 2
3
1 2 3
3 3
1 2
1 3
2 3
4
2 2 2 3
3
1 2 4
4 4
3 1
3 2
1 4
2 4
5
3 2 2 4 2
3
1 3 4

*/