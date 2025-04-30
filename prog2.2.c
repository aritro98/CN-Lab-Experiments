#include <stdio.h>
#include <string.h>
struct dob{
    int day;
    int month;
    int year;
};
struct stuinfo{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};
void StuVal(struct stuinfo student){
    printf("Roll No:%d\n",student.roll_no);
    printf("Name:%s\n",student.name);
    printf("CGPA:%.2f\n",student.CGPA);
    printf("Date of Birth:%02d/%02d/%04d\n",student.age.day,student.age.month,student.age.year);
}
void StuAddr(struct stuinfo *student){
    printf("Roll No:%d\n",student->roll_no);
    printf("Name:%s\n",student->name);
    printf("CGPA:%.2f\n",student->CGPA);
    printf("Date of Birth:%02d/%02d/%04d\n",student->age.day,student->age.month,student->age.year);
}
int main(){
    struct stuinfo student;
    printf("Enter Roll No:");
    scanf("%d",&student.roll_no);
    printf("Enter Name:");
    scanf("%s",student.name);
    printf("Enter CGPA:");
    scanf("%f",&student.CGPA);
    printf("Enter Date of Birth (day/month/year):");
    scanf("%d %d %d",&student.age.day,&student.age.month,&student.age.year);
    printf("\nUsing call-by-value:\n");
    StuVal(student);
    printf("\nUsing call-by-address:\n");
    StuAddr(&student);
    return 0;
}

