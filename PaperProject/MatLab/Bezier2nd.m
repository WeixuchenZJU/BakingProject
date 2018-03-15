function [pst] = Bezier2nd(s,t,cp200,cp110,cp020,cp011,cp002,cp101)
%BEZIER2ND 此处显示有关此函数的摘要
%   此处显示详细说明
%i=2.j=0,l=0
B200=s^2;
B110=2*s*t;
B101=2*s*(1-s-t);
B020=t^2;
B011=2*t*(1-s-t);
B002=(1-s-t)^2;
pst=B200*cp200+B110*cp110+B101*cp101+B020*cp020+B011*cp011+B002*cp002;-
end

