#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_S 13
#define NUM_G 12

struct node{
	char name[31];
	int amount;
	struct node *next;
};
struct node *head_s = NULL;
struct node *tail_s = NULL;
struct node *head_g = NULL;
struct node *tail_g = NULL;

char surgical[NUM_S][31] = {"Anesthetic", "Antibiotics", "Antiseptic", "Clamp", "Defibrilator", "Lab Kit", "Pins", "Scalpel", "Splint", "Sponge", "Tranfussion", "Ultrasound", "Stitches"};
char galactic[NUM_G][31] = {"AI Brain", "Cyborg Diplomat", "Galactibolt", "Gigablaster", "Growton Torpedo", "Quadriscanner", "Hypershields", "Space Meds", "Star Supplies", "Stellar Document", "Tactical Drone", "Teleporter Charge"};

void show_menu(){
	printf("Please select a task:\n");
	printf("1. Autoclave\n");
	printf("2. Startool Nanoforge\n");
	printf("3. Exit\n");
	printf("---------------------\n");
	printf("Input: ");
}

struct node *create_new_node(char inp_name[31], int inp_amount){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	strcpy(new_node->name, inp_name);
	new_node->amount = inp_amount;
	new_node->next = NULL;
	
	return new_node;
}

void insert_list(char inp_name[31], int inp_amount, int code){
	struct node *tool = create_new_node(inp_name, inp_amount);
	
	if(code == 1){
		if(head_s == NULL){
			head_s = tail_s = tool;
			tail_s->next = NULL;
		}
		else{
			tail_s->next = tool;
			tail_s = tool;
			tail_s->next = NULL;
		}
	}
	
	else if(code == 2){
		if(head_g == NULL){
			head_g = tail_g = tool;
			tail_g->next = NULL;
		}
		else{
			tail_g->next = tool;
			tail_g = tool;
			tail_g->next = NULL;
		}
	}	
}

void show_tool_list(int code){
	int i = 0;
	struct node *curr = NULL;
	
	if(code == 1){
		printf("No\tAmount\tSurgical Tool\n");
		curr = head_s;
	}
	else if(code == 2){
		printf("No\tAmount\tGalactic Tool\n");
		curr = head_g;
	}

	while(curr != NULL){
		printf("%d\t%d\t%s\n", i + 1, curr->amount, curr->name);
		i++;
		curr = curr->next;
	}
	printf("\n");
	
	printf(">> Please input %d is you're finished.\n", i + 1);
	printf("---------------------\n");
	printf("Input: ");
}

void perform_tool_reforge(int code){
	int inp_amount[NUM_S];
	int i, sel, n;
	
	if(code == 1){
		printf("Please insert the initial numbers of the surgical tools you are having:\n");
		printf("---------------------\n");
		n = NUM_S;
		
	} else if(code == 2){
		printf("Please insert the initial numbers of the galatic tools you are having:\n");
		printf("---------------------\n");
		n = NUM_G;
	}

	for(i = 0; i < n; i++){
		do{
			if(code == 1){
				printf("%s: ", surgical[i]); scanf("%d", &inp_amount[i]); getchar();
			} else if(code == 2){
				printf("%s: ", galactic[i]); scanf("%d", &inp_amount[i]); getchar();
			}
			
			if(inp_amount[i] < 0){
				printf("<Number of the tool is invalid.>>\n\n");
			}
			
		} while(inp_amount[i] < 0);
	}
	printf("\n");
	
	for(i = 0; i < n; i++){
		if(code == 1){
			insert_list(surgical[i], inp_amount[i], 1);
		} else if(code == 2){
			insert_list(galactic[i], inp_amount[i], 2);
		}
	}
	
	do{
		struct node *curr = NULL;
		struct node *del = NULL;
		
		if(code == 1){
			curr = head_s;
			del = head_s;
		}
		
		else if(code == 2){
			curr = head_g;
			del = head_g;
		}

		printf("Select a tool to exchange:\n");
		printf("---------------------\n");

		if(code == 1){
			show_tool_list(1);
		} else if(code == 2){
			show_tool_list(2);
		}
		
		scanf("%d", &sel); getchar();
		printf("\n");
			
		if(sel < 1 || sel > n + 1){
			printf("<<Invalid option selection.>>\n\n");
		} else if(sel == n + 1){
			break;
		}
		
		else {
			for(i = 1; i < sel; i++){
				del = del->next;
			}
		
			if(del->amount >= 20){
				del->amount -= 20;
				while(curr != NULL){
					if(curr != del){
						curr->amount++;
					}
					curr = curr->next;
				}
			}
		
			else {
				printf("<<Only tools with number of 20 or more can be nanoforge-performed.>>\n\n");
			}
		}	
			
	} while(sel != n + 1);
}

void delete_list(int code){
	struct node *del = NULL;
	struct node *curr = NULL;
	if(code == 1){
		curr = head_s;
		while(curr != NULL){
			del = curr;
			curr = curr->next;
			free(del);
		}
		del == NULL;
		
	} else if(code == 2){
		curr = head_g;
		while(curr != NULL){
			del = curr;
			curr = curr->next;
			free(del);
		}
		del == NULL;
		
	}
}

int main(){
	char selection;
	
	do{
		show_menu();
		scanf("%c", &selection); getchar();
		printf("\n\n");
	
		if(selection == '1'){
			perform_tool_reforge(1);
			delete_list(1);
		}
		else if(selection == '2'){
			perform_tool_reforge(2);
			delete_list(2);
		}
		
	} while(selection != '3');
	
	return 0;
}
