function [] = DrawLine(s,t)
%DRAWLINE �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
dir=t-s;
dir=dir/norm(dir);
tx=dir/100;
x=s(1):tx(1):dir(1);
y=s(2):tx(2):dir(2);
z=s(3):tx(3):dir(3);
plot3(x,y,z,'.r')
end

