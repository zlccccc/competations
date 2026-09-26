program p5;
const
  dx:array[1..4]of integer=(-1,0,1,0);
  dy:array[1..4]of integer=(0,1,0,-1);
var
  n,i,j,k,tot,num:integer;
  mp:array[0..61,0..61]of integer;
  vis:array[0..61,0..61]of boolean;
//
procedure fill (x,y:integer);
var
  i:integer;
begin
  if vis[x,y] then
    exit;
  vis[x,y]:=true;
  inc(num);
  for i:=1 to 4 do
    if mp[x+dx[i],y+dy[i]]=mp[x,y] then
      fill(x+dx[i],y+dy[i]);
end;
//
begin
  assign(input,'p5.in');
  reset(input);
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to n do
      read(mp[i,j]);
    readln;
  end;
  for i:=0 to n+1 do
  begin
    vis[0,i]:=true;
    vis[n+1,i]:=true;
    vis[i,0]:=true;
    vis[i,n+1]:=true;
  end;
  for i:=1 to n do
    for j:=1 to n do
      if mp[i,j]=0 then
      begin
        vis[i,j]:=true;
        for k:=1 to 4 do
          vis[i+dx[k],j+dy[k]]:=true;
      end;
  tot:=0;
  for i:=1 to n do
    for j:=1 to n do
      if not vis[i,j] then
      begin
        inc(tot);
        num:=0;
        fill(i,j);
        writeln(tot,':',num);
      end;
  writeln(tot);
  assign(input,'');
  reset(input);
  readln;
end.
