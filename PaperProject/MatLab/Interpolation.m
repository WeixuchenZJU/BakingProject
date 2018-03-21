for i=1:1
tri0=load(strcat(strcat('..\\BakingData\\cube\\t',num2str(i-1,'%d')),'.txt'));
vv0= tri0(1,3:5)';
vv1=tri0(2,3:5)';
vv2=tri0(3,3:5)';
%将三维空间上的点投影到xoy平面上
v0=[0,0,0]';
v1=[norm(vv1-vv0),0,0]';
e12=norm(vv2-vv1);
e02=norm(vv2-vv0);
a=v1(1);
c=(e02*e02-e12*e12+a*a)/(2*a);
b=sqrt(e02*e02-c*c);
v2=[c,b,0]';
% subplot(3,4,i);
DrawTriangle(v0,v1,v2);
    for j=4:10204
        s=tri0(j,1);
        t=tri0(j,2);
        sp=s*v0+t*v1+(1-s-t)*v2;
        plot3(sp(1),sp(2),tri0(j,3),'.','Color',tri0(j,3:5));
    end
end

% [sp,v0,v1,v2]=UniformSampleTri(v0,v1,v2,2000);
% p01=(v0+v1)/2;
% p12=(v1+v2)/2;
% p02=(v0+v2)/2;
% p01(3)=5;
% p02(3)=10;
% p12(3)=7;
% hold on;
% %画控制点
% plot3(p01(1),p01(2),p01(3),'or');
% hold on;
% plot3(p02(1),p02(2),p02(3),'or');
% hold on;
% plot3(p12(1),p12(2),p12(3),'or');
% hold on;
% %根据控制点确定的曲面形状采样
% for i=1:length(sp)
% spp=Bezier2nd(sp(1,i),sp(2,i),v0,p01,v1,p12,v2,p02);
% plot3(spp(1),spp(2),spp(3),'xg');
% hold on;
% end

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


