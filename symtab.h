#define SIZE 1500    //Size of the hash table
#define MAXTOKENLEN 40  //Max size for each token passed from lexer

/* how parameter is passed */
#define BY_REFERENCE 0
#define BY_VALUE 1

/* revisit types */
#define PARAM_CHECK 1
#define ASSIGN_CHECK 2

/* Types of values that we can have */
typedef union Value{
	int ival;
	double fval;
	char cval;
	char *sval;
}Value;

/* parameter struct */
typedef struct Param{
	int par_type;
	char param_name[MAXTOKENLEN];
	
	// to store the value
	Value val;
	int passing;
}Param;

/* a linked list of references (lineno's) for each variable */
typedef struct RefList{ 
    int lineno;
    struct RefList *next;
}RefList;

// struct that represents a list node
typedef struct sym_entry{
	// name, size of name, scope and occurrences (lines)
	char name[MAXTOKENLEN];
    int st_size;
    int scope;
    RefList *lines;	// References to line numbers when used
    
	// to store value
	Value val;
	
	// type
    int sym_type;
    
    // for arrays (info type) and for functions (return type)
	int inf_type;
	
	// array stuff
	Value *vals;
	int array_size;
	
	// function parameters
	Param *parameters;
	int num_of_pars;
	
	// pointer to next item in the list
	struct sym_entry *next;
}sym_entry;

typedef struct revisit_queue{
    // symbol table entry
	sym_entry *entry;
	
	// name of identifier
    char *name;
	
    // type of revisit
    int revisit_type;
	
	// parameters of function calls
    int **par_types;
    int *num_of_pars;
    int num_of_calls;
	
	// assignment expression nodes
	void **nodes;
	int num_of_assigns;

    // maybe additional information to simplify the process ...
    struct revisit_queue *next;
	
}revisit_queue;

/* static structures */
static sym_entry **hash_table;
static revisit_queue *queue;


// Symbol Table Functions
void init_hash_table(); // initialize hash table
unsigned int hash(char *key); // hash function 
void insert(char *name, int len, int type, int lineno); // insert entry
sym_entry *lookup(char *name); // search for entry
sym_entry *lookup_func_call(char *name);	// search for the entry of a function call
void symtab_dump(FILE *of); // dump file
void set_type(char *name, int sym_type, int inf_type); // set the type of an entry (declaration)
int get_type(char *name); // get the type of an entry
void hide_scope(); // hide the current scope
void incr_scope(); // go to next scope
Param def_param(int par_type, char *param_name); // define parameter
int declareFunction(char *name, int return_type, int numPars, Param *params);	// Declaring function
int funcParameterCheck(char *name, int num_of_calls, int** par_types, int *num_of_pars);
void add_to_queue(sym_entry *entry, char *name, int type); // add to queue
revisit_queue *search_queue(char *name);
revisit_queue *search_prev_queue(char *name);
int revisit(char *name); // revisit entry by also removing it from queue
void revisit_dump(FILE *of); // dump file
