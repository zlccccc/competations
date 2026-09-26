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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

template<typename T>inline T powMM(T a, T b,T M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
const int maxsqrtk=3.5e7+7;
int p[maxsqrtk],cntp;
void initfactor() {
	int i,j;
	rep(i,2,maxsqrtk) {
		if (!p[i]) p[cntp++]=i;
		REP(j,cntp) {
			if (i*p[j]>=maxsqrtk) break;
			p[i*p[j]]=1;
			if (i%p[j]==0) break;
		}
	}
	debug("cnt_prime=%d\n",cntp);
}
const int maxk=57;
vector<LL> minvalue[maxk],factor[maxk];
LL kth[maxk],cntk;
typedef pair<LL,LL> pll;
priority_queue<pll,vector<pll>,less<pll> > Q;
int TaskA() {
	int i,id;
	LL n,k;
	scanf("%I64d%I64d",&n,&k);
	REP(id,cntk) if (kth[id]==k) break;
	if (cntk==id) {
		//init
		deputs("initialize");
		kth[cntk++]=k;
		REP(i,cntp) {
			if (p[i]>k/p[i]) break;
			if (k%p[i]==0) factor[id].push_back(p[i]);
			while (k%p[i]==0) k/=p[i];
		} if (k!=1) factor[id].push_back(k);
//        for (LL v:factor[id]) debug("%I64d ",v);deputs("  <- v");
		if (factor[id].size()>2) {
//            deputs("factor>2");
			LL p=factor[id][0];
			minvalue[id].resize(p,INFF);
			minvalue[id][0]=0;
			Q.push(make_pair(0ll,0ll));
			while (Q.size()) {
				auto now=Q.top(); Q.pop();
				LL pos=now.second;
				if (minvalue[id][pos]!=now.first) continue;
				for (LL len:factor[id]) if (len!=p) {
						LL nxtpos=(pos+len)%p,nxtlen=minvalue[id][pos]+len;
						if (minvalue[id][nxtpos]>nxtlen) {
							minvalue[id][nxtpos]=nxtlen;
							Q.push(make_pair(minvalue[id][nxtpos],nxtpos));
						}
					}
			}
		}
	}
	if (factor[id].size()==0) {
		return 0*puts("NO");
	} if (factor[id].size()==1) {
		if (n%factor[id][0]==0) return 0*puts("YES");
		else return 0*puts("NO");
	} if (factor[id].size()==2) { //ax+by=n; calculate a_min
		LL inv,a,p1=factor[id][0],p2=factor[id][1];
		inv=powMM(p1,p2-2,p2); a=n%p2*inv%p2;
		if (a*p1<=n) return 0*puts("YES");
		else return 0*puts("NO");
	} else {
		if (minvalue[id][n%factor[id][0]]<=n) return 0*puts("YES");
		else return 0*puts("NO");
	}
}
int main() {
	int startTime=clock();
	initfactor();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
