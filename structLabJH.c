#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int recoil;
	int aimAssist;
	int impact;
	int range;
	int blastRadius;
	int velocity;
	int stability;
	int ROF;
	int reload;
	int mag;
	int equip;
	int chargeTime;
	int drawTime;
	int accuracy;
} Details;

typedef struct {
	char name[50];
	char tier[15];
	char type[30];
	char category[20];
	char element[10];

	Details stats;

	char perks[15][50];

} Item;

// Body uses "struct node" because "Node" hasn't been declared yet
typedef struct node {

	Item entry;

	struct node *next;
} Node;

Node *head = NULL;
Node *current = NULL;



// Display functions
void displayList();
void displayEntryDetailed(Item entry);
void displayEntry(Item entry);

// Linked list management
void insert(Item entry);
void delete(int index, int quiet);
Node* getNode(int index);
int length();

// Initialization
void initializeLinkedList(char *path);

// User functions
void add();
void search(char query[50], char field[10]);
void get(int index);
void help();
void displayFields();

int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Invalid number of parameters, please supply an input file\n");
		exit(-1);
	}

	// Intializes linked list from file
	initializeLinkedList(argv[1]);

	// Brings up help menu 
	help();

	char s[100] = {0};

	// Continually gets user input
	while (strcmp(s, "q") != 0) {
		printf("Enter an option (q to quit): ");
		scanf(" %s", s);
		
		
		// To lower
		int i = 0;
		while (s[i++] != '\0') s[i] += 32*(64 < s[i] && s[i] < 91);
		
		if (strcmp(s, "add") == 0) {
			add();
		} else if (strcmp(s, "search") == 0) {
			displayFields();
			
			char field[10];
			char query[50];

			printf("Field: ");
			scanf(" %s", field);
			printf("Query: ");
			scanf(" %[^\n]s", query);
			search(query, field);
		} else if (strcmp(s, "get") == 0) {
			int index = -1;

			printf("Enter the index of the record you want to get: ");
			scanf(" %d", &index);
			// That way it displays as counting from 1, but removes correctly
			get(--index);
		} else if (strcmp(s, "delete") == 0) {
			int index = -1;

			printf("Enter the index of the record you wnat to delete: ");
			scanf(" %d", &index);
			// That way it displays as counting from 1, but removes correctly
			delete(--index,1);
		} else if (strcmp(s, "display") == 0) {
			displayList();
		} else if (strcmp(s, "q") == 0) {
			break;
		} else {
			printf("Not a valid option\n");
		}
		puts("========================================");
	}

	return 0;
}

// User input
void add() {
	Item entry;

	char s[100];

	// Fills in first 5 elements
	printf("Enter the name: ");
	scanf(" %[^\n]s", s);
	strcpy(entry.name,s);
	printf("Enter the tier: ");
	scanf(" %[^\n]s", s);
	strcpy(entry.tier,s);
	printf("Enter the type: ");
	scanf(" %[^\n]s", s);
	strcpy(entry.type,s);
	printf("Enter the category: ");
	scanf(" %[^\n]s", s);
	strcpy(entry.category,s);
	printf("Enter the element: ");
	scanf(" %[^\n]s", s);
	strcpy(entry.element,s);

	// Fills in all integer stats
	int i;
	printf("Enter the recoil stat: ");
	scanf(" %d", &i);
	entry.stats.recoil = i;
	printf("Enter the aimAssist stat: ");
	scanf(" %d", &i);
	entry.stats.aimAssist = i;
	printf("Enter the impact stat: ");
	scanf(" %d", &i);
	entry.stats.impact = i;
	printf("Enter the range stat: ");
	scanf(" %d", &i);
	entry.stats.range = i;
	printf("Enter the blastRadius stat: ");
	scanf(" %d", &i);
	entry.stats.blastRadius = i;
	printf("Enter the velocity stat: ");
	scanf(" %d", &i);
	entry.stats.velocity = i;
	printf("Enter the stability stat: ");
	scanf(" %d", &i);
	entry.stats.stability = i;
	printf("Enter the ROF stat: ");
	scanf(" %d", &i);
	entry.stats.ROF = i;
	printf("Enter the reload stat: ");
	scanf(" %d", &i);
	entry.stats.reload = i;
	printf("Enter the mag stat: ");
	scanf(" %d", &i);
	entry.stats.mag = i;
	printf("Enter the equip stat: ");
	scanf(" %d", &i);
	entry.stats.equip = i;
	printf("Enter the chargeTime stat: ");
	scanf(" %d", &i);
	entry.stats.chargeTime = i;
	printf("Enter the drawTime stat: ");
	scanf(" %d", &i);
	entry.stats.drawTime = i;
	printf("Enter the accuracy stat: ");
	scanf(" %d", &i);
	entry.stats.accuracy = i;


	// Fills in all applicable perks
	int ind = 0;
	printf("Enter a perk: ");	
	scanf(" %[^\n]s", s);

	while (strcmp(s,"q") != 0 && ind < 16) {
		strcpy(entry.perks[ind],s);
		printf("Enter a perk (q to quit): ");
		scanf(" %[^\n]s", s);
		ind++;
	}

	printf("Inserted "); 
	displayEntry(entry);
	puts("===========================");
	displayEntryDetailed(entry);
	insert(entry);
	
}

// Searches for all matching records with matching query and field
// Equivalent to SQL Command:
// SELECT * FROM TABLE WHERE field = query
// Concrete example:
// search("Thorn", "name"); is the same as
// SELECT * FROM TABLE WHERE name = "Thorn";
void search(char query[50], char field[10]) {

	printf("Searching for \"%s\" in field \"%s\"... \n", query, field);

	Node *ptr = head;
	int index = 1;

	ptr = ptr->next;

	// Although it would be cleaner to write this as one while loop and then a check
	// I think that this is more efficient because then it only checks it once, instead of
	// every iteration.
	if (strcmp("name",field) == 0) {
		while (ptr != NULL) {
			if (strcmp(query, ptr->entry.name)==0) {
				printf("%3d. ",index);
				displayEntry(ptr->entry);		
			}
			ptr = ptr->next;
			index++;
		}
	} else if (strcmp("tier", field) == 0) {
		while (ptr != NULL) {
			if (strcmp(query, ptr->entry.tier)==0) {
				printf("%3d. ",index);
				displayEntry(ptr->entry);		
			}
			ptr = ptr->next;	
			index++;
		}
	} else if (strcmp("type", field) == 0) {
		while (ptr != NULL) {
			if (strcmp(query, ptr->entry.type)==0) {
				printf("%3d. ",index);
				displayEntry(ptr->entry);		
			}
			ptr = ptr->next;	
			index++;
		}	
	} else if (strcmp("category", field) == 0) {
		while (ptr != NULL) {
			if (strcmp(query, ptr->entry.category)==0) {
				printf("%3d. ",index);
				displayEntry(ptr->entry);		
			}
			ptr = ptr->next;	
			index++;
		}	
	} else if (strcmp("element", field) == 0) {
		while (ptr != NULL) {
			if (strcmp(query, ptr->entry.element)==0) {
				printf("%3d. ",index);
				displayEntry(ptr->entry);		
			}
			ptr = ptr->next;	
			index++;
		}
	} else {
		printf("Not a valid field query");
	}
}

// Gets a detailed list about a specific Node
void get(int index) {
	displayEntryDetailed(getNode(index)->entry);
}

// Prints a help message
void help() {
	displayFields();
	printf("Commands: \n");
	printf("Add: add a new entry to the start of the list\n");
	printf("Search: Enter a query and a field to search for all records that match\n");
	printf("Get: Gets a detailed view of an item given an index\n");
	printf("Delete: deletes an item at a given index\n");
	printf("Display: Displays the list of records\n");
	printf("Help: Displays this menu\n");
}

// Displays the fields
// Only its own function because the search command displays it
void displayFields() {
	printf("The fields in this database are:\n");
	printf("+----+----+----+--------+-------+\n");
	printf("|name|tier|type|category|element|\n");
	printf("+----+----+----+--------+-------+\n");
}

// Inserts to the start of the linked list
void insert(Item entry) {
	
	Node *link = (Node*) malloc(sizeof(Node));

	link->entry = entry;
	link->next = head;

	head = link;
	
}

// Delete item from Linked List at index
// Has quiet option when doing non-user instructions
void delete(int index, int quiet) {
	
	Node* current = head;
	Node* previous = NULL;

	if (!head) return;

	int count = 0;

	while (count != index) {
		// Check if last
		if (!current->next) return;

		previous = current;
		current = current->next;
		count++;
	}

	// if first one is being deleted
	if (current == head) {
		head = head->next;
	} else {
		previous->next = current->next;
	}
	
	if (quiet != 0) {
		printf("Deleted: ");
		displayEntry(current->entry);
	}
	// I think this frees the memory?
	free(current);
}

// Gets the Node at a specific index
// Still here because might be useful for linked list stuff in the future, even though it's a little unecessary right now
Node* getNode(int index) {
	
	Node* current = head;


	if (!head) return NULL;

	int count = 0;

	while (count != index) {
		// Check if last
		if (!current->next) return NULL;

		current = current->next;
		count++;
	}

	return current;
}

// Gets the length of the linked list
// (Mostly unused now, was useful for testing)
int length() {

	int len = 0;

	Node *current;

	for (current = head; current != NULL; current = current->next) {
		len++;
	}
	return len;
}

// Initializes the linked list
void initializeLinkedList(char *file) {

	FILE *fp;
	char row[1000];
	char *token;

	fp = fopen(file,"r");


	// Gets the first row
	fgets(row, 1000, fp);

	int jj = 0;

	while (!feof(fp)) {
		// gets entry
		fgets(row,1000,fp);
		
		// creates the Item for the entry
		char* token = strtok(row, ",");
		int count = 0;

		Item entry;
		Details stats;
		entry.stats = stats;

		// inserts token into data field
		while (token) {
			switch (count)
			{
				case 0:
					strcpy(entry.name,token);
					break;
				case 1:
					strcpy(entry.tier,token);
					break;
				case 2:
					strcpy(entry.type,token);
					break;
				case 3:
					strcpy(entry.category,token);
					break;
				case 4:
					strcpy(entry.element,token);
					break;
				case 5:
					entry.stats.recoil = atoi(token);
					break;
				case 6:
					entry.stats.aimAssist = atoi(token);
					break;
				case 7:
					entry.stats.impact = atoi(token);
					break;
				case 8:
					entry.stats.range = atoi(token);
					break;
				case 9:
					entry.stats.blastRadius = atoi(token);
					break;
				case 10:
					entry.stats.velocity = atoi(token);
					break;
				case 11:
					entry.stats.stability = atoi(token);
					break;
				case 12:
					entry.stats.ROF = atoi(token);
					break;
				case 13:
					entry.stats.reload = atoi(token);
					break;
				case 14:
					entry.stats.mag = atoi(token);
					break;
				case 15:
					entry.stats.equip = atoi(token);
					break;
				case 16:
					entry.stats.chargeTime = atoi(token);
					break;
				case 17:
					entry.stats.drawTime = atoi(token);
					break;
				case 18:
					entry.stats.accuracy = atoi(token);
					break;
				default:
					break;
			}
			if (count > 18) {
				strcpy(entry.perks[count-19],token); 
			}
			token = strtok(NULL,",");
			count++;
		}
		insert(entry);
	}
	// Removes the duplicated last element
	delete(0,0);
}

// Displays simple itemized list
void displayList() {

	Node *ptr = head;
	int index = 1;

	while (ptr != NULL) {
		printf("%3d. ",index++);
		displayEntry(ptr->entry);
		ptr = ptr->next;
	}

}

// More detailed list, intended for getting specific items
void displayEntryDetailed(Item e) {
	printf("%s, %s %s, %s %s\n",e.name,e.tier,e.type,e.category,e.element);
	puts("Statistics:");
	printf("Recoil: %d\nAA: %d\nImpact: %d\nRange: %d\nBlast: %d\nVelo: %d\nStabil: %d\nROF: %d\nReload %d\nMag: %d\nEquip: %d\nCharge: %d\nDrae. %d\nAcc: %d\n",	
		e.stats.recoil,
		e.stats.aimAssist,
		e.stats.impact,
		e.stats.range,
		e.stats.blastRadius,
		e.stats.velocity,
		e.stats.stability,
		e.stats.ROF,
		e.stats.reload,
		e.stats.mag,
		e.stats.equip,
		e.stats.chargeTime,
		e.stats.drawTime,
		e.stats.accuracy);
	puts("Perks");
	
	int i = -1;
	// No clue why the empty strings have a length of 2 but they do, so it skips if it's too short
	while (strlen(e.perks[++i]) > 2 && i < 14) {
		printf("%s\n", e.perks[i]);
	}
	return;
}

// Much simpler display, only displays necessary info
void displayEntry(Item e) {
	printf("%s, %s %s, %s %s\n",e.name,e.tier,e.type,e.category,e.element);
}

