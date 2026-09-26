#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const int maxn=1e5+7;
int a[maxn];
int n,k;
LL m;
bool mark=0;
LL check(int x){
    int i,j=0,cnt=0;
    LL ret=0;
    FOR(i,1,n){
        while (j<=n&&cnt<k){
            j++;if (a[j]>=x) cnt++;
        }
//        if (j<=n) printf("%d:%d %d\n",i,j,x);
        ret+=(n-j+1);
        if (a[i]>=x) cnt--;
    }
    return ret;
}
int main(){
    int i,j,T;
	scanf("%d",&T);
    while (T--){
        scanf("%d%d%lld",&n,&k,&m);
        FOR(i,1,n) scanf("%d",&a[i]);
        int l=0,r=INF;
        while (l+1<r){
            int mid=(l+r)/2;
//            printf("%d %lld\n",mid,check(mid));
            if (check(mid)>=m) l=mid;
            else r=mid;
        }
        printf("%d\n",l);
    }
	return 0;
}
/*
2

*/
