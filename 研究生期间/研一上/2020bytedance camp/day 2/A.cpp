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
const LL M=998244353;
const LL maxn=1e5+107;
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

set<pii> S;//free positions
int T[maxn*4],A[maxn*4];
map<string,pii> MP;//first position
void update(int x,int pos,int val,int l=1,int r=100001) {//length
    if (l==r) {
        // printf("change %d(%d) to %d\n",pos,x,val);
        A[l]=val;
        T[x]=val; return;
    } int mid=(l+r)/2;
    if (pos<=mid) update(x<<1,pos,val,l,mid);
    else update(x<<1|1,pos,val,mid+1,r);
    T[x]=max(T[x<<1],T[x<<1|1]);
    // printf("%d %d %d %d %d %d\n",x,l,r,pos,val,T[x]);
}
int query(int x,int val,int l=1,int r=100001) {
    if (l==r) return l;
    int mid=(l+r)/2;
    if (T[x<<1]>=val) return query(x<<1,val,l,mid);
    return query(x<<1|1,val,mid+1,r);
}
inline void change(int l,int r) {
    // assert(l<=r);
    update(1,l,r-l+1);
}
char str[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    S.insert(make_pair(1,100000));//free length
    change(1,100000);
    FOR(i,1,n) {
        scanf("%s",str);
        if (str[4]=='=') {//must alloc
            string now; int len;
            now=now+str[0]+str[1]+str[2]+str[3];
            sscanf(str+11,"%d",&len);
            int startpos=query(1,len);
            if (startpos<=100000) {
                pii p=*S.lower_bound(make_pair(startpos,0));
                // printf("%d %d\n",p.first,p.second);
                S.erase(p); change(p.first,p.first-1);//remove it
                assert(p.first+len-1<=p.second);
                MP[now]=make_pair(p.first,p.first+len-1);//split it
                p.first+=len;
                if (p.first<=p.second) {
                    S.insert(p);
                    change(p.first,p.second);//final
                }
            } else MP[now]=make_pair(0,0);
            // cout<<now<<len<<"  pos= "<<startpos<<"\n";
        } else if (str[4]=='(') {//free
            string now;
            now=now+str[5]+str[6]+str[7]+str[8];
            pii p=MP[now]; MP[now]=make_pair(0,0);
            if (p.second!=0) {//merge
                auto pt=S.upper_bound(p);
                if (pt!=S.end()) {
                    pii nxt=*pt;
                    if (nxt.first==p.second+1) {
                        S.erase(nxt); change(nxt.first,nxt.first-1);
                        p.second=nxt.second;
                    }
                } pt=S.upper_bound(p);
                if (pt!=S.begin()) {
                    pt--; pii pre=*pt;
                    // printf("%d %d\n",pre.first,pre.second);
                    if (pre.second==p.first-1) {
                        S.erase(pre); p.first=pre.first;
                    }
                } change(p.first,p.second);
                S.insert(p);
            }
            // cout<<"free"<<now<<"\n";
        } else if (str[4]=='u') {
            string now;
            now=now+str[7]+str[8]+str[9]+str[10];
            if (MP.count(now)) printf("%d\n",MP[now].first);
            else puts("0");
            // cout<<"output"<<now;
        }
        // int t;
        // for (auto now:S) printf("(%d,%d)",now.first,now.second); puts("<-S");
        // FOR(t,1,100000) if (A[t]) printf("(%d,%d)",t,t+A[t]-1); puts("<-A");
    }
}
/*
100
data=alloc(239);
more=alloc(17);
xxxx=alloc(17);
yyyy=alloc(17);
output(more);
free(xxxx)
xxxx=alloc(17);
free(more)


100
data=alloc(99999);
more=alloc(1);
xxxx=alloc(1);
yyyy=alloc(1);
output(more);
free(data)
free(xxxx)
xxxx=alloc(1);
free(more)
more=alloc(1);
xxxx=alloc(1);
yyyy=alloc(1);
free(xxxx)
zzzz=alloc(2);


100
xxxx=alloc(1);
more=alloc(1);
xxxx=alloc(1);
yyyy=alloc(1);
free(xxxx)
zzzz=alloc(2);
free(zzzz)
free(xxxx)
free(yyyy)
free(more)

5
long=alloc(50002);
file=alloc(50000);
output(long);
free(long);
output(file);

10
xxxx=alloc(100000);
yyyy=alloc(1);
free(xxxx)
xxxx=alloc(2)
output(xxxx)
output(yyyy)
free(yyyy)
yyyy=alloc(10)
*/