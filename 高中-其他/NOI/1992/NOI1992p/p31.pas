program p31;
var
  sn,i,j:integer;
  map:array['A'..'Z','A'..'Z']of boolean;
  stack:array[1..100]of char;
  ch,root:char;
  tick:array['A'..'Z']of boolean;
//
procedure print (s:char);
var
  son:boolean;
  i:char;
begin
  write('P');
  tick[s]:=true;
  son:=false;
  for i:='A' to 'Z' do
    if map[s,i] and not tick[i] then
    begin
      son:=true;
      break;
    end;
  if son then
  begin
    write('(');
    for i:='A' to 'Z' dos
      if map[s,i] and not tick[i] then
        print(i);
    write(')');
  end;
end;
//
begin
  sn:=0;
  repeat
    read(ch);
    if ch=')' then
    begin
      i:=sn;
      while stack[i]<>'(' do
        dec(i);
      j:=sn;
      while j>=i do
      begin
        map[stack[j],stack[i-1]]:=true;
        map[stack[i-1],stack[j]]:=true;
        dec(j);
      end;
      sn:=i-1;
    end
    else
    begin
      inc(sn);
      stack[sn]:=ch;
    end;
  until eoln;
  readln;
  readln(root);
  print(root);
  writeln;
  readln;
end.
