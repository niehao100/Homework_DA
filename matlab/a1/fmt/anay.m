clc;clear;close all;
freq=[];time=[];A=[];
%freq �洢ÿ�εĻ�����г��Ƶ��
%time �洢ÿ������ʱ��
%A    �洢ÿ�λ�����г�������
for i=2:32
    [freq,time,A]=f_f(freq,time,['fmt (' num2str(i) ').wav'],A);
end

note=round(log2(freq(1,:)/220)*12);