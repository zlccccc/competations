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

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};

mint pw2[maxn*2];
struct node{
    vector<ull> v;
    node(int x) {
        v.resize((x+63)/64,0ull);
    };
    void set(int x) {
        v[x/64]|=1ull<<(ull)(x%64);
    }
};

mint getXorValue(const node &x,const node &y) {
    mint ret=0,mul=1;
    REP_(i,x.v.size()) ret+=mul*(int)((x.v[i]^y.v[i])%(ull)mod),mul*=pw2[64];
    return ret;
}
mint getCount(const node &x1,const node &x2,const node &y1,const node &y2) {
    int cnt1=0,cnt2=0;
    REP_(i,x1.v.size()) {
        cnt1+=__builtin_popcountll(x1.v[i]&y1.v[i]);
        cnt2+=__builtin_popcountll(x2.v[i]&y2.v[i]);
    }
    return mint(cnt1)*cnt2;
}
int solve() {
    int n,m;
    cin>>n>>m;
    pw2[0]=1;
    rep_(i,1,maxn*2) pw2[i]=pw2[i-1]*2;
    vector<string> A(n);
    REP_(i,n) {
        cin>>A[i];
        reverse(A[i].begin(),A[i].end());
    }
    bool solve1=false;
    bool solve2=false;
    if (n<m) solve1=1; else solve2=1;
    // solve1=solve2=1;
    if (solve1) {
        vector<node> vec(n,node(m));
        REP_(i,n) REP_(j,m) if (A[i][j]=='1') vec[i].set(j);
        mint res=0;
        REP_(i,n) rep_(j,i+1,n) {
            // {
            //     mint tmp=0;
            //     REP_(k,m) if (A[i][k]!=A[j][k]) tmp+=pw2[k];
            //     printf("TMP=%lld\n",tmp.x);
            // }
            mint cur=getXorValue(vec[i],vec[j]);
            res+=cur*cur;
            // printf("cur=%lld\n",cur.x);
        }
        cout<<res.x<<endl;
    }
    if (solve2) {
        vector<array<node,2>> vec(m,{node(n),node(n)});
        REP_(i,n) REP_(j,m) {
            vec[j][(int)(A[i][j]-'0')].set(i);
            // if (j==47) {
            //     printf("%d %d\n",i/64,1ull<<(ull)(i%64));
            //     printf("j=%d %d; sz=%d %lld %lld\n",j,A[i][j]-'0',vec[j][0].v.size(),vec[j][0].v[0],vec[j][1].v[0]);
            // }
        }
        mint res=0;
        REP_(i,m) rep_(j,i,m) {
            mint cnt1=getCount(vec[i][0],vec[i][1],vec[j][0],vec[j][1]);
            mint cnt2=getCount(vec[i][0],vec[i][1],vec[j][1],vec[j][0]);
            mint cnt=cnt1+cnt2;
            if (i!=j) cnt*=2;
            res+=cnt*pw2[i+j];

            // {
            //     mint tmp=0;
            //     REP_(x,n) rep_(y,x,n) if (A[x][i]!=A[y][i]&&A[x][j]!=A[y][j]) tmp+=1;
            //     if (i!=j) tmp*=2;
            //     if ((tmp-cnt).x) {
            //         printf("i=%d; j=%d\n",i,j);
            //         REP_(x,n) printf("%c ",A[x][i]); puts(" <- A");
            //         printf("vec=%lld %lld; %d\n",vec[i][0].v[0],vec[i][1].v[0],vec[i][0].v.size());
            //         printf("TMP=%lld; cnt=%lld; div=%lld\n",tmp.x,cnt.x,(tmp-cnt).x);
            //         printf("%d %d\n",cnt1.x,cnt2.x);
            //     }
            //     // res+=tmp*pw2[i+j];
            // }
        }
        cout<<res.x<<endl;
    }
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    // while (1) solve();
    FOR_(_,1,T){
        solve();
    }
}
/*
3 72
011001101011101011010110110011001101101001010101110101111000111010100111
010100010101010101111101010101010110101000011111111110100101001010110011
111100101010110101010110011010100101101010101010101010100100110101111001

3 20
01100110101110101100
01010001010101010111
11110010101011010100
*/