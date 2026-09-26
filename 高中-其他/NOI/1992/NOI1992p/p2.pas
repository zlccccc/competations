program p2;
type
  link=^node;
  node=
  record
    v:char;
    flag:boolean;
    next,down:link;
  end;
var
  ch:char;
  st:string;
  et,i:integer;
  alp,pri:array[#1..#127]of 0..3;
  p,t:link;
//
procedure illegal;
begin
  writeln('Illegal');
  readln;
  halt;
end;
//
procedure free (p:link);
begin
  if p^.next<>nil then
    free(p^.next);
  if p^.down<>nil then
    free(p^.down);
  dispose(p);
end;
//
function ex (h1,h2:link):link;
var
  first:boolean;
  p,s:link;
begin
  first:=true;
  while h1<>nil do
  begin
    new(p);
    p^.v:=h1^.v;
    p^.flag:=h1^.flag;
    p^.next:=nil;
    p^.down:=nil;
    if first then
    begin
      first:=false;
      ex:=p;
      s:=p;
    end
    else
    begin
      s^.down:=p;
      s:=s^.down;
    end;
    h1:=h1^.down;
  end;
  while h2<>nil do
  begin
    new(p);
    p^.v:=h2^.v;
    p^.flag:=h2^.flag;
    p^.next:=nil;
    p^.down:=nil;
    s^.down:=p;
    s:=s^.down;
    h2:=h2^.down;
  end;
end;
//
function calc (f,e:integer):link;
type
  data=
  record
    flag:boolean;
    v:char;
  end;
var
  flag,next,first:boolean;
  i,pl:integer;
  sp:1..4;
  p,t,s,h1,h2,p1,p2:link;
  path:array[1..100]of data;
//**
procedure DFS (h:link;dep:integer);
var
  i:integer;
  x:link;
begin
  if h=nil then
  begin
    new(p);
    p^.next:=nil;
    p^.down:=nil;
    p^.v:=path[1].v;
    p^.flag:=not path[1].flag;
    h2:=p;
    for i:=2 to dep-1 do
    begin
      new(s);
      s^.next:=nil;
      s^.down:=nil;
      s^.v:=path[i].v;
      s^.flag:=not path[i].flag;
      p^.down:=s;
      p:=p^.down;
    end;
    if first then
    begin
      first:=false;
      calc:=h2;
      t:=h2;
    end
    else
    begin
      t^.next:=h2;
      t:=t^.next;
    end;
    exit;
  end;
  x:=h;
  while x<>nil do
  begin
    path[dep].flag:=x^.flag;
    path[dep].v:=x^.v;
    DFS(h^.next,dep+1);
    x:=x^.down;
  end;
end;
//**
begin
  if pos('(',copy(st,f,e-f+1))=0 then
  begin
    flag:=false;
    next:=false;
    first:=true;
    for i:=f to e do
      if alp[st[i]]=1 then
      begin
        new(p);
        p^.v:=st[i];
        p^.flag:=flag;
        flag:=false;
        p^.next:=nil;
        p^.down:=nil;
        if first then
        begin
          first:=false;
          t:=p;
          s:=p;
          calc:=p;
          continue;
        end;
        if next then
        begin
          t^.next:=p;
          t:=t^.next;
          s:=t;
          next:=false;
        end
        else
        begin
          s^.down:=p;
          s:=s^.down;
        end;
      end
      else
        case st[i] of
          '~':
            flag:=not flag;
          '+':
            next:=true;
        end;
  end
  else
  begin
    et:=0;
    sp:=4;
    for i:=f to e do
      case alp[st[i]] of
        2:
          if (et=0) and (pri[st[i]]<sp) then
          begin
            sp:=pri[st[i]];
            pl:=i;
          end;
        3:
          if st[i]='(' then
            inc(et)
          else
            dec(et);
      end;
    case sp of
      1:
      begin
        h1:=calc(f,pl-1);
        h2:=calc(pl+1,e);
        calc:=h1;
        p:=h1;
        while p^.next<>nil do
          p:=p^.next;
        p^.next:=h2;
      end;
      2:
      begin
        h1:=calc(f,pl-1);
        h2:=calc(pl+1,e);
        p1:=h1;
        p2:=h2;
        first:=true;
        while p1<>nil do
        begin
          s:=p2;
          while p2<>nil do
          begin
            p:=ex(p1,p2);
            if first then
            begin
              first:=false;
              calc:=p;
              t:=p;
            end
            else
            begin
              t^.next:=p;
              t:=t^.next;
            end;
            p2:=p2^.next;
          end;
          p1:=p1^.next;
          p2:=s;
        end;
        free(h1);
        free(h2);
      end;
      3:
      begin
        first:=true;
        h1:=calc(pl+2,e-1);
        DFS(h1,1);
        free(h1);
      end;
      4:
        calc:=calc(f+1,e-1);
    end;
  end;
end;
//
procedure fix (h:link);
var
  del:boolean;
  t,s,tt,ht:link;
  tick:array[boolean,#1..#127]of boolean;
begin
  ht:=h;
  h:=h^.next;
  while h<>nil do
  begin
    s:=h;
    fillchar(tick,sizeof(tick),false);
    del:=false;
    while s<>nil do
    begin
      if tick[s^.flag,s^.v] then
      begin
        tt:=s;
        t^.down:=s^.down;
        s:=s^.down;
        dispose(tt);
        continue;
      end;
      if tick[not s^.flag,s^.v] then
      begin
        tt:=h;
        ht^.next:=h^.next;
        h:=h^.next;
        free(tt^.down);
        dispose(tt);
        del:=true;
        break;
      end;
      tick[s^.flag,s^.v]:=true;
      t:=s;
      s:=s^.down;
    end;
    if not del then
    begin
      ht:=h;
      h:=h^.next;
    end;
  end;
end;
//
begin
  for ch:='a' to 'z' do
    alp[ch]:=1;
  for ch:='A' to 'Z' do
    alp[ch]:=1;
  alp['~']:=2;
  alp['*']:=2;
  alp['+']:=2;
  alp['(']:=3;
  alp[')']:=3;
  pri['+']:=1;
  pri['*']:=2;
  pri['~']:=3;
  readln(st);
  et:=0;
  for i:=1 to length(st) do
    case alp[st[i]] of
      0:
        illegal;
      2:
      begin
        if st[i]='~' then
          if not ((alp[st[i+1]]=1) or (st[i+1]='(') or (st[i+1]='~')) then
            illegal
          else
        else
          if not (((alp[st[i+1]]=1) or (st[i+1]='(') or (st[i+1]='~')) and ((alp[st[i-1]]=1) or (st[i-1]=')'))) then
            illegal;
      end;
      3:
      begin
        if st[i]='(' then
          inc(et)
        else
          dec(et);
        if et<0 then
          illegal;
      end;
    end;
  if et>0 then
    illegal;
  p:=calc(1,length(st));
  new(t);
  t^.next:=p;
  t^.down:=nil;
  p:=t;
  fix(p);
  p:=p^.next;
  while p<>nil do
  begin
    t:=p;
    while p<>nil do
    begin
      if p^.flag then
        write('~');
      write(p^.v);
      p:=p^.down;
      if p<>nil then
        write('*');
    end;
    p:=t^.next;
    if p<>nil then
      write('+');
  end;
  writeln;
  readln;
end.
