program p6;
const
  ep=1e-5;
var
  n,i:integer;
  a,b,sur:real;
  x,y:array[1..100]of real;
//
function search (x1,y1,x2,y2:real):real;
var
  i:integer;
  t1,t2:real;
begin
  search:=(x2-x1)*(y2-y1);
  for i:=1 to n do
  begin
    if (x2-x1>=x[i]-ep) and (y2-y1>=y[i]-ep) then
    begin
      t1:=search(x1,y1+y[i],x2,y2);
      t2:=search(x1+x[i],y1,x2,y1+y[i]);
      if t1+t2<search then
        search:=t1+t2;
      t1:=search(x1,y1+y[i],x1+x[i],y2);
      t2:=search(x1+x[i],y1,x2,y2);
      if t1+t2<search then
        search:=t1+t2;
    end;
    if (x2-x1>=y[i]-ep) and (y2-y1>=x[i]-ep) then
    begin
      t1:=search(x1,y1+x[i],x2,y2);
      t2:=search(x1+y[i],y1,x2,y1+x[i]);
      if t1+t2<search then
        search:=t1+t2;
      t1:=search(x1,y1+x[i],x1+y[i],y2);
      t2:=search(x1+y[i],y1,x2,y2);
      if t1+t2<search then
        search:=t1+t2;
    end;
  end;
end;
//
begin
  assign(input,'p6.in');
  reset(input);
  readln(a,b);
  readln(n);
  for i:=1 to n do
    readln(x[i],y[i]);
  sur:=search(0,0,a,b);
  writeln(sur:0:2);
  assign(input,'');
  reset(input);
  readln;
end.
