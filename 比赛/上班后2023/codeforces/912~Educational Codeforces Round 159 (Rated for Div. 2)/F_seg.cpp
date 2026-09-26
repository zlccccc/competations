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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

namespace LB {
    typedef int BaseType;
    const int MaxBit=20;
    struct L_B {
        BaseType b[MaxBit]; bool have_0;
        L_B() {clear();}
        void clear() {memset(b,0,sizeof(b)); have_0=0;}
        void insert(BaseType x) {
            rREP_(i,MaxBit) if ((x>>i)&1) {
                if (!b[i]) b[i]=x; x^=b[i];
            }
        }
        void rebuild() {
            rREP_(i,MaxBit) rREP_(j,i) if ((b[i]>>j)&1) b[i]^=b[j];
        }
        BaseType XORMIN(BaseType x) {
            rREP_(i,MaxBit) if ((b[i]^x)<x) x^=b[i];
            return x;
        }
    } T[maxn*4];
}
using namespace LB;

void update(int x,int pos,int val,int L,int R) {
    T[x].insert(val);
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
}
vector<int> nodes;
void query(int x,int l,int r,int L,int R) {
    // printf("update %d %d %d %d %d\n",x,l,r,L,R);
    if (l<=L&&R<=r) {
        // printf("%d->%d\n",L,R);
        nodes.push_back(x);
        return;
    }
    int mid=(L+R)/2;
    if (l<=mid) query(x<<1,l,r,L,mid);
    if (mid<r) query(x<<1|1,l,r,mid+1,R);
}


vector<int> edge[maxn];
int fa[maxn],dep[maxn],sz[maxn],tot;
int top[maxn],id[maxn],son[maxn];
void dfs1(int u,int father,int depth) {
    int mx=-1; sz[u]=1;
    fa[u]=father; son[u]=0; dep[u]=depth;
    for (int v:edge[u]) {
        if (v==father) continue;
        dfs1(v,u,depth+1); sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}
void dfs2(int u,int x) {
    top[u]=x; id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (int v:edge[u]) {
        if (v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
int n;
inline int Query(int x,int y) {
    int ret=0;
    while (top[x]!=top[y]) {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        query(1,id[top[x]],id[x],1,n);
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y);
    query(1,id[x],id[y],1,n);
    return ret;
}

int A[maxn];
int main() {
    scanf("%d",&n);
    FOR_(i,1,n) scanf("%d",&A[i]);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    // FOR_(i,1,n) printf("%d ",id[i]); puts("<- id");
    FOR_(i,1,n) update(1,id[i],A[i],1,n);
    int q;
    scanf("%d",&q);
    FOR_(i,1,q) {
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        nodes.clear();
        Query(x,y);
        L_B cur;
        for (int v:nodes) 
            rREP_(i,20) if (T[v].b[i]) cur.insert(T[v].b[i]);
        cur.rebuild();
        if (cur.XORMIN(k)==0) puts("YES");
        else puts("NO");
    }
}
/*
*/