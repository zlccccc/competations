#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#define N 3000000
priority_queue<int> q;
int i,j;
int n,k;
int num;
int dec;
int end0,start0;
struct node{
	int s,e,pos;
}a[N+4];
bool cmp(node l,node r){
	return l.s<r.s;
}
int main()
{
	scanf("%d%d",&n,&k);
	for (i=0;i<n;i++) scanf("%d%d",&a[i].s,&a[i].e);
	for (i=0;i<n;i++) a[i].pos=i;
	sort(a,a+n,cmp);
//	for (i=0;i<n;i++) printf("%d %d\n",a[i].s,a[i].e);
	for (i=0;i<n;i++){
		q.push(-a[i].e);
		num++;
		if (num>k){
			q.pop();
			num--;
		}
		while (!q.empty()&&-q.top()<a[i].s){
			q.pop();
			num--;
		}
//		printf("%d      %d %d \n",num,a[i].s,-q.top());
		if (num==k&&-q.top()-a[i].s+1>dec) {
			dec=-q.top()-a[i].s+1;
			end0=-q.top();
			start0=a[i].s;
		}
	}
	printf("%d\n",dec);
	if (dec==0) while (k--) printf("%d ",k+1);
	else for (i=0;i<n&&k;i++) if (a[i].s<=start0&&a[i].e>=end0) printf("%d ",a[i].pos+1),k--;
	return 0;
}
