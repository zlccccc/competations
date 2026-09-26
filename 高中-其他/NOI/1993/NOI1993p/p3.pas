program p3;
type
  high=array[0..255]of integer;
var
  i,f:integer;
  ch:char;
  a,b,c:high;
//
function less (e:integer):boolean;
var
  i:integer;
begin
  while a[f]=0 do
    inc(f);
  if e-f+1>b[0] then
    exit(true);
  if e-f+1<b[0] then
    exit(false);
  i:=1;
  while a[f+i-1]=b[i] do
    inc(i);
  if a[f+i-1]>=b[i] then
    exit(true)
  else
    exit(false);
end;
//
procedure min (e:integer);
var
  x,i,j:integer;
begin
  i:=e;
  j:=b[0];
  x:=0;
  while (i>=1) and (j>=1) do
  begin
    x:=a[i]-b[j]+8+x;
    a[i]:=x mod 8;
    x:=x div 8-1;
    dec(i);
    dec(j);
  end;
  if x<>0 then
    dec(a[i]);
end;
//
procedure print (var v:high);
var
  i:integer;
begin
  i:=1;
  while (i<=v[0]) and (v[i]=0) do
    inc(i);
  if i>v[0] then
    write(0);
  while i<=v[0] do
  begin
    write(v[i]);
    inc(i);
  end;
  writeln;
end;
//
begin
  repeat
    read(ch);
    inc(a[0]);
    a[a[0]]:=ord(ch)-48;
  until eoln;
  readln;
  repeat
    read(ch);
    inc(b[0]);
    b[b[0]]:=ord(ch)-48;
  until eoln;
  readln;
  c[0]:=a[0];
  f:=1;
  for i:=b[0] to a[0] do
  begin
    while less(i) do
    begin
      inc(c[i]);
      min(i);
    end;
  end;
  print(c);
  print(a);
  readln;
end.
