function [bc] = RandomUniforSampleTri(v0,v1,v2,N)
%RANDOMUNIFORSAMPLETRI 此处显示有关此函数的摘要
%   此处显示详细说明
 %   在三角形上均匀采样并绘制点
 %在矩形内均匀采样
    %使用海伦公式求三角形的面积
     ea=norm(v2-v1);
     eb=norm(v2-v0);
     ec=norm(v1-v0);
     em=ea;
     %找到最长的边
     if(ea>eb)
         %如果ea最大 不用调整顶点顺序
        if(ea>ec)
            %否则ec最大，调整顶点顺序 
        else
          temp=v0;
          v0=v2;
          v2=v1;
          v1=temp;
          em=ec;
        end
     else
         if(eb>ec)
            temp=v0;
            v0=v1;
            v1=v2;
            v2=temp;  
            em=eb;
         else
            temp=v0;
            v0=v2;
            v2=v1;
            v1=temp; 
            em=ec;
         end
     end
     %求两个邻边的中点
     p01=(v0+v1)/2;
     p02=(v0+v2)/2;
    %p=ea+eb+ec;
    %p=p/2;
   % area=sqrt(p*(p-ea)*(p-eb)*(p-ec));
    tc=((v2(1)-v0(1))*(v2(1)-v1(1))+(v2(2)-v0(2))*(v2(2)-v1(2))+(v2(3)-v0(3))*(v2(3)-v1(3)))/((v2(1)-v1(1))*(v2(1)-v1(1))+(v2(2)-v1(2))*(v2(2)-v1(2))+(v2(3)-v1(3))*(v2(3)-v1(3)));
    ptc=tc*v1+(1-tc)*v2;
    h=v0-ptc;
    eh=norm(h);
    bc=[];
    count=0;
    A=[v0(1)-v2(1),v0(2)-v2(2),v0(3)-v2(3);v1(1)-v2(1),v1(2)-v2(2),v1(3)-v2(3)]';
    em
    h
    %垂直于三角形的向量ej
    ej=cross(v1-v0,v2-v0);
for i=1:N 
    s=rand();%高方向采样
    t=rand();%底方向采样
    sp=v1+s*h+t*(v2-v1);
    %判断采样点是否在三角形内部
    if(IsInTriangle(v0,v1,v2,sp))
         plot3(sp(1),sp(2),sp(3),'oc');
         %根据采样点计算重心坐标
         b=[sp(1)-v2(1),sp(2)-v2(2),sp(3)-v2(3)]';
         count=count+1;
         bc(:,count)=A\b ;
    else
        %判断采样点和高的位置关系
        if(dot(cross(sp-ptc,h),ej)>0)
            sp=2*p02-sp;
        else
            sp=2*p01-sp;
        end
         plot3(sp(1),sp(2),sp(3),'oc');
         b=[sp(1)-v2(1),sp(2)-v2(2),sp(3)-v2(3)]';
         count=count+1;
         bc(:,count)=A\b ;
    end
   % sp=SampleOnTri(v0,v1,v2,s,t);
   
    
    
%     错误的采样方法
   
end
end

