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
const LL M=998244353;
const LL maxn=2e6+7;
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
    // inline void read(T &x) {Istream::readPositive(x);}
    inline void read(T &x) {Istream::read(x);} //negative
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;


int n;
int pos[maxn];
pair<pii,int> Q[maxn];
int MAX[maxn],ans[maxn];
inline int lowbit(int x) {return x&-x;}
inline void update(int x,int val) {
    x=n+1-x;
    for (;x<=n;x+=lowbit(x)) max_(MAX[x],val);
}
inline int query(int x) {
    x=n+1-x;
    int ret=0;
    for (;x;x-=lowbit(x)) ret=max(ret,MAX[x]);
    return ret;
}
int A[maxn];
set<int> S;//right-max-values
int fa[maxn];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    int i,q;
    // scanf("%d",&n);
    read(n);
    FOR(i,1,n) read(A[i]); //scanf("%d",&A[i]);
    // scanf("%d",&q);
    read(q);
    FOR(i,1,q) {
        // assert(scanf("%d%d",&Q[i].first.first,&Q[i].first.second)==2);
        read(Q[i].first.first);
        read(Q[i].first.second);
        Q[i].second=i;
    }
    FOR(i,1,q) swap(Q[i].first.first,Q[i].first.second);
    sort(Q+1,Q+1+q); int nowQ=1;
    FOR(i,1,q) swap(Q[i].first.first,Q[i].first.second);
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,n) {
        int prev=pos[A[i]];
        if (prev) fa[prev]=prev+1;
        update(prev+1,i-prev-1);
        pos[A[i]]=i;
        while(nowQ<=q&&Q[nowQ].first.second==i) {
            auto now=Q[nowQ++];
            int l=now.first.first,id=now.second;
            int lmax=getfa(l);
            max_(ans[id],i-lmax);
            max_(ans[id],query(l));
            // printf("%d->%d: r=%d mid=%d\n",l,i,i-lmax,query(l));
            // for (int v:S) printf("%d ",v); puts("<- Set inside");
        }
    } S.clear();
    FOR(i,1,2000000) pos[i]=0; nowQ=1;
    sort(Q+1,Q+1+q); reverse(Q+1,Q+1+q);
    FOR(i,1,n) fa[i]=i;
    rFOR(i,1,n) {
        int prev=pos[A[i]];
        if (prev) fa[prev]=prev-1;
        pos[A[i]]=i;
        while(nowQ<=q&&Q[nowQ].first.first==i) {
            auto now=Q[nowQ++];
            int r=now.first.second,id=now.second;
            int rmax=getfa(r);
            max_(ans[id],rmax-i);
            // printf("%d->%d: left=%d\n",i,r,rmax-i);
            // for (int v:S) printf("%d ",v); puts("<- Set inside");
        }
    } S.clear();
    // FOR(i,1,q) printf("%d\n",ans[i]);
    FOR(i,1,q) println(ans[i]);
}
/*
*/