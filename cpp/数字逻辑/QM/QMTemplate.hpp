// ʹ���Լ��ġ�ѧ�š��滻���е�2013011280
// ʹ���Լ��ġ��������滻��������
//
// QMTemplate.hpp��ʹ�ã�
// ֱ�Ӱ�QMTemplate.hpp������ͨͷ�ļ���ʹ�þͿ����ˡ�ʵ����hpp����.cpp��.h�ĺϲ���
#ifndef _QM2013011280_HPP_
#define _QM2013011280_HPP_

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
		std::int tmp=0,i=0,j=0;
		
		//
		//
		// �������Լ����㷨
		//
        //
		return retval;
	}

	// �Լ���ӵĳ�Ա����������static�������ſ��Ժܺõ����QM����������

};

#endif
