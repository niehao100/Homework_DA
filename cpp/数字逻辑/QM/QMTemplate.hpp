// ʹ���Լ��ġ�ѧ�š��滻���е�2013011280
// ʹ���Լ��ġ��������滻��������
//
// QMTemplate.hpp��ʹ�ã�
// ֱ�Ӱ�QMTemplate.hpp������ͨͷ�ļ���ʹ�þͿ����ˡ�ʵ����hpp����.cpp��.h�ĺϲ���
#ifndef _QM2013011280_HPP_
#define _QM2013011280_HPP_
#define INF=0xffffffffffffffff;
#include <string>
#include <vector>
class QM201301180
{
public:
	static std::string Name()
	{
		// �����Լ�������
		return "����";
	}

	static std::string StudentID()
	{
		// �����Լ���ѧ��
		return "201301180";
	}

	// QM����
	// ���룺
	// 	��С������m, m_count
	// 	�޹�������d, d_count
	// ���أ�
	// 	�����ʽ
	//  ����У����ʱ�ԭ�̺�����ǰ�������ں����������е�����԰��ձ��������Ӹߵ������С�ÿһ���и�
    //  λ������ǰ����λ�����ں󡣸ߵ�λ����������ABC��������
	static std::string QM(const unsigned int* m, unsigned int m_count, 
			const unsigned int* d, unsigned int d_count) 
	{
		std::string retval;
		std::vector<unsigned char> *bit=new std::vector<unsigned char>(m_count);
		int tmp=0,i=0,j=0;
		QM201301180::flag_max=0;
		QM201301180::FindHighbit(bit[0],m[m_count-1]);
		QM201301180::FindHighbit(bit[0],d[d_count-1]);
		//
		//
		// �������Լ����㷨
		//
        //
		return retval;
	}

	static std::vector<int> FindHighbit(std::vector<unsigned char> &bit, const unsigned int m){
		int tmp = 0x8000000000000000,flag=0;
		for(;tmp!=0;tmp=(int)(tmp/2)){
			if((m&tmp)!=0) 
				flag++;
			if(flag!=1)
				bit.push_back((m&tmp)!=0);
		}
		if(flag>QM201301180::flag_max) flag==flag_max;
	}

	static std::vector<int> Rebit(std::vector<unsigned char> &bit, const unsigned int m){
		int tmp = 0,i=0;
		for(i=flag_max;i>-1;tmp=1<<i)
			bit.push_back((m&tmp)!=0);
	}
	// �Լ���ӵĳ�Ա����������static�������ſ��Ժܺõ����QM����������
	static int flag_max;
};

#endif
