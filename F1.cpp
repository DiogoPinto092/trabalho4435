#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <limits>
#include "F1.hpp"

using namespace std;

bool DriResult::operator<(const DriResult &dri) const {
    return this->grid<dri.grid;
}

bool Qualifying::operator>( const Qualifying& other) const {
    return timeLap > other.timeLap;
}

NodeRace::~NodeRace() { 
    delete left; 
    delete right;
}

Driver:: Driver(int driverI, string cod, string nam, vector<int> numbe, string dateOfBir, string  nationali):  driverId(driverI), code(cod), name(nam), numbers(numbe), dateOfBirth(dateOfBir), nationality(nationali) {};
Driver:: Driver(int driverI, string cod, string nam,  string dateOfBir, string  nationali):  driverId(driverI), code(cod), name(nam), dateOfBirth(dateOfBir), nationality(nationali) {};

int Driver::getDriverId() const { return driverId; }

string Driver::getCode() const { return code; }

string Driver::getName() const { return name; }

vector<int> Driver::getNumbers() const { return numbers; }

string Driver::getDateOfBirth() const { return dateOfBirth; }

string Driver::getNationality() const { return nationality; }

int Driver::addNumber(int num)
{
    if (num<1 || num>199) return -1;
    vector<int>::iterator it;
    it=find(numbers.begin(),numbers.end(),num);
    if (it!=numbers.end()) {
        return 1;
    }
    numbers.push_back(num);
    return 0;
}


Constructor::Constructor(int constructorId, string name, string country) : constructorId(constructorId), name(name), nationality(country) {};

int Constructor::getConstructorId() const { return constructorId; }

string Constructor::getName() const { return name; }

string Constructor::getCountry() const { return nationality; }

vector<DriCons*> Constructor::getDrivers() { return Drivers; }


int Constructor::deleteDriver(int driveId)
{
   
    for ( auto it=Drivers.begin();it!=Drivers.end(); it++){
        if ((*it)->driver->getDriverId()==driveId) {
           delete(*it);
	Drivers.erase(it);
	return 0;
            } 
        }
        
    
  
   return -1;
}


int Constructor::addDriver(int driveId, int year, DriverManagement &driverManager)
{
   
    if (year<1900 || year>2025 ) return -1;

    vector<Driver*>::iterator it;
    vector<Driver*> vDriver=driverManager.getVectorDrivers();
    Driver* driver;
    bool existDriver=false;
    for (size_t i=0;i<vDriver.size();i++) {
      if(vDriver[i]->getDriverId()==driveId) {
        existDriver=true;
        driver=vDriver[i];
      }

    }
    if (existDriver) {
    int b;
    int e;
    for ( size_t i=0;i<Drivers.size(); i++){
        if (Drivers[i]->driver==driver) {
            b=Drivers[i]->begin;
            e=Drivers[i]->end;
            if (year>=b && year<=e) return 1;
            if (year==e+1) {
                Drivers[i]->end=year;
                return 0;
            } 
        }
        
    
    }
    DriCons *newDriCons=new DriCons(year,year,driver) ;
    Drivers.push_back(newDriCons);
    return 0;
   }
   return -1;
}


DriverManagement::DriverManagement(){ vectorDrivers.clear();};
DriverManagement::~DriverManagement(){
    while(vectorDrivers.size()!=0)
       {

	  	
            delete (vectorDrivers[vectorDrivers.size()-1]);
            vectorDrivers.pop_back();
                
       } 
    }


vector<Driver*> DriverManagement::getVectorDrivers() const { return vectorDrivers; }

int DriverManagement::driverInsert(Driver* driver)
{
    if (driver==nullptr) return -1;
    for (auto it = vectorDrivers.begin(); it != vectorDrivers.end(); ++it) {
        if ((*it) == driver) {
            return 1;
        }
    }
    vectorDrivers.push_back(driver);
    return -1; 
}

int DriverManagement::driverDelete(int driverId)
{
    for (auto it = vectorDrivers.begin(); it != vectorDrivers.end(); ++it) {
        if ((*it)->getDriverId() == driverId) {
            delete *it; 
            vectorDrivers.erase(it); 
            return 0; 
        }
    }
    return -1; // Series not found
}

ConstructorManagement::ConstructorManagement(){vectorConstructores.clear();};
ConstructorManagement::~ConstructorManagement(){
while(vectorConstructores.size()!=0)
   {   
        while(vectorConstructores[vectorConstructores.size()-1]->getDrivers().size()!=0) {
	vectorConstructores[vectorConstructores.size()-1]->deleteDriver(vectorConstructores[vectorConstructores.size()-1]->getDrivers()[0]->driver->getDriverId());

}
   
        delete (vectorConstructores[vectorConstructores.size()-1]);
        vectorConstructores.pop_back();
            
   } 
}
vector<Constructor*> ConstructorManagement::getVectorConstructores() const { return vectorConstructores; }

int ConstructorManagement::addConstrutor(Constructor* newConstructor)
{
    if(newConstructor==nullptr) return -1;
    auto it=find(vectorConstructores.begin(),vectorConstructores.end(),newConstructor);
    if (it==vectorConstructores.end()) {
        vectorConstructores.push_back(newConstructor);
        return 0;
    }
    return 1;
}


void Driver::displayDriverInfo(ostream& os) const
{

    os << "Displaying driver info:" << endl;
    os << "-----DriverId: " << driverId << endl;
    os << "-----Code: " << code << endl;
    os << "-----Name: " << name << endl;
    os << "-----used numbers: " ;
    for (size_t i = 0; i < numbers.size()-1; ++i) {
        os  << numbers[i] << " " ;
    }
    os  << numbers[numbers.size()-1]<< endl;
    os << "-----Date of birth: " << dateOfBirth << endl;
    os << "-----Country: " << nationality;
   
}



Circuit:: Circuit(int circuitI, string nam, string locat, string  countr, int al):  circuitId(circuitI), name(nam), location(locat), country(countr), alt(al) {};

int Circuit::getCircuitId() const { return circuitId; }

string Circuit::getName() const { return name; }

string Circuit::getLocation() const { return location; }

string Circuit::getCountry() const { return country; }

int Circuit::getAlt() const { return alt; }

void Circuit::displayCircuitInfo(ostream& os) const
{

    os << "Displaying circuit info:" << endl;
    os << "-----CircuitId: " << circuitId << endl;
    os << "-----Name: " << name << endl;
    os << "-----Location: " << location << endl;
    os << "-----Country: " << country << endl;
    os << "-----Altitude: " << alt <<" metros"<< endl;
   
}


CircuitManagement::CircuitManagement(){ listCircuits.clear();};
CircuitManagement::~CircuitManagement(){
    while(listCircuits.size()!=0)
       {

	  	    Circuit* cir=listCircuits.back();
            listCircuits.pop_back();
            delete (cir);
       
                
       } 
    }


list<Circuit*> CircuitManagement::getListCircuits() const { return listCircuits; }

int CircuitManagement::circuitInsert(Circuit* circuit)
{
    if (circuit==nullptr) return -1;
    for (auto it = listCircuits.begin(); it != listCircuits.end(); ++it) {
        if ((*it) == circuit) {
            return 1;
        }
    }
    listCircuits.push_back(circuit);
    return -1; 
}

int CircuitManagement::circuitDelete(int circuitId)
{
    for (auto it = listCircuits.begin(); it != listCircuits.end(); ++it) {
        if ((*it)->getCircuitId() == circuitId) {
            delete *it; 
            listCircuits.erase(it); 
            return 0; 
        }
    }
    return -1; 
}




int ConstructorManagement::updateConstructorDrivers(string filename, DriverManagement& manager)
{
    ifstream file(filename);
   
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return -1;
    }

    string line;
    bool existConstructor=false;
    Constructor* construct;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        int constrId, driId,year;
        string ci,di,ye;
        
        getline(ss, ci, ';');
        getline(ss, di, ';');
        getline(ss, ye, ';');
       
        constrId = stoi(ci);
        driId = stoi(di);
        year = stoi(ye);
        existConstructor=false;
        for ( size_t i=0; i<vectorConstructores.size();i++) {
            if (vectorConstructores[i]->getConstructorId()==constrId) {
                existConstructor=true;
                construct=vectorConstructores[i];
            }
        }
        if (existConstructor==true) {
            
            construct->addDriver(driId,year,manager);
        }

      
    }
    file.close();
   
    return 0;
}


vector<string> ConstructorManagement::DriversAndConstructorsOfOneYear(int year,vector<string> &vConstr) {
    vector<string> vDriver;
    if (year<1900 || year>2025 ) return vDriver;
    vector<string>::iterator it;
    vector<DriCons*> dC;
    for (size_t i=0;i<vectorConstructores.size();i++){
        dC=vectorConstructores[i]->getDrivers();
        for (size_t j=0;j<dC.size();j++) {
            if (year>=dC[j]->begin && year<=dC[j]->end) {
                it=find(vDriver.begin(),vDriver.end(),dC[j]->driver->getName());
                if (it==vDriver.end()) {
                    vDriver.push_back(dC[j]->driver->getName());
                }
                it=find(vConstr.begin(),vConstr.end(),vectorConstructores[i]->getName());
                if (it==vConstr.end()) {
                    vConstr.push_back(vectorConstructores[i]->getName());
                }

            }

        }

    }
    sort(vConstr.begin(),vConstr.end());
    sort(vDriver.begin(),vDriver.end());
    return vDriver;
}


Race:: Race(int raceI, int seas, int roun, Circuit*  circui, string dat):  raceId(raceI), season(seas), round(roun), circuit(circui), date(dat) {};

Race::~Race() {

   while(listRaceResults.size()!=0)
       {

	  	    DriResult* rac=listRaceResults.back();
              listRaceResults.pop_back();
            delete (rac);
       
                
       } 
    }






int Race::getRaceId() const { return raceId; }

int Race::getSeason() const { return season; }

int Race::getRound() const { return round; }

Circuit* Race::getCircuit() const { return circuit; }

string Race::getDate() const { return date; }

list<DriResult*>  Race::getListRaceResults() const { return listRaceResults; }

int Race::addDriverResult(DriResult *driveR, DriverManagement &driManager) {
    if (driveR==nullptr) 
    return -1;
    vector<Driver*> vd=driManager.getVectorDrivers();
    bool exist=false;
   
    for (size_t i=0;i<vd.size();i++){
        if (vd[i]->getDriverId()==driveR->drive->getDriverId()) {
            exist=true;
           
            break;
        }
    }
    
    if (!exist) return -1;
    for (auto it=listRaceResults.begin();it!=listRaceResults.end();it++) {
        if ((*it)->drive==driveR->drive) {
           
            return 1;

        }
    }
    listRaceResults.push_back(driveR);
    return 0;
}



void Race::displayRaceInfo(ostream& os) const
{

    os << "Displaying race info:" << endl;
    os << "-----RaceId: " << raceId << endl;
    os << "-----Season: " << season << endl;
    os << "-----Round: " << round << endl;
    os << "-----CircuitName: " << circuit->getName() << endl;
    os << "-----Date: " << date << endl;
   
}


RaceManagement::RaceManagement(){ listRaces.clear();};
RaceManagement::~RaceManagement(){
    while(listRaces.size()!=0)
       {

	  	    Race* rac=listRaces.back();
              listRaces.pop_back();
            delete (rac);
       
                
       } 
    }


list<Race*> RaceManagement::getListRaces() const { return listRaces; }

int RaceManagement::raceInsert(Race* race)
{
    if (race==nullptr) return -1;
    for (auto it = listRaces.begin(); it != listRaces.end(); ++it) {
        if ((*it) == race) {
            return 1;
        }
    }
    listRaces.push_back(race);
    return -1; 
}

int RaceManagement::raceDelete(int raceId)
{
    for (auto it = listRaces.begin(); it != listRaces.end(); ++it) {
        if ((*it)->getRaceId() == raceId) {
            delete *it; 
            listRaces.erase(it); 
            return 0; 
        }
    }
    return -1; 
}





int RaceManagement::numberRacePerSeason(int nRaces) {
    if (nRaces<1) return -1;
    int count=0,cfim=0;
    int year=1950;
    while(year<2025){
        count=0;
     for(auto it=listRaces.begin();it!=listRaces.end();it++) {
        if ((*it)->getSeason()==year) 
            count++;
     }
     if (count==nRaces)
        cfim++;
    year++;
    
    }
    return cfim;
    
    }
    
    queue<string> RaceManagement::seasonGrandPrix(int year) {
        queue<string> qu;
        if(year<1950 || year>2024) {
            return qu;
        }
        vector<Race*> ve;
        for (auto it=listRaces.begin();it!=listRaces.end();it++) {
            if ((*it)->getSeason()==year) {
                ve.push_back(*it);
            }
    
        }
        int i=1;
       
        while (!ve.empty()) {
              
                for(size_t j=0;j!=ve.size();j++) {
                if (ve[j]->getRound()==i) {
                    
    
                    qu.push(ve[j]->getCircuit()->getName());
                    ve.erase(ve.begin()+j);
                    j--;
                    i++;
                }
                }
               
    
    
        }
        return qu;
    }
    
    int RaceManagement::uploadFromFile(string filename, DriverManagement &driManager, ConstructorManagement &consManager) {
        
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open allresults.csv file." << endl;
            return -1;
        }
        int count=0, tip;
        string line;
       
        Race* rac;
        Driver* dri;
        DriResult * dr;
        Constructor *constr;
        stringstream ss;
        //raceId;driverId;constructorId;number;grid;position;laps;statusId
        int raceI,driveI,constructorI,numbe,gri,positio,lap,statusI;
       // Circuit* cir=NULL;
        vector<Driver*> vd=driManager.getVectorDrivers();
        vector<Constructor*> vc=consManager.getVectorConstructores();
        while (getline(file, line)) {
            
            string read;
            
                
            ss.clear();
            ss << line; 
        
            
            
            getline(ss, read, ';');
            raceI=stoi(read);
            
            getline(ss, read, ';');
            driveI=stoi(read);
         
            getline(ss, read, ';');
            constructorI=stoi(read);
            getline(ss, read, ';');
            numbe=stoi(read);
            getline(ss, read, ';');
            gri=stoi(read);
            
            getline(ss, read, ';');
            positio=stoi(read);
           
            getline(ss, read, ';');
            lap=stoi(read);
            getline(ss, read, ';');
            statusI=stoi(read);
            dri=nullptr;
            constr=nullptr;
            
            for (auto it=vd.begin();it!=vd.end();it++){
                if ((*it)->getDriverId()==driveI) {
                    dri=(*it);
                }
            }
            for (auto it1=vc.begin();it1!=vc.end();it1++){
                if ((*it1)->getConstructorId()==constructorI) {
                    constr=(*it1);
                }
            }
           
            if (dri!=nullptr && constr!=nullptr) {
            rac=nullptr;
            for (auto it2=listRaces.begin();it2!=listRaces.end();it2++) {
                if ((*it2)->getRaceId()==raceI) {
                    rac=*it2;
                }
            }
            if (rac!=nullptr) {
            
            
            dr = new DriResult(dri,constr,numbe,gri,positio,lap,statusI);
            tip=rac->addDriverResult(dr,driManager);
            if (tip==0)
            count++;
             }
            }
        }
       
        
        file.close();
    
    
        return count;
    
    
    
    }
    
    string RaceManagement::driverStatus(string status, int &num) {
        if (status.empty()) {
            return "";
        }
        int sta=0;
        for (size_t i=0;i<N_STATUS;i++) {
            if (vStauts[i]==status) {
                sta=i;
            }
        }
        if (sta==0) return "";
        string result="";
    
        vector<pair<string,int>> vresult;
        list<DriResult*> ldr;
        string dId;
        bool exist=false;
        for (auto it=listRaces.begin();it!=listRaces.end();it++) {
            ldr=(*it)->getListRaceResults();
            for (auto it2=ldr.begin();it2!=ldr.end();it2++) {
                if ((*it2)->status==sta) {
                    dId=(*it2)->drive->getName();
                    exist=false;
                    for (size_t i=0;i<vresult.size();i++) {
                        if (vresult[i].first==dId) {
                          exist=true;
                          vresult[i].second++;
                        }
                    }
                    if (!exist) {
                        vresult.push_back({dId,1});
                    }
    
                }
            }
        }
        int max=0; 
        for (size_t i=0;i<vresult.size();i++) {
            if (vresult[i].second>max) {
                max=vresult[i].second;
                result=vresult[i].first;
            } else if (vresult[i].second>max && vresult[i].first<result) {
                max=vresult[i].second;
                result=vresult[i].first;
            }
        }
        num=max;
        return result;
    }
    
    int RaceManagement::scoreCareer (int driveI, DriverManagement &drivManager, int &ngrids) {
    
    bool exist=false;
    vector<Driver*> vd=drivManager.getVectorDrivers();
    for(auto it=vd.begin();it!=vd.end();it++) {
        if ((*it)->getDriverId()==driveI)
         exist=true;
    }
    if (!exist) return -1;
    ngrids=0;
    vector<int> v50{0,8,6,4,3,2};
    vector<int> v60{0,9,6,4,3,2,1};
    vector<int> v91{0,10,6,4,3,2,1};
    vector<int> v03{0,10,8,6,5,4,3,2,1};
    vector<int> v10{0,25,18,15,12,10,8,6,4,2,1};
    list<DriResult*> ld;
    DriResult * dr=NULL;
    Race * rc=NULL;
    int count=0;
    for(auto it2=listRaces.begin();it2!=listRaces.end();it2++) {
        ld=(*it2)->getListRaceResults();
        rc=(*it2);
        for ( auto it3=ld.begin();it3!=ld.end();it3++) {
            dr=(*it3);
            if (dr->drive->getDriverId()==driveI) {
                if (rc->getSeason()<1960) {
                    if (dr->position<6)
                    count+=v50[dr->position];
                }
                if (rc->getSeason()>1959 && rc->getSeason()<1991) {
                    if (dr->position<7)
                    count+=v60[dr->position];
                }
                if (rc->getSeason()>1990 && rc->getSeason()<2003) {
                    if (dr->position<7)
                    count+=v91[dr->position];
                }
                if (rc->getSeason()>2002 && rc->getSeason()<2010) {
                    if (dr->position<9)
                    count+=v03[dr->position];
                }
                if (rc->getSeason()>2009) {
                    if (dr->position<11)
                    count+=v10[dr->position];
                }
                if (dr->grid==1) ngrids++;
            }
        }
    
    }
    return count;
    }
    
    string RaceManagement::moreTimesNumber(int number,int &count) {
        list<DriResult*> dr;
    
        if (number<1 || number >199) return "";
        vector<pair<string,int>> vaux;
        bool exist=false;
        for (Race* rac:listRaces) {
            dr=rac->getListRaceResults();
            for (DriResult* dresult:dr){
             if  (dresult->number==number) {
                exist=false;
                for (pair<string,int> &p:vaux) {
                   
                    if (p.first==dresult->constructor->getName()) {
                    
                        p.second++;
                        exist=true;
                    }
                }
                if (!exist) {
                    vaux.push_back(make_pair(dresult->constructor->getName(),1));
                }
    
                break;
             }
            }
    
        }
        int max=0;
        string name="";
        for (pair<string,int> p:vaux) {
     
            if (p.second>max || (p.second==max && p.first<name)) {
                max=p.second;
                name=p.first;
            }
        }
        count=max;
        return name;
    }
    
    priority_queue<Qualifying,vector<Qualifying>, greater<Qualifying>> RaceManagement::startingGrid(vector<Qualifying> &vQ) {
        priority_queue<Qualifying,vector<Qualifying>, greater<Qualifying>> pq;
        if (vQ.empty()) return pq;
    
        priority_queue<Qualifying,vector<Qualifying>, greater<Qualifying>> pqaux;
        vector<Qualifying> vaux;
        Qualifying qaux;
        bool exist=false;
      //  pqaux.push(qaux);
      for (size_t i=0;i<vQ.size();i++) {
            pqaux.push(vQ[i]);
        } 
    
        while (!pqaux.empty()) {
            qaux=pqaux.top();
            exist=false;
            for (size_t j=0;j<vaux.size();j++) {
                if (vaux[j].driver->getDriverId()==qaux.driver->getDriverId()) {
    
                    exist=true;
                    break;
                }
            }
            if (!exist) {
                pq.push(qaux);
                vaux.push_back(qaux);
            }
            pqaux.pop();
        } 
        return pq;
    }
     
RaceManagementTree::RaceManagementTree() {
    root=nullptr;
}

RaceManagementTree::~RaceManagementTree() {
    delete root;
}
    
NodeRace* RaceManagementTree::findMinNode(NodeRace* node) {
    NodeRace* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
    }

NodeRace* RaceManagementTree::deleteNode(NodeRace* root, int raceSeason, int round) {
    // Base case: empty tree
    if (root == nullptr) {
        return root;
    }

    // If the raceSeason to be deleted is smaller than the season of the current node, search the left subtree
    if (raceSeason < root->race->getSeason()) {
        root->left = deleteNode(root->left, raceSeason,round);
    }
    // If the raceSeason to be deleted is greater than the season of the current node, search the right subtree
    else if (raceSeason > root->race->getSeason()) {
        root->right = deleteNode(root->right, raceSeason,round);
    }
    else if (round <root->race->getRound()) {
        root->left = deleteNode(root->left, raceSeason,round);
    }
    else if (round > root->race->getRound()) {
        root->right = deleteNode(root->right, raceSeason,round);
    } else     // If the user is the same as the year of the current node, this is the node to be deleted

    {
        // Case 1: node without children or with only one child
        if (root->left == nullptr) {
                NodeRace* temp = root->right;
                delete root;
                return temp;
        } else if (root->right == nullptr) {
                NodeRace* temp = root->left;
                delete root;
                return temp;
            }

        // Case 2: node with two children
        // Finds the minimum node of the right subtree (the successor)
        NodeRace* temp = findMinNode(root->right);
        // Copy successor to this node
        root->race = temp->race;
        // Exclui o sucessor
        root->right = deleteNode(root->right, temp->race->getSeason(),temp->race->getRound());
        }
    return root;
}

void RaceManagementTree::inorderTraversal(NodeRace* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->race->getSeason() << "-" << root->race->getRound() << "º GP de " << root->race->getCircuit()->getName()<< endl;
        inorderTraversal(root->right);
    }
}

NodeRace* RaceManagementTree::getRoot() const
{
    return root;
}

void RaceManagementTree::addRace(Race* newracer) {
 
    root = insertNode(root, newracer);

}

void RaceManagementTree::remove( int raceSeason, int round) {
        root = deleteNode(root, raceSeason,round);
    }

void RaceManagementTree::inorder() {
        inorderTraversal(root);
    }



    NodeRace* RaceManagementTree::insertNode(NodeRace* root, Race* newRace) {
        // If the tree is empty, create a new node and return it
        if (root == nullptr) {
           
            return new NodeRace(newRace);
        }
    
        // Compares username to decide where to insert the node
        if (newRace->getSeason() < root->race->getSeason()) {
            root->left = insertNode(root->left, newRace);
        } else if (newRace->getSeason() > root->race->getSeason()) {
            root->right = insertNode(root->right, newRace);
        } else if (newRace->getRound() < root->race->getRound()) {
            root->left = insertNode(root->left, newRace);
        } else if (newRace->getRound() > root->race->getRound()) {
            root->right = insertNode(root->right, newRace);
        }
        return root;
    }
    
    
    vector<pair<string,int>> RaceManagementTree::driverVictoriesGP(NodeRace* root,int circuitId) {
       vector<pair<string,int>> vres, vresLeft,vresRight;
        if (root==nullptr) {
        return vres;
       }
       if (root->race->getCircuit()->getCircuitId()==circuitId){
            for (DriResult* dr:root->race->getListRaceResults()) {
                if (dr->position==1) {
                    vres.push_back(make_pair(dr->drive->getName(),1));
                }
            }
    
       }
       vresLeft=driverVictoriesGP(root->left,circuitId);
       bool exist=false;
       for (pair<string,int> &l:vresLeft) {
    
            for (pair<string,int> &r:vres ) {
                if (l.first==r.first) {
                exist=true;
                r.second=l.second+r.second;
                }
            }
            if (!exist) 
                vres.push_back(l);
       }
       vresRight=driverVictoriesGP(root->right,circuitId);
       for (pair<string,int> &l:vresRight) {
    
        for (pair<string,int> &r:vres ) {
            if (l.first==r.first) {
            exist=true;
            r.second=l.second+r.second;
            }
        }
        if (!exist) 
            vres.push_back(l);
    }
      pair<string,int> pmax;
      int k;
     
      if (vres.size()>1) {
      for (size_t i=0;i<vres.size()-1;i++) {
       pmax=vres[i];
     
        k=i;
         for (size_t j=i+1;j<vres.size();j++) {
            if ((vres[j].second>pmax.second) || ((vres[j].second==pmax.second) && (vres[j].first<pmax.first))) {
                pmax=vres[j];
                k=j;
            }
         } 
         swap(vres[k],vres[i]);
      } 
    }
      return vres; 
    }
    
    
    string RaceManagementTree::bestPerformance(NodeRace* root,int season,int round,int &grid, int&position) {
      if (root==nullptr) {
    
        return "";
      }
      string name="";
      int bt=-1,dif,p=50;
    
      if (root->race->getSeason()==season && root->race->getRound()==round) {
      
        for (DriResult *dr:root->race->getListRaceResults()) {
            dif=dr->grid-dr->position;
            if ((dr->position!=-1) &&( dif>bt || (dif==bt && dr->position<p))) {
                bt=dif;
                name=dr->drive->getName();
                p=dr->position;
                grid=dr->grid;
                position=dr->position;
            }
        }
       return name;
      } else if (season<root->race->getSeason()) {
     
           return bestPerformance(root->left,season,round,grid,position);
      } else if (season>root->race->getSeason()) {
        
        return bestPerformance(root->right,season,round,grid,position);
    } else if (round <root->race->getRound()) {
        return bestPerformance(root->left,season,round,grid,position);
    } else if (round>root->race->getRound()) {
     return bestPerformance(root->right,season,round,grid,position);
    }
    
      return name;
    }

ConstructorGraph::ConstructorGraph()
    {
        totalConstructors = 0;
        constructorNodes.clear();
        network.clear();
    }
    
size_t ConstructorGraph::getTotal() const
    {
        return totalConstructors;
    }
    
vector<Constructor*> ConstructorGraph::getConstructorNodes() const
    {
        return constructorNodes;
    }
    
vector<list<TransferData*>> ConstructorGraph::getNetwork() const
    {
        return network;
    }
    
int ConstructorGraph::addConstructorNode(Constructor* constructorPtr)
    {
        if (!constructorPtr) return -1;
    
        if (constructorPosition(constructorPtr) >= 0) return 1; // Constructor already exists in the graph
        
        constructorNodes.push_back(constructorPtr);
        network.resize(constructorNodes.size());
        totalConstructors = constructorNodes.size();
        return 0;
    }
    
int ConstructorGraph::constructorPosition(Constructor* constructorPtr)
    {
        if (!constructorPtr) return -2;
    
        auto it = find( constructorNodes.begin(), constructorNodes.end(), constructorPtr);
        if (it == constructorNodes.end()) return -1; // Node does not exist
    
        return it - constructorNodes.begin();
    }
    
int ConstructorGraph::addTranfer(Constructor* ConstructorA, TransferData* Transf)
    {
        if (!ConstructorA || !Transf) return -1;
    
        int posA = constructorPosition(ConstructorA), posB = constructorPosition(Transf->constructor);
    
        if (posA == -2 || posB == -2) return -1; // Error
    
        // Check if the nodes exist
        if (posA == -1) {
            addConstructorNode(ConstructorA); // Add ConstructorA
            posA = constructorPosition(ConstructorA); // Update posA with ConstructorA position
        }
        if (posB == -1) {
            addConstructorNode(Transf->constructor); // Add Transf->constructor
            posB = constructorPosition(Transf->constructor); // Update posB with Transf->constructor position
        }
    
        // Check if the edge already exists
        for (auto &tf:network.at(posA)) {
        if (tf->constructor==Transf->constructor) 
        {
        tf->numDrivers= tf->numDrivers+Transf->numDrivers;   
        tf->pointsDiff= tf->pointsDiff+Transf->pointsDiff; 
       tf->winsDiff= tf->winsDiff+Transf->winsDiff; 
        return 1; 
        }
        }
        network.at(posA).push_back(Transf);
        return 0;
    }
    
int ConstructorGraph::removeTransfer(Constructor* ConstructorA, Constructor* ConstructorB)
    {
        if (!ConstructorA || !ConstructorB) return -1;
    
        int posA = constructorPosition(ConstructorA), posB = constructorPosition(ConstructorB);
    
        if (posA == -1 || posB == -1 || posA == -2 || posB == -2) return -1; // Error
    
        // Check if the edge does not exist
        for (auto it=network.at(posA).begin();it!=network.at(posA).end();it++){
            if ((*it)->constructor==ConstructorB) {
                network.at(posA).erase(it);
                return 0;  

            }

        }
       
        return 1;
    }
    
    void ConstructorGraph::printGraph()
    {
        for (int i = 0; i < (int) totalConstructors; i++) {
            cout << "(" << i << ") " << constructorNodes.at(i)->getName() << " -> ";
    
            size_t j = 0;
            for (auto u_follow : network.at(i)){
                cout << u_follow->constructor->getName() << "( "<<u_follow->pointsDiff<<","<<u_follow->winsDiff<<","<<u_follow->numDrivers<<")";
                j++;
                if (j != network.at(i).size()) cout << " | ";
            }
            cout << endl;
        }
        cout << endl;
    } 




/**************************/
/*     A implementar      */
/**************************/

Constructor* ConstructorGraph::worstVictories(Constructor* constructorA) {

return nullptr;
}

Constructor* ConstructorGraph::moreDrivers(Constructor* constructorB) {
return nullptr;
}

vector<string> ConstructorGraph::noConnection ( Constructor* constructorA ) {
  
return {};
}

int ConstructorGraph::updateTransfersOfYear(int year,  RaceManagement &RaM) {

    return -1;
}


F1APP::F1APP()
{
    
}


void F1APP::updateF1APP(DriverManagement &drM, ConstructorManagement &coM, CircuitManagement &ciM, RaceManagement &raM) {

}

Driver* F1APP::mostRaceFinish(int yearA, int yearB) {

return nullptr;
}

list<string> F1APP::pointsWidthoutWon(Circuit* cir) {

return {};
}

string F1APP::poleToWin() {

return "";
}

Constructor * F1APP::mostRaceNotPole(int yearA, int yearB) {
 
return nullptr;

};
vector<pair<string,int>> F1APP::classificationBySeason(int season){

return {};
}