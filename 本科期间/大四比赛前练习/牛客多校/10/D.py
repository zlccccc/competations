x,y=0,0
def exgcd(a,b):
	global x,y
	if b==0:
		x,y=1,0
		return a
	# print("a,bini",a,b)
	d=exgcd(b,a%b)
	t=x
	# print("a,b,x,y,t_ini",a,b,x,y,t)
	x=y
	y=t-a//b*y
	# print("x,y,t",x,y,t)
	return d
_n,_m=map(int,input().split())
flag,k,m=1,1,0
for i in range(_n):
	u,v=map(int,input().split())
	a,r=u,v
	if flag==1:
		d=exgcd(k,a)
		# print(x,y,d,m,r)
		if (r-m)%d!=0:
			flag=0
			continue
		x=(x*(r-m)//d+a//d)%(a//d)
		y=k//d*a
		m=(x*k+m)%y
		if m<0:
			m+=y
		k=y
		# print("k=",k)
ans=m
if flag==1:
	if ans<=_m:
		print(ans)
	else :
		print("he was probably lying")
if flag==0:
	print("he was definitely lying")