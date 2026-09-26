program p4;
const
  oo=500;
var
  change:boolean;
  t:char;
  n,i,j:integer;
  map:array[1..100,1..100]of integer;
  d,pre,path:array[1..100]of integer;
begin
  assign(input,'p4.in');
  reset(input);
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(t);
      if t='1' then
        map[i,j]:=-1
      else
        map[i,j]:=oo;
    end;
    readln;
  end;
  repeat
    change:=false;
    for i:=1 to n do
      for j:=1 to n do
        if d[i]+map[i,j]<d[j] then
        begin
          change:=true;
          d[j]:=d[i]+map[i,j];
          pre[j]:=i;
        end;
  until not change;
  i:=n;
  j:=0;
  while i<>1 do
  begin
    inc(j);
    path[j]:=i;
    i:=pre[i];
  end;
  inc(j);
  path[j]:=1;
  for i:=j downto 1 do
    write(path[i],' ');
  writeln;
  assign(input,'');
  reset(input);
  readln;
end.
