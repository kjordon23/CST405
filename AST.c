#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------AST NODE MANAGEMENT-------------------- */

/* 
Steps for all Constructors for each type of AST Node
1. Allocate memory for each type of node
2. Set entries of each node to the parameters of each method
3. Return the created node type-casted to an AST_Node type

*/

int cont_revisit = 0; // 1: contains revisit, 0: not
int lineno = 0;

AST_Node *new_ast_node(Node_Type type, AST_Node *left, AST_Node *right){

	AST_Node *node = malloc (sizeof (AST_Node));
	
	node->type = type;
	node->left = left;
	node->right = right;
	
	return node;
}

/* Declarations */
AST_Node *new_declarations_node(AST_Node **declarations, int declaration_count, AST_Node *declaration){
	
	AST_Node_Declarations *node = malloc (sizeof (AST_Node_Declarations));
	
	node->type = DECLARATIONS;
	
	// if first declaration
	if(declarations == NULL){
		declarations = (AST_Node**) malloc (sizeof (AST_Node*));
		declarations[0] = declaration;
		declaration_count = 1;
	}
	// else, add new declaration
	else{
		declarations = (AST_Node**) realloc (declarations, (declaration_count + 1) * sizeof (AST_Node*));
		declarations[declaration_count] = declaration;
		declaration_count++;
	}
	
	node->declarations = declarations;
	node->declaration_count = declaration_count;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_decl_node(int data_type, sym_entry **names, int names_count){

	AST_Node_Decl *node = malloc (sizeof (AST_Node_Decl));
	

	node->type = DECL_NODE;
	node->data_type = data_type;
	node->names = names;
	node->names_count = names_count;

	return (struct AST_Node *) node;
}
AST_Node *new_ast_const_node(int const_type, Value val){

	AST_Node_Const *node = malloc (sizeof (AST_Node_Const));
	

	node->type = CONST_NODE;
	node->const_type = const_type;
	node->val = val;
	

	return (struct AST_Node *) node;
}

/* Statements */

AST_Node *new_statements_node(AST_Node **statements, int statement_count, AST_Node *statement){

	AST_Node_Statements *node = malloc (sizeof (AST_Node_Statements));
	

	node->type = STATEMENTS;
	
	// if first statement
	if(statements == NULL){
		statements = (AST_Node**) malloc (sizeof (AST_Node*));
		statements[0] = statement;
		statement_count = 1;
	}
	// else, add new statement
	else{
		statements = (AST_Node**) realloc (statements, (statement_count + 1) * sizeof (AST_Node*));
		statements[statement_count] = statement;
		statement_count++;
	}
	
	node->statements = statements;
	node->statement_count = statement_count;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node *else_branch){
	
	AST_Node_If *node = malloc (sizeof (AST_Node_If));
	
	node->type = IF_NODE;
	node->condition = condition;
	node->if_branch = if_branch;
	node->else_branch = else_branch;
	

	return (struct AST_Node *) node;
}

AST_Node *new_ast_while_node(AST_Node *condition, AST_Node *while_branch){

	AST_Node_While *node = malloc (sizeof (AST_Node_While));
	
	node->type = WHILE_NODE;
	node->condition = condition;
	node->while_branch = while_branch;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_assign_node(sym_entry *entry, AST_Node *assign_val){

	AST_Node_Assign *node = malloc (sizeof (AST_Node_Assign));
	
	node->type = ASSIGN_NODE;
	node->entry = entry;
	node->assign_val = assign_val;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_simple_node(int statement_type){

	AST_Node_Simple *node = malloc (sizeof (AST_Node_Simple));
	
	node->type = SIMPLE_NODE;
	node->statement_type = statement_type;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_func_call_node(sym_entry *entry, AST_Node **params, int num_of_pars){

	AST_Node_Func_Call *node = malloc (sizeof (AST_Node_Func_Call));
	
	node->type = FUNC_CALL;
	node->entry = entry;
	node->params = params;
	node->num_of_pars = num_of_pars;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_call_params_node(AST_Node **params, int num_of_pars, AST_Node *param){

	AST_Node_Call_Params *node = malloc (sizeof (AST_Node_Call_Params));
	
	node->type = CALL_PARAMS;
	
	// first parameter
	if(params == NULL){
		params = (AST_Node**) malloc (sizeof (AST_Node*));
		params[0] = param;
		num_of_pars = 1;
	}
	// add new parameter
	else{
		params = (AST_Node**) realloc (params, (num_of_pars + 1) * sizeof (AST_Node*));
		params[num_of_pars] = param;
		num_of_pars++;
	}
	
	node->params = params;
	node->num_of_pars = num_of_pars;
	
	return (struct AST_Node *) node;
}

/* Expressions */

AST_Node *new_ast_arithm_node(enum Arithm_op op, AST_Node *left, AST_Node *right){

	AST_Node_Arithm *node = malloc (sizeof (AST_Node_Arithm));
	
	node->type = ARITHM_NODE;
	node->op = op;
	node->left = left;
	node->right = right;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_bool_node(enum Bool_op op, AST_Node *left, AST_Node *right){

	AST_Node_Bool *node = malloc (sizeof (AST_Node_Bool));
	
	node->type = BOOL_NODE;
	node->op = op;
	node->left = left;
	node->right = right;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_rel_node(enum Rel_op op, AST_Node *left, AST_Node *right){

	AST_Node_Rel *node = malloc (sizeof (AST_Node_Rel));
	
	node->type = REL_NODE;
	node->op = op;
	node->left = left;
	node->right = right;

	return (struct AST_Node *) node;
}

AST_Node *new_ast_equ_node(enum Equ_op op, AST_Node *left, AST_Node *right){

	AST_Node_Equ *node = malloc (sizeof (AST_Node_Equ));
	
	node->type = EQU_NODE;
	node->op = op;
	node->left = left;
	node->right = right;
	
	return (struct AST_Node *) node;	
}

AST_Node *new_ast_ref_node(sym_entry *entry){

	AST_Node_Ref *node = malloc (sizeof (AST_Node_Ref));
	
	node->type = REF_NODE;
	node->entry = entry;
	
	return (struct AST_Node *) node;	
}

/* Functions */
AST_Node *new_func_declarations_node(AST_Node **func_declarations, int func_declaration_count, AST_Node *func_declaration){

	AST_Node_Func_Declarations *node = malloc (sizeof (AST_Node_Func_Declarations));
	

	node->type = FUNC_DECLS;
	
	// first declaration
	if(func_declarations == NULL){
		func_declarations = (AST_Node**) malloc (sizeof (AST_Node*));
		func_declarations[0] = func_declaration;
		func_declaration_count = 1;
	}
	// add new declaration
	else{
		func_declarations = (AST_Node**) realloc (func_declarations, (func_declaration_count + 1) * sizeof (AST_Node*));
		func_declarations[func_declaration_count] = func_declaration;
		func_declaration_count++;
	}
	
	node->func_declarations = func_declarations;
	node->func_declaration_count = func_declaration_count;	

	return (struct AST_Node *) node;
}

AST_Node *new_ast_func_decl_node(int ret_type, sym_entry *entry){

	AST_Node_Func_Decl *node = malloc (sizeof (AST_Node_Func_Decl));
	

	node->type = FUNC_DECL;
	node->ret_type = ret_type;
	node->entry = entry;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_ret_type_node(int ret_type){

	AST_Node_Ret_Type *node = malloc (sizeof (AST_Node_Ret_Type));
	

	node->type = RET_TYPE;
	node->ret_type = ret_type;	

	return (struct AST_Node *) node;
}

AST_Node *new_ast_decl_params_node(Param *parameters, int num_of_pars, Param param){

	AST_Node_Decl_Params *node = malloc (sizeof (AST_Node_Decl_Params));
	
	node->type = DECL_PARAMS;
	
	// first declaration
	if(parameters == NULL){
		parameters = (Param*) malloc (sizeof (Param));
		parameters[0] = param;
		num_of_pars = 1;
	}
	// add new declaration
	else{
		parameters = (Param*) realloc (parameters, (num_of_pars + 1) * sizeof (Param));
		parameters[num_of_pars] = param;
		num_of_pars++;
	}
	
	node->parameters = parameters;
	node->num_of_pars = num_of_pars;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_return_node(int ret_type, AST_Node *ret_val){

	AST_Node_Return *node = malloc (sizeof (AST_Node_Return));
	
	node->type = RETURN_NODE;
	node->ret_type = ret_type;
	node->ret_val = ret_val;
	
	return (struct AST_Node *) node;
}

AST_Node *new_ast_read_node(sym_entry *entry, Value val) {
	AST_Node_Read *node = malloc (sizeof (AST_Node_Read));

	node->type = READ_NODE;
	node->entry = entry;
	node->val = val;

	return (struct AST_Node *) node;
}

AST_Node *new_ast_write_node(sym_entry *entry) {
	AST_Node_Write *node = malloc (sizeof (AST_Node_Write));

	node->type = WRITE_NODE;
	node->entry = entry;

	return (struct AST_Node *) node;
}
AST_Node *new_ast_writeln_node() {
	AST_Node_WriteLn *node = malloc (sizeof (AST_Node_WriteLn));

	node->type = WRITELN_NODE;

	return (struct AST_Node *) node;
}

int expression_data_type(AST_Node *node){
	/* temp nodes */
	AST_Node_Arithm *temp_arithm;
	AST_Node_Bool *temp_bool;
	AST_Node_Rel *temp_rel;
	AST_Node_Equ *temp_equ;
	AST_Node_Ref *temp_ref;
	AST_Node_Const *temp_const;
	AST_Node_Func_Call *temp_func_call;
	
	/* return type depends on the AST node type */
	switch(node->type){
		case ARITHM_NODE: /* arithmetic expression */
			temp_arithm = (AST_Node_Arithm *) node;
			
			/* set datatype again */
			temp_arithm->data_type = get_result_type(
				expression_data_type(temp_arithm->left),  /* data type of left expression */
				expression_data_type(temp_arithm->right), /* data type of right expression */
				ARITHM_OP                    /* operation type */
			);
			
			return temp_arithm->data_type; 
			break;
		case BOOL_NODE:   /* boolean expression */
			temp_bool = (AST_Node_Bool *) node;
			
			/* set datatype again */
			if(temp_bool->op != NOT_COND){ /* AND or OR */
				temp_bool->data_type = get_result_type(
					expression_data_type(temp_bool->left),  /* data type of left expression */
					expression_data_type(temp_bool->right), /* data type of right expression */
					BOOL_OP                      /* operation type */
				);	
			}
			else{ /* NOT */
				temp_bool->data_type = get_result_type(
					expression_data_type(temp_bool->left), /* data type of left expression */
					UNDEF,                      /* there is no right expression */
					NOT_OP                      /* operation type */
				);	
			}
			
			return temp_bool->data_type;
			break;
		case REL_NODE:    /* relational expression */
			temp_rel = (AST_Node_Rel *) node;
			
			/* set datatype again */
			temp_rel->data_type = get_result_type(
					expression_data_type(temp_rel->left),  /* data type of left expression  */
					expression_data_type(temp_rel->right), /* data type of right expression */
					RELATION_OP                       /* operation type */
			);
			
			return temp_rel->data_type;
			break;
		case EQU_NODE:    /* equality expression */
			temp_equ = (AST_Node_Equ *) node;
			
			/* set datatype again */
			temp_equ->data_type = get_result_type(
					expression_data_type(temp_equ->left),  /* data type of left expression  */
					expression_data_type(temp_equ->right), /* data type of right expression */
					EQUAL_OP                       /* operation type */
			);
			
			return temp_equ->data_type;
			break;
		case REF_NODE:    /* identifier reference */
			temp_ref = (AST_Node_Ref *) node;
			/* if "simple" type */
			int type = temp_ref->entry->sym_type;
			if(type == INT_TYPE	|| type == FLOAT_TYPE || type == CHAR_TYPE){
				return temp_ref->entry->sym_type;
			}
			/* if array or pointer */
			else{
				return temp_ref->entry->inf_type;
			}
			break;
		case CONST_NODE:  /* constant */
			temp_const = (AST_Node_Const *) node;
			return temp_const->const_type; /* constant data type */
			break;
		case FUNC_CALL:   /* function call */
			temp_func_call = (AST_Node_Func_Call *) node;
			
			/* check if it needs revisit */
			if(temp_func_call->entry->sym_type == UNDEF){
				if(temp_func_call->entry->inf_type == UNDEF){
					cont_revisit = 1;  /* contains revisit */
					return INT_TYPE;   /*   dummy return   */
				}
			}
			
			return temp_func_call->entry->inf_type; /* return type */
			break;
		default: /* wrong choice case */
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
	}
}

/* Steps for creating AST
1. Traverse the Syntax tree at each node created
2. Print the necessary information at each node
 */

void ast_print_node(AST_Node *node){
	/* temporary nodes for each type*/
	AST_Node_Declarations *temp_declarations;
	AST_Node_Decl *temp_decl;
	AST_Node_Const *temp_const;
	AST_Node_Statements *temp_statements;
	AST_Node_If *temp_if;
	AST_Node_Assign *temp_assign;
	AST_Node_Simple *temp_simple;
	AST_Node_Func_Call *temp_func_call;
	AST_Node_Call_Params *temp_call_params;
	AST_Node_Arithm *temp_arithm;
	AST_Node_Bool *temp_bool;
	AST_Node_Rel *temp_rel;
	AST_Node_Equ *temp_equ;
	AST_Node_Ref *temp_ref;
	AST_Node_Func_Declarations *temp_func_declarations;
	AST_Node_Func_Decl *temp_func_decl;
	AST_Node_Ret_Type *temp_ret_type;
	AST_Node_Decl_Params *temp_decl_params;
	AST_Node_Return *temp_return;
	AST_Node_Read *temp_read;
	AST_Node_Write *temp_write;
	AST_Node_WriteLn *temp_writeln;
	
	switch(node->type){
		case BASIC_NODE:
			printf("Basic Node\n");
			break;
		case DECLARATIONS:
			temp_declarations = (struct AST_Node_Declarations *) node;
			printf("Declarations Node with %d declaration(s)\n", temp_declarations->declaration_count);
			break;
		case DECL_NODE:
			temp_decl = (struct AST_Node_Decl *) node;
			printf("Declaration Node of data-type ", temp_decl->data_type, temp_decl->names_count);
			if (temp_decl->data_type == 1) {
				printf("int for %d name(s)\n", temp_decl->names_count);
			}
			else if (temp_decl->data_type == 2) {
				printf("float for %d name(s)\n", temp_decl->names_count);
			}
			else if (temp_decl->data_type == 3) {
				printf("char for %d name(s)\n", temp_decl->names_count);
			}
			break;
		case CONST_NODE:
			temp_const = (struct AST_Node_Const *) node;
			printf("Constant Node of const-type ");
			switch(temp_const->const_type){
				case INT_TYPE:
					printf("int with value %d\n", temp_const->val.ival);
					break;
				case FLOAT_TYPE:
					printf("float with value %.2f\n", temp_const->val.fval);
					break;
				case CHAR_TYPE:
					printf("char with value %c\n",  temp_const->val.cval);
					break;
			}
			break;
		case STATEMENTS:
			temp_statements = (struct AST_Node_Statements *) node;
			printf("Statements Node with %d statement(s)\n", temp_statements->statement_count);
			break;
		case IF_NODE:
			temp_if = (struct AST_Node_If *) node;
			printf("If statement found\n");
			if(temp_if->else_branch == NULL){
				printf("No Else Statement Found\n");
			}
			else{
				printf("Else Statement Found\n");
			}			
			break;
		case WHILE_NODE:
			printf("While Node\n");
			break;
		case ASSIGN_NODE:
			temp_assign = (struct AST_Node_Assign *) node;
			printf("Assign Node of entry %s\n", temp_assign->entry->name);
			if (temp_assign->assign_val->type == CONST_NODE) {
				AST_Node_Const * node = (struct AST_Node_Const *) temp_assign->assign_val;
				temp_assign->entry->val = node->val;
			}
			break;
		case SIMPLE_NODE:
			temp_simple = (struct AST_Node_Simple *) node;
			if (temp_simple->statement_type == 1) {
				printf("Break Statement found\n");
			}
			break;
		case FUNC_CALL:
			temp_func_call = (struct AST_Node_Func_Call *) node;
			temp_func_call->entry->sym_type = FUNCTION_TYPE;
			printf("Function Call Node with %d parameters\n", temp_func_call->num_of_pars);
			break;
		case CALL_PARAMS:
			temp_call_params = (struct AST_Node_Call_Params *) node;
			printf("Function Call Parameters Node with %d parameters\n", temp_call_params->num_of_pars);
		case ARITHM_NODE:
			temp_arithm = (struct AST_Node_Arithm *) node;
			printf("Arithmetic Node of operator ");
			switch(temp_arithm->op) {
				case 0:
					printf("+\n");
					break;
				case 1:
					printf("-\n");
					break;
				case 2:
					printf("*\n");
					break;
				case 3:
					printf("/\n");
					break;
			}
			break;
		case BOOL_NODE:
			temp_bool = (struct AST_Node_Bool *) node;
			printf("Boolean Node of operator ");
			switch(temp_bool->op) {
				case 0:
					printf("||\n");
					break;
				case 1:
					printf("&&\n");
					break;
				case 2:
					printf("!\n");
					break;
			}
			break;
		case REL_NODE:
			temp_rel = (struct AST_Node_Rel *) node;
			printf("Relational Node of operator ");
			switch(temp_rel->op) {
				case 0:
					printf(">\n");
					break;
				case 1:
					printf("<\n");
					break;
				case 2:
					printf(">=\n");
					break;
				case 3:
					printf("<=\n");
					break;
			}
			break;
		case EQU_NODE:
			temp_equ = (struct AST_Node_Equ *) node;
			printf("Equality Node of operator ");
			switch(temp_equ->op) {
				case 0:
					printf("==\n");
					break;
				case 1:
					printf("!=\n");
					break;
			}
			break;
		case REF_NODE:
			temp_ref = (struct AST_Node_Ref *) node;
			printf("Variable Reference Node of entry %s\n", temp_ref->entry->name);
			break;
		case FUNC_DECLS:
			temp_func_declarations = (struct AST_Node_Func_Declarations *) node;
			printf("Function Declarations Node with %d function declaration(s)\n", temp_func_declarations->func_declaration_count);
			break;
		case FUNC_DECL:
			temp_func_decl = (struct AST_Node_Func_Decl *) node;
			printf("Function Declaration Node of %s with ret_type ", temp_func_decl->entry->name);
			if (temp_func_decl->ret_type == 1) {
				printf("int and %d parameters\n", temp_func_decl->entry->num_of_pars);
			}
			else if (temp_func_decl->ret_type == 2) {
				printf("float and %d parameters\n", temp_func_decl->entry->num_of_pars);
			}
			else if (temp_func_decl->ret_type == 3) {
				printf("char and %d parameters\n", temp_func_decl->entry->num_of_pars);
			}
			else if (temp_func_decl->ret_type == 6) {
				printf("void and %d parameters\n", temp_func_decl->entry->num_of_pars);
			}
			break;
		case RET_TYPE:
			temp_ret_type = (struct AST_Node_Ret_Type *) node;
			printf("Return type %d which is ", temp_ret_type->ret_type);
			break;
		case DECL_PARAMS:
			temp_decl_params = (struct AST_Node_Decl_Params *) node;
			printf("Function declaration parameters node of %d parameters\n", temp_decl_params->num_of_pars);
			break;
		case RETURN_NODE:
			temp_return = (struct AST_Node_Return *) node;
			printf("Return Node of ret_type %d\n", temp_return->ret_type);
			break;
		case READ_NODE:
			temp_read = (struct AST_Node_Read *) node;
			printf("Read Node to the variable %s\n", temp_read->entry->name);
			break;
		case WRITE_NODE:
			temp_write = (struct AST_Node_Write *) node;
			printf("Write Node to the variable %s\n", temp_write->entry->name);
			break;
		case WRITELN_NODE:
			temp_writeln = (struct AST_Node_WriteLn *) node;
			printf("Writing New Line\n");
			break;
		default: /* wrong choice case */
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
	}
}

void ast_traversal(AST_Node *node){
	int i;
	
	/* check if empty */
	if(node == NULL){
		return;
	}
	
	/* left and right child cases */
	if(node->type == BASIC_NODE || node->type == ARITHM_NODE || node->type == BOOL_NODE || node->type == REL_NODE || node->type == EQU_NODE){
		ast_print_node(node); // postfix
		generate_mips_code(node);	// Basic Node is Ignored inside method
	}
	/* declarations case */
	else if(node->type == DECLARATIONS){
		AST_Node_Declarations *temp_declarations = (struct AST_Node_Declarations *) node;	
		ast_print_node(node);
		generate_mips_code(node);
		for(i = 0; i < temp_declarations->declaration_count; i++){
			ast_traversal(temp_declarations->declarations[i]);
		}
	}
	/* statements case */
	else if(node->type == STATEMENTS){
		AST_Node_Statements *temp_statements = (struct AST_Node_Statements *) node;	
		ast_print_node(node);	
		for(i = 0; i < temp_statements->statement_count; i++){
			ast_traversal(temp_statements->statements[i]);
		}
	}
	/* the if case */
	else if(node->type == IF_NODE){
		AST_Node_If *temp_if = (struct AST_Node_If *) node;
		ast_print_node(node);
		generate_mips_code(node);	
		printf("Condition:\n");
		ast_traversal(temp_if->condition);
		
		printf("If branch:\n");
		ast_traversal(temp_if->if_branch);
	
		if(temp_if->else_branch != NULL){
			printf("Else branch:\n");
			ast_traversal(temp_if->else_branch);
		}
	}
	/* while case */
	else if(node->type == WHILE_NODE){
		AST_Node_While *temp_while = (struct AST_Node_While *) node;
		ast_print_node(node);
		generate_mips_code(node);
		printf("Condition:\n");
		ast_traversal(temp_while->condition);
		printf("While Branch:\n");
		ast_traversal(temp_while->while_branch);
	}
	/* assign case */
	else if(node->type == ASSIGN_NODE){
		AST_Node_Assign *temp_assign = (struct AST_Node_Assign *) node;
		ast_print_node(node);
		generate_mips_code(node);
		printf("Assigning:\n");
		ast_traversal(temp_assign->assign_val);
	}
	/* function call case */
	else if(node->type == FUNC_CALL){
		AST_Node_Func_Call *temp_func_call = (struct AST_Node_Func_Call *) node;
		ast_print_node(node);
		generate_mips_code(node);
		printf("Call parameters:\n");
		for(i = 0; i < temp_func_call->num_of_pars; i++){
			ast_traversal(temp_func_call->params[i]);
		}
	}
	/* function declarations case */
	else if(node->type == FUNC_DECLS){
		AST_Node_Func_Declarations *temp_func_declarations = (struct AST_Node_Func_Declarations *) node;	
		ast_print_node(node);
		for(i = 0; i < temp_func_declarations->func_declaration_count; i++){
			ast_traversal(temp_func_declarations->func_declarations[i]);
		}
	}
	/* function declaration case */
	else if(node->type == FUNC_DECL){
		AST_Node_Func_Decl *temp_func_decl = (struct AST_Node_Func_Decl *) node;
		ast_print_node(node);
		generate_mips_code(node);
		if(temp_func_decl->entry->num_of_pars != 0){
			printf("Parameters:\n");
			for(i = 0; i < temp_func_decl->entry->num_of_pars; i++){
				printf("Parameter %s of type ", temp_func_decl->entry->parameters[i].param_name);
				if (temp_func_decl->entry->parameters[i].par_type == 1) {
					printf("int\n");
				} else if (temp_func_decl->entry->parameters[i].par_type == 2) {
					printf("float\n");
				} else if (temp_func_decl->entry->parameters[i].par_type == 3) {
					printf("char\n");
				}
			}
		}
		if(temp_func_decl->declarations != NULL){
			printf("Function declarations:\n");
			ast_traversal(temp_func_decl->declarations);
		}
		if(temp_func_decl->statements != NULL){
			printf("Function statements:\n");
			ast_traversal(temp_func_decl->statements);
		}
		if(temp_func_decl->return_node != NULL){
			printf("Return node:\n");
			ast_traversal(temp_func_decl->return_node);
		}
	}
	/* parameter declarations case */
	else if(node->type == DECL_PARAMS){
		AST_Node_Decl_Params *temp_decl_params = (struct AST_Node_Decl_Params *) node;
		ast_print_node(node);
		generate_mips_code(node);
		printf("Call parameters:\n");
		for(i = 0; i < temp_decl_params->num_of_pars; i++){
			printf("Parameter %s of type %d\n", temp_decl_params->parameters[i].param_name, temp_decl_params->parameters[i].par_type);
		}		
	}
	/* return case */
	else if(node->type == RETURN_NODE){
		AST_Node_Return *temp_return = (struct AST_Node_Return *) node;
		ast_print_node(node);
		printf("Returning:\n");
		ast_traversal(temp_return->ret_val);
	}
	/* read case */
	else if(node->type == READ_NODE){
		AST_Node_Read *temp_read = (struct AST_Node_Read *) node;
		ast_print_node(node);
		generate_mips_code(node);
		printf("Reading value to %s\n", temp_read->entry->name);
	}
	/* return case */
	else if(node->type == WRITE_NODE){
		AST_Node_Write *temp_write = (struct AST_Node_Write *) node;
		ast_print_node(node);
		generate_mips_code(node);
		printf("Writing value of %s to console\n", temp_write->entry->name);
	}
	/* return case */
	else if(node->type == WRITELN_NODE){
		AST_Node_WriteLn *temp_writeln = (struct AST_Node_WriteLn *) node;
		ast_print_node(node);
		generate_mips_code(node);
	}
	else if (node->type == SIMPLE_NODE) {
		AST_Node_Simple *temp_simple = (struct AST_Node_Simple *) node;
		ast_print_node(node);
		generate_mips_code(node);
	}
	/* others */
	else{
		ast_print_node(node);
	}
}

void generate_mips_code(AST_Node *node){	// This will be pseudo-mips, meaning we are just printing the output of what the code generator should accomplish for statements, functions and declarations within our program
	/* temporary nodes for each type*/
	AST_Node_Declarations *temp_declarations;
	AST_Node_If *temp_if;
	AST_Node_Assign *temp_assign;
	AST_Node_Simple *temp_simple;
	AST_Node_Func_Call *temp_func_call;
	AST_Node_Call_Params *temp_call_params;
	AST_Node_Func_Declarations *temp_func_declarations;
	AST_Node_Func_Decl *temp_func_decl;
	AST_Node_Read *temp_read;
	AST_Node_Write *temp_write;
	
	switch(node->type){
		case DECLARATIONS:
			temp_declarations = (struct AST_Node_Declarations *) node;
			printf("{Code Generator} Generate Declarations in .data section with all %d declaration(s)\n", temp_declarations->declaration_count);
			break;
		case IF_NODE:
			temp_if = (struct AST_Node_If *) node;
			printf("{Code Generator} Create condition logic for if statement in mips code by using the slt and branch (bne and beq) commands, then create new label for the jump to the if branch and produce mips codes for all statements in if branch\n");
			if(temp_if->else_branch == NULL){
				printf("{Code Generator} Since there is no else statement, proceed to next node in AST\n");
			}
			else{
				printf("{Code Generator} Since there is an else statement, generate mips codes for statements in else branch under condition logic\n");
			}			
			break;
		case WHILE_NODE:
			printf("{Code Generator} Create label for while loop, use branch commands (bge, bgt, ble, blt) to create condition logic in mips, generate code for statements inside loop, and jump back to the beginning of the loop branch if condition has not been met\n");
			break;
		case ASSIGN_NODE:
			temp_assign = (struct AST_Node_Assign *) node;
			printf("{Code Generator} Generate mips code necesary to handle the assignment of %s\n", temp_assign->entry->name);
			break;
		case SIMPLE_NODE:
			temp_simple = (struct AST_Node_Simple *) node;
			if (temp_simple->statement_type == 1) {
				printf("{Code Generator} Generate the mips code to allow the program to jump from the loop when prompted to\n");
			}
			break;
		case FUNC_CALL:
			temp_func_call = (struct AST_Node_Func_Call *) node;
			printf("{Code Generator} Create mips code that will jump to the called function in the statement using the jal keyword and the name of the function\n");
			break;
		case CALL_PARAMS:
			temp_call_params = (struct AST_Node_Call_Params *) node;
			printf("{Code Generator} Create registers and mips code for the parameters of the function before the function call\n");
		case ARITHM_NODE:
			printf("{Code Generator} Generate the mips code for the arithmetic expression\n");
			break;
		case BOOL_NODE:
			printf("{Code Generator} Generate the mips code for the boolean expression shown\n");
			break;
		case REL_NODE:
			printf("{Code Generator} Generate the mips code for the relational expression shown\n");
			break;
		case EQU_NODE:
			printf("{Code Generator} Generate the mips code for the equality expression\n");
		case FUNC_DECL:
			temp_func_decl = (struct AST_Node_Func_Decl *) node;
			printf("{Code Generator} Jump out of the main method and create label for the %s method, start producing mips code for statements involved with this function\n", temp_func_decl->entry->name);
			break;
		case DECL_PARAMS:
			printf("{Code Generator} Use Code Generator to set values to parameters in the declaration to the parameters to the function's call \n");
			break;
		case READ_NODE:
			temp_read = (struct AST_Node_Read *) node;
			printf("{Code Generator} Generate code that will allow the user to store a value to the variable %s\n", temp_read->entry->name);
			break;
		case WRITE_NODE:
			temp_write = (struct AST_Node_Write *) node;
			printf("{Code Generator} Generate code that will display the value of the variable %s to the console\n", temp_write->entry->name);
			break;
		case WRITELN_NODE:
			printf("{Code Generator} Generate code that will display a new line break to the console\n");
			break;
		default: /* wrong choice case */
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
	}
}
