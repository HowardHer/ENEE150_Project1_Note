#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function prototype
typedef struct{
	char name[15];
	float balance;
	float initial_balance;
	float total_random_numbers;
	float average_random_numbers;
	float total_sum;
	float average_sum;
	int win_count;
}Person;

typedef struct{
	int round;
	int value;
	int sums[4];
}Stat;

typedef struct{
	int round;
	float value;
	float sums[4];
}Float_Stat;

int get_sum(int value);

int get_maximum(int array[], int size);

int get_max_index(float array[]);

int get_second_max_index(float array[]);

int get_second_max(int array[], int size);

int get_third_max(int array[], int size);

void print_endgame_info(Person *player, int round, FILE *output);

// copies whatever is in b to a
void copy_values(int a[], int b[]);

int cmpfunc (const void * a, const void * b);

float get_float_maximum(float array[], int size);

float get_float_minimum(float array[], int size);

int get_minimum_index(float array[]);

float get_third_float_max(float array[], int size);

void copy_float_values(float a[], float b[]);


// function definition
int get_sum(int value){
	int sum = 0;
	sum = value % 10;
	value = value / 10;
	sum = sum + value;
	return sum;
}

int get_max_index(float array[]){
	float array_copy[4];
	int i;
	for(i = 0; i < 4; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	for(i = 0; i < 4;i++){
		if(array[i] == array_copy[3]){
			return i;
		}
	}
}

int get_second_max_index(float array[]){
	float array_copy[4];
	int i;
	for(i = 0; i < 4; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	for(i = 0; i < 4;i++){
		if(array[i] == array_copy[2]){
			return i;
		}
	}
}

int get_minimum_index(float array[]){
	float array_copy[4];
	int i;
	for(i = 0; i < 4; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	for(i = 0; i < 4;i++){
		if(array[i] == array_copy[0]){
			return i;
		}
	}
}

int get_maximum(int array[], int size){
	int maximum = array[0];
	int i;
	for(i = 1; i <= size - 1; i++){
		if(array[i] > maximum){
			maximum = array[i];
		}
	}
	return maximum;
}

float get_float_maximum(float array[], int size){
	float array_copy[4];
	int i;

	for(i = 0; i < size; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	return array_copy[3];
}

void copy_values(int a[], int b[]){
	int i;
	for(i = 0; i < 4; i++){
		a[i] = b[i];
	}
}

void copy_float_values(float a[], float b[]){
	int i;
	for(i = 0; i < 4; i++){
		a[i] = b[i];
	}
}

int cmpfunc (const void * a, const void * b) {
	return ( *(int*)a - *(int*)b );
}

int get_second_max(int array[], int size){
	int array_copy[4];
	int i;

	for(i = 0; i < size; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(int), cmpfunc);

	return array_copy[2];
}

float get_float_minimum(float array[], int size){
	float array_copy[4];
	int i;

	for(i = 0; i < size; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	return array_copy[0];
}

int get_third_max(int array[], int size){
	int array_copy[4];
	int i;

	for(i = 0; i < size; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(int), cmpfunc);

	return array_copy[1];
}

float get_second_float_max(float array[], int size){
	float array_copy[4];
	int i;

	for(i = 0; i < size; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	return array_copy[2];
}

float get_third_float_max(float array[], int size){
	float array_copy[4];
	int i;

	for(i = 0; i < size; i++){
		array_copy[i] = array[i];
	}
	qsort(array_copy, 4, sizeof(float), cmpfunc);

	return array_copy[1];
}

void print_endgame_info(Person *player, int round, FILE *output){
	int i;
	for(i = 0; i < 4; i++){
		fprintf(output,"%s:\n", player[i].name);
		fprintf(output,"initial balance: $%.2f\n", player[i].initial_balance);
		fprintf(output,"ending balance: $%.2f\n", player[i].balance);
		fprintf(output,"lost: $%.2f\n", player[i].initial_balance - player[i].balance);

		player[i].average_random_numbers = (float)player[i].total_random_numbers / round;
		fprintf(output,"average_random_numbers: %.2f\n", player[i].average_random_numbers);

		player[i].average_sum = (float)player[i].total_sum / round;
		fprintf(output,"average sum: %.2f\n", player[i].average_sum);
		fprintf(output,"number of rounds won: %d\n", player[i].win_count);
		fprintf(output,"\n");
	}
}

// ./a.out mode seed round names.txt (numbers.txt) outputFile.txt
/*
 * if mode == 1, 7 arguments
 * if mode == 2, 6 arguments, numbers.txt does not exist
 */
int main(int argc, char **argv){
	int mode = atoi(argv[1]);
	int seed = atoi(argv[2]);
	int round = atoi(argv[3]);
	FILE *list;
	FILE *input;
	FILE *output;
	Person player[4];
	int i = 0;
	int index = 0;
	int count = 0;
	char ch;
	int value[4];
	int sum[4];

	Stat largest_winning_sum = {0, 0, {0}};
	Stat smallest_winning_sum = {0, 0, {0}};
	Stat largest_non_winning_sum = {0, 0, {0}};
	float average_winning_sum = 0;
	Float_Stat largest_net_win = {0, 0, {0}};
	Float_Stat largest_net_loss = {0, 0, {0}};
	int two_way_tie = 0;
	int three_way_tie = 0;

	float winning_sum = 0;
	int second_largest_sum = 0; 

	float random_number = 0;
	int contribution = 0;
	float earn[4];
	float player_get[4];

	srand(seed);

	
	//check if there are 7 command line arguments, when mode == 1
	if(mode == 1 && argc != 7){
		printf("Wrong number of arguments.\n");
		exit(1);
	}else if(mode == 2 && argc != 6){
		printf("Wrong number of arguments.\n");
		exit(1);
	}

	if(mode == 1){
		list = fopen(argv[4],"r");
		input = fopen(argv[5],"r");
		output = fopen(argv[6],"w");
	}else if(mode == 2){
		list = fopen(argv[4],"r");
		output = fopen(argv[5],"w");
	}else{
		printf("Wrong mode number\n");
		exit(3);
	}
	
	// Error checking
	if(list == NULL){
		printf("Player file (names.txt) does not exist.\n");
		exit(2);
	}
	if(mode == 1 && input == NULL){
		printf("Input value file does not exist\n");
		exit(2);
	}

	// Get names and inital balance
	for(i = 0; i < 4; i++){
		index = 0;
		do{
			ch = fgetc(list);
			if(isalpha(ch)){
				player[i].name[index] = ch;
			}else{
				player[i].name[index] = '\0';
			}
			index++;
		}while(ch != ' ');

		fscanf(list,"%f ", &player[i].balance);
	}

	// Initialization
	for(i = 0; i < 4; i++){
		player[i].initial_balance = player[i].balance;
		player[i].average_random_numbers = 0;
		player[i].average_sum = 0;
		player[i].win_count = 0;
		player[i].total_random_numbers = 0;
		player[i].total_sum = 0;
	}

	// For each round
	for(count = 1; count <= round; count++){
		if(mode == 1 && feof(input)){
			break;
		}
		for(i = 0; i < 4; i++){
			if(mode == 1){
				fscanf(input,"%d",&value[i]);
			}else{
				value[i] = rand()%100;
			}
			sum[i] = get_sum(value[i]);
			player[i].total_random_numbers += value[i];
			player[i].total_sum += sum[i];
		}

		winning_sum = get_maximum(sum,4);
		for(index = 0; index < 4; index++){
			if(winning_sum == sum[index]){
				break;
			}
		}
		if(player[index].balance - winning_sum < 0){
			break;
		}

		second_largest_sum = get_second_max(sum,4);
		if(winning_sum > largest_winning_sum.value){
			largest_winning_sum.value = winning_sum;
			largest_winning_sum.round = count;
			copy_values(largest_winning_sum.sums, sum);
		}
		if(second_largest_sum > largest_non_winning_sum.value){
			largest_non_winning_sum.value = second_largest_sum;
			largest_non_winning_sum.round = count;
			copy_values(largest_non_winning_sum.sums, sum);
		}

		if(count == 1){
			smallest_winning_sum.value = winning_sum;
			smallest_winning_sum.round = count;
			copy_values(smallest_winning_sum.sums, sum);
		}else if(count != 1 && winning_sum < smallest_winning_sum.value){
			smallest_winning_sum.value = winning_sum;
			smallest_winning_sum.round = count;
			copy_values(smallest_winning_sum.sums, sum);
		}
		average_winning_sum = (average_winning_sum*(count - 1) + winning_sum) / count;

		for(i = 0; i < 4; i++){
			earn[i] = 0;
			player_get[i] = 0;
		}
		player[index].win_count++;
		player[index].balance -= winning_sum;
		earn[index] -= winning_sum;

		
		fprintf(output,"Round %d:\n", count);
		for(i = 0;i < 4;i++){
			fprintf(output,"%s: %d-->%d\t",player[i].name, value[i], sum[i]);
		}
		fprintf(output,"\n");

		fprintf(output,"%s contributes $%.2f to the pool. New balance: $%.2f\n", 
			player[index].name, (float)sum[index], player[index].balance);

		for(i = 0; i < 4; i++){
			if(i == 3){
				player[i].balance = player[i].balance + winning_sum;
				earn[i] += winning_sum;
				player_get[i] = winning_sum;
			}else{
				do{
					random_number = winning_sum* ((float)rand() / RAND_MAX);
				}while((winning_sum - random_number) < (0.01*(3-i)));
				player[i].balance += random_number;
				earn[i] += random_number;
				winning_sum -= random_number;
				player_get[i] = random_number;
			}
		}

		if(count == 1){
			largest_net_win.value = get_float_maximum(earn,4);
			largest_net_win.round = count;
			copy_float_values(largest_net_win.sums, earn);
		}else if(largest_net_win.value < get_float_maximum(earn, 4)){
			largest_net_win.value = get_float_maximum(earn,4);
			largest_net_win.round = count;
			copy_float_values(largest_net_win.sums, earn);
		}

		if(count == 1){
			largest_net_loss.value = get_float_minimum(earn,4);
			largest_net_loss.round = count;
			copy_float_values(largest_net_loss.sums, earn);
		}else if(count != 1 && largest_net_loss.value > get_float_minimum(earn,4)){
			largest_net_loss.value = get_float_minimum(earn,4);
			largest_net_loss.round = count;
			copy_float_values(largest_net_loss.sums, earn);
		}

		if(get_float_maximum(sum,4) == get_second_float_max(sum,4)){
			two_way_tie++;
		}else if(get_float_maximum(sum,4) == get_second_float_max(sum,4) 
			&& get_float_maximum(sum,4) == get_third_float_max(sum,4)){
			three_way_tie++;
		}

		for(i = 0; i < 4; i++){
			fprintf(output,"%s takes $%.2f, new balance is $%.2f\n", player[i].name, player_get[i], player[i].balance);
		}
		fprintf(output,"\n");
		
	}
	print_endgame_info(player, count, output);
	fprintf(output,"largest winning sum: %d in round %d (%d %d %d %d)\n", 
		largest_winning_sum.value, largest_winning_sum.round, largest_winning_sum.sums[0],
		largest_winning_sum.sums[1], largest_winning_sum.sums[2], largest_winning_sum.sums[3]);
	fprintf(output,"smallest winning sum: %d in round %d (%d %d %d %d)\n",
		smallest_winning_sum.value, smallest_winning_sum.round, smallest_winning_sum.sums[0],
		smallest_winning_sum.sums[1], smallest_winning_sum.sums[2], smallest_winning_sum.sums[3]);
	fprintf(output,"largest non-winning sum: %d in round %d (%d %d %d %d)\n", 
		largest_non_winning_sum.value, largest_non_winning_sum.round, largest_non_winning_sum.sums[0],
		largest_non_winning_sum.sums[1], largest_non_winning_sum.sums[2], largest_non_winning_sum.sums[3]);
	fprintf(output,"average winning sum: %.2f\n", average_winning_sum);

	fprintf(output,"largest net win: $%.2f %s in round %d ($%.2f $%.2f $%.2f $%.2f)\n", largest_net_win.value, 
		player[get_max_index(largest_net_win.sums)].name, largest_net_win.round,
		largest_net_win.sums[0], largest_net_win.sums[1], largest_net_win.sums[2],
		largest_net_win.sums[3]);
	fprintf(output,"largest net loss: $%.2f %s in round %d ($%.2f $%.2f $%.2f $%.2f)\n", largest_net_loss.value,
		player[get_minimum_index(largest_net_loss.sums)].name, largest_net_loss.round,
		largest_net_loss.sums[0], largest_net_loss.sums[1], largest_net_loss.sums[2],
		largest_net_loss.sums[3]);
	fprintf(output,"number of rounds with 2-way tied winning sum: %d\n", two_way_tie);
	fprintf(output,"number of rounds with 3-way tied winning sum: %d\n", three_way_tie);

	fclose(list);
	fclose(output);
	if(mode == 1){
		fclose(input);
	}

	return 0;
}