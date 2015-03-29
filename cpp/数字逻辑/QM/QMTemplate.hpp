// ʹ���Լ��ġ�ѧ�š��滻���е�2013011280
// ʹ���Լ��ġ��������滻��������
//
// QMTemplate.hpp��ʹ�ã�
// ֱ�Ӱ�QMTemplate.hpp������ͨͷ�ļ���ʹ�þͿ����ˡ�ʵ����hpp����.cpp��.h�ĺϲ���
#ifndef _QM2013011280_HPP_
#define _QM2013011280_HPP_
#define INF 0xffffffffffffffff;
#include <string>
#include <vector>
#include <iostream>
#include<algorithm>
using std::vector;
using std::string;
using std::sort;
using std::unique;
using std::find;
using std::count;

class QM2013011280
{
public:
	static string Name()	{
		// �����Լ�������
		return "����";
	}

	static string StudentID(){
		// �����Լ���ѧ��
		return "2013011280";
	}

	// QM����
	// ���룺
	// 	��С������m, m_count
	// 	�޹�������d, d_count
	// ���أ�
	// 	�����ʽ
	//  ����У����ʱ�ԭ�̺�����ǰ�������ں����������е�����԰��ձ��������Ӹߵ������С�ÿһ���и�
	//  λ������ǰ����λ�����ں󡣸ߵ�λ����������ABC��������
	static string QM(const unsigned int* m, unsigned int m_count, 
		const unsigned int* d, unsigned int d_count) {
			string retval,tstring;
			vector<vector<unsigned char>> bit,prime_implicant,
				essential_prime_implicant,size2,size4,size8,size16;//�洢�����ƻ�����,���̺�����ʱ�Դ�̺���,���˸����������Ե�size8����
			vector<unsigned char> cover;
			int i=0,j=0,is_d=0;//ѭ���ñ���

			//ȷ��������
			if(m_count)
				QM2013011280::FindHighbit(m[m_count-1]);
			if(d_count)
				QM2013011280::FindHighbit(d[d_count-1]);
			//�����ƻ���vector�����һ�����洢�����Ƶ�0�ĸ���

			for(is_d=0;is_d<d_count+1;is_d++){
				essential_prime_implicant.clear();
				prime_implicant.clear();
				size2.clear();
				size4.clear();
				size8.clear();
				size16.clear();
				bit.clear();
				for(i=0;i<m_count;i++){
					bit.push_back(Rebit(m[i]));
					cover.push_back(m[i]);
				}
				for(i=is_d;i<d_count;i++){
					bit.push_back(Rebit(d[i]));
					cover.push_back(d[i]);
				}

				search_prime_implicant(bit,size2,prime_implicant);
				sort(size2.begin(),size2.end());
				size2.erase(unique(size2.begin(),size2.end()),size2.end());

				search_prime_implicant(size2,size4,prime_implicant);
				sort(size4.begin(),size4.end());
				size4.erase(unique(size4.begin(),size4.end()),size4.end());

				search_prime_implicant(size4,size8,prime_implicant);
				sort(size8.begin(),size8.end());
				size8.erase(unique(size8.begin(),size8.end()),size8.end());

				search_prime_implicant(size8,size16,prime_implicant);
				sort(size16.begin(),size16.end());
				size16.erase(unique(size16.begin(),size16.end()),size16.end());

				sort(prime_implicant.begin(),prime_implicant.end());

				prime_implicant.erase(unique(prime_implicant.begin(),prime_implicant.end()),prime_implicant.end());
				//�������ʱ�Դ�̺�
				int tmp=0,is_epi=0;
				for(;!cover.empty();){
					for(i=0;i<cover.size()&&(!cover.empty());i++){
						for(j=0;j<prime_implicant.size()&&(!cover.empty());j++){
							if(prime_implicant[j].end()
								!=find((prime_implicant[j]).begin()+flag_max+1,
								(prime_implicant[j]).end(),cover[i])){
									tmp=j;
									is_epi++;
							}
						}
						if(j)	j--;
						if(is_epi==1)
							cover_one(prime_implicant,essential_prime_implicant,cover,j);
						j=0;
					}
					sort(prime_implicant.begin(),prime_implicant.end());
					for(j=0;j<prime_implicant.size()&&(!cover.empty());j++){
						if(prime_implicant[j].end()
							!=find((prime_implicant[j]).begin()+flag_max+1,
							(prime_implicant[j]).end(),cover[0])){

								cover_one(prime_implicant,essential_prime_implicant,cover,j);	
						}
					}
				}
				sort(essential_prime_implicant.begin(),essential_prime_implicant.end());
				for(i=essential_prime_implicant.end()-essential_prime_implicant.begin()-1;
					i>-1;i--){
						char a='A';
						for(j=0;j<flag_max;j++,a++){						
							switch(essential_prime_implicant[i][j]){
							case 1:tstring+=a;break;
							case 0:tstring+=a;tstring+="'";break;
							default:break;
							}
						}
						if(i&&!tstring.empty()) tstring+="+";
				}

				if(tstring.empty()) tstring='1';
				if(is_d==0) retval=tstring;
				if(count(tstring.begin(),tstring.end(),'+')<count(retval.begin(),retval.end(),'+')) retval=tstring;
				tstring.clear();
			}

			return retval;
	}

	static void FindHighbit(const unsigned int m){
		int flag=0,i=31;
		unsigned tmp = 1<<31;
		for(;i>-1;i--){
			tmp=1<<i;
			if((m&tmp)!=0) {
				flag=i+1;
				break;
			}
		}
		if(flag>flag_max)  flag_max=flag;
	}

	static vector<unsigned char> Rebit(const unsigned int m){
		unsigned int tmp = 0;
		int i=0,flag=0,count1=0;
		vector<unsigned char> bit;
		for(i=flag_max-1;i>-1;i--){
			tmp=1<<i;
			bit.push_back((m&tmp)!=0);
			if((m&tmp)==0) 
				count1++;
		}
		bit.push_back(count1);
		bit.push_back(m);
		return bit;
	}

	static vector<unsigned char> merge
		(vector<vector<unsigned char>>& bit,int bit1,int bit2){
			int count_diff=0,diff=0,i=0;
			vector<unsigned char> tmp;
			for(i=0;i<flag_max;i++){
				if(bit[bit1][i]==bit[bit2][i]){
					count_diff++;
				}
				else diff=i;
			}
			if(count_diff==(flag_max-1)){
				tmp=bit[bit1];
				if(tmp[diff]==0) 
					tmp[flag_max]-=1;
				tmp[diff]=5;
				for(i=flag_max+1;bit[bit2].begin()+i<bit[bit2].end();i++)
					tmp.push_back(bit[bit2][i]);
				sort(tmp.begin()+flag_max+1,tmp.end());
				tmp.erase(unique(tmp.begin()+flag_max+1,tmp.end()),tmp.end());
			}
			return tmp;
	}

	static void search_prime_implicant
		(vector<vector<unsigned char>>&bit,vector<vector<unsigned char>>& size,
		vector<vector<unsigned char>>&prime_implicant){//�������̺��һ����
			vector<unsigned char> tmp;
			int is_epi,i=0,j=0;
			if(bit.size()==1) {
				prime_implicant.push_back(bit[0]);
				return;
			}
			for(i=0,is_epi=1;i<(bit.size());i++){
				for(j=0;j<bit.size();j++){
					tmp=merge(bit,i,j);
					if(!tmp.empty())	{
						is_epi=0;
						if(j>i)
							size.push_back(tmp);
					}
				}
				if(is_epi==1) 
					prime_implicant.push_back(bit[i]);
				is_epi=1;
			}	
	}	


	static void cover_one(vector<vector<unsigned char>>& prime_implicant,
		vector<vector<unsigned char>>& essential,
		vector<unsigned char>&cover,int count){
			essential.push_back(prime_implicant[count]);
			for(int i=flag_max+1;i<(prime_implicant[count]).size()&&(!cover.empty());i++)
				if(find(cover.begin(),cover.end(),prime_implicant[count][i])!=cover.end())
					cover.erase(find(cover.begin(),cover.end(),prime_implicant[count][i]));
			prime_implicant.erase(prime_implicant.begin()+count);
	}

	static int flag_max;
};
bool operator< (vector<unsigned char> a,vector<unsigned char> b){
	return count(a.begin(),a.begin()+QM2013011280::flag_max-1,5)
		<count(a.begin(),a.begin()+QM2013011280::flag_max-1,5);
}
bool operator== (vector<unsigned char> a,vector<unsigned char> b){
	int count_diff=0,diff=0,i=0;
	vector<unsigned char> tmp;
	for(i=0;i<QM2013011280::flag_max;i++){
		if(a[i]==b[i]){
			count_diff++;
		}
	}
	return count_diff==QM2013011280::flag_max;

}
int QM2013011280::flag_max=0;


#endif
