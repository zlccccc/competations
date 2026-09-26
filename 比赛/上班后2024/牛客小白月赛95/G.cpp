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

// const int mod = 1e9+7;
const int mod=998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this; }
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this; }
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this; }
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this; }
    mint operator+(const mint &a)const { return mint(*this) += a; }
    mint operator-(const mint &a)const { return mint(*this) -= a; }
    mint operator*(const mint &a)const { return mint(*this) *= a; }
    mint operator/(const mint &a)const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x; }
    bool operator==(const mint &a)const { return x == a.x; }
};
istream & operator>>(istream &o,mint &a) { o>>a.x; a=a.fix(); return o; }
ostream & operator<<(ostream &o,const mint &a) { o<<a.x; return o; }

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
    template<typename T, typename... Args>
    inline void read(T &x, Args&... args) { read(x); read(args...); }
}
using namespace fastIO;

ll sameval[maxn],multi=29;
struct Node {
    ll lsum,rsum,weight;
    ll val;
}T[maxn*4];
char s[maxn];
Node Merge(const Node &x,const Node &y) {
    return Node{x.lsum+y.lsum*x.weight,x.rsum*y.weight+y.rsum,x.weight*y.weight};
}
void build(int x,int l,int r) {
    // printf("build %d %d %d\n",x,l,r);
    if (l==r) {
        T[x]=Node{s[l]-'a'+1,s[r]-'a'+1,multi,0};  // multi=29
        return;
    }
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    T[x]=Merge(T[x<<1],T[x<<1|1]);
}
inline void Fix(Node &x,int len,int val) {
    x={val*sameval[len],val*sameval[len],x.weight,val};
}
void change(int x,int l,int r,int L,int R,ll val) {
    // printf("change %d %d %d %d %d %d\n",x,l,r,L,R,val.x);
    if (l<=L&&R<=r) {
        Fix(T[x],R-L+1,val);
        return;
    }
    int mid=(L+R)/2;
    if (T[x].val!=0) {
        Fix(T[x<<1],mid-L+1,T[x].val);
        Fix(T[x<<1|1],R-mid,T[x].val);
        T[x].val=0;
    }
    if (l<=mid) change(x<<1,l,r,L,mid,val);
    if (mid<r) change(x<<1|1,l,r,mid+1,R,val);
    T[x]=Merge(T[x<<1],T[x<<1|1]);
}
Node solve(int x,int l,int r,int L,int R) {
    // printf("solve %d %d %d %d %d\n",x,l,r,L,R);
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (T[x].val!=0) {
        Fix(T[x<<1],mid-L+1,T[x].val);
        Fix(T[x<<1|1],R-mid,T[x].val);
        T[x].val=0;
    }
    Node ret={0,0,1};
    if (l<=mid) ret=Merge(ret,solve(x<<1,l,r,L,mid));
    if (mid<r) ret=Merge(ret,solve(x<<1|1,l,r,mid+1,R));
    T[x]=Merge(T[x<<1],T[x<<1|1]);
    return ret;
}
int solve() {
    int n,q;
    // scanf("%d%d",&n,&q);
    read(n); read(q);
    sameval[0]=0;
    FOR_(i,1,n) sameval[i]=sameval[i-1]*multi+1;
    // scanf("%s",s+1);
    read(s+1);
    build(1,1,n);
    FOR_(i,1,q) {
        int op; read(op);
        // scanf("%d",&op);
        int l,r;
        // scanf("%d%d",&l,&r);
        read(l); read(r);
        if (op==1) {
            auto tomid=[&](int l,int r) {
                int lx=-1,rx=r-l+1;  // 二分到right
                while (lx+1<rx) {
                    int midx=(lx+rx)/2;
                    Node a=solve(1,l,l+midx,1,n),b=solve(1,r-midx,r,1,n);
                    // printf("l,r=%d %d; length=%d; %d %d\n",l,r,midx,a.lsum,b.rsum);
                    if (a.lsum==b.rsum) lx=midx;
                    else rx=midx;
                }
                return lx+1;  // same length
            };
            int len;
            len=tomid(l,r);
            l+=len; r-=len;
            l++; r--;
            // if (l>=r) {puts("YES"); continue;}
            if (l>=r) {println("YES"); continue;}
            Node a=solve(1,l,r,1,n);
            if (a.lsum==a.rsum) {println("YES"); continue;}
            // len=tomid(l,r);
            // l+=len; r-=len;
            // if (l>=r) {println("YES"); continue;}
            else println("NO");
            // puts("solve first type");
        } else {
            char s[2]; read(s);
            change(1,l,r,1,n,s[0]-'a'+1);
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