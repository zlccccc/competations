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

struct node{
    ll res,maxl,maxr,sum;
    node(ll cur=0) {res=maxl=maxr=sum=cur;}
}T[maxn*4];
node merge(node x,node y) {
    node res;
    res.res=max(max(x.res,y.res),x.maxr+y.maxl);
    res.maxl=max(x.maxl,x.sum+y.maxl);
    res.maxr=max(y.maxr,x.maxr+y.sum);
    res.sum=x.sum+y.sum;
    return res;
}
void update(int x,int pos,int val,int L,int R) {
    // printf("update %d %d %d %d %d\n",x,pos,val,L,R);
    if (L==R) {
        T[x]=node(T[x].sum+val);
        return;
    }
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,val,L,mid);
    if (mid<pos) update(x<<1|1,pos,val,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r,int L,int R) {
    // printf("query %d %d %d %d %d\n",x,l,r,L,R);
    if (l<=L&&R<=r) return T[x];
    int mid=(L+R)/2;
    if (l<=mid&&mid<r) return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
    if (l<=mid) return query(x<<1,l,r,L,mid);
    if (mid<r) return query(x<<1|1,l,r,mid+1,R);
    assert(0);
}
vector<pii> upd[maxn];
vector<ar3> que[maxn];
ll res[maxn];
int solve() {
    int n,m;
    cin>>n>>m;
    FOR_(i,1,m) {
        int l,r,x;
        cin>>l>>r>>x;
        upd[l].push_back({i,x});
        upd[r+1].push_back({i,-x});
    }
    int q=0;
    cin>>q;
    FOR_(i,1,q) {
        int k,l,r;
        cin>>k>>l>>r;
        que[k].push_back({l,r,i});
    }
    FOR_(i,1,n) {
        for (auto &cur:upd[i]) {
            update(1,cur.first,cur.second,1,m);
        }
        for (auto &cur:que[i]) {
            res[cur[2]]=query(1,cur[0],cur[1],1,m).res;
        }
    }
    FOR_(i,1,q) cout<<res[i]<<"\n";
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