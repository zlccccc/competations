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
const LL maxn=2e5+107;
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

int Hid[maxn],h[maxn];
int MAX[maxn*4],MIN[maxn*4];//update
void update(int x,int pos,int L,int R) {
    if (L==R) {MAX[x]=MIN[x]=h[Hid[pos]]; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    if (mid<pos) update(x<<1|1,pos,mid+1,R);
    MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
    MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
int op,val;
int query(int x,int l,int r,int L,int R) {
    // if (op==3) printf("query %d %d %d %d %d: %d %d\n",x,l,r,L,R,MIN[x],MAX[x]);
    int mid=(L+R)/2;
    if (l<=L&&R<=r) {
        if (op==1) {
            // printf("fin query %d %d %d %d; %d\n",l,r,L,R,MAX[x]);
            if (MAX[x]<=val) return 0;
            if (L==R)  return L;
            int ret=0;
            if (mid<r&&MAX[x<<1|1]>val) ret=query(x<<1|1,l,r,mid+1,R);
            if (ret) return ret;
            if (l<=mid&&MAX[x<<1]>val) ret=query(x<<1,l,r,L,mid);
            return ret;
        } else if (op==2) {
            return MAX[x];//query max
        } else {
            if (L==R) return L;
            if (MIN[x<<1]<=MIN[x<<1|1]) return query(x<<1,l,r,L,mid);
            else return query(x<<1|1,l,r,mid+1,R);
        }
    }
    if (op==1) {//one; one log
        int ret=0;
        if (mid<r&&MAX[x<<1|1]>val) ret=query(x<<1|1,l,r,mid+1,R);
        if (ret) return ret;
        if (l<=mid&&MAX[x<<1]>val) ret=query(x<<1,l,r,L,mid);
        return ret;
    }
    if (op==2) {//r-maxvalue
        int ret=-INF;
        if (l<=mid) ret=max(ret,query(x<<1,l,r,L,mid));
        if (mid<r) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
        return ret;
    }
    if (op==3) {//left-maxposition
        int lv=0,rv=0;
        if (l<=mid) lv=query(x<<1,l,r,L,mid);
        if (mid<r) rv=query(x<<1|1,l,r,mid+1,R);
        if (!lv||!rv) return lv|rv;
        if (h[Hid[lv]]<=h[Hid[rv]]) return lv;
        return rv;
    } assert(0);
    return 0;
}
int A[maxn];
vector<int> v;
int getid(int x) {return lower_bound(v.begin(),v.end(),x)-v.begin()+1;};
int main() {
    int n,i;
    scanf("%d",&n);
    // FOR(i,1,n) A[i]=rand(),h[i]=-rand()%n+1;
    FOR(i,1,n) scanf("%d%d",&A[i],&h[i]);
    FOR(i,1,n) v.push_back(A[i]);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    FOR(i,1,n) A[i]=getid(A[i]),Hid[A[i]]=i;
    FOR(i,1,n) update(1,i,1,n);
        // int j;
        // FOR(j,1,n) printf("%d ",h[Hid[j]]); puts("<- h");
    FOR(i,1,n) {
        int x=A[i];
        // printf("solve %d\n",x);
        {
            op=1; val=h[i];
            int lp=query(1,1,x-1,1,n);
            if (lp) {
                // printf("change L %d %d\n",lp,h[i]);
                h[Hid[lp]]=h[i]; update(1,lp,1,n);
            }
        }
        {
            op=2;
            int w=query(1,x+1,n,1,n);
            if (w<=h[i]) {
                op=3;
                int rp=query(1,x+1,n,1,n);
                if (rp) {
                    // printf("change R %d %d; w=%d\n",rp,h[i],w);
                    h[Hid[rp]]=h[i]; update(1,rp,1,n);
                }
            }
        }
        // int j;
        // FOR(j,1,n) printf("%d ",h[Hid[j]]); puts("<- h");
        // system("pause");
    }
    FOR(i,1,n) printf("%d ",h[i]);
}
/*
3
2 3
1 4
3 2

5
3 10
2 8
4 6
1 7
5 3
*/