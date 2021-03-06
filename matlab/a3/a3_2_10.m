clear;clc;close all;
load('jpegcodes');
load('hall');
load('JpegCoeff');

%判断DC
i=1;
DC=[];
%解码至残差
while(i<=length(DCstream))
    for ca=1:12
        try%可能存在DCstream不够长的情况
            if(DCstream(i:i+DCTAB(ca,1)-1)==DCTAB(ca,2:1+DCTAB(ca,1)));
                i=i+DCTAB(ca,1);
                if(ca==1)
                    DC=[DC 0];
                    i=i+1;
                    break
                elseif(DCstream(i)==1)
                    %此处为ca(Category的序号)与数字位数的对应关系
                    DC=[DC bin2dec(num2str(DCstream(i:i+ca-2)))];
                else
                    DC=[DC -bin2dec(num2str(~DCstream(i:i+ca-2)))];
                end
                i=i+ca-1;
                break;
            end
        end
    end
end
%恢复至量化
for i=2:length(DC)
    DC(i)=DC(i-1)-DC(i);
end
%判断AC
i=1;count=1;
AC=zeros(63,length(DC));tmp=[];
%解码至zig-zag前
while(i<=length(ACstream))
        %判断EOB
        if(ACstream(i:i+3)==[1 0 1 0])
            i=i+4;
            AC(:,count)=[tmp;zeros(63-length(tmp),1)];
            tmp=[];
            count=count+1;
            continue;
        end
        %判断ZRL
        if((i+10)<=length(ACstream))
            if(ACstream(i:i+10)==[1 1 1 1 1 1 1 1 0 0 1])
                i=i+11;
                tmp=[tmp;zeros(16,1)];
                continue;
            end
        end
        for j=1:160
            %避免溢出
            try
                if(ACstream(i:i+ACTAB(j,3)-1)==ACTAB(j,4:3+ACTAB(j,3)));
                    i=i+ACTAB(j,3);
                    Run=fix((j-1)/10);
                    if(ACstream(i)==1)
                        %此处为run/size与数字位数的对应关系
                        tmp=[tmp;zeros(Run,1);bin2dec(num2str(ACstream(i:i+j-10*Run-1)))];
                else
                    tmp=[tmp;zeros(Run,1);-bin2dec(num2str(~ACstream(i:i+j-10*Run-1)))];
                end
                i=i+j-10*Run;
                break;
            end
        end
    end
end
%反zigzag
source=[DC;AC];
%C为最终数据
pic=zeros(m,n);
M=ceil(m/8);N=ceil(n/8);
for i=1:M
    for j=1:N
        %量化
        pic(i*8-7:i*8,j*8-7:j*8)=izigzag(source(:,i*N-N+j));
        pic(i*8-7:i*8,j*8-7:j*8)=idct2(pic(i*8-7:i*8,j*8-7:j*8).*QTAB)+128;
        %zig-zag
    end
end
pic=uint8(pic);
subplot(1,2,1)
imshow(hall_gray);
title('origin');
subplot(1,2,2);
imshow(pic);
title('decode');

MSR=1/(m*n)*sum(sum((pic-hall_gray).^2));
PSNR=10*log10(255^2/MSR)
