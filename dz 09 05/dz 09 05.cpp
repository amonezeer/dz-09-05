#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Vehicle {
    string type;
    string model;

    virtual void move() = 0;
    virtual ~Vehicle() {}
};

struct Truck : public Vehicle {
    void move() override {
        cout << "Грузовик движется по дороге" << endl;
    }
};

struct Ship : public Vehicle {
    void move() override {
        cout << "Корабль плывет по морю" << endl;
    }
};

struct Airplane : public Vehicle {
    void move() override {
        cout << "Самолет летит в небе" << endl;
    }
};

struct TransportFactory {
    virtual Vehicle* createTransport() = 0;
    virtual ~TransportFactory() {}
};

struct TruckFactory : public TransportFactory {
    Vehicle* createTransport() override {
        Truck* truck = new Truck();
        cout << "Введите модель грузовика: ";
        cin >> truck->model;
        truck->type = "Грузовик";
        return truck;
    }
};

struct ShipFactory : public TransportFactory {
    Vehicle* createTransport() override {
        Ship* ship = new Ship();
        cout << "Введите модель судна: ";
        cin >> ship->model;
        ship->type = "Судно";
        return ship;
    }
};


struct AirplaneFactory : public TransportFactory {
    Vehicle* createTransport() override {
        Airplane* airplane = new Airplane();
        cout << "Введите модель самолета: ";
        cin >> airplane->model;
        airplane->type = "Самолет";
        return airplane;
    }
};

void createAndAddTransport(TransportFactory* factory, vector<Vehicle*>& vehicles) {
    vehicles.push_back(factory->createTransport());
}

int main() {

    system("chcp 1251");

    vector<Vehicle*> vehicles;
    int choice;

    do {
        cout << "Выберите тип создаваемого транспорта (1 – Грузовик, 2 – Корабль, 3 – Самолет, 0 – Выход): \n ";
        cin >> choice;

        switch (choice) {
        case 1: createAndAddTransport(new TruckFactory(), vehicles); break;
        case 2: createAndAddTransport(new ShipFactory(), vehicles); break;
        case 3: createAndAddTransport(new AirplaneFactory(), vehicles); break;
        default: break;
        }
    } while (choice != 0);


    for (const auto& vehicle : vehicles) {
        cout << "Тип: " << vehicle->type << ", Модель: " << vehicle->model << endl;
        vehicle->move();
        delete vehicle; 
    }

    return 0;
}
