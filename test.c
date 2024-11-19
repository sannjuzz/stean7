#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// Define the structure for storing student information
struct Student {
    int roll_no;
    char name[MAX_NAME_LENGTH];
    float marks;
};

// Function prototypes
void add_student();
void display_students();
void search_student(int roll_no);
void write_to_file(struct Student students[], int student_count);
int read_from_file(struct Student students[]);

int main() {
    struct Student students[MAX_STUDENTS];
    int choice, student_count = read_from_file(students);

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student(students, &student_count);
                break;
            case 2:
                display_students(students, student_count);
                break;
            case 3: {
                int roll_no;
                printf("Enter Roll Number to Search: ");
                scanf("%d", &roll_no);
                search_student(roll_no, students, student_count);
                break;
            }
            case 4:
                write_to_file(students, student_count);
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a new student
void add_student(struct Student students[], int *student_count) {
    if (*student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    struct Student new_student;
    printf("Enter Roll Number: ");
    scanf("%d", &new_student.roll_no);
    printf("Enter Student Name: ");
    getchar();  // to clear the newline character from buffer
    fgets(new_student.name, MAX_NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;  // Remove newline character
    printf("Enter Marks: ");
    scanf("%f", &new_student.marks);

    students[*student_count] = new_student;
    (*student_count)++;
    printf("Student added successfully!\n");
}

// Function to display all students
void display_students(struct Student students[], int student_count) {
    if (student_count == 0) {
        printf("No students available.\n");
        return;
    }

    printf("\nList of Students:\n");
    for (int i = 0; i < student_count; i++) {
        printf("Roll No: %d, Name: %s, Marks: %.2f\n", students[i].roll_no, students[i].name, students[i].marks);
    }
}

// Function to search for a student by roll number
void search_student(int roll_no, struct Student students[], int student_count) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_no == roll_no) {
            printf("Student Found: Roll No: %d, Name: %s, Marks: %.2f\n", students[i].roll_no, students[i].name, students[i].marks);
            return;
        }
    }
    printf("Student with Roll Number %d not found.\n", roll_no);
}

// Function to write student records to a file
void write_to_file(struct Student students[], int student_count) {
    FILE *file = fopen("student_records.txt", "w");
    if (file == NULL) {
        printf("Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d,%s,%.2f\n", students[i].roll_no, students[i].name, students[i].marks);
    }

    fclose(file);
    printf("Student records saved to file.\n");
}

// Function to read student records from a file
int read_from_file(struct Student students[]) {
    FILE *file = fopen("student_records.txt", "r");
    int count = 0;

    if (file == NULL) {
        printf("No previous records found.\n");
        return 0;
    }

    while (fscanf(file, "%d,%49[^,],%f\n", &students[count].roll_no, students[count].name, &students[count].marks) == 3) {
        count++;
        if (count >= MAX_STUDENTS) break;
    }

    fclose(file);
    return count;
}
