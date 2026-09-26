program p2;
type
  high=array[0..300]of integer;
const
  m=8;
var
  dot,i,f:integer;
  s1,s2:string;
  a,b,c:high;
//
function zero (e:integer):boolean;
var
  i:integer;
begin
  i:=f;
  while (i<=e) and (a[i]=0) do
    inc(i);
  if i>e then
    exit(true)
  else
    exit(false);
end;
//
function more (e:integer):boolean;
var
  i:integer;
begin
  if e-f+1=b[0] then
  begin
    i:=f;
    while (i<=e) and (a[i]=b[i-f+1]) do
      inc(i);
    if (i>e) or (a[i]>b[i-f+1]) then
      exit(true)
    else
      exit(false);
  end
  else
    if e-f+1>b[0] then
      exit(true)
    else
      exit(false);
end;
//
procedure mus (e:integer);
var
  x,i,j:integer;
begin
  i:=e;
  j:=b[0];
  x:=0;
  while (i>=f) and (j>=1) do
  begin
    x:=a[i]+10-b[j]+x;
    a[i]:=x mod 10;
    x:=x div 10-1;
    dec(j);
    dec(i);
  end;
  if x<>0 then
    dec(a[i]);
  while (f<=e) and (a[f]=0) do
    inc(f);
end;
//
begin
  readln(s1);
  readln(s2);
  for i:=1 to length(s1) do
    if s1[i]='.' then
      dot:=i
    else
    begin
      inc(a[0]);
      a[a[0]]:=ord(s1[i])-ord('0');
    end;
  if dot=0 then
    dot:=a[0]+1;
  for i:=1 to length(s2) do
    if s2[i]='.' then
      dot:=dot+length(s2)-i
    else
    begin
      inc(b[0]);
      b[b[0]]:=ord(s2[i])-ord('0');
    end;
  i:=1;
  f:=1;
  while (i<=a[0]+m) and not zero(i) do
  begin
    while more(i) do
    begin
      inc(c[i]);
      mus(i);
    end;
    inc(i);
  end;
  c[0]:=i-1;
  i:=1;
  while (i<dot-1) and (c[i]=0) do
    inc(i);
  while i<=c[0] do
  begin
    if i=dot then
      write('.');
    write(c[i]);
    inc(i);
  end;
  while i<=a[0] do
  begin
    write(0);
    inc(i);
  end;
  readln;
end.
