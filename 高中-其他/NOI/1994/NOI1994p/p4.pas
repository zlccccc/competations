program p4;
var
  s,i,j,t:integer;
  path:array[1..255]of integer;
  st:string;
begin
  readln(st);
  st:=st+#1;
  readln(s);
  for i:=1 to s do
  begin
    j:=1;
    while st[j+1]>=st[j] do
      inc(j);
    path[i]:=j;
    delete(st,j,1);
  end;
  for i:=1 to s do
  begin
    t:=path[i];
    for j:=1 to i-1 do
      if path[j]<=path[i] then
        inc(t);
    write(t,' ');
  end;
  writeln;
  delete(st,length(st),1);
  writeln(st);
  readln;
end.
