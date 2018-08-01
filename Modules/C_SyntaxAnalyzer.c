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

long varsize;

Node *objectsStart;
Node *universe;
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

        for (int i = 0; i < size1; ++i)
            if (name1[i] != name2[i])
                return 0;

        return 1;

    } else
        return 0;
}

//Добавление нового узла в objectStart
Node *addNode(int class) {

    Node *objects = objectsStart;

    end.name = lexTokensFlow.current->symbols;
    end.nameLength = lexTokensFlow.current->length;


    while (namesEquals(lexTokensFlow.current->symbols, lexTokensFlow.current->length, objects->next->name,
                       objects->next->nameLength) != 1)
        objects = objects->next;

    if (objects->next == &end) {
        Node *newObject = node_new();
        node_setName(newObject, lexTokensFlow.current->symbols, lexTokensFlow.current->length);
        newObject->class = class;
        newObject->next = &end;
        objects->next = newObject;
        return newObject;
    } else {
        Mark("declared again");
        return objects->next;
    }

};
//Поиск объекта в objectStart
Node *find() {

    Node *objects = objectsStart;
    Node *object;

    node_setName(&end, lexTokensFlow.current->symbols, lexTokensFlow.current->length);

    while (true) {

        object = objects->next;

        while (namesEquals(object->name, object->nameLength, lexTokensFlow.current->symbols,
                           lexTokensFlow.current->length) !=
               1) {
            object = object->next;
        }

        if (object != &end) {
            return object;
        }

        if (objects == universe) {
            Mark("Not declared");
            return object;
        }

        objects = objects->dsc;
    }
}

Node *findField(Node *list) {
    node_setName(&end, lexTokensFlow.current->symbols, lexTokensFlow.size);
    while (namesEquals(list->name, list->nameLength, lexTokensFlow.current->symbols, lexTokensFlow.current->length) !=
           1) {
        list = list->next;
    }
    return list;
}

bool isParam(Node *obj) {
    //CHANGE
    return (obj->class == PAR) || (obj->class == VARIABLE) && (obj->val > 0);
}

void openScope() {
    Node *s = node_new();
    s->class = HEAD;
    s->dsc = objectsStart;
    s->next = &end;
    objectsStart = s;
}

void closeScope() {
    objectsStart = objectsStart->dsc;
}

static enter(int class, long value, char *name, int size, Type *type) {
    Node *node = node_new();
    node->class = class;
    node->val = value;
    node->type = type;
    node_setName(node, name, size);
    node->next = objectsStart->next;
    objectsStart->next = node;
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


void expression(struct Item *item1);

struct Item selector(struct Item *item) {
    struct Item item2;
    while ((lexTokensFlow.current->type == terminalSymbols.LBRAK.type) ||
           (lexTokensFlow.current->type == terminalSymbols.PERIOD.type)) {
        if (lexTokensFlow.current->type == terminalSymbols.LBRAK.type) {
            tf_next(&lexTokensFlow);
            expression(&item2);

            if (item->type->form == ARRAY)
                Index(item, &item2);
            else
                Mark("NOT ARR");

            if (lexTokensFlow.current->type == terminalSymbols.RBRAK.type)
                tf_next(&lexTokensFlow);
            else
                Mark("]");
        } else {
            tf_next(&lexTokensFlow);

            if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
                if (item->type->form == RECORD) {
                    Node *obj = findField(item->type->fields);
                    tf_next(&lexTokensFlow);
                    if (obj != &end) {
                        Field(item, obj);
                    } else {
                        Mark("not defined");
                    }
                } else
                    Mark("not record");
            } else {
                Mark("ident?");
            }
        }
    }
}

// factor = ident selector | integer | ( expression ) | ~ factor

factor(struct Item *_factor) {

    Node *node;

    if (lexTokensFlow.current->type < terminalSymbols.LPAREN.type) {
        Mark("ident?");

        while (lexTokensFlow.current->type >= terminalSymbols.LPAREN.type)
            tf_next(&lexTokensFlow);
    }

    if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
        node = find();
        tf_next(&lexTokensFlow);
        MakeItem(_factor, node);
        selector(_factor);
    } else if (lexTokensFlow.current->type == terminalSymbols.NUMBER.type) {
        MakeConstltem(_factor, &intType,
                      toInt(lexTokensFlow.current->symbols, lexTokensFlow.current->length));
        tf_next(&lexTokensFlow);
    } else if (lexTokensFlow.current->type == terminalSymbols.LPAREN.type) {
        tf_next(&lexTokensFlow);
        expression(_factor);
        if (lexTokensFlow.current->type == terminalSymbols.RPAREN.type)
            tf_next(&lexTokensFlow);
        else
            Mark(")?");
    } else if (lexTokensFlow.current->type == terminalSymbols.NOT.type) {
        tf_next(&lexTokensFlow);
        factor(_factor);
        Op1(terminalSymbols.NOT.type, _factor);
    } else {
        Mark("factor?");
        MakeItem(_factor, &end);
    }
}


// term = factor {(* | DIV | MOD | &) factor}
void term(struct Item *item) {
    int operator;

    struct Item item2;

    factor(item); // Proceed factor

    while ((lexTokensFlow.current->type >= terminalSymbols.TIMES.type) &&
           (lexTokensFlow.current->type <= terminalSymbols.AND.type)) {

        operator = lexTokensFlow.current->type;
        tf_next(&lexTokensFlow);
        if (operator == terminalSymbols.AND.type)
            Op1(operator, item);
        factor(&item2);
        Op2(operator, item, &item2);
    }
}

void simpleExpression(struct Item *item1) {

    struct Item item2;

    int operator;

    if (lexTokensFlow.current->type == terminalSymbols.PLUS.type) {
        tf_next(&lexTokensFlow);
        term(item1);
    } else if (lexTokensFlow.current->type == terminalSymbols.MINUS.type) {
        tf_next(&lexTokensFlow);
        term(item1);
        Op1(terminalSymbols.MINUS.type, item1);
    } else {
        term(item1);
    }

    while ((lexTokensFlow.current->type >= terminalSymbols.PLUS.type) &&
           (lexTokensFlow.current->type <= terminalSymbols.OR.type)) {
        operator = lexTokensFlow.current->type;
        tf_next(&lexTokensFlow);

        if (operator == terminalSymbols.OR.type) {
            Op1(operator, item1);
        }
        term(&item2);
        Op2(operator, item1, &item2);
    }
}

//expression = SimpleExpression [relation SimpleExpression]

void expression(struct Item *item1) {

    struct Item item2;
    int operator;

    simpleExpression(item1); //Proceed SimpleExpression

    if ((lexTokensFlow.current->type >= terminalSymbols.EQL.type) &&
        (lexTokensFlow.current->type <= terminalSymbols.GTR.type)) {

        operator = lexTokensFlow.current->type;
        tf_next(&lexTokensFlow);
        simpleExpression(&item2);
        Relation(operator, item1, &item2);
    }
}

struct Item parameter(Node *framePointer) {
    struct Item item;
    expression(&item);

    if (isParam(framePointer)) {
        Parameter(&item, framePointer->type, framePointer->class);
        framePointer = framePointer->next;
    } else {
        item.mode = NULL;
        Mark("too many arguments");
    }
}

struct Item param(struct Item item) {
    if (lexTokensFlow.current->type == terminalSymbols.LPAREN.type)
        Mark(")?");
    expression(&item);
    if (lexTokensFlow.current->type == terminalSymbols.RPAREN.type)
        Mark(")?");
    return item;
}

void StatSequence() {
    Node *par;
    Node *node;
    struct Item item1;
    struct Item item2;
    long l;

    while (true) {
        node = &end;

        if (lexTokensFlow.current->type < terminalSymbols.IDENT.type) {
            Mark("operator?");
            do {
                tf_next(&lexTokensFlow);
            } while (lexTokensFlow.current->type < terminalSymbols.IDENT.type);
        }

        if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
            node = find();
            tf_next(&lexTokensFlow);
            MakeItem(&item1, node);
            selector(&item1);
            if (lexTokensFlow.current->type == terminalSymbols.BECOMES.type) {
                tf_next(&lexTokensFlow);
                expression(&item2);
                Store(&item1, &item2);
            } else if (lexTokensFlow.current->type == terminalSymbols.EQL.type) {
                Mark("Did you mean :=?");
                tf_next(&lexTokensFlow);
                expression(&item2);
            } else if (item1.mode == PROC) {
                par = node->dsc;
                if (lexTokensFlow.current->type == terminalSymbols.LPAREN.type) {
                    tf_next(&lexTokensFlow);
                    if (lexTokensFlow.current->type == terminalSymbols.RPAREN.type)
                        tf_next(&lexTokensFlow);
                    else {
                        while (true) {
                            parameter(par);

                            if (item1.mode != NULL) {
                                par = par->next;
                            }

                            if (lexTokensFlow.current->type == terminalSymbols.COMMA.type)
                                tf_next(&lexTokensFlow);
                            else if (lexTokensFlow.current->type == terminalSymbols.RPAREN.type) {
                                tf_next(&lexTokensFlow);
                                break;
                            } else if (lexTokensFlow.current->type >= terminalSymbols.SEMICOLON.type)
                                break;
                            else
                                Mark(") or ,?");
                        }
                    }
                }

                if (node->val < 0) {
                    Mark("straightforward call");
                } else if (~isParam(par)) {
                    Call(&item1);
                } else {
                    Mark("too many arguments");
                }
            } else if (item1.mode == S_PROC) {
                if (node->val <= 3);
                item2 = param(item2);
                IOCall(&item1, &item2);
            } else if (node->class == TYP) {
                Mark("wrong operator");
            } else {
                Mark("operator");
            }
        } else if (lexTokensFlow.current->type == terminalSymbols.IF.type) {
            tf_next(&lexTokensFlow);
            expression(&item1);
            CJump(&item1);
            if (lexTokensFlow.current->type == terminalSymbols.THEN.type)
                tf_next(&lexTokensFlow);
            else
                Mark("THEN?");
            StatSequence();
            l = 0;
            while (lexTokensFlow.current->type == terminalSymbols.ELSEIF.type) {
                tf_next(&lexTokensFlow);
                FJump(&l);
                FixLink(item1.a);
                expression(&item1);
                CJump(&item1);
                if (lexTokensFlow.current->type == terminalSymbols.THEN.type)
                    tf_next(&lexTokensFlow);
                else
                    Mark("THEN?");
                StatSequence();
            }
            if (lexTokensFlow.current->type == terminalSymbols.ELSE.type) {
                tf_next(&lexTokensFlow);
                FJump(&l);
                FixLink(item1.a);
                StatSequence();
            } else {
                FixLink(item1.a);
            }
            FixLink(item1.a);
            if (lexTokensFlow.current->type == terminalSymbols.END.type)
                tf_next(&lexTokensFlow);
            else
                Mark("END?");
        } else if (lexTokensFlow.current->type == terminalSymbols.WHILE.type) {
            tf_next(&lexTokensFlow);
            l = pc;
            expression(&item1);
            CJump(&item1);
            if (lexTokensFlow.current->type == terminalSymbols.DO.type)
                tf_next(&lexTokensFlow);
            else
                Mark("DO?");
            StatSequence();
            BJump(l);
            FixLink(item1.a);
        }
        if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
            tf_next(&lexTokensFlow);
        else if ((lexTokensFlow.current->type >= terminalSymbols.SEMICOLON.type) && (lexTokensFlow.current->type)
                 || (lexTokensFlow.current->type >= terminalSymbols.ARR.type))
            break;
        else
            Mark(";?");
    }
};

// identList = ident {, ident};
//Идентификация переменных одного типа
Node *identList(int class) {

    if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {

        //Add Identifier to parse tree
        Node *firstAdded = addNode(class); //Have to save link for parameter setup later
        tf_next(&lexTokensFlow);

        while (lexTokensFlow.current->type == terminalSymbols.COMMA.type) {
            tf_next(&lexTokensFlow);
            if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
                //If there are any more identifiers add them too
                addNode(class);
                tf_next(&lexTokensFlow);
            } else Mark("Identifier?");
        }


        if (lexTokensFlow.current->type ==
            terminalSymbols.COLON.type) { // Probably better to move this block it in declarations
            tf_next(&lexTokensFlow);
        } else
            Mark("Missing \":\"");

        return firstAdded;
    }
}
//Определение типа объекта
Type *type() {

    Node *obj;
    struct Item x;
    Type *tp;
    Type *typ = &intType;

    if (lexTokensFlow.current->type != terminalSymbols.IDENT.type &&
        lexTokensFlow.current->type < terminalSymbols.ARR.type) {

        Mark("type?");

        do { tf_next(&lexTokensFlow); }
        while (!(lexTokensFlow.current->type == terminalSymbols.IDENT.type &&
                 lexTokensFlow.current->type >= terminalSymbols.ARR.type));
    }

    if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&lexTokensFlow);

        if (obj->class == TYP)
            typ = obj->type;
        else
            Mark("Identifiers isn't a type");

    } else if (lexTokensFlow.current->type == terminalSymbols.ARR.type) {

        tf_next(&lexTokensFlow);
        expression(&x);

        if ((x.mode != CONST) && (x.a < 0))
            Mark("Array length should be constant and greater than zero");

        if (lexTokensFlow.current->type == terminalSymbols.OF.type)
            tf_next(&lexTokensFlow);
        else
            Mark("Missing \"OF\" word");

        Type *baseType = type();

        typ = type_new();
        typ->form = terminalSymbols.ARR.type;
        typ->base = baseType;
        typ->len = (int) x.a;
        typ->size = typ->len * baseType->size;

    } else if (lexTokensFlow.current->type == terminalSymbols.REC.type) {

        tf_next(&lexTokensFlow);

        typ = type_new();
        typ->form = RECORD;
        typ->size = 0;

        openScope();

        while (true) {
            if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {

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

            if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                tf_next(&lexTokensFlow);
            else if (lexTokensFlow.current->type == terminalSymbols.IDENT.type)
                Mark("Missing \";\"");
            else
                break;
        }

        typ->fields = objectsStart->next;
        closeScope();
        if (lexTokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&lexTokensFlow);
        } else
            Mark("Missing \"END\"");
    } else
        Mark("Identifier expected");

    return typ;
}

// declarations = ["CONST" {ident = expression ;}] [TYPE {ident = type;}] [VAR = {IdentList : type ;}] {ProcedureDeclarations;}
// ORDER SENSITIVE
long declarations(long *varsize) {

    Node *firstAdded;
    Node *obj;
    struct Item item;


    if ((lexTokensFlow.current->type < terminalSymbols.CONSTT.type) &&
        (lexTokensFlow.current->type != terminalSymbols.END.type)) {

        Mark("Declarations?"); // REPLACE

        while ((lexTokensFlow.current->type < terminalSymbols.CONSTT.type) ||
               (lexTokensFlow.current->type != terminalSymbols.END.type))
            tf_next(&lexTokensFlow);
    }

    while (true) {

        if (lexTokensFlow.current->type == terminalSymbols.CONSTT.type) { // Proceed CONST declarations if there are any

            tf_next(&lexTokensFlow);

            while (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {

                obj = addNode(CONST);

                tf_next(&lexTokensFlow);

                if (lexTokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&lexTokensFlow);
                else
                    Mark("=?");

                expression(&item);

                if (item.mode == CONST) { //CONST expr MUST consist of constants
                    obj->val = item.a;
                    obj->type = item.type;
                } else {
                    Mark("not const");
                }

                if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&lexTokensFlow);
                else
                    Mark(";");
            }
        }

        if (lexTokensFlow.current->type == terminalSymbols.TYPE.type) {

            tf_next(&lexTokensFlow);

            while (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {

                obj = addNode(TYP);
                tf_next(&lexTokensFlow);

                if (lexTokensFlow.current->type == terminalSymbols.EQL.type)
                    tf_next(&lexTokensFlow);
                else
                    Mark("=?");

                obj->type = type();

                if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&lexTokensFlow);
                else Mark(";?");
            }
        }

        if (lexTokensFlow.current->type == terminalSymbols.VAR.type) {
            tf_next(&lexTokensFlow);

            while (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {

                firstAdded = identList(VARIABLE);
                Type *tp = type(); // Proceed type identification
                obj = firstAdded;

                while (obj != &end) {
                    obj->type = tp;
                    obj->level = curlev;
                    *varsize = *varsize + obj->type->size;
                    obj->val = -(*varsize);
                    obj = obj->next;
                }


                if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                    tf_next(&lexTokensFlow);
                else
                    Mark(";?");
            }
        }


        if ((lexTokensFlow.current->type >= terminalSymbols.CONSTT.type) &&
            (lexTokensFlow.current->type <= terminalSymbols.VAR.type))
            Mark("Declaration?");
        else
            break;

    }
};

//
void FPSection(long *parblksize) {
    Node *obj, *firstAdded;
    Type *tp;
    long parsize;

    if (lexTokensFlow.current->type == terminalSymbols.VAR.type) {
        tf_next(&lexTokensFlow);
        firstAdded = identList(PAR);
    } else
        firstAdded = identList(VARIABLE);

    if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&lexTokensFlow);
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

    if (firstAdded->class == VARIABLE) {
        parsize = tp->size;
        if (tp->form >= ARRAY) {
            Mark("not parameter");
        } else {
            parsize = WordSize;
        }
    }

    obj = firstAdded;

    while (obj != &end) {
        obj->type = tp;
        *parblksize += parsize;
        obj = obj->next;
    }

}

//procedureDeclaration = ProcedureHeading; ProcedureBody ident;
// ProcedureHeading = PROCEDURE ident [FormalParameters];
//
void procedureDeclaration() {
    int const marksize = 8;
    Node *procedure, *obj;
    char *procedureIdentifier;
    int procedureIdentifierLength;
    long locblksize = 0;//
    long parblksize = 0;//

    tf_next(&lexTokensFlow);

    if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
        procedureIdentifier = lexTokensFlow.current->symbols;
        procedureIdentifierLength = lexTokensFlow.current->length;
        procedure = addNode(PROC);
        tf_next(&lexTokensFlow);
        parblksize = marksize;
        IncLevel(1);
        openScope();
        procedure->val = -1;

        if (lexTokensFlow.current->type == terminalSymbols.LPAREN.type) {

            tf_next(&lexTokensFlow);

            if (lexTokensFlow.current->type == terminalSymbols.RPAREN.type)
                tf_next(&lexTokensFlow);
            else {

                FPSection(&parblksize);

                while (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
                    tf_next(&lexTokensFlow);
                    FPSection(&parblksize);
                }

                if (lexTokensFlow.current->type == terminalSymbols.RPAREN.type)
                    tf_next(&lexTokensFlow);
                else
                    Mark(")?");
            }
        } else if (curlev == 1) {
            obj = obj->next;
            EnterCMD(procedureIdentifier, procedureIdentifierLength);
        }

        obj = objectsStart->next;
        locblksize = parblksize;
        while (obj != &end) {
            obj->level = curlev;
            if (obj->class == PAR)
                locblksize -= WordSize;
            else {
                obj->val = locblksize;
            }
            obj = obj->next;
        }

        procedure->dsc = objectsStart->next;

        if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
            tf_next(&lexTokensFlow);

        } else {
            Mark(";?");
        }

        declarations(&locblksize);

        while (lexTokensFlow.current->type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type)
                tf_next(&lexTokensFlow);
            else
                Mark(";?");

        }

        procedure->val = pc;
        Enter(locblksize);

        if (lexTokensFlow.current->type == terminalSymbols.BEGIN.type) {
            tf_next(&lexTokensFlow);
            StatSequence();
        }

        if (lexTokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&lexTokensFlow);
        } else
            Mark("Missing \"END\" word");

        if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {

            if (!(namesEquals(procedureIdentifier, procedureIdentifierLength, lexTokensFlow.current->symbols,
                              lexTokensFlow.current->length))) {
                Mark("Name doesn't match");

            }

            tf_next(&lexTokensFlow);
            Return(parblksize - marksize);
            closeScope();
            IncLevel(-1);

        }
    }

};


void moduleWithoutCloseScope() {

    char *moduleIdentifier;
    int moduleIdentifierLength;

    if (tf_next(&lexTokensFlow)->type == terminalSymbols.MODULE.type) {
        scope_initialise();
        Open();
        openScope();
        if (tf_next(&lexTokensFlow)->type == terminalSymbols.IDENT.type) {
            moduleIdentifier = lexTokensFlow.current->symbols;
            moduleIdentifierLength = lexTokensFlow.current->length;

            if (tf_next(&lexTokensFlow)->type == terminalSymbols.SEMICOLON.type) {
                tf_next(&lexTokensFlow);
            }
        } else {
            Mark(";?");
        }


        declarations(&varsize); // Proceed declarations

        while (lexTokensFlow.current->type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (lexTokensFlow.current->type == terminalSymbols.SEMICOLON.type) {
                tf_next(&lexTokensFlow);
            } else
                Mark(";?");
        }

        Header(varsize);
        if (lexTokensFlow.current->type == terminalSymbols.BEGIN.type) {
            tf_next(&lexTokensFlow);
            StatSequence();
        }
        if (lexTokensFlow.current->type == terminalSymbols.END.type) {
            tf_next(&lexTokensFlow);

        } else
            Mark("End?");
        if (lexTokensFlow.current->type == terminalSymbols.IDENT.type) {
            if (namesEquals(moduleIdentifier, moduleIdentifierLength, lexTokensFlow.current->symbols,
                            lexTokensFlow.current->length) != 1) {
                Mark("Name doesn't match");
            }
            tf_next(&lexTokensFlow);
        } else
            Mark("Identifier");
        if (lexTokensFlow.current->type != terminalSymbols.PERIOD.type) {
            Mark(".?");
        }

    } else
        Mark("Module?");
}

// STARTING SYMBOL
// MODULE = MODULE ident; [ImportList] declarations [BEGIN StatementSequence] END ident "."
void module() {

    moduleWithoutCloseScope();
    closeScope();
}







