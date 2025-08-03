#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[maxn],L[maxn];
vector<pii> vec[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n,m;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%d",&A[i]);
        FOR(i,1,n) L[i]=n+1;
        FOR(i,1,m) {
            int l,r; scanf("%d%d",&l,&r);
            min_(L[r],l);
        }
        rFOR(i,1,n-1) min_(L[i],L[i+1]);
        map<int,vector<int> > MP;\
        int minr=0;
        FOR(i,1,n) vec[i].clear();
        FOR(i,1,n) {
            MP[A[i]].push_back(i);
            auto &V=MP[A[i]];
            int id=lower_bound(V.begin(),V.end(),L[i])-V.begin();
            // printf("i=%d: id=%d; L=%d\n",i,id,L[i]);
            if (id>=V.size()-1) continue;
            int l1=V[id],l2=V[id+1];
            int r1=V[V.size()-2],r2=i;
            // printf("vec: %d-%d; %d-%d\n",l1,l2,r1,r2);
            max_(minr,r1);
            vec[r1].push_back({l1,1});
            vec[r2].push_back({l1,-1});
            vec[r2].push_back({l2,1});
        }
        if (!minr) {puts("0"); continue;}
        multiset<int> S;
        int ans=n+1;
        FOR(i,1,n) {
            for (pii now:vec[i]) {
                if (now.second==1) S.insert(now.first);
                else S.erase(S.lower_bound(now.first));
            }
            if (i>=minr) {
                min_(ans,i-*S.begin()+1);
            }
        }
        printf("%d\n",ans);
    }
}
/*
*/