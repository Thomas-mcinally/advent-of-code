#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

#define HASHMAP_SIZE 256

typedef struct LinkedListNode {
    char *key;
    int value;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct{
    LinkedListNode *buckets[HASHMAP_SIZE];
} HashMap;

HashMap *create_empty_hashmap()
{
    HashMap *result = malloc(sizeof(HashMap));
    for (size_t i=0; i < HASHMAP_SIZE; i++)
    {
        result->buckets[i] = malloc(sizeof(LinkedListNode));
        result->buckets[i]->key = NULL;
        result->buckets[i]->value = 0;
        result->buckets[i]->next = NULL;
        result->buckets[i]->prev = NULL;
    }
    return result;
}

void free_hashmap(HashMap *map)
{
    for (size_t i=0; i < HASHMAP_SIZE; i++)
    {
        LinkedListNode *head = map->buckets[i];
        while (head->next != NULL){
            LinkedListNode *temp = head->next;
            free(head);
            head = temp;
        }
        free(head);
    }
    free(map);
}

int generate_hash(char *label)
{
    int hash = 0;
    while (*label != '\0')
    {
        hash += *label;
        hash *= 17;
        hash %= HASHMAP_SIZE;
        label++;
    }
    return hash;
}

void hashmap_set(HashMap *map, char *label, int val)
{
    int hash = generate_hash(label);
    LinkedListNode *head = map->buckets[hash];
    while (head->next != NULL){
        head = head->next;
        if (strcmp(head->key, label) == 0)
        {
            head->value = val;
            return;
        }
    }

    // this key isnt in map yet
    LinkedListNode *new_node = malloc(sizeof(LinkedListNode));
    new_node->key = label;
    new_node->value = val;
    new_node->next = NULL;
    new_node->prev = head;

    head->next = new_node;
}

int hashmap_get(HashMap *map, char *label)
{
    int hash = generate_hash(label);
    LinkedListNode *head = map->buckets[hash];
    while (head->next != NULL){
        head = head->next;
        if (strcmp(head->key, label) == 0)
        {
            return head->value;
        }
    }

    fprintf(stderr, "KeyError, the provided key doesn't exist in the hashmap\n");
    exit(1);
}

void hashmap_del(HashMap *map, char *label)
{
    int hash = generate_hash(label);
    LinkedListNode *head = map->buckets[hash];
    while (head->next != NULL){
        head = head->next;
        if (strcmp(head->key, label) == 0)
        {
            head->prev->next = head->next;
            if (head->next != NULL) head->next->prev = head->prev;
            return;
        }
    }

    // Key doesnt exist in hashmap, so do nothing
}

size_t part1(char *filepath){
    char *file_contents = read_entire_file(filepath);


    size_t content_i = 0;
    size_t total_value = 0;
    char *label_start = file_contents; 
    while (file_contents[content_i] != '\0')
    {
        if (file_contents[content_i] == ',') {
            file_contents[content_i] = '\0';
            total_value += generate_hash(label_start);
            label_start = file_contents + content_i + 1;
        }

        content_i++;
    }
    total_value += generate_hash(label_start);

    return total_value;
}

size_t part2(char *filepath){
    char *file_contents = read_entire_file(filepath);

    size_t content_i = 0;
    char *label_start = file_contents;
    HashMap *map = create_empty_hashmap(); 
    while (file_contents[content_i] != '\0')
    {
        if (file_contents[content_i] == '=') {
            file_contents[content_i] = '\0';
            int focal_length = file_contents[content_i + 1] - '0';

            hashmap_set(map, label_start, focal_length);

            label_start = file_contents + content_i + 3;
            content_i++;
        }
        else if (file_contents[content_i] == '-') {
            file_contents[content_i] = '\0';

            hashmap_del(map, label_start);
            label_start = file_contents + content_i + 2;
        }
        content_i++;
    }


    size_t total_2 = 0;
    for (size_t box_i=0; box_i < HASHMAP_SIZE; box_i++)
    {
        LinkedListNode *head = map->buckets[box_i];
        int list_i = 0;
        while (head->next != NULL){
            head = head->next;
            list_i++;

            total_2 += (box_i+1) * list_i * (head->value);
        }
    }
    free_hashmap(map);
    return total_2;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    

    printf("part1 sol: %zu\n", part1(file_path));

    printf("part2 sol: %zu\n", part2(file_path));
}
