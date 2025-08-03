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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char c[maxn];
int n,m;
char a[maxn],b[maxn];
vector<int> ans;
void change(int x){
    ans.push_back(n-x);
    int i,j;
    FOR(i,1,n) c[i]=a[i];
    FOR(i,1,n) a[i]=c[(i-1+x)%n+1];
//    printf("change %d : %s  ",x,a+1);
    reverse(a+1,a+n-x+1);
//    printf("change %d : %s\n",x,a+1);
}
int i,j,k;
bool rev;
int cnt[255];
int l,r,now;
int main(){
    scanf("%d",&n);
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1);
    FOR(i,1,n) cnt[a[i]]++,cnt[b[i]]--;
    REP(i,255) if (cnt[i]) return 0*puts("-1");
    l=(n+1)/2;r=l+1;now=0;
    while (now!=n){
//        printf("l-r = %d %d\n",l,r);
        if (1<=l){
            int nxt=now+1;
            while (a[nxt]!=b[l]) nxt++;
//            printf("now,nxt=%d %d\n",now,nxt);
            change(nxt-1);change(n-nxt+now+1);change(n-now-1);
            now++;l--;
        }else change(now),change(n-now);
//        FOR(i,1,now) printf("%c",a[i]);puts("");
        if (r<=n){
            int nxt=now+1;
            while (a[nxt]!=b[r]) nxt++;
            change(nxt-1);change(n-nxt+now+1);change(n-now-1);
            now++;r++;
        }else change(now),change(n-now);
//        FOR(i,1,now) printf("%c",a[i]);puts("");
    }printf("%d\n",ans.size());
    for (int v:ans) printf("%d ",v);
}
/*
*/
