function bo = omg_check(mtx)
    % -------------- �������˵�� --------------
    
    %   ��������У�mtxΪͼ���ľ������������ĸ�ʽ��
    %   [ 1 2 3;
    %     0 2 1;
    %     3 0 0 ]
    %   ��ͬ�����ִ�����ͬ��ͼ����0����˴�û�п顣
    %   ������[m, n] = siz(mtx)��ȡ������������
    
    %   ע��mtx��������Ϸ�����ͼ����λ�ö�Ӧ��ϵ���±�(x1, y1)��������������
    %   ������������½�Ϊԭ�㽨������ϵ��x�᷽���x1����y�᷽���y1��
    
    % --------------- �������˵�� --------------- %
    
    %   Ҫ�����ó��Ĳ����������steps������,��ʽ���£�
    %   steps(1)��ʾ��������
    %   ֮��ÿ�ĸ���x1 y1 x2 y2�������mtx(x1,y1)��mtx(x2,y2)��ʾ�Ŀ�������
    %   ʾ���� steps = [2, 1, 1, 1, 2, 2, 1, 3, 1];
    %   ��ʾһ������������һ����mtx(1,1)��mtx(1,2)��ʾ�Ŀ�������
    %   �ڶ�����mtx(2,1)��mtx(3,1)��ʾ�Ŀ�������
    
    %% --------------  �������������Ĵ��� O(��_��)O~  ------------
    
    mtx_tmp=zeros(size(mtx));
    siz=max(max(mtx));
    count=0;
    while(siz~=0)
        for i=1:siz
            [m,n]=find(mtx==i);
            for j=1:length(m)
                for k=j+1:length(n)   
                    if mtx(m(j),n(j))~=0&&mtx(m(k),n(k))~=0;
                       if detect(mtx,m(j),n(j),m(k),n(k))==1
                            count=count+1;
                            mtx(m(j),n(j))=0;
                            mtx(m(k),n(k))=0;
                        end
                    end
                end
            end
        end
        siz=max(max(mtx));
        if(mtx_tmp==mtx)
            bo=0;
            return;
        end
        mtx_tmp=mtx;%������ѭ��
    end
    bo=1;
    return;
end
