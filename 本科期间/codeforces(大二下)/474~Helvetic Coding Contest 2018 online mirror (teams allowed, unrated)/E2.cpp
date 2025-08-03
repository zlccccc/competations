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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

struct node{
    int pos;int length;
    node(int p,int l):pos(p),length(l){}
    bool operator < (const node &A)const {
        if (A.length!=length) return length<A.length;
        return pos<A.pos;
    }
};
set<node> S;
set<node>::iterator it;
int A[maxn],pre[maxn],suf[maxn];
void del(int x){
    pre[suf[x]]=pre[x];
    suf[pre[x]]=suf[x];
}
int main() {
	int i,j,l;
	int n,k;
	int ans=0;
	scanf("%d%d",&k,&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	sort(A+1,A+1+n);n--;
	FOR(i,1,n){
	    pre[i]=i-1;suf[i]=i+1;
        A[i]=A[i+1]-A[i];
        S.insert(node(i,A[i]));
	}
//	FOR(i,1,n) printf("%d ",A[i]);puts("");
	while (k--){
        it=S.begin();
        int pos=(*it).pos;
        ans+=(*it).length;
        S.erase(it);
//        printf("%d : %d\n",pos,A[pos]);
        if (pre[pos]!=0&&suf[pos]!=n+1){
            A[pos]=A[pre[pos]]+A[suf[pos]]-A[pos];
            S.insert(node(pos,A[pos]));
        }else del(pos);
        if (pre[pos]!=0){
            int x=pre[pos];
            S.erase(node(x,A[x]));
            del(x);
        }if (suf[pos]!=n+1){
            int x=suf[pos];
            S.erase(node(x,A[x]));
            del(x);
        }
    }
	printf("%d\n",ans);
	return 0;
}
/*
8 3
3 3 1 2 2 1 1 3
0 0 1
*/
