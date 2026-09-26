program p5;
var
  k,m,n,t:integer;
begin
  readln(k);
  m:=1;
  n:=1;
  while (m+n<=k) do
  begin
    t:=n;
    n:=m+n;
    m:=t;
  end;
  writeln(m);
  writeln(n);
  readln;
end.
