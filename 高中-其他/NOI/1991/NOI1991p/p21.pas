program p21;
var
  n,m,s,oj,i,j:byte;
  food:array[1..10]of byte;
  return:array[1..10]of byte;
begin
  readln(n,m);
  food[1]:=m;
  return[1]:=n*2;
  oj:=2*n;
  i:=1;
  while oj>food[i] do
  begin
    s:=oj-food[i];
    inc(i);
    oj:=3*s;
    food[i]:=m;
    return[i]:=s*2;
  end;
  food[i]:=oj;
  writeln(i);
  for j:=1 to i do
    writeln(j,' ',food[j],' ',return[j]);
  readln;
end.
