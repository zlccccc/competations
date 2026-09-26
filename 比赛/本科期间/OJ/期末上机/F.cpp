#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <algorithm>
#define REP(I,S,N) for (I=S;I<N;I++)
#define rREP(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
const int maxn=1e6+7;
const int INF=0x3f3f3f3f;
using namespace std;
typedef long long LL;
//奇了怪了。。为啥CB不对啊 
int f[maxn];
LL a[maxn],l[maxn];
LL h,allt;
    int T,n,m,i,j;
bool cmp(int i,int j){
    return a[i]*l[j]>a[j]*l[i];
}
int main(){
    while (~scanf("%d%lld",&n,&h)){
        FOR(i,1,n) scanf("%lld%lld",&a[i],&l[i]),f[i]=i;
        sort(f+1,f+1+n,cmp);
        allt=0;
        FOR(i,1,n){
			allt+=l[f[i]];
			if (h>0) h-=a[f[i]]*allt;
		}
//        printf("%lld %d\n",h,0);
        if (h<=0) puts("NO");
        else puts("YES");
    }
}