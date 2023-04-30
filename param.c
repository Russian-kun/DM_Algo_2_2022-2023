#include "param.h"
#include <stdlib.h>
#include <string.h>

typedef struct _dict {
    int size, maxsize;
    char** values;
    char** keys;
} dict, *Dict;

static Dict newDict() {
    Dict dict = (Dict)malloc(sizeof(dict));
    dict->size = 0;
    dict->maxsize = 10;
    dict->keys = (char**)malloc(sizeof(char*) * 10);
    dict->values = (char**)malloc(sizeof(char*) * 10);
    return dict;
}

static void freeDict(Dict dict) {
    free(dict->keys);
    free(dict->values);
    free(dict);
}

static void dictSet(Dict dict, char* key, char* value) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            dict->values[i] = value;
            return;
        }
    }
    if (dict->size == dict->maxsize) {
        dict->maxsize *= 2;
        dict->keys = (char**)realloc(dict->keys, sizeof(char*) * dict->maxsize);
        dict->values = (char**)realloc(dict->values, sizeof(char*) * dict->maxsize);
    }
    dict->keys[dict->size] = key;
    dict->values[dict->size] = value;
    dict->size++;
}

static Dict readParams(int argv, char* argc[]) {
    Dict dict = newDict();
    for (int i = 1; i < argv; i++) {
        char* arg = argc[i];
        if (arg[0] == '-' && strlen(arg) > 1) {
            char* key = arg + 1;
            char* value = argc[++i];
            dictSet(dict, key, value);
        }
    }
    return dict;
}

static char* dictGet(Dict dict, char* key) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            return dict->values[i];
        }
    }
    return NULL;
}

void interpretParam(int argc, char* argv[], int* nbp, int* help, int W, int wmin, int kp) {
    Dict dict = readParams(argc, argv);

    // Tres peu opti mais bon pas grave si c'est juste pour recuperer les parametres
    if (dictGet(dict, "help") != NULL || dictGet(dict, "h") != NULL) {
        *help = 1;
        freeDict(dict);
        return;
    }

    if (dictGet(dict, "nbp") != NULL || dictGet(dict, "n") != NULL) {
        *nbp = atoi(dictGet(dict, "nbp"));
    }

    if (dictGet(dict, "W") != NULL || dictGet(dict, "W") != NULL) {
        W = atoi(dictGet(dict, "W"));
    }

    if (dictGet(dict, "wmin") != NULL || dictGet(dict, "w") != NULL) {
        wmin = atoi(dictGet(dict, "wmin"));
    }

    if (dictGet(dict, "kp") != NULL || dictGet(dict, "k") != NULL) {
        kp = atoi(dictGet(dict, "kp"));
    }

    freeDict(dict);
}