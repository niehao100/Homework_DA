run anay.m;
%���ȸ�Ϊ��� 220Hz Ϊ��׼��
f=round(log2(freq(1,:)/220)*12);
%������Ϊ����
[C,I]=sort(f);
A_tmp=zeros(6,18);
tmp=C(1);count=0;
%���ظ�����Ƶ������ȡƽ��
for i=1:31
    if C(i)==tmp;
        A_tmp(:,C(i)+6)=A_tmp(:,C(i)+6)+A(:,I(i));
        count=count+1;
    else
        A_tmp(:,C(i-1)+6)=(A_tmp(:,C(i-1)+6)+A(:,I(i-1)))/count;
        tmp=C(i);
        count=1;
    end
end
A_tmp(:,C(31)+6)=A(:,I(31));
%�����ڵ�������������������ƽ��ֵ���
for i=1:18
    if A_tmp(:,i)==0
        A_tmp(:,i)=(A_tmp(:,i+1)+A_tmp(:,i-1))/2;
    end
end

base=220;f=8000;s=zeros(f*0.05,1);
s=[s;m_note_guitar(10,0.5,base,f,A_tmp(:,10+6))];
s=[s;m_note_guitar(10,0.25,base,f,A_tmp(:,10+6))];
s=[s;m_note_guitar(12,0.25,base,f,A_tmp(:,12+6))];
s=[s;m_note_guitar(5,1,base,f,A_tmp(:,5+6))];
s=[s;m_note_guitar(3,0.5,base,f,A_tmp(:,3+6))];
s=[s;m_note_guitar(3,0.25,base,f,A_tmp(:,3+6))];
s=[s;m_note_guitar(0,0.25,base,f,A_tmp(:,0+6))];
s=[s;m_note_guitar(5,1,base,f,A_tmp(:,5+6))];
sound(s,f);
