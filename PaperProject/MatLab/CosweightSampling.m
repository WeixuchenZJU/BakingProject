% phi=0:pi/50:pi/2;
% theta=0:pi/50:2*pi;
% [pp,tt]=meshgrid(phi,theta);
% x=sin(pp).*cos(tt);
% y=sin(pp).*sin(tt);
% z=cos(pp);
% mesh(x,y,z);
% hold on;
% plot3(0,0,0,'go');
% hold on;
for i=1:256
phi=rand()*2*pi;
theta=asin(sqrt(rand()));
psi=[cos(phi)*sin(theta),sin(phi)*sin(theta),cos(theta)];
DrawLine([0,0,0],psi);
hold on;
end