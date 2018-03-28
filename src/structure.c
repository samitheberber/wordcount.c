/* structure.c */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#include "structure.h"

struct hashtable *htable[1];

/* Create storage */
StorageP buildStorage(void) {
    StorageP storage;
    if ( (storage = malloc(sizeof(Storage))) == NULL)
        return NULL;
    storage->fc = NULL;
    return storage;
}

/* Free chars like a list */
static void freeChars(CharacterP this, FILE* file) {
    CharacterP p, q;
    p = this;
    while (p != NULL) {
        q = p->next;
        fprintf(file, "'%c': %d\n", p->c, p->count);
        free(p);
        p = q;
    }
}

/* Free storage */
int unbuildStorage(StorageP this, FILE* file) {

    if (this == NULL)
        return 1;

    /* If there are chars setted, free them first */
    if (this->fc != NULL)
        freeChars(this->fc, file);

    free(this);

    return 1;
}

/* Insert a char in list */
static int pushChar(StorageP this, char c) {
    CharacterP current, new;
    current = this->fc;

    if ( (new = malloc(sizeof(Character))) == NULL)
        return 0;

    new->c = c;
    new->count = 1;
    new->next = NULL;

    /* Insert new in current, if current is empty */
    if (current == NULL) {
        this->fc = new;
        return 1;
    }

    /* Loop while there are items */
    while (current->next != NULL) {
        if ( current->c == c ) {
            /* If chars match, increase count and return true */
            current->count++;
            free(new);
            return 1;
        } else
            current = current->next;
    }

    /* Check for first element if there isn't any childs in it */
    if (current->c == c) {
        current->count++;
        free(new);
    } else
        current->next = new;

    return 1;
}

/* Run on every char the pushChar-function */
static void addChars(StorageP storage, char* word) {
    char c;
    int i = 0;
    while ((c =word[i]) != '\0') {
        pushChar(storage, c);
        i++;
    }
}

/* Insert words from file */
void insertWords(StorageP storage, FILE* file) {
    char* word;
    struct hashtable *ctable;
    while ( (fscanf(file, "%s", (word = calloc(1000, sizeof(char))))) != EOF ) {
        if ( strlen(word) >= 2 ) {
            /* When word is atleast two char long recognize it at word */
            if ( (ctable = findhash(word)) == NULL)
                addhash(word);
            else
                ctable->count++;
        }
        addChars(storage, word);
        free(word);
    }
    free(word);
}

/* Insert word in hashtable */
struct hashtable *addhash (char *key) {
    struct hashtable *newhash;
    struct hashtable *curhash;
    unsigned int hashval = 0; /* Our hash code is 0 so create one big list */
    newhash = (struct hashtable *)(malloc(sizeof(struct hashtable)));
    if (newhash == NULL) {
        exit(EXIT_FAILURE);
    }
    newhash->key = malloc(strlen(key));
    strcpy(newhash->key, key);
    newhash->count = 1;
    if (htable[hashval] == NULL) {
        htable[hashval] = newhash;
        htable[hashval]->parent = NULL;
        htable[hashval]->child = NULL;
    } else {
        curhash=htable[hashval];
        while(curhash->child != NULL) {
            curhash=curhash->child;
        }
        curhash->child = newhash;
        newhash->child = NULL;
        newhash->parent = curhash;
    }
    return newhash;
}

struct hashtable *findhash(char *key) {
    unsigned int hashval;
    struct hashtable *curhash;
    hashval = 0;
    if (htable[hashval] == NULL) {
        return NULL;
    }
    if (!strcmp(htable[hashval]->key, key)) {
        curhash = htable[hashval];
        return curhash;
    } else {
        if (htable[hashval]->child == NULL) {
            return NULL;
        }
        curhash = htable[hashval]->child;
        if (!strcmp(curhash->key, key)) {
            return curhash;
        }
        while (curhash->child != NULL) {
            if (!strcmp((curhash->key), (key))) {
                return curhash;
            }
            curhash = curhash->child;
        }
        if (!strcmp(curhash->key, key)) {
            return curhash;
        } else {
            return NULL;
        }
    }
}

void printAndEmptyWords(FILE* file) {
    struct hashtable *curhash, *prevhash;
    if (htable[0] != NULL) {
        curhash = htable[0];
        while(curhash != NULL) {
            fprintf(file, "'%s': %d\n", curhash->key, curhash->count);
            prevhash = curhash;
            curhash = curhash->child;
            free(prevhash->key);
            free(prevhash);
        }
    }
}
