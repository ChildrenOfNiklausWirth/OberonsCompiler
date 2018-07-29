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

void object_addObject(Node *node, Node *next) {
    node->next = next;
    node = node->next;

}

void createRightResultForObjectStart(Node *rightObjectStart) {
    rightObjectStart=calloc(1, sizeof(Node));
    Node *currentNode;
    currentNode = object_newObject(5, 0, 0, "Point", sizeof("Point") - 1, type_new(), NULL, NULL);
    object_addObject(rightObjectStart, currentNode);

    currentNode = object_newObject(5, 0, 0, "int1", sizeof("int1") - 1, type_new(), NULL, NULL);
    object_addObject(rightObjectStart, currentNode);

}


int compareNodesPointer(Node *node1, Node *node2) {


}

int main() {

    lexAnalysis(address);
    moduleWithoutCloseScope();

    createRightResultForObjectStart(rigthObjectStart);


}