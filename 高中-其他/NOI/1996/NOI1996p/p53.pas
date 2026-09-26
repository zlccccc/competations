program p53;
const
  dx:array[1..4]of smallint=(-1,0,1,0);
  dy:array[1..4]of smallint=(0,1,0,-1);
type
  timetype=
  record
    ID,t:smallint;
  end;
  col=
  record
    x,y:smallint;
  end;
  listtype=
  record
    oj,ren:smallint;
  end;
var
  c1,c2,c3:char;
  n,m,i,j,p,a,b,upn,pkn:smallint;
  f1,f2,f3:string;
  map:array[1..10,1..10]of smallint;
  time:array[1..60]of timetype;
  need:array[1..60]of smallint;
  sw:timetype;
  pl,ari,lev:array[1..50]of smallint;
  eff:array[1..50,0..50]of smallint;
  up,pk:array[1..99]of col;
  cov:array[1..99]of smallint;
  vis:array[1..10,1..10]of boolean;
  next:boolean;
//
procedure search (dep:smallint);
var
  i,j,ln:smallint;
  reach:array[1..99]of boolean;
  list:array[1..99]of listtype;
  sw:listtype;
//**
procedure fill (x,y:smallint);
var
  tx,ty,i:smallint;
begin
  if vis[x,y] then
    exit;
  vis[x,y]:=true;
  if map[x,y]<100 then
    reach[map[x,y]]:=true;
  for i:=1 to 4 do
  begin
    tx:=x+dx[i];
    ty:=y+dy[i];
    if (tx<1) or (tx>m) or (ty<1) or (ty>n) then
      continue;
    if map[tx,ty]=102 then
      continue;
    if (map[tx,ty]<100) and (cov[map[tx,ty]]<>0) then
      continue;
    fill(tx,ty);
  end;
end;
//**
function can (x,y:smallint):boolean;
var
  tx,ty,i:smallint;
begin
  if vis[x,y] then
    exit(false);
  vis[x,y]:=true;
  if map[x,y]=100 then
    exit(true);
  for i:=1 to 4 do
  begin
    tx:=x+dx[i];
    ty:=y+dy[i];
    if (tx<1) or (tx>m) or (ty<1) or (ty>n) then
      continue;
    if map[tx,ty]=102 then
      continue;
    if (map[tx,ty]<100) and (cov[map[tx,ty]]<>0) and (lev[cov[map[tx,ty]]]>lev[eff[time[dep].ID,j]]) then
      continue;
    if can(tx,ty) then
      exit(true);
  end;
  exit(false);
end;
//**
begin
  if dep>p*2 then
  begin
    for i:=1 to 50 do
      if pl[i]<>0 then
        writeln(i,'  ',pl[i]);
    close(output);
    halt;
  end;
  if time[dep].ID<0 then
  begin
    cov[pl[-time[dep].ID]]:=0;
    search(dep+1);
    cov[pl[-time[dep].ID]]:=-time[dep].ID;
    exit;
  end;
  fillchar(reach,sizeof(reach),false);
  fillchar(vis,sizeof(vis),false);
  for i:=1 to upn do
    fill(up[i].x,up[i].y);
  ln:=0;
  for i:=1 to pkn do
    if reach[i] then
    begin
      inc(ln);
      list[ln].oj:=i;
    end;
  for i:=1 to ln do
  begin
    list[i].ren:=0;
    cov[list[i].oj]:=1;
    fillchar(reach,sizeof(reach),false);
    fillchar(vis,sizeof(vis),false);
    for j:=1 to upn do
      fill(up[j].x,up[j].y);
    for j:=1 to pkn do
      if reach[j] then
        inc(list[i].ren);
    cov[list[i].oj]:=0;
  end;
  for i:=1 to ln-1 do
    for j:=i+1 to ln do
      if list[i].ren<list[j].ren then
      begin
        sw:=list[i];
        list[i]:=list[j];
        list[j]:=sw;
      end;
  for i:=1 to ln do
  begin
    if list[i].ren<need[dep] then
      break;
    cov[list[i].oj]:=time[dep].ID;
    pl[time[dep].ID]:=list[i].oj;
    next:=true;
    for j:=1 to eff[time[dep].ID,0] do
    begin
      fillchar(vis,sizeof(vis),false);
      if not can(pk[pl[eff[time[dep].ID,j]]].x,pk[pl[eff[time[dep].ID,j]]].y) then
      begin
        next:=false;
        break;
      end;
    end;
    if next then
      search(dep+1);
    cov[list[i].oj]:=0;
  end;
end;
//
begin
  readln(f1);
  readln(f2);
  readln(f3);
  assign(input,f1);
  reset(input);
  readln(m,n);
  pkn:=0;
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(c1,c2);
      case c1 of
        '*':
        begin
          map[i,j]:=100;
          inc(upn);
          up[upn].x:=i;
          up[upn].y:=j;
        end;
        '&':
          map[i,j]:=101;
        '#':
          map[i,j]:=102;
        else
        begin
          val(c1+c2,map[i,j]);
          pk[map[i,j]].x:=i;
          pk[map[i,j]].y:=j;
          if map[i,j]>pkn then
            pkn:=map[i,j];
        end;
      end;
      if j<n then
        read(c3,c3);
    end;
    readln;
  end;
  assign(input,f2);
  reset(input);
  readln(p);
  for i:=1 to p do
  begin
    read(time[i*2].ID);
    time[i*2-1].ID:=-time[i*2].ID;
    for j:=1 to 2 do
    begin
      read(c1,c1,c2,c3);
      val(c2+c3,a);
      read(c1,c2,c3);
      val(c2+c3,b);
      time[i*2-j+1].t:=a*60+b;
    end;
    readln;
  end;
  for i:=1 to p*2-1 do
    for j:=i+1 to p*2 do
      if time[i].t>time[j].t then
      begin
        sw:=time[i];
        time[i]:=time[j];
        time[j]:=sw;
      end;
  for i:=1 to p*2 do
    if time[i].ID<0 then
    begin
      j:=i-1;
      while (j>=1) and (time[j].ID<>-time[i].ID) do
        dec(j);
      ari[-time[i].ID]:=j;
      lev[-time[i].ID]:=i;
    end;
  for i:=1 to p*2 do
    if time[i].ID>0 then
      for j:=i+1 to lev[time[i].ID]-1 do
        if (time[j].ID<0) and (ari[-time[j].ID]<i) then
        begin
          inc(eff[time[i].ID,0]);
          eff[time[i].ID,eff[time[i].ID,0]]:=-time[j].ID;
        end;
  for i:=1 to p*2 do
  begin
    j:=0;
    while (i+j<=p*2) and (time[i+j].ID>0) do
      inc(j);
    need[i]:=j-1;
  end;
  fillchar(cov,sizeof(cov),0);
  fillchar(pl,sizeof(pl),0);
  assign(output,f3);
  rewrite(output);
  search(1);
  writeln('NO ANSWER!');
  close(output);
end.
