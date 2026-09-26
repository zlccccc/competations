program p1;
var
  tot,m:integer;
  num:array['a'..'z']of integer;
  ch:char;
  path:array[1..100]of char;
//
procedure DFS (dep:integer);
var
  c:char;
  i:integer;
begin
  if dep>m then
  begin
    for i:=1 to m do
      write(path[i]);
    writeln;
    inc(tot);
  end
  else
    for c:='a' to 'z' do
      if num[c]>0 then
      begin
        dec(num[c]);
        path[dep]:=c;
        DFS(dep+1);
        inc(num[c]);
      end;
end;
//
begin
  repeat
    read(ch);
    inc(num[ch]);
  until eoln;
  readln;
  readln(m);
  DFS(1);
  writeln(tot);
  readln;
end.
