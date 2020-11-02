/****************************************
** 程序描述:学生成绩管理系统v3.0
** 日期:20201102
** 创建人：200110725
****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

void Menu();
void InputRecord(int stuID[], char stuName[][20], int stuScore[][6], int *num, int *Subject_num);
void ListRecord(int stuID[], char stuName[][20], int stuScore[][6], int num, int Subject_num);
void CalculateCourse(int stuScore[][6], int num, int Subject_num, int tot[]);
void CalculateStudent(int stuScore[][6], int num, int Subject_num, int tot[]);
void SortScore(int retID[], char retName[][20], int retScore[][6], int stuID[], char stuName[][20], int stuScore[][6], int num,  int Subject_num, int (*compare)(int a, int b));
void SortID(int retID[], char retName[][20], int retScore[][6], int stuID[], char stuName[][20], int stuScore[][6], int num, int Subject_num, int (*compare)(int a, int b));
void SortName(int retID[], char retName[][20], int retScore[][6], int stuID[], char stuName[][20], int stuScore[][6], int num, int Subject_num);
int SearchID(int stuID[], int num);
int SearchName(char stuName[][20], int num);
void OutputStu(int stuID[], char stuName[][20], int stuScore[][6], int Subject_num, int pos);

void AnalysisStu(int stuScore[][6], int num, int Subject_num);

int Ascending(int a, int b);
int Descending(int a, int b);
void swapNum(int *a, int *b);
void swapStr(char a[], char b[]);

int main()
{

    printf("Number:200110725\n");
	printf("subject No.7\n");
	printf("\n");
	int stuID[N]; char stuName[N][20]; int stuScore[N][6];
	int ansID[N]; char ansName[N][20]; int ansScore[N][6];
	int num = 0, flag = 0, Subject_num = 0;
	while(1)
    {
        int opt = 0, tot[N], pos;
        double average[N];
        Menu();
        scanf("%d", &opt);
        if(opt > 1 && !flag)
        {
            printf("No data!\n");
            InputRecord(stuID, stuName, stuScore, &num, &Subject_num);
            flag = 1;
            printf("\n");
            continue;
        }
        switch(opt)
        {
        case 1:
            InputRecord(stuID, stuName, stuScore, &num, &Subject_num);
            flag = 1;
            break;
        case 2:
            ListRecord(stuID, stuName, stuScore, num, Subject_num);
            break;
        case 3:
            CalculateCourse(stuScore, num, Subject_num, tot);
            for(int i = 0; i < Subject_num; i++)
            {
                average[i] = (double)tot[i] / num;
            }
            for(int i = 0; i < Subject_num; i++)
            {
                printf("subject %d: total score is: %d, average score is: %.4lf\n", i + 1, tot[i], average[i]);
            }
            break;
        case 4:
            CalculateStudent(stuScore, num, Subject_num, tot);
            for(int i = 0; i < num; i++)
            {
                average[i] = (double)tot[i] / Subject_num;
            }
            for(int i = 0; i < num; i++)
            {
                printf("subject %d: total score is: %d, average score is: %.4lf\n", i + 1, tot[i], average[i]);
            }
            break;
        case 5:
            SortScore(ansID, ansName, ansScore, stuID, stuName, stuScore, num, Subject_num, Descending);
            ListRecord(ansID, ansName, ansScore, num, Subject_num);
            break;
        case 6:
            SortScore(ansID, ansName, ansScore, stuID, stuName, stuScore, num, Subject_num, Ascending);
            ListRecord(ansID, ansName, ansScore, num, Subject_num);
            break;
        case 7:
            SortID(ansID, ansName, ansScore, stuID, stuName, stuScore, num, Subject_num, Ascending);
            ListRecord(ansID, ansName, ansScore, num, Subject_num);
            break;
        case 8:
            SortName(ansID, ansName, ansScore, stuID, stuName, stuScore, num, Subject_num);
            ListRecord(ansID, ansName, ansScore, num, Subject_num);
            break;
        case 9:
            pos = SearchID(stuID, num);
            OutputStu(stuID, stuName, stuScore, Subject_num, pos);
            break;
        case 10:
            pos = SearchName(stuName, num);
            OutputStu(stuID, stuName, stuScore, Subject_num, pos);
            break;
        case 11:
            AnalysisStu(stuScore, num, Subject_num);
            break;
        case 0:
            exit(0);
        default:
            printf("Input Error\n");
        }
        printf("\n");
    }
	return 0;
}
void Menu()
{

    printf("1.Input record\n");
    printf("2.List record\n");
    printf("3.Calculate total and average score of every course\n");
    printf("4.Calculate total and average score of every student\n");
    printf("5.Sort in descending order by total score of every student\n");
    printf("6.Sort in ascending order by total score of every student\n");
    printf("7.Sort in ascending order by StudentID\n");
    printf("8.Sort in dictionary order by name\n");
    printf("9.Search by StudentID\n");
    printf("10.Search by name\n");
    printf("11.Statistic analysis for every course\n");
    printf("0.Exit\n");
    printf("Please enter your choice:");
}
void InputRecord(int stuID[], char stuName[][20], int stuScore[][6], int *num, int *Subject_num)
{
    *num = 0; *Subject_num = 0;
    int ERROR = 1;
    while(ERROR)
    {
        printf("Please input the number of students:");
        scanf("%d", num);
        printf("Please input the number of subjects:");
        scanf("%d", Subject_num);
        if(*num > N || *Subject_num > 6)
        {
            ERROR = 1;
            printf("Input overrun! Please input again.\n");
        }
        else
        {
            ERROR = 0;
        }
    }
    for(int i = 0; i < *num; i++)
    {
        printf("Please input #%d student number and name:\n", i + 1);
        scanf("%d%s", &stuID[i], stuName[i]);
        printf("Please input the score of each subject:\n");
        for(int j = 0; j < *Subject_num; j++)
        {
            scanf("%d", &stuScore[i][j]);
        }
    }
    return;
}
void ListRecord(int stuID[], char stuName[][20], int stuScore[][6], int num, int Subject_num)
{
    for(int i = 0; i < num; i++)
    {
        printf("%d. %d %s\n", i + 1, stuID[i], stuName[i]);
        for(int j = 0; j < Subject_num; j++)
        {
            printf("%-3d", stuScore[i][j]);
        }
        printf("\n");
    }
}
void CalculateCourse(int stuScore[][6], int num, int Subject_num, int tot[])
{
    for(int i = 0; i < Subject_num; i++)
    {
        tot[i] = 0;
    }
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < Subject_num; j++)
        {
            tot[j] += stuScore[i][j];
        }
    }
    return;
}
void CalculateStudent(int stuScore[][6], int num, int Subject_num, int tot[])
{
    for(int i = 0; i < num; i++)
    {
        tot[i] = 0;
    }
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < Subject_num; j++)
        {
            tot[i] += stuScore[i][j];
        }
    }
    return;
}
void SortScore(int retID[], char retName[][20], int retScore[][6], int stuID[], char stuName[][20], int stuScore[][6], int num,  int Subject_num, int (*compare)(int a, int b))
{
    int totScore[N];
    for(int i = 0; i < num; i++)
    {
        totScore[i] = 0;
        retID[i] = stuID[i];
        strcpy(retName[i], stuName[i]);
        for(int j = 0; j < Subject_num; j++)
        {
            retScore[i][j] = stuScore[i][j];
            totScore[i] += stuScore[i][j];
        }
    }
    for(int i = 0; i < num - 1; i++)
    {
        for(int j = 0; j < num - 1; j++)
        {
            if(!compare(totScore[j], totScore[j + 1]))
            {
                swapNum(&retID[j], &retID[j + 1]);
                swapStr(retName[j], retName[j + 1]);
                for(int k = 0; k < Subject_num; k++)
                {
                    swapNum(&retScore[j][k], &retScore[j + 1][k]);
                }
                swapNum(&totScore[j], &totScore[j + 1]);
            }
        }
    }
}
void SortID(int retID[], char retName[][20], int retScore[][6], int stuID[], char stuName[][20], int stuScore[][6], int num, int Subject_num, int (*compare)(int a, int b))
{
    for(int i = 0; i < num; i++)
    {
        retID[i] = stuID[i];
        strcpy(retName[i], stuName[i]);
        for(int j = 0; j < Subject_num; j++)
        {
            retScore[i][j] = stuScore[i][j];
        }
    }
    for(int i = 0; i < num - 1; i++)
    {
        for(int j = 0; j < num - 1; j++)
        {
            if(!compare(retID[j], retID[j + 1]))
            {
                swapNum(&retID[j], &retID[j + 1]);
                swapStr(retName[j], retName[j + 1]);
                for(int k = 0; k < Subject_num; k++)
                {
                    swapNum(&retScore[j][k], &retScore[j + 1][k]);
                }
            }
        }
    }
}
void SortName(int retID[], char retName[][20], int retScore[][6], int stuID[], char stuName[][20], int stuScore[][6], int num, int Subject_num)
{
    for(int i = 0; i < num; i++)
    {
        retID[i] = stuID[i];
        strcpy(retName[i], stuName[i]);
        for(int j = 0; j < Subject_num; j++)
        {
            retScore[i][j] = stuScore[i][j];
        }
    }
    for(int i = 0; i < num - 1; i++)
    {
        for(int j = 0; j < num - 1; j++)
        {
            if(strcmp(retName[j], retName[j + 1]) > 0)
            {
                swapNum(&retID[j], &retID[j + 1]);
                swapStr(retName[j], retName[j + 1]);
                for(int k = 0; k < Subject_num; k++)
                {
                    swapNum(&retScore[j][k], &retScore[j + 1][k]);
                }
            }
        }
    }
}
int SearchID(int stuID[], int num)
{
    static int orderID[N], pos[N], isorder = 0;
    if(!isorder)
    {
        for(int i = 0; i < num; i++)
        {
            orderID[i] = stuID[i];
            pos[i] = i;
        }
        for(int i = 0; i < num - 1; i++)
        {
            for(int j = 0; j < num - 1; j++)
            {
                if(orderID[j] > orderID[j + 1])
                {
                    swapNum(&orderID[j], &orderID[j + 1]);
                    swapNum(&pos[j], &pos[j + 1]);
                }
            }
        }
        isorder = 1;
    }

    int ret = -1, ID = 0;
    printf("Please input student number:\n");
    scanf("%d", &ID);
    int l = 0, r = num - 1;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(orderID[mid] < ID)
        {
            l = mid + 1;
        }
        else if(orderID[mid] == ID)
        {
            ret = pos[mid];
            break;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ret;
}
int SearchName(char stuName[][20], int num)
{
    int ret = -1; char Name[20];
    printf("Please input student name:\n");
    scanf("%s", Name);
    for(int i = 0; i < num; i++)
    {
        if(strcmp(stuName[i], Name) == 0)
        {
            ret = i;
            break;
        }
    }
    return ret;
}
void OutputStu(int stuID[], char stuName[][20], int stuScore[][6], int Subject_num, int pos)
{
    if(pos == -1)
    {
        printf("Can't find this student!\n");
    }
    else
    {
        printf("The student's number is %d, name is %s\n", stuID[pos], stuName[pos]);
        printf("The student's score is:");
        for(int i = 0; i < Subject_num; i++)
        {
            printf("%-3d", stuScore[pos][i]);
        }
        printf("\n");
    }
}
void AnalysisStu(int stuScore[][6], int num, int Subject_num)
{
    int result[6][5];
    memset(result, 0, sizeof(result));
    char level[5][100] = {"Excellent", "Good", "Average", "Pass", "Fail"};
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < Subject_num; j++)
        {
            if(stuScore[i][j] >= 90)
            {
                result[j][0]++;
            }
            else if(stuScore[i][j] >= 80)
            {
                result[j][1]++;
            }
            else if(stuScore[i][j] >= 70)
            {
                result[j][2]++;
            }
            else if(stuScore[i][j] >= 60)
            {
                result[j][3]++;
            }
            else
            {
                result[j][4]++;
            }
        }
    }
    for(int i = 0; i < Subject_num; i++)
    {
        printf("Subject %d:\n", i + 1);
        for(int j = 0; j < 5; j++)
        {
            double percent = (double)result[i][j] / num;
            printf("%s: %d students, percentage: %3.1lf%%\n", level[j], result[i][j], percent * 100);
        }
    }
}
void swapNum(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void swapStr(char a[], char b[])
{
    char tmp[20];
    strcpy(tmp, a);
    strcpy(a, b);
    strcpy(b, tmp);
}
int Ascending(int a, int b)
{
    if(a <= b) return 1;
    return 0;
}
int Descending(int a, int b)
{
    if(a >= b) return 1;
    return 0;
}
