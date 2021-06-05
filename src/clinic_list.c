#include <stdio.h>
#include <stdlib.h>
#include "../include/clinic_list.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node {
    int student_id;
    int grade;
    struct node *next;
};

struct list {
    int clinic_id;
    int vacancies;
    int passing_score;
    Node_clinic *head; 
};

Node_clinic *create_college_node(int student_id, int grade){
    Node_clinic *newNode = malloc(sizeof(Node_clinic));
    if (!newNode) {
        return NULL;
    }
    newNode->student_id = student_id;
    newNode->grade = grade;
    newNode->next = NULL;

    return newNode;
}

List_clinic *make_college_list(int number_of_clinics) {
    int i = 0;
    List_clinic *list = malloc(sizeof(List_clinic) * number_of_clinics);

    if (!list) {
        return NULL;
    }

    for(i = 0; i < number_of_clinics; i++) {
        list[i].head = NULL;
    }

    return list;
}

void display_college_list(List_clinic *list, int clinic_id) {
    Node_clinic *current = list[clinic_id].head;

    if(list[clinic_id].head == NULL) 
        return;
  
    for(; current != NULL; current = current->next) {
        printf("%d\n", current->student_id);
    }
}

void add_student_to_college(List_clinic *list, int college_id, int student_id, int grade) {
    Node_clinic *current = NULL;

    if(grade < list[college_id].passing_score) {
        return;
    }

    if(list[college_id].head == NULL){
        list[college_id].head = create_college_node(student_id, grade);
    }
    else {
        current = list[college_id].head; 
        while (current->next!=NULL){
            current = current->next;
        }
        current->next = create_college_node(student_id, grade);
    }
}

int college_has_student(List_clinic *list, int clinic_id, int student_id) {
    Node_clinic *current = list[clinic_id].head;            
    Node_clinic *previous = current;           
    
    while(current != NULL){           
        if(current->student_id == student_id){      
            return 1;
        }                               
        previous = current;             
        current = current->next;        
    }  

    return 0;
}

void delete_student_from_college(List_clinic *list, int clinic_id, int student_id) {
    Node_clinic *current = list[clinic_id].head;            
    Node_clinic *previous = current;           
    while(current != NULL){           
        if(current->student_id == student_id){      
            previous->next = current->next;
            if(current == list[clinic_id].head)
                list->head = current->next;
            free(current);
            return;
        }                               
        previous = current;             
        current = current->next;        
    }                                 
}                                   

void destroy_college_list(List_clinic *list, int number_of_clinics) {
    int i = 0;
    Node_clinic *current = NULL;
    Node_clinic *next = current;

    for(; i < number_of_clinics; i++) {
        current = list[i].head;
        next = current;

        while(current != NULL){
            next = current->next;
            free(current);
            current = next;
        }
    }

    free(list);
}
