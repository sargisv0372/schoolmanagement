#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentInfo {
    char fname[50];
    char lname[50];
    int roll;
    float cgpa;
    int *cid; // Using dynamic allocation for course IDs
};

int num_students = 0;
int max_students = 50;
struct StudentInfo **students;

// Function to add a new student
void add_student() {
    if (num_students < max_students) {
        struct StudentInfo *new_student = (struct StudentInfo *)malloc(sizeof(struct StudentInfo));

        if (new_student == NULL) {
            printf("Memory allocation failed. Exiting.\n");
            exit(EXIT_FAILURE);
        }

        printf("Add the Student Details\n");
        printf("-------------------------\n");
        printf("Enter the first name of student: ");
        scanf("%s", new_student->fname);
        printf("Enter the last name of student: ");
        scanf("%s", new_student->lname);
        printf("Enter the Roll Number: ");
        scanf("%d", &(new_student->roll));
        printf("Enter the CGPA you obtained: ");
        scanf("%f", &(new_student->cgpa));

        // Dynamic allocation for course IDs
        new_student->cid = (int *)malloc(5 * sizeof(int));

        if (new_student->cid == NULL) {
            printf("Memory allocation failed. Exiting.\n");
            free(new_student);
            exit(EXIT_FAILURE);
        }

        printf("Enter the course ID of each course\n");
        for (int j = 0; j < 5; j++) {
            printf("Enter course ID %d: ", j + 1);
            scanf("%d", &(new_student->cid[j]));
        }

        // Add the new student to the array
        students[num_students] = new_student;
        num_students++;
    } else {
        printf("Maximum number of students reached. Cannot add more.\n");
    }
}

// Function to find a student by the first name
void find_fn() {
    char target_fname[50];
    printf("Enter the First Name of the student: ");
    scanf("%s", target_fname);

    int found = 0;

    for (int j = 0; j < num_students; j++) {
        if (strcmp(students[j]->fname, target_fname) == 0) {
            printf("The Students Details are\n");
            printf("First name: %s\n", students[j]->fname);
            printf("Last name: %s\n", students[j]->lname);
            printf("Roll Number: %d\n", students[j]->roll);
            printf("CGPA: %f\n", students[j]->cgpa);
            printf("Course IDs:\n");

            for (int k = 0; k < 5; k++) {
                printf("%d\n", students[j]->cid[k]);
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with the specified First Name.\n");
    }
}

// Function to find students enrolled in a particular course
void find_c() {
    int target_cid;
    printf("Enter the course ID: ");
    scanf("%d", &target_cid);

    int found = 0;

    for (int j = 0; j < num_students; j++) {
        for (int d = 0; d < 5; d++) {
            if (target_cid == students[j]->cid[d]) {
                printf("The Students Details are\n");
                printf("First name: %s\n", students[j]->fname);
                printf("Last name: %s\n", students[j]->lname);
                printf("Roll Number: %d\n", students[j]->roll);
                printf("CGPA: %f\n", students[j]->cgpa);

                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("No Students Found for the given Course ID\n");
    }
}

// Function to print the total number of students
void tot_s() {
    printf("The total number of Students is %d\n", num_students);
    printf("Maximum number of students allowed: %d\n", max_students);
    printf("Remaining slots for students: %d\n", max_students - num_students);
}

// Function to delete a student by the roll number
void del_s() {
    int target_roll;
    printf("Enter the Roll Number to delete: ");
    scanf("%d", &target_roll);

    int found = 0;

    for (int j = 0; j < num_students; j++) {
        if (target_roll == students[j]->roll) {
            free(students[j]->cid); // Free memory allocated for course IDs
            free(students[j]);      // Free memory allocated for the student

            // Shift the remaining students
            for (int k = j; k < num_students - 1; k++) {
                students[k] = students[k + 1];
            }

            num_students--;
            found = 1;
            printf("The Roll Number is removed Successfully\n");
            break;
        }
    }

    if (!found) {
        printf("No student found with the specified Roll Number\n");
    }
}

// Function to update a student's data
void up_s() {
    int target_roll;
    printf("Enter the roll number to update the entry: ");
    scanf("%d", &target_roll);

    int found = 0;

    for (int j = 0; j < num_students; j++) {
        if (students[j]->roll == target_roll) {
            printf("1. First name\n2. Last name\n3. Roll Number\n4. CGPA\n5. Courses\n");
            int choice;
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter the new First name: ");
                    scanf("%s", students[j]->fname);
                    break;
                case 2:
                    printf("Enter the new Last name: ");
                    scanf("%s", students[j]->lname);
                    break;
                case 3:
                    printf("Enter the new Roll Number: ");
                    scanf("%d", &(students[j]->roll));
                    break;
                case 4:
                    printf("Enter the new CGPA: ");
                    scanf("%f", &(students[j]->cgpa));
                    break;
                case 5:
                    printf("Enter the new courses\n");
                    for (int k = 0; k < 5; k++) {
                        printf("Enter course ID %d: ", k + 1);
                        scanf("%d", &(students[j]->cid[k]));
                    }
                    break;
                default:
                    printf("Invalid choice. No update performed.\n");
                    break;
            }

            printf("UPDATED SUCCESSFULLY.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No data available for the specified roll number.\n");
    }
}

// Function to save data to file before exiting
void save_to_file() {
    FILE *file = fopen("C:\\Users\\User\\Desktop\\StudentData.txt", "w");

    if (file == NULL) {
        printf("Error opening file. Data not saved.\n");
        return;
    }

    for (int i = 0; i < num_students; i++) {
        fprintf(file, "First name: %s\n", students[i]->fname);
        fprintf(file, "Last name: %s\n", students[i]->lname);
        fprintf(file, "Roll Number: %d\n", students[i]->roll);
        fprintf(file, "CGPA: %f\n", students[i]->cgpa);
        fprintf(file, "Course IDs: ");
        for (int k = 0; k < 5; k++) {
            fprintf(file, "%d ", students[i]->cid[k]);
        }
        fprintf(file, "\n\n");
    }

    fclose(file);
}

int main() {
    students = (struct StudentInfo **)malloc(max_students * sizeof(struct StudentInfo *));

    if (students == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    int choice;
    while (1) {
        printf("The Task that you want to perform\n");
        printf("1. Add the Student Details\n");
        printf("2. Find the Student Details by First Name\n");
        printf("3. Find the Student Details by Course ID\n");
        printf("4. Find the Total number of Students\n");
        printf("5. Delete the Students Details by Roll Number\n");
        printf("6. Update the Students Details by Roll Number\n");
        printf("7. Save and Exit\n");
        printf("Enter your choice to find the task: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                find_fn();
                break;
            case 3:
                find_c();
                break;
            case 4:
                tot_s();
                break;
            case 5:
                del_s();
                break;
            case 6:
                up_s();
                break;
            case 7:
                save_to_file();
                // Free memory allocated for the array of students
                for (int i = 0; i < num_students; i++) {
                    free(students[i]->cid);
                    free(students[i]);
                }
                free(students);
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}












