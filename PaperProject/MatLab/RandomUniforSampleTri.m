function [bc] = RandomUniforSampleTri(v0,v1,v2,N)
%RANDOMUNIFORSAMPLETRI �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
 %   ���������Ͼ��Ȳ��������Ƶ�
 %�ھ����ھ��Ȳ���
    %ʹ�ú��׹�ʽ�������ε����
     ea=norm(v2-v1);
     eb=norm(v2-v0);
     ec=norm(v1-v0);
     em=ea;
     %�ҵ���ı�
     if(ea>eb)
         %���ea��� ���õ�������˳��
        if(ea>ec)
            %����ec��󣬵�������˳�� 
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
     %�������ڱߵ��е�
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
    %��ֱ�������ε�����ej
    ej=cross(v1-v0,v2-v0);
for i=1:N 
    s=rand();%�߷������
    t=rand();%�׷������
    sp=v1+s*h+t*(v2-v1);
    %�жϲ������Ƿ����������ڲ�
    if(IsInTriangle(v0,v1,v2,sp))
         plot3(sp(1),sp(2),sp(3),'oc');
         %���ݲ����������������
         b=[sp(1)-v2(1),sp(2)-v2(2),sp(3)-v2(3)]';
         count=count+1;
         bc(:,count)=A\b ;
    else
        %�жϲ�����͸ߵ�λ�ù�ϵ
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
   
    
    
%     ����Ĳ�������
   
end
end

