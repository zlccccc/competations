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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
 
LL val[maxn<<2];
//Ä³¸öÄæÐò¶ÔµÄ¹±Ï×:l*(n-r+1);
void update(int x,int pos,LL VAL,int L,int R){
    val[x]+=VAL;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,VAL,L,mid);
    else update(x<<1|1,pos,VAL,mid+1,R);
}
LL query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return val[x];
    int mid=(L+R)/2;LL ret=0;
    if (l<=mid) ret+=query(x<<1,l,r,L,mid);
    if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
    return ret;
}
int a[maxn];
vector<int> V;
int n,m;
int i,j,k;
__int128 ans;
void print(__int128 x){
        if (x==0) {return;}
    if (x) print(x/10);
    putchar(x%10+'0');
}
int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]),V.push_back(a[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    FOR(i,1,n) a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
    FOR(i,1,n){
        ans+=1ll*(n-i+1)*query(1,a[i]+1,n+1,1,n+1);
        update(1,a[i],i,1,n+1);
    }
    print(ans);
    if (!ans) putchar('0');
}
/*
20
19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
*/
