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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
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


int A[maxn],cnt[maxn*4],MIN[maxn*4];
void update(int x,int l,int r,int val,int L,int R) {
    if (l<=L&&R<=r&&(MIN[x]+val>=0||L==R)) {
        if (L==R&&cnt[x]+val<0) {
            if (A[L]==1) return;
            int p=sqrt(A[L]);
            while (p*p<A[L]) p++;
            while (p*p>A[L]) p--;
            // printf("sqrt: x=%d: l=%d; r=%d; val=%d; L,R=%d %d; val=%d->%d; cnt=%d\n",x,l,r,val,L,R,A[L],p,cnt[L]);
            A[L]=p;
            if (A[L]==1) cnt[x]=MIN[x]=INF;
            else cnt[x]=MIN[x]=0;
            return;
        } else {
            // printf("val=%d; sum=%d; L,R=%d %d\n",val,MIN[x],L,R);
            MIN[x]+=val; cnt[x]+=val;
            assert(MIN[x]>=0);
            return;
        }
    }
    int mid=(L+R)/2;
    if (cnt[x]) {
        cnt[x<<1]+=cnt[x]; MIN[x<<1]+=cnt[x];
        cnt[x<<1|1]+=cnt[x]; MIN[x<<1|1]+=cnt[x];
        cnt[x]=0;
    }
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
    
int query(int x,int pos,int L,int R) {
    if (L==R) return cnt[x];
    int mid=(L+R)/2;
    if (cnt[x]) {
        cnt[x<<1]+=cnt[x]; MIN[x<<1]+=cnt[x];
        cnt[x<<1|1]+=cnt[x]; MIN[x<<1|1]+=cnt[x];
        cnt[x]=0;
    }
    int ret;
    if (pos<=mid) ret=query(x<<1,pos,L,mid);
    else ret=query(x<<1|1,pos,mid+1,R);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
    return ret;
}

// 欧拉降幂
inline int mod(LL a,int b){
    if (a<b) return a;
    return a%b+b;
}
inline int poww(int a,int b,int M){
    int ret=1;
    for (;b;b>>=1ll,a=mod(1ll*a*a,M))
        if (b&1) ret=mod(1ll*ret*a,M);
    return ret;
}
ll phi(ll x){
    ll k=x;
    for (ll i=2;i*i<=k;i++) if (k%i==0){
        x=x/i*(i-1);
        while (k%i==0) k/=i;
    } if (k!=1) x=x/k*(k-1);
    return x;
}
int P[maxn];
int a[maxn];
int tot;
int solve(int l,int r,int pos) {
    if (l==r||pos==tot) return mod(a[l],P[pos]);
    int res=solve(l+1,r,pos+1);
    // printf("%d %d %d: pow(%d;%d); mod %d\n",l,r,pos,2,res,P[pos]);
    return poww(a[l],res,P[pos]);
}

int main() {
    P[1]=1e9+7;
    for (tot=1;P[tot]!=1;tot++) P[tot+1]=phi(P[tot]);
    // FOR_(i,1,10) printf("%d ",a[i]);

    int n,q;
    read(n); read(q);
    FOR_(i,1,n) read(A[i]);
    FOR_(i,1,q) {
        int op;
        read(op);
        if (op==1) {
            int l,r;
            read(l); read(r);
            update(1,l,r,-1,1,n);
        } else if (op==2) {
            int l,r;
            read(l); read(r);
            update(1,l,r,1,1,n);
        } else if (op==3) {
            int x;
            read(x);
            int pw=query(1,x,1,n);
            a[1]=A[x]; a[2]=2; a[3]=pw;
            println(solve(1,3,1)%P[1]);
            // cout<<poww(A[x],poww(2,pw,P[1]-1),P[1])%P[1]<<"\n";
        }
    }
    return 0;
}
/*
1 100 2
2 1 1 3 1
2 1 1 3 1
2 1 1 3 1
2 1 1 3 1
2 1 1 3 1
2 1 1 3 1
*/