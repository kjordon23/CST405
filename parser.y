%{
#include "symtab.c"
#include "AST.h"
#include "AST.c"
#include "semantics.c"
#include "code_gen.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>	// for time()
#include <unistd.h>	// for sleep()
#define YYDEBUG 1
extern int yylex();
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
// for declarations
sym_entry **names;
int name_count = 0;	// number of declarations on line of tokens

// initializing values for arrays
Value *vals;
int value_count = 0;
void yyerror (const char *s) {
	fprintf(stderr, "There is a parse error at line %i: %s\n", yylineno, s);
}

void add_to_names(sym_entry *entry){
	// first entry
	if(name_count == 0){
		name_count = 1;
		names = (sym_entry **) malloc( 1 * sizeof(sym_entry *));
		names[0] = entry;
	}
	// general case
	else{
		name_count++;
		names = (sym_entry **) realloc(names, name_count * sizeof(sym_entry *));
		names[name_count - 1] = entry;		
	}
}

void add_to_vals(Value val){
	// first entry
	if(value_count == 0){
		value_count = 1;
		vals = (Value *) malloc(1 * sizeof(Value));
		vals[0] = val;
	}
	// general case
	else{
		value_count++;
		vals = (Value *) realloc(vals, value_count * sizeof(Value));
		vals[value_count - 1] = val;
	}
}

extern int yydebug; // Only for debugging purposes

// temp variable for functions
AST_Node_Func_Decl *temp_function;
%}

%start prog

%union {
	Value val;
	sym_entry* symtab_item;
	AST_Node* node;
	int data_type;
	int const_type;
	int array_size;
	Param parameter;
}

%token <val> INT_T CHAR_T VOID_T FLOAT_T
%token <symtab_item> ID
%token <val> PLUS MINUS TIMES DIVIDE
%token <val> SEMICOLON LEFTBRAC RIGHTBRAC EQUAL LEFTCURLY RIGHTCURLY COMMA LEFTPAREN RIGHTPAREN
%token <val> EXCLAMCOND ANDCOND ORCOND LTCOND GTCOND LTECOND GTECOND NOTEQUAL EQCOND
%token <val> WRITELN_T WRITE_T WHILE_T IF_T ELSE_T RETURN_T BREAK_T READ_T
%token <val> NUMBER
%token <val> NUM_FLOAT
%token <val> CHAR_VAL

%precedence NEG

%left COMMA
%right EQUAL
%left ORCOND ANDCOND NOTEQUA EQCOND
%left LTCOND LTECOND GTCOND GTECOND
%left PLUS MINUS TIMES DIVIDE
%right EXCLAMCOND
%left LEFTPAREN RIGHTPAREN LEFTCURLY RIGHTCURLY


%type <node> prog VarDecList VarDecl FuncDecl FuncDecList FuncDecListOptional FuncType ParamDecList ParamDecListTail Block
%type <node> stmtList stmt readStatement decisionStatement whileStatement writeStatement ElseStatement
%type <node> Expr Const funcCall funcCallParam funcCallParams assign var_ref
%type <parameter> ParamDecl
%type <array_size> array
%type <symtab_item> var initVar
%type <data_type> Type


%%

prog:
    VarDecList { ast_traversal($1); } stmtList { ast_traversal($3); } FuncDecListOptional { ast_traversal($5); } 
;

/* Handling all Variable Declarations and initializations */

VarDecList:
	VarDecList VarDecl {
		AST_Node_Declarations *temp = (AST_Node_Declarations*) $1;
		$$ = new_declarations_node(temp->declarations, temp->declaration_count, $2);
	}
| 	VarDecl {
		$$ = new_declarations_node(NULL, 0, $1);
	}
| /* empty */	{$$ = NULL;}
;

VarDecl:
	Type {declare = 1;} decNames {declare = 0;} SEMICOLON
	{
		if ($1 == VOID_TYPE) {
			yyerror("Void is not a correct variable type");
			exit(1);
		}

		$$ = new_ast_decl_node($1, names, name_count);
		name_count = 0;

		AST_Node_Decl *tempDec = (AST_Node_Decl* ) $$;

		// declare the types of the variables being declared
		for (int i = 0; i < tempDec->names_count; i++) {
			if (tempDec->names[i]->sym_type == UNDEF) {
				set_type(tempDec->names[i]->name, tempDec->data_type, UNDEF);
			}
			else if (tempDec->names[i]->sym_type == ARRAY_TYPE) {
				set_type(tempDec->names[i]->name, ARRAY_TYPE, tempDec->data_type);
			}
		}
	}
;

decNames:
	decNames COMMA var {add_to_names($3);}
|	decNames COMMA initVar {add_to_names($3);}
|	var	{add_to_names($1);}
|	initVar {add_to_names($1);}
;

var:
	ID 
	{
		$$ = $1;
	}
|	ID array 
	{
		if (declare == 1) 
		{
			$1->sym_type = ARRAY_TYPE;
			$1->array_size = $2;
			$1->vals = NULL;
			$$ = $1;
		}
	}
;

array:
	LEFTBRAC Expr RIGHTBRAC 
	{
		// Syntax error if the declaration contains an expression
		if (declare == 1) {
			yyerror("Array cannot contain an expression\nExiting Program\n");
			exit(1);
		}
	}
|	LEFTBRAC NUMBER RIGHTBRAC
	{
		// Pass in the size from the number token
		$$ = $2.ival;
	}
;

initVar:
	ID EQUAL Const
	{
		AST_Node_Const *tempCons = (AST_Node_Const*) $3;
		$1->val = tempCons->val;
		$1->sym_type = tempCons->const_type;
		$$ = $1;
	}
|	ID array EQUAL LEFTCURLY values RIGHTCURLY
	{
		if ($2 != value_count) {
			fprintf(stderr, "Semantic Error at line %d: Initialized Array does not contain the right amount of values", yylineno);
			exit(1);
		}
		$1->sym_type = ARRAY_TYPE;
		$1->array_size = $2;
		$1->vals = vals;
		$$ = $1;
		value_count = 0;
	}
;

values:
	values COMMA Const
	{
		AST_Node_Const *temp = (AST_Node_Const*) $3;
		add_to_vals(temp->val);
	}
|	Const 
	{
		AST_Node_Const *temp = (AST_Node_Const*) $1;
		add_to_vals(temp->val);
	}
;

Type:
    INT_T {$$ = INT_TYPE;}
|   CHAR_T {$$ = CHAR_TYPE;}
|	FLOAT_T {$$ = FLOAT_TYPE;}
|	VOID_T {$$ = VOID_TYPE;}
;

/* Statement Handling and Calls to Functions */

stmtList:
	stmt 
	{
		$$ = new_statements_node(NULL, 0, $1);
	}
|	stmtList stmt 
	{
		AST_Node_Statements *tempState = (AST_Node_Statements*) $1;
		$$ = new_statements_node(tempState->statements, tempState->statement_count, $2);
	}
|	/* empty */	{$$ = NULL;}
;

stmt:
    assign SEMICOLON { $$ = $1; }
|	readStatement { $$ = $1; }
|	writeStatement { $$ = $1; }
|	whileStatement { $$ = $1; }
|	decisionStatement { $$ = $1; }
|	BREAK_T SEMICOLON {$$ = new_ast_simple_node(1);}
|	funcCall SEMICOLON { $$ = $1; }
|	Block { $$ = $1; }
;

readStatement:
	READ_T LEFTPAREN var RIGHTPAREN SEMICOLON { $$ = new_ast_read_node($3, $3->val); }
;

writeStatement:
	WRITE_T LEFTPAREN var RIGHTPAREN SEMICOLON { $$ = new_ast_write_node($3);}
|	WRITELN_T SEMICOLON { $$ = new_ast_writeln_node(); }
;

whileStatement:
	WHILE_T LEFTPAREN Expr RIGHTPAREN Block 
	{ 
		$$ = new_ast_while_node($3, $5);
		if ($3->type == BOOL_NODE || $3->type == REL_NODE || $3->type == EQU_NODE) {
			printf("{Optimization Opportunity (Loop Unrolling)} Loop Unrolling can occur at line %d, which means that we can repeat the block of code inside if statement until the condition has been met\n", yylineno);
		}
	}
	
	
;

decisionStatement:
	IF_T LEFTPAREN Expr RIGHTPAREN Block ElseStatement 
	{
		$$ = new_ast_if_node($3, $5, $6);
	}
;

ElseStatement:
	ELSE_T Block {$$ = $2;}
|	/*empty*/ {$$ = NULL;}
;

Block:
     LEFTCURLY stmtList RIGHTCURLY { $$ = $2; }
;

Expr:
	Expr PLUS Expr 
	{ 
		$$ = new_ast_arithm_node(ADD_OP, $1, $3);
		if ($3->type == CONST_NODE) {
			if (((AST_Node_Const*)$3)->val.ival == 0 || ((AST_Node_Const*)$3)->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only adding by 0\n", yylineno);
			}
		} 
        else if ($1->type == CONST_NODE) {
			if (((AST_Node_Const*)$1)->val.ival == 0 || ((AST_Node_Const*)$1)->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only adding by 0\n", yylineno);
			}
		}
        if ($1->type == CONST_NODE && $3->type == CONST_NODE){
            printf("{Optimization Opportunity (Constant Folding)} You can perform the arithmetic on line %d insde the semantic analyzer, and then you would only have to pass in a constant node without having to generate code for the arithmetic.\n", yylineno);
        }
	}
|	Expr MINUS Expr 
	{ 
		$$ = new_ast_arithm_node(SUB_OP, $1, $3); 
		if ($3->type == CONST_NODE) {
			if (((AST_Node_Const*)$3)->val.ival == 0 || ((AST_Node_Const*)$3)->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only subtracting by 0\n", yylineno);
			}
		} 
        else if ($1->type == CONST_NODE) {
			if (((AST_Node_Const*)$1)->val.ival == 0 || ((AST_Node_Const*)$1)->val.fval == 0) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only subtracting by 0\n", yylineno);
			}
		}
        if ($1->type == CONST_NODE && $3->type == CONST_NODE){
            printf("{Optimization Opportunity (Constant Folding)} You can perform the arithmetic on line %d insde the semantic analyzer, and then you would only have to pass in a constant node without having to generate code for the arithmetic.\n", yylineno);
        }
	}
|	Expr TIMES Expr 
	{ 
		$$ = new_ast_arithm_node(MUL_OP, $1, $3);
		if ($3->type == CONST_NODE) {
			if (((AST_Node_Const*)$3)->val.ival == 1 || ((AST_Node_Const*)$3)->val.fval == 1) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only multiplying by 1\n", yylineno);
			}
            else if (((AST_Node_Const*)$3)->val.ival > 1) {
				printf("{Optimization Opportunity (Strength Reduction)} At line %d, You can add the multiplier %d times to eliminate operations that have a heavy cost.\n", yylineno, ((AST_Node_Const*)$3)->val.ival);
			}
		} 
        else if ($1->type == CONST_NODE) {
			if (((AST_Node_Const*)$1)->val.ival == 1 || ((AST_Node_Const*)$1)->val.fval == 1) {
				printf("{Optimization Opportunity (Algebraic Simplification)} There is no need to generate code for the addition at line %d since you are only multiplying by 1\n", yylineno);
			}
            else if (((AST_Node_Const*)$3)->val.ival > 1) {
				printf("{Optimization Opportunity (Strength Reduction)} At line %d, You can add the multiplier %d times to eliminate operations that have a heavy cost.\n", yylineno, ((AST_Node_Const*)$3)->val.ival);
			}
		} 
        if ($1->type == CONST_NODE && $3->type == CONST_NODE){
            printf("{Optimization Opportunity (Constant Folding)} You can perform the arithmetic on line %d insde the semantic analyzer, and then you would only have to pass in a constant node without having to generate code for the arithmetic.\n", yylineno);
        }
	}
|	Expr DIVIDE Expr { $$ = new_ast_arithm_node(DIV_OP, $1, $3); }
|	Expr EQCOND Expr { $$ = new_ast_equ_node(EQUAL_COND, $1, $3); }
|	Expr NOTEQUAL Expr { $$ = new_ast_equ_node(NOT_EQUAL_COND, $1, $3); }
|	Expr ORCOND Expr { $$ = new_ast_bool_node(OR_COND, $1, $3); }
|	Expr ANDCOND Expr { $$ = new_ast_bool_node(AND_COND, $1, $3); }
|	EXCLAMCOND Expr { $$ = new_ast_bool_node(NOT_COND, $2, NULL); }
|	Expr LTCOND Expr { $$ = new_ast_rel_node(LESS_COND, $1, $3); }
|	Expr GTCOND Expr { $$ = new_ast_rel_node(GREATER_COND, $1, $3); }
|	Expr LTECOND Expr { $$ = new_ast_rel_node(LESS_EQUAL_COND, $1, $3); }
|	Expr GTECOND Expr { $$ = new_ast_rel_node(GREATER_EQUAL_COND, $1, $3); }
|	LEFTPAREN Expr RIGHTPAREN { $$ = $2; }
|	var_ref { $$ = $1; }
|	Const	{ $$ = $1; }
|	MINUS Const %prec NEG
	{
		AST_Node_Const *tempConst = (AST_Node_Const*) $2;
		switch(tempConst->const_type) {
			case INT_TYPE:
				tempConst->val.ival *= -1;
				break;
			case FLOAT_T:
				tempConst->val.fval *= -1;
				break;
			case CHAR_TYPE:
				yyerror("Error having a negative sign in front of a char variable");
				exit(1);
				break;
		}

		$$ = (AST_Node *) tempConst;
	}
|	funcCall
	{
		$$ = $1;
	}
;

assign:
	var_ref EQUAL Expr
	{
		AST_Node_Ref *tempRef = (AST_Node_Ref*) $1;
		$$ = new_ast_assign_node(tempRef->entry, $3);
		// Optimization Here, Redundant Expression elimination, Get rid of when we have expression equal to each other
		if ($1->type == REF_NODE && $3->type == REF_NODE) {
			if (((AST_Node_Ref*)$1)->entry->name == ((AST_Node_Ref*)$3)->entry->name) {
				printf("{Optimization Opportunity (Redundant Expressions)} Entries is the same on both sides of the equal in line %d, which means it can be ignored when in the code generation stage\n", yylineno);
			}
		}	
		/* find datatypes */
		int type1 = get_type(tempRef->entry->name);
		int type2 = expression_data_type($3);

		/* the last function will give us information about revisits */

		/* contains revisit => add assignment-check to revisit queue */
		if(cont_revisit == 1){	
			/* search if entry exists */
			revisit_queue *q = search_queue(tempRef->entry->name);
			if(q == NULL){
				add_to_queue(tempRef->entry, tempRef->entry->name, ASSIGN_CHECK);
				q = search_queue(tempRef->entry->name);	
			}

			/* setup structures */
			if(q->num_of_assigns == 0){ /* first node */
				q->nodes = (void**) malloc(sizeof(void*));
			}
			else{ /* general case */
				q->nodes = (void**) realloc(q->nodes, (q->num_of_assigns + 1) * sizeof(void*));
			}

			/* add info of assignment */
			q->nodes[q->num_of_assigns] = (void*) $3;

			/* increment number of assignments */
			q->num_of_assigns++;

			/* reset revisit flag */
			cont_revisit = 0;

			printf("Assignment revisit for %s at line %d\n", tempRef->entry->name, yylineno);
		}
		else{ /* no revisit */
			/* check assignment semantics */
			get_result_type(
				type1,       /*  variable datatype  */
				type2,       /* expression datatype */
				ISEQUAL  /* checking compatibility only (no operator) */
			);
		}
	}
;

var_ref:
	var
	{
		// Even though it is still shown in symbol table, compiler will not execute code if entry not declared with type
		if ($1->sym_type == NULL) {
			fprintf(stderr, "Semantic Error at line %d: Variable %s has not been declared yet.\nExiting Program\n", yylineno, $1->name); 
			exit(1);
		}
		$$ = new_ast_ref_node($1);
	}
;

funcCall:
	ID LEFTPAREN funcCallParams RIGHTPAREN
	{
		AST_Node_Call_Params *tempParams = (AST_Node_Call_Params*) $3;
		$$ = new_ast_func_call_node($1, tempParams->params, tempParams->num_of_pars);

		revisit_queue *q = search_queue($1->name);
		if (q != NULL){
			/* setup structures */
			if(q->num_of_calls == 0){ /* first call */
				q->par_types = (int**) malloc(sizeof(int*));
				q->num_of_pars = (int*) malloc(sizeof(int));
			}
			else { /* general case */
				q->par_types = (int**) realloc(q->par_types, (q->num_of_calls + 1) * sizeof(int*));
				q->num_of_pars = (int*) realloc(q->num_of_pars, (q->num_of_calls + 1) * sizeof(int));
			}
		
			/* add info of function call */
			q->num_of_pars[q->num_of_calls] = tempParams->num_of_pars;
			q->par_types[q->num_of_calls] = (int*) malloc(tempParams->num_of_pars * sizeof(int));
			/* get the types of the parameters */
			for(int i = 0; i < tempParams->num_of_pars; i++){
				/* get datatype of parameter-expression */
				q->par_types[q->num_of_calls][i] = expression_data_type(tempParams->params[i]);
			}
		
			/* increment number of calls */
			q->num_of_calls++;
		}
		else{
			/* function declared before call */
			if($1->sym_type == FUNCTION_TYPE){
				/* check number of parameters */
				if($1->num_of_pars != tempParams->num_of_pars){
					fprintf(stderr, "Function call of %s has wrong num of parameters!\n", $1->name);
					exit(1);
				}
				/* check if parameters are compatible */
				for(int i = 0; i < tempParams->num_of_pars; i++){
					/* type of parameter in function declaration */
					int type_1 = expression_data_type(tempParams->params[i]);
				
					/* type of parameter in function call*/
					int type_2 = $1->parameters[i].par_type;
				
					/* check compatibility for function call */
					get_result_type(type_1, type_2, ISEQUAL);
					/* error occurs automatically in the function */
				}
			}
		}
	}
;

funcCallParams:

	funcCallParam
	{
		$$ = $1;
	}
|	/* empty */
	{
		AST_Node_Call_Params *tempParams = malloc (sizeof (AST_Node_Call_Params));
		tempParams->type = CALL_PARAMS;
		tempParams->params = NULL;
		tempParams->num_of_pars = 0;
		$$ = (AST_Node*)tempParams;
	}
;

funcCallParam:
	funcCallParam COMMA Expr
	{
		AST_Node_Call_Params *tempParams = (AST_Node_Call_Params*) $1;
		$$ = new_ast_call_params_node(tempParams->params, tempParams->num_of_pars, $3);
	}
|	Expr
	{
		$$ = new_ast_call_params_node(NULL, 0, $1);
	}
;

/* Function Declarations */

FuncDecListOptional:
	FuncDecList
	{
		$$ = $1;
	}
|	/* empty */ 
	{
		$$ = NULL;
	}
;

FuncDecList:
	FuncDecList FuncDecl 
	{
		AST_Node_Func_Declarations *tempFunc = (AST_Node_Func_Declarations*) $1;
		$$ = new_func_declarations_node(tempFunc->func_declarations, tempFunc->func_declaration_count, $2);
	}
|	FuncDecl 
	{
		$$ = new_func_declarations_node(NULL, 0, $1);
	}
;

FuncDecl:
	{incr_scope();} FuncDeclHead FuncDeclTail 
	{
		revisit(temp_function->entry->name);

		hide_scope();
		$$ = (AST_Node *) temp_function;
	}
;

FuncDeclHead:
	{declare_func = 1;} FuncType ID LEFTPAREN
	{
		// Optimization Here, Dead Code Elimination
		if (lookup_func_call($3->name) == NULL) {
			printf("{Optimization Opportunity (Dead Code Elimination)} No function call for method '%s' at line %d, will eliminate code for entire function in code generation\n", $3->name, yylineno);
		}
		declare_func = 0;
		AST_Node_Ret_Type *tempRet = (AST_Node_Ret_Type *) $2;
		temp_function = (AST_Node_Func_Decl *) new_ast_func_decl_node (tempRet->ret_type, $3);
		temp_function->entry->sym_type = FUNCTION_TYPE;
		temp_function->entry->inf_type = tempRet->ret_type;
	}
	ParamDecList RIGHTPAREN
	{
		if ($6 != NULL) {
			AST_Node_Decl_Params *tempParams = (AST_Node_Decl_Params *) $6;

			temp_function->entry->parameters = tempParams->parameters;
			temp_function->entry->num_of_pars = tempParams->num_of_pars;
		}
		else {
			temp_function->entry->parameters = NULL;
			temp_function->entry->num_of_pars = 0;
		}
	}
;

FuncType:
	Type { $$ = new_ast_ret_type_node($1); }
;

ParamDecList:
	ParamDecListTail { $$ = $1;}
|	VOID_T { $$ = NULL; }
|	/* epsilon */ { $$ = NULL;}

;

ParamDecListTail:
	ParamDecListTail COMMA ParamDecl 
	{
		AST_Node_Decl_Params *tempParams = (AST_Node_Decl_Params *) $1;
		$$ = new_ast_decl_params_node(tempParams->parameters, tempParams->num_of_pars, $3);
	}
|	ParamDecl 
	{
		$$ = new_ast_decl_params_node(NULL, 0, $1);
	}
;

ParamDecl:
	{ declare = 1; } Type var
	{
		declare = 0;

		// Setting the type of the parameter
		if ($3->sym_type == UNDEF) {
			set_type($3->name, $2, UNDEF);
		}
		else if ($3->sym_type == ARRAY_TYPE) {
			set_type($3->name, ARRAY_TYPE, $2);
		}

		// Defining the parameter that is passed
		$$ = def_param($2, $3->name);
	}
;

FuncDeclTail:
	LEFTCURLY FuncVarDecs FuncStatements FuncReturn RIGHTCURLY { /* Used to recognize rule in bison */}
;

FuncVarDecs:
	VarDecList
	{
		temp_function->declarations = $1;
	}
;

FuncStatements:
	stmtList
	{
		temp_function->statements = $1;
	}
;

FuncReturn:
	RETURN_T Expr SEMICOLON
	{
		temp_function->return_node = new_ast_return_node(temp_function->ret_type, $2);
	}
|	/* empty */
	{
		temp_function->return_node = NULL;
	}
;


Const:
	NUMBER { $$ = new_ast_const_node(INT_TYPE, $1); }
|	NUM_FLOAT { $$ = new_ast_const_node(FLOAT_TYPE, $1); }
|	CHAR_VAL { $$ = new_ast_const_node(CHAR_TYPE, $1); }
|	MINUS Const %prec NEG
	{
		AST_Node_Const *tempConst = (AST_Node_Const*) $2;
		switch(tempConst->const_type) {
			case INT_TYPE:
				tempConst->val.ival *= -1;
				break;
			case FLOAT_T:
				tempConst->val.fval *= -1;
				break;
			case CHAR_TYPE:
				yyerror("Error having a negative sign in front of a char variable");
				exit(1);
				break;
		}

		$$ = (AST_Node *) tempConst;
	}
;

%%

int main(int argc, char **argv)
{
	/*#if YYDEBUG		// Only for debugging purposes
	yydebug = 1;
	#endif*/
	time_t begin  = time(NULL);
	init_hash_table();
	yyin = fopen("text.gcupl", "r");
	printf("Lexical Analysis Done\n\nParse Tree Initiated\n\n");
	yyparse();	// Handles all of the parsing for each of the rules defined
	fclose(yyin);
	printf("\nSyntax Analysis Done\n");
	
	/* perform the semantic checks (assignments) */
	if(queue != NULL){
		revisit_queue *cur;
		cur = queue;
		while(cur != NULL){
			if(cur->revisit_type == ASSIGN_CHECK){
				revisit(cur->name);
			}
			cur = cur->next;
		}
	}
	yyout = fopen("symbolTable.txt", "w");
	if (yyout == NULL) {
		printf("Empty File");
	}
	symtab_dump(yyout);
	fclose(yyout);
	// revisit queue dump
	yyout = fopen("revisit_dump.out", "w");
	if (yyout == NULL) {
		printf("Empty File");
	}
	revisit_dump(yyout);
	/* if still not empty -> Warning */
	if(queue != NULL){
		printf("Warning: Something has not been checked in the revisit queue!\n");
	}
	fclose(yyout);
	generate_code();
	sleep(3);
	time_t end = time(NULL);
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Time elasped is %f seconds\n", time_spent);
	return 0;
}