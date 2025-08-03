#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<queue>
using namespace std;
const int maxn=2009;

set<string>S;
string a[maxn],b[maxn];

int n,m;
int col[maxn];
queue<int>q;
vector<int>G[maxn];
void bfs(int s){
	col[s]=1;q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<G[x].size();++i){
			int v=G[x][i];
			if(col[v])continue;
			col[v]=3-col[x];
			q.push(v);
		}
	}
}

int match[maxn],vis[maxn];
int dfs(int x){
	for(int i=0;i<G[x].size();++i){
		int v=G[x][i];
		if(vis[v])continue;
		vis[v]=1;
		if(!match[v]||dfs(match[v])){
			match[v]=x;return 1;
		}
	}
	return 0;
}

int h[maxn],r[maxn];
void dfs2(int x){
	if(h[x])return;
	h[x]=1;
	for(int i=0;i<G[x].size();++i){
		int v=G[x][i];h[v]=1;
		v=r[v];
		dfs2(v);
	}
}

char s[maxn];
int main(){
	scanf("%d",&m);
	while(m--)scanf("%s",s);
	scanf("%d",&m);
	while(m--)scanf("%s",s);
	
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i];
		for(int j=1;j<i;++j){
			if(a[i]==b[j]||a[j]==b[i]){
				G[i].push_back(j);
				G[j].push_back(i);
			}
		}
	}
	for(int i=1;i<=n;++i)if(!col[i])bfs(i);
	for(int i=1;i<=n;++i){
		if(col[i]==2)continue;
		memset(vis,0,sizeof(vis));
		dfs(i);
	}
	for(int i=1;i<=n;++i)if(match[i])r[match[i]]=i;
	for(int i=1;i<=n;++i){
		if(col[i]==2)dfs2(i);
	}
	int cnt=0;
	for(int i=1;i<=n;++i){
		if(col[i]==1&&h[i]){
			if(S.count(b[i]))continue;
			S.insert(b[i]);++cnt;
		}
		if(col[i]==2&&!h[i]){
			if(S.count(b[i]))continue;
			S.insert(b[i]);++cnt;
		}
	}
	S.clear();
	printf("%d\n",cnt);
	for(int i=1;i<=n;++i){
		if(col[i]==1&&h[i]){
			if(S.count(b[i]))continue;
			S.insert(b[i]);
			cout<<b[i]<<endl;
		}
		if(col[i]==2&&!h[i]){
			if(S.count(b[i]))continue;
			S.insert(b[i]);
			cout<<b[i]<<endl;
		}
	}
	return 0;
}
