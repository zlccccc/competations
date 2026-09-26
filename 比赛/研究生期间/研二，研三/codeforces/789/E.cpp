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

int n;
struct Tree{
    ll A[maxn];
    inline int lowbit(int x) {return x&-x;}
    Tree() {memset(A,0,sizeof(A));}
    void update(int x,ll val) {
        for (;x<=n;x+=lowbit(x)) A[x]+=val;
    }
    ll query(int x) {
        ll ret=0;
        for (;x;x-=lowbit(x)) ret+=A[x];
        return ret;
    }
}T[4];
struct node{
    int r,id,op;
};
vector<node> Q[maxn];
ll ans[maxn];
int A[maxn],id[maxn];
set<int> S;
vector<int> fac[maxn];
int main() {
    int i; int q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&A[i]),id[A[i]]=i;
    FOR(i,1,n) for (int j=i;j<=n;j+=i) fac[j].push_back(i);
    FOR(i,0,n+1) S.insert(i);
    FOR(i,1,n) {
        int pos=id[i];
        auto it=S.lower_bound(pos);
        --it; int pl=*it+1;
        ++it; ++it; int pr=*it-1;
        // printf("i=%d; l,r=%d %d\n",i,pl,pr);
        vector<pii> V;
        for (int x:fac[i]) {
            int y=i/x;
            if (x>=y) continue;
            int px=id[x],py=id[y];
            if (px>py) swap(px,py);
            if (px<pl||py>pr) continue;
            px=min(px,pos); py=max(py,pos);
            // if (pr==py) continue;
            // printf("x,y=%d %d; %d-%d; %d-%d\n",x,y,pl,px,py,pr);
            // pl->px; py->pr
            V.push_back(make_pair(px,py));
        }
        // int k; FOR(k,pl,pr) printf("%d ",A[k]); puts("<- k");
        sort(V.begin(),V.end(),greater<pii>());
        int py=pr+1,left=-1;
        for (auto now:V) {
            // left->now.first;
            if (left!=-1&&left!=now.first) {
                int pl=now.first+1,px=left;
                // printf("merge solve %d-%d; %d-%d\n",pl,px,py,pr);
                Q[pl].push_back({py,0,1});
                Q[pl].push_back({pr+1,0,-1});
                Q[px+1].push_back({py,0,-1});
                Q[px+1].push_back({pr+1,0,1});
            }
            left=now.first;
            py=min(py,now.second);
        }
        if (left!=-1) {
            int px=left;
            // printf("merge solve2 %d-%d; %d-%d\n",pl,px,py,pr);
            Q[pl].push_back({py,0,1});
            Q[pl].push_back({pr+1,0,-1});
            Q[px+1].push_back({py,0,-1});
            Q[px+1].push_back({pr+1,0,1});
        }
        S.erase(pos);
    }
    FOR(i,1,q) {
        int l,r; scanf("%d%d",&l,&r);
        // Q[l-1].push_back({l-1,i,1});
        Q[l-1].push_back({r,i,-1});
        // Q[r].push_back({l-1,i,-1});
        Q[r].push_back({r,i,1});
    }
    FOR(i,1,n) {
        for (auto now:Q[i]) {
            if (now.id) {
                int l=i,r=now.r,id=now.id,op=now.op;
                // printf("query i=%d; %d %d; id=%d; op=%d\n",i,l,r,id,op);
                ans[id]+=op*(T[0].query(r)+T[1].query(r)*r+T[2].query(r)*l+T[3].query(r)*l*r);
            } else {
                int l=i,r=now.r,op=now.op;
                // printf("update i=%d; %d %d; op=%d\n",i,l,r,op);
                l--; r--;
                T[0].update(r,(ll)l*r*op);
                T[1].update(r,-l*op);
                T[2].update(r,-r*op);
                T[3].update(r,1*op);
            }
        }
    }
    FOR(i,1,q) printf("%lld\n",ans[i]);
}
/*
100 3
49 56 7 17 8 26 96 41 71 40 60 31 58 57 66 12 55 42 97 10 54 87 3 83 68 88 22 15 20 59 61 32 25 38 62 43 48 35 93 51 80 81 94 84 50 6 2 90 91 29 95 44 47 99 36 18 30 85 4 45 14 19 16 70 89 27 39 76 33 67 13 21 74 69 86 79 53 46 1 52 28 11 9 23 73 5 100 24 77 63 37 64 65 72 98 78 75 92 82 34
45 54
7 22
12 21

*/