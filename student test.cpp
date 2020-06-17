#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <tchar.h>
#include <list>

using namespace std;

char UserName[15],UserPassword[15];//�û�������û���������
char realName[15],realPassword[15];//��ȷ���û���������
char defaultName[15]="admin",defaultPassword[15]="admin";//Ĭ���û���������
bool isChangePassword=false;//��¼�Ƿ��޸�����
bool isChangeInformation=false;//��¼�Ƿ��޸�ѧ����Ϣ
int changeTimes=0;//��¼�޸�����ʱ�������Ĵ���
int stu_cnt=0;//ѧ������
char *oldFileName,*newFileName;//�����ļ��ľ��Ե�ַ

struct Student  //�ɼ��ṹ��
{
    char name[9];//����
    char num[9];//ѧ��
    int age;//����
    char sex[1];//�Ա�
    int Math;//��ѧ
    int English;//Ӣ��
    int Program;//�����
    int sum;//�ܷ�
} s;

void Init();//��ʼ����¼ҳ��
void readFileAdd();//��ȡ�����ļ��ľ���Ŀ¼
void readStudent();//��ȡѧ����Ŀ
void StuManage();//ѧ����Ϣ����ϵͳ ������ַ�ͼ��
void Login();//��¼ϵͳ
int isLogin();//�ж��Ƿ��¼�ɹ�
int MenuSelect();//�˵�ѡ��
void MainMenu();//���˵�����
void Head();//ѧ����Ϣ����ϵͳ�ַ�ͼ��
void printfError();//��ʾ������Ϣ
void changePassword();//�޸�����
void scanfInformation();//����ѧ����Ϣ
void Quit();//�˳���������½������˵�
void readfile();//�����ļ�
void writefile();//д���ļ�
void Change_Information();//����
void Delete_Information();//ɾ��
void Show_Information();//���ѧ����Ϣ
void Add_Information();//���ѧ����Ϣ
void Search_Information();//��ѯѧ����Ϣ
bool Find_Information();//����ѧ����Ϣ
void Sord_Information();//����ѧ����Ϣ
void Show_Sorted(list<Student>& ss);//��ʾ������ѧ����Ϣ

typedef enum Menu
{
    Exit,ChangePassword,Show,Add,Sort,Change,Delete,Search
} MENU;



//��ʼ����¼ҳ��
void Init()
{
    readFileAdd();
    readStudent();

    system("mode con cols=120 lines=40");//��ʼ����������С
    printf("��ӭʹ�ñ�ϵͳ��\n");
    int i;
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
    char heihei[] = { "��������ѧ������ϵͳ..." };
    for (i = 0; i < strlen(heihei); i++)
    {
        printf("%c", heihei[i]);
        Sleep(25);
    }
    system("cls");
    Login();
}

void readFileAdd()//��ȡ�����ļ��ľ���Ŀ¼
{
    TCHAR _szPath[MAX_PATH + 1]= {0};
    GetModuleFileName(NULL, _szPath, MAX_PATH);
    (_tcsrchr(_szPath, _T('\\')))[1] = 0;//ɾ���ļ�����ֻ���·�� �ִ�
    string strPath;
    for (int n=0; _szPath[n]; n++)
    {
        if (_szPath[n]!=_T('\\'))
        {
            strPath +=_szPath[n] ;
        }
        else
        {
            strPath += _T("\\\\");
        }
    }
    string oldFilePath=strPath;

    oldFilePath=oldFilePath+"stu.dat";
    oldFileName = new char[strlen(oldFilePath.c_str())+1];
    strcpy(oldFileName, oldFilePath.c_str());

    string newFilePath=strPath;
    newFilePath=newFilePath+"stu_temp.dat";
    newFileName = new char[strlen(newFilePath.c_str())+1];
    strcpy(newFileName, newFilePath.c_str());

}
//��ȡѧ����Ŀ
void readStudent()
{

    ifstream fin("stu.dat",ios::binary);
    fin.seekg(0,ios::end);
    streampos ps=fin.tellg();
    stu_cnt=ps/sizeof(s);
    fin.close();
}

//ѧ����Ϣ����ϵͳ�ַ�ͼ��
void Head()
{
    printf("\n");
    printf("\t\t\t\t\t�q �]%�r                   �q ```�r  \n");
    printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ (��:��)\n");
    printf("\t\t\t\t\t(~):(~)                  (~)v(~) \n");
    printf("\n\n\n");
}

//ѧ����Ϣ����ϵͳ ������ַ�ͼ��
void StuManage()
{
    printf("\n");
    printf("\t\t\t\t\t�q �]%�r                           �q ```�r  \n");
    printf("\t\t\t\t\t(@^o^@) ѧ����Ϣ����ϵͳ   �����(��:��)\n");
    printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
    printf("\n\n\n");
}

//��ʾ������Ϣ
void printfError()
{
    printf("\n\t\t\t\t\t\t��ʽ�������������룺");
}

//��¼ϵͳ
void Login()
{
    StuManage();
    char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
    for (int i = 0; i<strlen(xing); i++)
    {
        printf("%c", xing[i]);
        Sleep(5);
    }
    printf("\n\n\t\t\t\t\t\t�����������˺�����:\n\n\n\n\t\t\t\t\t\t�˺�:");
    cin>>UserName;
    printf("\n\n\t\t\t\t\t\t����:");
    cin>>UserPassword;

}

//�ж��Ƿ��¼�ɹ�
int isLogin()
{
    int times = 0;	//�����������

    ifstream passIn;//������
    passIn.open("password.dat",ios::in|ios::binary);//Ϊ�����password.txt
    if(!passIn.is_open())//�����ʧ�ܣ��򴴽��ļ�
    {
        ofstream passOut;//�����
        passOut.open("password.dat",ios::binary);
        passOut.write(defaultName,sizeof(defaultName));
        passOut.write(defaultPassword,sizeof(defaultPassword));
        passOut.close();
        passIn.open("password.dat",ios::in|ios::binary);
    }
    passIn.read(realName,sizeof(realName));
    passIn.read(realPassword,sizeof(realPassword));
    passIn.close();

    while (strcmp(UserName,realName)||strcmp(UserPassword,realPassword))
    {
        times++;	//����������� times++
        if (times > 3)
        {
            printf("\n\n\n\n\t\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", times);
            Sleep(1000);
            system("cls");
            char shutdown[] = { "ϵͳ����%d���ر�..." };
            for (int i = 0; i < 3; i++)
            {
                printf(shutdown, 3 - i);
                Sleep(1000);
                system("cls");
            }
            exit(0);
        }
        printf("\n\n\n\n\t\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - times);
        getch();
        system("cls");
        Login();
    }
    return 1;

}

//�޸�����
void changePassword()
{
    char tempName[15],tempPassword[15],oldPassword[15];

    Head();
    printf("\t\t\t**********************�޸��û���������*********************\n\n\n");
    cout<<"\t\t\t�����û���Ϊ��"<<realName;
    cout<<endl<<"\n\t\t\tҪ������������������֤��¼���������ˣ����������ľ����룺";
    cin>>oldPassword;

    if(strcmp(oldPassword,realPassword)==0)//������ȷ
    {

        cout<<"\n\t\t\t�������������û�����������14λ��:";
        cin>>tempName;
        while(strlen(tempName)>14)
        {
            printf("\n\t\t\t��ʽ�������������룺");
            cin>>tempName;
        }
        cout<<"\n\t\t\t���������������루������14λ��:";
        cin>>tempPassword;
        while(strlen(tempPassword)>14)
        {
            printf("\n\t\t\t��ʽ�������������룺");
            cin>>tempPassword;
        }

        ofstream passOut;
        passOut.open("password.dat",ios::binary|ios::trunc);
        if(passOut.is_open())
        {
            isChangePassword=true;
            passOut.write(tempName,sizeof(tempName));
            passOut.write(tempPassword,sizeof(tempPassword));
        }
        passOut.close();
        cout<<endl<<"\t\t\t��ϲ�����޸ĳɹ������μ������û���������~";
    }
    while(strcmp(oldPassword,realPassword))//�������
    {
        changeTimes++;
        if (changeTimes > 3)
        {
            printf("\n\n\n\n\t\t\t�˺Ż�������������ۼƴﵽ%d�Σ�ϵͳ����3���ر�", changeTimes);
            Sleep(3000);
            system("cls");
            char shutdown[] = { "ϵͳ����%d���ر�..." };
            for (int i = 0; i < 3; i++)
            {
                printf(shutdown, 3 - i);
                Sleep(1000);
                system("cls");
            }
            exit(0);
        }
        printf("\n\n\n\t\t\t�˺Ż������������,�㻹��%d�ε�¼���ᣬ����������µ�¼...", 4 - changeTimes);
        getch();
        system("cls");
        changePassword();
    }
    Quit();
}

//�˳���������½������˵�
void Quit()
{
    char ch;
    printf("\n\t ");
    for (int i = 0; i < 50; i++)
    {
        printf("* ");
        Sleep(10);
    }
    printf("\n\n\t\t\t\tҪ���ص�¼���水�����\t\t�˳������������밴Esc��\n");
    ch = getch();
    if (ch == 0x1b)	//esc������
    {
//		SaveData();
        _Exit(0);
    }
    //���½������˵�
    MainMenu();
}

//д���ļ�
void writefile()
{
    ofstream fout("stu.dat",ios::binary|ios::app);//���������
//    fout.open("stu.dat",ios::binary|ios::ate);
    fout.write((char*)&s, sizeof(s));
    fout.close();
}

//�����ļ�
void readfile()
{
    ifstream fin("stu.dat",ios::in|ios::binary);//����������
    while(fin.read((char*)&s,sizeof(s)))
    {
        printf("\t\t\t");
        printf("%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",s.num,s.name,s.age,s.sex,s.Math,s.English,s.Program,s.sum);
    }
    fin.close();
}

//����ѧ����Ϣ
bool Find_Information(char *id)
{
    ifstream fin("stu.dat",ios::in|ios::binary);//����������
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(strcmp(s.num,id)==0)
        {
            return true;
        }
    }
    fin.close();
    return false;
}
//����ѧ����Ϣ
void scanfInformation()
{
    char id[9];
    char _name[9];
    printf("\n\t\t\t\t\t\tѧ�ţ�������9���ַ���:");
    if(stu_cnt==0)
    {
        cin>>s.num;
        while(strlen(s.num)>9)
        {
            printfError();
            cin>>s.num;
        }
    }
    else
    {
        cin>>id;
        while(Find_Information(id)&&isChangeInformation==false)
        {
            printf("\n\t\t\t\t\t\t�Ѵ��ڸ�ѧ������Ϣ�����������룺");
            cin>>id;
            if(strlen(id)>9)
            {
                printfError();
                cin>>id;
            }
        }
        if(Find_Information(id)==false)
        {
            while(strlen(id)>9)
            {
                printfError();
                cin>>id;
            }
        }
        strncpy(s.num,id,9);
    }

    printf("\n\t\t\t\t\t\t������������9���ַ���:");
    cin>>_name;
    while(strlen(_name)>9)
    {
        printfError();
        cin>>_name;
    }
    strncpy(s.name,_name,9);

    cout<<"\n\t\t\t\t\t\t�������䣺";
    cin>>s.age;
    while(s.age<0||s.age>100)
    {
        printfError();
        cin>>s.age;
    }

    cout<<"\n\t\t\t\t\t\t�����Ա�MΪ���ԣ�FΪŮ�ԣ���";
    char sex[1];
    cin>>sex;
    while((sex[0]!='M'&&sex[0]!='m'&&sex[0]!='F'&&sex[0]!='f')||strlen(sex)!=1)
    {
        printfError();
        cin>>sex;
    }
    strncpy(s.sex,sex,1);
    if(s.sex[0]=='m')
        s.sex[0]='M';
    if(s.sex[0]='f')
        s.sex[0]='F';

    printf("\n\t\t\t\t\t\t�ߵ���ѧ�������ٷ��ƣ�:");
    cin>>s.Math;
    while(s.Math<0||s.Math>100)
    {
        printfError();
        cin>>s.Math;
    }

    printf("\n\t\t\t\t\t\t��ѧӢ������ٷ��ƣ�:");
    cin>>s.English;
    while(s.English<0||s.English>100)
    {
        printfError();
        cin>>s.English;
    }

    printf("\n\t\t\t\t\t\t������ƣ������ٷ��ƣ�:");
    cin>>s.Program;
    while(s.Program<0||s.Program>100)
    {
        printfError();
        cin>>s.Program;
    }

    s.sum=s.Math+s.English+s.Program;
    printf("\n\t\t\t\t\t\t��ѧ�����ܷ�Ϊ��%d",s.sum);
}
//���ѧ����Ϣ
void Add_Information()
{
    char n;
    do
    {
        system("cls");
        Head();
        printf("\t\t\t\t\t\t���ѧ����Ϣ:\n\n\n\n");
        scanfInformation();
        writefile();
        stu_cnt++;
        printf("\n\n\t\t\t\t\t\t��Y����������������ء�");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}

//���ѧ����Ϣ
void Show_Information()
{
    Head();
    if(stu_cnt==0)
    {
        printf("\t\t\t**********************���������� %d ��ѧ��*********************\n\n\n", stu_cnt);
        printf("\t\t\t����ѧ����Ϣ��\n");
    }
    else
    {
        printf("\t\t\t**********************���������� %d ��ѧ��*********************\n\n\n", stu_cnt);
        printf("\t\t\tѧ��\t  ����\t   ����\t  �Ա�\t  ����\t  Ӣ��\t  �������\t�ܷ�\n\n");
        readfile();
    }
    Quit();
}

//��ѯѧ����Ϣ
void Search_Information()
{
    char n;
    do
    {
        system("cls");
        Head();
        char id[9];
        printf("\t\t\t\t\t\t��ѯѧ����Ϣ��\n\n");
        printf("\t\t\t\t\t\t������ѧ��ѧ�ţ�");
        cin>>id;
        if(Find_Information(id))
        {
            printf("\n\n\n\t\t\t\t\t\tҪ��ѯ��ѧ����Ϣ...\n\n");
            printf("\t\t\tѧ��\t  ����\t   ����\t  �Ա�\t  ����\t  Ӣ��\t  �������\t�ܷ�\n\n");
            printf("\t\t\t");
            printf("%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",s.num,s.name,s.age,s.sex,s.Math,s.English,s.Program,s.sum);
        }
        else
            printf("\n\n\n\n\t\t\t\t\t   û���ҵ�Ҫ��ѯ��ѧ����Ϣ......\n\n");
        printf("\n\n\t\t\t\t\t\t��Y������ѯ������������ء�\n");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}
void Delete_Information()//ɾ��
{
    char n;
    do
    {
        system("cls");
        Head();
        char id[9];
        printf("\t\t\t\t\t������Ҫɾ��ѧ����ѧ�ţ�");
        cin>>id;
        if(Find_Information(id))
        {
            printf("\n\t\t\t\t\t��˶�ѧ����Ϣ...\n\n");
            printf("\t\t\tѧ��\t  ����\t   ����\t  �Ա�\t  ����\t  Ӣ��\t  �������\t�ܷ�\n\n");
            printf("\t\t\t");
            printf("%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",s.num,s.name,s.age,s.sex,s.Math,s.English,s.Program,s.sum);
            printf("\n\t\t\t\t\tȷ�������밴Yɾ����������Esc�������룡");
            char ch;
            ch=getch();
            if (ch == 0x1b)
            {
                Delete_Information();
            }
            if(ch == 'y'||ch =='Y')
            {
                ifstream in("stu.dat",ios::binary);
                ofstream out("stu_temp.dat",ios::trunc|ios::binary);
                while(in.read((char*)&s,sizeof(s)))
                {
                    if(strcmp(id,s.num)!=0)
                    {
                        out.write((char*)&s, sizeof(s));
                    }
                }
                in.close();
                out.close();
                remove(oldFileName);
                rename(newFileName,oldFileName);
                printf("\n\n\t\t\t\t\tɾ���ɹ���");
                stu_cnt--;
            }
        }
        else
        {
            cout<<"\n\t\t\t\t\tѧ�������ڣ���Y�������룬����������ء�";
            char m;
            m=getch();
            if(m=='Y'||m=='y')
                Delete_Information();
            else
                Quit();

        }
        printf("\n\n\t\t\t\t\t��Y����ɾ��������������ء�");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}

void Change_Information()//�޸�ѧ����Ϣ
{
    char n;
    do
    {
        system("cls");
        Head();
        printf("\t\t\t\t\t������Ҫ�޸�ѧ����ѧ�ţ�");
        char id[9];
        cin>>id;
        if(Find_Information(id))
        {
            ifstream in("stu.dat",ios::binary);
            ofstream out("stu_temp.dat",ios::trunc|ios::binary);
            while(in.read((char*)&s,sizeof(s)))
            {
                if(strcmp(id,s.num)!=0)
                {
                    out.write((char*)&s, sizeof(s));
                }
                if(strcmp(id,s.num)==0)
                {
                    printf("\n\t\t\t\t\t���������������޸ĵ���Ŀ������Ҫ����ԭ������\n");
                    isChangeInformation=true;
                    scanfInformation();
                    out.write((char*)&s, sizeof(s));
                    printf("\n\n\t\t\t\t\t\t�޸ĳɹ���");
                }
            }
            in.close();
            out.close();
            remove(oldFileName);
            rename(newFileName,oldFileName);
        }
        else
        {
            cout<<"\n\t\t\t\t\tѧ�������ڣ���Y�������룬����������ء�";
            char m;
            m=getch();
            if(m=='Y'||m=='y')
                Change_Information();
            else
                Quit();
        }
        printf("\n\n\t\t\t\t\t�Ƿ�����޸ģ���Y����������������ء�");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}

//�Զ����������
bool StuCmp(const Student& s1,const Student& s2)
{
    return s1.sum>s2.sum;
}

//����ѧ����Ϣ
void Sord_Information()
{
    list<Student>ss;
    ifstream fin("stu.dat",ios::in|ios::binary);
    while(fin.read((char*)&s,sizeof(s)))
    {
        ss.push_back(s);
    }
    fin.close();
    ss.sort(StuCmp);
    Show_Sorted(ss);
    Quit();
}

//��ʾ������ѧ����Ϣ
void Show_Sorted(list<Student>& ss)
{
    int i=1;
    Head();
    if(stu_cnt==0)
    {
        printf("\t\t\t**********************���������� %d ��ѧ��*********************\n\n\n", stu_cnt);
        printf("\t\t\t����ѧ����Ϣ��\n");
    }
    else
    {
        printf("\t\t\t**********************���������� %d ��ѧ��*********************\n\n\n", stu_cnt);
        printf("\t\t\t���\tѧ��\t  ����\t   ����\t  �Ա�\t  ����\t  Ӣ��\t  �������\t�ܷ�\n\n");
        for(auto it=ss.begin(); it!=ss.end(); it++)
        {
            printf("\t\t\t%-8d%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",i,it->num,it->name,it->age,it->sex,it->Math,it->English,it->Program,it->sum);
            i++;
        }
    }
}
//�˵�ѡ��
int MenuSelect()
{
    char c;
    do
    {
        system("cls");
        Head();
        printf("\t\t\t\t   �q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�����T�T�T�r\n");
        printf("\t\t\t\t   ��              ѧ����Ϣ����ϵͳ              ��\n");
        printf("\t\t\t\t   �t�T�T�T�����T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s\n");
        printf("\t\t\t\t   ����������������������������������������������������������������������������������������-��\n");
        printf("\t\t\t\t   ��                                            ��\n");
        printf("\t\t\t\t   �� 1. �޸�����                    2. ��ʾ���� ��\n");
        printf("\t\t\t\t   ��                                            ��\n");
        printf("\t\t\t\t   �� 3. �������                    4. �������� ��\n");
        printf("\t\t\t\t   ��                                            ��\n");
        printf("\t\t\t\t   �� 5. �޸�����                    6. ɾ������ ��\n");
        printf("\t\t\t\t   ��                                            ��\n");
        printf("\t\t\t\t   �� 7. ��ѯ����                    0. �˳����� ��\n");
        printf("\t\t\t\t   ��                                            ��\n");
        printf("\t\t\t\t   ��������������������������������������������������������������������������������������������\n");
        printf("\t\t\t\t\t\t  ����ѡ��(0-7):");
        c = getche();
    }
    while (c < '0' || c > '7');
    return c - '0';
}

//���˵�����
void MainMenu()
{
    if (isChangePassword||isLogin())//��¼�ɹ�������޸������
    {
        switch (MenuSelect())	//�˵�ѡ��
        {
        case Exit:		//�˳�����
            _Exit(0);
            break;
        case ChangePassword:	//�޸�����
            system("cls");
            changePassword();
            break;
        case Show:		//��ʾ����ѧ����Ϣ
            system("cls");
            Show_Information();
            break;
        case Add:		//���ѧ����Ϣ
            system("cls");
            Add_Information();//����ѧ����Ϣ
            break;
        case Sort:		//��ѧ����Ϣ�ֽܷ�������
            system("cls");
            Sord_Information();
            break;
        case Change:	//�޸�ѧ����Ϣ
            system("cls");
            Change_Information();
            break;
        case Delete:	//ɾ��ѧ����Ϣ
            system("cls");
            Delete_Information();
            break;
        case Search:	//��ѯѧ����Ϣ
            system("cls");
            Search_Information();
            Quit();
            break;
        }
    }
}
int main()
{
    Init();
    MainMenu();
}
