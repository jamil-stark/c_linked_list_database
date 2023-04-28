#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_ID_LEN 10

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

    printf("Would you like to start with an empty database (E) or a file (F)? ");
    scanf("%c", &choice);
    while (choice != 'E' && choice != 'F')
    {
        printf("Invalid input. Please enter E or F: ");
        scanf(" %c", &choice);
    }

    if (choice == 'F')
    {
        printf("Please enter the filename: ");
        scanf("%s", filename);

        FILE *fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("Error: Could not open file\n");
            exit(EXIT_FAILURE);
        }

        while (fscanf(fp, "%[^,],%[^,],%lf,%d\n", name, id, &gpa, &creditHours) == 4)
        {
            student = createStudent(name, id, gpa, creditHours);
            addStudent(db, student);
        }

        fclose(fp);
    }

    printf("Welcome to the student database system!\n");

    do
    {
        printf("\nMain menu:\n");
        printf("C) Create a new student record\n");
        printf("R) Read from the database\n");
        printf("D) Delete a student record\n");
        printf("X) Exit\n");
        printf("Please enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case 'C':
            printf("\nPlease enter the following information for the new student:\n");
            printf("Name: ");
            scanf("%s", name);
            printf("ID: ");
            scanf("%s", id);
            printf("GPA: ");
            scanf("%lf", &gpa);
            printf("Credit hours: ");
            scanf("%d", &creditHours);

            student = createStudent(name, id, gpa, creditHours);
            addStudent(db, student);

            printf("\nStudent %s (%s) was successfully added to the database.\n", name, id);
            break;

        case 'R':
        {
            printf("\nRead menu:\n");
            printf("1. Print information of first 10 students\n");
            printf("2. Print students on honor roll\n");
            printf("3. Print students on academic probation\n");
            printf("4. Print freshman students\n");
            printf("5. Print sophomore students\n");
            printf("6. Print junior students\n");
            printf("7. Print senior students\n");
            printf("8. Back to main menu\n");

            char readChoice;
            do
            {
                printf("\nEnter your choice (1-8): ");
                scanf(" %c", &readChoice);
            } while (readChoice < '1' || readChoice > '8');

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
            case '2': {
            printf("\nStudents on honor roll:\n");
            StudentNode* p = db->pHonorRollList;
            while (p != NULL) {
                printf("\nName: %s %s\n", p->pStudent->name, p->pStudent->id);
                printf("GPA: %.2lf\n", p->pStudent->gpa);
                printf("Credit hours: %d\n", p->pStudent->creditHours);
                p = p->pNext;
            }
            break;
        }
            }
        }
        }
    } while (choice != 'c');
}


Database* createDatabase() {
    Database* db = malloc(sizeof(Database));
    db->pIDList = NULL;
    db->pHonorRollList = NULL;
    db->pAcademicProbationList = NULL;
    db->pFreshmanList = NULL;
    db->pSophomoreList = NULL;
    db->pJuniorList = NULL;
    db->pSeniorList = NULL;
    return db;
}


void addStudent(Database* db, Student* student) {
    // Create new student node
    StudentNode* newNode = malloc(sizeof(StudentNode));
    newNode->pStudent = student;
    newNode->pNext = NULL;

    // Insert student into ID list
    newNode->pNext = db->pIDList;
    db->pIDList = newNode;

    // Insert student into class standing lists
    if (student->creditHours < 30) {
        StudentNode* newFreshmanNode = malloc(sizeof(StudentNode));
        newFreshmanNode->pStudent = student;
        newFreshmanNode->pNext = db->pFreshmanList;
        db->pFreshmanList = newFreshmanNode;
    } else if (student->creditHours < 60) {
        StudentNode* newSophomoreNode = malloc(sizeof(StudentNode));
        newSophomoreNode->pStudent = student;
        newSophomoreNode->pNext = db->pSophomoreList;
        db->pSophomoreList = newSophomoreNode;
    } else if (student->creditHours < 90) {
        StudentNode* newJuniorNode = malloc(sizeof(StudentNode));
        newJuniorNode->pStudent = student;
        newJuniorNode->pNext = db->pJuniorList;
        db->pJuniorList = newJuniorNode;
    } else {
        StudentNode* newSeniorNode = malloc(sizeof(StudentNode));
        newSeniorNode->pStudent = student;
        newSeniorNode->pNext = db->pSeniorList;
        db->pSeniorList = newSeniorNode;
    }

    // Insert student into honor roll or academic probation list
    if (student->gpa >= 3.5) {
        StudentNode* newHonorRollNode = malloc(sizeof(StudentNode));
        newHonorRollNode->pStudent = student;
        newHonorRollNode->pNext = db->pHonorRollList;
        db->pHonorRollList = newHonorRollNode;
    } else if (student->gpa < 2.0) {
        StudentNode* newAcademicProbationNode = malloc(sizeof(StudentNode));
        newAcademicProbationNode->pStudent = student;
        newAcademicProbationNode->pNext = db->pAcademicProbationList;
        db->pAcademicProbationList = newAcademicProbationNode;
    }
}



Student* createStudent(char* name, char* id, double gpa, int creditHours) {
    // Allocate memory for a new Student
    Student* student = (Student*) malloc(sizeof(Student));

    // Allocate memory for the name and id strings
    student->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    student->id = (char*) malloc((strlen(id) + 1) * sizeof(char));

    // Copy the name and id strings into the new memory locations
    strcpy(student->name, name);
    strcpy(student->id, id);

    // Set the gpa and creditHours fields
    student->gpa = gpa;
    student->creditHours = creditHours;

    // Return a pointer to the new Student
    return student;
}
