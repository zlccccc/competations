program p4;
var
  m,n,r1,r2,i,p:integer;
  path:array[1..50]of integer;
//
procedure DFS (dep,from:integer);
var
  i:integer;
begin
  if dep>r2 then
  begin
    inc(p);
    write(p,':');
    for i:=1 to r2 do
      write(path[i],' ');
    writeln;
    exit;
  end;
  for i:=from to r1-r2+dep do
  begin
    path[dep]:=i;
    DFS(dep+1,i+1);
  end;
end;
//
begin
  readln(m,n);
  r1:=1;
  for i:=1 to m do
    r1:=r1*i;
  for i:=1 to n-1 do
    r1:=r1 div i;
  for i:=1 to m-n+1 do
    r1:=r1 div i;
  r2:=r1*(m-n+1) div m;
  writeln(r1,' ',r2);
  p:=0;
  DFS(1,1);
  readln;
end.
