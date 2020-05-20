/* token types */
#define UNDEF 0 // Initial Value for all entries (will set types for entries as code goes through parser)
#define INT_TYPE 1
#define FLOAT_TYPE 2
#define CHAR_TYPE 3
#define ARRAY_TYPE 4
#define FUNCTION_TYPE 5
#define VOID_TYPE 6

/* operator types */
#define ISEQUAL 0  // Used to check types of assignments and parameters
#define ARITHM_OP 1
#define BOOL_OP 2
#define NOT_OP 3 
#define RELATION_OP 4 
#define EQUAL_OP 5 

// Function Declarations
int get_result_type (int type_1, int type_2, int op_type); /* type check and result type */
void type_error(int type_1, int type_2, int op_type);      /* print type error */