function [] = UniformSampleBC(A,B,C,N)
%UNIFORMSAMPLEBC 根据重心坐标采样三角形内的点
%   此处显示详细说明
% Method 1
subplot(1,2,2);
DrawTriangle(A,B,C);
for i=1:N
%     s=i/N;
%     t=i/N;
    s=rand();
    t=rand();
%     a=1-sqrt(t);
%     b=(1-s)*sqrt(t);
%     c=s*sqrt(t);
if s+t>1
    s=1-s;
    t=1-t;
end
a=1-s-t;
b=s;
c=t;
    sp=a*A+b*B+c*C;
    plot3(sp(1),sp(2),sp(3),'.r');
    hold on;
end
subplot(1,2,1);
DrawTriangle(A,B,C);
for i=1:N
%     s=i/N;
%     t=i/N;
    s=rand();
    t=rand();
    a=1-sqrt(t);
    b=(1-s)*sqrt(t);
    c=s*sqrt(t);
    sp=a*A+b*B+c*C;
    plot3(sp(1),sp(2),sp(3),'.g');
    hold on;
end
end

