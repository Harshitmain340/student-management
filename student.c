#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int rollNo;
    char name[50];
    char course[50];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    printf("Enter Roll No: ");
    scanf("%d", &s.rollNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student record added successfully!\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp))
    {
        printf("Roll No: %d\nName: %s\nCourse: %s\nMarks: %.2f\n\n", s.rollNo, s.name, s.course, s.marks);
    }
    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    int rollNo, found = 0;
    FILE *fp = fopen("students.dat", "rb");

    printf("Enter Roll No to search: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo == rollNo)
        {
            printf("\n Student Found!\nRoll No: %d\nName: %s\nCourse: %s\nMarks: %.2f\n", s.rollNo, s.name, s.course, s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Student not found!\n");
    }
}

void updateStudent()
{
    struct Student s;
    int rollNo, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Roll No to update: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(s), 1, fp))
        {
        if (s.rollNo == rollNo)
        {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Course: ");
            scanf(" %[^\n]", s.course);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student record updated successfully!\n");
    else
        printf("Student not found!\n");
}

void deleteStudent()
{
    struct Student s;
    int rollNo, found = 0;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Roll No to delete: ");
    scanf("%d", &rollNo);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (s.rollNo != rollNo)
        {
            fwrite(&s, sizeof(s), 1, temp);
        } else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student record deleted successfully!\n");
    else
        printf("Student not found!\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
