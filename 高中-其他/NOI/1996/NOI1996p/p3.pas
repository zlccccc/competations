program p3;
var
  filename,st:string;
  x:smallint;
//
function r (f,e:smallint):smallint;
var
  i,c:smallint;
begin
  c:=0;
  for i:=f to e do
    case st[i] of
      '(':
        inc(c);
      ')':
        dec(c);
      '+':
        if c=0 then
          exit(r(f,i-1)+r(i+1,e));
      '*':
        if c=0 then
          exit(r(f,i-1)*r(i+1,e));
    end;
  if f=e then
    exit(x)
  else
    exit(r(f+1,e-1));
end;
//
function t (f,e:smallint):smallint;
var
  i,c:smallint;
begin
  c:=0;
  for i:=f to e do
    case st[i] of
      '(':
        inc(c);
      ')':
        dec(c);
      '+':
        if c=0 then
          exit(t(f,i-1)+t(i+1,e));
      '*':
        if c=0 then
          exit(t(f,i-1)*r(i+1,e)+t(i+1,e)*r(f,i-1));
    end;
  if f=e then
    exit(1)
  else
    exit(t(f+1,e-1));
end;
//
begin
  readln(filename);
  assign(input,filename);
  reset(input);
  readln(st);
  readln(x);
  writeln(t(1,length(st)));
  readln;
end.
