program p5;
var
  c:char;
  n,i,j,s,t:integer;
  map:array[1..100,1..100]of boolean;
  vis:array[1..100]of boolean;
//
procedure fill (s:integer);
var
  i:integer;
begin
  if vis[s] then
    exit;
  vis[s]:=true;
  for i:=1 to n do
    if map[s,i] then
      fill(i);
end;
//
begin
  assign(input,'p5.in');
  reset(input);
  readln(n);
  for i:=1 to n do
  begin
    for j:=1 to n do
    begin
      read(c);
      if c='1' then
        map[i,j]:=true
      else
        map[i,j]:=false;
    end;
    readln;
  end;
  readln(s);
  for t:=1 to n do
  begin
    write(t,':');
    for i:=1 to n do
    begin
      fillchar(vis,sizeof(vis),false);
      vis[i]:=true;
      fill(s);
      if not vis[t] then
        write(i,' ');
      vis[i]:=false;
    end;
    write(t);
    writeln;
  end;
  assign(input,'');
  reset(input);
  readln;
end.
