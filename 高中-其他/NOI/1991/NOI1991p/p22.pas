program p22;
const
  oo=10000;
type
  one=
  record
    c,s,ID:integer;
  end;
  pathtype=
  record
    car,ID,ret:integer;
  end;
var
  n,p,i,j,cost,day,rc1,rc2,rn1,rn2:integer;
  hum:array[1..10]of one;
  sw:one;
  r1,r2,path:array[1..10]of pathtype;
  left:array[0..10]of integer;
  tick:array[1..10]of boolean;
//
procedure DFS (dep,from:integer);
var
  best:one;
  i,j,tday:integer;
  first:boolean;
begin
  if dep>p+1 then
    exit;
  if day=0 then
  begin
    dec(path[dep-1].car,left[0]);
    if cost<rc2 then
    begin
      rc2:=cost;
      rn2:=dep-1;
      r2:=path;
    end;
    if (dep-1<rn1) or (dep-1=rn1) and (cost<rc1) then
    begin
      rn1:=dep-1;
      rc1:=cost;
      r1:=path;
    end;
    exit;
  end;
  first:=true;
  for i:=from to p do
    if not tick[i] and (hum[i].s*(day+1)<=hum[i].c) then
    begin
      if first then
      begin
        first:=true;
        best.c:=hum[i].c;
        best.s:=hum[i].s;
      end
      else
        if (hum[i].c<=best.c) and (hum[i].s>=best.s) then
          exit;
      tick[i]:=true;
      path[dep].car:=hum[i].c;
      path[dep].ID:=hum[i].ID;
      path[dep].ret:=day;
      inc(cost,hum[i].c);
      left[day]:=left[day]+hum[i].c-hum[i].s*day;
      tday:=day;
      for j:=1 to day do
        dec(left[j],hum[i].s);
      while (day>0) and (left[day]>=0) do
      begin
        inc(left[day-1],left[day]);
        dec(day);
      end;
      DFS(dep+1,i+1);
      while (day<tday) do
      begin
        inc(day);
        dec(left[day],left[day+1]);
      end;
      for j:=1 to day do
        inc(left[j],hum[i].s);
      left[day]:=left[day]-hum[i].c+hum[i].s*day;
      dec(cost,hum[i].c);
      tick[i]:=false;
    end;
end;
//
begin
  readln(n,p);
  for i:=1 to p do
  begin
    hum[i].ID:=i;
    readln(hum[i].c,hum[i].s);
  end;
  for i:=1 to p-1 do
    for j:=i+1 to p do
      if (hum[i].c<hum[j].c) or (hum[i].c=hum[j].c) and (hum[i].s>hum[j].s) then
      begin
        sw:=hum[i];
        hum[i]:=hum[j];
        hum[j]:=sw;
      end;
  day:=n;
  rc2:=oo;
  rn2:=oo;
  rn1:=oo;
  DFS(1,1);
  if rn1=oo then
  begin
    writeln('No solution.');
    readln;
    halt;
  end;
  writeln(rn1);
  writeln(rc1);
  for i:=1 to rn1 do
    writeln(r1[i].ID,' ',r1[i].car,' ',r1[i].ret);
  writeln;
  writeln(rn2);
  writeln(rc2);
  for i:=1 to rn2 do
    writeln(r2[i].ID,' ',r2[i].car,' ',r2[i].ret);
  writeln;
  readln;
end.
