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

namespace KDT {
    const double alpha=0.75;
    const int DIM=2;
    struct point {
        int A[DIM],max[DIM],min[DIM];
        int l,r; int size; int val,sum;
        void init(int Val) {
            sum=0; Val=val;
            l=r=0; initval();
        }
        void initval() {
            int i; size=1;
            REP_(i,DIM) min[i]=max[i]=A[i];
        }
    } T[maxn*4]; int TOT;
    int Cur;
    bool cmp(int x,int y) {
        return T[x].A[Cur]<T[y].A[Cur];
    }
    void update(int x) {
        int i; T[x].initval();
        int l=T[x].l,r=T[x].r;
        if (l) T[x].size+=T[l].size;
        if (r) T[x].size+=T[r].size;
        REP_(i,DIM) {
            if (l) {
                T[x].max[i]=max(T[x].max[i],T[l].max[i]);
                T[x].min[i]=min(T[x].min[i],T[l].min[i]);
            }
            if (r) {
                T[x].max[i]=max(T[x].max[i],T[r].max[i]);
                T[x].min[i]=min(T[x].min[i],T[r].min[i]);
            }
        }
    }
    int id[maxn],tot;
    void build(int &x,int l,int r,int cur) { //should have id
        x=0; if (l>r) return;
        int m=(l+r)/2; Cur=cur;
        nth_element(id+l,id+m,id+r+1,cmp);
        x=id[m];
        build(T[x].l,l,m-1,cur^1);
        build(T[x].r,m+1,r,cur^1);
        update(x);
    }
    void getid(int x) { //没有顺序=_=
        id[++tot]=x;
        if (T[x].l) getid(T[x].l);
        if (T[x].r) getid(T[x].r);
    }
    void rebuild(int &x,int cur) {
        tot=0; getid(x);
        build(x,1,tot,cur);
    }
    void insert(int &x,int now,int cur) {
        if (!x) {x=now; return;}
        Cur=cur;
        if (cmp(now,x)) insert(T[x].l,now,cur^1);
        else insert(T[x].r,now,cur^1);
        update(x);
        if (T[x].size*alpha+3<max(T[T[x].l].size,T[T[x].r].size))
            rebuild(x,cur);
    }
    void addnode(int &x,int px,int py,int val) {
        TOT++; T[TOT].A[0]=px; T[TOT].A[1]=py;
        T[TOT].init(val); insert(x,TOT,0);
    }
    int x0,y0,x1,y1;//check两个=_=
    int check(int x,int y) {
        return x0<=x&&x<=x1&&y0<=y&&y<=y1;
    }
    int ok(point &A) {
        return check(A.A[0],A.A[1]);
    }
    int allin(point &A) {
        return  x0<=A.min[0]&&A.max[0]<=x1&&
                y0<=A.min[1]&&A.max[1]<=y1;
    }
    int allout(point &A) {
        return  A.max[0]<x0||x1<A.min[0]||
                A.max[1]<y0||y1<A.min[1];
    }
    int query(int x) {
        if (!x) return 0;
        if (allin(T[x])) return T[x].size;
        if (allout(T[x])) return 0;
        int ret=0;
        if (ok(T[x])) ret++;
        if (T[x].size==1) return ret;
        ret+=query(T[x].l);
        ret+=query(T[x].r);
        return ret;
    }
}

int root;
int Ask(int l,int r,int x) {
    KDT::x0=l; KDT::x1=r;
    KDT::y0=1; KDT::y1=x; 
    return KDT::query(root);
}
void Update(int x,int y,int val) {
    KDT::addnode(root,x,y,val);
}

int n;
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
        int del=Ask(id[v],out[v],x-1);  // v是w
        int add=Ask(1,id[v]-1,v-1)+Ask(out[v]+1,n,v-1);  // x是w
        cur-=del; cur+=add;
        // printf("%d -> %d: -=%d; +=%d\n",x,v,Ask(id[v],out[v],v-1),Ask(1,id[v]-1,v-1)+Ask(out[v]+1,n,v-1));
        dfs2(v,x);
        cur+=del; cur-=add;
    }
}
int solve() {
    cin>>n;
    FOR_(i,1,n-1) {
        int x,y;
        cin>>x>>y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs1(1,0,0);

    FOR_(i,1,n) KDT::id[i]=i;
    FOR_(i,1,n) {
        KDT::T[i].A[0]=id[i];  // x
        KDT::T[i].A[1]=i; // y
        KDT::T[i].init(1); // val
    }
    KDT::TOT=n;

    KDT::build(root,1,n,0);
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