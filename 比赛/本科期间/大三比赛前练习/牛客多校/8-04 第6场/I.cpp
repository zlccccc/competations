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
typedef unsigned int UI;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=4e5+7;
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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
// int n,m,q;
void initialize() {}
char str[maxn];
  
int ans[maxn];
int root[maxn];
struct node{
    int nxt,l,r,val;
    node(){nxt=l=r=val=0;}
}T[maxn*34]; int tot;
int UL,UR,VAL;
void update(int &x,int y,int L,int R){
    x=++tot; T[x]=T[y]; T[x].val=0;
    if (T[y].val) T[x].nxt=y;
    if (UL<=L&&R<=UR) {
        T[x].val=VAL;
        return;
    } int mid=(L+R)/2;
    if (UL<=mid) update(T[x].l,T[y].l,L,mid);
    if (mid<UR) update(T[x].r,T[y].r,mid+1,R);
}
int lastans,cnt,pos,val;
void query(int x,int L,int R){
    if (!x) return; int pre=0;
    for (int y=x;y;y=T[pre].nxt,T[pre].nxt=0) {
        int v=T[y].val; pre=y;
        if (v&&!ans[v]) {
            if (!lastans) lastans=v;
            else lastans=(ll)v*lastans%M;
            ans[v]=val; cnt++;
        } T[y].val=0;
    }
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) query(T[x].l,L,mid);
    if (mid<pos) query(T[x].r,mid+1,R);
}
vector<int> V;
inline int getid(int x){return lower_bound(V.begin(), V.end(),x)-V.begin()+1;}
struct Query{
    int l,r;
}Q[maxn];
vector<pii> have[maxn];
  
  
namespace fastIO {
#define BUF_SIZE 100000
#define OUT_SIZE 1000000
    bool IOerror = 0;
  
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if (p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
  
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
  
    inline int read(char *s) {
        char ch = nc();
        for (; blank(ch); ch = nc());
        if (IOerror)
            return 0;
        for (; !blank(ch) && !IOerror; ch = nc())
            *s++ = ch;
        *s = 0;
        return 1;
    }
  
    inline int RI(int &a) {
        char ch = nc();
  
        a = 0;
        for (; blank(ch); ch = nc());
        if (IOerror)
            return 0;
        int flag;
        if (ch == '-') {
            flag = -1;
            ch = nc();
        } else { flag = 1; }
        for (; !blank(ch) && !IOerror; ch = nc())
            a = a * 10 + ch - '0';
        a = a * flag;
        return 1;
    }
  
    struct Ostream_fwrite {
        char *buf, *p1, *pend;
  
        Ostream_fwrite() {
            buf = new char[BUF_SIZE];
            p1 = buf;
            pend = buf + BUF_SIZE;
        }
  
        void out(char ch) {
            if (p1 == pend) {
                fwrite(buf, 1, BUF_SIZE, stdout);
                p1 = buf;
            }
            *p1++ = ch;
        }
  
        void flush() {
            if (p1 != buf) {
                fwrite(buf, 1, p1 - buf, stdout);
                p1 = buf;
            }
        }
  
        ~Ostream_fwrite() { flush(); }
    } Ostream;
  
    inline void print(char x) { Ostream.out(x); }
  
    inline void println() { Ostream.out('\n'); }
  
    inline void flush() { Ostream.flush(); }
  
    char Out[OUT_SIZE], *o = Out;
  
    inline void print1(char c) { *o++ = c; }
  
    inline void println1() { *o++ = '\n'; }
  
    inline void flush1() {
        if (o != Out) {
            if (*(o - 1) == '\n')
                *--o = 0;
            puts(Out);
        }
    }
  
    struct puts_write {
        ~puts_write() { flush1(); }
    } _puts;
};
inline void out(int x){
    if (x>9) out(x/10);
    fastIO::Ostream.out(x%10+'0');
}
int main() {
    int T,_T;
    scanf("%d",&T);
    FOR(_T,1,T){
        fastIO::Ostream.out('C');
        fastIO::Ostream.out('a');
        fastIO::Ostream.out('s');
        fastIO::Ostream.out('e');
        fastIO::Ostream.out(' ');
        fastIO::Ostream.out('#');
        out(_T);
        fastIO::Ostream.out(':');
        fastIO::Ostream.out('\n');
        int i;
        int n,m;
        V.clear(); tot=0;
        fastIO::RI(n);
        fastIO::RI(m);
        FOR(i,1,n){
            fastIO::RI(Q[i].l);
            fastIO::RI(Q[i].r);
            V.push_back(Q[i].l); V.push_back(Q[i].r);
        } FOR(i,1,n) ans[i]=0;
        V.push_back(INF); V.push_back(-INF);
        sort(V.begin(),V.end());
        V.erase(unique(V.begin(), V.end()),V.end());
        FOR(i,1,(int)V.size()) have[i].clear();
        FOR(i,1,n) have[getid(Q[i].l)].push_back(make_pair(getid(Q[i].r),i));
        FOR(i,1,(int)V.size()) root[i]=0;
        FOR(i,1,(int)V.size()){
            root[i]=root[i-1];
            for (auto x:have[i]) {
                UL=i; UR=x.first; VAL=x.second;
                update(root[i],root[i],1,V.size());
            }
        } lastans=0;
        FOR(i,1,m) {
            int pos;
            fastIO::RI(pos); pos^=lastans;
            int l=getid(pos); int r=l;
            lastans=0; cnt=0;//V[l]<=pos
            if (r<=(int)V.size()) {
                if (V[l-1]>pos) l--;
                ::pos=r,::val=i;
                query(root[l],1,V.size());
            }
            // printf("query: pos=%d l=%d r=%d; %d %d; lastans=%d\n",pos,l,r,V[l-1],pos,lastans);
            // printf("  lastans: %d\n",lastans);
            out(cnt);
            fastIO::Ostream.out('\n');
        }
        FOR(i,1,n) out(ans[i]),fastIO::Ostream.out(" \n"[i==n]);
    }
}
/*
4
  
3 4
1 3 2 6 -999 1000000000
-1000 1 5 2
  
3 3
1 2 3 7 -2 0
2 7 0
  
4 10
1 1 3 3 5 5 7 7
0 100 2 100 4 100 6 100 8 100
  
4 4
-1 1 -2 2 3 6 7 9
2 3 8 0
*/