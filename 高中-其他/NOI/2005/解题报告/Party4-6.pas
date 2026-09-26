const maxn = 1000; maxm = 20000; oo = -10000;
type
  link = ^node;
  node = record
           k,id : longint;
           next : link;
         end;
var
  f,lim     : array[1..maxn] of longint;
  use,con,ansuse   : array[1..maxm] of boolean;
  u,v,c,e   : array[0..maxm] of longint;
  min,chos,dist,edge,opt  : array[1..maxn] of longint;
  tree      : array[1..maxn] of link;
  i,j,n,m,vp,ans,deg,now : longint;
  p : link;

Procedure sort(l,r : longint);
 var i,j,x,y : longint;
  begin
    i := l; j := r; x := c[(i+j) div 2];
    repeat
      while c[i] > x do inc(i);
      while c[j] < x do dec(j);
      if i <= j then
        begin
          y := e[i]; e[i] := e[j]; e[j] := y;
          y := u[i]; u[i] := u[j]; u[j] := y;
          y := v[i]; v[i] := v[j]; v[j] := y;
          y := c[i]; c[i] := c[j]; c[j] := y;
          inc(i); dec(j);
        end;
    until i > j;
    if l < j then sort(l,j);
    if i < r then sort(i,r);
  end;

Function root(k : longint) : longint;
  begin
    if f[k] = k then exit(k);
    f[k] := root(f[k]);
    root := f[k];
  end;

Function kruskal : longint;
 var sum,i : longint;
     p     : link;
  begin
    for i := 1 to n do f[i] := i;
    fillchar(use,sizeof(use),false);
    sum := 0;
    for i := 1 to m do if (u[i]<>vp)and(v[i]<>vp) then
      if root(u[i])<>root(v[i]) then
        begin
          use[i] := true;
          f[f[u[i]]] := f[v[i]];
        end;
    for i := 1 to n do min[i] := oo;
    for i := 1 to n do chos[i] := 0;
    for i := 1 to m do
      if (u[i] = vp) then
        begin
          if c[i] > min[root(v[i])] then
            begin
              min[root(v[i])] := c[i];
              chos[root(v[i])] := i;
            end;
        end else
      if (v[i] = vp) then
        begin
          if c[i] > min[root(u[i])] then
            begin
              min[root(u[i])] := c[i];
              chos[root(u[i])] := i;
            end;
        end;
    deg := 0;
    for i := 1 to m do
      if (u[i] = vp) then
        begin
          use[chos[root(v[i])]] := true;
        end else
      if (v[i] = vp) then
        begin
          use[chos[root(u[i])]] := true;
        end;
    for i := 1 to m do if use[i] then
      if (v[i] = vp)or(u[i] = vp) then inc(deg);
    sum := 0;
    fillchar(con,sizeof(con),false);
    for i := 1 to m do if use[i] then
      begin
        sum := sum + c[i];
        if u[i] = vp then con[v[i]] := true;
        if v[i] = vp then con[u[i]] := true;
      end;
    kruskal := sum;
  end;

Procedure dfs(father,k,x : longint);
 var p : link;
  begin
    opt[k] := x;
    p := tree[k];
    while p <> nil do
      begin
        if p^.k <> father then
          begin
            dist[p^.k] := dist[k]+c[p^.id];
            if c[x] > c[p^.id] then dfs(k,p^.k,p^.id)
                               else dfs(k,p^.k,x);
          end;
        p := p^.next;
      end;
  end;

Procedure solve;
 var i,j,delta,k : longint;
     p,q : link;
  begin
    dist[vp] := 0;
    c[0] := -oo;
    dfs(0,vp,0);
    delta := oo; k := 0;
    for i := 1 to n do if i<>vp then
      if con[i] = false then
        if edge[i]<>0 then
          if c[edge[i]]-c[opt[i]] > delta then
            begin
              delta := c[edge[i]]-c[opt[i]];
              k := i;
            end;
    now := now+delta;
    i := opt[k];
    p := tree[u[i]];
    if p^.k = v[i] then
      begin
        tree[u[i]] := tree[u[i]]^.next;
        dispose(p);
      end
    else
      begin
        while (tree[u[i]]<>nil)and(tree[u[i]]^.next^.k <> v[i]) do
          tree[u[i]] := tree[u[i]]^.next;
        q := tree[u[i]]^.next;
        tree[u[i]]^.next := tree[u[i]]^.next^.next;
        dispose(q);
        tree[u[i]] := p;
      end;
    use[i] := false;
    p := tree[v[i]];
    if p^.k = u[i] then
      begin
        tree[v[i]] := tree[v[i]]^.next;
        dispose(p);
      end
    else
      begin
        while (tree[v[i]]<>nil)and(tree[v[i]]^.next^.k <> u[i]) do
          tree[v[i]] := tree[v[i]]^.next;
        q := tree[v[i]]^.next;
        tree[v[i]]^.next := tree[v[i]]^.next^.next;
        dispose(q);
        tree[v[i]] := p;
      end;
    i := edge[k];
    use[i] := true;
    new(p); p^.k := u[i]; p^.id := i; p^.next := tree[v[i]]; tree[v[i]] := p;
    new(p); p^.k := v[i]; p^.id := i; p^.next := tree[u[i]]; tree[u[i]] := p;
    if now > ans then
      begin
        ans := now;
        ansuse := use;
      end;
  end;

begin
  assign(input,'party.in'); reset(input);
  assign(output,'party.out'); rewrite(output);
  readln(n,m);
  for i := 1 to n do read(lim[i]); readln;
  for i := 1 to m do
    begin
      readln(u[i],v[i],c[i]);
      e[i] := i;
    end;
  sort(1,m);
  for i := 1 to n do if lim[i]<>n-1 then break;
  vp := i;
  fillchar(edge,sizeof(edge),0);
  for i := 1 to m do
    begin
      if v[i] = vp then edge[u[i]] := i;
      if u[i] = vp then edge[v[i]] := i;
    end;
  now := kruskal;
  for i := 1 to m do if use[i] then
    begin
      new(p); p^.k := v[i]; p^.id := i; p^.next := tree[u[i]]; tree[u[i]] := p;
      new(p); p^.k := u[i]; p^.id := i; p^.next := tree[v[i]]; tree[v[i]] := p;
    end;
  ans := now; ansuse := use;
  for i := deg+1 to lim[vp] do solve;
  writeln(ans);
  for i := 1 to m do if ansuse[i] then writeln(e[i]);
  close(input); close(output);
end.
