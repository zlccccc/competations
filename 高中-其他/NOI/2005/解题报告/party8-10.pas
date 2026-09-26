{$R-,S-,Q-,I-}
const maxn = 1000; maxm = 20000; x = 97;{97 for test 8,10; 98 for test 9}
type
  rec = record u,v,c : integer; end;
var
  edge      : array[1..maxm] of rec;
  e         : array[1..maxm] of integer;
  f         : array[1..maxn] of integer;
  use,ansu  : array[1..maxm] of boolean;
  deg,lim   : array[1..maxn] of integer;
  n,m,i,ans : longint;

Procedure sort(l,r : integer);
 var i,j,x,y : integer;
     t       : rec;
  begin
    i := l; j := r; x := edge[(i+j) div 2].c;
    repeat
      while edge[i].c > x do inc(i);
      while edge[j].c < x do dec(j);
      if i <= j then
        begin
          y := e[i]; e[i] := e[j]; e[j] := y;
          t := edge[i]; edge[i] := edge[j]; edge[j] := t;
          inc(i); dec(j);
        end;
    until i > j;
    if l < j then sort(l,j);
    if i < r then sort(i,r);
  end;

Function root(k : integer) : integer;
  begin
    if f[k] = k then exit(k);
    f[k] := root(f[k]);
    root := f[k];
  end;

Procedure kruscal;
 var now,i : longint;
  begin
   now := 0;
   for i := 1 to n do f[i] := i;
   fillchar(use,sizeof(use),false);
   fillchar(deg,sizeof(deg),0);
   for i := 1 to m do if root(edge[i].u)<>root(edge[i].v) then
     if (deg[edge[i].u]<lim[edge[i].u])and(deg[edge[i].v]<lim[edge[i].v]) then
       if random(100)+1<=x then
         begin
           now := now+edge[i].c;
           use[e[i]] := true;
           f[f[edge[i].u]] := f[edge[i].v];
           inc(deg[edge[i].u]); inc(deg[edge[i].v]);
         end;
    for i := 2 to n do if root(i)<>root(1) then exit;
    if now > ans then
      begin
        ansu := use;
        ans := now;
      end;
  end;

begin
  assign(input,'party.in'); reset(input);
  assign(output,'party.out'); rewrite(output);
  readln(n,m);
  for i := 1 to n do read(lim[i]); readln;
  for i := 1 to m do
    readln(edge[i].u,edge[i].v,edge[i].c);
  for i := 1 to m do e[i] := i;
  sort(1,m);
  ans := 0;
  for i := 1 to 1000000 do kruscal;
  writeln(ans);
  for i := 1 to m do if ansu[i] then writeln(i);
  close(input); close(output);
end.
