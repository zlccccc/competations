program p33;
const
  size=20;
type
  state=array[1..size,0..size]of integer;
  link=^node;
  node=
  record
    s:state;
    next:link;
  end;
var
  maxn,tot,i:integer;
  s:state;
  h:array[1..size]of link;
//
function same (var s1,s2:state;n:integer):boolean;
var
  i,j,n1,n2,r1,r2:integer;
  list:array[0..size]of integer;
  tick2:array[1..size]of boolean;
  d1,d2,t1,t2:array[1..size]of integer;
//**
function equal (p1,p2,f1,f2:integer):boolean;
var
  i,j:integer;
  match:boolean;
begin
  if d1[p1]<>d2[p2] then
    exit(false);
  for i:=1 to s1[p1,0] do
    if s1[p1,i]<>f1 then
    begin
      match:=false;
      for j:=1 to s2[p2,0] do
        if (s2[p2,j]<>f2) and not tick2[s2[p2,j]] then
          if equal(s1[p1,i],s2[p2,j],p1,p2) then
          begin
            tick2[s2[p2,j]]:=true;
            match:=true;
            break;
          end;
      if not match then
        exit(false);
    end;
  exit(true);
end;
//**
begin
  n1:=n;
  n2:=n;
  for i:=1 to n do
  begin
    d1[i]:=s1[i,0];
    d2[i]:=s2[i,0];
  end;
  t1:=d1;
  while n1>2 do
  begin
    list[0]:=0;
    for i:=1 to n do
      if t1[i]=1 then
      begin
        inc(list[0]);
        list[list[0]]:=i;
      end;
    dec(n1,list[0]);
    for i:=1 to list[0] do
    begin
      t1[list[i]]:=-1;
      for j:=1 to s1[list[i],0] do
        if t1[s1[list[i],j]]<>-1 then
          dec(t1[s1[list[i],j]]);
    end;
  end;
  t2:=d2;
  while n2>2 do
  begin
    list[0]:=0;
    for i:=1 to n do
      if t2[i]=1 then
      begin
        inc(list[0]);
        list[list[0]]:=i;
      end;
    dec(n2,list[0]);
    for i:=1 to list[0] do
    begin
      t2[list[i]]:=-1;
      for j:=1 to s2[list[i],0] do
        if t2[s2[list[i],j]]<>-1 then
          dec(t2[s2[list[i],j]]);
    end;
  end;
  if n1<>n2 then
    exit(false);
  r2:=1;
  while t2[r2]=-1 do
    inc(r2);
  for r1:=1 to n do
  begin
    fillchar(tick2,sizeof(tick2),false);
    if t1[r1]<>-1 then
      if equal(r1,r2,0,0) then
        exit(true);
  end;
  exit(false);
end;
//
procedure print (ss,f:integer);
var
  i:integer;
begin
  write('P');
  if (s[ss,0]=1) and (s[ss,1]=f) then
    exit;
  write('(');
  for i:=1 to s[ss,0] do
    if s[ss,i]<>f then
      print(s[ss,i],ss);
  write(')');
end;
//
function visit (now:integer):boolean;
var
  p:link;
begin
  p:=h[now];
  while p<>nil do
  begin
    if same(s,p^.s,now) then
      exit(true);
    p:=p^.next;
  end;
  new(p);
  p^.s:=s;
  p^.next:=h[now];
  h[now]:=p;
  exit(false);
end;
//
procedure search (now:integer);
var
  i:integer;
begin
  if now>maxn then
  begin
    print(1,0);
    writeln;
    inc(tot);
    exit;
  end;
  for i:=1 to now-1 do
  begin
    inc(s[i,0]);
    s[i,s[i,0]]:=now;
    s[now,0]:=1;
    s[now,1]:=i;
    if not visit(now) then
      search(now+1);
    dec(s[i,0]);
    s[now,0]:=0;
  end;
end;
//
begin
  readln(maxn);
  for i:=1 to maxn do
    h[i]:=nil;
  search(2);
  writeln(tot);
  readln;
end.
