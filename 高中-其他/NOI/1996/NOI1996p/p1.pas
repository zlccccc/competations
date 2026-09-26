program p1;
const
  hn=502397;
type
  link=^node;
  node=
  record
    name:string[10];
    num:word;
    next:link;
  end;
var
  found:boolean;
  p:link;
  hh:dword;
  m,pn,i,f:word;
  filename:string;
  name,mid,sw:string[10];
  hash:array[0..hn-1]of link;
  path:array[1..3000]of string[10];
//
procedure qsort (f,e:word);
var
  i,j:word;
begin
  mid:=path[random(e-f+1)+f];
  i:=f;
  j:=e;
  repeat
    while path[i]<mid do
      inc(i);
    while path[j]>mid do
      dec(j);
    if i<=j then
    begin
      sw:=path[i];
      path[i]:=path[j];
      path[j]:=sw;
      inc(i);
      dec(j);
    end;
  until i>j;
  if i<e then
    qsort(i,e);
  if f<j then
    qsort(f,j);
end;
//
begin
  for f:=1 to 3 do
  begin
    readln(filename);
    assign(input,filename);
    reset(input);
    while not eof do
    begin
      readln(name);
      hh:=0;
      for i:=1 to length(name) do
        hh:=(hh+(ord(name[i])-64)) mod hn;
      p:=hash[hh];
      found:=false;
      while p<>nil do
      begin
        if p^.name=name then
        begin
          inc(p^.num);
          found:=true;
          break;
        end;
        p:=p^.next;
      end;
      if not found then
      begin
        new(p);
        p^.name:=name;
        p^.num:=1;
        p^.next:=hash[hh];
        hash[hh]:=p;
      end;
    end;
    assign(input,'');
    reset(input);
  end;
  pn:=0;
  readln(m);
  for hh:=0 to hn-1 do
  begin
    p:=hash[hh];
    while p<>nil do
    begin
      if p^.num=m then
      begin
        inc(pn);
        path[pn]:=p^.name;
      end;
      p:=p^.next;
    end;
  end;
  randomize;
  qsort(1,pn);
  for i:=1 to pn do
    writeln(path[i]);
  readln;
end.
