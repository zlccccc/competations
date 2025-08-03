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
const LL maxn=3e5+107;
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


namespace fastIO {//感觉没问题, 测试几次
#define BUF_SIZE 100000
    namespace Istream {
        bool IOerror = 0;
        inline char ic() {
            static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
            if (p1==pend) {
                p1=buf;
                pend=buf+fread(buf,1,BUF_SIZE,stdin);
                if (pend == p1) {IOerror = 1; return -1;}
            } return *p1++;
        }
        inline bool blank(char ch) {
            return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
        }
        template<typename T>
        inline void readPositive(T &x) {//no
            char ch; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
        }
        template<typename T>
        inline void read(T &x) {
            char ch; T op=1; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            if (ch=='-') op=-1,ch=ic();
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
            x*=op;
        }
        inline void read(char &c) {
            c=ic();
        }
        inline void read(char *s) { //len
            char ch;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (; !blank(ch)&&!IOerror; ch=ic()) *s++=ch;
            *s='\0';
        }
    }
    namespace Ostream {
        char buf[BUF_SIZE], *p1 = buf, *pend = buf + BUF_SIZE;
        inline void flush() {
            fwrite(buf,1,p1-buf,stdout);
            p1=buf;
        }
        inline void oc(char ch) {
            if (p1 == pend) flush();
            *p1++=ch;
        }
        inline void println() {
            oc('\n');
        }
        template<typename T>
        inline void print(T x) {
            static char s[27],*s1=s;
            if (!x) *s1++='0';
            if (x<0) oc('-'),x=-x;
            while (x) *s1++=x%10+'0',x/=10;
            do {s1--; oc(*s1);} while (s1!=s);
        }
        inline void print(char s) {
            oc(s);
        }
        inline void print(char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(const char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(string s) {
            for (unsigned i=0; i<s.length(); i++) oc(s[i]);
        }
        struct _flush {
            ~_flush() {flush();}
        } fflush;
    };
    template<typename T>
    inline void read(T &x) {Istream::readPositive(x);}
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

// 考虑两端点即可
// 不能删除, 用不删莫队; ST表O(1)lca
struct Edges {
    int to; LL len; int next;
    Edges(int _to=0,LL _len=0,int _next=0):to(_to),len(_len),next(_next) {}
} edge[maxn*2]; int etot;
int head[maxn];
int fa[maxn];
LL uplen[maxn];
int id[maxn],dfn[maxn],idtot;
inline void addedge(int u,int v,LL len) {
    edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
}
namespace LCA {//内部和外部dfn不同...
    int dep[maxn]; LL len[maxn];
    int st_dfn[maxn],tot;
    int ST[maxn*2][20];//only L
    void dfs(int x,int f,int d,LL l) {
        int i; dep[x]=d; len[x]=l;
        st_dfn[x]=++tot; ST[tot][0]=x;
        ::id[++idtot]=x; ::dfn[x]=idtot;
        for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f) {
                int v=edge[i].to;
                ::fa[v]=x; ::uplen[v]=edge[i].len;
                dfs(v,x,d+1,l+edge[i].len);
                ST[++tot][0]=x;
            }
    }
    int t_t[maxn*2];
    inline void initST(int n) {
        int i,j;
        FOR(i,1,n*2) t_t[i]=t_t[i>>1]+1;
        FOR(i,1,n*2) {
            rep(j,1,t_t[i]) {
                int u=ST[i][j-1],v=ST[i-(1<<(j-1))][j-1];
                ST[i][j]=dep[u]<dep[v]?u:v;
            }
        }
    }
    inline int lca(int x,int y) {
        x=st_dfn[x]; y=st_dfn[y];
        if (x>y) swap(x,y);
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t]; y=ST[y][t];
        return dep[x]<dep[y]?x:y;
    }
    inline LL dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int));
        etot=idtot=tot=0;
    }
}

ll V[maxn];
int R[maxn];
int BID[maxn],SIZE=500;
vector<pair<pii,int> > Q[maxn];
vector<pii> _Q[maxn];
pii update(pii x,int pos) {
    ll ini=LCA::dis(x.first,x.second);
    ll val1=LCA::dis(pos,x.first);
    ll val2=LCA::dis(pos,x.second);
    if (ini>val1&&ini>val2) return x;
    if (val1>val2) return make_pair(pos,x.first);
    else return make_pair(pos,x.second);
}
int main() {
    int i,j;
    int n,q; read(n); read(q);
    // scanf("%d%d",&n,&q);
    LCA::init(n);
    FOR(i,1,n-1) {
        int u,v,w;
        read(u); read(v); read(w);
        // scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    } LCA::dfs(1,0,0,0);
    LCA::initST(n);
    // FOR(i,1,n) FOR(j,1,n) printf("%d-%d:%lld\n",i,j,LCA::dis(i,j));
    FOR(i,1,n) {BID[i]=i/SIZE; R[i/SIZE]=i;}
    FOR(i,1,q) {
        int l,r; read(l); read(r);
        // scanf("%d%d",&l,&r);
        int id=BID[l];
        if (R[id]>r) {
            pii ans=make_pair(l,l);
            FOR(j,l+1,r) ans=update(ans,j);
            V[i]=LCA::dis(ans.first,ans.second);
            // printf("CAL %d %d\n",ans.first,ans.second);
        } else Q[id].push_back(make_pair(make_pair(l,r),i));
    }
    FOR(i,0,n) if (Q[i].size()) {//BLOCK
        pii ans=make_pair(R[i],R[i]);
        for (auto now:Q[i])
            _Q[now.first.second].push_back(make_pair(now.first.first,now.second));
        FOR(j,R[i],n) {
            ans=update(ans,j);
            for (auto now:_Q[j]) {
                pii noww=ans; int k;
                FOR(k,now.first,R[i]-1) noww=update(noww,k);
                // printf("query %d %d %d: %d %d\n",now.first,j,now.second,noww.first,noww.second);
                V[now.second]=LCA::dis(noww.first,noww.second);
            } _Q[j].clear();
        } Q[i].clear();
    }
    FOR(i,1,q) println(V[i]);
    // printf("%lld\n",V[i]);
}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/