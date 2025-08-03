#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
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
struct frac{
    ll x,y;
    frac(ll _x,ll _y) {
        if (_y<0) _x=-_x,_y=-_y;
        else if (_y==0) _x=abs(_x);
        x=_x; y=_y;
        // norm();
    }
    void norm() {
        ll d=gcd(abs(x),abs(y));
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
        int i,j; n=_n;
        start=0; changes.clear();
        FOR(i,1,n) T[i].id=i;
        sort(T+1,T+1+n,[](point &a,point &b){//k=-inf=1/-eps
            if (a.x!=b.x) return a.x>b.x;
            return a.y>b.y;
        });
        FOR(i,1,n) pos_id[T[i].id]=i;
        FOR(i,1,n) FOR(j,i+1,n) if (T[i].x!=T[j].x) {//change position
            // printf("to be change: %f %d %d(pos=%d %d)\n",frac(T[i].y-T[j].y,T[i].x-T[j].x).value(),T[i].id,T[j].id,pos_id[T[i].id],pos_id[T[j].id]);
            changes.push_back(make_pair(frac(T[i].y-T[j].y,T[i].x-T[j].x),make_pair(i,j)));//rotate id
        }
        sort(changes.begin(),changes.end());//low to high
        for (auto &now:changes) {
            pii id=now.second;
            now.second=make_pair(T[id.first].id,T[id.second].id);
        }
    }
    void init_rotate(int n) {
        int i; //k' should be 1/k (y=kx)
        FOR(i,1,n) swap(T[i].x,T[i].y);//swap
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
        int i; //direct; /sqrt(x^2+y^2)=>length
        FOR(i,1,n) printf("%lld(%d) ",T[i].x*k.x-T[i].y*k.y,T[i].id); printf(" <- position_direct; x*y=%lld;, k=%f\n",k.x*k.y,k.value());//(/=xy)
    }
}P;

vector<int> tow;
//sort by T[i].x*k.x-T[i].y*k.y
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        scanf("%d%d",&P.T[i].x,&P.T[i].y);
        P.T[i].y=-P.T[i].y;
    }
    P.init_direct(n);

    for (auto now:P.changes) {
        auto frac=now.first;
        ll pos=frac.x/frac.y;
        if (pos>0&&pos<=m) tow.push_back(pos);
    } tow.push_back(m);
    sort(tow.begin(), tow.end());
    ll ans=-INFF; ll left=1;//left to position
    for (ll pos:tow) {
        P.change(frac(pos,1));
        ll l=left,r=min((ll)m,pos); left=r+1;
        if (l<=r) {
            ans=max(ans,l*(P.T[1].x+P.T[2].x)-P.T[1].y-P.T[2].y);
            ans=max(ans,r*(P.T[1].x+P.T[2].x)-P.T[1].y-P.T[2].y);
        }
        // FOR(i,1,n) printf("%lld(%d) ",P.T[i].x*l-P.T[i].y,P.T[i].id); puts("<< l");
        // P.print(frac(pos,1));
    }
    printf("%lld\n",ans);
}
/*
10 30
3 1
2 1
1 3
4 6
7 5
4 6
8 4
8 1
8 3
7 2
*/