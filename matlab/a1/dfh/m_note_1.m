function m_note_1(note,time,base,f)
    %�������
    %note����,
	%between -5~25,
	%-10 means an empty beat 
    %time����ʱ��
    %base����
    %f����Ƶ��
    n=[-5:19];
    freq=base*2.^kron(1/12,n);
    t=[0:time*f]/f;
    if note==10
        s=0*t;
    else
        s=cos(2*pi*freq(note+6)*t);
        sound(s,f);
        pause(time+0.01);
    end
    return 
