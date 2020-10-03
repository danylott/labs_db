#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

const int CLEAR_GARBAGE = 50;

struct Train {
    unsigned int id;
    char name[32];
    unsigned int weight;
    unsigned int power;
    bool exists;
};

struct TrainIndex {
    unsigned int train_id;
    int position;
};

struct Passenger {
    unsigned int id;
    char first_name[32];
    char last_name[32];
    char passport[32];
    short age;
    int first_travel_position;
    bool exists;
};

struct PassengerIndex {
    unsigned int passenger_id;
    int position;
};

struct Travel {
    unsigned int id;
    unsigned int train_id;
    unsigned int passenger_id;
    char date[32];
    int next_travel_position;
    bool exists;
    // helper value for get_travel works as get_travel_position also
    int current_position;
};

bool check_position(int position, char who[]) {
    if(position == -1) {
        printf("%s %s %s", "This", who, "does not exist!");
        return false;
    }
    return true;
}

void initial_data() {
    FILE *train_data_file = fopen("../train.data", "w+b");
    struct Train train1 = {1, "Train 1", 100000, 500, true};
    struct Train train2 = {2, "Train 2", 50000, 600, true};
    struct Train train3 = {3, "Train 3", 80000, 700, true};

    fwrite(&train1, sizeof(struct Train), 1, train_data_file);
    fwrite(&train2, sizeof(struct Train), 1, train_data_file);
    fwrite(&train3, sizeof(struct Train), 1, train_data_file);

    fclose(train_data_file);

    FILE *train_index_file = fopen("../train.index", "w+b");
    struct TrainIndex train_index1 = {1, 0};
    struct TrainIndex train_index2 = {2, 1};
    struct TrainIndex train_index3 = {3, 2};

    fwrite(&train_index1, sizeof(struct TrainIndex), 1, train_index_file);
    fwrite(&train_index2, sizeof(struct TrainIndex), 1, train_index_file);
    fwrite(&train_index3, sizeof(struct TrainIndex), 1, train_index_file);

    fclose(train_index_file);

    FILE *passenger_data_file = fopen("../passenger.data", "w+b");
    struct Passenger passenger1 = {1, "First 1", "Last 1", "A", 19, 0, true};
    struct Passenger passenger2 = {2, "First 2", "Last 2", "C", 24, -1, true};
    struct Passenger passenger3 = {3, "First 3", "Last 3", "B", 25, 1, true};

    fwrite(&passenger1, sizeof(struct Passenger), 1, passenger_data_file);
    fwrite(&passenger2, sizeof(struct Passenger), 1, passenger_data_file);
    fwrite(&passenger3, sizeof(struct Passenger), 1, passenger_data_file);

    fclose(passenger_data_file);

    FILE *passenger_index_file = fopen("../passenger.index", "w+b");
    struct PassengerIndex passenger_index1 = {1, 0};
    struct PassengerIndex passenger_index2 = {2, 1};
    struct PassengerIndex passenger_index3 = {3, 2};

    fwrite(&passenger_index1, sizeof(struct PassengerIndex), 1, passenger_index_file);
    fwrite(&passenger_index2, sizeof(struct PassengerIndex), 1, passenger_index_file);
    fwrite(&passenger_index3, sizeof(struct PassengerIndex), 1, passenger_index_file);

    fclose(passenger_index_file);

    FILE * travel_file = fopen("../travel.data", "w+b");
    struct Travel travel1 = {1, 1,1, "2020", -1, true};
    struct Travel travel2 = {2, 2,3, "2019", 2, true};
    struct Travel travel3 = {3, 3,3, "2020", 3, true};
    struct Travel travel4 = {4, 2,3, "2020", -1, true};

    fwrite(&travel1, sizeof(struct Travel), 1, travel_file);
    fwrite(&travel2, sizeof(struct Travel), 1, travel_file);
    fwrite(&travel3, sizeof(struct Travel), 1, travel_file);
    fwrite(&travel4, sizeof(struct Travel), 1, travel_file);

    fclose(travel_file);
}

void print_train_index(struct TrainIndex train_index) {
    printf ("TrainIndex: train_id = %d position = %d\n", train_index.train_id, train_index.position);
}

void print_train(struct Train train) {
    printf ("Train: id = %3d | name = %9s | weight = %7d | power = %6d | exists = %2d |\n",
            train.id, train.name, train.weight, train.power, train.exists);
}

void print_passenger(struct Passenger passenger) {
    printf ("Passenger: id = %2d | first = %8s | last = %8s |"
            " passport = %2s | age = %3d | first_travel = %2d | exists = %2d |\n",
            passenger.id, passenger.first_name, passenger.last_name,
            passenger.passport, passenger.age, passenger.first_travel_position, passenger.exists);
}

void print_travel(struct Travel travel) {
    printf("Travel: universal_code = %3d | train_id = %3d |"
           " passenger_id = %3d | date = %5s | next_travel = %3d | exists = %3d |\n",
            travel.id, travel.train_id,
            travel.passenger_id, travel.date, travel.next_travel_position, travel.exists);
}

void print_all_trains() {
    printf("%s", "\nThis is all Trains:\n");
    FILE *train_data_file = fopen("../train.data", "rb");
    struct Train train;
    while(fread(&train, sizeof(struct Train), 1, train_data_file)) {
            print_train(train);
    }
    fclose(train_data_file);
}

void print_all_passengers() {
    printf("%s", "\nThis is all Passengers:\n");
    FILE *passenger_data_file = fopen("../passenger.data", "rb");
    struct Passenger passenger;
    while(fread(&passenger, sizeof(struct Passenger), 1, passenger_data_file)) {
            print_passenger(passenger);
    }
    fclose(passenger_data_file);
}

void print_all_travels() {
    printf("%s", "\nThis is all Travels:\n");
    FILE *travel_data_file = fopen("../travel.data", "rb");
    struct Travel travel;
    while(fread(&travel, sizeof(struct Travel), 1, travel_data_file)) {
            print_travel(travel);
    }
    fclose(travel_data_file);
}

int find_train_position(int id) {
    FILE *train_index_file = fopen("../train.index", "rb");
    int index = 0;
    struct TrainIndex temp;
    while(fread(&temp, sizeof(struct TrainIndex), 1, train_index_file)) {
        if (temp.train_id == id) {
            return temp.position;
        }
        index += 1;
    }

    fclose(train_index_file);
    return -1;
}

struct Train train_error() {
    printf("%s", "This train does not exist!\n");
    struct Train error = {0, "error"};
    return error;
}

struct Train get_train(int id) {
    int position = find_train_position(id);
    if(check_position(position, "train")) {
        FILE *train_data_file = fopen("../train.data", "rb");
        fseek(train_data_file, position * sizeof(struct Train), SEEK_SET);
        struct Train found_train;
        fread(&found_train, sizeof(struct Train), 1, train_data_file);
        if(!found_train.exists) {
            return train_error();
        }
        return found_train;
    }
    return train_error();
}

int find_passenger_position(int id) {
    FILE *passenger_index_file = fopen("../passenger.index", "rb");
    struct PassengerIndex passenger_indexes[20];
    int index = 0;
    struct PassengerIndex temp;
    struct PassengerIndex correct_passenger_index;
    while(fread(&temp, sizeof(struct PassengerIndex), 1, passenger_index_file)) {
        if (temp.passenger_id == id) {
            return temp.position;
        }
        passenger_indexes[index] = temp;
        index += 1;
    }
    fclose(passenger_index_file);

    return -1;
}

struct Passenger passenger_error() {
    printf("%s", "This passenger does not exist!\n");
    struct Passenger error = {0, "error"};
    return error;
}

struct Passenger get_passenger(int id) {
    int position = find_passenger_position(id);
    if(check_position(position, "passenger")) {
        FILE *passenger_data_file = fopen("../passenger.data", "rb");
        fseek(passenger_data_file, position * sizeof(struct Passenger), SEEK_SET);
        struct Passenger found_passenger;
        fread(&found_passenger, sizeof(struct Passenger), 1, passenger_data_file);
        if(!found_passenger.exists) {
            return passenger_error();
        }
        return found_passenger;
    }
    return passenger_error();
}

struct Travel travel_error() {
    printf("%s", "This travel does not exist!\n");
    struct Travel travel = {0, 0, 0, "error"};
    return travel;
}

struct Travel get_travel(int passenger_id, int travel_id) {
    struct Passenger passenger = get_passenger(passenger_id);
    FILE * travel_file = fopen("../travel.data", "rb");
    if(passenger.first_travel_position != -1) {
        fseek(travel_file, passenger.first_travel_position * sizeof(struct Travel), SEEK_SET);
        struct Travel temp;
        while(fread(&temp, sizeof(struct Travel), 1, travel_file)) {
            if(temp.id == travel_id) {
                // cheats here only for get_travel()
                temp.current_position = ftell(travel_file) / sizeof(struct Travel) - 1;
                return temp;
            }
            if(temp.next_travel_position != -1) {
                fseek(travel_file, temp.next_travel_position * sizeof(struct Travel), SEEK_SET);
            } else {
                break;
            }
        }
    }
    return travel_error();
}

void update_train_file(int position, struct Train train) {
    FILE *train_data_file = fopen("../train.data", "rb+");

    fseek(train_data_file, position * sizeof(struct Train), SEEK_SET);
    fwrite(&train, sizeof(struct Train), 1, train_data_file);

    fclose(train_data_file);
}

void update_passenger_file(int position, struct Passenger passenger) {
    FILE *passenger_data_file = fopen("../passenger.data", "rb+");

    fseek(passenger_data_file, position * sizeof(struct Passenger), SEEK_SET);
    fwrite(&passenger, sizeof(struct Passenger), 1, passenger_data_file);

    fclose(passenger_data_file);
}

void update_travel_file(int position, struct Travel travel) {
    FILE *travel_data_file = fopen("../travel.data", "rb+");

    fseek(travel_data_file, position * sizeof(struct Travel), SEEK_SET);
    fwrite(&travel, sizeof(struct Travel), 1, travel_data_file);

    fclose(travel_data_file);
}

void delete_train(int id) {
    struct Train train_to_delete = get_train(id);
    printf("%s", "Train to delete: \n");
    print_train(train_to_delete);

    int train_position = find_train_position(id);

    train_to_delete.exists = false;
    update_train_file(train_position, train_to_delete);
}

void delete_travels(int position) {
    struct Travel temp;
    while (position != -1) {
        FILE *travel_data_file = fopen("../travel.data", "rb");
        fseek(travel_data_file, position * sizeof(struct Travel), SEEK_SET);
        fread(&temp, sizeof(struct Travel), 1, travel_data_file);
        fclose(travel_data_file);
        temp.exists = false;
        update_travel_file(position, temp);
        position = temp.next_travel_position;
    }
}

void delete_passenger(int id) {
    struct Passenger passenger_to_delete = get_passenger(id);
    printf("%s", "Passenger to delete: \n");
    print_passenger(passenger_to_delete);

    int passenger_position = find_passenger_position(id);

    passenger_to_delete.exists = false;
    delete_travels(passenger_to_delete.first_travel_position);
    update_passenger_file(passenger_position, passenger_to_delete);
}

void delete_travel(int passenger_id, int travel_id) {
    struct Passenger passenger = get_passenger(passenger_id);
    struct Travel travel_to_delete = get_travel(passenger_id, travel_id);
    if (travel_to_delete.id != 0){
        printf("%s", "Travel to delete: \n");
        print_travel(travel_to_delete);
        int position = passenger.first_travel_position;
        FILE *travel_data_file = fopen("../travel.data", "rb");
        struct Travel previous, current;
        previous.id = -1;
        int previous_position = 0;
        fseek(travel_data_file, position * sizeof(struct Travel), SEEK_SET);
        fread(&current, sizeof(struct Travel), 1 , travel_data_file);

        while(current.id != travel_id) {
            previous_position = position;
            position = current.next_travel_position;
            previous = current;
            fseek(travel_data_file, position * sizeof(struct Travel), SEEK_SET);
            fread(&current, sizeof(struct Travel), 1 , travel_data_file);
        }
        if(previous.id == -1) {
            passenger.first_travel_position = -1;
            update_passenger_file(find_train_position(passenger_id), passenger);
        } else {
            previous.next_travel_position = current.next_travel_position;
            update_travel_file(previous_position, previous);
        }
        current.exists = false;
        update_travel_file(position, current);
        fclose(travel_data_file);
    }
}

void update_train(int id, char name[], int weight, int power) {
    int position = find_train_position(id);
    if(check_position(position, "train")) {
        struct Train train = get_train(id);
        strcpy(train.name, name);
        train.weight = weight;
        train.power = power;
        update_train_file(position, train);
    }
}

void update_passenger(int id, char first_name[], char last_name[], char passport[], short age) {
    int position = find_passenger_position(id);
    if(check_position(position, "passenger")) {
        struct Passenger passenger = get_passenger(id);
        strcpy(passenger.first_name, first_name);
        strcpy(passenger.last_name, last_name);
        strcpy(passenger.passport, passport);
        passenger.age = age;
        update_passenger_file(position, passenger);
    }
}

void update_travel(int passenger_id, int travel_id, char date[]) {
    struct Travel travel = get_travel(passenger_id, travel_id);
    int position = travel.current_position;
    if(check_position(position, "travel")) {
        strcpy(travel.date, date);
        update_travel_file(position, travel);
    }
}

void append_passenger_file(struct Passenger passenger) {
    FILE *passenger_data_file = fopen("../passenger.data", "ab+");
    fwrite(&passenger, sizeof(struct Passenger), 1, passenger_data_file);
    fclose(passenger_data_file);
}

void append_train_file(struct Train train) {
    FILE *train_data_file = fopen("../train.data", "ab+");
    fwrite(&train, sizeof(struct Train), 1, train_data_file);
    fclose(train_data_file);
}

void append_travel_file(struct Travel travel) {
    FILE *travel_data_file = fopen("../travel.data", "ab+");
    fwrite(&travel, sizeof(struct Travel), 1, travel_data_file);
    fclose(travel_data_file);
}

int get_last_passenger_position() {
    FILE *passenger_data_file = fopen("../passenger.data", "rb");
    fseek(passenger_data_file, 0, SEEK_END);
    int position = ftell(passenger_data_file) / sizeof(struct Passenger);
    fclose(passenger_data_file);
    return position;
}

int get_last_train_position() {
    FILE *train_data_file = fopen("../train.data", "rb");
    fseek(train_data_file, 0, SEEK_END);
    int position = ftell(train_data_file) / sizeof(struct Train);
    fclose(train_data_file);
    return position;
}

int get_last_travel_position() {
    FILE *travel_data_file = fopen("../travel.data", "rb");
    fseek(travel_data_file, 0, SEEK_END);
    int position = ftell(travel_data_file) / sizeof(struct Travel);
    fclose(travel_data_file);
    return position;
}

unsigned int insert_passenger_index(int position) {
    FILE *passenger_index_file = fopen("../passenger.index", "rb+");
    struct PassengerIndex previous_index;
    fseek(passenger_index_file, 0, SEEK_END);
    int last = ftell(passenger_index_file) / sizeof(struct PassengerIndex) - 1;
    if(last >= 0) {
        fseek(passenger_index_file, last * sizeof(struct PassengerIndex), SEEK_SET);
        fread(&previous_index, sizeof(struct PassengerIndex), 1, passenger_index_file);
        struct PassengerIndex current_index = {previous_index.passenger_id + 1, position};
        fseek(passenger_index_file, 0, SEEK_END);
        fwrite(&current_index, sizeof(struct PassengerIndex), 1, passenger_index_file);
        fclose(passenger_index_file);
        return previous_index.passenger_id + 1;
    }
    return 1;
}

unsigned int insert_train_index(int position) {
    FILE *train_index_file = fopen("../train.index", "rb+");
    struct TrainIndex previous_index;
    fseek(train_index_file, 0, SEEK_END);
    int last = ftell(train_index_file) / sizeof(struct TrainIndex) - 1;
    if(last >= 0) {
        fseek(train_index_file, last * sizeof(struct TrainIndex), SEEK_SET);
        fread(&previous_index, sizeof(struct TrainIndex), 1, train_index_file);
        struct TrainIndex current_index = {previous_index.train_id + 1, position};
        fseek(train_index_file, 0, SEEK_END);
        fwrite(&current_index, sizeof(struct TrainIndex), 1, train_index_file);
        fclose(train_index_file);
        return previous_index.train_id + 1;
    }
    return 1;
}

void insert_passenger(struct Passenger new_passenger) {
    new_passenger.first_travel_position = -1;
    new_passenger.exists = true;
    int position = get_last_passenger_position();
    new_passenger.id = insert_passenger_index(position);
    append_passenger_file(new_passenger);
}

void insert_train(struct Train new_train) {
    new_train.exists = true;
    int position = get_last_train_position();
    new_train.id = insert_train_index(position);
    append_train_file(new_train);
}

void insert_travel(int passenger_id, struct Travel new_travel) {
    new_travel.next_travel_position = -1;
    new_travel.passenger_id = passenger_id;
    new_travel.exists = true;
    struct Passenger passenger = get_passenger(passenger_id);
    int position = get_last_travel_position();
    append_travel_file(new_travel);
    if(passenger.first_travel_position == -1) {
        passenger.first_travel_position = position;
        update_passenger_file(find_passenger_position(passenger_id), passenger);
    } else {
        FILE *travel_data_file = fopen("../travel.data", "rb");
        struct Travel current;
        int prev_position = passenger.first_travel_position;
        fseek(travel_data_file, position * sizeof(struct Travel), SEEK_SET);
        fread(&current, sizeof(struct Travel), 1, travel_data_file);
        while(current.next_travel_position != -1) {
            prev_position = current.next_travel_position;
            fseek(travel_data_file, current.next_travel_position * sizeof(struct Travel), SEEK_SET);
            fread(&current, sizeof(struct Travel), 1, travel_data_file);
        }
        struct Travel temp;
        fseek(travel_data_file, prev_position * sizeof(struct Travel), SEEK_SET);
        fread(&temp, sizeof(struct Travel), 1, travel_data_file);
        temp.next_travel_position = position;
        update_travel_file(prev_position, temp);
        fclose(travel_data_file);
    }
}

int count_trains() {
    FILE *train_data_file = fopen("../train.data", "rb");
    struct Train train;
    int result = 0;
    while(fread(&train, sizeof(struct Train), 1, train_data_file)) {
        if(train.exists) {
            result++;
        }
    }
    fclose(train_data_file);
    return result;
}

int count_passengers() {
    FILE *passenger_data_file = fopen("../passenger.data", "rb");
    int result = 0;
    struct Passenger passenger;
    while(fread(&passenger, sizeof(struct Passenger), 1, passenger_data_file)) {
        if(passenger.exists) {
            result++;
        }
    }
    fclose(passenger_data_file);
    return result;
}

int count_travels() {
    FILE *travel_data_file = fopen("../travel.data", "rb");
    int result = 0;
    struct Travel travel;
    while(fread(&travel, sizeof(struct Travel), 1, travel_data_file)) {
        if(travel.exists) {
            result++;
        }
    }
    fclose(travel_data_file);
    return result;
}

int count_passenger_travels(int passenger_id) {
    struct Passenger passenger = get_passenger(passenger_id);
    int result = 0;
    int position = passenger.first_travel_position;
    struct Travel travel;
    FILE *travel_data_file = fopen("../travel.data", "rb");
    while(position != -1) {
        result++;
        fseek(travel_data_file, position * sizeof(struct Travel), SEEK_SET);
        fread(&travel, sizeof(struct Travel), 1, travel_data_file);
        position = travel.next_travel_position;
    }
    fclose(travel_data_file);
    return result;
}

void print_menu() {
    printf("\nTrain System:\n");
    printf("Enter one of the following commands:\n");
    printf("\t\"get-all\" - get all tables\n");
    printf("\t\"get-passenger id\" - get Passenger by id\n");
    printf("\t\"get-passenger-all\" - get all Passengers\n");
    printf("\t\"get-train id\" - get Train by id\n");
    printf("\t\"get-train-all\" - get all Trains\n");
    printf("\t\"get-travel passenger_id travel_id\" - get Travel by passenger_id and travel_id\n");
    printf("\t\"get-travel-all\" - get all Travels\n");
    printf("\t\"insert-passenger first_name last_name passport age\" - add new Passenger\n");
    printf("\t\"insert-train name weight power\" - add new Train\n");
    printf("\t\"insert-travel universal_code passenger_id train_id date\" - add new Travel\n");
    printf("\t\"update-passenger id first_name last_name passport age\" - update Passenger\n");
    printf("\t\"update-train id name weight power\" - update Train\n");
    printf("\t\"update-travel passenger_id travel_id date\" - update Travel\n");
    printf("\t\"delete-passenger id\" - delete Passenger (with connected Travels) by id\n");
    printf("\t\"delete-train id\" - delete Train by id\n");
    printf("\t\"delete-travel passenger_id travel_id\" - delete Travel by passenger_id travel_id\n");
    printf("\t\"count\" - to count amount of data in each table\n");
    printf("\t\"exit\" - to exit\n");
}

int to_int(char text[]) {
    return (int) strtol(text, (char **)NULL, 10);
}

int handle_operation() {
    char operation[200];
    fgets(operation, 100, stdin);
    char copy[200];
    strcpy(copy, operation);

    char* option = strtok(operation, " \n");
    if (!strcmp(option, "insert-passenger")) {
        char first_name[32], last_name[32], passport[32], age[32];
        sscanf(copy, "%s %s %s %s %s", operation, first_name, last_name, passport, age);
        struct Passenger passenger;
        strcpy(passenger.first_name, first_name);
        strcpy(passenger.last_name, last_name);
        strcpy(passenger.passport, passport);
        passenger.age = to_int(age);
        insert_passenger(passenger);
    } else if (!strcmp(option, "insert-train")) {
        char name[32], weight[32], power[32];
        sscanf(copy, "%s %s %s %s", operation, name, weight, power);
        struct Train train;
        strcpy(train.name, name);
        train.weight = to_int(weight);
        train.power = to_int(power);
        insert_train(train);
    } else if (!strcmp(option, "insert-travel")) {
        char date[32], code[32], passenger_id[32], train_id[32];
        sscanf(copy, "%s %s %s %s %s", operation, code, passenger_id, train_id, date);
        struct Travel travel;
        travel.id = to_int(code);
        travel.passenger_id = to_int(passenger_id);
        travel.train_id = to_int(train_id);
        strcpy(travel.date, date);
        insert_travel(to_int(passenger_id), travel);
    } else if (!strcmp(option, "update-passenger")) {
        char first_name[32], last_name[32], passport[32], age[32], id[32];
        sscanf(copy, "%s %s %s %s %s %s", operation, id, first_name, last_name, passport, age);
        update_passenger(to_int(id), first_name, last_name, passport, to_int(age));
    } else if (!strcmp(option, "update-train")) {
        char name[32], weight[32], power[32], id[32];
        sscanf(copy, "%s %s %s %s %s", operation, id, name, weight, power);
        update_train(to_int(id), name, to_int(weight), to_int(power));
    } else if (!strcmp(option, "update-travel")) {
        char date[32], code[32], passenger_id[32], travel_id[32];
        sscanf(copy, "%s %s %s %s", operation, passenger_id, code, date);
        update_travel(to_int(passenger_id), to_int(code), date);
    } else if (!strcmp(option, "get-passenger")) {
        char id[32];
        sscanf(copy, "%s %s", operation, id);
        print_passenger(get_passenger(to_int(id)));
    } else if (!strcmp(option, "get-train")) {
        char id[32];
        sscanf(copy, "%s %s", operation, id);
        print_train(get_train(to_int(id)));
    } else if (!strcmp(option, "get-travel")) {
        char passenger_id[32], travel_id[32];
        sscanf(copy, "%s %s %s", operation, passenger_id, travel_id);
        print_travel(get_travel(to_int(passenger_id), to_int(travel_id)));
    } else if (!strcmp(option, "get-passenger-all")) {
        print_all_passengers();
    } else if (!strcmp(option, "get-train-all")) {
        print_all_trains();
    } else if (!strcmp(option, "get-travel-all")) {
        print_all_travels();
    } else if (!strcmp(option, "delete-passenger")) {
        char id[32];
        sscanf(copy, "%s %s", operation, id);
        delete_passenger(to_int(id));
    } else if (!strcmp(option, "delete-train")) {
        char id[32];
        sscanf(copy, "%s %s", operation, id);
        delete_train(to_int(id));
    } else if (!strcmp(option, "delete-travel")) {
        char passenger_id[32], travel_id[32];
        sscanf(copy, "%s %s %s", operation, passenger_id, travel_id);
        delete_travel(to_int(passenger_id), to_int(travel_id));
    } else if (!strcmp(option, "count-all")) {
        printf("count passengers = %d\n", count_passengers());
        printf("count trains = %d\n", count_trains());
        printf("count travels = %d\n", count_travels());
    } else if (!strcmp(option, "get-all")) {
        print_all_passengers();
        print_all_trains();
        print_all_travels();
    } else if (!strcmp(option, "exit")) {
        return -1;
    } else {
        printf("\nInvalid command!\n");
    }
    return 0;
}

int main() {
    printf("%d", CLEAR_GARBAGE);
    initial_data();
    print_all_trains();
    print_all_passengers();
    print_all_travels();
    print_menu();
    while(true) {
        if(handle_operation() == -1) {
            break;
        }
    }
    return 0;
}