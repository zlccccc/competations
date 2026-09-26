program p6;
const
  dx:array[1..4]of integer=(-1,0,1,0);
  dy:array[1..4]of integer=(0,1,0,-1);
  hn=502397;
type
  list=
  record
    ln,code:integer;
    x,y:array[1..9]of integer;
  end;
  link=^node;
  node=
  record
    data:list;
    next:link;
  end;
var
  n,i,j,k,t,m,p,sn,cn,sx,sy,usen,usew,best:integer;
  map:array[1..10,1..9,1..9]of boolean;
  s:array[1..10]of integer;
  w:array[1..13702]of list;
  vis:array[-9..9,-9..9]of boolean;
  cov,re:array[1..10,1..9,1..9]of integer;
  use:array[1..1818]of integer;
  now,tmp:list;
  r,tt:array[0..8,0..8]of integer;
  hash:array[0..hn-1]of link;
//
function equal (var d1,d2:list):boolean;
var
  i,j:integer;
begin
  if d1.ln<>d2.ln then
    exit(false);
  fillchar(tt,sizeof(tt),0);
  for i:=1 to d1.ln do
    inc(tt[d1.x[i],d1.y[i]]);
  for i:=1 to d2.ln do
    dec(tt[d2.x[i],d2.y[i]]);
  for i:=0 to 8 do
    for j:=0 to 8 do
      if tt[i,j]<>0 then
        exit(false);
  exit(true);
end;
//
function has (var tmp:list):boolean;
var
  i,h:integer;
  p:link;
begin
  sx:=100;
  sy:=100;
  for i:=1 to tmp.ln do
  begin
    if tmp.x[i]<sx then
      sx:=tmp.x[i];
    if tmp.y[i]<sy then
      sy:=tmp.y[i];
  end;
  for i:=1 to tmp.ln do
  begin
    dec(tmp.x[i],sx);
    dec(tmp.y[i],sy);
  end;
  h:=0;
  for i:=1 to tmp.ln do
    h:=(h+r[tmp.x[i],tmp.y[i]]) mod hn;
  p:=hash[h];
  while p<>nil do
  begin
    if equal(tmp,p^.data) then
      exit(true);
    p:=p^.next;
  end;
  new(p);
  p^.data:=tmp;
  p^.next:=hash[h];
  hash[h]:=p;
  exit(false);
end;
//
procedure add (var tmp:list);
begin
  inc(sn);
  w[sn]:=tmp;
end;
//
procedure r1 (var tmp:list);
var
  i:integer;
begin
  for i:=1 to tmp.ln do
    tmp.y[i]:=20-tmp.y[i];
end;
//
procedure r2 (var tmp:list);
var
  i:integer;
begin
  for i:=1 to tmp.ln do
    tmp.x[i]:=20-tmp.x[i];
end;
//
procedure r3 (var tmp:list);
var
  i:integer;
begin
  for i:=1 to tmp.ln do
  begin
    t:=tmp.y[i];
    tmp.y[i]:=tmp.x[i];
    tmp.x[i]:=20-t;
  end;
end;
//
function exist:boolean;
begin
  tmp:=now;
  if has(tmp) then
    exit(true);
  inc(cn);
  tmp.code:=cn;
  add(tmp);
  r1(tmp);
  if not has(tmp) then
    add(tmp);
  r2(tmp);
  if not has(tmp) then
    add(tmp);
  r1(tmp);
  if not has(tmp) then
    add(tmp);
  r3(tmp);
  if not has(tmp) then
    add(tmp);
  r1(tmp);
  if not has(tmp) then
    add(tmp);
  r2(tmp);
  if not has(tmp) then
    add(tmp);
  r1(tmp);
  if not has(tmp) then
    add(tmp);
  exit(false);
end;
//
procedure DFS (dep:integer);
var
  i,j,tx,ty:integer;
begin
  if dep>p then
    exit;
  for i:=1 to now.ln do
    for j:=1 to 4 do
    begin
      tx:=now.x[i]+dx[j];
      ty:=now.y[i]+dy[j];
      if not vis[tx,ty] then
      begin
        inc(now.ln);
        now.x[now.ln]:=tx;
        now.y[now.ln]:=ty;
        vis[tx,ty]:=true;
        if not exist then
          DFS(dep+1);
        dec(now.ln);
        vis[tx,ty]:=false;
      end;
    end;
end;
//
function can (now,x,y,wi:integer):boolean;
var
  i:integer;
begin
  for i:=1 to w[wi].ln do
  begin
    if (x+w[wi].x[i]<1) or (x+w[wi].x[i]>s[now]) or (y+w[wi].y[i]<1) or (y+w[wi].y[i]>s[now]) then
      exit(false);
    if (cov[now,x+w[wi].x[i],y+w[wi].y[i]]<>0) or not map[now,x+w[wi].x[i],y+w[wi].y[i]] then
      exit(false);
  end;
  exit(true);
end;
//
procedure search (now,x,y:integer);
var
  i,j:integer;
  back:boolean;
begin
  if usen>m then
    exit;
  if usew>=best then
    exit;
  if now>n then
  begin
    best:=usew;
    re:=cov;
    exit;
  end;
  if x>s[now] then
  begin
    search(now+1,1,1);
    exit;
  end;
  if y>s[now] then
  begin
    search(now,x+1,1);
    exit;
  end;
  if not map[now,x,y] or (cov[now,x,y]<>0) then
  begin
    search(now,x,y+1);
    exit;
  end;
  for i:=1 to sn do
    if can (now,x,y,i) then
    begin
      inc(usew);
      if use[w[i].code]=0 then
      begin
        inc(usen);
        use[w[i].code]:=usen;
        back:=true;
      end
      else
        back:=false;
      for j:=1 to w[i].ln do
        cov[now,x+w[i].x[j],y+w[i].y[j]]:=use[w[i].code];
      search(now,x,y+1);
      for j:=1 to w[i].ln do
        cov[now,x+w[i].x[j],y+w[i].y[j]]:=0;
      if back then
      begin
        dec(usen);
        use[w[i].code]:=0;
      end;
      dec(usew);
    end;
end;
//
begin
  assign(input,'p6.in');
  reset(input);
  readln(n);
  for i:=1 to n do
  begin
    readln(s[i]);
    for j:=1 to s[i] do
    begin
      for k:=1 to s[i] do
      begin
        read(t);
        map[i,j,k]:=t=1;
      end;
      readln;
    end;
  end;
  readln;
  assign(input,'');
  reset(input);
  readln(m,p);
  w[1].ln:=1;
  w[1].x[1]:=0;
  w[1].y[1]:=0;
  w[1].code:=1;
  now:=w[1];
  fillchar(vis,sizeof(vis),false);
  vis[0,0]:=true;
  sn:=1;
  cn:=1;
  t:=1;
  for i:=0 to p-1 do
    for j:=0 to p-1 do
    begin
      r[i,j]:=t;
      t:=t*64 mod hn;
    end;
  for i:=0 to hn-1 do
    hash[i]:=nil;
  DFS(2);
  for i:=1 to sn do
  begin
    sx:=100;
    sy:=100;
    for j:=1 to w[i].ln do
      if (w[i].x[j]<sx) or (w[i].x[j]=sx) and (w[i].y[j]<sy) then
      begin
        sx:=w[i].x[j];
        sy:=w[i].y[j];
      end;
    for j:=1 to w[i].ln do
    begin
      dec(w[i].x[j],sx);
      dec(w[i].y[j],sy);
    end;
  end;
  best:=100;
  search(1,1,1);
  for i:=1 to n do
  begin
    for j:=1 to s[i] do
    begin
      for k:=1 to s[i] do
        if re[i,j,k]>0 then
          write(chr(re[i,j,k]+64))
        else
          write(' ');
      writeln;
    end;
    writeln;
  end;
  writeln(best);
  readln;
end.
