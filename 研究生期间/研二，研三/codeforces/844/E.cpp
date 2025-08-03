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
#include <functional>
#include <random>
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
// const LL M=998244353;
// ll M=1;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// 先solve 3, 然后1-2贪心?
void solve() {
    int i,k,n;
    scanf("%d",&n);
    vector<ar3> val; //mask,l,r
    vector<ar3> ans(n+1,((ar3){0,0,0}));
    vector<int> Pos;
    REP(i,n) {
        int u,d,l,r;
        scanf("%d%d%d%d",&u,&l,&d,&r); r++;
        Pos.push_back(l); Pos.push_back(r); // l->r
        val.push_back({u|d,l,r});
    } Pos.push_back(INF);
    sort(Pos.begin(),Pos.end());
    Pos.erase(unique(Pos.begin(),Pos.end()),Pos.end());
    auto getid=[&](int x) {
        return lower_bound(Pos.begin(),Pos.end(),x)-Pos.begin();
    };
    REP(i,n) val[i][1]=getid(val[i][1]),val[i][2]=getid(val[i][2]);
    vector<vector<ar3>> R(Pos.size(),vector<ar3>()); // right,color,id
    REP(i,n) R[val[i][1]].push_back({val[i][2],val[i][0],i+1});
    // solve pos=3
    vector<int> col[3];
    col[1].resize(Pos.size(),0); col[2].resize(Pos.size(),0);
    // REP(i,(int)Pos.size()) {
    //     for (auto p:R[i]) {
    //         printf("solve %d %d %d ??\n",p[0],p[1],p[2]);
    //     }
    // }
    int sum=0;
    { // solve 3
        int rig=0;
        REP(i,(int)Pos.size()) {
            rig=max(rig,i);
            for (auto p:R[i]) { // right,color,id
                if (p[1]!=3) continue;
                if (p[0]>rig) { // rig -> p[0]
                    // printf("solve %d -> %d: col[3]; id=%d\n",rig,p[0],p[2]);
                    rep(k,rig,p[0]) {
                        col[1][k]=col[2][k]=p[2];
                        sum+=(Pos[k+1]-Pos[k])*2;
                    }
                    ans[p[2]]={3,rig,p[0]};
                    rig=p[0];
                }
            }
        }
    }
    { // solve 1 and 2
        int rig[3]={0,0,0};
        REP(i,(int)Pos.size()-1) {
            sort(R[i].begin(),R[i].end());
            reverse(R[i].begin(),R[i].end()); // only cover once!
            rig[1]=max(rig[1],i);
            rig[2]=max(rig[2],i);
            for (auto p:R[i]) { // right, color, id
                while (col[1][rig[1]]) rig[1]++;
                while (col[2][rig[2]]) rig[2]++;
                if (p[1]==3) continue;
                int o=p[1];
                if (p[0]<=rig[o]) continue; // not useful
                // really solve; color=p[1];
                // check inside
                rep(k,rig[o],p[0]) {
                    if (col[o][k]) {
                        if (col[o][k]==col[o][p[0]-1]) break; // last one
                        // else: inside remove!
                        ans[col[o][k]][0]&=~o; // just cover it
                    } else sum+=(Pos[k+1]-Pos[k]);
                    col[o][k]=p[2];
                }
                ans[p[2]]={o,rig[o],k}; // choose-pos
                rig[o]=k;
            }
        }
    }
    printf("%d\n",sum);
    FOR(i,1,n) {
        if (ans[i][0]==0) puts("0 0 0 0");
        else {
            int l=ans[i][0]&1,r=ans[i][0]&2;
            if (!l) l=r; if (!r) r=l;
            printf("%d %d %d %d\n",l,Pos[ans[i][1]],r,Pos[ans[i][2]]-1);
        }
    }
    // puts("solve");
    // REP(i,(int)Pos.size()) printf("%d ",Pos[i]); puts("<- position");
    // REP(i,(int)Pos.size()) printf("%d ",col[1][i]); puts(" <- row 1");
    // REP(i,(int)Pos.size()) printf("%d ",col[2][i]); puts(" <- row 2");
    // puts("");
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        solve();
    }
}
/*
5
-1 1 -1 -1 1
1
-1
2
1 -1

*/