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

struct Node objectsStart;
struct Node universe;
struct Node end;

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

    end.name = syntaxTokensFlow.current->symbols;
    end.size = syntaxTokensFlow.current->length;


    while (namesEquals(syntaxTokensFlow.current->symbols, syntaxTokensFlow.current->length, objects->next->name,
                       objects->next->size) != 1)
        objects = objects->next;

    if (objects->next == &end) {
        Node *newObject = node_new();
        object_setName(newObject, syntaxTokensFlow.current->symbols, syntaxTokensFlow.current->length);
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

    object_setName(&end, syntaxTokensFlow.current->symbols, syntaxTokensFlow.current->length);
    while (true) {

        object = objects->next;

        while (namesEquals(object->name, object->size, syntaxTokensFlow.current->symbols, syntaxTokensFlow.current->length) != 1) {
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
    object_setName(&end, syntaxTokensFlow.current->symbols, syntaxTokensFlow.size);
    while (namesEquals(list.name, list.size, syntaxTokensFlow.current->symbols, syntaxTokensFlow.current->length) != 1) {
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

struct Item expression(struct Item item1);

struct Item selector(struct Item item) {
    while ((syntaxTokensFlow.current->type == terminalSymbols.LBRAK.type) &&
           (syntaxTokensFlow.current->type == terminalSymbols.PERIOD.type)) {
        if (syntaxTokensFlow.current->type == terminalSymbols.LBRAK.type) {
            tf_next(&syntaxTokensFlow);
            struct Item exp = expression(item);

            if (exp.type->form == ARRAY)
                Index(item, exp);
            else
                printf("NOT ARR");

            if (syntaxTokensFlow.current->type == terminalSymbols.RBRAK.type)
                tf_next(&syntaxTokensFlow);
            else
                printf("]");
        } else {
            tf_next(&syntaxTokensFlow);

            if (syntaxTokensFlow.current->type != terminalSymbols.IDENT.type) {
                if (item.type->form == RECORD) {
                    struct Node obj = findField(*item.type->fields);
                    tf_next(&syntaxTokensFlow);
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

    if (syntaxTokensFlow.current->type < terminalSymbols.LPAREN.type) {
        printf("ident?");

        while (syntaxTokensFlow.current->type >= terminalSymbols.LPAREN.type)
            tf_next(&syntaxTokensFlow);
    }

    if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
        object = *find();
        tf_next(&syntaxTokensFlow);
        MakeItem(_factor, object);
        selector(_factor);
    } else if (syntaxTokensFlow.current->type == terminalSymbols.NUMBER.type) {
        _factor = MakeConstltem(_factor, intType, toInt(syntaxTokensFlow.current->symbols, syntaxTokensFlow.current->length));
        tf_next(&syntaxTokensFlow);
    } else if (syntaxTokensFlow.current->type == terminalSymbols.LPAREN.type) {
        tf_next(&syntaxTokensFlow);
        _factor = expression(_factor);
        if (syntaxTokensFlow.current->type == terminalSymbols.RPAREN.type)
            tf_next(&syntaxTokensFlow);
        else
            printf(")?");
    } else if (syntaxTokensFlow.current->type == terminalSymbols.NOT.type) {
        tf_next(&syntaxTokensFlow);
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

    while ((syntaxTokensFlow.current->type >= terminalSymbols.TIMES.type) &&
           (syntaxTokensFlow.current->type <= terminalSymbols.AND.type)) {

        operator = syntaxTokensFlow.current->type;
        tf_next(&syntaxTokensFlow);
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

    if (syntaxTokensFlow.current->type == terminalSymbols.PLUS.type) {
        tf_next(&syntaxTokensFlow);
        item1 = term(item1);
    } else if (syntaxTokensFlow.current->type == terminalSymbols.MINUS.type) {
        tf_next(&syntaxTokensFlow);
        item1 = term(item1);
        Op1(terminalSymbols.MINUS.type, item1);
    } else {
        item1 = term(item1);
    }

    while ((syntaxTokensFlow.current->type >= terminalSymbols.PLUS.type) &&
           (syntaxTokensFlow.current->type <= terminalSymbols.OR.type)) {
        operator = syntaxTokensFlow.current->type;
        tf_next(&syntaxTokensFlow);

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

    if ((syntaxTokensFlow.current->type >= terminalSymbols.EQL.type) &&
        (syntaxTokensFlow.current->type <= terminalSymbols.GTR.type)) {

        operator = syntaxTokensFlow.current->type;
        tf_next(&syntaxTokensFlow);
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
    if (syntaxTokensFlow.current->type == terminalSymbols.LPAREN.type)
        printf(")?");
    expression(item);
    if (syntaxTokensFlow.current->type == terminalSymbols.RPAREN.type)
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

        if (syntaxTokensFlow.current->type < terminalSymbols.IDENT.type) {
            printf("operator?");
            while (syntaxTokensFlow.current->type < terminalSymbols.IDENT.type) {
                tf_next(&syntaxTokensFlow);
            }
        }

        if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
            obj = *find();
            tf_next(&syntaxTokensFlow);
            MakeItem(item1, obj);
            selector(item1);
            if (syntaxTokensFlow.current->type == terminalSymbols.BECOMES.type) {
                tf_next(&syntaxTokensFlow);
                expression(item2);
                Store(item1, item2);
            } else if (syntaxTokensFlow.current->type == terminalSymbols.EQL.type) {
                printf(":=?");
                tf_next(&syntaxTokensFlow);
                expression(item2);
            } else if (item1.mode == PROC) {
                parameter = *obj.dsc;
                if (syntaxTokensFlow.current->type == terminalSymbols.LPAREN.type) {
                    tf_next(&syntaxTokensFlow);
                    if (syntaxTokensFlow.current->type == terminalSymbols.RPAREN.type)
                        tf_next(&syntaxTokensFlow);
                    else {
                        while (true) {
                            if (syntaxTokensFlow.current->type == terminalSymbols.COMMA.type)
                                tf_next(&syntaxTokensFlow);
                            else if (syntaxTokensFlow.current->type == terminalSymbols.RPAREN.type) {
                                tf_next(&syntaxTokensFlow);
                                break;
                            } else if (syntaxTokensFlow.current->type >= terminalSymbols.SEMICOLON.type)
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
        } else if (syntaxTokensFlow.current->type == terminalSymbols.IF.type) {
            tf_next(&syntaxTokensFlow);
            expression(item1);
            CJump(item1);
            if (syntaxTokensFlow.current->type == terminalSymbols.THEN.type)
                tf_next(&syntaxTokensFlow);
            else
                printf("THEN?");
            StatSequence();
            l = 0;
            while (syntaxTokensFlow.current->type == terminalSymbols.ELSEIF.type) {
                tf_next(&syntaxTokensFlow);
                FJump(l);
                FixLink(l);
                expression(item1);
                CJump(item1);
                if (syntaxTokensFlow.current->type == terminalSymbols.THEN.type)
                    tf_next(&syntaxTokensFlow);
                else
                    printf("THEN?");
                StatSequence();
            }
            if (syntaxTokensFlow.current->type == terminalSymbols.ELSE.type) {
                tf_next(&syntaxTokensFlow);
                FJump(l);
                FixLink(item1.a);
                StatSequence();
            } else {
                FixLink(item1.a);
            }
            FixLink(l);
            if (syntaxTokensFlow.current->type == terminalSymbols.END.type)
                tf_next(&syntaxTokensFlow);
            else
                printf("END?");
        } else if (syntaxTokensFlow.current->type == terminalSymbols.WHILE.type) {
            tf_next(&syntaxTokensFlow);
            l = pc;
            expression(item1);
            CJump(item1);
            if (syntaxTokensFlow.current->type == terminalSymbols.DO.type)
                tf_next(&syntaxTokensFlow);
            else
                printf("DO?");
            StatSequence();
            BJump(l);
            FixLink(item1.a);
        }
        if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
            tf_next(&syntaxTokensFlow);
        else if ((syntaxTokensFlow.current->type >= terminalSymbols.SEMICOLON.type) && (syntaxTokensFlow.current->type)
                 || (syntaxTokensFlow.current->type >= terminalSymbols.ARR.type))
            break;
        else
            printf(";?");
    }
};

// identList = ident {, ident};
Node *identList(int class) {

    if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {

        //Add Identifier to parse tree
        Node *firstAdded = addNode(class); //Have to save link for parameter setup later
        tf_next(&syntaxTokensFlow);

        while (syntaxTokensFlow.current->type == terminalSymbols.COMMA.type) {
            tf_next(&syntaxTokensFlow);
            if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
                //If there are any more identifiers add them too
                addNode(class);
                tf_next(&syntaxTokensFlow);
            } else Mark("Identifier?");
        }


        if (syntaxTokensFlow.current->type ==
            terminalSymbols.COLON.type) { // Probably better to move this block it in declarations
            tf_next(&syntaxTokensFlow);
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

    if (syntaxTokensFlow.current->type != terminalSymbols.IDENT.type && syntaxTokensFlow.current->type < terminalSymbols.ARR.type) {

        Mark("тип?");

        do { tf_next(&syntaxTokensFlow); }
        while (!(syntaxTokensFlow.current->type == terminalSymbols.IDENT.type &&
                 syntaxTokensFlow.current->type >= terminalSymbols.ARR.type));
    }

    if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&syntaxTokensFlow);

        if (obj->class == TYP)
            typ = obj->type;
        else
            Mark("Identifiers isn't a type");

    } else if (syntaxTokensFlow.current->type == terminalSymbols.ARR.type) {

        tf_next(&syntaxTokensFlow);
        x = expression(x);

        if ((x.mode != CONST) && (x.a < 0))
            Mark("Array size should be constant and greater than zero");

        if (syntaxTokensFlow.current->type == terminalSymbols.OF.type)
            tf_next(&syntaxTokensFlow);
        else
            Mark("Missing \"OF\" word");

        Type *baseType = type();

        typ = type_new();
        typ->form = terminalSymbols.ARR.type;
        typ->base = baseType;
        typ->len = (int) x.a;
        typ->size = typ->len * baseType->size;

    } else if (syntaxTokensFlow.current->type == terminalSymbols.REC.type) {

        tf_next(&syntaxTokensFlow);

        typ = type_new();
        typ->form = RECORD;
        typ->size = 0;

        openScope();

        while (true) {
            if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {

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

            if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                tf_next(&syntaxTokensFlow);
            else if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type)
                Mark("Missing \";\"");
            else
                break;
        }

        typ->fields = objectsStart.next;
        closeScope();
        if (syntaxTokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&syntaxTokensFlow);
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

    if ((syntaxTokensFlow.current->type < terminalSymbols.CONSTT.type) &&
        (syntaxTokensFlow.current->type != terminalSymbols.END.type)) {

        printf("Declarations?"); // REPLACE

        while ((syntaxTokensFlow.current->type < terminalSymbols.CONSTT.type) ||
               (syntaxTokensFlow.current->type != terminalSymbols.END.type))
            tf_next(&syntaxTokensFlow);
    }

    while (true) {

        if (syntaxTokensFlow.current->type == terminalSymbols.CONSTT.type) { // Proceed CONST declarations if there are any

            tf_next(&syntaxTokensFlow);

            while (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {

                obj = addNode(CONST);

                tf_next(&syntaxTokensFlow);

                if (syntaxTokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&syntaxTokensFlow);
                else
                    printf("=?");

                item = expression(item);

                if (item.mode == CONST) { //CONST expr MUST consist of constants
                    obj->val = item.a;
                    obj->type = item.type;
                } else {
                    printf("not const");
                }

                if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&syntaxTokensFlow);
                else
                    printf(";");
            }
        }

        if (syntaxTokensFlow.current->type == terminalSymbols.INT.type) {

            tf_next(&syntaxTokensFlow);

            while (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {

                obj = addNode(TYP);
                tf_next(&syntaxTokensFlow);

                if (syntaxTokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&syntaxTokensFlow);
                else
                    printf("=?");

                type();

                if (syntaxTokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&syntaxTokensFlow);
                else printf(";?");
            }
        }

        if (syntaxTokensFlow.current->type == terminalSymbols.VAR.type) {
            tf_next(&syntaxTokensFlow);

            while (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {

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


                if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&syntaxTokensFlow);
                else
                    printf(";?");
            }

            if ((syntaxTokensFlow.current->type >= terminalSymbols.CONSTT.type) &&
                (syntaxTokensFlow.current->type <= terminalSymbols.VAR.type))
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

    if (syntaxTokensFlow.current->type == terminalSymbols.VAR.type) {
        tf_next(&syntaxTokensFlow);
        identList(PAR);
    } else
        identList(VARIABLE);

    if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&syntaxTokensFlow);
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

        while (&obj != &end) {
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

    tf_next(&syntaxTokensFlow);

    if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
        procid = syntaxTokensFlow.current->symbols;
        proc = node_new();
        tf_next(&syntaxTokensFlow);
        parblksize = marksize;
        IncLevel(1);
        openScope();
        proc->val = -1;
        if (syntaxTokensFlow.current->type == terminalSymbols.LPAREN.type) {
            tf_next(&syntaxTokensFlow);
            if (syntaxTokensFlow.current->type == terminalSymbols.RPAREN.type)
                tf_next(&syntaxTokensFlow);
            else {
                FPSection(&locblksize, &parblksize);

                while (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
                    tf_next(&syntaxTokensFlow);
                    FPSection(&locblksize, &parblksize);
                }

                if (syntaxTokensFlow.current->type == terminalSymbols.RPAREN.type)
                    tf_next(&syntaxTokensFlow);
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
        if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
            tf_next(&syntaxTokensFlow);

        } else {
            Mark(";?");
        }

        locblksize = 0;
        declarations();
        while (syntaxTokensFlow.current->type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                tf_next(&syntaxTokensFlow);
            else
                Mark(";?");

        }
        proc->val = pc;
        Enter(locblksize);
        if (syntaxTokensFlow.current->type == terminalSymbols.BEGIN.type) {
            tf_next(&syntaxTokensFlow);
            StatSequence();

        }
        if (syntaxTokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&syntaxTokensFlow);
        } else
            Mark("end ?");
        if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
            //TODO
            if (procid != syntaxTokensFlow.current->symbols) {
                Mark("не подходит");
                tf_next(&syntaxTokensFlow);
            }
            Return(parblksize - marksize);
            closeScope();
            IncLevel(-1);

        }
    }

};


// STARTING SYMBOL
void module() {

    char *moduleIdentifier;
// MODULE = MODULE ident; [ImportList] declarations [BEGIN StatementSequence] END ident "."
    if (tf_next(&syntaxTokensFlow)->type == terminalSymbols.MODULE.type) {
        Open();
        openScope();
        if (tf_next(&syntaxTokensFlow)->type == terminalSymbols.IDENT.type) {
            moduleIdentifier = syntaxTokensFlow.current->symbols;

            if (tf_next(&syntaxTokensFlow)->type == terminalSymbols.SEMICOLON.type) {
                tf_next(&syntaxTokensFlow);
            }
        } else {
            Mark(";?");
        }

        varsize += declarations(); // Proceed declarations

        while (syntaxTokensFlow.current->type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (syntaxTokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
                tf_next(&syntaxTokensFlow);
                StatSequence();
            } else
                Mark(";?");
        }

        Header(varsize);
        if (syntaxTokensFlow.current->type == terminalSymbols.BEGIN.type) {
            tf_next(&syntaxTokensFlow);
            StatSequence();
        }
        if (syntaxTokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&syntaxTokensFlow);

        } else
            Mark("End?");
        if (syntaxTokensFlow.current->type == terminalSymbols.IDENT.type) {
            //TODO
            if (moduleIdentifier != syntaxTokensFlow.current->symbols) {
                Mark("не подходит");
            }
            tf_next(&syntaxTokensFlow);

        } else
            Mark("идентефикатор");
        if (syntaxTokensFlow.current->type != terminalSymbols.PERIOD.type) {
            Mark(".?");
        }
        closeScope();

    } else
        Mark("Модуль?");

}
