function [in] = IsInTriangle(A,B,C,P)
%ISINTRIANGLE 此处显示有关此函数的摘要
%   判断点p是否在三角形内
PA=A-P;
PB=B-P;
PC=C-P;
%判断三个叉积
CPA=cross(PA,B-A);
CPB=cross(PB,C-B);
CPC=cross(PC,A-C);
% CPA=CPA/norm(CPA);
% CPB=CPB/norm(CPB);
% CPC=CPC/norm(CPC);
dot(CPA,CPB);
dot(CPA,CPC);
dot(CPC,CPB);
if(dot(CPA,CPB)<0||dot(CPC,CPB)<0||dot(CPA,CPC)<0)
    in=0;
else
    in=1;
end
end

