program p3;
var
  path:array[1..100]of integer;
  n,i,j,maxdep,from,lna,lnb,mina,minb,min:integer;
  filename:string;
  la,lb:array[1..20]of integer;
  a,b:array[1..20,1..20]of char;
  sa,sb:array[1..400]of char;
//
function DFS (dep:integer):boolean;
var
  i,t:integer;
  found:boolean;
begin
  if (lna>100) or (lnb>100) then
    exit(false);
  if dep>maxdep then
    exit(true);
  found:=false;
  for i:=1 to n do
  begin
    path[dep]:=i;
    move(a[i],sa[lna+1],la[i]);
    move(b[i],sb[lnb+1],lb[i]);
    inc(lna,la[i]);
    inc(lnb,lb[i]);
    t:=from;
    while (from<=lna) and (from<=lnb) and (sa[from]=sb[from]) do
      inc(from);
    if (from>lna) and (from>lnb) then
    begin
      for i:=1 to dep do
        writeln(path[i]);
      close(output);
      halt;
    end;
    if (from>lna) or (from>lnb) then
      if DFS(dep+1) then
        found:=true;
    from:=t;
    dec(lna,la[i]);
    dec(lnb,lb[i]);
  end;
  exit(found);
end;
//
begin
  readln(filename);
  assign(input,filename);
  assign(output,'output.txt');
  reset(input);
  rewrite(output);
  readln(n);
  mina:=100;
  minb:=100;
  for i:=1 to n do
  begin
    j:=0;
    repeat
      inc(j);
      read(a[i,j]);
    until eoln;
    la[i]:=j;
    if j<mina then
      mina:=j;
    readln;
  end;
  for i:=1 to n do
  begin
    j:=0;
    repeat
      inc(j);
      read(b[i,j]);
    until eoln;
    lb[i]:=j;
    if j<minb then
      minb:=j;
    readln;
  end;
  if mina<minb then
    min:=minb
  else
    min:=mina;
  min:=100 div min;
  from:=1;
  maxdep:=1;
  while (maxdep<=min) and DFS(1) do
    inc(maxdep);
  writeln('No Answer');
  close(output);
end.
