function [s]=m_note_3(note,time,base,f)
    %�������
    %note����
	%between-5~25
	%-10 means an empty beat 
    %time����ʱ��
    %base����
    %f����Ƶ��
    %s�����ź�
    n=-5:19;    
    freq=base*2.^kron(1/12,n);
    t=((1:(time)*f)/f)';
    if note==-10
        s=0*t;
    else
        e=(t<0.1*time).*(t-0.1*time)*80+(t>=0.1*time&t<0.15*time).*(0.1*time-t)*4.46/time-(t>=0.15*time&t<0.95*time)*0.223+(t>=0.9*time).*((0.9*time-t)*40-0.223);
        %exp(e)Ϊָ������     
        s=exp(e).*(cos(2*pi*freq(6+note)*t)+0.2*cos(2*pi*2*freq(6+note)*t)+0.3*cos(2*pi*3*freq(6+note)*t));
    end
    return 
