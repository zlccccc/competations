program p2;
var
  sum:array[0..200]of integer;
  s:array[1..200]of integer;
  n,i,j,min,max,mi:integer;
  dp,pre:array[1..100,1..100]of integer;
  filename:string;
//
procedure print (f,l:integer);
var
  i:integer;
begin
  if l=1 then
    exit;
  if pre[f,l]=1 then
  begin
    print(f,l-1);
    for i:=f+l to f+n-1 do
      write(s[i],' ');
    writeln(-s[f+l-1],' ',sum[f-1]-sum[f+l-2]);
  end
  else
  begin
    print(f+1,l-1);
    for i:=f+l to f+n-1 do
      write(s[i],' ');
    writeln(-s[f],' ',sum[f]-sum[f+l-1]);
  end;
end;
//
begin
  readln(filename);
  assign(input,filename);
  reset(input);
  assign(output,'output.txt');
  rewrite(output);
  readln(n);
  for i:=1 to n do
    read(s[i]);
  readln;
  move(s[1],s[n+1],n*4);
  sum[0]:=0;
  for i:=1 to 2*n do
    sum[i]:=sum[i-1]+s[i];
  for j:=2 to n do
    for i:=1 to n do
    begin
      if dp[i,j-1]>dp[i mod n+1,j-1] then
      begin
        dp[i,j]:=dp[i mod n+1,j-1];
        pre[i,j]:=2;
      end
      else
      begin
        dp[i,j]:=dp[i,j-1];
        pre[i,j]:=1;
      end;
      dp[i,j]:=dp[i,j]+sum[i+j-1]-sum[i-1];
    end;
  min:=10000;
  for i:=1 to n do
    if dp[i,n]<min then
    begin
      min:=dp[i,n];
      mi:=i;
    end;
  print(mi,n);
  writeln(sum[n]);
  writeln;
  for j:=2 to n do
    for i:=1 to n do
    begin
      if dp[i,j-1]<dp[i mod n+1,j-1] then
      begin
        dp[i,j]:=dp[i mod n+1,j-1];
        pre[i,j]:=2;
      end
      else
      begin
        dp[i,j]:=dp[i,j-1];
        pre[i,j]:=1;
      end;
      dp[i,j]:=dp[i,j]+sum[i+j-1]-sum[i-1];
    end;
  max:=0;
  for i:=1 to n do
    if dp[i,n]>max then
    begin
      max:=dp[i,n];
      mi:=i;
    end;
  print(mi,n);
  writeln(sum[n]);
  close(output);
end.
