program p4;
type
  high=array[0..50]of word;
var
  tmp,t,re:high;
  m,i,j,k:word;
  dp:array[1..200,0..20]of high;
  filename,num,st:string;
//
function cov (f,e:word):high;
var
  i,j:word;
begin
  i:=e;
  j:=1;
  while (i>=f+4) do
  begin
    val(copy(num,i-3,4),cov[j]);
    inc(j);
    dec(i,4);
  end;
  val(copy(num,f,i-f+1),cov[j]);
  cov[0]:=j;
end;
//
function add (var a,b:high):high;
var
  i,x:word;
begin
  i:=1;
  x:=0;
  while (i<=a[0]) and (i<=b[0]) do
  begin
    x:=a[i]+b[i]+x;
    add[i]:=x mod 10000;
    x:=x div 10000;
    inc(i);
  end;
  while (i<=a[0]) do
  begin
    x:=a[i]+x;
    add[i]:=x mod 10000;
    x:=x div 10000;
    inc(i);
  end;
  while (i<=b[0]) do
  begin
    x:=b[i]+x;
    add[i]:=x mod 10000;
    x:=x div 10000;
    inc(i);
  end;
  if x=0 then
    add[0]:=i-1
  else
  begin
    add[i]:=x;
    add[0]:=i;
  end;
end;
//
function less (var a,b:high):boolean;
var
  i:integer;
begin
  if a[0]<b[0] then
    exit(true);
  if a[0]>b[0] then
    exit(false);
  i:=a[0];
  while (i>=1) and (a[i]=b[i]) do
    dec(i);
  if i<1 then
    exit(false);
  if a[i]<b[i] then
    exit(true)
  else
    exit(false);
end;
//
begin
  readln(filename);
  assign(input,filename);
  reset(input);
  readln(num);
  readln(m);
  for i:=1 to length(num) do
    dp[i,0]:=cov(i,length(num));
  for j:=1 to m do
    for i:=1 to length(num)-j do
    begin
      dp[i,j,0]:=100;
      for k:=i+1 to length(num)-j+1 do
      begin
        t:=cov(i,k-1);
        tmp:=add(dp[k,j-1],t);
        if less(tmp,dp[i,j]) then
          dp[i,j]:=tmp;
      end;
    end;
  re:=dp[1,m];
  write(re[re[0]]);
  for i:=re[0]-1 downto 1 do
  begin
    str(re[i],st);
    while length(st)<4 do
      st:='0'+st;
    write(st);
  end;
  writeln;
  assign(input,'');
  reset(input);
  readln;
end.
