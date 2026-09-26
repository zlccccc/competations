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


vector<int> edge[maxn];
int leftmax[maxn];//better than x
int f[maxn],w[maxn];//ans
// set<pair<pii,pii> > S;//get lower and upper(left&rig)
vector<pair<pii,pii> > S;//get lower and upper(left&rig)
int dep[maxn];
int dfn[maxn],rig[maxn],tot;//dfn
vector<pii> ask[maxn];
//getlca; dfn
void dfs(int x,int depth){
    dfn[x]=++tot; dep[x]=depth;
    S.push_back(make_pair(make_pair(dep[x],w[x]),make_pair(tot,x)));
    // S.insert(make_pair(make_pair(dep[x],w[x]),make_pair(tot,x)));
    for (int v:edge[x]) {
        // printf("%d %d\n",v,x);
        dfs(v,depth+1);
    } rig[x]=tot;
    ask[rig[x]].push_back(make_pair(dfn[x],x));
}
inline int lowbit(int x) {return x&-x;}
int n,sum[maxn];
void update(int x,int val) {
    for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}
int query(int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=sum[x];
    return ret;
}
vector<pii> V[maxn];
int main() {
    int i,x;
    // scanf("%d%d",&n,&x);
    // FOR(i,2,n) {int p; scanf("%d",&p); edge[p].push_back(i);}
    // FOR(i,1,n) scanf("%d",&w[i]);
    read(n); read(x);
    FOR(i,2,n) {int p; read(p); edge[p].push_back(i);}
    FOR(i,1,n) read(w[i]);
    dfs(1,1);
    sort(S.begin(), S.end());
    FOR(i,1,n) {
        auto should=make_pair(dep[i],w[i]^x),pos=make_pair(dfn[i],i);
        // auto it=S.lower_bound(make_pair(should,pos));
        // if (it!=S.end()&&it->first==should) {//-1
        //     // printf("get:done; %d %d\n",it->second.first,it->second.second);
        //     if (it->second==pos) it++;
        //     if (it!=S.end()&&it->first==should) {
        //         int pos=it->second.second;//nxt position
        //         int l=dfn[i],r=dfn[pos];
        //         V[r].push_back(make_pair(dep[i],l));
        //         // printf("nxt x=%d; pos=%d; dep=%d l,r=%d %d\n",i,pos,dep[i],l,r);
        //     }
        // }
        auto it=lower_bound(S.begin(), S.end(), make_pair(should,pos));
        // auto it=S.lower_bound(make_pair(should,pos));
        if (it!=S.begin()) {
            it--;
            if (it->first==should) {
                int pos=it->second.second;//nxt position
                int l=dfn[pos],r=dfn[i];
                V[r].push_back(make_pair(dep[i],l));
                // printf("prev x=%d; pos=%d; dep=%d l,r=%d %d\n",i,pos,dep[i],l,r);
            }
        }
    }
    int all=0;
    FOR(i,1,n) {
        for (auto v:V[i]) {//change left
            int d=v.first,l=v.second;
            if (!leftmax[d]) all++;
            if (leftmax[d]<l) {
                if (leftmax[d]) update(leftmax[d],-1);
                leftmax[d]=l;
                update(leftmax[d],1);
            }
        }
        for (auto v:ask[i]) {
            int l=v.first,id=v.second;
            f[id]=all-query(l-1);
        }
    }
    int ans=0;
    // FOR(i,1,n) printf("%d ",f[i]); puts("<- f");
    FOR(i,1,n) add_(ans,i^(n-f[i]));
    printf("%d\n",ans);
}
/*
10 0
5 10 5 1 1 9 2 6 5
5 0 5 5 5 5 5 5 0 5
*/