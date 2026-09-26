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
const LL M=998244353;
// ll M=1;
const LL maxn=1e5+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

namespace KDT {
    const double alpha=0.75;
    const int DIM=2;
    struct point {
        int A[DIM],max[DIM],min[DIM];
        int l,r; int size; int sum,val;
        void init(int v) {
            l=r=0; val=v; initval(); 
        }
        void initval() {
            int i; size=1; sum=val;
            REP(i,DIM) min[i]=max[i]=A[i];
        }
    } T[maxn*3]; int TOT;
    int Cur;
    bool cmp(int x,int y) {
        return T[x].A[Cur]<T[y].A[Cur];
    }
    void update(int x) {
        int i; T[x].initval();
        int l=T[x].l,r=T[x].r;
        if (l) T[x].size+=T[l].size,T[x].sum+=T[l].sum;
        if (r) T[x].size+=T[r].size,T[x].sum+=T[r].sum;
        REP(i,DIM) {
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
        if (allin(T[x])) return T[x].sum;
        if (allout(T[x])) return 0;
        int ret=0;
        if (ok(T[x])) ret+=T[x].val;
        if (T[x].size==1) return ret;
        ret+=query(T[x].l);
        ret+=query(T[x].r);
        return ret;
    }
}
int root;

void update(int x,int y,int val) {
    KDT::addnode(root,x,y,val);
}
int query(int xl,int xr,int yl,int yr) {
    KDT::x0=xl; KDT::x1=xr; KDT::y0=yl; KDT::y1=yr;
    return KDT::query(root);
}

array<int,2> A[maxn];
int main() {
    int n,k,q,i;
    ll ans=0;
    scanf("%d%d%d",&n,&k,&q);
    FOR(i,1,n) {
        scanf("%d%d",&A[i][0],&A[i][1]);
        if (A[i][0]<A[i][1]) swap(A[i][0],A[i][1]);
        int X=A[i][0]+A[i][1],Y=A[i][0]-A[i][1]+1;
        update(X,Y,1); ans+=query(X-k,X+k,Y-k,Y+k)-1;
        // printf("query=%d\n",query(X-k,X+k,Y-k,Y+k));
    }
    while (q--) {
        int op; scanf("%d",&op);
        if (op==1) printf("%lld\n",ans);
        else if (op==2) {
            int u; scanf("%d",&u);
            if (k>1e5) continue;
            k=min((ll)1e5,(ll)k*u);
            ans=0;
            FOR(i,1,n) {
                int X=A[i][0]+A[i][1],Y=A[i][0]-A[i][1]+1;
                ans+=query(X-k,X+k,Y-k,Y+k)-1;
            } ans/=2;
        } else {
            int o,x,y;
            scanf("%d%d%d",&o,&x,&y);
            int X,Y; if (x<y) swap(x,y);
            X=A[o][0]+A[o][1],Y=A[o][0]-A[o][1]+1;
            ans-=query(X-k,X+k,Y-k,Y+k)-1; update(X,Y,-1);
            A[o][0]=x; A[o][1]=y;
            X=A[o][0]+A[o][1],Y=A[o][0]-A[o][1]+1;
            update(X,Y,1); ans+=query(X-k,X+k,Y-k,Y+k)-1;
        }
    }
}
/*
*/