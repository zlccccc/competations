{$R-,S-,Q-,I-}
const maxn = 200; oo = 1000000;
var
  heap,where,which   : array[1..maxn] of longint;
  f,g                : array[1..maxn,1..maxn] of longint;
  map                : array[1..maxn,1..maxn] of char;
  n,m,i,j,x,y,k,size : integer;

Procedure swap(a,b : integer);
 var t : longint;
  begin
    t := heap[a]; heap[a] := heap[b]; heap[b] := t;
    t := which[a]; which[a] := which[b]; which[b] := t;
    where[which[a]] := a; where[which[b]] := b;
  end;

Procedure ins_heap(value,whi : longint);
 var i : integer;
  begin
    inc(size); heap[size] := value; which[size] := whi; where[whi] := size;
    i := size;
    repeat
      if i = 1 then break;
      if heap[i] > heap[i div 2] then
        begin
          swap(i,i div 2);
          i := i div 2;
        end
      else break;
    until false;
  end;

Procedure del_heap(whe : integer);
 var i : integer;
  begin
    i := where[whe];
    swap(where[whe],size);
    dec(size);
    repeat
      k := i;
      if (i*2<=size)and(heap[i*2]>heap[k]) then k := i*2;
      if (i*2+1<=size)and(heap[i*2+1]>heap[k]) then k := i*2+1;
      if k = i then break;
      swap(i,k);
      i := k;
    until false;
  end;

Procedure solve1(k : integer);
 var i,j,x : integer;
  begin
    g := f;
    for j := 1 to m do
      begin
        fillchar(heap,sizeof(heap),0);
        size := 0; x := n+1;
        for i := n downto 1 do if map[i,j]='.' then
          begin
            ins_heap(f[i,j]+i,i);
            if i+k+1<x then del_heap(i+k+1);
            f[i,j] := g[which[1],j]+which[1]-i;
          end
        else
          begin
            fillchar(heap,sizeof(heap),0);
            size := 0; x := i;
          end;
      end;
  end;

Procedure solve2(k : integer);
 var i,j,x : integer;
  begin
    g := f;
    for j := 1 to m do
      begin
        fillchar(heap,sizeof(heap),0);
        size := 0; x := 0;
        for i := 1 to n do if map[i,j]='.' then
          begin
            ins_heap(f[i,j]+n-i,i);
            if i-k-1>x then del_heap(i-k-1);
            f[i,j] := g[which[1],j]+i-which[1];
          end
        else
          begin
            fillchar(heap,sizeof(heap),0);
            size := 0; x := i;
          end;
      end;
  end;

Procedure solve3(k : integer);
 var i,j,x : integer;
  begin
    g := f;
    for i := 1 to n do
      begin
        fillchar(heap,sizeof(heap),0);
        size := 0; x := m+1;
        for j := m downto 1 do if map[i,j]='.' then
          begin
            ins_heap(f[i,j]+j,j);
            if j+k+1<x then del_heap(j+k+1);
            f[i,j] := g[i,which[1]]+which[1]-j;
          end
        else
          begin
            fillchar(heap,sizeof(heap),0);
            size := 0; x := j;
          end;
      end;
  end;

Procedure solve4(k : integer);
 var i,j,x : integer;
  begin
    g := f;
    for i := 1 to n do
      begin
        fillchar(heap,sizeof(heap),0);
        size := 0; x := 0;
        for j := 1 to n do if map[i,j]='.' then
          begin
            ins_heap(f[i,j]+m-j,j);
            if j-k-1>x then del_heap(j-k-1);
            f[i,j] := g[i,which[1]]+j-which[1];
          end
        else
          begin
            fillchar(heap,sizeof(heap),0);
            size := 0; x := j;
          end;
      end;
  end;

begin
  assign(input,'adv19006.in'); reset(input);
  assign(output,'adv19006.out'); rewrite(output);
  readln(n,m,x,y,k);
  for i := 1 to n do
    begin
      for j := 1 to m do
        begin
          read(map[i,j]);
          f[i,j] := -oo
        end;
      readln;
    end;
  f[x,y] := 0;
  for i := 1 to k do
    begin
      readln(x,y,j);
      case j of
        1 : solve1(y-x+1);
        2 : solve2(y-x+1);
        3 : solve3(y-x+1);
        4 : solve4(y-x+1);
      end;
    end;
  k := 0;
  for i := 1 to n do
    for j := 1 to m do
      if f[i,j] > k then k := f[i,j];
  writeln(k);
  close(input); close(output);
end.
