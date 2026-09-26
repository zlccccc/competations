program p51;
const
  m=4;
  n=5;
  map:array[1..m,1..n]of smallint=
  (
    (1,101,100,101,2),
    (3,4,101,5,6),
    (7,8,101,102,9),
    (10,11,101,101,12)
  );
  dx:array[1..4]of smallint=(-1,0,1,0);
  dy:array[1..4]of smallint=(0,1,0,-1);
type
  timetype=
  record
    ID:smallint;
    t:word;
  end;
var
  c1,c2,c3:char;
  p,i,j,k,a,b:word;
  f1,f2,st:string;
  vis:array[1..10,1..10]of boolean;
  cov,reach:array[1..99]of boolean;
  pl:array[1..50]of smallint;
  time:array[1..60]of timetype;
  sw:timetype;
//
procedure fill (x,y:smallint);
var
  i,tx,ty:smallint;
begin
  if vis[x,y] then
    exit;
  if map[x,y]<100 then
    reach[map[x,y]]:=true;
  vis[x,y]:=true;
  if cov[map[x,y]] then
    exit;
  for i:=1 to 4 do
  begin
    tx:=x+dx[i];
    ty:=y+dy[i];
    if (tx<1) or (tx>m) or (ty<1) or (ty>n) then
      continue;
    if map[tx,ty]=102 then
      continue;
    fill(tx,ty);
  end;
end;
//
begin
  readln(f1);
  readln(f2);
  assign(input,f1);
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
  assign(input,f2);
  reset(input);
  for i:=1 to p do
    readln(a,pl[a]);
  assign(input,'');
  reset(input);
  fillchar(cov,sizeof(cov),false);
  for k:=1 to p*2 do
  begin
    fillchar(reach,sizeof(reach),false);
    fillchar(vis,sizeof(vis),false);
    for i:=1 to m do
      for j:=1 to n do
        if map[i,j]=100 then
          fill(i,j);
    if not reach[pl[abs(time[k].ID)]] then
    begin
      writeln('Wrong!');
      readln;
      halt;
    end;
    if time[k].ID>0 then
      cov[pl[time[k].ID]]:=true
    else
      cov[pl[-time[k].ID]]:=false;
  end;
  writeln('Right!');
  readln;
end.
