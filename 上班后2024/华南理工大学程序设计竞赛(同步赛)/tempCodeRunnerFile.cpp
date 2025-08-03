// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,5> ar5;
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

int solve() {
    int n,m;
    bool mark=0;
    scanf("%d%d",&n,&m);
    if (n>m) swap(n,m),mark=1;
    vector<map<vector<int>,pair<int,vector<int>>>> MP(m+1);
    MP[0][vector<int>(n)]={0,vector<int>(n)};
    FOR_(k,1,m) {
        for (auto &[pre,presta]:MP[k-1]) {
            REP_(sta,1<<n) {
                vector<int> fa(n*2+1),idx(n*2+1);
                FOR_(i,1,n+n) fa[i]=i;
                int tot=n;
                vector<int> cur;
                REP_(i,n) cur.push_back(pre[i]);
                REP_(i,n) cur.push_back(((sta>>i)&1)?++tot:0);
                function<int(int)> getfa=[&](int x) { return fa[x]==x?x:fa[x]=getfa(fa[x]); };
                bool notokay=false;
                auto merge=[&](int x,int y) {
                    // printf("merge %d %d\n",x,y);
                    x=getfa(x); y=getfa(y);
                    if (x==y) notokay=true;
                    fa[x]=y;
                };
                // REP_(i,n+n) printf("%d ",cur[i]); puts("<- ind cur");
                rep_(i,n,n+n) {
                    if (cur[i]&&cur[i-n]) merge(cur[i-n],cur[i]);
                    if (i+1<n+n&&cur[i]&&cur[i+1]) merge(cur[i],cur[i+1]);
                }
                REP_(i,n) if (cur[i]&&getfa(cur[i])<n) notokay=true; // not linked yet
                if (notokay) continue;
                int cnt=0;
                rep_(i,n,n+n) {
                    if (cur[i]&&!idx[getfa(cur[i])]) idx[getfa(cur[i])]=++cnt;
                }
                vector<int> nxt(n);
                REP_(i,n) nxt[i]=cur[i+n]?idx[getfa(cur[i+n])]:0;
                // rep_(i,n,n+n) printf("%d ",idx[i]); puts("<- idx");
                int c=presta.first+__builtin_popcount(sta);
                MP[k][nxt]=max(MP[k][nxt],{c,pre});
                // printf("k=%d\n",k);
                // for (int v:pre) printf("%d ",v); puts("<- pre");
                // for (int v:nxt) printf("%d ",v); puts("<- nxt");
                // printf("c=%d; cnt=%d\n",c,cnt);
            }
        }
        // printf("k=%d\n",k);
        // for (auto &[pre,presta]:MP[k]) {
        //     int cnt=presta.first;
        //     for (int v:pre) printf("%d ",v); printf(" <- %d\n",cnt);
        // }
    }
    vector<vector<int>> finRes;
    pair<int,vector<int>> lastres={-1,{}};
    for (auto &[pre,presta]:MP[m]) {
        lastres=max(lastres,{presta.first,pre});
    }
    rFOR_(i,1,m) {
        finRes.push_back(lastres.second);
        lastres=MP[i][lastres.second];
    }
    if (!mark) {
        REP_(i,m) {
            REP_(j,n) if (finRes[i][j]) putchar('.');
            else putchar('W');
            puts("");
        }
    } else {
        swap(n,m);
        REP_(i,n) {
            REP_(j,m) if (finRes[i][j]) putchar('.');
            else putchar('W');
            puts("");
        }
    }
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/