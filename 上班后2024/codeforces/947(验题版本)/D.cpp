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

int solve() {
    int n,q;
    scanf("%d%d",&n,&q);
    vector<int> col(n+1),A(n+1);  // c一开始是全空的
    FOR_(i,1,n) scanf("%d",&A[i]);
    vector<vector<int>> edge(n+1);
    edge[0].push_back(1);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    vector<int> fa(n+1);
    function<void(int,int)> dfs=[&](int x,int f) {
        fa[x]=f;
        for (int v:edge[x]) if (v!=f) dfs(v,x);
    };
    dfs(0,-1);
    ar3 all={0,0,0};
    vector<ar3> sub(n+1,{0,0,0});  // du-linked-subtree
    auto change=[&](int x) {
        // printf("change %d; fa=%d; col=%d\n",x,fa[x],col[x]);
        // REP_(i,3) printf("%d ",sub[x][i]); puts("<- sub");
        // REP_(i,3) printf("%d ",sub[fa[x]][i]); puts("<- sub-fa");
        // if (fa[x]) REP_(i,3) printf("%d ",sub[fa[fa[x]]][i]); puts("<- sub-fa-fa");
        auto changefa=[&](int x,int op) {
            if (fa[x]>0&&col[fa[x]]) {
                int df=min(2,sub[fa[x]][0]+sub[fa[x]][1]+sub[fa[x]][2]); // d-father
                if (fa[fa[x]]>0) { // fa[fa]度数不会有变化; 但是sub可能变化
                    sub[fa[fa[x]]][df]+=op;
                    df=min(2,df+col[fa[fa[x]]]);
                }
                // printf("df=%d\n",df);
                all[df]+=op;
            }
        };
        if (col[x]==0) {
            REP_(i,3) all[min(2,i)]-=sub[x][i];  // sub-value (b-b)
            REP_(i,3) all[min(2,i+1)]+=sub[x][i];  // sub-value (b-b)
            changefa(x,-1);
            // REP_(i,3) printf("%d ",sub[x][i]); puts("<- cur");
            // REP_(i,3) printf("%d ",all[i]); puts("<- all");
            int d=min(2,sub[x][0]+sub[x][1]+sub[x][2]);
            sub[fa[x]][d]+=1;
            all[min(2,d+col[fa[x]])]++;  // self
            changefa(x,1);
        } else {
            REP_(i,3) all[min(2,i+1)]-=sub[x][i];  // sub-value (b-b)
            REP_(i,3) all[min(2,i)]+=sub[x][i];  // sub-value (b-b)
            changefa(x,-1);
            int d=min(2,sub[x][0]+sub[x][1]+sub[x][2]);
            sub[fa[x]][d]-=1;
            all[min(2,d+col[fa[x]])]--;  // self
            changefa(x,1);
        }
        // REP_(i,3) printf("%d ",sub[x][i]); puts("<- fin sub");
        // REP_(i,3) printf("%d ",sub[fa[x]][i]); puts("<- fin sub-fa");
        // if (fa[x]) REP_(i,3) printf("%d ",sub[fa[fa[x]]][i]); puts("<- fin sub-fa-fa");
        col[x]^=1;
    };
    FOR_(i,1,n) if (A[i]) {
        change(i);
        // printf("change %d\n",i);
        // FOR_(i,1,n) printf("%d ",col[i]); puts("<- color");
        // REP_(i,3) printf("%d ",all[i]); puts("<- all");
    }
    ll cnt=0;
    FOR_(i,1,q) {
        int op,v,u,z;
        scanf("%d%d",&op,&v);
        if (op==1) {
            scanf("%d",&z);
            // u=v;
            u=(v+cnt*z)%n+1;
            // printf("change %d\n",u);
            change(u);
        } else {
            int c;
            scanf("%d%d",&c,&z);
            // u=v;
            u=(v+cnt*z)%n+1;
            fa.push_back(u);
            col.push_back(0);
            sub.push_back({0,0,0});
            n++;
            // printf("insert %d %d\n",u,c);
            if (c) change(n);
        }
        // // if (all[3]) puts("No");
        // FOR_(i,1,n) printf("%d ",fa[i]); puts("<- fa");
        // FOR_(i,1,n) printf("%d ",col[i]); puts("<- color");
        // REP_(i,3) printf("%d ",all[i]); puts("<- all");
        if (all[1]==2&&all[0]==0) puts("Yes"),cnt++;
        else if (all[1]==0&&all[0]==1) puts("Yes"),cnt++;
        else puts("No");
    }
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
1
3 100
1 0 0
1 2
1 3
2 3 1 0
1 3 0
2 1 1 0
2 5 1 0
2 6 1 0
1 2 0
1 3 0
1 1 0
1 5 0
1 6 0
1 7 0
*/