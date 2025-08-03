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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));


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

int use[maxn];
priority_queue<int> Q[maxn];
int solve() {
    int n;
    scanf("%d",&n);
    FOR_(i,1,n) {
        int op,x;
        scanf("%d%d",&op,&x);
        if (op==1) {
            Q[x].push(i);
        } else {
            if (Q[x].size()) {
                use[Q[x].top()]=1;
                Q[x].pop();
            } else {
                return 0*puts("-1");
            }
            use[i]=-1;
        }
    }
    int cur=0,res=0;
    FOR_(i,1,n) {
        cur+=use[i];
        res=max(res,cur);
    }
    printf("%d\n",res);
    FOR_(i,1,n) if (use[i]!=-1) printf("%d ",use[i]);
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
    return 0;
}
/*
7 2
1 2
1 3
1 4
3 5
4 6
3 7
1 6 5 1
2 6 7 3
*/