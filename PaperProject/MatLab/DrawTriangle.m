function [] = DrawTriangle(v0,v1,v2)
%DRAWTRIANGLE 此处显示有关此函数的摘要
%   此处显示详细说明
% outputArg1 = inputArg1;
% outputArg2 = inputArg2;
plot3(v0(1),v0(2),v0(3),'or');
hold on;
plot3(v1(1),v1(2),v1(3),'og');
hold on;
plot3(v2(1),v2(2),v2(3),'ob');
hold on;

x=[v0(1),v1(1),v2(1),v0(1)];
y=[v0(2),v1(2),v2(2),v0(2)];
z=[v0(3),v1(3),v2(3),v0(3)];
plot3(x,y,z,'LineWidth',2);
end

