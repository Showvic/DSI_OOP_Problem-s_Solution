#include <bits/stdc++.h>

using namespace std;

int totalEarnings=0;

class Student
{
    int cls;
    string name;
    bool subject[3];//M,E,B
    double avgMarks;
    int daysTaught;
    int earnings;
    int factor;//extra variable for tracking the subject number
    int examdays;//extra variable for tracking the exam days
public:
    //void setData(int cls,string name,int arr,double avg,int taught days,int earnings )
    void addStudent();
    void editStudent();
    Student(int cls,string name,bool arr[],int factor)//constructor for initializing values
    {
        this->cls=cls;
        this->name = name;
        for(int i=0; i<3; i++)
        {
            this->subject[i]=arr[i];
        }
        this->factor = factor;
        this->avgMarks = 0;
        this->daysTaught =0;
        this->earnings = 0;
        this->examdays = 0;
    }
    int getclass()
    {
        return cls;
    }
    void setclass(int c)
    {
        this->cls=c;
    }
    string getname()
    {
        return this->name;
    }
    void setname(string n)
    {
        this->name=n;
    }
    bool * getsubject()
    {
        return this->subject;
    }
    void setsubject(bool s[])
    {
        for(int i=0; i<3; i++)
        {
            this->subject[i]=s[i];
        }
    }
    double getavgMarks()
    {
        return this->avgMarks;
    }
    void setavgMarks(double avgmrk)
    {
        this->avgMarks = avgmrk;
    }

    int getdaysTaught()
    {
        return this->daysTaught;
    }
    void setdaysTaught(int d)
    {
        this->daysTaught=d;
    }
    int getEarnings()
    {
        return this->earnings;
    }
    void setEarnings(int e)
    {
        this->earnings =e;
    }
    int getFactor()
    {
        return this->factor;
    }
    void setFactor(int f)
    {
        this->factor=f;
    }
    int getExamdays()
    {
        return this->examdays;
    }
    void setExamdays(int ed)
    {
        this->examdays = ed;
    }

};



vector<Student>studentList;//Global vector for storing Student List

void addStudent()
{
    int cls;
    string name;
    bool arr[3];
    int factor=0;
    memset(arr,false,3);// Initialize all elements of array = false
    cout<<"Enter the class of the student : ";
    cin>>cls;

    cout<<"Enter the name of the student  : ";
    cin>>name;
    cout<<"Enter the subject you taught Math English Bangla respectively(1 for TRUE & 0 for FALSE) example 1 0 1 : ";
    for(int i=0; i<3; i++)
    {
        cin>>arr[i];
        if(arr[i]==true)
            factor++;
    }
    Student st(cls,name,arr,factor);//Call constructor
    studentList.push_back(st);//store object into Global List
    cout<<endl;

}

void editStudent()
{
    string name;
    int cls;
    cout<<"Enter student's class & name whose info you want to edit"<<endl;
    cout<<"Class : ";
    cin>>cls;
    cout<<"Name  : ";
    cin>>name;
    int n = studentList.size();
    for(int i=0; i<n; i++)//Iterate through all over the List
    {
        Student &tem=studentList[i];
        if(tem.getclass()==cls && tem.getname()==name)//Checking the conditions
        {
            int day,mark;
            cout<<"Add day(usually 1) and Marks(-1, if exam not taken) : ";//one day you may not take any exam only teach
            cin>>day>>mark;

            int daysTaught = tem.getdaysTaught();
            int earnings = tem.getEarnings();
            int factor = tem.getFactor();
            double avgmarks = tem.getavgMarks();
            int exmdays = tem.getExamdays();

            tem.setdaysTaught((daysTaught+ day));//Increasing daysTaught's value by adding day's value
            tem.setEarnings(( earnings+(day*factor) ));//increasing earnings's value by adding day*factor value
            totalEarnings += (day*factor);//Increasing total earning (global variable's) value


            //totalDaysTaught+=day;
            if(mark!=-1)//if one day you taught and give marks
            {
                double totalMarks = (avgmarks*exmdays);
                totalMarks+=(double)mark;
                tem.setExamdays((exmdays+1));//exam days increases(needed for avg marks)
                tem.setavgMarks((totalMarks/tem.getExamdays()));
            }

            break;
        }
    }

}

void delete_student()
{
    int cls;
    string name;
    cout<<"Enter class and name of a student you want to delete\n";
    cout<<"Class : ";
    cin>>cls;
    cout<<endl;
    cout<<"Name : ";
    cin>>name;

    int n = studentList.size();//determining the student list size
    int pos;
    for(int i=0; i<n; i++)
    {
        Student tem =  studentList[i];//copy the object to another object
        if(tem.getclass()==cls && tem.getname()==name)//checking validation
        {

            studentList.erase(studentList.begin()+i);//delete the object from the student list
            break;
        }
    }

}

void list_of_students()
{
    int cls;
    string name;
    char ch;
    cout<<"What you want to choose: Class(press c) or Name(press n): ";
    cin>>ch;
    if(ch=='c'||ch=='C')
    {
        cout<<"Enter a class to see students : ";
        cin>>cls;
        int n=studentList.size();
        cout<<setw(20)<<"Name"<<setw(10)<<"Earnings"<<setw(10)<<" Average_Marks "<<endl;
        for(int i=0; i<n; i++)
        {
            if(studentList[i].getclass()==cls)//checking validation through classes
            {
                Student tem = studentList[i];
                cout<<setw(20)<<tem.getname()<<setw(10)<<tem.getEarnings()<<setw(10)<<tem.getavgMarks()<<endl;
            }
        }
    }
    else if(ch=='n'||ch=='N')
    {
        cout<<"Enter the name of a student : ";
        cin>>name;
        int n=studentList.size();
        cout<<setw(5)<<"Class"<<setw(25)<<"Subject(s)"<<setw(20)<<"Average_Marks"<<setw(25)<<"Total_day_taught"<<setw(15)<<"Total_earnings"<<endl;
        for(int i=0; i<n; i++)
        {
            if(studentList[i].getname()==name)
            {
                string subjt="";
                Student tem = studentList[i];
                bool *p = tem.getsubject();//get the bool subject array using pointer
                cout<<setw(5)<<tem.getclass();
                for(int j=0; j<3; j++)
                {
                    if(*(p+j)==true&&j==0)
                        subjt+="Math,";
                    else if(*(p+j)==true && j==1)
                        subjt+="English,";
                    else if(*(p+j)==true && j==2)
                        subjt+="Bangla,";
                }
                cout<<setw(25)<<subjt<<setw(20)<<tem.getavgMarks()<<setw(25)<<tem.getdaysTaught()<<setw(15)<<tem.getEarnings()<<endl;
                break;
            }
        }
    }
    else
    {
        cout<<"Invalid choice"<<endl;
    }


}

void seeOverall()
{
    int n = studentList.size();
    int totalDayTaught_allClasses=0;
    int totalDayTaught_class8=0,totalDayTaught_class9=0,totalDayTaught_class10=0;
    int indvEarning_class8=0,indvEarning_class9=0,indvEarning_class10=0;
    int indvEarning_math=0,indvEarning_english=0,indvEarning_bangla=0;
    double avgMarks_allStudent=0;
    for(int i=0; i<n; i++)//iterate through the student list to get the values
    {
        Student tem = studentList[i];
        totalDayTaught_allClasses += tem.getdaysTaught();
        avgMarks_allStudent += tem.getavgMarks();
        if(tem.getclass()==8)
        {
            totalDayTaught_class8 += tem.getdaysTaught();
            indvEarning_class8 += tem.getEarnings();
        }
        else if(tem.getclass()==9)
        {
            totalDayTaught_class9 += tem.getdaysTaught();
            indvEarning_class9 += tem.getEarnings();
        }
        else if(tem.getclass()==10)
        {
            totalDayTaught_class10 += tem.getdaysTaught();
            indvEarning_class10 += tem.getEarnings();
        }
        bool *p = tem.getsubject();
        for(int j=0; j<3; j++)//checking individual earning for a student on subject array
        {
            if(*(p+j)==true&&j==0)
                indvEarning_math += (tem.getEarnings()/tem.getFactor());
            else if(*(p+j)==true && j==1)
                indvEarning_english += (tem.getEarnings()/tem.getFactor());
            else if(*(p+j)==true && j==2)
                indvEarning_bangla += (tem.getEarnings()/tem.getFactor());
        }

    }

    cout<<"Total days taught across all classes : "<<totalDayTaught_allClasses<<endl;
    cout<<endl;

    cout<<setw(50)<<"Individual days taught in each class"<<endl;
    cout<<setw(30)<<"Class_8"<<setw(10)<<"Class_9"<<setw(10)<<"Class_10"<<endl;
    cout<<setw(30)<<totalDayTaught_class8<<setw(10)<<totalDayTaught_class9<<setw(10)<<totalDayTaught_class10<<endl;

    cout<<endl;
    cout<<"Total Earnings : "<<totalEarnings<<endl;
    cout<<endl;

    cout<<setw(50)<<"Individual Earnings of each class"<<endl<<endl;
    cout<<setw(30)<<"Class_8"<<setw(10)<<"Class_9"<<setw(10)<<"Class_10"<<endl;
    cout<<setw(30)<<indvEarning_class8<<setw(10)<<indvEarning_class9<<setw(10)<<indvEarning_class10<<endl;
    cout<<endl;

    cout<<setw(50)<<"Individual Earnings of each subject"<<endl<<endl;
    cout<<setw(30)<<"Math"<<setw(10)<<"English"<<setw(10)<<"Bangla"<<endl;
    cout<<setw(30)<<indvEarning_math<<setw(10)<<indvEarning_english<<setw(10)<<indvEarning_bangla<<endl;
    cout<<endl;

    cout<<setw(50)<<"Average marks of all students"<<endl<<endl;

    cout<<setw(20)<<"Class"<<setw(20)<<"Name"<<setw(20)<<"Average_marks"<<endl;
    for(int i=0; i<n; i++)
    {
        Student tem = studentList[i];
        cout<<setw(20)<<tem.getclass()<<setw(20)<<tem.getname()<<setw(20)<<tem.getavgMarks()<<endl;
    }


}

int main()
{

    cout<<"1 for ADD A STUDENT\n2 for EDIT A STUDENT\n3 for DELETE A STUDENT\n4 for see INDIVIDUAL INFO\n5 for see OVERALL INFO\n0 for EXIT"<<endl;
    cout<<endl;
    int test;
    do
    {
        cout<<"Enter case value : ";
        cin>>test;

        if(test==1)
        {
            cout<<"Add Student\n"<<endl;
            addStudent();
            cout<<endl;
        }
        else if(test==2)
        {
            cout<<"Edit Student\n"<<endl;
            editStudent();
            cout<<endl;
        }
        else if(test==3)
        {
            cout<<"Delete Student\n"<<endl;
            delete_student();
            cout<<endl;
        }
        else if(test==4)
        {
            cout<<"List of  Students\n"<<endl;
            list_of_students();
            cout<<endl;
        }
        else if(test==5)
        {
            cout<<"Overall Student Info\n"<<endl;
            seeOverall();
            cout<<endl;
        }
        else if(test>5)
        {
            cout<<"Invalid Choice.......\nEnter Case value again!"<<endl;
            cout<<endl;
//        int n = studentList.size();
//        cout<<setw(30)<<"STUDENT TABLE\n";
//        cout<<setw(5)<<"Class"<<setw(30)<<"Name"<<setw(25)<<" Average_Marks "<<setw(10)<<" Days_Taught "<<setw(10)<<" Earnings "<<endl;
//
//        for(int i=0;i<n;i++){
//            Student tem = studentList[i];
//            cout<<setw(5)<<tem.getclass()<<setw(30)<<tem.getname()<<setw(20)<<tem.getavgMarks()<<setw(10)<<tem.getdaysTaught()<<setw(10)<<tem.getEarnings()<<endl;
//        }
        }
    }
    while(test!=0);

    return 0;
}
