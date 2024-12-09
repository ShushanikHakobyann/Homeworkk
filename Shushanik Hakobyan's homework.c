/*
Write a C program to sort an array of integers entered by the user.
Ask the user for the number of elements they want to sort, then read
array elements into the dynamically created array. The sorting should
be done in a separate function.
– Write a Makefile for the program.
– Compile using optimized and debug modes.
– Set breakpoint in the sorting function, and run the program step by
step using GDB.
– Intentionally make a memory leak and detect it using Valgrind.
– Document code using Doxygen format and generate
documentation for it.*/
#include <stdio.h>
#include <stdlib.h>

void sortArray(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int size;
    printf("Enter the number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int *array = malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%d", &array[i]) != 1) {
            printf("Invalid input detected.\n");
            free(array);
            return 1;
        }
    }

    sortArray(array, size);

    printf("Sorted array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}

/*
Write a C program to store and manage student details (name,
surname, ID, and grade). Include the following operations in the menu
driven user interface:
– Add a new student to the list.
– Remove a student by ID.
– Search a student by ID.
– Display all student details.
– Display average grade of all students.
– Save student details into “group_details.csv” file – every student
detail in a new line and the details separated by commas.
– Read student details from a file.
Ensure that memory is dynamically allocated and properly freed when
students are removed or the program ends.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    char surname[50];
    int id;
    float grade;
    struct Student *next;
} Student;

Student *addStudent(Student *head) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    printf("Enter name: ");
    scanf("%s", newStudent->name);
    printf("Enter surname: ");
    scanf("%s", newStudent->surname);
    printf("Enter ID: ");
    scanf("%d", &newStudent->id);
    printf("Enter grade: ");
    scanf("%f", &newStudent->grade);
    newStudent->next = head;
    return newStudent;
}

Student *removeStudent(Student *head, int id) {
    Student *current = head, *prev = NULL;
    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            free(current);
            printf("Student removed.\n");
            return head;
        }
        prev = current;
        current = current->next;
    }
    printf("Student not found.\n");
    return head;
}

void searchStudent(Student *head, int id) {
    while (head) {
        if (head->id == id) {
            printf("Name: %s, Surname: %s, ID: %d, Grade: %.2f\n", head->name, head->surname, head->id, head->grade);
            return;
        }
        head = head->next;
    }
    printf("Student not found.\n");
}

void displayStudents(Student *head) {
    while (head) {
        printf("Name: %s, Surname: %s, ID: %d, Grade: %.2f\n", head->name, head->surname, head->id, head->grade);
        head = head->next;
    }
}

void displayAverageGrade(Student *head) {
    int count = 0;
    float total = 0.0;
    while (head) {
        total += head->grade;
        count++;
        head = head->next;
    }
    if (count > 0) {
        printf("Average Grade: %.2f\n", total / count);
    } else {
        printf("No students in the list.\n");
    }
}

void saveToFile(Student *head) {
    FILE *file = fopen("group_details.csv", "w");
    while (head) {
        fprintf(file, "%s,%s,%d,%.2f\n", head->name, head->surname, head->id, head->grade);
        head = head->next;
    }
    fclose(file);
    printf("Data saved to group_details.csv\n");
}

Student *readFromFile() {
    FILE *file = fopen("group_details.csv", "r");
    if (!file) {
        printf("File not found.\n");
        return NULL;
    }
    Student *head = NULL, *tail = NULL;
    while (!feof(file)) {
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if (fscanf(file, "%[^,],%[^,],%d,%f\n", newStudent->name, newStudent->surname, &newStudent->id, &newStudent->grade) == 4) {
            newStudent->next = NULL;
            if (!head) {
                head = tail = newStudent;
            } else {
                tail->next = newStudent;
                tail = newStudent;
            }
        } else {
            free(newStudent);
        }
    }
    fclose(file);
    printf("Data loaded from group_details.csv\n");
    return head;
}

int main() {
    Student *head = NULL;
    int choice, id;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Search Student\n");
        printf("4. Display All Students\n");
        printf("5. Display Average Grade\n");
        printf("6. Save to File\n");
        printf("7. Read from File\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                head = addStudent(head);
                break;
            case 2:
                printf("Enter ID to remove: ");
                scanf("%d", &id);
                head = removeStudent(head, id);
                break;
            case 3:
                printf("Enter ID to search: ");
                scanf("%d", &id);
                searchStudent(head, i


/*Write a C program to compare two files, printing
the first line where they differ.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char file1[100], file2[100];
    char line1[1024], line2[1024];
    FILE *fp1, *fp2;

    printf("Enter the first file name: ");
    scanf("%s", file1);
    printf("Enter the second file name: ");
    scanf("%s", file2);

    fp1 = fopen(file1, "r");
    fp2 = fopen(file2, "r");

    if (!fp1 || !fp2) {
        printf("Error opening files.\n");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        return 1;
    }

    int lineNum = 1;
    while (fgets(line1, sizeof(line1), fp1) && fgets(line2, sizeof(line2), fp2)) {
        if (strcmp(line1, line2) != 0) {
            printf("Files differ at line %d:\n", lineNum);
            printf("File 1: %s", line1);
            printf("File 2: %s", line2);
            fclose(fp1);
            fclose(fp2);
            return 0;
        }
        lineNum++;
    }

    if (feof(fp1) && feof(fp2)) {
        printf("Files are identical.\n");
    } else {
        printf("Files differ at line %d:\n", lineNum);
        if (!feof(fp1)) {
            printf("File 1: %s", fgets(line1, sizeof(line1), fp1));
        }
        if (!feof(fp2)) {
            printf("File 2: %s", fgets(line2, sizeof(line2), fp2));
        }
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}


/*Write a program similiar to Unix “grep” utility*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <search_term> <filename>\n", argv[0]);
        return 1;
    }

    char *searchTerm = argv[1];
    char *fileName = argv[2];
    FILE *file = fopen(fileName, "r");

    if (!file) {
        printf("Error: Could not open file %s\n", fileName);
        return 1;
    }

    char line[1024];
    int lineNum = 1;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, searchTerm)) {
            printf("Line %d: %s", lineNum, line);
        }
        lineNum++;
    }

    fclose(file);
    return 0;
}


/*Write a C program that reads names into the array of strings and
prints duplicate names.*/


#include <stdio.h>
#include <string.h>

int main() {
    int n;
    printf("Enter the number of names: ");
    scanf("%d", &n);

    char names[n][100];
    printf("Enter the names:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    printf("Duplicate names:\n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(names[i], names[j]) == 0) {
                printf("%s\n", names[i]);
                break;
            }
        }
    }

    return 0;
}

/*
Write a C program that reads two dimensional array of integers and
prints the transpose of the matrix.*/


#include <stdio.h>

int main() {
    int rows, cols;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int matrix[rows][cols], transpose[cols][rows];

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }

    printf("Transpose of the matrix:\n");
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%d ", transpose[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/*
Write a C program (tail) that prints the last n lines of its input. By
default n is 10, but it can be changed by an optional argument, so
that "tail -25" prints last 25 lines.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LENGTH 1024

int main(int argc, char *argv[]) {
    int n = 10;
    if (argc == 2 && argv[1][0] == '-') {
        n = atoi(argv[1] + 1);
    }

    char *lines[MAX_LINES];
    int count = 0;

    for (int i = 0; i < MAX_LINES; i++) {
        lines[i] = NULL;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (lines[count % MAX_LINES]) {
            free(lines[count % MAX_LINES]);
        }
        lines[count % MAX_LINES] = strdup(buffer);
        count++;
    }

    int start = count > n ? count - n : 0;
    for (int i = start; i < count; i++) {
        printf("%s", lines[i % MAX_LINES]);
    }

    for (int i = 0; i < MAX_LINES; i++) {
        if (lines[i]) {
            free(lines[i]);
        }
    }

    return 0;
}

/*Write a C program that sorts array of strings based on the provided
callback function.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ascending(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int descending(const void *a, const void *b) {
    return strcmp(*(const char **)b, *(const char **)a);
}

void sortStrings(char *arr[], int n, int (*compare)(const void *, const void *)) {
    qsort(arr, n, sizeof(char *), compare);
}

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);

    char *arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(100);
        printf("Enter string %d: ", i + 1);
        scanf("%s", arr[i]);
    }

    int choice;
    printf("Choose sorting order: 1 for ascending, 2 for descending: ");
    scanf("%d", &choice);

    if (choice == 1) {
        sortStrings(arr, n, ascending);
    } else if (choice == 2) {
        sortStrings(arr, n, descending);
    }

    printf("Sorted strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
        free(arr[i]);
    }

    return 0;
}