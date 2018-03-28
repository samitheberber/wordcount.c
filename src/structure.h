/* structure.h */

typedef struct character {
    char c;
    int count;
    struct character *next;
} Character, *CharacterP;

typedef struct worddata {
    int count;
} WD, *WDP;

typedef struct {
    CharacterP fc;
} Storage, *StorageP;

/* Create a storage */
StorageP buildStorage(void);

/* Unbuild a storage */
int unbuildStorage(StorageP, FILE*);

/* Inserts words in strorage */
void insertWords(StorageP, FILE*);

/* Hash table */
struct hashtable {
    struct hashtable *child;
    struct hashtable *parent;
    char* key;
    int count;
};
struct hashtable *addhash(char *);
struct hashtable *findhash(char *);
void printAndEmptyWords(FILE*);
