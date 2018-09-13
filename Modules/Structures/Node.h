#ifndef OBERONSCOMPILER_C_OBJECT_H
#define OBERONSCOMPILER_C_OBJECT_H
struct Item;
typedef struct Node Node;
typedef struct type Type;



typedef struct type {
    int form;
    Node *fields;//For complex object
    Type *base;
    int size;
    int len;

} Type;

Type *type_new();

int type_equals(Type type1, Type type2);

struct Item {
    int mode;
    int level;
    Type *type;
    long a, b, c, r;
};

//int item_equals(struct Item item1, struct Item item2);

typedef struct Node {
    int class;//Допустимые значения в SA
    int level;//Уровень вложенности
    long val;//адрес точки входа в процедуру
    char *name;
    int nameLength;
    Type *type;//Для переменных
    Node *dsc;//Для процедур
    Node *next;
} Node;

Node *node_new();

void node_setName(struct Node *obj, char *name, int name_size);

int nodes_equals(struct Node object1, struct Node object2);


#endif //OBERONSCOMPILER_C_OBJECT_H
