#include		<iostream>
#include		<string>
#include		<stdio.h>
#include		<vector>
#include		<stdlib.h>
#include		"md5.h"
#include	    <windows.h>//for windows
#include		<conio.h>
using namespace std;

class Course
{
public:
	Course(string n="",char c=0,double g=-1,char p=-1){
		cname=n;
		credit=c;
		grade=g;
		pass=p;
	}
	Course(const Course &cp):grade(cp.Getgrade()),cname(cp.Getcname()),pass(cp.Getpass()),credit(cp.Getcredit()){}
	void Insertgrade(double g);
	void Insertgrade(unsigned char p) {pass=p;}
	double Getgrade() const {return grade;}
	string Getcname() const {return cname;}
	char Getpass()	const {return pass;}
	char Getcredit() const {return credit;}
	void Print(){
		cout<<cname<<":\t";
		if(grade!=-1)	cout<<grade;
		if(pass==1) 
			cout<<"\tͨ��\t";
		if(pass==2)
			cout<<"\t����\t";
		if(pass==3) 
			cout<<"\t����\t";
		if(pass==0)
			cout<<"\t������\t";
		if(pass==-1) 
			cout<<"\t����Ϣ\t";
	}
private:
	double grade;
	string cname;
	char pass;//1��ʾͨ����2���ã�3����
	char credit;
};

void	Course::Insertgrade(double g){
	grade=g;
	if(g>=80){
		if(g>=90) pass=3;
		else pass=2;
	}
	else{
		if(g>=60) pass=1;
		else pass=0;
	}
}

class Clist
{
public:
	Clist(vector<Course> cl):clist(cl){
		gpa=0;
		gmin=100;
		gmax=0;
		countcoures=0;
	}
	Clist(const Clist &cp):clist(cp.Getclist()),gmax(cp.Getgmax()),gmin(cp.Getgmin()),gpa(cp.Getgpa()),countcoures(cp.Getcountcoures()){}
	void Insertcourse(string cname,char c){
		Course tmp(cname,c,(double)-1,(char)-1);
		clist.push_back(tmp);
		countcoures++;
	}
	void Delcourse(int cno){
		clist.erase(clist.begin()+cno);  
	}
	void Insertgrade(vector<double> g)
	{
		for(int i=0;i<g.size();i++){
			clist[(int)g[i]/101].Insertgrade(g[i]-101*((int)g[i]/101));
			if((g[i]-(int)g[i]/101)<gmin) gmin=g[i]-101*((int)g[i]/101);
			if((g[i]-(int)g[i]/101)>gmax) gmax=g[i]-101*((int)g[i]/101);
			//���ɼ�����ʱд�� �γ̺�*101+�ɼ�����ʽ�����㴫��
		}
		Refreshgpa();
	}
	void Insertgrade(vector<unsigned char> p) 
	{
		for(int i=0;i<p.size();i++){
			clist[(int)p[i]/10].Insertgrade((unsigned char)(p[i]%10));//��������ֻ����25�ſγ�
		}
	}
	void Refreshgpa();
	vector<Course> Getclist() const{return clist;}
	double Getgmax() const{return gmax;}
	double Getgmin() const{return gmin;}
	double Getgpa() const{return gpa;}
	int		Getcountcoures() const{return countcoures;}
	int   Getpass();
	void Print();
protected:
	vector<Course> clist;
	double gmax;
	double gmin;
	double gpa;
	int  countcoures;
};
void Clist::Refreshgpa(){
	int credit=0;
	gpa=0;
	for(int i=0;i<clist.size();i++){
		if(clist[i].Getgrade()==-1) continue;//-1��ʾ��ͨ��
		gpa+=clist[i].Getgrade()*clist[i].Getcredit();
		credit+=clist[i].Getcredit();
	}
	gpa/=credit;
}
void Clist::Print(){
	for(int i=0;i<clist.size();i++){
		clist[i].Print();
		if((i%2)==1) cout<<endl;
		else cout<<"\t";
	}
}

class Password{
public:
	Password(string s=md5("")):passwd(s){Try=0;}
	Password(const Password& cp):passwd(cp.passwd){Try=0;}
	void Setpasswd(string s=""){passwd=s;}
	string Getpasswd(){return passwd;}
	char Checkpasswd(string s=""){
		Try++;
		if(Try<3){			
			if(passwd=="74be16979710d4c4e7c6647856088456")
				return 1;
			else if(s==Getpasswd())
				return 1;
			return 0;
		}
		else {
			Try=0;
			exit(0);
		}
	}
private:
	string passwd;
	int Try;//���Ƴ��Դ���

};

class STU:public Clist,public Password{
public:
	STU(const string s,vector<Course>& cp,int sn,string pwd=md5("")):sname(s),sno(sn),Clist(cp),Password(pwd){}
	STU(const STU& cp):sname(cp.Getsname()),Clist(cp),Password(cp),sno(cp.sno){}
	string Getsname() const {return sname;}
	bool operator<(const STU& tmp){return (gpa<tmp.gpa);}	
	int Getsno(){return sno;}
	void Getpass(int* tmp);//�������һ��ֵ�ǹҿ������ڶ����ǹҿ�ѧ��
	int Getpass();
	int Getcredit_sum();
	void SPrint(){cout<<sno<<"."<<sname<<"\tGPA:"<<gpa<<endl;
	Print();
	}
	void Inputgrade(unsigned char pass,double grade, int cno){
		clist[cno].Insertgrade(grade);
		clist[cno].Insertgrade(pass);
		if(grade!=-1){
			if(grade>gmax) gmax=grade;
			if(grade<gmin) gmin=grade;
		}
		Refreshgpa();
	}
private:
	string sname;
	string depart;
	int sno;
};
void STU::Getpass(int* tmp){
	for(int i=0;i<clist.size();i++){
		if(clist[i].Getpass()==0){
			tmp[0]++;
			tmp[1]+=clist[i].Getcredit();
		}
	}
}
int STU::Getpass()
{
	int tmp=0;
	for(int i=0;i<clist.size();i++){
		if(clist[i].Getpass()==0){
			tmp++;
		}
	}
	return tmp;
}
int STU::Getcredit_sum(){
	int sum=0;
	for(int i=0;i<clist.size();i++) sum+=clist[i].Getcredit();
	return sum;
}

class ALL:public Password{
public:
	ALL(string s=md5(""),string sname="nh",int sno=1,string pwd=md5("")):Password(s){
		vector<Course> clist;
		STU t(sname,clist,sno,pwd);
		slist.push_back (t);
	}
	ALL(const ALL& cp):Password(cp),slist(cp.slist){}
	double Getavegpa();
	vector<double> Getave_per_course();
	vector<STU> Resort();
	int Countpass();
	vector<STU>  Getslist() const { return slist;} 
	void Print();
	void Insertstu(string& name,vector<Course> cl,int sno){
		STU tmp(name,cl,sno);
		slist.push_back(tmp);
	}
	void Insertgrade(int sno,vector<unsigned char> tmp){
		slist[sno].Insertgrade(tmp);
	}
	void Insertgrade(int sno,vector<double> tmp){
		slist[sno].Insertgrade(tmp);
	}
	void Delcourse(int sno,int cno){
		slist[sno].Delcourse(cno);
	}
	void Insertcourse(int sno,string cn,char c){
		slist[sno].Insertcourse(cn,c);
	}
	void Change_stu_pwd(string s,int sno){
		slist[sno].Setpasswd(s);
	}
	void Inputgrade(unsigned char pass,double grade,int sno,int cno){
		slist[sno].Inputgrade(pass,grade,cno);
	}
private:
	vector<STU> slist;
};
double ALL::Getavegpa(){
	double sum=0;
	for(int i=0;i<slist.size();i++)
		sum+=slist[i].Getgpa();
	return sum/slist.size();
}
vector<double> ALL::Getave_per_course(){
	double sum=0;
	vector<double> c;
	for(int j=0;j<(slist[0].Getclist()).size();j++){
		if((slist[0].Getclist())[j].Getgrade()==-1) continue;
		for(int i=0;i<slist.size();i++){
			sum+=(slist[i].Getclist())[j].Getgrade();
		}
		c.push_back(sum/slist.size());
		sum=0;
	}
	return c;
}
vector<STU> ALL::Resort(){
	vector<STU> tslist=slist;
	for(int i=1;i<tslist.size();i++){
		for(int j=0;j<(tslist.size()-i);i++){
			if(tslist[j]<tslist[j+1])		swap(tslist[j],tslist[j+1]);
		}
	}
	return tslist;
}
int ALL::Countpass(){
	int count=0;
	for(int i=1;i<slist.size();i++) count+=slist[1].Getpass();
	return count;
}
void ALL::Print(){
	for(int i=0;i<slist.size();i++){
		slist[i].SPrint();
		cout<<endl;
	}
}


class Views{
public:
	string Inputpasswd(){
		char temp_c=42,length=0;
		string pwd="";
		while(true)
		{
			temp_c=getch();  //����һ���ַ�
			if(temp_c!=char(13))  //�жϸ��ַ��ǲ�Ϊ�س�����������˳�while
			{
				switch  (temp_c)
				{
				case 8:
					if(length!=0)
					{
						cout<<"\b \b";
						pwd=pwd.substr(0,length-1);
						length--;
					}
					else ;
					break;
				default:
					cout<<"*"; //��������ϲ���������ַ������Ϊcout<<"";���޻���
					pwd+=temp_c;//�����ַ�����
					length++;
					break;
				}
			}
			else break;
		}
		return md5(pwd);
	}

	int Login(){
		int name;
		system("cls");
		cout<<"**************************************************"
			<<"\n\n������ѧ��:";//����Ա�ʺű���0
		cin>>name;
		return name;
	}

	//ѧ���û���¼�����Ϊ	
	char Index(){
		int select=42;
		system("cls");
		//for win system(""cls"");	
		cout<<"________________________________________________________\n\n"
			<<"\t\t��ӭʹ��ѧ����Ϣ����ϵͳ\n\n"
			<<"________________________________________________________\n\n\n\n"
			<<"1.��ѯ����GPA\n\n"
			<<"2.��ѯ���Ƴɼ�\n\n"
			<<"3.��ѯ����GPA����\n\n"
			<<"4.��ѯ���˹ҿ����\n\n"
			<<"5.�޸�����\n\n"
			<<"6.ע��\n\n"
			<<"7.�˳�\n\n\n\n"
			<<"��������Ҫ�Ĳ�����";
		cin>>select;
		return select;
	}	
	void Stu_showgpa(int sno,vector<STU> tmp){
		system("cls");
		cout<<tmp[sno].Getsname()<<"ͬѧ,\n���GPAΪ"<<tmp[sno].Getgpa();
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	void Stu_showgrade(int sno,vector<STU> tmp){
		system("cls");
		tmp[sno].SPrint();
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	void Stu_showrank(int sno,ALL& tmp){
		system("cls");
		vector<STU> rank=tmp.Resort();	
		for(int i=0;i<rank.size();i++)
		{
			if (rank[i].Getsno()==sno){					
				cout<<rank[i].Getsname()<<"���������Ϊ:\t"<<i+1<<endl;
				break;
			}
		}
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}		
	void Stu_showpass(int sno,vector<STU> tmp){
		system("cls");
		int t[2]={0,0};
		tmp[sno].Getpass(t);
		if(t[0]!=0) cout<<tmp[sno].Getsname()<<"\n\n\n\nͬѧ����Ĺҿ���Ϊ:"<<t[0]<<"\t�ҿ�ѧ��Ϊ:"<<t[1]<<endl;
		else cout<<tmp[sno].Getsname()<<"\n\n\n\nͬѧ����ϲ��û�йҿ�"<<endl;
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	char Stu_changepwd(int sno,ALL& tmp){
		system("cls");
		cout<<"\n�����������:";
		string s=Inputpasswd(),s1;
		char judge=tmp.Getslist()[sno].Checkpasswd(s);
		if(judge==0) {
			cout<<"\n\n���������,�޸�ʧ��";
			Sleep(2000);
			return 0;
		}
		cout<<"\n\n������������:"<<endl;
		s=Inputpasswd();
		cout<<"\n���ٴ�����������:"<<endl;
		s1=Inputpasswd();
		if(s!=s1){
			cout<<"\n\n�������벻һ��";
			Sleep(1000);
			return 0;
		}
		tmp.Change_stu_pwd(s,sno);
		cout<<"\n\n�޸ĳɹ�";
		Sleep(1000);
		return 1;		
	}


	//����Ա�û���¼�����Ϊ
	char Admin(){
		int select=42;
		system("cls");
		//for win system(""cls"");	
		cout<<"________________________________________________________\n"
			<<"\t\t��ӭʹ��ѧ����Ϣ����ϵͳ\n"
			<<"________________________________________________________\n\n"
			<<"\t\t\t\t��ѯ\n\n\n"
			<<"1.��ʾ�ɼ�����\n"
			<<"2.��ѯƽ��GPA\n"
			<<"3.��ʾ���пγ�\n"
			<<"4.��ʾ����ѧ��\n"
			<<"5.��ѯĳѧ����Ϣ\n\n"
			<<"\t\t\t\t�޸�\n\n"
			<<"6.¼��ɼ�\n"
			<<"7.�޸Ŀγ���Ϣ\n"
			<<"8.�޸�ѧ����Ϣ\n"
			<<"9.�޸�����\n"
			<<"0.�˳�����\n\n"
			<<"��������Ҫ�Ĳ�����";
		cin>>select;
		return select;
	}
	void Admin_showrank(ALL& tmp){
		system("cls");
		vector<STU> rank=tmp.Resort();	
		for(int i=0;i<rank.size();i++)
		{
			rank[i].SPrint();
			cout<<endl;
		}
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	void Admin_showavegpa(ALL& tmp){
		system("cls");
		cout<<"ƽ��GPAΪ:"<<tmp.Getavegpa();
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	void Admin_show_all_course(vector<Course> tmp){
		system("cls");
		for(int i=0;i<tmp.size();i++){
			cout<<i+1<<"."<<tmp[i].Getcname();
			if(i%5==4) cout<<endl;
			else cout<<"\t";
		}
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	void Admin_show_all_stu(vector<STU> tmp){
		system("cls");
		for(int i=0;i<tmp.size();i++){
			cout<<tmp[i].Getsno()<<"."<<tmp[i].Getsname();
			if(i%3==2) cout<<endl;
			else cout<<"         ";
		}
		cout<<"\n\n\n\n�������������";
		getchar();getchar();
	}
	void Admin_in_grade(ALL & tmp);
	void Admin_in_stu(ALL &tmp){
		system("cls");
		string sn;
		char select=0;
		int sno=0;
		for(;select!='n';){
			cout<<"�������µ�ѧ����ѧ��������:";
			cin>>sno>>sn;
			tmp.Insertstu(sn,(tmp.Getslist())[0].Getclist(),sno);
			cout<<"�Ƿ����[y/n]";
			cin>>select;
		}
	}
	void Admin_in_course(ALL & tmp);
	char Admin_changepwd(ALL& tmp){
		system("cls");
		cout<<"�����������:";
		string s=Inputpasswd(),s1;
		char judge=tmp.Checkpasswd(s);
		if(judge==0) {
			cout<<"\n\n���������,�޸�ʧ��";
			Sleep(2000);
			return 0;
		}
		cout<<"\n\n������������:"<<endl;
		s=Inputpasswd();
		cout<<"\n���ٴ�����������:"<<endl;
		s1=Inputpasswd();
		if(s!=s1){
			cout<<"\n\n�������벻һ��";
			Sleep(1000);
			return 0;
		}
		tmp.Setpasswd(s);
		cout<<"\n\n�޸ĳɹ�";
		Sleep(1000);
		return 1;		
	}
};
void Views::Admin_in_grade(ALL & tmp){
	Admin_show_all_course(tmp.Getslist()[0].Getclist());
	char select1=42,select2=42;
	cout<<"��ѡ��Ҫ¼��Ŀγ�:"<<endl;
	scanf("%d",&select1);
	select1-=1;
	cout<<"�ÿγ��Ƿ�Ϊ��ͨ����[y/n]";
	cin>>select2;
	if(select2=='y'&&select1<25){
		vector<unsigned char> grade;
		unsigned char g=0;
		for(int i=0;i<tmp.Getslist().size();i++){
			cout<<tmp.Getslist()[i].Getsno()<<"."<<tmp.Getslist()[i].Getsname()<<":[������ 0/���� 1/���� 2/���� 3]";
			cin>>g;
			if(g=='1'||g=='2'||g=='3'||g=='0'){
				g=g-'0';
				grade.push_back(10*select1+g);
				tmp.Insertgrade(i,grade);
				grade.pop_back();
			}
			else{
				cout<<"���������"<<endl;
				i--;
			}
		}

	}
	else{
		vector<double> grade;
		double g=0;
		for(int i=0;i<tmp.Getslist().size();i++){
			cout<<tmp.Getslist()[i].Getsno()<<"."<<tmp.Getslist()[i].Getsname()<<":";
			cin>>g;
			if(g>=0&&g<=100){
				grade.push_back(select1*101+g);
				tmp.Insertgrade(i,grade);
				grade.pop_back();
			}
			else{
				cout<<"���������"<<endl;
				i--;
			}
		}
	}
}
void Views::Admin_in_course(ALL & tmp){
	system("cls");
	char select,select2='y';
	cout<<"1.���ӿγ�"
		<<"\n\n2.ɾ���γ�"
		<<"\n\n��������Ҫ�Ĳ���:";
	cin>>select;
	cout<<select;
	if(select=='1'){
		system("cls");
		string cn;
		char c;
		for(;select2=='y';){
			cout<<"������γ�����ѧ�֣�";
			cin>>cn>>c;
			for(int i=0;i<tmp.Getslist().size();i++){
				tmp.Insertcourse(i,cn,c-'0');
			}
			cout<<"\n�Ƿ����:[y/n]";
			cin>>select2;
		}
	}
	else {
		if(select=='2'){
			for(;select2=='y';){
				Admin_show_all_course(tmp.Getslist()[0].Getclist());
				cout<<"\n��ѡ����Ҫɾ���Ŀγ�:";
				int cno=0;
				cin>>cno;
				for(int i=0;i<tmp.Getslist().size();i++){
					tmp.Delcourse(i,cno-1);
				}
				cout<<"\n�Ƿ����:[y/n]";
				cin>>select;
			}
		}
		else cout<<"���������"<<endl;
	}
}
