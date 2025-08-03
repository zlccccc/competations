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

namespace LCT {
    const int maxn=1e5+7;
    struct info {
        int size,sum;
        info(int _val=-INF,int _size=1):
            size(_size),sum(_val) {}
        void print() {
            debug(" debug: infomation: sum=%d size=%d\n",sum,size);
        }
    };
    struct tag {
        int same,add;//same:lazy
        tag() {same=-INF; add=0;}
        bool tagadd() {return (add!=0);}
        bool tagsame() {return (same!=-INF);}
    };
    info merge(const info &x,const info &y) {
        info ret=x;
        ret.size+=y.size;
        ret.sum+=y.sum;
        return ret;
    }
    struct node {
        int son[2],fa;
        int val;
        info chain; tag chaintag;
        bool rev,isroot;//root=1:isroot
        void init(int _val) {
            val=_val;
            chain=info(val);
            chaintag=tag();
            rev=0; son[0]=son[1]=0;
            fa=0; isroot=1;
        }
    } T[maxn];
    void Reverse(int x) {
        T[x].rev^=1;
        swap(T[x].son[0],T[x].son[1]);
    }
    void pushup(int x) {
        T[x].chain=info(T[x].val);//clear
        if (T[x].son[0])
            T[x].chain=merge(T[T[x].son[0]].chain,T[x].chain);
        if (T[x].son[1])
            T[x].chain=merge(T[x].chain,T[T[x].son[1]].chain);
    }
    void pushdown(int x) {
        if (T[x].rev) {
            if (T[x].son[0]) Reverse(T[x].son[0]);
            if (T[x].son[1]) Reverse(T[x].son[1]);
            T[x].rev=0;
        }
    }
    void rotate(int x,int kind) {
        int y=T[x].fa,z=T[y].fa;
        T[y].son[!kind]=T[x].son[kind],T[T[x].son[kind]].fa=y;
        T[x].son[kind]=y,T[y].fa=x;
        if (T[y].isroot) {T[x].isroot=true; T[y].isroot=false;}
        else T[z].son[T[z].son[1]==y]=x;
        T[x].fa=z; pushup(y);
    }
    void PreChange(int x) {//change_from_root
        static int ids[maxn],i,k;
        for (k=0; !T[x].isroot; k++){
            ids[k]=x,x=T[x].fa;
        } ids[k++]=x;
        rREP_(i,k) pushdown(ids[i]);
    }
    void splay(int x) { //to root
        PreChange(x);
        while (!T[x].isroot) {
            int y=T[x].fa,z=T[y].fa;
            int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
            if (T[y].isroot) rotate(x,rx);
            else {
                if (rx==ry) rotate(y,ry);
                else rotate(x,rx);
                rotate(x,ry);
            }
        } pushup(x);
    }
    int access(int x) {
        int y=0;
        for (; x; x=T[x].fa) {
            splay(x);
            T[T[x].son[1]].isroot=true;
            T[x].son[1]=y;
            T[y].isroot=false;
            y=x; pushup(x);
        } return y;
    }
    bool judge(int u,int v) {
        while (T[u].fa) u=T[u].fa;
        while (T[v].fa) v=T[v].fa;
        return u==v;
    }
    void makeroot(int x) {
        access(x); splay(x);
        Reverse(x);
    }
    bool link(int u,int v) {
        if (judge(u,v)) return 1;
        makeroot(u); T[u].fa=v;
        return 0;
    }
    bool cut(int u,int v) {
        makeroot(u); splay(v);
        T[T[v].son[0]].fa=T[v].fa;
        T[v].fa=0;
        T[T[v].son[0]].isroot=true;
        T[v].son[0]=0;
        pushup(v);
        return 0;
    }
    pair<int,int> ask(int u,int v) {
        makeroot(u); access(v); splay(v);
        return {T[v].chain.sum,T[v].chain.size};
    }
};

int solve() {
    int n,q;
    scanf("%d%d",&n,&q);
    FOR_(i,1,n) LCT::T[i].init(i);  // initialize
    vector<set<int>> edge(n+1);
    int prevres=0;
    FOR_(i,1,q) {
        ll A,B,C;
        scanf("%lld%lld%lld",&A,&B,&C);
        int op=1+(((A*(1+prevres))%998244353)%2);
        int u=1+(((B*(1+prevres))%998244353)%n);
        int v=1+(((C*(1+prevres))%998244353)%n);
        // printf("ask %d %d %d\n",op,u,v);
        int samelink=LCT::judge(u,v);
        // printf("same=%d\n",samelink);
        if (op==1) {
            if (samelink) LCT::cut(u,v);
            else LCT::link(u,v);
        } else {
            if (!samelink) prevres=0;
            else {
                pii cur=LCT::ask(u,v);
                // printf("ask res=%d %d\n",cur.first,cur.second);
                if (cur.second!=3) prevres=0;
                else prevres=cur.first-u-v;
            }
            printf("%d\n",prevres);
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