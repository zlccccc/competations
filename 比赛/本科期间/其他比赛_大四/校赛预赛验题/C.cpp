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
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e7+107;
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

bitset<1<<24> BIT;
//15^6
int ax[]={0,0,1,-1};
int ay[]={1,-1,0,0};
char str[20][20];
int Q[maxn],cnt[maxn],st,ed;
vector<pii> v,at;
inline int getsta(const pii &p,const pii &v0,const pii &v1) {
    int sta=0;
    sta|=p.first;
    sta|=p.second<<4;
    sta|=v0.first<<8;
    sta|=v0.second<<12;
    sta|=v1.first<<16;
    sta|=v1.second<<20;
    return sta;
}
inline void printsta(int now,int cnt) {
    pii b=make_pair(now&15,(now>>4)&15);
    vector<pii> c;
    c.push_back(make_pair((now>>8)&15,(now>>12)&15));
    c.push_back(make_pair((now>>16)&15,(now>>20)&15));
    printf("%d %d (%d %d), (%d %d)  %d\n",b.first,b.second,c[0].first,c[0].second,c[1].first,c[1].second,cnt);
}
int main() {
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        scanf("%s",str[i]+1);
    } pii p;
    FOR(i,1,n) FOR(j,1,m) {
        if (str[i][j]=='s') {
            p=make_pair(i,j);
        } else if (str[i][j]=='#') {
            v.push_back(make_pair(i,j));
        } else if (str[i][j]=='@') {
            at.push_back(make_pair(i,j));
        }
    } sort(v.begin(),v.end());
    sort(at.begin(),at.end());
    int sta=getsta(p,v[0],v[1]);
    st=0; ed=-1;
    Q[++ed]=sta;
    while (st<=ed) {
        int now=Q[st++];
        // printsta(now,cnt[st]);
        vector<pii> c;
        pii b=make_pair(now&15,(now>>4)&15);
        pii c0=make_pair((now>>8)&15,(now>>12)&15);
        pii c1=make_pair((now>>16)&15,(now>>20)&15);
        REP(i,4) {
            pii nb=make_pair(b.first+ax[i],b.second+ay[i]);
            if (str[nb.first][nb.second]=='*') continue;
            if (str[nb.first][nb.second]==0) continue;
            int nxtsta; pii nxtc0=c0,nxtc1=c1;
            if (nb!=c0&&nb!=c1) {
                nxtsta=getsta(nb,nxtc0,nxtc1);
            } else {
                pii nnb=make_pair(nb.first+ax[i],nb.second+ay[i]);
                if (str[nnb.first][nnb.second]=='*') continue;
                if (str[nnb.first][nnb.second]==0) continue;
                if (nnb==c0||nnb==c1) continue;
                if (nb==c0) nxtc0=nnb;
                else nxtc1=nnb;
                if (nxtc0>nxtc1) swap(nxtc0,nxtc1);
                nxtsta=getsta(nb,nxtc0,nxtc1);
            } if (BIT[nxtsta]) continue;
            BIT.set(nxtsta);
            Q[++ed]=nxtsta;
            cnt[ed]=cnt[st-1]+1;
            if (nxtc0==at[0]&&nxtc1==at[1]) {
                printf("%d\n",cnt[ed]);
                return 0;
            } 
        }
    } puts("-1");
    return 0;
}
/*
7 7
.....*.
.....*.
..**...
..**...
...s...
.....##
.....@@

7 7
.......
.......
.#.....
.......
...s.#.
.....**
.....*@

*/