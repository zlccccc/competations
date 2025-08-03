#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#define N 5001
#define AND 1
#define OR 2
#define XOR 3
using namespace std;
bool num[N][N],t[N];
int n,m,x[N],y[N],o[N],ansmin[N],ansmax[N];
string a,b;
map <string,int> mp;
int f(int dig,bool b)
{
	int s=0;
	for(int i=1;i<=n;i++)
	{
		if(o[i])
		{
			int xx,yy;
			if(x[i]==-1)xx=b;
			else xx=t[x[i]];
			if(y[i]==-1)yy=b;
			else yy=t[y[i]];
			if(o[i]==AND)t[i]=xx&yy;
			else if(o[i]==OR)t[i]=xx|yy;
			else if(o[i]==XOR)t[i]=xx^yy;
		}
		else t[i]=num[i][dig];
		s+=t[i];
	}
	return s;
}
int main(int argc, char *argv[])
{
	string t;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>t>>b;
		mp[a]=i;
		if(b[0]>='0'&&b[0]<='9')
		{
			for(int j=1;j<=m;j++)
				num[i][j]=b[j-1]-'0';
		}
		else
		{
			if(b[0]=='?')x[i]=-1;
			else x[i]=mp[b];
			cin>>t;
			if(t[0]=='A')o[i]=AND;
			else if(t[0]=='O')o[i]=OR;
			else if(t[0]=='X')o[i]=XOR;
			cin>>b;
			if(b[0]=='?')y[i]=-1;
			else y[i]=mp[b];
		}
	}
	for(int i=1;i<=m;i++)
	{
		int x=f(i,0),y=f(i,1);
		if(x<=y)ansmin[i]=0;else ansmin[i]=1;
		if(x>=y)ansmax[i]=0;else ansmax[i]=1;
	}
	for(int i=1;i<=m;i++)
		cout<<ansmin[i];cout<<endl;
	for(int i=1;i<=m;i++)
		cout<<ansmax[i];cout<<endl;
	return 0;
}