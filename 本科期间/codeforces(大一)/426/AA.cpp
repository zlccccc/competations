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
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int T;
int a[]={
	2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,
	53,59,61,67,71,73,79,83,89,97,
	101,103,107,109,113,127,131,137,139,149,
	151,157,163,167,173,179,181,191,193,197,199,
	211,223,227,229,233,239,241,
	251,257,263,269,271,277,281,283,293,
	307,311,313,317,331,337,347,349,
	353,359,367,373,379,383,389,397,
	401,409,419,421,431,433,439,443,449,
	457,461,463,467,479,487,491,499,
	503,509,521,523,541,547,
	557,563,569,571,577,587,593,599,
	601,607,613,617,619,631,641,643,647,
	653,659,661,673,677,683,691,
	701,709,719,727,733,739,743,
	751,757,761,769,773,787,797,
	809,811,821,823,827,829,839,
	853,857,859,863,877,881,883,887,
	907,911,919,929,937,941,947,
	953,967,971,977,983,991,997};
LL n,m,t,i;
int t1,t2;
inline int solve(LL n,LL m){
	t=pow(n*m,1.0/3);
	if ((t-1)*(t-1)*(t-1)==n*m) t--;
	if ((t+1)*(t+1)*(t+1)==n*m) t++;
	if (t*t*t!=n*m) return 0*puts("No");
	REP(i,168){
		if (t<a[i]) break;
		if (t%a[i]==0){
			t1=t2=0;
			while (n%a[i]==0) n/=a[i],t1++;
			while (m%a[i]==0) m/=a[i],t2++;
			if (t1>2*t2||t2>2*t1) return 0*puts("No");
			while (t%a[i]==0) t/=a[i];
		}
	}
	if (t==1) return 0*puts("Yes");
	t1=t2=0;
	while (n%t==0) n/=t,t1++;
	while (m%t==0) m/=t,t2++;
	if (t1>2*t2||t2>2*t1) return 0*puts("No");
	puts("Yes");
}
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%I64d%I64d",&n,&m);
		solve(n,m);
	}
}
/*
*/
