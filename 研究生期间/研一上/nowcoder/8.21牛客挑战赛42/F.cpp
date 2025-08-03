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
const LL maxn=1e5+107;
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

//输出写错了....坑爹啊
int bit[100][100][100];//block
vector<int> v;
int A[100][100],used[100][100];
int SUM[1<<16|7],val[20];
int q[maxn][4],ans[maxn];
int fin[60000000];
int p[5000000],tot;
int main() {
    int n,limit,i,j,k,sum=0;
    // scanf("%d%d",&n,&limit);
    read(n); read(limit);
    //筛下看看能不能过...
    sum=1;
    // float t_ss=clock();
    FOR(i,2,limit){
        if (!fin[i]) p[tot++]=i,fin[i]=powMM(i,limit);
        REP(j,tot){
            //感觉上不会爆,因为是从小往筛的
            if (i*p[j]>limit) break;
            fin[i*p[j]]=(ll)fin[i]*fin[p[j]]%M;
        }
        add_(sum,fin[i]);
    }
    // printf("fir %f\n",clock()-t_ss);
    // FOR(i,1,limit) printf("%d(%lld) ",fin[i],powMM(i,limit)); puts(" <- fin");
    // sum=0;
    // FOR(i,1,limit) add_(sum,powMM(i,limit));
    FOR(i,1,n) FOR(j,1,n) {
        // A[i][j]=rand()%limit+1;
        read(A[i][j]);
        // scanf("%d",&A[i][j]);
        v.push_back(A[i][j]);
    } sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    int m;
    read(m);
    // scanf("%d",&m);
    // float t_st=clock();
    FOR(i,1,m) {
        read(q[i][0]); read(q[i][1]); read(q[i][2]); read(q[i][3]);
        // scanf("%d%d%d%d",&q[i][0],&q[i][1],&q[i][2],&q[i][3]);
        if (q[i][0]>q[i][2]) swap(q[i][0],q[i][2]);
        if (q[i][1]>q[i][3]) swap(q[i][1],q[i][3]);
        // REP(j,4) q[i][j]=rand()%n+1;
        ans[i]=sum;
    }
    FOR(i,1,n) FOR(j,1,n) {
        A[i][j]=lower_bound(v.begin(),v.end(),A[i][j])-v.begin();
    }
    const int BLOCK=15; int o;
    REP(o,((int)v.size()-1+BLOCK)/BLOCK) {//COUNT
        int L=o*BLOCK,R=L+BLOCK-1;
        // printf("%d - %d\n",L,R);
        FOR(i,L,R) {
            if (i<(int)v.size()) val[i-L]=powMM(v[i],limit);
            else val[i-L]=0;
            SUM[1<<(i-L)]=val[i-L];
        } SUM[0]=0;
        REP(i,(1<<BLOCK)) if (i) {
            int lowbit=i&-i;
            if (i==lowbit) continue;
            SUM[i]=(SUM[i^lowbit]+SUM[lowbit])%M;
        }
        FOR(i,1,n) {
            FOR(j,1,n) {//j to k
                if (L<=A[i][j]&&A[i][j]<=R) {
                    bit[j][j][i]=1<<(A[i][j]-L);
                    used[i][j]=1;
                } else bit[j][j][i]=0;
            }
            FOR(j,1,n) FOR(k,j+1,n)
                bit[j][k][i]=bit[j][k-1][i]|bit[k][k][i];
        }
        FOR(i,1,m) {
            int x=q[i][0],y=q[i][1],X=q[i][2],Y=q[i][3];
            //y-Y
            int now=0;
            FOR(j,x,X) now|=bit[y][Y][j];
            // printf("%d ",i); pr2(now,BLOCK); puts ("  < << ");
            add_(ans[i],M-SUM[now]);
        }
        // FOR(i,1,n) FOR(j,1,n) printf("%d%c",A[i][j]," \n"[j==n]);
    }
    FOR(i,1,m) println(ans[i]);
    // FOR(i,1,m) printf("%d\n",ans[i]);
    // printf("%f\n",clock()-t_st);
}
/*
3 9
1 1 1
1 1 1
1 1 1
3
1 1 1 1
2 2 3 3
*/