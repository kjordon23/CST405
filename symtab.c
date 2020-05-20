  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "symtab.h"

/* current scope */
int cur_scope = 0;

int declare = 0; // 1: declaring variable, 0: not

int declare_func = 0; // 1: declaring function, 0: not

// Symbol Table Functions

void init_hash_table(){
	int i; 
	hash_table = malloc(SIZE * sizeof(sym_entry*));
	for(i = 0; i < SIZE; i++) hash_table[i] = NULL;
}

unsigned int hash(char *key){
	unsigned int hash = 0;
    unsigned c;

    while(c = *key++) hash = hash*9 ^ c;

    return hash % SIZE;
}

void insert(char *name, int len, int type, int lineno){
	unsigned int hashval = hash(name);
	sym_entry *l = hash_table[hashval];
	
	while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
	
	/* variable not yet in table */
	if (l == NULL){
		/* check if we are really declaring */
		if(declare == 1){
			/* set up entry */
			l = (sym_entry*) malloc(sizeof(sym_entry));
			strncpy(l->name, name, len);
			l->st_size = len;
			l->sym_type = type;
			l->scope = cur_scope;
			l->lines = (RefList*) malloc(sizeof(RefList));
			l->lines->lineno = lineno;
			l->lines->next = NULL;
			
			/* add to hashtable */
			l->next = hash_table[hashval];
			hash_table[hashval] = l; 
			//printf("Inserted %s for the first time with linenumber %d within scope %d!\n", name, lineno, cur_scope);
		}
		else{
			/* add it to check it again later */
			l = (sym_entry*) malloc(sizeof(sym_entry));
			strncpy(l->name, name, len);
			l->st_size = len;
			l->sym_type = type;
			l->scope = cur_scope;
			l->lines = (RefList*) malloc(sizeof(RefList));
			l->lines->lineno = lineno;
			l->lines->next = NULL;
			l->next = hash_table[hashval];
			hash_table[hashval] = l;
			// printf("Inserted %s at line %d to check it again later!\n", name, lineno);

			add_to_queue(l, l->name, PARAM_CHECK);
			
		}
	}
	/* found in table */
	else{
		// just add line number
		if(declare == 0){
			/* find last reference */
			RefList *t = l->lines;
			while (t->next != NULL) t = t->next;
			
			/* add linenumber to reference list */
			t->next = (RefList*) malloc(sizeof(RefList));
			t->next->lineno = lineno;
			t->next->next = NULL;
			// printf("Found %s again at line %d!\n", name, lineno);
		}
		/* new entry */
		else{
			/* same scope - multiple declaration error! */
			if(l->scope == cur_scope){
				fprintf(stderr, "A multiple declaration of variable %s at line %d\nExiting Program\n.", name, lineno);
 				exit(1);
			}
			/* other scope - create new entry */
			else{
				/* set up entry */
				l = (sym_entry*) malloc(sizeof(sym_entry));
				strncpy(l->name, name, len);
				l->st_size = len;
				l->sym_type = type;
				l->scope = cur_scope;
				l->lines = (RefList*) malloc(sizeof(RefList));
				l->lines->lineno = lineno;
				l->lines->next = NULL;
				
				/* add to hashtable */
				l->next = hash_table[hashval];
				hash_table[hashval] = l; 
				// printf("Inserted %s for a new scope with linenumber %d!\n", name, lineno);
			}	
		}		
	}
}

sym_entry *lookup(char *name){ /* return symbol if found or NULL if not found */
	unsigned int hashval = hash(name);
	sym_entry *l = hash_table[hashval];
	while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
	//printf("Found entry %s\n", l->name);
	return l;
}

sym_entry *lookup_func_call(char *name){ /* return symbol if found or NULL if not found */
	unsigned int hashval = hash(name);
	sym_entry *l = hash_table[hashval];
	while ((l != NULL) && (strcmp(name,l->name) != 0)) l = l->next;
	if (l != NULL && l->scope == 0) {
		return l;
	}
	return NULL;
}

void symtab_dump(FILE * of){  /* dump file */
  fprintf(of, "%-15s%-15s%-15s%-15s%-15s\n\n", "NAME", "TYPE", "SIZE (arrays) ","SCOPE", "VALUE");
  for (int i = 0; i < SIZE; ++i){ 
	if (hash_table[i] != NULL){ 
		sym_entry *l = hash_table[i];
		while (l != NULL){ 
			fprintf(of,"%-15s", l->name);
			if (l->sym_type == INT_TYPE)                fprintf(of,"%-15s","int");
			else if (l->sym_type == FLOAT_TYPE)          fprintf(of,"%-15s","float");
			else if (l->sym_type == CHAR_TYPE)          fprintf(of,"%-15s","char");
			else if (l->sym_type == ARRAY_TYPE){
				if (l->inf_type == INT_TYPE) 		   fprintf(of,"%-15s","array of int");
				else if (l->inf_type  == FLOAT_TYPE)    fprintf(of,"%-15s","array of float");
				else if (l->inf_type  == CHAR_TYPE)    fprintf(of,"%-15s","array ofchar");
				else fprintf(of,"%-15s","undef");
			}
			else if (l->sym_type == FUNCTION_TYPE){
				if (l->inf_type == INT_TYPE) 		   fprintf(of,"%-15s","int function");
				else if (l->inf_type  == FLOAT_TYPE)    fprintf(of,"%-15s","float function");
				else if (l->inf_type  == CHAR_TYPE)	   fprintf(of,"%-15s","char function");
				else if (l->inf_type  == VOID_TYPE)	   fprintf(of,"%-15s","void function");
				else fprintf(of,"%-15s","func");
			}
            if (l->sym_type == ARRAY_TYPE) { // Printing Array Size
                fprintf(of, "%-15d", l->array_size);
            }
            else {
                fprintf(of, "%-15s", "NA");
            }
			fprintf(of,"%-15d",l->scope); // Printing Scope
			// Printing Values
            if (l->sym_type == INT_TYPE) {
                fprintf(of, "%-25d", l->val.ival);
            }
            else if (l->sym_type == FLOAT_TYPE) {
                fprintf(of, "%-25f", l->val.fval);
            }
            else if (l->sym_type == CHAR_TYPE) {
                fprintf(of, "%-25c", l->val.cval);
            }
            else if (l->sym_type == ARRAY_TYPE) {
				if (l->vals != NULL) {	// Not initialized yet
					fprintf(of, "{");
                	for (int i = 0; i < l->array_size - 1; i++) {
                    	if (l->inf_type == INT_TYPE) {
                        	fprintf(of, "%d, ", l->vals[i].ival);
                    	}
                    	else if (l->inf_type == FLOAT_TYPE) {
                        	fprintf(of, "%f, ", l->vals[i].fval);
                    	}
                    	else if (l->inf_type == CHAR_TYPE) {
                        	fprintf(of, "%c, ", l->vals[i].cval);
                    	}
                	}
					if (l->inf_type == INT_TYPE) {
                        	fprintf(of, "%d}", l->vals[l->array_size - 1].ival);
                    	}
                    	else if (l->inf_type == FLOAT_TYPE) {
                        	fprintf(of, "%f}", l->vals[l->array_size - 1].fval);
                    	}
                    	else if (l->inf_type == CHAR_TYPE) {
                        	fprintf(of, "%c}", l->vals[l->array_size - 1].cval);
                    	}
				}
				else {
					fprintf(of, "%-25s ", "NULL");
				}
            }
			else {
					fprintf(of, "%-25s ", "NULL");
			}
			fprintf(of,"\n");
			l = l->next;
		}
    }
  }
}

// Type Functions

void set_type(char *name, int sym_type, int inf_type){ // set the type of an entry (declaration)
	/* lookup entry */
	sym_entry *l = lookup(name);
	
	/* set as "main" type */
	l->sym_type = sym_type;	
	
	/* if array or function */
	if(inf_type != UNDEF){
		l->inf_type = inf_type;
	}	
}

int get_type(char *name){ // get the type of an entry
	/* lookup entry */
	sym_entry *l = lookup(name);
	
	/* if "simple" type */
	if(l->sym_type == INT_TYPE || l->sym_type == FLOAT_TYPE || l->sym_type == CHAR_TYPE){
		return l->sym_type;
	}
	/* if array or function */
	else{
		return l->inf_type;
	}
}

// Scope Management Functions

void hide_scope()	{ /* go back in scope */
	sym_entry *l;
    /* for all the lists */
    for (int i = 0; i < SIZE; i++){
        if(hash_table[i] != NULL){
            l = hash_table[i];
            /* Find the first item that is from another scope */
            while(l != NULL && l->scope == cur_scope){
                //printf("Hiding %s..\n", l->name);
                l = l->next;
            }
            /* Set the list equal to that item */
            hash_table[i] = l;
        }
    }
    cur_scope--;
}

void incr_scope(){ /* go to next scope */
	cur_scope++;
}

// Defining Parameters for functions to be passed through rules of bison

Param def_param(int par_type, char *param_name){ // define parameter
	Param param; /* Parameter struct */
	
	/* set the information */
	param.par_type = par_type;
	strcpy(param.param_name, param_name);
	
	/* return the structure */
	return param;
}

int declareFunction(char *name, int return_type, int numPars, Param *params) {
	sym_entry *entry = lookup(name);
	if (entry->sym_type != UNDEF) {	// If not declared undefined
		entry->sym_type = FUNCTION_TYPE;	// Declare entry type
		entry->inf_type = return_type;	// Declare return type
		entry->num_of_pars = numPars;	// Enter the number of parameters
		entry->parameters = params;		// Insert parameters

		return 0;
	}
	else {
		fprintf(stderr, "Function %s already declared!\n", name);
		exit(1);
	}
}

int funcParameterCheck(char *name, int num_of_calls, int** par_types, int *num_of_pars){ // check parameters
	int i, j, type_1, type_2;
	
	/* lookup entry */
	sym_entry *l = lookup(name);
	
	/* for all function calls */
	for(i = 0 ; i < num_of_calls ; i++){
		/* check number of parameters */
		if(l->num_of_pars != num_of_pars[i]){
			fprintf(stderr, "Function call of %s has wrong num of parameters!\n", name);
			exit(1);
		}
		/* check if parameters are compatible */
		for(j = 0; j < num_of_pars[i]; j++){
			/* type of parameter in function declaration */
			type_1 = l->parameters[j].par_type; 
			
			/* type of parameter in function call*/
			type_2 = par_types[i][j]; 
			
			/* check compatibility for function call */
			get_result_type(type_1, type_2, ISEQUAL);
			/* error occurs automatically in the function */
		}
	}
	
	return 0; /* success */
}

// add to queue functions
void add_to_queue(sym_entry *entry, char *name, int type){
    revisit_queue *q;

	/* queue is empty */
	if(queue == NULL){
		/* set up entry */
		q = (revisit_queue*) malloc(sizeof(revisit_queue));
		q->entry = entry;
		q->name = name;
		q->revisit_type = type;
		q->next = NULL;

		/* additional info */
		if(type == PARAM_CHECK){
			q->num_of_calls = 0;
		}
		else if(type == ASSIGN_CHECK){
			q->num_of_assigns = 0;
		}

		/* q "becomes" the queue */
		queue = q;
	}
	/* queue not empty */
	else{
		/* find last element */
		q = queue;
		while(q->next != NULL) q = q->next;

		/* add element to the end */
		q->next = (revisit_queue*) malloc(sizeof(revisit_queue));
		q->next->entry = entry;
		q->next->name = name;
		q->next->revisit_type = type;
		q->next->next = NULL;

		/* additional info */
		if(type == PARAM_CHECK){
			q->next->num_of_calls = 0;
		}
		else if(type == ASSIGN_CHECK){
			q->next->num_of_assigns = 0;
		}
	}		
}

// search queue
revisit_queue *search_queue(char *name){ /* search queue */
    revisit_queue *q;

    /* search for the entry */
    q = queue;
    while( (q != NULL) && (strcmp(q->name, name) != 0) ) q = q->next;

    return q;
}

// search the previous queue
revisit_queue *search_prev_queue(char *name){
	revisit_queue *q;

	/* queue is empty */
	if(queue == NULL){
		return NULL;
	}

	/* special case - first entry */
	if( strcmp(queue->name, name) == 0 ){
		return NULL;
	}

	/* search for the entry */
	q = queue;
	while( (q != NULL) && (strcmp(q->next->name, name) != 0) ) q = q->next;
	
	return q;
}

// revisit function
int revisit(char *name){
    int i, type1, type2;

	revisit_queue *q = search_queue(name);
	revisit_queue *q2;

	if(q == NULL){
		return -1; // no entry
	}

	/* revisit entry depending on the type */
	switch(q->revisit_type){
		case PARAM_CHECK:			
			/* run parameter check */
			if(!funcParameterCheck(name, q->num_of_calls, q->par_types, q->num_of_pars)){
				printf("Successful Parameter Check of %s\n", name);
			}

			/* remove entry by making it point to it's next */
			q2 = search_prev_queue(name);
			if(q2 == NULL){ /* special case: first entry */
				queue = queue->next;
			}
			else{
				q2->next = q2->next->next;
			}

			break;
		case ASSIGN_CHECK:

			/* run assignment check for each assignment */
			type1 = get_type(q->entry->name);
			for(i = 0; i < q->num_of_assigns; i++){
				type2 = expression_data_type(q->nodes[i]);

				/* perform assignment check */
				get_result_type( type1, type2, ISEQUAL);
			}

			/* remove entry by making it point to it's next */
			q2 = search_prev_queue(name);
			if(q2 == NULL){ /* special case: first entry */
				queue = queue->next;
			}
			else{
				q2->next = q2->next->next;
			}

			break;
		/* ... */
	}

	return 0; // success
}

// dump file formatting
void revisit_dump(FILE *of){
	int i;
	revisit_queue *q;
	q = queue;

	fprintf(of,"------------ -------------\n");
	fprintf(of,"Identifier   Revisit Type\n");
	fprintf(of,"------------ -------------\n");
  	while(q != NULL){
  		fprintf(of, "%-13s", q->name);
  		if(q->revisit_type == PARAM_CHECK){
  			fprintf(of,"%s","Parameter Check ");
  			fprintf(of,"for %d function calls",q->num_of_calls);
		}
		else if(q->revisit_type == ASSIGN_CHECK){
  			fprintf(of,"%s","Assignment Check ");
  			fprintf(of,"for %d assignments",q->num_of_assigns);
		}
		// more later on
		fprintf(of, "\n");
  		q = q->next;	
	}
}



