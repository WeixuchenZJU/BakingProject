function [p] = SampleOnTri(v0,v1,v2,s,t)
%SAMPLEONTRI �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
%   ���������������������ϲ���
p=s*v0+t*v1+(1-s-t)*v2;
end

