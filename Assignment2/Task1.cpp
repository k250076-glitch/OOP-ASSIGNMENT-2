#include <iostream>
using namespace std;
class Displayable{
public:
    virtual void show()= 0;  //MADE THIS CLASS ABSTRACT
};

class Searchable{
public:
    virtual bool matchesBrand(string brand) = 0; 
    virtual bool matchesPrice(float minP, float maxP) = 0;
    
};
class Approvable{
public:
    virtual void approve() = 0;          
    virtual bool isApproved()  = 0; 
};


class user:public Displayable{
    int id;
    string name;
    string city;
    string phone;
    string email;
    public:
        user(){ // DEFAULT CONSTUCTOR (IF NO PARAMETER WILL PASS)
            id = 0000;
            name = "Anonymous";
        }
        user(int id, string name, string city, string phone, string email):id(id),name(name),city(city),phone(phone),email(email){} // PARAMETRIZED CONSTUCTOR
        user(user &obj){ // COPY CONSTRUCTOR
            id = obj.id;
            name = obj.name;
            city = obj.city;
            phone = obj.phone;
            email = obj.email;
        }
        void display(){
            cout << "User: " << name <<endl;
            cout<<"City: " << city << endl;
        }
        string getName(){ 
            return name; 
        }
        int getId(){ 
            return id; 
        }

        void show(){
            cout << "User: " << name << " | City: " << city << endl;
        }
        bool operator==(user &other){
            bool temp;
            temp = id == other.id;
            return temp;
        }
        friend void printUserReport(user &u);
};

void printUserReport(user &u){
    cout << " User Report => ID: " << u.id << " | Email: " << u.email << endl;
}

class Engine{
    int power;
    string fuelType;
    int capacity;
    public:
        Engine(int power = 100, string fuelType = "Petrol", int capacity = 1300):power(power),fuelType(fuelType),capacity(capacity){}
        void displaySpecs(){
            cout << "Engine: " <<power<< "HP " << fuelType<< " " << capacity << "cc"<<endl;
        }
};


class Vehicle:public Searchable{
    int vehicleid;
    Engine engine1; // COMPOSITION
    string brand;
    string model;
    int year;
    float price;
    int mileage;
public:
    Vehicle(int id=0,string b="IDK",string m="IDK",int y=0,float p=0,int mil=0):vehicleid(id),engine1(){
        brand=b; model=m; year=y; price=p; mileage=mil;
    }
    virtual void displayVehicle()= 0;
    bool matchesBrand(string b){ 
        return brand == b; 
    }
    bool matchesPrice(float minP, float maxP){
        bool temp;
        temp = price >= minP && price <= maxP;
        return temp;
    }

    string getBrand(){
        return brand; 
    }
    float getPrice(){ 
        return price; 
    }
    int getYear(){ 
        return year;  
    }
    int getMileage(){ 
        return mileage; 
    }
    void displayBase(){
        cout<<"ID:"<<vehicleid<<" "<<brand<<" "<<model<<" Year:"<<year<<" Price:"<<price<<" Mileage:"<<mileage<<endl;
        engine1.displaySpecs();
    }
    bool operator==(Vehicle &other){
        bool temp;
        temp = brand==other.brand && model==other.model && year==other.year;
        return temp;
    }
    float operator+(Vehicle &other){
        float temp;
        temp =  price + other.price;
        return temp;
    }
    friend void compareVehiclePrices(Vehicle &v1,Vehicle &v2);

};

void compareVehiclePrices(Vehicle &v1,Vehicle &v2){
    cout << "Price Compare: Rs." << v1.price
         << " vs Rs." << v2.price << endl;
    if(v1.price < v2.price)
        cout<< v1.brand << " " << v1.model << " is cheaper." << endl;
    else
        cout <<v2.brand << " " << v2.model << " is cheaper." << endl;
}


class Car:public Vehicle{
    int numDoors;
    string bodyType;
    public:
        Car(int id=0,string b="IDK",string m="IDK",int y=0,float p=0,int mil=0,int doors=4, string body="Sedan"):Vehicle(id,b,m,y,p,mil), numDoors(doors), bodyType(body){}
        void displayVehicle(){
            cout<<"---------------------------------------"<<endl;
            cout<<"DISPLAYING CAR DETAILS"<<endl;
            cout<<"---------------------------------------"<<endl;
            displayBase();
            cout<<"Body: "<<bodyType<<" | Doors: "<<numDoors<<endl;
        }
        void displayVehicle(bool compact){
            if(compact)
                cout<<"CAR "<<getBrand()<<" Rs."<<getPrice()<<endl;
            else
                displayVehicle();
        }
};


class Bike:public Vehicle{
    string bikeType;
    bool hasGear;
    public:
        Bike(int id=0,string b="IDK",string m="IDK",int y=0,float p=0,int mil=0,string type="Standard", bool gear=true):Vehicle(id,b,m,y,p,mil), bikeType(type), hasGear(gear){}

        void displayVehicle(){
            cout<<"---------------------------------------"<<endl;
            cout<<"DISPLAYING BIKE DETAILS"<<endl;
            cout<<"---------------------------------------"<<endl;
            displayBase();
            cout<<"Type: "<<bikeType<<" | Geared: "<<(hasGear?"Yes":"No")<<endl;
        }

        void displayVehicle(bool compact){
            if(compact)
                cout<<"BIKE "<<getBrand()<<" Rs."<<getPrice()<<endl;
            else
                displayVehicle();
        }
};


class Truck:public Vehicle{
    float payloadTons;
    string truckClass;
    public:
        Truck(int id=0,string b="IDK",string m="IDK",int y=0,float p=0,int mil=0,float payload=5.0f, string cls="Light"):Vehicle(id,b,m,y,p,mil), payloadTons(payload), truckClass(cls){}

        void displayVehicle(){
            cout<<"---------------------------------------"<<endl;
            cout<<"DISPLAYING TRUCK DETAILS"<<endl;
            cout<<"---------------------------------------"<<endl;
            displayBase();
            cout<<"Payload: "<<payloadTons<<" tons | Class: "<<truckClass<<endl;
        }
};

class Seller; // DECLARED EARLIER SO CAN USE IT IN THE CODE BEFORE MAKING IT

class Listing:public Approvable{
    Vehicle *vehicle1;  
    Seller *seller1;    
    bool approved;
public:
    Listing(){
        vehicle1 = NULL;
        seller1 = NULL;
        approved = false;
    }
    void setListing(Vehicle *v, Seller *s){
        vehicle1 = v;
        seller1  = s;
    }
    void approve(){ 
        approved = true; 
    }
    bool isApproved(){ 
        return approved; 
    }

    void displayListing(){
        if(approved && vehicle1)
            vehicle1->displayVehicle();
    }
    Vehicle* getVehicle(){ 
        return vehicle1; 
    }
    friend void auditListing(Listing &l);
};

void auditListing(Listing &l){
    cout << "Listing Audit => Approved: "<< (l.approved ? "Yes" : "No") << endl;
}

class Seller : public user{
    Listing listings[10];
    int listingCount;
    string shopName;
public:
    Seller(){ // DEFAULT CONSTRUCTOR
        listingCount=0;
        shopName="";
    }
    Seller(int id, string name, string city, string phone,string email, string shop=""):user(id, name, city, phone, email), shopName(shop){
        listingCount=0;
    }

    void addListing(Vehicle *v){
        listings[listingCount].setListing(v, this);
        listingCount++;
    }
    Listing* getListings(){ 
        return listings; 
    }
    int getCount(){ 
        return listingCount; 
    }

    void showSeller(){ 
        display(); 
    }
    void show(){
        cout << "SELLER " << getName() << " | Shop: " << shopName << endl;
    }
};

class Favorite{
    Vehicle *vehicle;
public:
    Favorite(){ 
        vehicle = NULL; 
    }
    void addFavorite(Vehicle *v){ 
        vehicle = v; 
    }
    void showFavorite(){
        if(vehicle) vehicle->displayVehicle();
    }
};

class Message{
    string text;
    string sender;
    string receiver;
public:
    Message(string s="",string r="",string t=""){
        sender=s; 
        receiver=r; 
        text=t;
    }
    void displayMessage(){
        cout<<sender<<" -> "<<receiver<<" : "<<text<<endl;
    }
};


class Buyer:public user{
    Favorite favorites[10];
    int favCount;
    float budget;
public:
    Buyer(int id, string name, string city, string phone,string email, float budget=0):user(id, name, city, phone, email), budget(budget){
        favCount=0;
    }
    void saveFavorite(Vehicle *v){
        favorites[favCount++].addFavorite(v);
    }
    void viewFavorites(){
        for(int i=0;i<favCount;i++)
            favorites[i].showFavorite();
    }
    void sendMessage(string seller, string text){
        Message m(getName(), seller, text);
        m.displayMessage();
    }
    void show(){
        cout << "BUYER " << getName() << " | Budget: Rs." << budget << endl;
    }
};



class Admin:public user{
    static int approvedCount;
    string accessLevel;
    public:
        Admin(int id, string name, string city, string phone,string email, string level="Standard"):user(id, name, city, phone, email),accessLevel(level){}
        void approveListing(Listing &l){
            l.approve();
            approvedCount++;
        }
        static void showApproved(){
            cout<<"Approved Listings: "<<approvedCount<<endl;
        }
        void show(){
            cout << "ADMIN " << getName() << " | Access: " << accessLevel << endl;
        }
};
int Admin::approvedCount=0;


class Marketplace{
    Listing listings[50];
    int totalListings;
    static int systemListings;
public:
    Marketplace(){ 
        totalListings=0; 
    }
    void addListing(Listing l){
        listings[totalListings]=l;
        totalListings++;
        systemListings++;
    }
    void searchByBrand(string brand){
        for(int i=0;i<totalListings;i++) {
            Vehicle *v = listings[i].getVehicle();
            if(v && v->matchesBrand(brand))
                listings[i].displayListing();
        }
    }

    void searchByPrice(float minP, float maxP){
        cout<<"--- Price Range Rs."<<minP<<" to Rs."<<maxP<<" ---"<<endl;
        for(int i=0;i<totalListings;i++) {
            Vehicle *v = listings[i].getVehicle();
            if(v && v->matchesPrice(minP, maxP))
                listings[i].displayListing();
        }
    }
    static void totalSystemListings(){
        cout<<"Total Listings in System: "<<systemListings<<endl;
    }
};
int Marketplace::systemListings=0;



int main(){
Seller seller(101,"Mustafa","Karachi","033535","mustafapolani@gmail","Mustafa Motors");
Buyer  buyer(201,"Ahmed","Lahore","033121","ahmed@gmail",800000);
Admin  admin(301,"Admin","Islamabad","033222","admin@gmail","SuperAdmin");

Car   car1(101,"Toyota","Corolla",2020,450000,30000);
Bike  bike1(201,"Yamaha","YBR125",2022,180000,12000);
Truck truck1(301,"Isuzu","NKR",2018,900000,80000);

seller.addListing(&car1);
seller.addListing(&bike1);

Listing *sellerListings = seller.getListings();
admin.approveListing(sellerListings[0]);

Marketplace market;
market.addListing(sellerListings[0]);
market.addListing(sellerListings[1]);

cout<<"Approved Cars"<<endl;;
market.searchByBrand("Toyota");

buyer.saveFavorite(&car1);
cout<<"Favorites"<<endl;
buyer.viewFavorites();

buyer.sendMessage("Mustafa","Is this car still available?");
Admin::showApproved();
Marketplace::totalSystemListings();



Vehicle *fleet[3] = {&car1, &bike1, &truck1};
for(int i=0;i<3;i++)
    fleet[i]->displayVehicle();  

car1.displayVehicle(true);   
bike1.displayVehicle(true);

Car car2(102,"Honda","Civic",2020,520000,45000);

if(car1 == car2)
    cout<<"Same vehicle."<<endl;
else
    cout<<"Different vehicles."<<endl;

float totalValue = car1 + car2;
cout<<"Combined fleet value: Rs."<<totalValue<<endl;

user u1(101,"Mustafa","Karachi","033535","mustafapolani92@gmail");
user u2(201,"Ahmed","Lahore","033121","alphalearning35@gmail");
if(u1 == u2)
    cout<<"Same user."<<endl;
else
    cout<<"Different users."<<endl;

printUserReport(u1);
compareVehiclePrices(car1, car2);
auditListing(sellerListings[0]);

Displayable *people[3] = {&seller, &buyer, &admin};
for(int i=0;i<3;i++)
    people[i]->show();

market.searchByPrice(100000, 500000);

}