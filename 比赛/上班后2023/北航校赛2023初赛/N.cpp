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
int V[maxn];
int n;
int A[maxn];
int Cnt=0;
bool test=false;
int ask() {
    Cnt++; if (Cnt>n*10) assert(0);
    cout.flush();
    int res=0;
    FOR_(i,1,n) res+=(A[i]==V[i]);
    if (!test) {
        FOR_(i,1,n) cout<<A[i]<<" ";
        cout<<"\n"; cout.flush();
        cin>>res;
    }
    // if (test) {FOR_(i,1,n) cout<<A[i]<<" "; puts("");}
    // if (test) cout<<"  F="<<res<<endl;
    // if (test&&res==n) FOR_(i,1,n) cout<<A[i]<<" ";
    if (test&&res==n) FOR_(i,1,n) cout<<A[i]-V[i]<<" ";

    // if (res==-1) assert(0);
    if (res==-1||res==n) exit(0);
    else return res;
}
int sufsum[maxn];
int res[maxn];
int solve() {
    FOR_(i,1,n) A[i]=1;
    int Count1=ask();
    FOR_(i,1,n) {
        A[i]=2;
        int c=ask();
        if (c-Count1==1) res[i]=2;
        else if (Count1-c==1) res[i]=1,sufsum[i]=1;
        else if (c!=Count1) assert(0);
        A[i]=1;
    }
    // FOR_(i,1,n) printf("%d ",res[i]); puts("<- after first operation");
    rFOR_(i,1,n) sufsum[i]+=sufsum[i+1];
    FOR_(x,3,n) {
        FOR_(i,1,n) A[i]=x;
        int T=ask();

        vector<int> Pos; Pos.push_back(0);
        FOR_(i,1,n) if (!res[i]) Pos.push_back(i);
        int _n=Pos.size()-1;
        Pos.push_back(n+1);

        int left=0;
        map<int,int> MP;
        FOR_(__,1,T) {
            rREP_(k,10) if (left+(1<<k)<=_n) {
                int cur=left+(1<<k);
                // printf("cur=%d; val=%d\n",cur,Pos[cur]);
                FOR_(i,1,Pos[cur]) A[i]=x;
                FOR_(i,Pos[cur]+1,n) A[i]=1;
                int c;
                if (MP.count(cur)) c=MP[cur];
                else MP[cur]=c=ask();
                // printf("%d ",c-sufsum[Pos[cur]+1]);
                if (c-sufsum[Pos[cur]+1]<__) left=cur;
            }
            // if (left==_n) {
            //     printf("left=%d; x=%d; fin size=%d\n",left,x,Pos.size());
            //     FOR_(i,1,n) cout<<res[i]<<" "; puts("  <<- current res");
            //     FOR_(i,1,n) if (res[i]-V[i]!=0) printf("%d(%d) ",res[i]-V[i],V[i]); puts("  <<- div res");
            //     FOR_(i,0,_n) printf("%d ",Pos[i]); puts("");
            // }
            assert(left!=_n);
            left++; res[Pos[left]]=x;
        }
        // FOR_(i,1,n) printf("%d ",res[i]); puts(" [[<- after second operation");
    }
    // FOR_(i,1,n) assert(res[i]!=0);
    FOR_(i,1,n) A[i]=res[i];
    ask();
    // assert(0);
    return 0;
}
void Test() {
    n=500; srand(time(0));
    // FOR_(i,1,n) V[i]=n-i+1; test=true;
    // FOR_(i,1,n) V[i]=n; test=true;
    FOR_(i,1,n) V[i]=rand()%n+1; test=true;
    // FOR_(i,1,n) cin>>V[i];
    FOR_(i,1,n) cout<<V[i]<<" "; puts("");
    solve();
}
int main() {
    // FOR_(i,1,10) Test();
    cin>>n; test=false;
    solve();
}
/*
*/