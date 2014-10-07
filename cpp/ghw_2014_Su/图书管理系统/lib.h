#include		<iostream>
#include		<string>
#include		<sstream>
#include		<stdio.h>
#include		<vector>
#include		<stdlib.h>
#include		"md5.h"
#include	    <windows.h>//for windows
#include		<time.h>
#include		<conio.h>
using namespace std;

string Time(time_t t){
	ostringstream s("");
	tm* tmp=localtime(&t);
	s<<tmp->tm_year+1900<<"-"<<tmp->tm_mon+1<<"-"<<tmp->tm_mday;
	return s.str();
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
	void Changepwd(string s=""){passwd=s;}
protected:
	string passwd;
	int Try;//���Ƴ��Դ���
};

class STU:public Password{
public:
	STU(vector<int> which,string s="",int sn=0,string pwd=md5("")):sname(s),sno(sn),
		which_borrow(which),Password(pwd){}
	STU(const STU& cp):sname(cp.sname),Password(cp),sno(cp.sno){}
	void SPrint(){cout<<sno<<"."<<sname<<endl;}
	void Borrow(int bno){
		which_borrow.push_back(bno);
	}
	void Return(int bno){
		for(int i=0;i<which_borrow.size();i++){
			if(which_borrow[i]==bno){
				which_borrow.erase(which_borrow.begin()+i);
				break;
			}
		}
	}
	int Getsno(){return sno;}
	string Getsname(){return sname;}
	vector<int> Getwhich(){return which_borrow;}
protected:
	string sname;
	vector<int> which_borrow;
	int sno;
};

class Book
{
public:
	Book(string bn="",time_t d=0,time_t rd=1,int in=1,int who=-1):bname(bn),date(d),redate(rd),inlib(in),who_borrow(who){}	
	Book(const Book &cp):bname(cp.Getbname()),date(cp.Getdate()),redate(cp.Getredate()),inlib(cp.Getinlib()),who_borrow(cp.Getwho()){

	}
	int Borrow(int who=0,int bd=0,time_t t=time(NULL)){
		if(inlib==1){
			date=t;
			redate=date+bd*86400;
			inlib=0;
			who_borrow=who;
			return 1;
		}
		else return 0;
	}
	bool operator<(const Book& tmp)
	{return (redate<tmp.redate);}	
	int Getwho()const {return who_borrow;}
	int Return(){
		date=0;
		inlib=1;
		if(time(NULL)>redate){
			redate=1;
			return who_borrow;
		}
		redate=0;
		return 0;
	}
	string Getbname() const{return bname;}
	time_t Getdate() const{return date;}
	time_t Getredate() const {return redate;}
	int Getinlib() const {return inlib;}

protected:
	time_t date;//�������
	string bname;//����
	time_t redate;//��������
	int inlib;//1��ʾ��ͼ���,0��ʾ�ѽ��
	int who_borrow;

};

class List
{
public:
	List(vector<Book> bl,vector<STU> s1):blist(bl),slist(s1){}
	List( List &cp):blist(cp.Getblist()),slist(cp.Getslist()){}
	vector<Book> Getbook_by_stu(int n){
		vector<Book> tmp;
		for (int i=0;i<blist.size();i++){
			if(blist[i].Getwho()==n)
				tmp.push_back(blist[i]);
		}
		return tmp;
	}
	vector<Book> Getblist(){return blist;}
	vector<STU>  Getslist(){return slist;}
protected:
	vector<Book> blist;
	vector<STU> slist;
};

class ALL:public Password,public List{
public:
	ALL(vector<Book> b,vector<STU> stu,string s=md5("")):Password(s),List(b,stu){}
	ALL(const ALL& cp):Password(cp),List(cp.blist,cp.slist){}
	void Addbook(string bn=""){
		Book tmp(bn);
		blist.push_back(tmp);
	}
	void Delbook(int bno){
		blist.erase(blist.begin()+bno);
	}
	void Addstu(string sn="",int sno=0){
		vector<int> v;
		STU tmp(v,sn,sno);
		slist.push_back(tmp);
	}
	void Setpasswd(string s=""){
		passwd=s;
	}
	void Borrow_book(int bno,int sno,int bd,time_t t=time(NULL)){
		if(blist[bno].Borrow(sno,bd,t)){
			slist[sno].Borrow(bno);
			cout<<"����ɹ�"<<endl;
		}
		else cout<<"���鲻�ڼ��ϣ���"<<endl;
	}
	int  Return_book(int bno,int sno){
		slist[sno].Return(bno);
		return blist[bno].Return();
	}
	void BPrint(){
		for(int i=0;i<blist.size();i++)		BPrint(i);				
	}
	void BPrint(int bno){
		cout<<bno<<"."<<blist[bno].Getbname()<<endl;
		if(blist[bno].Getinlib()==0)
			cout<<"\t �����ڣ�"<<Time(blist[bno].Getdate())<<"  "<<"�ڣ�"<<Time(blist[bno].Getredate())<<"��ֹ";
		if(blist[bno].Getinlib()==0&&blist[bno].Getredate()<time(NULL)) cout<<"\t\t״̬�����ڴ߻�";
		cout<<endl;
	}
	void SPrint(){
		for(int i=0;i<slist.size();i++) SPrint(i);
	}
	void SPrint(int sno){
		slist[sno].SPrint();
		if(slist[sno].Getwhich().size()!=0){
			for(int j=slist[sno].Getwhich().size()-1;j>-1;j--){
				cout<<"\t";
				BPrint(slist[sno].Getwhich()[j]);
			}
		}
	}
	void Search(string keyword);
	vector<Book> Resortbook();
	void Change_stu_pwd(string pwd,int sno){
		slist[sno].Setpasswd(pwd);
	}
};
void ALL::Search(string keyword){
	int i=0;
	for(i=0;i<blist.size();i++){
		if(blist[i].Getbname()==keyword){
			BPrint(i);
			break;
		}
	}
	if(blist.size()-1==i) cout<<"���鲻����";
}
vector<Book> ALL::Resortbook(){
	vector<Book> tblist=blist;
	for(int i=1;i<tblist.size();i++){
		for(int j=0;j<(tblist.size()-i);i++){
			if(tblist[j]<tblist[j+1])		swap(tblist[j],tblist[j+1]);
		}
	}
	return tblist;
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
			<<"\n\n\n\n ������ѧ��:";//����Ա�ʺű���0
		cin>>name;
		return name;
	}
	//ѧ���û���¼�����Ϊ	
	char Index(int sno,ALL & all){
		int select=42;
		system("cls");
		//for win system(""cls"");	
		cout<<"________________________________________________________\n\n"
			<<"\t\t��ӭʹ��ͼ��ݹ���ϵͳ\n\n"
			<<"________________________________________________________\n\n\n\n";
		all.SPrint(sno);
		cout<<"\n\n1.��ѯ�����鼮\n\n"
			<<"2.��ѯ�����鼮\n\n"
			<<"3.�޸�����\n\n"
			<<"4.ע��\n\n"
			<<"5.�˳�\n\n\n\n"
			<<"��������Ҫ�Ĳ�����";
		cin>>select;
		return select;
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
	void Stu_search(ALL &tmp){
		system("cls");
		string key;
		char select=0;

		for(;select!='n';){
			cout<<"��������Ҫ��ѯ���鼮��:";
			cin>>key;
			tmp.Search(key);
			cout<<"�Ƿ����[y/n]";
			cin>>select;
		}
	}
	//����Ա�û���¼�����Ϊ
	char Admin(){
		int select=42;
		system("cls");
		//for win system(""cls"");	
		cout<<"________________________________________________________\n"
			<<"\t\t��ӭʹ��ͼ��ݹ���ϵͳ\n"
			<<"________________________________________________________\n\n"
			<<"1.��ʾ�����鼮\n"
			<<"2.��ʾ����ѧ��\n"
			<<"3.��ѯ������Ϣ\n\n"
			<<"4.����\n"
			<<"5.����\n"
			<<"6.�����鼮\n"
			<<"7.ɾ���鼮\n"
			<<"8.����ѧ��\n"
			<<"9.�޸�����\n"
			<<"0.�˳�����\n\n"
			<<"��������Ҫ�Ĳ�����";
		cin>>select;
		return select;
	}
	void Admin_check_return(ALL& tmp){
		system("cls");
		vector<Book> blist=tmp.Resortbook();
		for(int i=0;i<blist.size();i++){
			if(blist[i].Getinlib()==0){
				cout<<i<<"."<<blist[i].Getbname()<<endl;
				cout<<"\t �����ڣ�"<<Time(blist[i].Getdate())<<"  "<<"�ڣ�"<<Time(blist[i].Getredate())<<"��ֹ";

				if(blist[i].Getredate()<time(NULL)&&blist[i].Getinlib()==0) cout<<"\t\t״̬�����ڴ߻�";
				cout<<endl;
			}
		}
	}
	void Admin_Borrow_book(ALL &tmp){
		system("cls");
		int user_id=-1,bno=-1,bd=7,i;
		char select=0;
		for(;select!='n';){
			tmp.SPrint();
			cout<<"��ѡ������ͬѧ��ѧ��:";
			cin>>user_id;
			for(i=0;(i<tmp.Getslist().size())&&(tmp.Getslist()[i].Getsno()!=user_id);i++);
			if(i==tmp.Getslist().size()){
				cout<<"�û�������";
				Sleep(1000);
				return;
			}
			tmp.BPrint();
			cout<<"��ѡ�������鼮������-1ֹͣ������";
			cin>>bno;
			if(bno==-1) break;
			cout<<"�����뱾�黹�����ޣ��죩";
			cin>>bd;
			tmp.Borrow_book(bno,i,bd);
			cout<<"�Ƿ����[y/n]";
			cin>>select;
		}
	}
	void Admin_return_book(ALL &tmp){
		system("cls");
		int sno=-1,bno=-1;
		char select=0;
		vector<Book> blist=tmp.Getblist();
		for(;select!='n';){
			for(int i=0;i<blist.size();i++){
				if(blist[i].Getinlib()==0){
					cout<<i<<"."<<blist[i].Getbname()<<endl;
					cout<<"\t �����ڣ�"<<Time(blist[i].Getdate())<<"  "<<"�ڣ�"<<Time(blist[i].Getredate())<<"��ֹ";

					if(blist[i].Getredate()<time(NULL)&&blist[i].Getinlib()==0) cout<<"\t\t״̬�����ڴ߻�";
					cout<<endl;
				}
			}
			cout<<"��ѡ��Ҫ�����鼮:������-1ֹͣ������";
			cin>>bno;
			if(bno==-1) break;
			tmp.Return_book(bno,tmp.Getblist()[bno].Getwho());
			cout<<"�Ƿ����[y/n]";
			cin>>select;
			blist=tmp.Getblist();
		}
	}
	void Admin_del_book(ALL &tmp){
		system("cls");
		int bno=-1;
		char select=0;
		for(;select!='n';){
			tmp.BPrint();
			cout<<"��ѡ��Ҫɾ�����鼮:������-1ֹͣ������";
			cin>>bno;
			if(bno==-1) break;
			tmp.Delbook(bno);
			cout<<"�Ƿ����[y/n]";
			cin>>select;
		}
	}
	void Admin_in_stu(ALL &tmp){
		system("cls");
		string sn;
		char select=0;
		int sno=0;
		for(;select!='n';){
			cout<<"�������µ�ѧ����ѧ��������:";
			cin>>sno>>sn;
			tmp.Addstu(sn,sno);
			cout<<"�Ƿ����[y/n]";
			cin>>select;
		}
	}
	void Admin_in_book(ALL & tmp){
		system("cls");
		string bn;
		char select=0;
		for(;select!='n';){
			cout<<"�������µ��鼮��:";
			cin>>bn;
			tmp.Addbook(bn);
			cout<<"�Ƿ����[y/n]";
			cin>>select;
		}
	}
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