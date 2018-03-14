function [p] = SampleOnTri(v0,v1,v2,s,t)
%SAMPLEONTRI 此处显示有关此函数的摘要
%   此处显示详细说明
%   根据重心坐标在三角形上采样
p=s*v0+t*v1+(1-s-t)*v2;
end

