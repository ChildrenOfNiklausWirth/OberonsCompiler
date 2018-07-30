#include "../../Modules/C_SyntaxAnalyzer.c"

char address[] = "../Tests/ProgrammsOnOberon/Trigonometry";
Node *rigthObjectStart;


Node *object_newObject(int class, int level, long val, char *name, int nameLength, Type *type, Node *dsc, Node *next) {
    Node *newObject = node_new();
    newObject->class = class;
    newObject->level = level;
    newObject->val = val;
    newObject->name = name;
    newObject->nameLength = nameLength;
    newObject->type = type;
    newObject->dsc = dsc;
    newObject->next = next;
    return newObject;
}

Type *type_newType(int form, Node *fields, Type *base, int size, int len) {
    Type *type = type_new();
    type->form = form;
    type->fields = fields;
    type->base = base;
    type->size = size;
    type->len = len;
    return type;

}

void object_addObject(Node *rightObjectStart, Node *next) {
    Node *copy = rightObjectStart;
    while (copy->next != NULL)
        copy = copy->next;
    copy->next = next;

}


void createRightResultForObjectStart(Node *rightObjectStart) {
    rightObjectStart = object_newObject(0, 0, 0, NULL, 0, NULL, NULL, NULL);
    Type *type;
    Node *fields;
    Node *dsc;
    Node *next;


    //end
    objectsStart = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    //RVLLengthSqr
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(1, 1, -4, "tempInt", sizeof("tempInt") - 1, type, NULL, dsc);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "lengthInt", sizeof("lengthInt") - 1, type, NULL, dsc);


    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);

    type = type_newType(3, fields, NULL, 8, 0);

    dsc = object_newObject(2, 1, 0, "pt", sizeof("pt") - 1, type, NULL, dsc);

    objectsStart = object_newObject(6, 0, 51, "RVLengthSqr", sizeof("RVLengthSqr") - 1, NULL, dsc, objectsStart);
    //RVLLengthSqr

    //sqr
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "sqrInt", sizeof("sqrInt") - 1, type, NULL, dsc);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(1, 1, 16, "int", sizeof("int") - 1, type, NULL, dsc);

    objectsStart = object_newObject(6, 0, 38, "sqr", sizeof("sqr") - 1, NULL, dsc, objectsStart);
    //sqr

    //isThirdOrForth
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "ansBool", sizeof("ansBool") - 1, type, NULL, dsc);


    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);


    type = type_newType(3, fields, NULL, 8, 0);
    dsc = object_newObject(2, 1, 0, "pt", sizeof("pt") - 1, type, NULL, dsc);

    objectsStart = object_newObject(6, 0, 19, "isThirdOrForth", sizeof("isThirdOrForth"), NULL, dsc, objectsStart);
    //isThirdOrForth

    //isFirstOrSecond
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type=type_newType(0,NULL,NULL,4,0);
    dsc=object_newObject(2,1,0,"ansBool", sizeof("ansBool")-1,type,NULL,dsc);

    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);


    type = type_newType(3, fields, NULL, 8, 0);
    dsc=object_newObject(2,1,0,"pt", sizeof("pt")-1,type,NULL,dsc);

    objectsStart=object_newObject(6,0,0,"isFirstOrSecond", sizeof("isFirstOrSecond")-1,NULL,dsc,objectsStart);
    ////isFirstOrSecond


    //bol4
    type=type_newType(0,NULL,NULL,4,0);
    objectsStart=object_newObject(1,0,-56,"bol4", sizeof("bol4")-1,type,NULL,objectsStart);

    //bol3
    type=type_newType(0,NULL,NULL,4,0);
    objectsStart=object_newObject(1,0,-52,"bol3", sizeof("bol3")-1,type,NULL,objectsStart);

    //bol2
    type=type_newType(0,NULL,NULL,4,0);
    objectsStart=object_newObject(1,0,-48,"bol2", sizeof("bol2")-1,type,NULL,objectsStart);

    //bol1
    type=type_newType(0,NULL,NULL,4,0);
    objectsStart=object_newObject(1,0,-44,"bol1", sizeof("bol1")-1,type,NULL,objectsStart);


    //pt3












}


int compareNodesPointer(Node *node1, Node *node2) {


}

int main() {

    lexAnalysis(address);
    moduleWithoutCloseScope();

    createRightResultForObjectStart(rigthObjectStart);


}