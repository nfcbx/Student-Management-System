#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <tchar.h>
#include <list>

using namespace std;

char UserName[15],UserPassword[15];//用户输入的用户名及密码
char realName[15],realPassword[15];//正确的用户名及密码
char defaultName[15]="admin",defaultPassword[15]="admin";//默认用户名及密码
bool isChangePassword=false;//记录是否修改密码
bool isChangeInformation=false;//记录是否修改学生信息
int changeTimes=0;//记录修改密码时密码错误的次数
int stu_cnt=0;//学生总数
char *oldFileName,*newFileName;//数据文件的绝对地址

struct Student  //成绩结构体
{
    char name[9];//姓名
    char num[9];//学号
    int age;//年龄
    char sex[1];//性别
    int Math;//数学
    int English;//英语
    int Program;//计算机
    int sum;//总分
} s;

void Init();//初始化登录页面
void readFileAdd();//读取数据文件的绝对目录
void readStudent();//读取学生数目
void StuManage();//学生信息管理系统 管理端字符图标
void Login();//登录系统
int isLogin();//判断是否登录成功
int MenuSelect();//菜单选择
void MainMenu();//主菜单界面
void Head();//学生信息管理系统字符图标
void printfError();//显示错误信息
void changePassword();//修改密码
void scanfInformation();//输入学生信息
void Quit();//退出程序或重新进入主菜单
void readfile();//读入文件
void writefile();//写出文件
void Change_Information();//更新
void Delete_Information();//删除
void Show_Information();//输出学生信息
void Add_Information();//添加学生信息
void Search_Information();//查询学生信息
bool Find_Information();//查找学生信息
void Sord_Information();//排序学生信息
void Show_Sorted(list<Student>& ss);//显示排序后的学生信息

typedef enum Menu
{
    Exit,ChangePassword,Show,Add,Sort,Change,Delete,Search
} MENU;



//初始化登录页面
void Init()
{
    readFileAdd();
    readStudent();

    system("mode con cols=120 lines=40");//初始化缓冲区大小
    printf("欢迎使用本系统！\n");
    int i;
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t");
    char heihei[] = { "即将进入学生管理系统..." };
    for (i = 0; i < strlen(heihei); i++)
    {
        printf("%c", heihei[i]);
        Sleep(25);
    }
    system("cls");
    Login();
}

void readFileAdd()//读取数据文件的绝对目录
{
    TCHAR _szPath[MAX_PATH + 1]= {0};
    GetModuleFileName(NULL, _szPath, MAX_PATH);
    (_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串
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
//读取学生数目
void readStudent()
{

    ifstream fin("stu.dat",ios::binary);
    fin.seekg(0,ios::end);
    streampos ps=fin.tellg();
    stu_cnt=ps/sizeof(s);
    fin.close();
}

//学生信息管理系统字符图标
void Head()
{
    printf("\n");
    printf("\t\t\t\t\t╭ ⺌%╮                   ╭ ```╮  \n");
    printf("\t\t\t\t\t(@^o^@) 学生信息管理系统 (⌒:⌒)\n");
    printf("\t\t\t\t\t(~):(~)                  (~)v(~) \n");
    printf("\n\n\n");
}

//学生信息管理系统 管理端字符图标
void StuManage()
{
    printf("\n");
    printf("\t\t\t\t\t╭ ⺌%╮                           ╭ ```╮  \n");
    printf("\t\t\t\t\t(@^o^@) 学生信息管理系统   管理端(⌒:⌒)\n");
    printf("\t\t\t\t\t(~):(~)                          (~)v(~) \n");
    printf("\n\n\n");
}

//显示错误信息
void printfError()
{
    printf("\n\t\t\t\t\t\t格式错误！请重新输入：");
}

//登录系统
void Login()
{
    StuManage();
    char xing[] = { "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " };
    for (int i = 0; i<strlen(xing); i++)
    {
        printf("%c", xing[i]);
        Sleep(5);
    }
    printf("\n\n\t\t\t\t\t\t请输入您的账号密码:\n\n\n\n\t\t\t\t\t\t账号:");
    cin>>UserName;
    printf("\n\n\t\t\t\t\t\t密码:");
    cin>>UserPassword;

}

//判断是否登录成功
int isLogin()
{
    int times = 0;	//密码输入次数

    ifstream passIn;//输入流
    passIn.open("password.dat",ios::in|ios::binary);//为输入打开password.txt
    if(!passIn.is_open())//如果打开失败，则创建文件
    {
        ofstream passOut;//输出流
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
        times++;	//密码输入错误 times++
        if (times > 3)
        {
            printf("\n\n\n\n\t\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", times);
            Sleep(1000);
            system("cls");
            char shutdown[] = { "系统将于%d秒后关闭..." };
            for (int i = 0; i < 3; i++)
            {
                printf(shutdown, 3 - i);
                Sleep(1000);
                system("cls");
            }
            exit(0);
        }
        printf("\n\n\n\n\t\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - times);
        getch();
        system("cls");
        Login();
    }
    return 1;

}

//修改密码
void changePassword()
{
    char tempName[15],tempPassword[15],oldPassword[15];

    Head();
    printf("\t\t\t**********************修改用户名及密码*********************\n\n\n");
    cout<<"\t\t\t您的用户名为："<<realName;
    cout<<endl<<"\n\t\t\t要继续操作，请首先验证登录者是您本人，请输入您的旧密码：";
    cin>>oldPassword;

    if(strcmp(oldPassword,realPassword)==0)//密码正确
    {

        cout<<"\n\t\t\t请输入您的新用户名（不多于14位）:";
        cin>>tempName;
        while(strlen(tempName)>14)
        {
            printf("\n\t\t\t格式错误！请重新输入：");
            cin>>tempName;
        }
        cout<<"\n\t\t\t请输入您的新密码（不多于14位）:";
        cin>>tempPassword;
        while(strlen(tempPassword)>14)
        {
            printf("\n\t\t\t格式错误！请重新输入：");
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
        cout<<endl<<"\t\t\t恭喜您，修改成功，请牢记您的用户名及密码~";
    }
    while(strcmp(oldPassword,realPassword))//密码错误
    {
        changeTimes++;
        if (changeTimes > 3)
        {
            printf("\n\n\n\n\t\t\t账号或密码输入错误累计达到%d次，系统将于3秒后关闭", changeTimes);
            Sleep(3000);
            system("cls");
            char shutdown[] = { "系统将于%d秒后关闭..." };
            for (int i = 0; i < 3; i++)
            {
                printf(shutdown, 3 - i);
                Sleep(1000);
                system("cls");
            }
            exit(0);
        }
        printf("\n\n\n\t\t\t账号或密码输入错误,你还有%d次登录机会，按任意键重新登录...", 4 - changeTimes);
        getch();
        system("cls");
        changePassword();
    }
    Quit();
}

//退出程序或重新进入主菜单
void Quit()
{
    char ch;
    printf("\n\t ");
    for (int i = 0; i < 50; i++)
    {
        printf("* ");
        Sleep(10);
    }
    printf("\n\n\t\t\t\t要返回登录界面按任意键\t\t退出并保存数据请按Esc键\n");
    ch = getch();
    if (ch == 0x1b)	//esc键按下
    {
//		SaveData();
        _Exit(0);
    }
    //重新进入主菜单
    MainMenu();
}

//写出文件
void writefile()
{
    ofstream fout("stu.dat",ios::binary|ios::app);//输出流对象
//    fout.open("stu.dat",ios::binary|ios::ate);
    fout.write((char*)&s, sizeof(s));
    fout.close();
}

//读入文件
void readfile()
{
    ifstream fin("stu.dat",ios::in|ios::binary);//读入流对象
    while(fin.read((char*)&s,sizeof(s)))
    {
        printf("\t\t\t");
        printf("%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",s.num,s.name,s.age,s.sex,s.Math,s.English,s.Program,s.sum);
    }
    fin.close();
}

//查找学生信息
bool Find_Information(char *id)
{
    ifstream fin("stu.dat",ios::in|ios::binary);//读入流对象
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
//输入学生信息
void scanfInformation()
{
    char id[9];
    char _name[9];
    printf("\n\t\t\t\t\t\t学号（不超过9个字符）:");
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
            printf("\n\t\t\t\t\t\t已存在该学生的信息！请重新输入：");
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

    printf("\n\t\t\t\t\t\t姓名（不超过9个字符）:");
    cin>>_name;
    while(strlen(_name)>9)
    {
        printfError();
        cin>>_name;
    }
    strncpy(s.name,_name,9);

    cout<<"\n\t\t\t\t\t\t输入年龄：";
    cin>>s.age;
    while(s.age<0||s.age>100)
    {
        printfError();
        cin>>s.age;
    }

    cout<<"\n\t\t\t\t\t\t输入性别（M为男性，F为女性）：";
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

    printf("\n\t\t\t\t\t\t高等数学（整数百分制）:");
    cin>>s.Math;
    while(s.Math<0||s.Math>100)
    {
        printfError();
        cin>>s.Math;
    }

    printf("\n\t\t\t\t\t\t大学英语（整数百分制）:");
    cin>>s.English;
    while(s.English<0||s.English>100)
    {
        printfError();
        cin>>s.English;
    }

    printf("\n\t\t\t\t\t\t程序设计（整数百分制）:");
    cin>>s.Program;
    while(s.Program<0||s.Program>100)
    {
        printfError();
        cin>>s.Program;
    }

    s.sum=s.Math+s.English+s.Program;
    printf("\n\t\t\t\t\t\t该学生的总分为：%d",s.sum);
}
//添加学生信息
void Add_Information()
{
    char n;
    do
    {
        system("cls");
        Head();
        printf("\t\t\t\t\t\t添加学生信息:\n\n\n\n");
        scanfInformation();
        writefile();
        stu_cnt++;
        printf("\n\n\t\t\t\t\t\t按Y继续，按任意键返回。");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}

//输出学生信息
void Show_Information()
{
    Head();
    if(stu_cnt==0)
    {
        printf("\t\t\t**********************本名单共有 %d 名学生*********************\n\n\n", stu_cnt);
        printf("\t\t\t暂无学生信息！\n");
    }
    else
    {
        printf("\t\t\t**********************本名单共有 %d 名学生*********************\n\n\n", stu_cnt);
        printf("\t\t\t学号\t  姓名\t   年龄\t  性别\t  高数\t  英语\t  程序设计\t总分\n\n");
        readfile();
    }
    Quit();
}

//查询学生信息
void Search_Information()
{
    char n;
    do
    {
        system("cls");
        Head();
        char id[9];
        printf("\t\t\t\t\t\t查询学生信息：\n\n");
        printf("\t\t\t\t\t\t请输入学生学号：");
        cin>>id;
        if(Find_Information(id))
        {
            printf("\n\n\n\t\t\t\t\t\t要查询的学生信息...\n\n");
            printf("\t\t\t学号\t  姓名\t   年龄\t  性别\t  高数\t  英语\t  程序设计\t总分\n\n");
            printf("\t\t\t");
            printf("%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",s.num,s.name,s.age,s.sex,s.Math,s.English,s.Program,s.sum);
        }
        else
            printf("\n\n\n\n\t\t\t\t\t   没有找到要查询的学生信息......\n\n");
        printf("\n\n\t\t\t\t\t\t按Y继续查询，按任意键返回。\n");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}
void Delete_Information()//删除
{
    char n;
    do
    {
        system("cls");
        Head();
        char id[9];
        printf("\t\t\t\t\t请输入要删除学生的学号：");
        cin>>id;
        if(Find_Information(id))
        {
            printf("\n\t\t\t\t\t请核对学生信息...\n\n");
            printf("\t\t\t学号\t  姓名\t   年龄\t  性别\t  高数\t  英语\t  程序设计\t总分\n\n");
            printf("\t\t\t");
            printf("%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",s.num,s.name,s.age,s.sex,s.Math,s.English,s.Program,s.sum);
            printf("\n\t\t\t\t\t确认无误请按Y删除，如有误按Esc重新输入！");
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
                printf("\n\n\t\t\t\t\t删除成功！");
                stu_cnt--;
            }
        }
        else
        {
            cout<<"\n\t\t\t\t\t学生不存在！按Y重新输入，按任意键返回。";
            char m;
            m=getch();
            if(m=='Y'||m=='y')
                Delete_Information();
            else
                Quit();

        }
        printf("\n\n\t\t\t\t\t按Y继续删除，按任意键返回。");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}

void Change_Information()//修改学生信息
{
    char n;
    do
    {
        system("cls");
        Head();
        printf("\t\t\t\t\t请输入要修改学生的学号：");
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
                    printf("\n\t\t\t\t\t请依次输入下列修改的项目，不需要的请原样输入\n");
                    isChangeInformation=true;
                    scanfInformation();
                    out.write((char*)&s, sizeof(s));
                    printf("\n\n\t\t\t\t\t\t修改成功！");
                }
            }
            in.close();
            out.close();
            remove(oldFileName);
            rename(newFileName,oldFileName);
        }
        else
        {
            cout<<"\n\t\t\t\t\t学生不存在！按Y重新输入，按任意键返回。";
            char m;
            m=getch();
            if(m=='Y'||m=='y')
                Change_Information();
            else
                Quit();
        }
        printf("\n\n\t\t\t\t\t是否继续修改？按Y继续，按任意键返回。");
        n=getch();
    }
    while(n=='Y'||n=='y');
    Quit();
}

//自定义排序规则
bool StuCmp(const Student& s1,const Student& s2)
{
    return s1.sum>s2.sum;
}

//排序学生信息
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

//显示排序后的学生信息
void Show_Sorted(list<Student>& ss)
{
    int i=1;
    Head();
    if(stu_cnt==0)
    {
        printf("\t\t\t**********************本名单共有 %d 名学生*********************\n\n\n", stu_cnt);
        printf("\t\t\t暂无学生信息！\n");
    }
    else
    {
        printf("\t\t\t**********************本名单共有 %d 名学生*********************\n\n\n", stu_cnt);
        printf("\t\t\t序号\t学号\t  姓名\t   年龄\t  性别\t  高数\t  英语\t  程序设计\t总分\n\n");
        for(auto it=ss.begin(); it!=ss.end(); it++)
        {
            printf("\t\t\t%-8d%-10s%-10s%-8d%-6s%-8d%-8d%-8d\t%-8d\n",i,it->num,it->name,it->age,it->sex,it->Math,it->English,it->Program,it->sum);
            i++;
        }
    }
}
//菜单选择
int MenuSelect()
{
    char c;
    do
    {
        system("cls");
        Head();
        printf("\t\t\t\t   ╭═════════════════════════════════○●○●═══╮\n");
        printf("\t\t\t\t   │              学生信息管理系统              │\n");
        printf("\t\t\t\t   ╰═══○●○●═════════════════════════════════╯\n");
        printf("\t\t\t\t   ┌───────────────────────────────────────────-┐\n");
        printf("\t\t\t\t   │                                            │\n");
        printf("\t\t\t\t   │ 1. 修改密码                    2. 显示数据 │\n");
        printf("\t\t\t\t   │                                            │\n");
        printf("\t\t\t\t   │ 3. 添加数据                    4. 数据排名 │\n");
        printf("\t\t\t\t   │                                            │\n");
        printf("\t\t\t\t   │ 5. 修改数据                    6. 删除数据 │\n");
        printf("\t\t\t\t   │                                            │\n");
        printf("\t\t\t\t   │ 7. 查询数据                    0. 退出程序 │\n");
        printf("\t\t\t\t   │                                            │\n");
        printf("\t\t\t\t   └────────────────────────────────────────────┘\n");
        printf("\t\t\t\t\t\t  请您选择(0-7):");
        c = getche();
    }
    while (c < '0' || c > '7');
    return c - '0';
}

//主菜单界面
void MainMenu()
{
    if (isChangePassword||isLogin())//登录成功或完成修改密码后
    {
        switch (MenuSelect())	//菜单选择
        {
        case Exit:		//退出程序
            _Exit(0);
            break;
        case ChangePassword:	//修改密码
            system("cls");
            changePassword();
            break;
        case Show:		//显示所有学生信息
            system("cls");
            Show_Information();
            break;
        case Add:		//添加学生信息
            system("cls");
            Add_Information();//输入学生信息
            break;
        case Sort:		//对学生信息总分进行排序
            system("cls");
            Sord_Information();
            break;
        case Change:	//修改学生信息
            system("cls");
            Change_Information();
            break;
        case Delete:	//删除学生信息
            system("cls");
            Delete_Information();
            break;
        case Search:	//查询学生信息
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
