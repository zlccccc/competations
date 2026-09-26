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
struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);


int solve() {
    int n,k;
    scanf("%d%d",&n,&k);
    vector<int> A,B,C;
    vector<double> psumB(1),psumC(1);
    REP_(i,n) {
        int x; scanf("%d",&x);
        A.push_back(x);
    }
    sort(A.begin(),A.end());

    for (int x:A) {
        if (x%13==0||x%37==0||x%137==0) B.push_back(x),psumB.push_back(psumB.back()+x);
        else C.push_back(x),psumC.push_back(psumC.back()+x);
    }

    vector<set<pii>> need(A.size());
    need[0].insert({k,0});
    REP_(i,A.size()-1) {
        for (auto u:need[i]) {
            pii v=u;
            while (v.first) {
                if (v.first<(ll)A[i]*A[i]) break; // not need;
                need[i+1].insert(v);
                v.first/=A[i];
                if (!v.second&&(A[i]%13==0||A[i]%37==0||A[i]%137==0)) {
                    v.second=1; v.first/=2;
                }
            }
        }
    }
    map<pii,pair<double,double>> cur,nxt;
    rREP_(i,A.size()) {
        nxt.clear();
        for (auto u:need[i]) {
            pii v=u; double base=1;
            while (v.first) {
                // printf("v.first=%d\n",v.first);
                pair<double,double> prev={1.,1.};
                // if (false) {
                if (v.first<(ll)A[i]*A[i]) {  // 只能最多选1个了; 或者不能选
                    // C value in range {A[i]->v.first}
                    {
                        int R=v.first;
                        if (A[i]<=R) {
                            int r=upper_bound(C.begin(),C.end(),R)-C.begin();
                            int l=lower_bound(C.begin(),C.end(),A[i])-C.begin();
                            // printf("FF %d->%d\n",l,r);
                            prev.first+=psumC[r]-psumC[l]; prev.second+=r-l;
                        }
                    }
                    // B value in range {A[i]->v.first/2}
                    {
                        double Bbase=1;
                        int R=v.first;
                        if (!v.second) R/=2,Bbase=2;
                        if (A[i]<=R) {
                            int r=upper_bound(B.begin(),B.end(),R)-B.begin();
                            int l=lower_bound(B.begin(),B.end(),A[i])-B.begin();
                            // printf("SS %d->%d\n",l,r);
                            prev.first+=(psumB[r]-psumB[l])*Bbase; prev.second+=r-l;
                        }
                    }
                    // printf("u=%d %d; A=%d: first type; towards base=%lf; pre=%d %d; %lf %lf\n",u.first,u.second,A[i],base,v.first,v.second,prev.first,prev.second);
                    nxt[u].first+=prev.first*base,nxt[u].second+=prev.second;
                    break;
                } else {
                    if (i+1<A.size()) prev=cur[v];  // 否则后面只能选一个0
                    else prev={1.,1.};
                    // printf("second type; towards base=%lf; pre=%d %d; %lf %lf\n",base,v.first,v.second,prev.first,prev.second);
                    nxt[u].first+=prev.first*base,nxt[u].second+=prev.second;
                }
                v.first/=A[i]; base*=A[i];
                if (!v.second&&(A[i]%13==0||A[i]%37==0||A[i]%137==0)) {
                    v.second=1; v.first/=2; base*=2;
                }
                if (A[i]==1) break;
            }
        }
        nxt.swap(cur);
        // for (auto v:need[i]) printf("(%d,%d:%lf/%lf) ",v.first,v.second,cur[v].first,cur[v].second); puts("<- final value");
    }
    printf("%.8lf\n",(cur[{k,0}].first-1)/max(1.,cur[{k,0}].second-1));
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
1 100
1
*/