#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "Structures/B_TerminalSymbols.h"
#include "Structures/A_Tokens.h"
#include "B_LexAnalyzer.h"
#include "Structures/Object.h"
#include "G_CodeGenerator.h"

const int WordSize = 4;

struct Object objectsStart;
struct Object universe;
struct Object end;
struct TokensFlow tokensFlow;

long toInt(char *val) {

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

struct Object addObject(struct Object object, int class) {

    end.name = tokensFlow.current.symbols;
    end.size = tokensFlow.current.size;

    struct Object objects = objectsStart;

    while (namesEquals(tokensFlow.current.symbols, tokensFlow.current.size, objects.name, objects.size) != 1)
        objects = objects.next;

    if (&object.next == &end) {
        struct Object newObject = object_new();
        object_setName(newObject, tokensFlow.current.symbols, tokensFlow.current.size);
        newObject.class = class;
        newObject.next = end;
        objects.next = newObject;
        object = newObject;
    } else {
        object = objects.next;
        printf("declared again");
    }

    return object;
};

struct Object find() {

    struct Object objects = objectsStart;
    struct Object object;

    object_setName(end, tokensFlow.current.symbols, tokensFlow.current.size);
    while (true) {

        object = objects.next;

        while (namesEquals(object.name, object.size, tokensFlow.current.symbols, tokensFlow.current.size) != 1) {
            object = object.next;
        }

        if (&object != &end) {
            return object;
        }

        if (&objects == &universe) {
            printf("Not declared");
            return object;
        }

        objects = objects.dsc;
    }
}

struct Object findField(struct Object list) {
    object_setName(end, tokensFlow.current.symbols, tokensFlow.size);
    while (namesEquals(list.name, list.size, tokensFlow.current.symbols, tokensFlow.current.size) != 1) {
        list = list.next;
    }
    return list;
}

bool isParam(struct Object obj) {
    //CHANGE
    return (obj.class == 2) || (obj.class == 1) && (obj.val > 0);
}

void openScope() {
    struct Object s = object_new();
    s.class = 0;
    s.dsc = objectsStart;
    s.next = end;
    objectsStart = s;
}

void closeScope() {
    objectsStart = objectsStart.dsc;
}

struct Item expression(struct Item item1);

struct Item selector(struct Item item) {
    while ((tokensFlow.current.type == terminalSymbols.LBRAK.type) &&
           (tokensFlow.current.type == terminalSymbols.PERIOD.type)) {
        if (tokensFlow.current.type == terminalSymbols.LBRAK.type) {
            tf_next(&tokensFlow);
            struct Item exp = expression();

            if (exp.type.form == Array)
                Index(item, exp);
            else
                printf("NOT ARRAY");

            if (tokensFlow.current.type == terminalSymbols.RBRAK.type)
                tf_next(&tokensFlow);
            else
                printf("]");
        } else {
            tf_next(&tokensFlow);

            if (tokensFlow.current.type != terminalSymbols.IDENT.type) {
                if (item.type.form == Record) {
                    struct Object obj = findField(item.type.fields);
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

void factor(struct Item item) {

    struct Object object;

    if (tokensFlow.current.type < terminalSymbols.LPAREN.type) {
        printf("ident?");

        while (tokensFlow.current.type >= terminalSymbols.LPAREN.type)
            tf_next(&tokensFlow);
    }

    if (tokensFlow.current.type == terminalSymbols.IDENT.type) {
        object = find();
        tf_next(&tokensFlow);
        MakeItem(item, object);
        selector(item);
    } else if (tokensFlow.current.type == terminalSymbols.NUMBER.type) {
        MakeConstltem(item, intType, toInt(tokensFlow.current.symbols));
        tf_next(&tokensFlow);
    } else if (tokensFlow.current.type == terminalSymbols.LPAREN.type) {
        tf_next(&tokensFlow);
        item = expression();
        if (tokensFlow.current.type == terminalSymbols.RPAREN.type)
            tf_next(&tokensFlow);
        else
            printf(")?");
    } else if (tokensFlow.current.type == terminalSymbols.NOT.type) {
        tf_next(&tokensFlow);
        factor(item);
        Op1(terminalSymbols.NOT.type, item);
    } else {
        printf("Множитель?");
        MakeItem(item, end);
    }

}

void term(struct Item item) {
    int operator;

    struct Item item1;

    while ((tokensFlow.current.type >= terminalSymbols.TIMES.type) &&
           (tokensFlow.current.type <= terminalSymbols.AND.type)) {

        operator = tokensFlow.current.type;
        tf_next(&tokensFlow);
        if (operator == terminalSymbols.AND.type)
            Op1(operator, item);
        factor(item1);
        Op2(operator, item, item1);
    }
}

void simpleExpression(struct Item item1) {

    struct Item item2;

    int operator;

    if (tokensFlow.current.type == terminalSymbols.PLUS.type) {
        tf_next(&tokensFlow);
        term(item1);
    } else if (tokensFlow.current.type == terminalSymbols.MINUS.type) {
        tf_next(&tokensFlow);
        term(item1);
        Op1(terminalSymbols.MINUS.type, item1);
    } else {
        term(item1);
    }

    while ((tokensFlow.current.type >= terminalSymbols.PLUS.type) &&
           (tokensFlow.current.type >= terminalSymbols.OR.type)) {
        operator = tokensFlow.current.type;
        tf_next(&tokensFlow);

        if (operator == terminalSymbols.OR.type) {

        }
        term(item2);
        Op2(operator, item1, item2);
    }
}

struct Item expression(struct Item item1) {

    struct Item item2;
    int operator;
    simpleExpression(item1);

    if ((tokensFlow.current.type >= terminalSymbols.EQL.type) &&
        (tokensFlow.current.type <= terminalSymbols.GTR.type)) {

        operator = tokensFlow.current.type;
        tf_next(&tokensFlow);
        simpleExpression(item2);
        Relation(operator, item1, item2);

    }
}

void parameter(struct Object framePointer) {
    struct Item item;
    expression(item);

    if (isParam(framePointer))
        Parameter(item, framePointer.type, framePointer.class);
    else
        printf("too many arguments");
}

void StatSequence() {
    struct Object parameter;
    struct Object obj;
    struct Item item1;
    struct Item item2;
    long l;

    while (true) {
        obj = end;

        if (tokensFlow.current.type < terminalSymbols.IDENT.type) {
            printf("operator?");
            while (tokensFlow.current.type < terminalSymbols.IDENT.type) {
                tf_next(&tokensFlow);
            }
        }

        if (tokensFlow.current.type == terminalSymbols.IDENT.type) {
            obj = find();
            tf_next(&tokensFlow);
            MakeItem(item1, obj);
            selector(item1);
            if (tokensFlow.current.type == terminalSymbols.BECOMES.type) {
                tf_next(&tokensFlow);
                expression(item2);
                Store(item1, item2);
            } else if (tokensFlow.current.type == terminalSymbols.EQL.type) {
                printf(":=?");
                tf_next(&tokensFlow);
                expression(item2);
            } else if (item1.mode == Proc) {
                parameter = obj.dsc;
                if (tokensFlow.current.type == terminalSymbols.LPAREN.type) {
                    tf_next(&tokensFlow);
                    if (tokensFlow.current.type == terminalSymbols.RPAREN.type)
                        tf_next(&tokensFlow);
                    else {
                        while (true) {
                            if (tokensFlow.current.type == terminalSymbols.COMMA.type)
                                tf_next(&tokensFlow);
                            else if (tokensFlow.current.type == terminalSymbols.RPAREN.type) {
                                tf_next(&tokensFlow);
                                break;
                            } else if (tokensFlow.current.type >= terminalSymbols.SEMICOLON.type)
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
            } else if (item1.mode == SProc) {
                if (obj.val <= 3);
                param(item2);
                IOCall(item1, item2);
            } else if (obj.class == Typ) {
                printf("wrong operator");
            } else {
                printf("operator");
            }
        } else if (tokensFlow.current.type == terminalSymbols.IF.type) {
            tf_next(&tokensFlow);
            expression(item1);
            CJump(item1);
            if (tokensFlow.current.type == terminalSymbols.THEN.type)
                tf_next(&tokensFlow);
            else
                printf("THEN?");
            StatSequence();
            l = 0;
            while (tokensFlow.current.type == terminalSymbols.ELSEIF.type) {
                tf_next(&tokensFlow);
                FJump(l);
                FixLink(l);
                expression(item1);
                CJump(item1);
                if (tokensFlow.current.type == terminalSymbols.THEN.type)
                    tf_next(&tokensFlow);
                else
                    printf("THEN?");
                StatSequence();
            }
            if (tokensFlow.current.type == terminalSymbols.ELSE.type) {
                tf_next(&tokensFlow);
                FJump(l);
                FixLink(item1.a);
                StatSequence();
            } else {
                FixLink(item1.a);
            }
            FixLink(l);
            if (tokensFlow.current.type == terminalSymbols.END.type)
                tf_next(&tokensFlow);
            else
                printf("END?");
        } else if (tokensFlow.current.type == terminalSymbols.WHILE.type) {
            tf_next(&tokensFlow);
            l = pc;
            expression(item1);
            CJump(item1);
            if (tokensFlow.current.type == terminalSymbols.DO.type)
                tf_next(&tokensFlow);
            else
                printf("DO?");
            StatSequence();
            BJump(l);
            FixLink(item1.a);
        }
        if (tokensFlow.current.type == terminalSymbols.SEMICOLON.type)
            tf_next(&tokensFlow);
        else if ((tokensFlow.current.type >= terminalSymbols.SEMICOLON.type) && (tokensFlow.current.type)
                 || (tokensFlow.current.type >= terminalSymbols.ARRAY.type))
            break;
        else
            printf(";?");
    }
};

void param(struct Item item) {
    if (tokensFlow.current.type == terminalSymbols.LPAREN.type)
        printf(")?");
    expression(item);
    if (tokensFlow.current.type == terminalSymbols.RPAREN.type)
        printf(")?");
}

void identList() {

}

void type() {

}

long declarations() {

    struct Object obj, first;
    struct Item item;

    long varsize = 0;

    if ((tokensFlow.current.type < terminalSymbols.CONSTT.type) &&
        (tokensFlow.current.type != terminalSymbols.END.type)) {

        printf("Declarations?"); // REPLACE

        while ((tokensFlow.current.type < terminalSymbols.CONSTT.type) ||
               (tokensFlow.current.type != terminalSymbols.END.type))
            tf_next(&tokensFlow);
    }

    while (true) {

        if (tokensFlow.current.type == terminalSymbols.CONSTT.type) {
            tf_next(&tokensFlow);
            while (tokensFlow.current.type == terminalSymbols.IDENT.type) {
                obj = object_new();

                tf_next(&tokensFlow);

                if (tokensFlow.current.type == terminalSymbols.EQL.type)
                    tf_next(&tokensFlow);
                else
                    printf("=?");

                expression(item);

                if (item.mode == CONST) {
                    obj.val = item.a;
                    obj.type = item.type;
                } else {
                    printf("not const");
                }

                if (tokensFlow.current.type == terminalSymbols.SEMICOLON.type)
                    tf_next(&tokensFlow);
                else
                    printf(";");
            }
        }

        if (tokensFlow.current.type == terminalSymbols.INTEGER.type) {
            tf_next(&tokensFlow);

            while (tokensFlow.current.type == terminalSymbols.IDENT.type) {

                obj = object_new();
                tf_next(&tokensFlow);

                if (tokensFlow.current.type == terminalSymbols.EQL.type)
                    tf_next(&tokensFlow);
                else
                    printf("=?");

                type();

                if (tokensFlow.current.type == terminalSymbols.EQL.type)
                    tf_next(&tokensFlow);
                else printf(";?");
            }
        }

        if (tokensFlow.current.type == terminalSymbols.VAR.type) {
            tf_next(&tokensFlow);

            while (tokensFlow.current.type == terminalSymbols.IDENT.type) {
                identList();
                struct Type tp = type();
                obj = first;
                while (&obj != &end) {
                    obj.type = tp;
                    obj.level = curlev;
                    varsize = varsize + obj.type.size;
                    obj.val = -varsize;
                    obj = obj.next;
                }
            }

            if (tokensFlow.current.type == terminalSymbols.SEMICOLON.type)
                tf_next(&tokensFlow);
            else
                printf(";?");
        }

        if ((tokensFlow.current.type >= terminalSymbols.CONSTT.type) &&
            (tokensFlow.current.type <= terminalSymbols.VAR.type))
            printf("Объявление?");
        else
            break;
    }
}

void FPSection(long* locblksize, long* parblksize) {
    struct Object obj, first;
    struct Type tp;
    long parsize;

    if (tokensFlow.current.type == terminalSymbols.VAR.type) {
        tf_next(&tokensFlow);
        identList();
    } else
        identList();

    if (tokensFlow.current.type == terminalSymbols.IDENT.type) {
        obj = find();
        tf_next(&tokensFlow);
        if (obj.class == Typ)
            tp = obj.type;
        else {
            Mark("ident?");
            tp = intType;
        }
    } else {
        Mark("ident?");
        tp = intType;
    }

    if (first.class == Var) {
        parsize = tp.size;
        if (tp.form >= Array) {
            Mark("not parameter");
        } else {
            parsize = WordSize;
        }
        obj = first;

        while (&obj != &end) {
            obj.type = tp;
            parblksize++;
            parsize++;
            obj = obj.next;
        }
    }
}

void procedureDeclaration() {
    int const marksize = 8;
    struct Object proc, obj;
    char* procid;
    long locblksize, parblksize;

    tf_next(&tokensFlow);

    if (tokensFlow.current.type == terminalSymbols.IDENT.type) {
        procid = tokensFlow.current.symbols;
        proc = object_new();
        tf_next(&tokensFlow);
        parblksize = marksize;
        IncLevel(1);
        openScope();
        proc.val = -1;
        if (tokensFlow.current.type == terminalSymbols.LPAREN.type) {
            tf_next(&tokensFlow);
            if (tokensFlow.current.type == terminalSymbols.RPAREN.type)
                tf_next(&tokensFlow);
            else {
                FPSection(&locblksize, &parblksize);

                while  (tokensFlow.current.type == terminalSymbols.SEMICOLON.type) {
                    tf_next(&tokensFlow);
                    FPSection(&locblksize, &parblksize);
                }

                if (tokensFlow.current.type == terminalSymbols.RPAREN.type)
                    tf_next(&tokensFlow);
                else
                    Mark(")?");
            }
        } else if (curlev == 1) {
            //ENTERCMD
        }
        obj = objectsStart.next;
        locblksize = parblksize;
        while (&obj != &end) {
            obj.level = curlev;

        }
    }
};


void module(struct TokensFlow tokensFlow, struct DeclaredVariables declaredVariables,
            struct TerminalSymbols terminalSymbols) {

    if (tf_next(&tokensFlow).type == terminalSymbols.MODULE.type) {
        if (tf_next(&tokensFlow).type == terminalSymbols.IDENT.type) {
            if (tf_next(&tokensFlow).type == terminalSymbols.SEMICOLON.type) {
                tf_next(&tokensFlow);
            }
        } else {
            printf("ident?");
        }

        declarations(tokensFlow, declaredVariables);

        while (tokensFlow.current.type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (tokensFlow.current.type == terminalSymbols.SEMICOLON.type)
                tf_next(&tokensFlow);
            else
                printf(";?");
        }


    }


}

void compile() {

}