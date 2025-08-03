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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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

struct node{
    int l,r,sum;
    node() {l=0;r=0;sum=0;}
}T[maxn*32];
int ntot;
void update(int &x,int pos,int L,int R) {
    T[++ntot]=T[x]; x=ntot;
    T[x].sum++;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,L,mid);
    else update(T[x].r,pos,mid+1,R);
}
int query(int &x,int l,int r,int L,int R) {
    if (!x) return 0;
    if (l<=L&&R<=r) return T[x].sum;
    int mid=(L+R)/2;
    int ret=0;
    if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
    return ret;
}

int n;
int root[maxn];
int Ask(int l,int r,int x) {
    return query(root[r],1,x,1,n)-query(root[l-1],1,x,1,n);
}

vector<int> edge[maxn];
int id[maxn],out[maxn],tot;
void dfs1(int x,int f,int depth) {  // get dfn and depth
    id[x]=++tot;
    for (int v:edge[x]) {
        if (v==f) continue;
        dfs1(v,x,depth+1);
    }
    out[x]=tot;
}
ll res[maxn];
ll cur;
void dfs2(int x,int f) {
    res[x]=cur;
    // 单点修改,区间查询有多少个小于x的数字
    for (int v:edge[x]) {
        if (v==f) continue;
        cur-=Ask(id[v],out[v],x-1);  // v是w
        cur+=Ask(1,id[v]-1,v-1)+Ask(out[v]+1,n,v-1);  // x是w
        // printf("%d -> %d: -=%d; +=%d\n",x,v,Ask(id[v],out[v],v-1),Ask(1,id[v]-1,v-1)+Ask(out[v]+1,n,v-1));
        dfs2(v,x);
        cur-=Ask(1,id[v]-1,v-1)+Ask(out[v]+1,n,v-1);  // x是w
        cur+=Ask(id[v],out[v],x-1);  // v是w
    }
}
int val[maxn];
int solve() {
    cin>>n;
    FOR_(i,1,n-1) {
        int x,y;
        cin>>x>>y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs1(1,0,0);
    FOR_(i,1,n) val[id[i]]=i;
    FOR_(i,1,n) {
        root[i]=root[i-1];
        update(root[i],val[i],1,n);
    }
    FOR_(i,1,n) cur+=Ask(id[i],out[i],i-1);
    dfs2(1,0);
    FOR_(i,1,n) cout<<res[i]<<" "; puts("");
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/