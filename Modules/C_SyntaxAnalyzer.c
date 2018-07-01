#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include "Structures/B_TerminalSymbols.h"
#include "Structures/A_Tokens.h"
#include "B_LexAnalyzer.h"
#include "Structures/Node.h"
#include "G_CodeGenerator.h"

const int WordSize = 4;

int varsize;

Node objectsStart;
Node universe;
Node end;

long toInt(char *val, int size) {

    long num = 0;
    int exp = 0;

    for (int i = size - 1; i >= 0; --i) {
        num += (long) (*(val + i) - '0') * (long) pow(10, exp++);
    }

    return num;
}

int namesEquals(char *name1, int size1, char *name2, int size2) {
    if (size1 == size2) {

        for (int i = 0; i < sizeof(size1); ++i)
            if (name1[i] != name2[i])
                return 0;

        return 1;

    } else
        return 0;
}




Node *addNode(int class) {

    Node *objects = &objectsStart;

    end.name = tokensFlow.current->symbols;
    end.size = tokensFlow.current->length;


    while (namesEquals(tokensFlow.current->symbols, tokensFlow.current->length, objects->next->name,
                       objects->next->size) != 1)
        objects = objects->next;

    if (objects->next == &end) {
        Node *newObject = node_new();
        node_setName(newObject, tokensFlow.current->symbols, tokensFlow.current->length);
        newObject->class = class;
        newObject->next = &end;
        objects->next = newObject;
        return newObject;
    } else {
        Mark("declared again");
        return objects->next;
    }

};

Node *find() {

    Node *objects = &objectsStart;
    Node *object;

    node_setName(&end, tokensFlow.current->symbols, tokensFlow.current->length);
    while (true) {

        object = objects->next;

        while (namesEquals(object->name, object->size, tokensFlow.current->symbols, tokensFlow.current->length) != 1) {
            object = object->next;
        }

        if (object != &end) {
            return object;
        }

        if (objects == &universe) {
            printf("Not declared");
            return object;
        }

        objects = objects->dsc;
    }
}

Node findField(struct Node list) {
    node_setName(&end, tokensFlow.current->symbols, tokensFlow.size);
    while (namesEquals(list.name, list.size, tokensFlow.current->symbols, tokensFlow.current->length) != 1) {
        list = *list.next;
    }
    return list;
}

bool isParam(struct Node obj) {
    //CHANGE
    return (obj.class == 2) || (obj.class == 1) && (obj.val > 0);
}

void openScope() {
    Node *s = node_new();
    s->class = HEAD;
    s->dsc = &objectsStart;
    s->next = &end;
    objectsStart = *s;
}

void closeScope() {
    objectsStart = *objectsStart.dsc;
}

static enter(int class, long value, char *name, int length, Type *type) {
    Node *node = node_new();
    node->class = class;
    node->val = value;
    node->type = type;
    node_setName(node, name, length);
    node->next = objectsStart.next;
    objectsStart.next = node;
}

void scope_initialise() {
    openScope();
    enter(TYP, 1, terminalSymbols.BOOL.name, terminalSymbols.BOOL.nameLength, &boolType);
    enter(TYP, 2, terminalSymbols.INT.name, terminalSymbols.INT.nameLength, &intType);
    enter(CONST, 1, "TRUE", 4, &boolType);
    enter(CONST, 0, "FALSE", 5, &boolType);
    enter(S_PROC, 1, "Read", 5, &boolType);
    enter(S_PROC, 2, "Write", 5, NULL);
    enter(S_PROC, 3, "WriteHex", 5, NULL);
    enter(S_PROC, 4, "WriteLn", 5, NULL);
    universe = objectsStart;
}


struct Item expression(struct Item item1);

struct Item selector(struct Item item) {
    while ((tokensFlow.current->type == terminalSymbols.LBRAK.type) &&
           (tokensFlow.current->type == terminalSymbols.PERIOD.type)) {
        if (tokensFlow.current->type == terminalSymbols.LBRAK.type) {
            tf_next(&tokensFlow);
            struct Item exp = expression(item);

            if (exp.type->form == ARRAY)
                Index(item, exp);
            else
                printf("NOT ARR");

            if (tokensFlow.current->type == terminalSymbols.RBRAK.type)
                tf_next(&tokensFlow);
            else
                printf("]");
        } else {
            tf_next(&tokensFlow);

            if (tokensFlow.current->type != terminalSymbols.IDENT.type) {
                if (item.type->form == RECORD) {
                    struct Node obj = findField(*item.type->fields);
                    tf_next(&tokensFlow);
                    if (&obj != &end) {
                        Field(item, obj);
                    } else {
                        printf("not defined");
                    }
                } else
                    printf("not record");
            } else {
                printf("ident?");
            }
        }
    }
}

// factor = ident selector | integer | ( expression ) | ~ factor

struct Item factor() {

    struct Item _factor;
    Node object;

    if (tokensFlow.current->type < terminalSymbols.LPAREN.type) {
        printf("ident?");

        while (tokensFlow.current->type >= terminalSymbols.LPAREN.type)
            tf_next(&tokensFlow);
    }

    if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
        object = *find();
        tf_next(&tokensFlow);
        MakeItem(_factor, object);
        selector(_factor);
    } else if (tokensFlow.current->type == terminalSymbols.NUMBER.type) {
        _factor = MakeConstltem(_factor, intType, toInt(tokensFlow.current->symbols, tokensFlow.current->length));
        tf_next(&tokensFlow);
    } else if (tokensFlow.current->type == terminalSymbols.LPAREN.type) {
        tf_next(&tokensFlow);
        _factor = expression(_factor);
        if (tokensFlow.current->type == terminalSymbols.RPAREN.type)
            tf_next(&tokensFlow);
        else
            printf(")?");
    } else if (tokensFlow.current->type == terminalSymbols.NOT.type) {
        tf_next(&tokensFlow);
        _factor = factor(_factor);
        Op1(terminalSymbols.NOT.type, _factor);
    } else {
        printf("Множитель?");
        MakeItem(_factor, end);
    }

    return _factor;

}


// term = factor {(* | DIV | MOD | &) factor}
struct Item term(struct Item item) {
    int operator;

    struct Item item1;

    item = factor(item); // Proceed factor

    while ((tokensFlow.current->type >= terminalSymbols.TIMES.type) &&
           (tokensFlow.current->type <= terminalSymbols.AND.type)) {

        operator = tokensFlow.current->type;
        tf_next(&tokensFlow);
        if (operator == terminalSymbols.AND.type)
            Op1(operator, item);
        factor(item1);
        Op2(operator, item, item1);
    }

    return item;
}

struct Item simpleExpression(struct Item item1) {

    struct Item item2;

    int operator;

    if (tokensFlow.current->type == terminalSymbols.PLUS.type) {
        tf_next(&tokensFlow);
        item1 = term(item1);
    } else if (tokensFlow.current->type == terminalSymbols.MINUS.type) {
        tf_next(&tokensFlow);
        item1 = term(item1);
        Op1(terminalSymbols.MINUS.type, item1);
    } else {
        item1 = term(item1);
    }

    while ((tokensFlow.current->type >= terminalSymbols.PLUS.type) &&
           (tokensFlow.current->type <= terminalSymbols.OR.type)) {
        operator = tokensFlow.current->type;
        tf_next(&tokensFlow);

        if (operator == terminalSymbols.OR.type) {

        }
        item2 = term(item2);
        Op2(operator, item1, item2);
    }

    return item1;
}

//expression = SimpleExpression [relation SimpleExpression]

struct Item expression(struct Item item1) {

    struct Item item2;
    int operator;

    item1 = simpleExpression(item1); //Proceed SimpleExpression

    if ((tokensFlow.current->type >= terminalSymbols.EQL.type) &&
        (tokensFlow.current->type <= terminalSymbols.GTR.type)) {

        operator = tokensFlow.current->type;
        tf_next(&tokensFlow);
        simpleExpression(item2);
        Relation(operator, item1, item2);
    }

    return item1;
}

void parameter(struct Node framePointer) {
    struct Item item;
    expression(item);

    if (isParam(framePointer))
        Parameter(item, *framePointer.type, framePointer.class);
    else
        printf("too many arguments");
}

void param(struct Item item) {
    if (tokensFlow.current->type == terminalSymbols.LPAREN.type)
        printf(")?");
    expression(item);
    if (tokensFlow.current->type == terminalSymbols.RPAREN.type)
        printf(")?");
}

void StatSequence() {
    Node parameter;
    Node obj;
    struct Item item1;
    struct Item item2;
    long l;

    while (true) {
        obj = end;

        if (tokensFlow.current->type < terminalSymbols.IDENT.type) {
            printf("operator?");
            while (tokensFlow.current->type < terminalSymbols.IDENT.type) {
                tf_next(&tokensFlow);
            }
        }

        if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
            obj = *find();
            tf_next(&tokensFlow);
            MakeItem(item1, obj);
            selector(item1);
            if (tokensFlow.current->type == terminalSymbols.BECOMES.type) {
                tf_next(&tokensFlow);
                expression(item2);
                Store(item1, item2);
            } else if (tokensFlow.current->type == terminalSymbols.EQL.type) {
                printf(":=?");
                tf_next(&tokensFlow);
                expression(item2);
            } else if (item1.mode == PROC) {
                parameter = *obj.dsc;
                if (tokensFlow.current->type == terminalSymbols.LPAREN.type) {
                    tf_next(&tokensFlow);
                    if (tokensFlow.current->type == terminalSymbols.RPAREN.type)
                        tf_next(&tokensFlow);
                    else {
                        while (true) {
                            if (tokensFlow.current->type == terminalSymbols.COMMA.type)
                                tf_next(&tokensFlow);
                            else if (tokensFlow.current->type == terminalSymbols.RPAREN.type) {
                                tf_next(&tokensFlow);
                                break;
                            } else if (tokensFlow.current->type >= terminalSymbols.SEMICOLON.type)
                                break;
                            else
                                printf(") or ,?");
                        }
                    }
                }
                if (obj.val < 0) {
                    printf("straightforward call");
                } else if (~isParam(parameter)) {
                    Call(item1);
                } else {
                    printf("too many arguments");
                }
            } else if (item1.mode == S_PROC) {
                if (obj.val <= 3);
                param(item2);
                IOCall(item1, item2);
            } else if (obj.class == TYP) {
                printf("wrong operator");
            } else {
                printf("operator");
            }
        } else if (tokensFlow.current->type == terminalSymbols.IF.type) {
            tf_next(&tokensFlow);
            expression(item1);
            CJump(item1);
            if (tokensFlow.current->type == terminalSymbols.THEN.type)
                tf_next(&tokensFlow);
            else
                printf("THEN?");
            StatSequence();
            l = 0;
            while (tokensFlow.current->type == terminalSymbols.ELSEIF.type) {
                tf_next(&tokensFlow);
                FJump(l);
                FixLink(l);
                expression(item1);
                CJump(item1);
                if (tokensFlow.current->type == terminalSymbols.THEN.type)
                    tf_next(&tokensFlow);
                else
                    printf("THEN?");
                StatSequence();
            }
            if (tokensFlow.current->type == terminalSymbols.ELSE.type) {
                tf_next(&tokensFlow);
                FJump(l);
                FixLink(item1.a);
                StatSequence();
            } else {
                FixLink(item1.a);
            }
            FixLink(l);
            if (tokensFlow.current->type == terminalSymbols.END.type)
                tf_next(&tokensFlow);
            else
                printf("END?");
        } else if (tokensFlow.current->type == terminalSymbols.WHILE.type) {
            tf_next(&tokensFlow);
            l = pc;
            expression(item1);
            CJump(item1);
            if (tokensFlow.current->type == terminalSymbols.DO.type)
                tf_next(&tokensFlow);
            else
                printf("DO?");
            StatSequence();
            BJump(l);
            FixLink(item1.a);
        }
        if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type)
            tf_next(&tokensFlow);
        else if ((tokensFlow.current->type >= terminalSymbols.SEMICOLON.type) && (tokensFlow.current->type)
                 || (tokensFlow.current->type >= terminalSymbols.ARR.type))
            break;
        else
            printf(";?");
    }
};

// identList = ident {, ident};
Node *identList(int class) {

    if (tokensFlow.current->type == terminalSymbols.IDENT.type) {

        //Add Identifier to parse tree
        Node *firstAdded = addNode(class); //Have to save link for parameter setup later
        tf_next(&tokensFlow);

        while (tokensFlow.current->type == terminalSymbols.COMMA.type) {
            tf_next(&tokensFlow);
            if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
                //If there are any more identifiers add them too
                addNode(class);
                tf_next(&tokensFlow);
            } else Mark("Identifier?");
        }


        if (tokensFlow.current->type ==
            terminalSymbols.COLON.type) { // Probably better to move this block it in declarations
            tf_next(&tokensFlow);
        } else
            Mark("Missing \":\"");

        return firstAdded;
    }
}

Type *type() {

    Node *obj;
    struct Item x;
    Type *tp;
    Type *typ = &intType;

    if (tokensFlow.current->type != terminalSymbols.IDENT.type && tokensFlow.current->type < terminalSymbols.ARR.type) {

        Mark("тип?");

        do { tf_next(&tokensFlow); }
        while (!(tokensFlow.current->type == terminalSymbols.IDENT.type &&
                 tokensFlow.current->type >= terminalSymbols.ARR.type));
    }

    if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&tokensFlow);

        if (obj->class == TYP)
            typ = obj->type;
        else
            Mark("Identifiers isn't a type");

    } else if (tokensFlow.current->type == terminalSymbols.ARR.type) {

        tf_next(&tokensFlow);
        x = expression(x);

        if ((x.mode != CONST) && (x.a < 0))
            Mark("Array size should be constant and greater than zero");

        if (tokensFlow.current->type == terminalSymbols.OF.type)
            tf_next(&tokensFlow);
        else
            Mark("Missing \"OF\" word");

        Type *baseType = type();

        typ = type_new();
        typ->form = terminalSymbols.ARR.type;
        typ->base = baseType;
        typ->len = (int) x.a;
        typ->size = typ->len * baseType->size;

    } else if (tokensFlow.current->type == terminalSymbols.REC.type) {

        tf_next(&tokensFlow);

        typ = type_new();
        typ->form = RECORD;
        typ->size = 0;

        openScope();

        while (true) {
            if (tokensFlow.current->type == terminalSymbols.IDENT.type) {

                Node *firstAdded = identList(FLD);

                tp = type();
                obj = firstAdded;
                while (obj != &end) {
                    obj->type = tp;
                    obj->val = typ->size;
                    typ->size += obj->type->size;
                    obj = obj->next;
                }
            }

            if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                tf_next(&tokensFlow);
            else if (tokensFlow.current->type == terminalSymbols.IDENT.type)
                Mark("Missing \";\"");
            else
                break;
        }

        typ->fields = objectsStart.next;
        closeScope();
        if (tokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&tokensFlow);
        } else
            Mark("Missing \"END\"");
    } else
        Mark("Identifier expected");

    return typ;
}

// declarations = ["CONST" {ident = expression ;}] [TYPE {ident = type;}] [VAR = {IdentList : type ;}] {ProcedureDeclarations;}
// ORDER SENSITIVE
long declarations() {

    Node *firstAdded;
    Node *obj;
    struct Item item;

    long varsize = 0;

    if ((tokensFlow.current->type < terminalSymbols.CONSTT.type) &&
        (tokensFlow.current->type != terminalSymbols.END.type)) {

        printf("Declarations?"); // REPLACE

        while ((tokensFlow.current->type < terminalSymbols.CONSTT.type) ||
               (tokensFlow.current->type != terminalSymbols.END.type))
            tf_next(&tokensFlow);
    }

    while (true) {

        if (tokensFlow.current->type == terminalSymbols.CONSTT.type) { // Proceed CONST declarations if there are any

            tf_next(&tokensFlow);

            while (tokensFlow.current->type == terminalSymbols.IDENT.type) {

                obj = addNode(CONST);

                tf_next(&tokensFlow);

                if (tokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&tokensFlow);
                else
                    printf("=?");

                item = expression(item);

                if (item.mode == CONST) { //CONST expr MUST consist of constants
                    obj->val = item.a;
                    obj->type = item.type;
                } else {
                    printf("not const");
                }

                if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&tokensFlow);
                else
                    printf(";");
            }
        }

        if (tokensFlow.current->type == terminalSymbols.INT.type) {

            tf_next(&tokensFlow);

            while (tokensFlow.current->type == terminalSymbols.IDENT.type) {

                obj = addNode(TYP);
                tf_next(&tokensFlow);

                if (tokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&tokensFlow);
                else
                    printf("=?");

                type();

                if (tokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&tokensFlow);
                else printf(";?");
            }
        }

        if (tokensFlow.current->type == terminalSymbols.VAR.type) {
            tf_next(&tokensFlow);

            while (tokensFlow.current->type == terminalSymbols.IDENT.type) {

                firstAdded = identList(VARIABLE);
                Type *tp = type(); // Proceed type identification
                obj = firstAdded;

                while (obj != &end) {
                    obj->type = tp;
                    obj->level = curlev;
                    varsize = varsize + obj->type->size;
                    obj->val = -varsize;
                    obj = obj->next;
                }


                if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&tokensFlow);
                else
                    printf(";?");
            }

            if ((tokensFlow.current->type >= terminalSymbols.CONSTT.type) &&
                (tokensFlow.current->type <= terminalSymbols.VAR.type))
                printf("Объявление?");
            else
                break;
        }

    }
};

void FPSection(long *locblksize, long *parblksize) {
    Node *obj, *first;
    Type *tp;
    long parsize;

    if (tokensFlow.current->type == terminalSymbols.VAR.type) {
        tf_next(&tokensFlow);
        identList(PAR);
    } else
        identList(VARIABLE);

    if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&tokensFlow);
        if (obj->class == TYP)
            tp = obj->type;
        else {
            Mark("ident?");
            tp = &intType;
        }
    } else {
        Mark("ident?");
        tp = &intType;
    }

    if (first->class == VARIABLE) {
        parsize = tp->size;
        if (tp->form >= ARRAY) {
            Mark("not parameter");
        } else {
            parsize = WordSize;
        }
        obj = first;

        while (obj != &end) {
            obj->type = tp;
            parblksize++;
            parsize++;
            obj = obj->next;
        }
    }
}

void procedureDeclaration() {
    int const marksize = 8;
    Node *proc, obj;
    char *procid;
    long locblksize, parblksize;

    tf_next(&tokensFlow);

    if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
        procid = tokensFlow.current->symbols;
        proc = node_new();
        tf_next(&tokensFlow);
        parblksize = marksize;
        IncLevel(1);
        openScope();
        proc->val = -1;
        if (tokensFlow.current->type == terminalSymbols.LPAREN.type) {
            tf_next(&tokensFlow);
            if (tokensFlow.current->type == terminalSymbols.RPAREN.type)
                tf_next(&tokensFlow);
            else {
                FPSection(&locblksize, &parblksize);

                while (tokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
                    tf_next(&tokensFlow);
                    FPSection(&locblksize, &parblksize);
                }

                if (tokensFlow.current->type == terminalSymbols.RPAREN.type)
                    tf_next(&tokensFlow);
                else
                    Mark(")?");
            }
        } else if (curlev == 1) {
            //ENTERCMD
        }
        obj = *objectsStart.next;
        locblksize = parblksize;
        while (&obj != &end) {
            obj.level = curlev;
            if (obj.class == PAR)
                locblksize -= WordSize;
            else {
                obj.val = locblksize;
                obj = *obj.next;
            }
        }
        proc->dsc = objectsStart.next;
        if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
            tf_next(&tokensFlow);

        } else {
            Mark(";?");
        }

        locblksize = 0;
        declarations();
        while (tokensFlow.current->type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                tf_next(&tokensFlow);
            else
                Mark(";?");

        }
        proc->val = pc;
        Enter(locblksize);
        if (tokensFlow.current->type == terminalSymbols.BEGIN.type) {
            tf_next(&tokensFlow);
            StatSequence();

        }
        if (tokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&tokensFlow);
        } else
            Mark("end ?");
        if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
            //TODO
            if (procid != tokensFlow.current->symbols) {
                Mark("не подходит");
                tf_next(&tokensFlow);
            }
            Return(parblksize - marksize);
            closeScope();
            IncLevel(-1);

        }
    }

};


// STARTING SYMBOL
// MODULE = MODULE ident; [ImportList] declarations [BEGIN StatementSequence] END ident "."
void module() {

    char *moduleIdentifier;

    if (tf_next(&tokensFlow)->type == terminalSymbols.MODULE.type) {
        scope_initialise();
        Open();
        openScope();
        if (tf_next(&tokensFlow)->type == terminalSymbols.IDENT.type) {
            moduleIdentifier = tokensFlow.current->symbols;

            if (tf_next(&tokensFlow)->type == terminalSymbols.SEMICOLON.type) {
                tf_next(&tokensFlow);
            }
        } else {
            Mark(";?");
        }

        varsize += declarations(); // Proceed declarations

        while (tokensFlow.current->type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (tokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
                tf_next(&tokensFlow);
                StatSequence();
            } else
                Mark(";?");
        }

        Header(varsize);
        if (tokensFlow.current->type == terminalSymbols.BEGIN.type) {
            tf_next(&tokensFlow);
            StatSequence();
        }
        if (tokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&tokensFlow);

        } else
            Mark("End?");
        if (tokensFlow.current->type == terminalSymbols.IDENT.type) {
            //TODO
            if (moduleIdentifier != tokensFlow.current->symbols) {
                Mark("не подходит");
            }
            tf_next(&tokensFlow);

        } else
            Mark("идентефикатор");
        if (tokensFlow.current->type != terminalSymbols.PERIOD.type) {
            Mark(".?");
        }
        closeScope();

    } else
        Mark("Модуль?");
}



