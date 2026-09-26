program p1;
type
  trie=^node;
  node=
  record
    now:integer;
    next:array[#1..#127]of trie;
  end;
var
  ch:char;
  st:string;
  n,i,now,d1,d2:integer;
  root,t:trie;
  path,re:array[1..255]of char;
//
procedure build (s:integer;p:trie);
var
  i:integer;
begin
  if s>length(st) then
    exit;
  if p^.next[st[s]]=nil then
  begin
    new(t);
    t^.now:=now;
    for i:=1 to 127 do
      t^.next[chr(i)]:=nil;
    p^.next[st[s]]:=t;
  end;
  build(s+1,p^.next[st[s]]);
end;
//
procedure insert (s:integer;p:trie);
begin
  if s>length(st) then
    exit;
  if p^.next[st[s]]=nil then
    exit;
  if p^.next[st[s]]^.now<>now-1 then
    exit;
  p^.next[st[s]]^.now:=now;
  insert(s+1,p^.next[st[s]]);
end;
//
procedure search (p:trie);
var
  i:integer;
begin
  if d1>d2 then
  begin
    d2:=d1;
    re:=path;
  end;
  for i:=1 to 127 do
  begin
    if p^.next[chr(i)]=nil then
      continue;
    if p^.next[chr(i)]^.now<>n then
      continue;
    inc(d1);
    path[d1]:=chr(i);
    search(p^.next[chr(i)]);
    dec(d1);
  end;
end;
//
begin
  readln(n);
  readln(st);
  new(root);
  root^.now:=0;
  for i:=1 to 127 do
    root^.next[chr(i)]:=nil;
  now:=1;
  for i:=1 to length(st) do
    build(i,root);
  for now:=2 to n do
  begin
    readln(st);
    for i:=1 to length(st) do
      insert(i,root);
  end;
  d1:=0;
  d2:=0;
  search(root);
  for i:=1 to d2 do
    write(re[i]);
  writeln;
  readln;
end.
