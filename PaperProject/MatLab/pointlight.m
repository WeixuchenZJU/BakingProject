%µ„π‚‘¥
N=100;
x=-0.5:1/N:0.5;
z=x;
[X,Z]=meshgrid(x,z);
Y=0.25./sqrt(X.^2+Z.^2+0.25);
surf(X,Z,Y)
% x=x';
% y=zeros(N+1,1);
% z=-0.5:1/N:0.5;
% z=z';
% lightpos=[0,0.5,0];
% lightcolor=[1,0,0];
% fragpos=[x,y,z];
% fragnorm=[0,1,0];
% fragcolor=zeros(N+1,3);
% for i=1:N+1
% fragcolor(i,:)=dot(norm(lightpos-fragpos(i,:)),fragnorm)*lightcolor;
% end
% y=1./sqrt(4*t.^2-8*t+5);
% theta=acos(y);
% plot(t,y,'r');
% hold on;
% plot(theta,y,'g');
% hold on;
% tt=0:1/N:1;
% yy=(y(N+1)-y(1))*(tt-t(1))/(tt(N+1)-tt(1))+y(1);
% plot(tt,yy,'b');
% x = -2:0.2:2;
% 
% y = x;
% 
% [X, Y] = meshgrid(x,y);
% 
% Z = -3*X + 2*Y;
% 
% 
