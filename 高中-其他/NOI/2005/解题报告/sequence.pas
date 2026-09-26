(*
program by hjs
In the program, |N = sqrt(N)
*)
{$R-,S-,Q-,I-} 
const maxn = 1000; oo= 10000;
      fin  = 'sequence.in';
      fou  = 'sequence.out';
type
  link = ^node;
  node = record
           a : array[1..maxn] of longint;
           tot,l,r,max,sum,t,v,c : longint;
           pre,suc : link;
         end;
var
  n,m,i,j,k,posi,tot,c : longint;
  sequence : array[1..500000] of longint;
  seq                : link;
  ch                 : char;

Procedure init(var seq : link; father : link); {O(1)}
  begin
    new(seq);
    seq^.tot := 0;
    seq^.max := 0;
    seq^.sum := 0;
    seq^.v := 0;
    seq^.l := 0;
    seq^.r := 0;
    seq^.t := 0;
    seq^.pre := father;
  end;

Procedure reverse(var seq : link); {O(|N)}
 var tmp : array[1..maxn] of longint;
     i : longint;
  begin
    seq^.t := 0;
    for i := 1 to seq^.tot do tmp[i] := seq^.a[i];
    for i := seq^.tot downto 1 do seq^.a[i] := tmp[seq^.tot-i+1];
  end;

Procedure makesam(var seq : link); {O(|N)}
 var i : longint;
  begin
    seq^.v := 0;
    for i := 1 to seq^.tot do seq^.a[i] := seq^.c;
    for i := seq^.tot+1 to maxn do seq^.a[i] := 0;
    if seq^.c > 0 then seq^.l := seq^.c*seq^.tot
                  else seq^.l := seq^.c;
    seq^.max := seq^.l; seq^.r := seq^.l;
    seq^.sum := seq^.c*seq^.tot;
    seq^.c := 0;
  end;

Procedure behalf(var seq : link); {O(|N)}
 var i,sum,min : longint;
  begin
    if seq = nil then exit;
    min := 0; sum := 0;
    seq^.max := -oo; seq^.l := -oo;
    for i := 1 to seq^.tot do
      begin
        sum := sum + seq^.a[i];
        if sum - min > seq^.max then seq^.max := sum - min;
        if sum < min then min := sum;
        if sum > seq^.l then seq^.l := sum;
      end;
    sum := 0; seq^.r := -oo;
    for i := seq^.tot downto 1 do
      begin
        sum := sum + seq^.a[i];
        if sum > seq^.r then seq^.r := sum;
      end;
    seq^.sum := sum;
  end;

Procedure merge; {O(|N*BigC)}
 var i : longint;
     head,mid : link;
  begin
    head := seq;
    while (seq<>nil)and(seq^.suc <> nil) do
      begin
        while (seq^.suc<>nil)and(seq^.tot+seq^.suc^.tot<=maxn) do
          begin
            if seq^.v = 1 then makesam(seq);
            if seq^.t = 1 then reverse(seq);
            if seq^.suc^.v = 1 then makesam(seq^.suc);
            if seq^.suc^.t = 1 then reverse(seq^.suc);
            for i := 1 to seq^.suc^.tot do
              seq^.a[i+seq^.tot] := seq^.suc^.a[i];
            seq^.tot := seq^.tot+seq^.suc^.tot;
            behalf(seq);
            mid := seq^.suc;
            seq^.suc := seq^.suc^.suc;
            mid^.suc^.pre := seq;
            dispose(mid);
          end;
        seq := seq^.suc;
      end;
    seq := head;
  end;

Procedure makelink(var l,r : link; tot : longint) {O(|N)};
 var p,f : link;
     i   : longint;
  begin
    p := nil;
    for i := 1 to tot do
      begin
        if i mod maxn = 1 then
          begin
            f := p;
            behalf(p);
            init(p,f);
            if i = 1 then l := p;
            f^.suc := p;
            p^.pre := f;
            p^.tot := 0;
          end;
        p^.tot := p^.tot+1;
        p^.a[(i-1) mod maxn+1] := sequence[i];
      end;
    behalf(p); r := p;
  end;

Procedure ins(posi,tot : longint); {O(|N+tot)}
 var head,l,r,p : link;
     now,i  : longint;
  begin
    if tot = 0 then exit;
    head := seq;
    makelink(l,r,tot);
    if seq = nil then
      begin
        seq := l; exit;
      end;
    now := 0;
    while (seq<>nil)and(now+seq^.tot < posi) do
      begin
        now := now + seq^.tot;
        seq := seq^.suc;
      end;
    if seq^.v = 1 then makesam(seq);
    if seq^.t = 1 then reverse(seq);
    if seq^.tot+now > posi then
      begin
        init(p,nil);
        for i := posi-now+1 to seq^.tot do
          p^.a[i-posi+now]  := seq^.a[i];
        p^.tot := seq^.tot - posi+now;
        seq^.tot := posi - now;
        behalf(p); behalf(seq);
        seq^.suc^.pre := p; p^.suc := seq^.suc;
        seq^.suc := p; p^.pre := seq;
      end;
    seq^.suc^.pre := r; r^.suc := seq^.suc;
    seq^.suc := l; l^.pre := seq;
    seq := head;
  end;

Procedure del(posi,tot : longint); {O(|N)}
 var head,mid : link;
     i,sub,now : longint;
  begin
    if tot = 0 then exit;
    head := seq; now := 0;
    while (seq<>nil)and(now+seq^.tot < posi) do
      begin
        now := now + seq^.tot;
        seq := seq^.suc;
      end;
    if seq^.v = 1 then makesam(seq);
    if seq^.t = 1 then reverse(seq);
    if seq^.tot-(posi-now)+1 < tot then
      begin
        sub := seq^.tot-(posi-now)+1;
        seq^.tot := posi-now-1;
        behalf(seq);
        while (seq^.suc<>nil)and(sub+seq^.suc^.tot <= tot) do
          begin
            mid := seq^.suc;
            sub := sub + seq^.suc^.tot;
            seq^.suc := seq^.suc^.suc;
            dispose(mid);
          end;
        seq^.suc^.pre := seq;
        seq := seq^.suc;
        if seq^.v = 1 then makesam(seq);
        if seq^.t = 1 then reverse(seq);
        for i := tot-sub+1 to seq^.tot do
          seq^.a[i-tot+sub] := seq^.a[i];
        dec(seq^.tot,tot-sub);
        behalf(seq);
      end
    else
      begin
        for i := posi-now+tot to seq^.tot do
          seq^.a[i-tot] := seq^.a[i];
        dec(seq^.tot,tot);
        behalf(seq);
      end;
    seq := head;
  end;

Procedure sam(posi,tot,c : longint); {(|N)}
 var head : link;
     i,now,sub : longint;
  begin
    head := seq;
    now := 0;
    while (seq<>nil)and(now+seq^.tot < posi) do
      begin
        now := now + seq^.tot;
        seq := seq^.suc;
      end;
    if seq^.v = 1 then makesam(seq);
    if seq^.t = 1 then reverse(seq);
    if seq^.tot-(posi-now)+1 < tot then
      begin
        sub := seq^.tot-(posi-now)+1;
        for i := posi-now to seq^.tot do seq^.a[i] := c;
        behalf(seq);
        seq := seq^.suc;
        while (seq<>nil)and(sub+seq^.tot <= tot) do
          begin
            sub := sub + seq^.tot;
            seq^.v := 1; seq^.c := c;
            if c > 0 then
              begin
                seq^.l := seq^.tot*c;
                seq^.r := seq^.tot*c;
                seq^.sum := seq^.tot*c;
                seq^.max := seq^.tot*c;
              end
            else
              begin
                seq^.l := c;
                seq^.r := c;
                seq^.sum := seq^.tot*c;
                seq^.max := c;
              end;
            seq := seq^.suc;
          end;
        if seq^.v = 1 then makesam(seq);
        if seq^.t = 1 then reverse(seq);
        for i := 1 to tot-sub do seq^.a[i] := c;
        behalf(seq);
      end
    else
      begin
        for i := posi-now to posi-now+tot-1 do seq^.a[i] := c;
        behalf(seq);
      end;
    seq := head;
  end;

Procedure revers(var seq : link; posi,tot : longint); {O(|N)}
 var tmp : array[1..maxn] of longint;
     i   : longint;
  begin
    for i := posi to posi+tot-1 do tmp[i-posi+1] := seq^.a[i];
    for i := tot downto 1 do seq^.a[tot-i+posi] := tmp[i];
  end;

Procedure revover(var lef,rig : link); {O(|N)}
 var p,q,last : link;
     tmp : longint;
  begin
    p := lef^.pre; q := rig^.suc;
    p^.suc := rig; last := p;
    while rig <> lef do
      begin
        rig^.t := 1-rig^.t;
        tmp := rig^.l; rig^.l := rig^.r; rig^.r := tmp;
        rig^.suc := rig^.pre;
        rig^.pre := last;
        last := rig;
        rig := rig^.suc;
      end;
    rig^.t := 1-rig^.t;
    tmp := rig^.l; rig^.l := rig^.r; rig^.r := tmp;
    rig^.suc := q;
    rig^.pre := last;
    q^.pre := rig;
  end;

Procedure rev(posi,tot : longint); {O(|N)}
 var head,p,left,right : link;
     i,now,sub : longint;
  begin
    head := seq;
    now := 0;
    while (seq<>nil)and(now+seq^.tot<posi) do
      begin
        now := now + seq^.tot;
        seq := seq^.suc;
      end;
    if seq^.v = 1 then makesam(seq);
    if seq^.t = 1 then reverse(seq);
    if seq^.tot-(posi-now)+1 < tot then
      begin
        init(p,seq);
        for i := posi-now to seq^.tot do
          p^.a[i-(posi-now)+1] := seq^.a[i];
        p^.tot := seq^.tot-(posi-now)+1;
        behalf(p);
        p^.suc := seq^.suc;
        seq^.suc^.pre := p;
        seq^.tot := seq^.tot-p^.tot;
        behalf(seq);
        left := p;
        sub := p^.tot;
        seq^.suc := p;
        seq := seq^.suc^.suc;
        while (seq<>nil)and(sub+seq^.tot<tot) do
          begin
            sub := sub + seq^.tot;
            seq := seq^.suc;
          end;
        if sub+seq^.tot = tot then
            right := seq
        else
          begin
            if seq^.v = 1 then makesam(seq);
            if seq^.t = 1 then reverse(seq);
            init(p,seq);
            for i := tot-sub+1 to seq^.tot do
              p^.a[i-tot+sub] := seq^.a[i];
            p^.tot := seq^.tot-tot+sub;
            behalf(p);
            p^.suc := seq^.suc;
            seq^.suc^.pre := p;
            seq^.suc := p;
            seq^.tot := seq^.tot-p^.tot;
            behalf(seq);
            right := p^.pre;
          end;
        revover(left,right);
      end
    else
      begin
        revers(seq,posi-now,tot);
        behalf(seq);
      end;
    seq := head;
  end;

Function max_sum : longint; {O(|N)}
 var max,last,i : longint;
     head: link;
  begin
    head := seq;
    last := 0;
    max := -oo;
    while seq<>nil do
      begin
        if seq^.l+last>max then max := seq^.l+last;
        if seq^.max > max then max := seq^.max;
        if last+seq^.sum < seq^.r
          then last := seq^.r
          else last := last+seq^.sum;
        seq := seq^.suc;
      end;
    seq := head;
    max_sum := max;
  end;

Function get_sum(posi,tot : longint) : longint; {O(|N)}
 var head : link;
     sum,i,now,plus  : longint;
  begin
    head := seq;
    sum := 0; now := 0;
    while (seq<>nil)and(seq^.tot+now < posi) do
      begin
        now := now + seq^.tot;
        seq := seq^.suc;
      end;
    if seq^.v = 1 then makesam(seq);
    if seq^.t = 1 then reverse(seq);
    plus := 0;
    if plus < tot then
    for i := posi - now to seq^.tot do
      begin
        sum := sum + seq^.a[i];
        inc(plus); if plus = tot then break;
      end;
    seq := seq^.suc;
    while (seq<>nil)and(plus+seq^.tot<tot) do
      begin
        plus := plus + seq^.tot;
        sum := sum + seq^.sum;
        seq := seq^.suc;
      end;
    if seq <> nil then
      begin
        if seq^.v = 1 then makesam(seq);
        if seq^.t = 1 then reverse(seq);
        now := 0;
        while plus < tot do
          begin
            inc(plus);
            inc(now);
            inc(sum,seq^.a[now]);
          end;
      end;
    seq := head;
    get_sum := sum;
  end;

begin
  assign(input,fin); reset(input);
  assign(output,fou); rewrite(output);
  readln(n,m);
  seq := nil;
  for i := 1 to n do read(sequence[i]); readln;
  ins(0,n);
  for i := 1 to m do
    begin
      read(ch);
      case ch of
        'I' : begin
                read(ch,ch,ch,ch,ch);
                read(posi,tot);
                for j := 1 to tot do read(sequence[j]);
                ins(posi,tot);
                readln;
              end;
        'D' : begin
                read(ch,ch,ch,ch,ch);
                readln(posi,tot);
                del(posi,tot);
              end;
        'M' : begin
                read(ch,ch);
                case ch of
                  'K' : begin
                          read(ch,ch,ch,ch,ch,ch);
                          readln(posi,tot,c);
                          sam(posi,tot,c);
                        end;
                  'X' : begin
                          readln;
                          writeln(max_sum);
                        end;
                end;
              end;
        'R' : begin
                read(ch,ch,ch,ch,ch,ch);
                readln(posi,tot);
                rev(posi,tot);
              end;
        'G' : begin
                read(ch,ch,ch,ch,ch,ch);
                readln(posi,tot);
                writeln(get_sum(posi,tot));
              end;
      end;
      if i mod 10 = 0 then merge;
    end;
  close(input); close(output);
end.
