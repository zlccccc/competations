{$R-,S-,Q-,I-}
const maxn = 100; x = 89;{x% to survive}
var
  e,g,graph,ansgraph  : array[1..maxn,1..maxn] of longint;
  use                 : array[1..maxn,1..maxn] of boolean;
  lim,d,p,deg         : array[1..maxn] of longint;
  visit               : array[1..maxn] of boolean;
  n,m,i,j,a,b,ans,tot : longint;
  start : double;

Procedure try(a,b : longint; var k : longint);
 var flag : boolean;
     min  : longint;
     x,y  : longint;

  Procedure dfs(last,k : longint; var min,x,y : longint);
   var i,a,b,tmp : longint;
    begin
      if visit[k] then
        begin
          flag := true;
          exit;
        end;
      visit[k] := true;
      for i := 1 to n do if i<>last then if graph[i,k] = 1 then
        begin
          a := x; b := y; tmp := min;
          if g[i,k] < min then
            begin min := g[i,k]; x := i; y := k; end;
          dfs(k,i,min,x,y);
          if flag then exit;
          x := a; y := b; min := tmp;
        end;
    end;

  begin
    fillchar(visit,sizeof(visit),false);
    graph[a,b] := 1;
    graph[b,a] := 1;
    min := g[a,b]; x := a; y := b;
    flag := false;
    dfs(0,a,min,x,y);
    inc(deg[a]); inc(deg[b]);
    if min < g[a,b] then
      begin
        k := 1;
        tot := tot+g[a,b]-min;
        graph[x,y] := 0;
        graph[y,x] := 0;
        dec(deg[x]); dec(deg[y]);
        exit;
      end;
    graph[a,b] := 0; graph[b,a] := 0;
    dec(deg[a]); dec(deg[b]);
  end;


Procedure prim(root : longint);
 var i,j,k,max : longint;
  begin
    fillchar(deg,sizeof(deg),0);
    fillchar(p,sizeof(p),0); p[root] := 1;
    for i := 1 to n do d[i] := root; d[root] := 0;
    tot := 0;
    repeat
      k := 0; max := 0;
      for i := 1 to n do if p[i] = 0 then
        for j := 1 to n do if p[j] = 1 then
          if deg[j] < lim[j] then
            if g[i,j] > max then if random(100)+1<=x then
              begin
                k := i; d[k] := j;
                max := g[i,j];
              end;
      if k = 0 then break;
      tot := tot + max;
      inc(deg[d[k]]); inc(deg[k]);
      p[k] := 1;
      if deg[k] < lim[k] then
        for i := 1 to n do if p[i] = 0 then
          if (g[i,d[i]] < g[i,k])or(deg[d[i]]=lim[d[i]]) then d[i] := k;
    until k = 0;
    for i := 1 to n do if p[i] = 0 then exit;
    fillchar(graph,sizeof(graph),0);
    for i := 1 to n do if d[i]<>0 then
      begin
        graph[d[i],i] := 1;
        graph[i,d[i]] := 1;
      end;
    repeat
      k := 0;
      for i := 1 to n do
        for j := 1 to n do
          if (graph[i,j]=0)and(g[i,j]<>-1) then
            if (deg[i]<lim[i])and(deg[j]<lim[j]) then
              try(i,j,k);
    until k = 0;
    if tot > ans then
      begin ans := tot; ansgraph := graph; end;
  end;

begin
  assign(input,'party7.in'); reset(input);
  assign(output,'party7.out'); rewrite(output);
  readln(n,m);
  for i := 1 to n do read(lim[i]); readln;
  fillchar(g,sizeof(g),255);
  for i := 1 to m do
    begin
      read(a,b);
      e[a,b] := i; e[b,a] := i;
      readln(g[a,b]);
      g[b,a] := g[a,b];
    end;
  ans := 0;
  for j := 1 to 100 do
    for i := 1 to n do prim(i);
  writeln(ans);
  for i := 1 to n-1 do
    for j := i+1 to n do
      if ansgraph[i,j] = 1 then
        writeln(e[i,j]);
  close(input); close(output);
end.
