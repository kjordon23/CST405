#include "code_gen.h"

void generate_code(){	
	FILE *fp;
	fp = fopen("mips.asm", "w");
	
	generate_data_declarations(fp);
	
	fclose(fp);
}

void generate_data_declarations(FILE *fp){
	/* print .data */
	fprintf(fp, "\t.data\n");	
	
	/* loop through the symbol table's lists */
	int i;
	for (i = 0; i < SIZE; i++){ 
		/* if hashtable list not empty */
		if (hash_table[i] != NULL){ 
			sym_entry *l = hash_table[i];
			/* loop through list */
			while (l != NULL){ 
				/* Simple Variables */
				if (l->sym_type == INT_TYPE){
					fprintf(fp, "%s: .word %d\n", l->name, l->val.ival);
				}
				else if (l->sym_type == FLOAT_TYPE){
					fprintf(fp, "%s: .double %f\n", l->name, l->val.fval);
				}
				else if (l->sym_type == CHAR_TYPE){
					fprintf(fp, "%s: .byte \'%c\'\n", l->name, l->val.cval);
				}				
				
				/* Array */
				else if (l->sym_type == ARRAY_TYPE){
					if (l->inf_type == INT_TYPE){
						fprintf(fp, "%s: .space %d\n", l->name, l->array_size*4);
					}
					else if (l->inf_type  == FLOAT_TYPE){
						fprintf(fp, "%s: .space %d\n", l->name, l->array_size*8);
					}
					else if (l->inf_type  == CHAR_TYPE){
						fprintf(fp, "%s: .space %d\n", l->name, l->array_size*1);
					}
				}
			
				l = l->next;
			}
		}
	}
	// Generate main method for statements afterwards
	fprintf(fp, "\n\t.text\n");
	fprintf(fp, "main:\n");
}