#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_ID_LEN 10
#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

typedef struct
{
    char *name;
    char *id;
    double gpa;
    int creditHours;
} Student;

typedef struct StudentNode
{
    Student *pStudent;
    struct StudentNode *pNext;
} StudentNode;

typedef struct
{
    StudentNode *pIDList;
    StudentNode *pHonorRollList;
    StudentNode *pAcademicProbationList;
    StudentNode *pFreshmanList;
    StudentNode *pSophomoreList;
    StudentNode *pJuniorList;
    StudentNode *pSeniorList;
} Database;

// Function prototypes
Database *createDatabase();
Student *createStudent(char *name, char *id, double gpa, int creditHours);
void addStudent(Database *db, Student *student);
// void deleteStudent(Database *db, char *id);
// void printStudent(Student *student);
// void printDatabase(Database *db);
// void printHonorRoll(Database *db);
// void printAcademicProbation(Database *db);
// void printClassStanding(Database *db, int classStanding);

int main()
{
    char choice;
    char filename[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char id[MAX_ID_LEN];
    double gpa;
    int creditHours;
    Database *db = createDatabase();
    Student *student;
    int looper = 1;

    printf("CS 211, Spring 2023\nProgram 4: Database of Students\n\nEnter E to start with an empty database,\nor F to start with a database that has information on students from a file.\nYour choice --> ");
    scanf("%c", &choice);
    while (choice != 'E' && choice != 'F')
    {
        printf("Invalid input. Please enter E or F: ");
        scanf(" %c", &choice);
    }

    if (choice == 'F')
    {
        printf("Enter the name of the file you would like to use: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Failed to open file\n");
            return 1;
        }

        // Skip the first line containing the column headers
        char line[MAX_LINE_LENGTH];
        fgets(line, MAX_LINE_LENGTH, file);

        // Loop through the remaining lines and extract the data
        while (fgets(line, MAX_LINE_LENGTH, file))
        {
            char *name = strtok(line, ",");
            char *id = strtok(NULL, ",");
            char *gpa_str = strtok(NULL, ",");
            char *credit_hours_str = strtok(NULL, ",");

            if (name == NULL || id == NULL || gpa_str == NULL || credit_hours_str == NULL)
            {
                printf("Invalid data format\n");
                continue;
            }

            // Convert GPA and credit hours strings to numbers
            double gpa = atof(gpa_str);
            int credit_hours = atoi(credit_hours_str);

            // Remove leading and trailing spaces from name and ID
            char *name_start = name;
            while (*name_start == ' ')
            {
                name_start++;
            }
            char *name_end = name + strlen(name) - 1;
            while (*name_end == ' ' || *name_end == '\n')
            {
                *name_end = '\0';
                name_end--;
            }

            char *id_start = id;
            while (*id_start == ' ')
            {
                id_start++;
            }
            char *id_end = id + strlen(id) - 1;
            while (*id_end == ' ' || *id_end == '\n')
            {
                *id_end = '\0';
                id_end--;
            }

            // Do something with the extracted data
            student = createStudent(name_start, id_start, gpa, credit_hours);
            addStudent(db, student);
        }

        fclose(file);
    }

    do
    {
        printf("Enter:\tC to create a new student and add them to the database,\n\tR to read from the database,\n\tD to delete a student from the database, or\n\tX to exit the program.\nYour choice --> ");
        scanf(" %c", &choice);
        getchar();

        switch (choice)
        {
        case 'C':
            printf("Enter the name of the new student: ");
            scanf("%[^\n]", name);
            printf("Enter the ID of the new student: ");
            scanf("%s", id);
            printf("Enter the GPA of the new student: ");
            scanf("%lf", &gpa);
            printf("Enter the credit hours of the new student: ");
            scanf("%d", &creditHours);

            student = createStudent(name, id, gpa, creditHours);
            addStudent(db, student);

            printf("Successfully added the following student to the database!\n%s:\n\tID - %s\n\tGPA - %.2lf\n\tCredit Hours - %d\n\n", name, id, gpa, creditHours);
            break;

        case 'R':
        {
            printf("Select one of the following:\n");
            printf("\t1) Display the head (first 10 rows) of the database\n");
            printf("\t2) Display students on the honor roll, in order of their GPA\n");
            printf("\t3) Display students on academic probation, in order of their GPA\n");
            printf("\t4) Display freshmen students, in order of their name\n");
            printf("\t5) Display sophomore students, in order of their name\n");
            printf("\t6) Display junior students, in order of their name\n");
            printf("\t7) Display senior students, in order of their name\n");
            printf("\t8) Display the information of a particular student\nYour choice --> ");

            char readChoice;
            scanf(" %c", &readChoice);

            while (readChoice < '1' || readChoice > '8')
            {
                printf("Sorry, that input was invalid. Please try again.\nYour choice -->  ");
                scanf(" %c", &readChoice);
            }

            switch (readChoice)
            {
            case '1':
            {
                printf("\nInformation of first 10 students:\n");
                int count = 0;
                StudentNode *p = db->pIDList;
                while (count < 10 && p != NULL)
                {
                    printf("\nName: %s %s\n", p->pStudent->name, p->pStudent->id);
                    printf("GPA: %.2lf\n", p->pStudent->gpa);
                    printf("Credit hours: %d\n", p->pStudent->creditHours);
                    p = p->pNext;
                    count++;
                }
                break;
            }
            case '2':
            {
                printf("\nStudents on honor roll:\n");
                StudentNode *p = db->pHonorRollList;
                while (p != NULL)
                {
                    printf("\nName: %s %s\n", p->pStudent->name, p->pStudent->id);
                    printf("GPA: %.2lf\n", p->pStudent->gpa);
                    printf("Credit hours: %d\n", p->pStudent->creditHours);
                    p = p->pNext;
                }
                break;
            }
            case '3':
            {
                printf("\nStudents on probation:\n");
                StudentNode *p = db->pAcademicProbationList;
                while (p != NULL)
                {
                    printf("\nName: %s %s\n", p->pStudent->name, p->pStudent->id);
                    printf("GPA: %.2lf\n", p->pStudent->gpa);
                    printf("Credit hours: %d\n", p->pStudent->creditHours);
                    p = p->pNext;
                }
                break;
            }
            }
        }
        break;

        case 'X':
        {
            printf("\nThanks for playing!\nExiting...");
            looper = 0;
            break;
        }
        }
    } while (looper);
}

Database *createDatabase()
{
    Database *db = malloc(sizeof(Database));
    db->pIDList = NULL;
    db->pHonorRollList = NULL;
    db->pAcademicProbationList = NULL;
    db->pFreshmanList = NULL;
    db->pSophomoreList = NULL;
    db->pJuniorList = NULL;
    db->pSeniorList = NULL;
    return db;
}

void addStudent(Database *db, Student *student)
{
    // Create new student node
    StudentNode *newNode = malloc(sizeof(StudentNode));
    newNode->pStudent = student;
    newNode->pNext = NULL;

    // Traverse the list to find the correct position to insert the new node
    StudentNode *prev = NULL;
    StudentNode *curr = db->pIDList;
    while (curr != NULL && strcmp(curr->pStudent->name, student->name) < 0)
    {
        prev = curr;
        curr = curr->pNext;
    }

    // Insert the new node
    if (prev == NULL)
    {
        // Insert at the beginning of the list
        newNode->pNext = db->pIDList;
        db->pIDList = newNode;
    }
    else
    {
        // Insert in the middle or at the end of the list
        prev->pNext = newNode;
        newNode->pNext = curr;
    }

    // Insert student into class standing lists
    if (student->creditHours < 30)
    {
        StudentNode *newFreshmanNode = malloc(sizeof(StudentNode));
        newFreshmanNode->pStudent = student;
        newFreshmanNode->pNext = db->pFreshmanList;
        db->pFreshmanList = newFreshmanNode;
    }
    else if (student->creditHours < 60)
    {
        StudentNode *newSophomoreNode = malloc(sizeof(StudentNode));
        newSophomoreNode->pStudent = student;
        newSophomoreNode->pNext = db->pSophomoreList;
        db->pSophomoreList = newSophomoreNode;
    }
    else if (student->creditHours < 90)
    {
        StudentNode *newJuniorNode = malloc(sizeof(StudentNode));
        newJuniorNode->pStudent = student;
        newJuniorNode->pNext = db->pJuniorList;
        db->pJuniorList = newJuniorNode;
    }
    else
    {
        StudentNode *newSeniorNode = malloc(sizeof(StudentNode));
        newSeniorNode->pStudent = student;
        newSeniorNode->pNext = db->pSeniorList;
        db->pSeniorList = newSeniorNode;
    }

    // Insert student into honor roll or academic probation list
    if (student->gpa >= 3.5)
    {
        StudentNode *newHonorRollNode = malloc(sizeof(StudentNode));
        newHonorRollNode->pStudent = student;
        newHonorRollNode->pNext = db->pHonorRollList;
        db->pHonorRollList = newHonorRollNode;
    }
    else if (student->gpa < 2.0)
    {
        StudentNode *newAcademicProbationNode = malloc(sizeof(StudentNode));
        newAcademicProbationNode->pStudent = student;
        newAcademicProbationNode->pNext = db->pAcademicProbationList;
        db->pAcademicProbationList = newAcademicProbationNode;
    }
}

Student *createStudent(char *name, char *id, double gpa, int creditHours)
{
    // Allocate memory for a new Student
    Student *student = (Student *)malloc(sizeof(Student));

    // Allocate memory for the name and id strings
    student->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    student->id = (char *)malloc((strlen(id) + 1) * sizeof(char));

    // Copy the name and id strings into the new memory locations
    strcpy(student->name, name);
    strcpy(student->id, id);

    // Set the gpa and creditHours fields
    student->gpa = gpa;
    student->creditHours = creditHours;

    // Return a pointer to the new Student
    return student;
}