program p32;
var
  ch,now:char;
  sn,i,j,n1,n2,n,r1,r2,a,b:integer;
  d1,d2,t1,t2:array[1..26]of integer;
  m1,m2:array[1..26,1..26]of boolean;
  stack:array[1..50]of char;
  list:array[0..26]of integer;
  s1,s2:array[1..26,0..26]of integer;
  tick2:array[1..26]of boolean;
//
procedure diff;
begin
  writeln('Different');
  readln;
  halt;
end;
//
function equal (p1,p2,f1,f2:integer):boolean;
var
  i,j:integer;
  match:boolean;
begin
  if t1[p1]<>t2[p2] then
    exit(false);
  for i:=1 to s1[p1,0] do
    if s1[p1,i]<>f1 then
    begin
      match:=false;
      for j:=1 to s2[p2,0] do
        if (s2[p2,j]<>f2) and not tick2[s2[p2,j]] then
          if equal(s1[p1,i],s2[p2,j],p1,p2) then
          begin
            tick2[s2[p2,j]]:=true;
            match:=true;
            break;
          end;
      if not match then
        exit(false);
    end;
  exit(true);
end;
//
begin
  n1:=0;
  sn:=0;
  now:=pred('A');
  repeat
    read(ch);
    if ch=')' then
    begin
      dec(n1);
      i:=sn;
      while stack[i]<>'(' do
        dec(i);
      j:=sn;
      while j>i do
      begin
        a:=ord(stack[j])-64;
        b:=ord(stack[i-1])-64;
        inc(d1[a]);
        inc(d1[b]);
        m1[a,b]:=true;
        m1[b,a]:=true;
        inc(s1[a,0]);
        s1[a,s1[a,0]]:=b;
        inc(s1[b,0]);
        s1[b,s1[b,0]]:=a;
        dec(j);
      end;
      sn:=i-1;
    end
    else
    begin
      inc(sn);
      inc(n1);
      if ch in ['A'..'Z'] then
      begin
        now:=succ(now);
        stack[sn]:=now;
      end
      else
        stack[sn]:='(';
    end;
  until eoln;
  readln;
  n2:=0;
  sn:=0;
  now:=pred('A');
  repeat
    read(ch);
    if ch=')' then
    begin
      dec(n2);
      i:=sn;
      while stack[i]<>'(' do
        dec(i);
      j:=sn;
      while j>i do
      begin
        a:=ord(stack[j])-64;
        b:=ord(stack[i-1])-64;
        inc(d2[a]);
        inc(d2[b]);
        m2[a,b]:=true;
        m2[b,a]:=true;
        inc(s2[a,0]);
        s2[a,s2[a,0]]:=b;
        inc(s2[b,0]);
        s2[b,s2[b,0]]:=a;
        dec(j);
      end;
      sn:=i-1;
    end
    else
    begin
      inc(sn);
      inc(n2);
      if ch in ['A'..'Z'] then
      begin
        now:=succ(now);
        stack[sn]:=now;
      end
      else
        stack[sn]:='(';
    end;
  until eoln;
  readln;
  if n1<>n2 then
    diff;
  n:=n1;
  t1:=d1;
  while n1>2 do
  begin
    list[0]:=0;
    for i:=1 to n do
      if d1[i]=1 then
      begin
        inc(list[0]);
        list[list[0]]:=i;
      end;
    dec(n1,list[0]);
    for i:=1 to list[0] do
    begin
      d1[list[i]]:=-1;
      for j:=1 to n do
        if m1[list[i],j] then
          dec(d1[j]);
    end;
  end;
  t2:=d2;
  while n2>2 do
  begin
    list[0]:=0;
    for i:=1 to n do
      if d2[i]=1 then
      begin
        inc(list[0]);
        list[list[0]]:=i;
      end;
    dec(n2,list[0]);
    for i:=1 to list[0] do
    begin
      d2[list[i]]:=-1;
      for j:=1 to n do
        if m2[list[i],j] then
          dec(d2[j]);
    end;
  end;
  if n1<>n2 then
    diff;
  r2:=1;
  while d2[r2]=-1 do
    inc(r2);
  for r1:=1 to n do
    if d1[r1]<>-1 then
      if equal(r1,r2,0,0) then
      begin
        writeln('Same');
        readln;
        halt;
      end
      else
        fillchar(tick2,sizeof(tick2),false);
  diff;
end.
