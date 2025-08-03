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

struct frac{
    ll x,y;
    frac(ll _x,ll _y) {
        if (_y<0) _x=-_x,_y=-_y;
        else if (_y==0) _x=abs(_x);
        x=_x; y=_y;
        // norm();
    }
    void norm() {
        ll d=__gcd(abs(x),abs(y));
        x/=d; y/=d;
    }
    bool operator<(const frac &k) const {
        return x*k.y<k.x*y;
    }
    bool operator<=(const frac &k) const {
        return x*k.y<=k.x*y;
    }
    bool operator!=(const frac &k) const {
        return x*k.y!=k.x*y;
    }
    double value(){
        return 1.0*x/y;
    }
};
struct point_rotate{//n^2
    struct point{
        int x,y; int id;
    }T[maxn];
    int start;
    vector<pair<frac,pii> > changes;
    int pos_id[maxn],n;
    void init_direct(int _n) {
        n=_n;
        start=0; changes.clear();
        FOR_(i,1,n) T[i].id=i;
        sort(T+1,T+1+n,[](point &a,point &b){//k=-inf=1/-eps
            if (a.x!=b.x) return a.x>b.x;
            return a.y>b.y;
        });
        FOR_(i,1,n) pos_id[T[i].id]=i;
        FOR_(i,1,n) FOR_(j,i+1,n) if (T[i].x!=T[j].x) {//change position
            // printf("to be change: %f %d %d(pos=%d %d)\n",frac(T[i].y-T[j].y,T[i].x-T[j].x).value(),T[i].id,T[j].id,pos_id[T[i].id],pos_id[T[j].id]);
            changes.push_back(make_pair(frac(T[i].y-T[j].y,T[i].x-T[j].x),make_pair(i,j)));//rotate id
        }
        sort(changes.begin(),changes.end());//low to high
        for (auto &now:changes) {
            pii id=now.second;
            now.second=make_pair(T[id.first].id,T[id.second].id);
        }
    }
    void init_rotate(int n) { //k' should be 1/k (y=kx)
        FOR_(i,1,n) swap(T[i].x,T[i].y);//swap
        init_direct(n);
    }
    void change(frac k) {//y=kx;作为法向量的直线
        for (;start<(int)changes.size()&&changes[start].first<=k;start++) {
            pii pos=changes[start].second;
            int x=pos.first,y=pos.second;
            // assert(pos_id[y]-pos_id[x]==1);
            swap(T[pos_id[y]],T[pos_id[x]]);
            swap(pos_id[y],pos_id[x]);
            // printf("swap: %d %d\n",x,y);
            // print(k);
        } 
    }
    void print(frac k) {
        //direct; /sqrt(x^2+y^2)=>length
        FOR_(i,1,n) printf("%lld(id=%d) ",T[i].x*k.x-T[i].y*k.y,T[i].id);
        printf(" <- position_direct; x*y=%lld;, k=%f\n",k.x*k.y,k.value());//(/=xy)
    }
}P;
int solve() {
    int n;
    scanf("%d",&n);
    FOR_(i,1,n) scanf("%d%d",&P.T[i].x,&P.T[i].y);
    P.init_direct(n);
    int Q;
    ll G,Ra,Rb;
    scanf("%d%lld%lld%lld",&Q,&G,&Ra,&Rb);
    auto NxtG=[](ll G) { return (48271*G)%((1ll<<31)-1); };
    vector<pair<frac,ll>> Que;
    FOR_(i,1,Q) {
        ll G0=G,G1=NxtG(G0),G2=NxtG(G1); G=NxtG(G2);
        ll A=-Ra+(G1%(2*Ra+1));
        ll B=-Rb+(G2*((1ll<<31)-1)+G)%(2*Rb+1);
        // printf("ask: %lld %lld\n",A,B);
        Que.push_back({frac(A,1),B});
    }
    sort(Que.begin(),Que.end());

    ll res=0;
    for (auto [dir,B]:Que) {
        P.change(dir);
        // printf("solve %lld %lld\n",dir.x,B);
        // P.print(dir);
        int l=0,r=n+1; // l: not-okay; r: okay
        while (l+1<r) {
            int mid=(l+r)/2;
            if (P.T[mid].x*dir.x-P.T[mid].y*dir.y<=-B) l=mid;
            else r=mid;
        }
        res+=l;
        // printf("res+=%d\n",n+1-r);
    }
    printf("%lld\n",res);
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