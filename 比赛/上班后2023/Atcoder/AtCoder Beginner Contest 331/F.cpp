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

const int mod1=1e9+7;
const int mod2=998244353;
// int mod=1;
ll pw1[maxn],pw2[maxn];
ar4 merge(ar4 x,ar4 y,int llen,int rlen) {
    ar4 ret;
    ret[0]=(x[0]*pw1[rlen]+y[0])%mod1;
    ret[1]=(x[1]+y[1]*pw1[llen])%mod1;
    ret[2]=(x[2]*pw2[rlen]+y[2])%mod2;
    ret[3]=(x[3]+y[3]*pw2[llen])%mod2;
    return ret;
}
ar4 T[maxn<<2];
void update(int x,int pos,char c,int L,int R) {
    if (L==R) {
        c-='a';
        T[x]={c,c,c,c}; return;
    }
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,c,L,mid);
    if (mid<pos) update(x<<1|1,pos,c,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1],mid-L+1,R-mid);
}
ar4 query(int x,int l,int r,int L,int R) {
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (l<=mid&&mid<r) {
        ar4 lval=query(x<<1,l,mid,L,mid);
        ar4 rval=query(x<<1|1,mid+1,r,mid+1,R);
        // cout<<mid-l+1<<"; "<<r-mid<<endl;
        return merge(lval,rval,mid-l+1,r-mid);
    }
    if (l<=mid) return query(x<<1,l,r,L,mid);
    if (mid<r) return query(x<<1|1,l,r,mid+1,R);
    assert(0);
}
int solve() {
    int n,q;
    string s;
    cin>>n>>q>>s;
    pw1[0]=pw2[0]=1;
    FOR_(i,1,n) pw1[i]=pw1[i-1]*29%mod1;
    // FOR_(i,1,n) pw1[i]=pw1[i-1]*10%mod1;
    FOR_(i,1,n) pw2[i]=pw2[i-1]*31%mod2;
    FOR_(i,1,n) update(1,i,s[i-1],1,n);
    FOR_(i,1,q) {
        int op;
        cin>>op;
        if (op==1) {
            int x; char c;
            cin>>x>>c;
            update(1,x,c,1,n);
        } else {
            int l,r;
            cin>>l>>r;
            ar4 res=query(1,l,r,1,n);
            // cout<<res[0]<<" "<<res[1]<<" "<<res[2]<<" "<<res[3]<<"  <<- result\n";
            if (res[0]==res[1]&&res[2]==res[3]) puts("Yes");
            else puts("No");
        }
    }
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
*/