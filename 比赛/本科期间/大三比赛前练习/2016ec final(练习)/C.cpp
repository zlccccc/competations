#include <bits/stdc++.h>
#include <utility>
#include <algorithm>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
typedef long long ll;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const int maxn=8e5+7;
const ll mod=1e9+7;
ll powMM(ll a,ll b,ll M=mod){
    ll ret=1;
    for (;b;b>>=1,a=a*a%M)
        if (b&1) ret=ret*a%M;
    return ret;
}

int C[maxn],A[maxn];//count
inline void ins(int x){C[A[x]]++;}
inline void rem(int x){C[A[x]]--;}
int main(){
    int _,T; scanf("%d",&T);
    FOR(_,1,T){
        int i,n;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&A[i]);
        int l1=1,r1,ans=0;
        FOR(r1,1,n) {
        	ins(r1); while (C[A[r1]]==2) rem(l1++);//first_first
        	int pre=-1;
        	int tmp=l1;
        	while (l1<=r1){
        		int l2=r1+1,r2,now=0;
        		FOR(r2,r1+1,n){
        			ins(r2); while (C[A[r2]]==2) rem(l2++);
        			now=max(now,r2-l2+1+r1-l1+1);
        		} while (l2<r2) rem(l2++);
        		// printf("%d-%d %d-%d : %d  %d\n",l1,r1,l2,r2,now,C[0]);
        		ans=max(ans,now);
        		if (now>pre) pre=now;
        		// else break;
        		rem(l1++);
        	} while (l1!=tmp) ins(--l1);
        	// printf("%d-%d : %d\n",l1,r1,pre);
      	  	// FOR(i,1,10) printf("%d ",C[i]);puts("");
        } while (l1<r1) rem(l1++);
        // printf("last %d-%d : %d\n",l1,r1,ans);
      	// FOR(i,0,10) printf("%d ",C[i]);puts("");
        printf("Case #%d: %d\n",_,ans);
    }
}
/*
3 3 1 2 3 8 3 1 2 1 6 1 2 5
3
1 1 1
*/