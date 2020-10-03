#include <stdio.h>
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
    struct Passenger passenger2 = {2, "First 2", "Last 2", "B", 31, -1, true};
    struct Passenger passenger3 = {3, "First 3", "Last 3", "C", 25, 1, true};

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
    printf ("Train: id = %3d | name = %8s | weight = %7d | power = %6d |\n",
            train.id, train.name, train.weight, train.power);
}

void print_passenger(struct Passenger passenger) {
    printf ("Passenger: id = %3d | first_name = %7s | last_name = %7s | passport = %3s | age = %3d |\n",
            passenger.id, passenger.first_name, passenger.last_name, passenger.passport, passenger.age);
}

void print_travel(struct Travel travel) {
    printf("Travel: id = %3d | train_id = %3d | passenger_id = %3d | date = %5s |\n",
            travel.id, travel.train_id, travel.passenger_id, travel.date);
}

void print_all_trains() {
    printf("%s", "\nThis is all Trains:\n");
    FILE *train_data_file = fopen("../train.data", "rb");
    struct Train train;
    while(fread(&train, sizeof(struct Train), 1, train_data_file)) {
        if(train.exists) {
            print_train(train);
        }
    }
    fclose(train_data_file);
}

void print_all_passengers() {
    printf("%s", "\nThis is all Passengers:\n");
    FILE *passenger_data_file = fopen("../passenger.data", "rb");
    struct Passenger passenger;
    while(fread(&passenger, sizeof(struct Passenger), 1, passenger_data_file)) {
        if(passenger.exists) {
            print_passenger(passenger);
        }
    }
    fclose(passenger_data_file);
}

void print_all_travels() {
    printf("%s", "\nThis is all Travels:\n");
    FILE *travel_data_file = fopen("../travel.data", "rb");
    struct Travel travel;
    while(fread(&travel, sizeof(struct Travel), 1, travel_data_file)) {
        if(travel.exists) {
            print_travel(travel);
        }
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

void insert_passenger(struct Passenger new_passenger) {
    FILE *passenger_data_file = fopen("../passenger.data", "w+b");
    FILE *passenger_index_file = fopen("../passenger.index", "rb");
    fseek(passenger_data_file, 0, SEEK_END);
    unsigned int position = ftell(passenger_data_file) / sizeof(struct Passenger);
    fwrite(&new_passenger, sizeof(struct Passenger), 1, passenger_data_file);
    struct PassengerIndex temp;
    while(fread(&temp, sizeof(struct PassengerIndex), 1, passenger_index_file)) {
        
    }
}


int main() {
    initial_data();
    print_all_trains();
    print_all_passengers();
    print_all_travels();

    printf("%s", "\nGet:\n");
    print_train(get_train(2));
    print_passenger(get_passenger(3));
    print_travel(get_travel(3, 4));

//    printf("%s", "\nUpdate:\n");
//
//    print_passenger(get_passenger(1));
//    update_passenger(1, "Changed 1", "Last Changed 1", "Changed A", 20);
//    print_passenger(get_passenger(1));
//
//    print_train(get_train(1));
//    update_train(1, "Changed 2", 5000, 1000);
//    print_train(get_train(1));

    printf("%s", "\nDelete:\n");

    delete_train(2);
    print_all_trains();
    print_all_travels();

    delete_passenger(3);
    print_all_passengers();
    print_all_travels();
    return 0;
}