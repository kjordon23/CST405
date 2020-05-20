/* ---------------------NODE TYPES-------------------------- */

typedef enum Node_Type {
	BASIC_NODE,   
	DECLARATIONS, 
	DECL_NODE,
	CONST_NODE,
	STATEMENTS, 
	IF_NODE,
	WHILE_NODE,
	ASSIGN_NODE,
	SIMPLE_NODE,
	FUNC_CALL,
	CALL_PARAMS,
	ARITHM_NODE,
	BOOL_NODE,
	REL_NODE,
	EQU_NODE,
	FUNC_DECLS,
	FUNC_DECL,
	RET_TYPE,     // function return type
	DECL_PARAMS,  // function parameters
	RETURN_NODE,  // return statement of functions
	REF_NODE,	  // variable reference
	READ_NODE,
	WRITE_NODE,
	WRITELN_NODE
}Node_Type;

/* --------------------OPERATOR TYPES----------------------- */

typedef enum Arithm_op{
	ADD_OP,  // + operator
	SUB_OP,  // - operator
	MUL_OP,  // * operator
	DIV_OP , // / operator
}Arithm_op;

typedef enum Bool_op{
	OR_COND,  // || operator
	AND_COND, // && operator
	NOT_COND  // ! operator
}Bool_op;

typedef enum Rel_op{
	GREATER_COND,        // > operator
	LESS_COND,           // < operator
	GREATER_EQUAL_COND,  // >= operator
	LESS_EQUAL_COND     // <= operator
}Rel_op;

typedef enum Equ_op{
	EQUAL_COND,    // == operator
	NOT_EQUAL_COND // != operator
}Equ_op;

/* -----------------------AST NODES------------------------- */

/* The basic node */
typedef struct AST_Node{
	enum Node_Type type; // node type
	struct AST_Node *left;  // left child
	struct AST_Node *right; // right child
}AST_Node;

/* Declarations */
typedef struct AST_Node_Declarations{
	enum Node_Type type; // node type
	
	// declarations
	struct AST_Node **declarations;
	int declaration_count;
}AST_Node_Declarations;

typedef struct AST_Node_Decl{
	enum Node_Type type; // node type
	
	// data type
	int data_type;
	
	// symbol table entries of the variables
	sym_entry **names;
	int names_count;
}AST_Node_Decl;

typedef struct AST_Node_Const{
	enum Node_Type type; // node type
	
	// data type
	int const_type;
	
	// constant value
	Value val;
}AST_Node_Const;

/* Statements */
typedef struct AST_Node_Statements{
	enum Node_Type type; // node type
	
	// statements
	struct AST_Node **statements;
	int statement_count;
}AST_Node_Statements;

typedef struct AST_Node_If{
	enum Node_Type type; // node type
	
	// condition
	struct AST_Node *condition;
	
	// if branch
	struct AST_Node *if_branch;
	
	// else branch
	struct AST_Node *else_branch;
}AST_Node_If;

typedef struct AST_Node_While{
	enum Node_Type type; // node type
	
	// condition
	struct AST_Node *condition;
	
	// branch
	struct AST_Node *while_branch;
}AST_Node_While;

typedef struct AST_Node_Assign{
	enum Node_Type type; // node type
	
	// symbol table entry
	sym_entry *entry;
	
	// assignment value
	struct AST_Node *assign_val;
}AST_Node_Assign;

typedef struct AST_Node_Simple{
	enum Node_Type type; // node type
	
	//break: '1'
	int statement_type;
}AST_Node_Simple;

typedef struct AST_Node_Func_Call{
	enum Node_Type type; // node type
	
	// function identifier
	sym_entry *entry;
	
	// call parameters
	AST_Node **params;
	int num_of_pars;
}AST_Node_Func_Call;

typedef struct AST_Node_Call_Params{
	enum Node_Type type; // node type
	
	// call parameters
	AST_Node **params;
	int num_of_pars;
}AST_Node_Call_Params;

/* Expressions */
typedef struct AST_Node_Arithm{
	enum Node_Type type; // node type

	// data type of result
	int data_type;
	
	// operator
	enum Arithm_op op;
	
	struct AST_Node *left;  // left child
	struct AST_Node *right; // right child
}AST_Node_Arithm;

typedef struct AST_Node_Bool{
	enum Node_Type type; // node type

	// data type of result
	int data_type;
	
	// operator
	enum Bool_op op;
	
	struct AST_Node *left;  // left child
	struct AST_Node *right; // right child
}AST_Node_Bool;

typedef struct AST_Node_Rel{
	enum Node_Type type; // node type

	// data type of result
	int data_type;
	
	// operator
	enum Rel_op op;
	
	struct AST_Node *left;  // left child
	struct AST_Node *right; // right child
}AST_Node_Rel;

typedef struct AST_Node_Equ{
	enum Node_Type type; // node type

	// data type of result
	int data_type;
	
	// operator
	enum Equ_op op;
	
	struct AST_Node *left;  // left child
	struct AST_Node *right; // right child
}AST_Node_Equ;

typedef struct AST_Node_Ref{
	enum Node_Type type; // node type
	
	// symbol table entry
	sym_entry *entry;
}AST_Node_Ref;

/* Functions */
typedef struct AST_Node_Func_Declarations{
	enum Node_Type type; // node type
	
	// declarations
	struct AST_Node **func_declarations;
	int func_declaration_count;
}AST_Node_Func_Declarations;

typedef struct AST_Node_Func_Decl{
	enum Node_Type type; // node type
	
	// return type
	int ret_type;
	
	// symbol table entry
	sym_entry *entry;
	
	// declarations, statements and return
	struct AST_Node *declarations;
	struct AST_Node *statements;
	struct AST_Node *return_node;
}AST_Node_Func_Decl;

typedef struct AST_Node_Ret_Type{
	enum Node_Type type; // node type
	
	// return type
	int ret_type;
}AST_Node_Ret_Type;

typedef struct AST_Node_Decl_Params{
	enum Node_Type type; // node type
	
	// parameters
	Param *parameters;
	int num_of_pars;
}AST_Node_Decl_Params;

typedef struct AST_Node_Return{
	enum Node_Type type; // node type
	
	// return type
	int ret_type;
	
	// return value
	struct AST_Node *ret_val;
}AST_Node_Return;

typedef struct AST_Node_Write
{
	enum Node_Type type; // node type
	// symbol table entry
	sym_entry *entry;
}AST_Node_Write;

typedef struct AST_Node_WriteLn
{
	enum Node_Type type; // node type

}AST_Node_WriteLn;

typedef struct AST_Node_Read
{
	enum Node_Type type; // node type
	// symbol table entry
	sym_entry *entry;

	Value val;
}AST_Node_Read;

int expression_data_type(AST_Node *node);

/* ------------------AST NODE MANAGEMENT-------------------- */

/* The basic node */
AST_Node *new_ast_node(Node_Type type, AST_Node *left, AST_Node *right); 	 // simple nodes

/* Declarations */
AST_Node *new_declarations_node(AST_Node **declarations, int declaration_count, AST_Node *declaration);
AST_Node *new_ast_decl_node(int data_type, sym_entry **names, int names_count); // declaration
AST_Node *new_ast_const_node(int const_type, Value val);					 // constant

/* Statements */
AST_Node *new_statements_node(AST_Node **statements, int statement_count, AST_Node *statement);
AST_Node *new_ast_if_node(AST_Node *condition, AST_Node *if_branch, AST_Node *else_branch);
AST_Node *new_ast_while_node(AST_Node *condition, AST_Node *while_branch);
AST_Node *new_ast_assign_node(sym_entry *entry, AST_Node *assign_val);
AST_Node *new_ast_simple_node(int statement_type);							 // continue or break
AST_Node *new_ast_func_call_node(sym_entry *entry, AST_Node **params, int num_of_pars); // function call
AST_Node *new_ast_call_params_node(AST_Node **params, int num_of_pars, AST_Node *param);	// function call parameters

/* Expressions */
AST_Node *new_ast_arithm_node(enum Arithm_op op, AST_Node *left, AST_Node *right);	// Arithmetic Node
AST_Node *new_ast_bool_node(enum Bool_op op, AST_Node *left, AST_Node *right);	// Boolean Node
AST_Node *new_ast_rel_node(enum Rel_op op, AST_Node *left, AST_Node *right);	// Relational Node
AST_Node *new_ast_equ_node(enum Equ_op op, AST_Node *left, AST_Node *right);	// Equaity (Equal or not Equal) Node
AST_Node *new_ast_ref_node(sym_entry *entry);

/* Functions */
AST_Node *new_func_declarations_node(AST_Node **func_declarations, int func_declaration_count, AST_Node *func_declaration);
AST_Node *new_ast_func_decl_node(int ret_type, sym_entry *entry);
AST_Node *new_ast_ret_type_node(int ret_type);                  // function return type
AST_Node *new_ast_decl_params_node(Param *parameters, int num_of_pars, Param param);
AST_Node *new_ast_return_node(int ret_type, AST_Node *ret_val);				 // function return
AST_Node *new_ast_read_node(sym_entry *entry, Value val);				 // function read
AST_Node *new_ast_write_node(sym_entry *entry);				 // function write
AST_Node *new_ast_writeln_node();				 // function writeln

/* Tree Traversal */
void ast_print_node(AST_Node *node);	// print information of node
void ast_traversal(AST_Node *node);