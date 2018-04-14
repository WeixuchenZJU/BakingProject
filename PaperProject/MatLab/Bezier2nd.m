function [pst] = Bezier2nd(s,t,cp200,cp020,cp002,cp110,cp101,cp011)
%BEZIER2ND 此处显示有关此函数的摘要
%   此处显示详细说明
%i=2.j=0,l=0
u=1-s-t;
B200=s^2;
B110=s*t;
B101=s*u;
B020=t^2;
B011=t*u;
B002=u^2;
pst=B200*cp200+B110*cp110+B101*cp101+B020*cp020+B011*cp011+B002*cp002;
end

