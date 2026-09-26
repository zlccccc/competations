program p1;
var
  n,lim,i,j,k,t,nl,ave,last,ss:integer;
  ch,mode:char;
  w:array[1..1000]of string[20];
  ll,sp:array[1..1000]of integer;
begin
  readln(lim);
  read(ch);
  while ch=' ' do
    read(ch);
  n:=1;
  while true do
  begin
    w[n]:=w[n]+ch;
    read(ch);
    if eoln then
      break;
    if ch=' ' then
    begin
      while not eoln and (ch=' ') do
        read(ch);
      if eoln then
        break;
      inc(n);
    end;
  end;
  w[n]:=w[n]+ch;
  readln;
  t:=length(w[1]);
  nl:=1;
  sp[nl]:=lim-t;
  if sp[nl]<0 then
  begin
    writeln('wrong');
    readln;
    halt;
  end;
  ll[nl]:=1;
  for i:=2 to n do
  begin
    t:=length(w[i])+1;
    if sp[nl]>=t then
    begin
      inc(ll[nl]);
      dec(sp[nl],t);
    end
    else
    begin
      inc(nl);
      sp[nl]:=lim-t+1;
      if sp[nl]<0 then
      begin
        writeln('wrong');
        readln;
        halt;
      end;
      ll[nl]:=1;
    end;
  end;
  readln(mode);
  case mode of
    '1':
    begin
      last:=0;
      for i:=1 to nl do
      begin
        write(w[last+1]);
        for j:=last+2 to last+ll[i] do
          write(' ',w[j]);
        last:=j;
        for j:=1 to sp[i] do
          write(' ');
        writeln;
      end;
    end;
    '2':
    begin
      last:=0;
      for i:=1 to nl do
      begin
        for j:=1 to sp[i] do
          write(' ');
        write(w[last+1]);
        for j:=last+2 to last+ll[i] do
          write(' ',w[j]);
        last:=j;
        writeln;
      end;
    end;
    '3':
    begin
      last:=0;
      for i:=1 to nl do
      begin
        if ll[i]=1 then
        begin
          writeln('//wrong at ',i);
          writeln(w[last+1]);
          continue;
        end;
        ave:=sp[i] div (ll[i]-1);
        ss:=sp[i] mod (ll[i]-1);
        write(w[last+1]);
        for j:=last+2 to last+ll[i] do
        begin
          for k:=1 to ave do
            write(' ');
          if j-last-1<=ss then
            write(' ');
          write(' ',w[j]);
        end;
        last:=j;
        writeln;
      end;
    end;
  end;
  readln;
end.
