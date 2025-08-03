#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int tot;
int n,i;
int a[maxn],root[maxn],tmp,cnt;
int last[maxn];//ȥ��
struct node{
	int left,right,sum; 
}T[maxn*40];
void update(int l,int r,int &x,int y,int pos,int v){
	T[++cnt]=T[y];T[cnt].sum+=v;x=cnt;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=pos) update(l,mid,T[x].left,T[y].left,pos,v);
	else update(mid+1,r,T[x].right,T[y].right,pos,v);
}
int query(int l,int r,int x,int k){//ֻ�õ�����˵�...����ZZ 
	if (l==r) return l;//����returnɶ����� 
	int mid=(l+r)/2;
	int sum=T[T[x].left].sum;
	if (sum>k) return query(l,mid,T[x].left,k);
	else return query(mid+1,r,T[x].right,k-sum);
}
int ask(int i){
	int t=1,ret=0;
	while (t<=n){
		t=query(1,n+1,root[t],i);
		ret++;
	}
	return ret;
}
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	rFOR(i,1,n){//���ﷴ�����ԭ��������Ҫ��ǰ�������k��λ�ô�ǰ����-1���� 
		if (!last[a[i]])
			update(1,n+1,root[i],root[i+1],i,1);//n+1��Ϊ�˳��� 
		else{
			update(1,n+1,tmp,root[i+1],last[a[i]],-1);
			update(1,n+1,root[i],tmp,i,1);//tmp��Ȼû�á�����root���� 
		}
		last[a[i]]=i;
	}
	FOR(i,1,n) printf("%d ",ask(i));
}
/*
*/
