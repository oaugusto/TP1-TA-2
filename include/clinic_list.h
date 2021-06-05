#ifndef CLINIC_LIST
#define CLINIC_LIST

typedef struct node Node_clinic;

typedef struct list List_clinic;

Node_clinic *create_clinic_node(int student_id, int grade);
List_clinic * make_clinic_list(int number_of_clinics);
void display_clinic_list(List_clinic *list, int clinic_id);
void add_student_to_clinic(List_clinic *list, int clinic_id, int student_id, int grade);
int clinic_has_student(List_clinic *list, int clinic_id, int student_id);
void delete_student_from_clinic(List_clinic *list, int clinic_id, int student_id);
void destroy_clinic_list(List_clinic *list, int number_of_clinics);

#endif
