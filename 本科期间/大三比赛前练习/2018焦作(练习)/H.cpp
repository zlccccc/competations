#include <bits/stdc++.h>
using namespace std;
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rREP(I,N) for (I=N-1;I>=0;I--)
typedef long long ll;
typedef long long ll;
typedef pair<int,int> pii;
const int maxn=1e6+7;
const ll inf=0x3f3f3f3f;
const ll mod=998244353;
ll powMM(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}

int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
int cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m){
	r[n++]=0;
	int i,j,p,*x=wa,*y=wb,*t;
	REP(i,m) ws1[i]=0;
	REP(i,n) ws1[x[i]=r[i]]++;
	rep(i,1,m) ws1[i]+=ws1[i-1];
	rREP(i,n) sa[--ws1[x[i]]]=i;
	for (j=p=1;p<n;j<<=1,m=p){
		p=0; rep(i,n-j,n) y[p++]=i;
		REP(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;
		REP(i,n) wv[i]=x[y[i]];
		REP(i,m) ws1[i]=0;
		REP(i,n) ws1[wv[i]]++;
		rep(i,1,m) ws1[i]+=ws1[i-1];
		rREP(i,n) sa[--ws1[wv[i]]]=y[i];
		t=x; x=y; y=t;
		p=1; x[sa[0]]=0;
		rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rnk[maxn],height[maxn];
ll rpos[maxn],sum;//more_sum
int l[maxn],r[maxn],id[maxn];
int R[maxn];//towards R->
void calheight(int *r,int *sa,int n){
	int i,j,k=0; ll psum=0;
	FOR(i,1,n) rnk[sa[i]]=i;
	// REP(i,n) printf("%d ",R[i]); puts("<- R");
	deque<pii> stk;//单调栈
	REP(i,n){
		if (k) {
			k--; //del_first
			//change_first
			pii now=*stk.rbegin(); stk.pop_back();
			psum-=(ll)now.first*now.second; now.second--;//first
			vector<pii> more;
			int p=i;
			while (now.second){
				int t=min(now.second,R[p]-p);
				psum+=(ll)r[p]*t;
				more.push_back(make_pair(r[p],t));
				now.second-=t; p=R[p];
			} reverse(more.begin(), more.end());
			for (auto now:more) stk.push_back(now);
		} j=sa[rnk[i]-1];
		// printf("%d %d\n",i,j);
		while (r[i+k]==r[j+k]) {
			if (!stk.size()||stk.front().first<r[i+k])
				stk.push_front(make_pair(r[i+k],0));
			psum+=stk.front().first; k++; stk.front().second++;//end
			// printf("k=%d\n",k);
		} //add back
		sum-=psum;
		// int t;
		// rep(t,j,n) printf("%d ",r[t]); printf("height=%d\n",k);
		// rep(t,i,n) printf("%d ",r[t]); puts(" < fir");
		// for(auto now:stk) printf("%d-%d ",now.first,now.second); puts("<- instack");
		// printf("psum= %lld\n",psum);
		height[rnk[i]]=k;
	}
}
int A[maxn],C[maxn];
vector<int> V;
int sa[maxn];
int main(){
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n; int i;
		scanf("%d",&n);
		V.clear();
		FOR(i,1,n) scanf("%d",&A[i]),V.push_back(A[i]);
		//first
		FOR(i,1,n) id[i]=i,l[i]=i-1,r[i]=i+1;
		sort(id+1,id+1+n,[](int i,int j){
			return A[i]<A[j];
		}); ll ans=0; sum=0;
		FOR(i,1,n) {
			ans+=(ll)A[id[i]]*(r[id[i]]-id[i])*(id[i]-l[id[i]]);
			R[id[i]-1]=r[id[i]]-1;
			l[r[id[i]]]=l[id[i]];
			r[l[id[i]]]=r[id[i]];
		}// printf(" ans1=%lld\n",ans);
		sort(V.begin(), V.end());
		V.erase(unique(V.begin(), V.end()),V.end());
		FOR(i,1,n) C[i-1]=lower_bound(V.begin(), V.end(),A[i])-V.begin()+1;
		da(C,sa,n,n+1);
		// FOR(i,0,n) printf("%d ",sa[i]); puts("");
		// puts("yes1");
		FOR(i,1,n) C[i-1]=A[i];
		calheight(C,sa,n);
		printf("%lld\n",ans+sum);
	}
}
/*
10
10
3 2 4 1 5 4 1 1 1 5
10
2 2 2 2 2 2 2 2 2 2
11
3 2 1 1 5 3 2 1 1 5 3

5
3 1 2 1 2

5
1 2 3 2 3
4
1 2 1 2
6
1 2 3 1 2 3
5
1 2 1 2 1
5
1 2 1 2 3
*/