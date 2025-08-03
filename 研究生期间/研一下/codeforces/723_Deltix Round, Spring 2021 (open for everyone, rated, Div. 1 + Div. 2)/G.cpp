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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

typedef pair<int,pii> P_P;
namespace KDT {
    const double alpha=0.75;
    const int DIM=2;
    struct point {
        int A[DIM],max[DIM],min[DIM];
        int l,r; int size;
        P_P val,MIN;
        void init(P_P now) {
            l=r=0; val=now; initval();
        }
        void initval() {
            int i; size=1; MIN=val;
            REP(i,DIM) min[i]=max[i]=A[i];
        }
    } T[maxn]; int TOT;
    int Cur;
    bool cmp(int x,int y) {
        return T[x].A[Cur]<T[y].A[Cur];
    }
    void update(int x) {
        int i; T[x].initval();
        int l=T[x].l,r=T[x].r;
        if (l) T[x].size+=T[l].size,T[x].MIN=min(T[x].MIN,T[l].MIN);
        if (r) T[x].size+=T[r].size,T[x].MIN=min(T[x].MIN,T[r].MIN);
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
    void addnode(int &x,int px,int py,P_P val) {
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
    P_P ans;
    int query(int x) {
        if (!x) return 0;
        if (allin(T[x])) {
            ans=min(ans,T[x].MIN);
            return T[x].size;
        }
        if (allout(T[x])) return 0;
        int ret=0;
        if (ok(T[x])) {
            ans=min(ans,T[x].val);
            ret++;
        }
        if (T[x].size==1) return ret;
        ret+=query(T[x].l);
        ret+=query(T[x].r);
        return ret;
    }
}

int root=0;
vector<P_P> P[maxn];
queue<pii> Q;
int Ans[maxn];
int main() {
    int i,n,m;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        int l,r; scanf("%d%d",&l,&r);
        P[r-l+1].push_back(make_pair(i,make_pair(l,r)));
    }
    rFOR(i,1,n) {
        for (auto now:P[i]) 
            KDT::addnode(root,now.second.first,now.second.second,now);
        int ans=0;
        Q.push(make_pair(1,n));
        while (Q.size()) {
            auto now=Q.front(); Q.pop();
            int l=now.first,r=now.second;
            KDT::x0=l; KDT::x1=n;
            KDT::y0=1; KDT::y1=r;
            KDT::ans=make_pair(m+1,make_pair(n+1,n+1));
            KDT::query(root);
            if (KDT::ans.first!=m+1) {
                int L=KDT::ans.second.first,R=KDT::ans.second.second;
                // printf("addans %d %d\n",L,R);
                ans+=R-L+1;
                Q.push(make_pair(l,L-1));
                Q.push(make_pair(R+1,r));
            }
        }
        Ans[i]=ans;
    }
    FOR(i,1,n) printf("%d\n",Ans[i]);
}
/*
10 80
2 7
5 10
3 8
3 5
1 7
6 7
3 8
1 2
5 7
3 10
2 9
2 6
1 8
3 8
4 5
8 9
5 8
1 9
2 4
2 9
3 5
6 10
7 9
1 2
8 9
1 8
1 9
2 7
5 7
9 9
2 10
1 5
3 6
2 10
5 9
2 3
6 9
6 8
4 8
8 10
6 8
2 10
1 5
1 5
9 10
2 10
5 8
1 9
1 4
10 10
1 7
4 9
7 8
3 9
5 9
4 9
1 4
5 10
4 4
7 10
1 9
3 10
4 8
1 5
5 5
2 10
2 10
4 7
6 8
5 9
6 9
1 8
5 7
2 10
9 10
9 10
5 9
6 7
5 9
1 3
5 9
2 4
2 10
3 10
10 10
2 10
5 8
3 10
3 10
6 8
1 5
4 8
5 10

*/