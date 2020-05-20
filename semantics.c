#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"

extern int yylineno;

// actual types are: INT_TYPE, FLOAT_TYPE, CHAR_TYPE

int get_result_type(int type_1, int type_2, int op_type){ /* type check and result type */
	switch(op_type){
		case ISEQUAL: /* type compatibility only, '1': compatible */
			// first type INT
			if(type_1 == INT_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return 1;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type REAL
			else if(type_1 == FLOAT_TYPE){
				// second type INT, REAL or CHAR
				if(type_2 == INT_TYPE || type_2 == FLOAT_TYPE || type_2 == CHAR_TYPE){
					return 1;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type CHAR
			else if(type_1 == CHAR_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return 1;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			break;
		/* ---------------------------------------------------------- */
		case ARITHM_OP: /* arithmetic operator */
			// first type INT
			if(type_1 == INT_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				// second type REAL
				else if(type_2 == FLOAT_TYPE){
					return FLOAT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type REAL
			else if(type_1 == FLOAT_TYPE){
				// second type INT, REAL or CHAR
				if(type_2 == INT_TYPE || type_2 == FLOAT_TYPE || type_2 == CHAR_TYPE){
					return FLOAT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type CHAR
			else if(type_1 == CHAR_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return CHAR_TYPE;
				}
				// second type REAL
				else if(type_2 == FLOAT_TYPE){
					return FLOAT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			else{
				type_error(type_1, type_2, op_type);
			}
			break;
		/* ---------------------------------------------------------- */
		
		/* ---------------------------------------------------------- */
		case BOOL_OP: /* Boolean operator */
			// first type INT
			if(type_1 == INT_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type CHAR
			else if(type_1 == CHAR_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return CHAR_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			else{
				type_error(type_1, type_2, op_type);
			}
			break;
		/* ---------------------------------------------------------- */
		case NOT_OP: /* special case of NOTOP */
			// type INT
			if(type_1 == INT_TYPE){
				return INT_TYPE;
			}
			// type CHAR
			else if(type_1 == CHAR_TYPE){
				return INT_TYPE;
			}
			else{
				type_error(type_1, type_2, op_type);
			}
			break;
		/* ---------------------------------------------------------- */
		case RELATION_OP: /* Relational operator */
			// first type INT
			if(type_1 == INT_TYPE){
				// second type INT, REAL or CHAR
				if(type_2 == INT_TYPE || type_2 == FLOAT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			else if(type_1 == FLOAT_TYPE){
				// second type INT, REAL or CHAR
				if(type_2 == INT_TYPE || type_2 == FLOAT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type CHAR
			else if(type_1 == CHAR_TYPE){
				// second type INT, REAL or CHAR
				if(type_2 == INT_TYPE || type_2 == FLOAT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			else{
				type_error(type_1, type_2, op_type);
			}
			break;
		/* ---------------------------------------------------------- */
		case EQUAL_OP: /* Equality operator */
			// first type INT
			if(type_1 == INT_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			else if(type_1 == FLOAT_TYPE){
				// second type REAL
				if(type_2 == FLOAT_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			// first type CHAR
			else if(type_1 == CHAR_TYPE){
				// second type INT or CHAR
				if(type_2 == INT_TYPE || type_2 == CHAR_TYPE){
					return INT_TYPE;
				}
				else{
					type_error(type_1, type_2, op_type);
				}
			}
			else{
				type_error(type_1, type_2, op_type);
			}
			break;
		/* ---------------------------------------------------------- */
		default: /* wrong choice case */
			fprintf(stderr, "Error in operator selection!\n");
			exit(1);
	}
}

void type_error(int type_1, int type_2, int op_type){ /* print type error */
	fprintf(stderr, "Type conflict between ");
	/* first type */
	if      (type_1 == INT_TYPE)           fprintf(stderr,"%s","int");
	else if (type_1 == FLOAT_TYPE)          fprintf(stderr,"%s","real");
	else if (type_1 == CHAR_TYPE)          fprintf(stderr,"%s","char");
	else                                   fprintf(stderr,"%s","other");
	
	fprintf(stderr, " and ");	
	
	/* second type */
	if      (type_2 == INT_TYPE)           fprintf(stderr,"%s","int");
	else if (type_2 == FLOAT_TYPE)          fprintf(stderr,"%s","real");
	else if (type_2 == CHAR_TYPE)          fprintf(stderr,"%s","char");
	else                                   fprintf(stderr,"%s","other");
	
	/* operator */
	fprintf(stderr," using op type ");
	switch(op_type){
		case ISEQUAL:
			fprintf(stderr,"%s","EQUAL");
			break;
		case ARITHM_OP:
			fprintf(stderr,"%s","ARITHM_OP");
			break;
		
		case BOOL_OP:
			fprintf(stderr,"%s","BOOL_OP");
			break;
		case NOT_OP:
			fprintf(stderr,"%s","NOT_OP");
			break;
		case RELATION_OP:
			fprintf(stderr,"%s","RELATION_OP");
			break;
		case EQUAL_OP:
			fprintf(stderr,"%s","EQUAL_OP");
			break;
		default: 
			fprintf(stderr, "Error in operator selection!\n");
			exit(1);	
	}
	
	/* line */
	fprintf(stderr, " in line %d\n", yylineno);
	
	exit(1);
}