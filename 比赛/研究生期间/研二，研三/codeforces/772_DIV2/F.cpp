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


vector<ll> H;
inline int getid(ll h) {return lower_bound(H.begin(),H.end(),h)-H.begin();}
ll A[maxn];
int w[maxn];
ll Lmax[maxn],Rmax[maxn];
pll wl[maxn],wr[maxn];//pair(h,sum), downstream
int main() {
    int n,i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%lld",&A[i]),H.push_back(A[i]);
    sort(H.begin(),H.end());
    H.erase(unique(H.begin(),H.end()),H.end());
    FOR(i,1,n) A[i]=getid(A[i]);
    ll ans=0;
    FOR(i,1,n) {
        int h=INF;
        FOR(j,i,n) {
            h=min(h,(int)A[j]);
            w[h]=max(w[h],j-i+1);
            ll now=H[h]*(j-i+1);
            max_(ans,now);
            max_(Rmax[i],now); max_(Lmax[j],now);
        }
    }
    REP(i,(int)H.size()) rep(j,i,(int)H.size()) {//w-up > w-down
        ll now=(H[j]-H[i])*w[j]+H[i]*w[i];
        // printf("%lld,%d -> %lld,%d: %lld\n",H[i],w[i],H[j],w[j],now);
        ans=max(ans,now);
    }
    // printf("ans=%lld\n",ans);
    //left-wl; right-wr
    FOR(i,1,n) max_(Lmax[i],Lmax[i-1]);
    rFOR(i,1,n) max_(Rmax[i],Rmax[i+1]);
    FOR(i,1,n-1) max_(ans,Lmax[i]+Rmax[i+1]);
    // FOR(i,1,n) printf("%5lld",Lmax[i]); puts("<- L");
    // FOR(i,1,n) printf("%5lld",Rmax[i]); puts("<- R");
    FOR(i,1,n) {
        int h,top;
        h=A[i]; top=0; int ri=i,li=i;
        while (A[ri]>=A[i]&&ri<=n) ri++; ri--;//must!
        while (A[li]>=A[i]&&li>=1) li--; li++;//must!
        rFOR(j,1,li) {//stack(w,v)
            h=min(h,(int)A[j]);
            pll nowans=make_pair(H[h],(ri-j+1)*H[h]);
            // if (i==33) {printf("(%lld,%lld)",nowans.first,nowans.second);}
            while (top&&nowans.second>=wl[top].second) top--;
            wl[++top]=nowans;
        }
        int R=top;
        h=A[i]; top=0;
        FOR(j,ri,n) {//stack(w,v)
            h=min(h,(int)A[j]);
            pll nowans=make_pair(H[h],(j-li+1)*H[h]);
            while (top&&nowans.second>=wr[top].second) top--;
            wr[++top]=nowans;
        } wr[top+1]=make_pair(-INFF,0);
        int k=1; // ri is necessary
        // if (i==33) {
        //     printf("l,r=%d,%d; h=%lld\n",li,ri,H[A[i]]);
        //     FOR(j,1,R) printf("(%lld,%lld)",wl[j].first,wl[j].second); puts("<- wl");
        //     FOR(j,1,top) printf("(%lld,%lld)",wr[j].first,wr[j].second); puts("<- wr");
        // }
        rFOR(j,1,R) {
            while (wr[k].first+wl[j].first>H[A[i]]) k++;
            // if (i==33) printf("i=%d; left=%lld; right=%lld; leftsum=%lld, rightsum=%lld; h=%d\n",i,wl[j].first,wr[k].first,wl[j].second,wr[k].second,H[A[i]]);
            max_(ans,wl[j].second+wr[k].second);
            // if (k>=top) max_(ans,wl[j].second+(H[A[i]]-wl[j].first)*(ri-li+1));
        }
        int Tmp=ri;
        rFOR(j,1,R) {//h->up
            while (H[A[Tmp]]+wl[j].first>H[A[i]]&&Tmp<=n) Tmp++;
            max_(ans,wl[j].second+(Tmp-li)*(H[A[i]]-wl[j].first));
        } Tmp=li;
        rFOR(j,1,top) {//h->up
            while (H[A[Tmp]]+wr[j].first>H[A[i]]&&Tmp>=1) Tmp--;
            max_(ans,wr[j].second+(ri-Tmp)*(H[A[i]]-wr[j].first));
        }
    }
    printf("%lld\n",ans);
}
/*
8
1 2 2 5 5 3 3 1

8
1 2 2 3 3 2 2 1

97
97 142 53 32 47 90 125 28 93 56 76 69 19 22 61 101 144 147 82 141 89 26 80 121 58 133 120 81 64 85 135 111 25 30 100 83 70 123 166 147 36 128 78 143 141 53 158 116 128 137 86 98 96 17 30 9 25 45 8 40 148 83 28 74 55 87 69 81 80 50 142 103 32 47 33 126 47 43 13 57 124 100 74 100 119 91 25 43 39 39 39 39 39 39 39 39 39 39 39 39

166 21 108 41 29 162 6 25 62 94 3 156 50 95 163 50 87 35 63 66 125 98 84 32 58 78 64 10 94 120 118 71 136 16 93 37 106 15 46 40 166 52 94 7 88 91 66 24 45 65 66 145 116 99 117 33 144 45 8 95 38 95 3 85 45 12 69 115 7 97 142 53 32 47 90 125 28 93 56 76 69 19 22 61 101 144 147 82 141 89 26 80 121 58 133 120 81 64 85 135 111 25 30 100 83 70 123 166 147 36 128 78 143 141 53 158 116 128 137 86 98 96 17 30 9 25 45 8 40 148 83 28 74 55 87 69 81 80 50 142 103 32 47 33 126 47 43 13 57 124 100 74 100 119 91 25 43 39 39 39 39 39 39 39 39 39 39 39 39
166
21 108 41 29 162 6 25 62 94 3 156 50 95 163 50 87 35 63 66 125 98 84 32 58 78 64 10 94 120 118 71 136 16 93 37 106 15 46 40 166 52 94 7 88 91 66 24 45 65 66 145 116 99 117 33 144 45 8 95 38 95 3 85 45 12 69 115 7 97 142 53 32 47 90 125 28 93 56 76 69 19 22 61 101 144 147 82 141 89 26 80 121 58 133 120 81 64 85 135 111 25 30 100 83 70 123 166 147 36 128 78 143 141 53 158 116 128 137 86 98 96 17 30 9 25 45 8 40 148 83 28 74 55 87 69 81 80 50 142 103 32 47 33 126 47 43 13 57 124 100 74 100 119 91 25 43 39 39 39 39 39 39 39 39 39 39 39 39
*/