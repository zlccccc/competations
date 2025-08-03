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

struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx) : f(mx + 1), g(mx + 1) {
        f[0] = 1;
        FOR_(i, 1, mx) f[i] = f[i - 1] * i;
        g[mx] = f[mx].pow(mod - 2);
        rFOR_(i, 1, mx) g[i - 1] = g[i] * i;
    }
    mint operator()(int a, int b) {
        if (b < 0 || a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} Comb(maxn); // Combination(x,y)

// Arrange(x,y)
mint Arra(int a, int b) { return Comb.f[a] * Comb.g[a - b]; }
// the number of way from (0, 0) to (w, h) which dosn't exceed line y = x + bound (y-x<=bound)
mint Catalan(int w, int h, int bound) { return Comb(w + h, h) - Comb(w + h, h - bound - 1); }

char s[maxn],str[maxn];
int p[maxn],l[maxn];  // manacher

struct node{
    int l,r,val;
}T[maxn*32];
int tot;
void update(int &x,int pos,int val,int L,int R) {
    T[++tot]=T[x]; x=tot;
    T[x].val+=val;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,val,L,mid);
    if (mid<pos) update(T[x].r,pos,val,mid+1,R);
}
int query(int x,int y,int l,int r,int L,int R) {
    if (!x&&!y) return 0;
    if (l<=L&&R<=r) return T[y].val-T[x].val;
    int mid=(L+R)/2,ret=0;
    if (l<=mid) ret+=query(T[x].l,T[y].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,T[y].r,l,r,mid+1,R);
    // printf("query x=%d,y=%d; %d -> %d: %d; cur=%d\n",x,y,L,R,ret,T[x].val);
    return ret;
}
// int rootrx[maxn],rootrval[maxn];
int root[maxn];
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    scanf("%s",s);
    {
        str[0]='+'; str[1]='%';
        REP_(i,n) {
            str[i*2+2]=s[i];
            str[i*2+3]='%';
        }
        int id=0,mx=0;
        FOR_(i,1,n*2+2) {
            if (mx>i) p[i]=min(p[2*id-i],mx-i);
            else p[i]=1;
            while (str[i+p[i]]==str[i-p[i]]) p[i]++;
            if (p[i]+i>mx) { mx=p[i]+i; id=i; }
        }
    }
    FOR_(i,1,n) l[i]=p[i*2]-1;
    // FOR_(i,1,n) printf("%d ",l[i]); puts("<- l");
    // puts(str);
    // FOR_(i,1,n*2+2) printf("%d ",p[i]); puts("<- manacher");
    {
        FOR_(i,1,n) {
            root[i]=root[i-1];
            // printf("upd %d: %d\n",i,(l[i]+1)/2);
            update(root[i],(l[i]+1)/2,1,1,n);
        }
    }
    FOR_(i,1,m) {
        int x,y,k;
        // scanf("%d%d",&x,&y); k=1;
        scanf("%d%d%d",&x,&y,&k);
        int l=0,r=(y-x)/2+1+1;  // r: maxlength
        // printf("l=%d; r=%d\n",l,r);
        while (l+1<r) {
            int mid=(l+r)/2;
            auto getRes=[&](int len) {
                int res=query(root[x+len-1-1],root[y-len+1],len,n,1,n);
                // printf("ask len=%d : %d -> %d; >= %d = %d\n",len,x+len-1-1,y-len+1,len,res);
                return res;
            };
            if (getRes(mid)>=k) l=mid;
            else r=mid;
        }
        ll res=(ll)l*l;
        printf("%lld\n",res);
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
10 10
aababaabbb
1 10
1 1
1 3
2 4
*/