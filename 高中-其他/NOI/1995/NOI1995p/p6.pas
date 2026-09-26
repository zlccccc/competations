program p6;
const
  dx:array[1..5]of shortint=(-1,0,1,0,0);
  dy:array[1..5]of shortint=(0,1,0,-1,0);
var
  m,n,i,j,t,r:shortint;
  map:array[0..17,0..17]of boolean;
  sx,sy,fx,fy:array[1..6]of shortint;
//
procedure solve1;
type
  data=
  record
    x,y:shortint;
    pre:word;
  end;
var
  f,e,mm:word;
  tx,ty,i,step:shortint;
  slot:array[1..256]of data;
  vis:array[0..16,0..16]of boolean;
//**
procedure print (s:word);
begin
  if slot[s].pre=0 then
    exit;
  print(slot[s].pre);
  writeln(slot[s].x,' ',slot[s].y);
end;
//**
begin
  f:=1;
  e:=2;
  mm:=1;
  step:=1;
  slot[f].x:=sx[1];
  slot[f].y:=sy[1];
  slot[f].pre:=0;
  fillchar(vis,sizeof(vis),false);
  vis[sx[1],sy[1]]:=true;
  repeat
    for i:=1 to 4 do
    begin
      tx:=slot[f].x+dx[i];
      ty:=slot[f].y+dy[i];
      if map[tx,ty] and not vis[tx,ty] then
      begin
        slot[e].x:=tx;
        slot[e].y:=ty;
        slot[e].pre:=f;
        vis[tx,ty]:=true;
        if (tx=fx[1]) and (ty=fy[1]) then
        begin
          writeln(step);
          print(e);
          exit;
        end;
        inc(e);
      end;
    end;
    inc(f);
    if f>mm then
    begin
      mm:=e-1;
      inc(step);
    end;
  until (f=e) or (step>60);
  writeln(-1);
end;
//
procedure solve2;
{$M 688128}
type
  data=
  record
    x,y:array[1..2]of shortint;
    pre:word;
  end;
var
  f,e,mm:word;
  step:shortint;
  tx,ty:array[1..2]of shortint;
  slot:array[1..65536]of data;
  vis:array[0..16,0..16,0..16,0..16]of boolean;
//**
procedure print (s:word);
begin
  if slot[s].pre=0 then
    exit;
  print(slot[s].pre);
  writeln(slot[s].x[1],' ',slot[s].y[1],' ',slot[s].x[2],' ',slot[s].y[2]);
end;
//**
procedure search (d:shortint);
var
  i,j:shortint;
begin
  if d>r then
  begin
    if vis[tx[1],ty[1],tx[2],ty[2]] then
      exit;
    for i:=1 to r do
    begin
      slot[e].x[i]:=tx[i];
      slot[e].y[i]:=ty[i];
    end;
    slot[e].pre:=f;
    vis[tx[1],ty[1],tx[2],ty[2]]:=true;
    i:=1;
    while (i<=r) and ((tx[i]=fx[i]) and (ty[i]=fy[i]) or (tx[i]=0) and (ty[i]=0)) do
      inc(i);
    if i>r then
    begin
      writeln(step);
      print(e);
      close(output);
      halt;
    end;
    inc(e);
    exit;
  end;
  if (slot[f].x[d]=fx[d]) and (slot[f].y[d]=fy[d]) or (slot[f].x[d]=0) and (slot[f].y[d]=0) then
  begin
    tx[d]:=0;
    ty[d]:=0;
    search(d+1);
    exit;
  end;
  for i:=1 to 5 do
  begin
    tx[d]:=slot[f].x[d]+dx[i];
    ty[d]:=slot[f].y[d]+dy[i];
    if not map[tx[d],ty[d]] then
      continue;
    j:=1;
    while (j<d) and not ((tx[j]=tx[d]) and (ty[j]=ty[d])) and not ((tx[j]=slot[f].x[d]) and (ty[j]=slot[f].y[d]) and (tx[d]=slot[f].x[j]) and (ty[d]=slot[f].y[j])) do
      inc(j);
    if j<d then
      continue;
    search(d+1);
  end;
end;
//**
begin
  f:=1;
  e:=2;
  mm:=1;
  step:=1;
  slot[f].x[1]:=sx[1];
  slot[f].y[1]:=sy[1];
  slot[f].x[2]:=sx[2];
  slot[f].y[2]:=sy[2];
  slot[f].pre:=0;
  fillchar(vis,sizeof(vis),false);
  vis[sx[1],sy[1],sx[2],sy[2]]:=true;
  repeat
    search(1);
    inc(f);
    if f>mm then
    begin
      mm:=e-1;
      inc(step);
    end;
  until (f=e) or (step>60);
  writeln(-1);
end;
//
procedure solve;
type
  data=
  record
    x,y:array[1..6]of shortint;
  end;
var
  f,i,pre,best:shortint;
  sum,bests:word;
  tx,ty,bx,by:array[1..6]of shortint;
  slot:array[1..60]of data;
  dis:array[1..6,0..16,0..16]of shortint;
//**
procedure print (s,d:shortint);
begin
  if s>f+1 then
  begin
    close(output);
    halt;
  end;
  write(slot[s].x[d],' ',slot[s].y[d]);
  if d=r then
  begin
    writeln;
    print(s+1,1);
  end
  else
  begin
    write(' ');
    print(s,d+1);
  end;
end;
//**
procedure search (d:shortint);
var
  i,j:shortint;
begin
  if d>r then
  begin
    i:=1;
    while (i<=r) and (tx[i]=slot[f].x[i]) and (ty[i]=slot[f].y[i]) do
      inc(i);
    if i>r then
      exit;
    pre:=0;
    sum:=0;
    for i:=1 to r do
    begin
      if dis[i,tx[i],ty[i]]>pre then
        pre:=dis[i,tx[i],ty[i]];
      inc(sum,dis[i,tx[i],ty[i]]);
    end;
    if (pre<best) or (pre=best) and (sum<bests) then
    begin
      bests:=sum;
      best:=pre;
      bx:=tx;
      by:=ty;
    end;
    exit;
  end;
  if (slot[f].x[d]=fx[d]) and (slot[f].y[d]=fy[d]) or (slot[f].x[d]=0) and (slot[f].y[d]=0) then
  begin
    tx[d]:=0;
    ty[d]:=0;
    search(d+1);
    exit;
  end;
  for i:=1 to 5 do
  begin
    tx[d]:=slot[f].x[d]+dx[i];
    ty[d]:=slot[f].y[d]+dy[i];
    if not map[tx[d],ty[d]] then
      continue;
    j:=1;
    while (j<d) and not ((tx[j]=tx[d]) and (ty[j]=ty[d])) and not ((tx[j]=slot[f].x[d]) and (ty[j]=slot[f].y[d]) and (tx[d]=slot[f].x[j]) and (ty[d]=slot[f].y[j])) do
      inc(j);
    if j<d then
      continue;
    search(d+1);
  end;
end;
//**
procedure getdis (s:shortint);
type
  tdata=
  record
    x,y:shortint;
  end;
var
  f,e,tx,ty,i,ss,mm:shortint;
  slot:array[1..256]of tdata;
  vis:array[1..16,1..16]of boolean;
begin
  f:=1;
  e:=2;
  mm:=1;
  ss:=1;
  slot[f].x:=fx[s];
  slot[f].y:=fy[s];
  dis[s,fx[s],fy[s]]:=0;
  fillchar(vis,sizeof(vis),false);
  vis[fx[s],fy[s]]:=true;
  repeat
    for i:=1 to 4 do
    begin
      tx:=slot[f].x+dx[i];
      ty:=slot[f].y+dy[i];
      if not map[tx,ty] or vis[tx,ty] then
        continue;
      slot[e].x:=tx;
      slot[e].y:=ty;
      vis[tx,ty]:=true;
      dis[s,tx,ty]:=ss;
      inc(e);
    end;
    inc(f);
    if f>mm then
    begin
      mm:=e-1;
      inc(ss);
    end;
  until f=e;
end;
//**
begin
  for i:=1 to r do
    getdis(i);
  slot[1].x:=sx;
  slot[1].y:=sy;
  for f:=1 to 60 do
  begin
    best:=100;
    bests:=10000;
    search(1);
    if best=100 then
      break;
    slot[f+1].x:=bx;
    slot[f+1].y:=by;
    if best=0 then
    begin
      writeln(f);
      print(2,1);
    end;
  end;
  writeln(-1);
end;
//
begin
  assign(input,'p6.in');
  assign(output,'p6.out');
  reset(input);
  rewrite(output);
  readln(m,n);
  for i:=1 to n do
  begin
    for j:=1 to m do
    begin
      read(t);
      map[i,j]:=t=0;
    end;
    readln;
  end;
  readln(r);
  for i:=1 to r do
    readln(sx[i],sy[i],fx[i],fy[i]);
  if r=1 then
    solve1;
  if r=2 then
    solve2;
  if r>2 then
    solve;
  close(output);
end.
