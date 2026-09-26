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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
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


inline ll powMM(ll a, ll b, ll mod) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}

namespace BruteForce {
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod)  { //C=A*B
        int n=A.size(),m=B.size();
        if (!n||!m) return vector<int>();
        vector<int> C(n+m-1,0);
        REP_(i,n) REP_(j,m) add_(C[i+j],(ll)A[i]*B[j]%mod,mod);
        return C;
    }
}

// FOR NTT
namespace NTT {
    static const int MOD=998244353;
    static const int g=3;
    static const int bruteforce_limit=16;
    vector<int> roots{0,1};
    inline int mul(int x,int y) {
        ll ret=(ll)x*y; (ret>MOD) &&(ret%=MOD);
        return ret;
    }
    int poww(int a,int b) {
        int ret=1;
        for (; b; b>>=1,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void dft(vector<int> &A,int len,int inv) {
        assert((int)A.size()==len);
        if (inv==-1) reverse(A.begin()+1, A.end());
        int i,j,k;
        // bitrev[i] = bitrev[i >> 1] >> 1 | (i & 1) << __builtin_ctz(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        }
        if ((int)roots.size()<len) {
            int k=__builtin_ctz(roots.size());
            roots.resize(len);
            while ((1<<k)<len) {
                int e=poww(g,(MOD-1)>>(k+1));
                for (int i=1<<(k-1); i<(1<<k); ++i) {
                    roots[2*i]=roots[i];
                    roots[2*i+1]=mul(roots[i],e);
                } ++k;
            }
        }
        for (i=1; i<len; i<<=1) { //fin version
            for (j=0; j<len; j+=i+i) { //merge length = i+i
                for (k=0; k<i; k++) {
                    int a=A[k+j];
                    // assert(k+i+j<(int)A.size());
                    // assert(k+i<(int)roots.size());
                    int b=mul(A[k+i+j],roots[k+i]);
                    int u=a+b; (u>=MOD) &&(u-=MOD); A[k+j]=u;
                    int v=a-b; (v<0) &&(v+=MOD); A[k+i+j]=v;
                }
            }
        }
        if (inv==-1) {
            int vn=poww(len,MOD-2);
            REP_(i,len) A[i]=mul(A[i],vn);
        }
    }
    vector<int> mul(const vector<int> &A,const vector<int> &B) { //C=A*B
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,MOD);
        int len=1;
        while (len<n+m-1) len<<=1;
        vector<int> _A(A),_B;
        _A.resize(len,0); dft(_A,len,1);
        if (A==B) _B=_A; else _B=B,_B.resize(len,0),dft(_B,len,1);
        REP_(i,len) _A[i]=mul(_A[i],_B[i]);
        dft(_A,len,-1); _A.resize(n+m-1);
        return _A;
    }
}

namespace FFT { // 任意模数fft
    static const int bruteforce_limit=16;
    struct complex {
        double a,b;
        complex(double _a=.0,double _b=.0):a(_a),b(_b) {}
        complex operator+(const complex x)const {return complex(a+x.a,b+x.b);}
        complex operator-(const complex x)const {return complex(a-x.a,b-x.b);}
        complex operator*(const complex x)const {return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
    };
    vector<complex> wn;
    void initwn(int l) {
        if ((int)wn.size()==l) return;
        wn.resize(l);
        REP_(i,l) wn[i]=complex(cos(2*pi*i/l),sin(2*pi*i/l));
    }
    void fft(vector<complex> &A,int len,int inv) {
        assert((int)A.size()==len);
        int i,j,k; initwn(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        } for (i=2; i<=len; i<<=1) {
            for (j=0; j<len; j+=i) {
                for (k=j; k<(j+i/2); k++) {
                    complex a,b; a=A[k];
                    b=A[k+i/2]*wn[(ll)(k-j)*len/i];
                    A[k]=a+b; A[k+i/2]=a-b;
                }
            }
        } if (inv==-1) REP_(i,len) A[i]=complex(A[i].a/len,A[i].b/len);
    }
    inline complex conj(complex &A) {return complex(A.a,-A.b);}
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod) { //C=A*B
        static vector<complex> x1,x2,x3,x4;
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,mod);
        int len=1;
        while (len<n+m-1) len<<=1;
        vector<int> C(len);
        x1.resize(len); x2.resize(len);
        x3.resize(len); x4.resize(len);
        static const int S=1<<15;
        REP_(i,n) x1[i]=complex(A[i]/S,A[i]%S);
        rep_(i,n,len) x1[i]=complex(); fft(x1,len,1);
        if (A==B) x2=x1;
        else {
            REP_(i,m) x2[i]=complex(B[i]/S,B[i]%S); rep_(i,m,len) x2[i]=complex();
            fft(x2,len,1);
        }
        REP_(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
            int j=(len-i)&(len-1);
            complex k1=(conj(x1[i])+x1[j])*complex(0.5,0);//dft k1
            complex b1=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b1
            complex k2=(conj(x2[i])+x2[j])*complex(0.5,0);//dft k2
            complex b2=(conj(x2[i])-x2[j])*complex(0,0.5);//dft b2
            x3[i]=k1*k2+k1*b2*complex(0,1);
            x4[i]=b1*k2+b1*b2*complex(0,1);
        } fft(x3,len,-1); fft(x4,len,-1);
        REP_(i,len) {
            ll kk=x3[i].a+0.5,kb=x3[i].b+0.5;
            ll bk=x4[i].a+0.5,bb=x4[i].b+0.5;
            C[i]=((kk%mod*S%mod+kb+bk)%mod*S%mod+bb)%mod;
        }
        C.resize(n+m-1);
        return C;
    }
}

namespace polynomial {
    static const int MOD=998244353;
    // static const int MOD=1e9+7;
    static const int g=3;
    inline int norm(int n) { return 1 << std::__lg(n * 2 - 1); }
    struct poly {
        vector<int> v;
        friend poly operator * (const poly &a,const poly &b) {
            return poly(NTT::mul(a.v,b.v));
            // return poly(FFT::mul(a.v,b.v,MOD));
        }
        poly() {}
        poly(int val) {if (val) v= {val};}
        // init usage:
        // A.init(T+1,[&](int x){
        //     return inv[x]%M*inv[x]%M*inv[x]%M;
        // });
        void init(int size, std::function<int(int)> f = [](int) {return 0;}) {
            v.resize(size);
            for (int i=0; i<size; i++) v[i]=f(i);
        }
        poly(const vector<int> &vec): v(vec) {
            while (v.size()&&!v.back()) v.pop_back();
        }
        poly(const vector<int> &vec,int size): v(vec) {
            v.resize(size);
        }
        poly rev() const {
            return poly(std::vector<int>(v.rbegin(),v.rend()));
        }
        void append(const poly &r) {
            v.insert(v.end(),r.v.begin(),r.v.end());
        }
        int size() const {
            return v.size();
        }
        poly resize(int size) {
            v.resize(size);
            return (*this);
        }
        poly alignxk(int k) const {
            return poly(v, k);
        }
        const int operator [](int n) const {
            if (n<0||n>=size()) return 0;
            return v[n];
        }
        friend poly operator + (const poly &a,const poly &b) {
            vector<int> ret(max(a.size(),b.size()));
            REP_(i,(int)ret.size())((ret[i]=a[i]+b[i])>=MOD)&&(ret[i]-=MOD);
            return poly(ret);
        }
        friend poly operator - (const poly &a,const poly &b) {
            vector<int> ret(max(a.size(),b.size()));
            REP_(i,(int)ret.size())((ret[i]=a[i]-b[i])<0)&&(ret[i]+=MOD);
            return poly(ret);
        }
        friend poly operator/(const poly &a, const poly &b) {
            return a.divide(b).first;
        }
        friend poly operator%(const poly &a, const poly &b) {
            return a.divide(b).second;
        }
        friend poly operator^(const poly &a, const poly &b) {
            return poly(a.v)^=b;
        }
        poly &operator += (poly b) {return (*this) = (*this) + b;}
        poly &operator -= (poly b) {return (*this) = (*this) - b;}
        poly &operator *= (poly b) {return (*this) = (*this) * b;}
        poly &operator ^= (const poly &r) {
            if (r.size() < size()) resize(r.size());
            for (int i = 0; i < size(); i++) v[i] = 1LL * v[i] * r[i] % MOD;
            return (*this);
        }
        poly modxk(int k) const { // %(x^k)
            k=min(k,size());
            return poly(vector<int>(v.begin(),v.begin()+k));//多一次copy; 可能无所谓
        }
        poly divxk(int k) const { // /(x^k)
            if (size()<=k) return poly();
            return poly(vector<int>(v.begin()+k,v.end()));//多一次copy; 可能无所谓
        }
        poly mulxk(int k) const { // *(x^k)
            if (!size()) return poly();
            vector<int> ret(v);
            ret.insert(ret.begin(),k,0);
            return poly(ret);
        }
        poly subpoly(int l,int r) const {
            return divxk(l).modxk(r-l+1);
        }
        poly mulT(poly b) const {  // self * reverse(b)
            if (b.size() == 0) return poly();
            int n = b.size();
            std::reverse(b.v.begin(), b.v.end());
            return ((*this) * b).divxk(n - 1);
        }
        poly deriv() const { // 求导
            if (v.empty()) return poly();
            std::vector<int> res(size() - 1);
            for (int i = 0; i < size() - 1; ++i)
                res[i] = 1ll * (i + 1) * v[i + 1] % MOD;
            return poly(res);
        }
        poly integr() const { // 积分
            if (v.empty()) return poly();
            std::vector<int> res(size() + 1);
            for (int i = 0; i < size(); ++i)
                res[i + 1] = (ll) v[i] * powMM(i+1,MOD-2,MOD) % MOD;
            return poly(res);
        }
        poly inv(int m) const { // 求逆 O(nlogn)
            poly x(powMM(v[0],MOD-2,MOD));
            int k = 1;
            while (k < m) {
                k *= 2;
                x = (x*(2-modxk(k)*x)).modxk(k);
            }
            return x.modxk(m);
        }
        poly log(int m) const { // 多项式对数函数 O(nlogn)
            // 当且仅当 [x^0]f(x) = 1 时， f(x)有对数多项式
            return (deriv()*inv(m)).integr().modxk(m);
        }
        poly exp(int m) const { // 多项式指数函数 O(nlogn)
            // 当且仅当 [x^0]f(x) = 0 时， f(x)有指数多项式
            // 否则 e 的泰勒展开不收敛
            poly x(1);
            int k = 1;
            while (k < m) {
                k *= 2;
                x = (x*(1-x.log(k)+modxk(k))).modxk(k);
            }
            return x.modxk(m);
        }
        poly sqrt(int m) const { // 多项式开根， 需满足[x^0] = 1
            poly x(1);
            int k=1;
            while (k<m) {
                k*=2;
                x=(x+modxk(k)*x.inv(k)).modxk(k)*((MOD+1)/2);
            }
            return x.modxk(m);
        }
        poly pow(int m,int _m=-1) { //高端的power写法; 注意乘法对MOD取模 exp对phi(MOD)取模; 取模是(x-m)%m+m;
            int n=size(),p=-1;
            if (_m==-1) _m=m;
            poly b; b.resize(n);
            for (int i=0;i<n;++i) if (v[i]) {p=i; break;}
            if (p==-1) return poly(!m);
            if (m==0) return poly(!!v[0]);
            if ((ll)m*p>=n) return b;
            int mu=powMM(v[p],_m,MOD),di=powMM(v[p],MOD-2,MOD);
            poly c=divxk(p).modxk(n-m*p)*di;
            c=c.log(n-m*p)*m;
            c=c.exp(n-m*p);
            b=c.mulxk(m*p)*mu;
            return b;
        }

        poly sin() const {
            int i = powMM(g, (MOD - 1) / 4,MOD);
            poly p = i * (*this);
            p = p.exp(p.size());
            poly q = (MOD - i) * (*this);
            q = q.exp(q.size());
            poly r = (p - q) * powMM(2 * i % MOD, MOD - 2,MOD);
            return r;
        }
        poly cos() const {
            int i = powMM(g, (MOD - 1) / 4,MOD);
            poly p = i * (*this);
            p = p.exp(p.size());
            poly q = (MOD - i) * (*this);
            q = q.exp(q.size());
            poly r = (p + q) * powMM(2, MOD - 2,MOD);
            return r;
        }
        poly tan() const { return sin() / cos(); }
        poly cot() const { return cos() / sin(); }
        poly arcsin() { // 要保证常数项是0
            poly sq = (*this) * (*this).modxk(size());
            for (int i = 0; i < size(); ++i)
                sq.v[i] = sq.v[i] ? MOD - sq.v[i] : 0;
            sq.v[0] = 1 + sq.v[0];
            if (sq.v[0] >= MOD) sq.v[0] -= MOD;
            poly r = (deriv() * sq.sqrt(size()).inv(size())).integr();
            return r;
        }
        poly arccos() { // 要保证常数项是0
            poly r = arcsin();
            for (int i = 0; i < size(); ++i)
                r.v[i] = r.v[i] ? MOD - r.v[i] : 0;
            return r;
        }
        poly arctan() { // 要保证常数项是0
            poly sq = (*this) * (*this).modxk(size());
            sq.v[0] = 1 + sq.v[0];
            if (sq.v[0] >= MOD) sq.v[0] -= MOD;
            poly r = (deriv() * sq.inv(size())).integr();
            return r;
        }
        poly arccot() { // 要保证常数项是0
            poly r = arctan();
            for (int i = 0; i < size(); ++i)
                r.v[i] = r.v[i] ? MOD - r.v[i] : 0;
            return r;
        }
        std::pair<poly, poly> divide(const poly &g) const {
            int n = v.size(), m = g.size();
            if (n < m) return make_pair(poly(), v);
            poly fR = rev();
            poly gR = g.rev().alignxk(n - m + 1);
            poly gRI = gR.inv(gR.size());
            poly qR = (fR * gRI).modxk(n - m + 1);
            poly q = qR.rev();
            poly r = ((*this) - g * q).modxk(m - 1);
            return std::make_pair(q, r);
        }

        void print(const char* s="\n") const {
            for (int val:v) printf("%d ",val); printf("%s",s);
        }
        void read(int n) {
            v.resize(n);
            REP_(i,n) scanf("%d",&v[i]),v[i]=(v[i]%MOD+MOD)%MOD;
        }
    };
    static const int bruteforce_limit=32;
    // f[i]+=f[i-j]*g[j]
    vector<int> half_self_fft(const vector<int> &f, const vector<int> &g,int n) {
        poly _g(g),ret;
        ret.resize(n);
        function<void(int, int, int)> work = [&](int p,int l,int r) {
            if (r-l<bruteforce_limit) {
            // if (r-l<2) {
                rep_(i,l,r) {
                    if (i<(int)f.size()) add_(ret.v[i],f[i],MOD);
                    rep_(j,1,r-i) add_(ret.v[i+j],(ll)ret[i]*g[j]%MOD,MOD);
                }
                return;
            }
            int m=(l+r)>>1;
            work(p*2,l,m);
            poly mul=ret.subpoly(l,m-1)*_g.subpoly(1,r-l-1);
            rep_(i,m,r) add_(ret.v[i],mul[i-l-1],MOD);
            work(p*2+1,m,r);
        };
        work(1,0,n);
        return ret.v;
    }
}
using namespace polynomial;

int solve() {
    int k,n,q;
    cin>>k;
    vector<int> c(k+1);
    FOR_(i,0,k) cin>>c[i];
    cin>>n;
    vector<int> g(n+1);
    FOR_(i,0,n) cin>>g[i];

    vector<int> ksum(n+1);
    {
        function<array<poly,2>(int,int)> solve=[&](int l,int r) {
            if (l==r) {
                if (c[l]==0) return array<poly,2>{poly(0),poly(1)};
                poly y; y.resize(2);
                y.v[0]=1; y.v[1]=(MOD-l)%MOD; // c[l]/(1-lx)
                return array<poly,2>{poly(c[l]),y};
            }
            int mid=(l+r)/2;
            auto left=solve(l,mid);
            auto right=solve(mid+1,r);
            poly x=left[0]*right[1]+left[1]*right[0],y=left[1]*right[1];
            // printf("solve l->r=%d %d\n",l,r);
            // left[0].print(); left[1].print();
            // right[0].print(); right[1].print(); 
            // x.print(); y.print();
            return array<poly,2>{x,y};
        };
        auto item=solve(0,k);
        poly cur=(item[0]*item[1].inv(n+1)).modxk(n+1);
        FOR_(i,0,n) ksum[i]=cur[i];
    }
    // for (int v:ksum) cout<<v<<" "; puts("<- ksum");
    // vector<mint> ksum(n+1);
    // FOR_(t,0,n) FOR_(x,0,k) ksum[t]+=mint(x).pow(t)*c[x];  // 多项式多点求值.

    // vector<mint> f(n+1);
    // rFOR_(i,0,n) {
    //     rFOR_(j,i,n) {
    //         mint base=Comb(j,i)*ksum[j-i];  // 分治fft
    //         if (j>i) g[i]-=f[j]*base;
    //         else f[i]=g[i]/base;
    //     }
    // }
    // g[i]=f[j]*C(j,i)*ksum[j-i]
    // g[i]*fac[i]=f[j]*fac[j]*ksum[j-i]*inv[j-i]
    vector<int> f(n+1);
    {
        mint kinv0=mint(1)/ksum[0];
        FOR_(i,0,n) ksum[i]=(Comb.g[i]*ksum[i]*kinv0).x;
        FOR_(i,0,n) g[i]=(Comb.f[i]*g[i]*kinv0).x;
        ksum[0]=0;
        FOR_(i,1,n) ksum[i]=(MOD-ksum[i])%MOD;

        reverse(g.begin(),g.end());
        // vector<int> res=g;
        // FOR_(i,0,n) {
        //     FOR_(j,0,i) res[i]=(mint(res[i])+mint(res[i-j])*ksum[j]).x;
        // }
        vector<int> res=half_self_fft(g,ksum,n+1);
        FOR_(i,0,n) f[i]=(Comb.g[i]*res[n-i]).x;
    }

    FOR_(i,0,n) cout<<f[i]<<" ";
    cout<<"\n";
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/