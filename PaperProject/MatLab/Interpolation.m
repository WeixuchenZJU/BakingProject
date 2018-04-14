for i=1:1
tri0=load(strcat(strcat('F:\\FinalProject\\PaperProject\\BakingData\\triangle\\t',num2str(i-1,'%d')),'.txt'));
vv0= tri0(1,3:5)';
vv1=tri0(2,3:5)';
vv2=tri0(3,3:5)';
%����ά�ռ��ϵĵ�ͶӰ��xoyƽ����
v0=[0,0,0]';
v1=[norm(vv1-vv0),0,0]';
e12=norm(vv2-vv1);
e02=norm(vv2-vv0);
a=v1(1);
c=(e02*e02-e12*e12+a*a)/(2*a);
b=sqrt(e02*e02-c*c);
v2=[c,b,0]';
% subplot(3,4,i);
%UniformSampleBC(v0,v1,v2,100);
DrawTriangle(v0,v1,v2);
A=zeros(3);
A2=zeros(6);
b=[0,0,0]';
b2=[0,0,0,0,0,0]';
    for j=4:length(tri0)
        s=tri0(j,1);
        t=tri0(j,2);
        u=1-s-t;
        sp=s*v0+t*v1+u*v2;
        h1=[s,t,u]';
        h2=[s^2,t^2,u^2,s*t,s*u,t*u]';
        Ai=h1*h1';
        A2i=h2*h2';
        A=A+Ai;
        A2=A2+A2i;
        bi=tri0(j,3)*h1;
        b2i=tri0(j,3)*h2;
        b=b+bi;
        b2=b2+b2i;
        plot3(sp(1),sp(2),tri0(j,3),'.','Color',[1,1,1]-tri0(j,3:5));
        hold on;
    end
    A;
    x=A\b;
    x2=A2\b2;
    vvv0=[v0(1),v0(2),x(1)];
    vvv1=[v1(1),v1(2),x(2)];
    vvv2=[v2(1),v2(2),x(3)];
    DrawTriangle(vvv0,vvv1,vvv2);
    %2nd Bezier
     for j=4:length(tri0)
        s=tri0(j,1);
        t=tri0(j,2);
        u=1-s-t;
        sp=s*v0+t*v1+u*v2;
        bezier2nd=Bezier2nd(s,t,x2(1),x2(2),x2(3),x2(4),x2(5),x2(6));
        plot3(sp(1),sp(2),bezier2nd,'.','Color',[1,0,0]);
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
% %�����Ƶ�
% plot3(p01(1),p01(2),p01(3),'or');
% hold on;
% plot3(p02(1),p02(2),p02(3),'or');
% hold on;
% plot3(p12(1),p12(2),p12(3),'or');
% hold on;
% %���ݿ��Ƶ�ȷ����������״����
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


