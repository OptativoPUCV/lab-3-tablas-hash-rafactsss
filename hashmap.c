#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long index = hash(key, map->capacity);
    long original = index;

    while (map->buckets[index] != NULL && map->buckets[index]->key != NULL) {
        if (is_equal(map->buckets[index]->key, key)) return;
        index = (index + 1) % map->capacity;
        if (index == original) return;
    }
    map->buckets[index] = createPair(key, value);
    map->size++;
    map->current = index;
}
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    long cap_antigua  = map->capacity;
    Pair ** old_buckets = map->buckets;

    long nueva_cap  = cap_antigua * 2;

    map->buckets = (Pair **) malloc(sizeof(Pair *) * nueva_cap);
    map->capacity = nueva_cap;
    map->size = 0;
    map->current = -1;
    for (long i = 0; i < nueva_cap; i++) {
        map->buckets[i] = NULL;
    }
    for (long i = 0; i < cap_antigua; i++) {
        if (old_buckets[i] != NULL && old_buckets[i]->key != NULL) {
            insertMap(map, old_buckets[i]->key, old_buckets[i]->value);
        }
    }

    free(old_buckets);
}


HashMap * createMap(long capacity) {
    HashMap * mapa = (HashMap *) malloc(sizeof(HashMap));
    mapa->buckets = (Pair **) malloc(sizeof(Pair *) * capacity);

    for (long i = 0; i < capacity; i++) {
        mapa->buckets[i] = NULL;
    }
    mapa->capacity = capacity;
    mapa->size = 0;
    mapa->current = -1;

    return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
    long index = hash(key, map->capacity);
    long originalIndex = index;

    while (map->buckets[index] != NULL) {    
        if (map->buckets[index]->key != NULL && strcmp(map->buckets[index]->key, key) == 0) {
            map->buckets[index]->key = NULL;
            map->size--;
            return;
        }
        index = (index + 1) % map->capacity;

        if (index == originalIndex) break;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
