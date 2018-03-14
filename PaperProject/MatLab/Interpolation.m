% % x=0:0.01:pi;
% % y=sin(x);
% % plot(x,y);
% t=0:0.01:1;
% % x = 1-t; 
% % y = t; 
% B1=(1-t).^3;
% B2=3*t.*((1-t).^2);
% B3=3*(t.^2).*(1-t);
% B4=t.^3;
% 
% plot(t,B1,t,B2,t,B3,t,B4);
% xlabel('t')
% text(0.09,0.8,'B_1(t)')
% text(0.84,0.8,'B_4(t)')
% text(0.29,0.46,'B_2(t)')
% text(0.64,0.46,'B_3(t)')
% subplot(1,3,1);
% plot(t,x,t,y);
% subplot(1,3,2);
% plot(t,x,t,y);
% subplot(1,3,3);
% plot(t,x,t,y);
v0=[1,0,0]';
v1=[0,0.5,0]';
v2=[0,-0.5,0]';
DrawTriangle(v0,v1,v2);
[sp,v0,v1,v2]=UniformSampleTri(v0,v1,v2,2000);
p01=(v0+v1)/2;
p12=(v1+v2)/2;
p02=(v0+v2)/2;
p01(3)=5;
p02(3)=10;
p12(3)=7;
hold on;
%画控制点
plot3(p01(1),p01(2),p01(3),'or');
hold on;
plot3(p02(1),p02(2),p02(3),'or');
hold on;
plot3(p12(1),p12(2),p12(3),'or');
hold on;
%根据控制点确定的曲面形状采样
for i=1:length(sp)
spp=Bezier2nd(sp(1,i),sp(2,i),v0,p01,v1,p12,v2,p02);
plot3(spp(1),spp(2),spp(3),'xg');
hold on;
end
%计算采样点处的颜色
% 
% plot3(v0(1),v0(2),v0(3),'or');
% hold on;
% plot3(v1(1),v1(2),v1(3),'og');
% hold on;
% plot3(v2(1),v2(2),v2(3),'ob');
% hold on;
% % 
% x=[v0(1),v1(1),v2(1)];
% y=[v0(2),v1(2),v2(2)];
% z=[v0(3),v1(3),v2(3)];
% plot3(x,y,z);


