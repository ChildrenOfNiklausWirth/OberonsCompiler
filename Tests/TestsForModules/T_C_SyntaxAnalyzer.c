#include "../../Modules/C_SyntaxAnalyzer.c"

char address[] = "../Tests/SamplePrograms/Trigonometry";


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

Node *getRightResultForObjectStart() {
    Node *rightObjectStart;
    Type *type;
    Node *fields;
    Node *dsc;




    rightObjectStart = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);//end

    //RVLLengthSqr
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);


    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(1, 1, -4, "tempInt", sizeof("tempInt") - 1, type, NULL, dsc);


    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "lengthInt", sizeof("lengthInt") - 1, type, NULL, dsc);


    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);//end

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);
    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);

    type = type_newType(3, fields, NULL, 8, 0);
    dsc = object_newObject(2, 1, 0, "pt", sizeof("pt") - 1, type, NULL, dsc);

    rightObjectStart = object_newObject(6, 0, 51, "RVLengthSqr", sizeof("RVLengthSqr") - 1, NULL, dsc,
                                        rightObjectStart);
    //RVLLengthSqr

    //sqr
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "sqrInt", sizeof("sqrInt") - 1, type, NULL, dsc);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(1, 1, 16, "int", sizeof("int") - 1, type, NULL, dsc);

    rightObjectStart = object_newObject(6, 0, 38, "sqr", sizeof("sqr") - 1, NULL, dsc, rightObjectStart);
    //sqr

    //isThirdOrForth
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "ansBool", sizeof("ansBool") - 1, type, NULL, dsc);


    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);


    type = type_newType(3, fields, NULL, 8, 0);
    dsc = object_newObject(2, 1, 12, "pt", sizeof("pt") - 1, type, NULL, dsc);

    rightObjectStart = object_newObject(6, 0, 19, "isThirdOrForth", sizeof("isThirdOrForth") - 1, NULL, dsc,
                                        rightObjectStart);
    //isThirdOrForth

    //isFirstOrSecond
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(2, 1, 0, "ansBool", sizeof("ansBool") - 1, type, NULL, dsc);


    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);//end

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);


    type = type_newType(3, fields, NULL, 8, 0);
    dsc = object_newObject(2, 1, 0, "pt", sizeof("pt") - 1, type, NULL, dsc);

    rightObjectStart = object_newObject(6, 0, 0, "isFirstOrSecond", sizeof("isFirstOrSecond") - 1, NULL, dsc,
                                        rightObjectStart);
    ////isFirstOrSecond


    //bol1,bol2,bol3,bol4
    type = type_newType(0, NULL, NULL, 4, 0);
    rightObjectStart = object_newObject(1, 0, -56, "bol4", sizeof("bol4") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -52, "bol3", sizeof("bol3") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -48, "bol2", sizeof("bol2") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -44, "bol1", sizeof("bol1") - 1, type, NULL, rightObjectStart);


    //pt3,pt2,pt3
    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);//end

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);

    type = type_newType(3, fields, NULL, 8, 0);
    rightObjectStart = object_newObject(1, 0, -40, "pt3", sizeof("pt3") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -32, "pt2", sizeof("pt2") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -24, "pt1", sizeof("pt1") - 1, type, NULL, rightObjectStart);


    //int4,int3,int2,int1
    type = type_newType(1, NULL, NULL, 4, 0);
    rightObjectStart = object_newObject(1, 0, -16, "int4", sizeof("int4") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -12, "int3", sizeof("int3") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -8, "int2", sizeof("int2") - 1, type, NULL, rightObjectStart);
    rightObjectStart = object_newObject(1, 0, -4, "int1", sizeof("int1") - 1, type, NULL, rightObjectStart);

    //Point
    fields = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);//end

    type = type_newType(1, NULL, NULL, 4, 0);
    fields = object_newObject(4, 0, 4, "y", sizeof("y") - 1, type, NULL, fields);
    fields = object_newObject(4, 0, 0, "x", sizeof("x") - 1, type, NULL, fields);

    type = type_newType(3, fields, NULL, 8, 0);
    rightObjectStart = object_newObject(5, 0, 0, "Point", sizeof("Point") - 1, type, NULL, rightObjectStart);
    //Point





    //DSC
    dsc = object_newObject(0, 0, 0, "int2", sizeof("int2") - 1, NULL, NULL, NULL);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(5, 0, 1, "BOOLEAN", sizeof("BOOLEAN") - 1, type, NULL, dsc);

    type = type_newType(1, NULL, NULL, 4, 0);
    dsc = object_newObject(5, 0, 2, "INTEGER", sizeof("INTEGER") - 1, type, NULL, dsc);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(3, 0, 1, "TRUE", sizeof("TRUE") - 1, type, NULL, dsc);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(3, 0, 0, "FALSE", sizeof("FALSE"), type, NULL, dsc);

    type = type_newType(0, NULL, NULL, 4, 0);
    dsc = object_newObject(7, 0, 1, "Read", sizeof("Read") - 1, type, NULL, dsc);

    dsc = object_newObject(7, 0, 2, "Write", sizeof("Write") - 1, NULL, NULL, dsc);

    dsc = object_newObject(7, 0, 3, "Write", sizeof("Write") - 1, NULL, NULL, dsc);

    dsc = object_newObject(7, 0, 4, "Write", sizeof("Write") - 1, NULL, NULL, dsc);

    dsc = object_newObject(0, 0, 0, NULL, 0, NULL, NULL, dsc);

    rightObjectStart->dsc = dsc;

    //DSC

    rightObjectStart = object_newObject(0, 0, 0, NULL, 0, NULL, NULL, rightObjectStart);
    return rightObjectStart;

}

void node_print(Node node) {
    for (int i = 0; i < node.nameLength; ++i)
        printf("%c", node.name[i]);
    printf("\n");

}

int node_assertEqualsTwoNodes(Node node1, Node node2) {

    if (node1.class != node2.class) {
        node_print(node1);
        node_print(node2);
        printf("Unequal class \n%d\n%d\n", node1.class, node2.class);
        return 0;
    }
    if (node1.level != node2.level) {
        node_print(node1);
        node_print(node2);
        printf("Unequal level \n%d\n%d\n", node1.level, node2.level);
        return 0;
    }
    if (node1.val != node2.val) {
        node_print(node1);
        node_print(node2);
        printf("Unequal val \nright %li\nour %li\n", node1.val, node2.val);
        return 0;
    }
    if (!namesEquals(node1.name, node1.nameLength, node2.name, node2.nameLength)) {
        node_print(node1);
        node_print(node2);
        printf("Unequal names \n%s\n%s\n", node1.name, node2.name);
        return 0;
    }
    if (node1.next != NULL && node2.next != NULL)
        if (!node_assertEqualsTwoNodes(*node1.next, *node2.next))
            return 0;
    if (node1.dsc != NULL && node2.dsc != NULL)
        if (!node_assertEqualsTwoNodes(*node1.dsc, *node2.dsc))
            return 0;

    return 1;

}


int main() {
    printf("SyntaxAnalyzer Testing...\n\n");
    FILE *file = fopen(address, "r");
    lexAnalysis(file);
    moduleWithoutCloseScope();

    Node *rightObjectStart = getRightResultForObjectStart();

    printf("objectStart equals\n");
    if (node_assertEqualsTwoNodes(*rightObjectStart, *objectsStart))
        printf("True");
    else
        printf("False");


}

