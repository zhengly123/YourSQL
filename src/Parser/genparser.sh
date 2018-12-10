flex lex.l
bison -d yacc.y
mv lex.yy.c lex.yy.cpp
mv yacc.tab.c yacc.tab.cpp