program p3;
var
  d,a1,an,a2,am:real;
  n,m,x1,x2,x3:integer;
//
procedure DFS (x,s:integer);
begin
  if s=1 then
  begin
    inc(x1,x);
    exit;
  end;
  if s=2 then
  begin
    inc(x2,x);
    exit;
  end;
  DFS(-2*x,s-1);
  DFS(x,s-2);
  inc(x3,x*2);
end;
//
begin
  readln(n,d,a1,an,m);
  x1:=0;
  x2:=0;
  x3:=0;
  DFS(1,n);
  a2:=(an-x3*d-x1*a1)/x2;
  x1:=0;
  x2:=0;
  x3:=0;
  DFS(1,m);
  am:=x1*a1+x2*a2+x3*d;
  writeln(am:0:2);
  readln;
end.
