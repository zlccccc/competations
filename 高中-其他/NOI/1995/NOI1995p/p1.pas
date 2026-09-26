program p1;
var
  num,line:integer;
  has:array[1..10000]of boolean;
  filename,oj,tmp:string;
  ch:char;
begin
  readln(filename);
  readln(oj);
  oj:=upcase(oj);
  assign(input,filename);
  assign(output,'output.txt');
  reset(input);
  rewrite(output);
  line:=1;
  num:=0;
  tmp:='';
  while not eof do
  begin
    read(ch);
    if ch in [' ',',','.',#13] then
    begin
      if upcase(tmp)=oj then
      begin
        inc(num);
        has[line]:=true;
      end;
      if ch='.' then
        inc(line);
      if ch=#13 then
        readln;
      tmp:='';
    end
    else
      tmp:=tmp+ch;
  end;
  writeln(num);
  reset(input);
  tmp:='';
  line:=1;
  while not eof do
  begin
    read(ch);
    if ch=#13 then
    begin
      readln;
      continue;
    end;
    tmp:=tmp+ch;
    if ch='.' then
    begin
      if has[line] then
        writeln(tmp);
      inc(line);
      tmp:='';
    end;
  end;
  close(output);
end.
