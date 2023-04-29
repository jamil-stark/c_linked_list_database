// #include <stdio.h>
// int main(void){
// FILE *fpt; // file pointer
// char c,d;
// char str[50];
// fpt=fopen("small-list.csv","r"); // file already exit for reading
// if(fpt==NULL)
//     printf("Can't open file ");
// else {
// while(fgets(str,50,fpt)){
// puts(str);
// }

// }
// fclose(fpt);
// return 0;
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_NAME_LEN 50
// #define MAX_ID_LEN 10

// int main()
// {
//     char choice;
//     char filename[MAX_NAME_LEN];
//     char name[MAX_NAME_LEN];
//     char id[MAX_ID_LEN];
//     double gpa;
//     int creditHours;

//     FILE *fp = fopen("small-list.csv", "r");
//     if (fp == NULL)
//     {
//         printf("Error: Could not open file\n");
//         exit(EXIT_FAILURE);
//     }

//     while (fscanf(fp, "%[^,],%[^,],%lf,%d\n", name, id, &gpa, &creditHours) == 4)
//     {
//         // printf("");
//         printf("%s %s %lf, %d",name, id, gpa, creditHours);
//         printf("Heu");

//     }

//     fclose(fp);
// }

#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

int main() {
    FILE *file = fopen("small-list.csv", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    // Skip the first line containing the column headers
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);

    // Loop through the remaining lines and extract the data
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *name = strtok(line, ",");
        char *id = strtok(NULL, ",");
        char *gpa_str = strtok(NULL, ",");
        char *credit_hours_str = strtok(NULL, ",");

        if (name == NULL || id == NULL || gpa_str == NULL || credit_hours_str == NULL) {
            printf("Invalid data format\n");
            continue;
        }

        // Convert GPA and credit hours strings to numbers
        double gpa = atof(gpa_str);
        int credit_hours = atoi(credit_hours_str);

        // Remove leading and trailing spaces from name and ID
        char *name_start = name;
        while (*name_start == ' ') {
            name_start++;
        }
        char *name_end = name + strlen(name) - 1;
        while (*name_end == ' ' || *name_end == '\n') {
            *name_end = '\0';
            name_end--;
        }

        char *id_start = id;
        while (*id_start == ' ') {
            id_start++;
        }
        char *id_end = id + strlen(id) - 1;
        while (*id_end == ' ' || *id_end == '\n') {
            *id_end = '\0';
            id_end--;
        }

        // Do something with the extracted data
        printf("Name: %s\n", name_start);
        printf("ID: %s\n", id_start);
        printf("GPA: %f\n", gpa);
        printf("Credit Hours Taken: %d\n", credit_hours);
        printf("\n");
    }

    fclose(file);
    return 0;
}
