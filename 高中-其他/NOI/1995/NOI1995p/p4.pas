program p4;
var
  n,m,i,j,last,now:smallint;
  filename,st:string;
  x2:array[0..14]of smallint;
  hash:array[1..32768]of boolean;
  //path:array[1..32768]of smallint;
  start:string[15];
//
{procedure DFS (dep:smallint);
var
  i,now:smallint;
begin
  if dep=m then
  begin
    writeln(n);
    for i:=1 to m do
    begin
      st:='';
      while path[i]>0 do
      begin
        st:=chr(path[i] mod 2+48)+st;
        path[i]:=path[i] div 2;
      end;
      while length(st)<n do
        st:='0'+st;
      writeln(st);
    end;
    close(output);
    halt;
  end;
  for i:=0 to n-1 do
  begin
    now:=path[dep] xor x2[i];
    if not hash[now] then
    begin
      hash[now]:=true;
      path[dep+1]:=now;
      DFS(dep+1);
      hash[now]:=false;
    end;
  end;
end; }
//
begin
  readln(filename);
  assign(input,filename);
  assign(output,'output.txt');
  reset(input);
  rewrite(output);
  readln(n);
  m:=1 shl n;
  for i:=0 to n-1 do
    x2[i]:=1 shl i;
  readln(start);
  now:=0;
  for i:=1 to n do
    now:=now+ord(start[i]='1')*x2[i-1];
  hash[now]:=true;
  writeln(n);
  writeln(start);
  last:=now;
  for i:=1 to m-1 do
    for j:=0 to n-1 do
    begin
      now:=last xor x2[j];
      if not hash[now] then
      begin
        last:=now;
        hash[now]:=true;
        st:='';
        while now>0 do
        begin
          st:=chr(now mod 2+48)+st;
          now:=now div 2;
        end;
        while length(st)<n do
          st:='0'+st;
        writeln(st);
        break;
      end;
    end;
  close(output);
end.
