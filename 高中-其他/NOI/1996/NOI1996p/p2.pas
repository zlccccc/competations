program p2;
var
  n,m,i,j,k,x,y,s,ef,h:word;
  filename:string;
  a:array[1..50,1..50]of byte;
  chart:array[1..1275,0..50]of byte;
  tick:array[1..1275]of boolean;
begin
  readln(filename);
  assign(input,filename);
  reset(input);
  readln(n);
  a[1,1]:=1;
  for i:=2 to n do
  begin
    a[i,1]:=1;
    for j:=2 to i-1 do
      a[i,j]:=a[i-1,j-1] xor a[i-1,j];
    a[i,i]:=1;
  end;
  m:=0;
  fillchar(chart,sizeof(chart),0);
  while not eof do
  begin
    readln(x,y,s);
    inc(m);
    chart[m,0]:=s;
    for i:=y to n-x+y do
      chart[m,i]:=a[n-x+1,i-y+1];
  end;
  assign(input,'');
  reset(input);
  ef:=0;
  for k:=1 to n do
  begin
    h:=1;
    while (h<=m) and not (not tick[h] and (chart[h,k]=1)) do
      inc(h);
    if h>m then
      continue;
    tick[h]:=true;
    inc(ef);
    for i:=1 to m do
      if not tick[i] and (chart[i,k]=1) then
      begin
        for j:=k to n do
          chart[i,j]:=chart[i,j] xor chart[h,j];
        chart[i,0]:=chart[i,0] xor chart[h,0];
      end;
  end;
  for i:=1 to m do
    if chart[i,0]=1 then
    begin
      j:=1;
      while (j<=n) and (chart[i,j]=0) do
        inc(j);
      if j>n then
      begin
        writeln('No Answer!');
        readln;
        halt;
      end;
    end;
  writeln(1 shl (n-ef));
  readln;
  halt;
end.
