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
int getPointsForPosition(int position, int season) {
    if (position <= 0) return 0;

    if (season < 1960) {
        const vector<int> points_vec = {0, 8, 6, 4, 3, 2}; 
        if (position > 0 && position < (int)points_vec.size()) return points_vec[position];
    } else if (season >= 1960 && season < 1991) {
        const vector<int> points_vec = {0, 9, 6, 4, 3, 2, 1};
        if (position > 0 && position < (int)points_vec.size()) return points_vec[position];
    } else if (season >= 1991 && season < 2003) {
        const vector<int> points_vec = {0, 10, 6, 4, 3, 2, 1};
        if (position > 0 && position < (int)points_vec.size()) return points_vec[position];
    } else if (season >= 2003 && season < 2010) {
        const vector<int> points_vec = {0, 10, 8, 6, 5, 4, 3, 2, 1};
        if (position > 0 && position < (int)points_vec.size()) return points_vec[position];
    } else if (season >= 2010) {
        const vector<int> points_vec = {0, 25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
        if (position > 0 && position < (int)points_vec.size()) return points_vec[position];
    }
    return 0;
}

bool isStrictlyFinished(int statusId) {
    return statusId == 1; // vStauts[1] is "Finished"
}

bool isRaceCompletedInclusively(int statusId) {
    if (statusId < 0 || statusId >= N_STATUS) return false;
    if (statusId == 1) return true; 
    
    const string& statusString = vStauts[statusId]; 
    if (!statusString.empty() && statusString[0] == '+' && statusString.find("Lap") != string::npos) {
        return true; 
    }
    return false;
}


Constructor* ConstructorGraph::worstVictories(Constructor* constructorA) { 
    if (!constructorA) return nullptr;
    int posA = constructorPosition(constructorA);
    if (posA < 0 || posA >= (int)network.size() || network[posA].empty()) return nullptr;

    Constructor* result_constructor = nullptr;
    // "Pior diferença de vitórias" interpreted as largest positive winsDiff (SourceWins - TargetWins_A)
    // This means A performed much worse than the source team regarding wins with these drivers.
    int max_deficit_wins_diff = -numeric_limits<int>::max(); // Initialize to a very small number
    int associated_max_deficit_points_diff = -numeric_limits<int>::max();

    for (TransferData* td : network[posA]) {
        if (!td || !td->constructor) continue;

        // Primary criterion: "Pior (largest positive) diferença de vitórias"
        if (result_constructor == nullptr || td->winsDiff > max_deficit_wins_diff) {
            max_deficit_wins_diff = td->winsDiff;
            associated_max_deficit_points_diff = td->pointsDiff;
            result_constructor = td->constructor;
        } else if (td->winsDiff == max_deficit_wins_diff) {
            // Tie in winsDiff, check "pior (largest positive) diferença de pontos"
            if (td->pointsDiff > associated_max_deficit_points_diff) {
                associated_max_deficit_points_diff = td->pointsDiff;
                result_constructor = td->constructor;
            } else if (td->pointsDiff == associated_max_deficit_points_diff) {
                // Tie in both, choose alphabetically smaller constructor name
                if (td->constructor->getName() < result_constructor->getName()) {
                    result_constructor = td->constructor;
                }
            }
        }
    }
    return result_constructor;
}

Constructor* ConstructorGraph::moreDrivers(Constructor* constructorB_source) { 
    if (!constructorB_source) return nullptr;

    Constructor* result_constructor = nullptr;
    int max_drivers = -1;
    int best_points_diff = numeric_limits<int>::min();
    int best_wins_diff = numeric_limits<int>::min();

    for (size_t i = 0; i < totalConstructors; ++i) {
        Constructor* receiver_candidate = constructorNodes[i];
        if (receiver_candidate == constructorB_source) continue; 
        if (i >= network.size()) continue; 

        for (TransferData* td : network[i]) {
            if (td && td->constructor == constructorB_source) { 
                if (result_constructor == nullptr || td->numDrivers > max_drivers) {
                    max_drivers = td->numDrivers;
                    best_points_diff = td->pointsDiff;
                    best_wins_diff = td->winsDiff;
                    result_constructor = receiver_candidate;
                } else if (td->numDrivers == max_drivers) {
                    if (td->pointsDiff > best_points_diff) {
                        best_points_diff = td->pointsDiff;
                        best_wins_diff = td->winsDiff;
                        result_constructor = receiver_candidate;
                    } else if (td->pointsDiff == best_points_diff) {
                        if (td->winsDiff > best_wins_diff) {
                            best_wins_diff = td->winsDiff;
                            result_constructor = receiver_candidate;
                        } else if (td->winsDiff == best_wins_diff) {
                            if (receiver_candidate->getName() < result_constructor->getName()) {
                                result_constructor = receiver_candidate;
                            }
                        }
                    }
                }
            }
        }
    }
    return result_constructor;
}

vector<string> ConstructorGraph::noConnection(Constructor* constructorA) { 
    vector<string> result_names;
    if (!constructorA) return result_names;
    int posA = constructorPosition(constructorA);
    if (posA < 0) return result_names;

    vector<bool> is_connected(totalConstructors, false);

    if(posA < (int)network.size()){
        for (TransferData* td : network[posA]) {
            if (td && td->constructor) {
                int pos_source = constructorPosition(td->constructor);
                if (pos_source >= 0) is_connected[pos_source] = true;
            }
        }
    }

    for (size_t i = 0; i < totalConstructors; ++i) {
        if (i == (size_t)posA) continue; 
        if(i < network.size()){
            for (TransferData* td : network[i]) {
                if (td && td->constructor == constructorA) {
                    is_connected[i] = true;
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < totalConstructors; ++i) {
        if (i == (size_t)posA) continue; 
        if (!is_connected[i] && constructorNodes[i]) { 
            result_names.push_back(constructorNodes[i]->getName());
        }
    }
    sort(result_names.begin(), result_names.end());
    return result_names;
}

int ConstructorGraph::updateTransfersOfYear(int year, RaceManagement &RaM) {
    if (year < 1950 || year > 2050) return -1;

    vector<pair<Driver*, pair<Constructor*, pair<int, int>>>> prev_year_info;
    vector<pair<Driver*, pair<Constructor*, pair<int, int>>>> curr_year_info;

    auto get_driver_data_entry = [](vector<pair<Driver*, pair<Constructor*, pair<int, int>>>>& vec, Driver* d) 
                                    -> pair<Constructor*, pair<int, int>>* {
        for(auto& entry : vec) {
            if(entry.first == d) return &entry.second;
        }
        return nullptr;
    };
    
    auto add_or_update_driver_data = [&](vector<pair<Driver*, pair<Constructor*, pair<int, int>>>>& vec, 
                                           Driver* d, Constructor* c, int points, int wins) {
        pair<Constructor*, pair<int, int>>* data = get_driver_data_entry(vec, d);
        if(data) {
            if(data->first == nullptr && c != nullptr) data->first = c; 
            data->second.first += points;
            data->second.second += wins;
        } else {
            if(d) vec.push_back({d, {c, {points, wins}}});
        }
    };

    for (Race* r : RaM.getListRaces()) {
        if (!r) continue;
        int race_season = r->getSeason();
        if (race_season != year - 1 && race_season != year) continue;

        for (DriResult* dr : r->getListRaceResults()) {
            if (!dr || !dr->drive || !dr->constructor) continue;
            int points = getPointsForPosition(dr->position, race_season);
            int wins = (dr->position == 1);

            if (race_season == year - 1) {
                add_or_update_driver_data(prev_year_info, dr->drive, dr->constructor, points, wins);
            } else { 
                add_or_update_driver_data(curr_year_info, dr->drive, dr->constructor, points, wins);
            }
        }
    }

    int transfers_count = 0;
    for (const auto& prev_entry : prev_year_info) {
        Driver* driver = prev_entry.first;
        Constructor* c_prev = prev_entry.second.first;
        int p_prev = prev_entry.second.second.first;
        int w_prev = prev_entry.second.second.second;

        pair<Constructor*, pair<int, int>>* curr_data = get_driver_data_entry(curr_year_info, driver);

        if (curr_data) {
            Constructor* c_curr = curr_data->first;
            int p_curr = curr_data->second.first;
            int w_curr = curr_data->second.second;

            if (c_prev && c_curr && c_prev != c_curr) { 
                addConstructorNode(c_curr);
                addConstructorNode(c_prev);
                TransferData* td = new TransferData(c_prev, p_prev - p_curr, w_prev - w_curr, 1);
                addTranfer(c_curr, td); 
                transfers_count++; 
            }
        }
    }
    return transfers_count;
}

F1APP::F1APP() : drM_ref(nullptr), coM_ref(nullptr), ciM_ref(nullptr), raM_ref(nullptr) {
    app_driver_race_logs.clear();
    app_constructor_wins_not_pole.clear();
    app_circuit_stats.clear();
    app_circuit_driver_performances.clear();
    app_season_driver_points.clear();
}

void F1APP::updateF1APP(DriverManagement &drM, ConstructorManagement &coM, CircuitManagement &ciM, RaceManagement &raM) {
    this->drM_ref = &drM;
    this->coM_ref = &coM;
    this->ciM_ref = &ciM;
    this->raM_ref = &raM;

    app_driver_race_logs.clear();
    app_constructor_wins_not_pole.clear();
    app_circuit_stats.clear();
    app_circuit_driver_performances.clear();
    app_season_driver_points.clear();
    
    vector<int> processed_race_ids_for_circuit_totals;

    if (!this->raM_ref) return;

    for (Race* r : this->raM_ref->getListRaces()) {
        if (!r || !r->getCircuit()) continue;
        int current_season = r->getSeason();
        int current_round = r->getRound();
        Circuit* current_circuit = r->getCircuit();

        F1APPCircuitStats* circuit_stat_entry_ptr = nullptr;
        for(auto& entry : app_circuit_stats) {
            if(entry.first == current_circuit) { circuit_stat_entry_ptr = &entry.second; break;}
        }
        if(!circuit_stat_entry_ptr) { 
            app_circuit_stats.push_back({current_circuit, F1APPCircuitStats()}); 
            circuit_stat_entry_ptr = &app_circuit_stats.back().second;
        }

        bool race_already_counted_for_total = false;
        for(int rid : processed_race_ids_for_circuit_totals) {
            if(rid == r->getRaceId()) { race_already_counted_for_total = true; break; }
        }
        if(!race_already_counted_for_total && circuit_stat_entry_ptr) {
            circuit_stat_entry_ptr->total_races++;
            processed_race_ids_for_circuit_totals.push_back(r->getRaceId());
        }

        for (DriResult* dr : r->getListRaceResults()) {
            if (!dr || !dr->drive || !dr->constructor) continue;
            Driver* driver = dr->drive;
            Constructor* constructor = dr->constructor;
            int points_for_race = getPointsForPosition(dr->position, current_season);

            // 1. Populate app_driver_race_logs
            vector<F1APPDriverRaceLog>* driver_logs_ptr = nullptr;
            for(auto& entry : app_driver_race_logs) {
                if(entry.first == driver) { driver_logs_ptr = &entry.second; break; }
            }
            if(!driver_logs_ptr) { 
                app_driver_race_logs.push_back({driver, {}});
                driver_logs_ptr = &app_driver_race_logs.back().second;
            }
            // MODIFIED for mostRaceFinish: use inclusive check for "not an abandon"
            if(driver_logs_ptr) driver_logs_ptr->push_back({current_season, current_round, isRaceCompletedInclusively(dr->status)});


            // 2. Populate app_constructor_wins_not_pole
            if (dr->position == 1 && dr->grid != 1) {
                vector<F1APPConstructorSeasonWin>* constructor_wins_ptr = nullptr;
                for(auto& entry : app_constructor_wins_not_pole) {
                    if(entry.first == constructor) { constructor_wins_ptr = &entry.second; break;}
                }
                if(!constructor_wins_ptr) { 
                    app_constructor_wins_not_pole.push_back({constructor, {}});
                    constructor_wins_ptr = &app_constructor_wins_not_pole.back().second;
                }
                if(constructor_wins_ptr) constructor_wins_ptr->push_back({current_season});
            }

            // 3. Populate app_circuit_stats (pole_wins part)
            if (dr->position == 1 && dr->grid == 1 && circuit_stat_entry_ptr) {
                 circuit_stat_entry_ptr->pole_wins++;
            }
            
            // 4. Populate app_circuit_driver_performances
            vector<pair<Driver*, vector<F1APPDriverCircuitPerformance>>>* circuit_drivers_perf_vec_ptr = nullptr;
            for(auto& entry : app_circuit_driver_performances){
                if(entry.first == current_circuit){ circuit_drivers_perf_vec_ptr = &entry.second; break;}
            }
            if(!circuit_drivers_perf_vec_ptr){ 
                app_circuit_driver_performances.push_back({current_circuit, {}});
                circuit_drivers_perf_vec_ptr = &app_circuit_driver_performances.back().second;
            }
            vector<F1APPDriverCircuitPerformance>* driver_perf_on_circuit_ptr = nullptr;
            for(auto& entry : *circuit_drivers_perf_vec_ptr) {
                if(entry.first == driver) { driver_perf_on_circuit_ptr = &entry.second; break;}
            }
            if(!driver_perf_on_circuit_ptr) { 
                circuit_drivers_perf_vec_ptr->push_back({driver, {}});
                driver_perf_on_circuit_ptr = &circuit_drivers_perf_vec_ptr->back().second;
            }
            if(driver_perf_on_circuit_ptr) driver_perf_on_circuit_ptr->push_back({dr->position, isRaceCompletedInclusively(dr->status), points_for_race});
            
            // 5. Populate app_season_driver_points
            vector<pair<Driver*, int>>* season_total_points_vec_ptr = nullptr;
            for(auto& entry : app_season_driver_points){
                if(entry.first == current_season){ season_total_points_vec_ptr = &entry.second; break;}
            }
            if(!season_total_points_vec_ptr){ 
                app_season_driver_points.push_back({current_season, {}});
                season_total_points_vec_ptr = &app_season_driver_points.back().second;
            }
            int* driver_total_points_ptr = nullptr;
            for(auto& entry : *season_total_points_vec_ptr) {
                if(entry.first == driver) {driver_total_points_ptr = &entry.second; break;}
            }
            if(!driver_total_points_ptr){ 
                season_total_points_vec_ptr->push_back({driver, 0});
                driver_total_points_ptr = &season_total_points_vec_ptr->back().second;
            }
            if(driver_total_points_ptr) *driver_total_points_ptr += points_for_race;
        }
    }
    
    for(auto& entry : app_driver_race_logs){
        sort(entry.second.begin(), entry.second.end(), [](const F1APPDriverRaceLog& a, const F1APPDriverRaceLog& b){
            if(a.season != b.season) return a.season < b.season;
            return a.round < b.round;
        });
    }
}

Driver* F1APP::mostRaceFinish(int yearA, int yearB) {
    if (yearA > yearB || !this->drM_ref) return nullptr;

    Driver* best_driver_ptr = nullptr;
    int max_overall_streak = 0;

    for (const auto& driver_log_pair : this->app_driver_race_logs) {
        Driver* current_driver = driver_log_pair.first;
        const vector<F1APPDriverRaceLog>& logs = driver_log_pair.second;

        int current_driver_streak = 0;
        int current_driver_max_streak_in_period = 0;

        for (const auto& log : logs) {
            if (log.season >= yearA && log.season <= yearB) {
                if (log.completed_no_abandon) { 
                    current_driver_streak++;
                } else {
                    current_driver_max_streak_in_period = max(current_driver_max_streak_in_period, current_driver_streak);
                    current_driver_streak = 0;
                }
            } else if (log.season < yearA) { 
                 current_driver_streak = 0; 
            } else if (log.season > yearB ) { 
                 current_driver_max_streak_in_period = max(current_driver_max_streak_in_period, current_driver_streak);
                 current_driver_streak = 0; 
                 break; 
            }
        }
        current_driver_max_streak_in_period = max(current_driver_max_streak_in_period, current_driver_streak);

        if (current_driver_max_streak_in_period > max_overall_streak) {
            max_overall_streak = current_driver_max_streak_in_period;
            best_driver_ptr = current_driver;
        } else if (current_driver_max_streak_in_period == max_overall_streak && max_overall_streak > 0) { 
            if (best_driver_ptr == nullptr || (current_driver && current_driver->getName() < best_driver_ptr->getName())) {
                best_driver_ptr = current_driver;
            }
        }
    }
    return best_driver_ptr;
}

Constructor* F1APP::mostRaceNotPole(int yearA, int yearB) {
    if (yearA > yearB || !this->coM_ref) return nullptr;

    vector<pair<Constructor*, int>> counts_in_period; 

    for(const auto& cons_wins_pair : this->app_constructor_wins_not_pole){
        Constructor* constructor = cons_wins_pair.first;
        const auto& wins_log = cons_wins_pair.second; 
        
        int wins_in_period_for_this_constructor = 0;
        for(const auto& win_event : wins_log){
            if(win_event.season >= yearA && win_event.season <= yearB){
                wins_in_period_for_this_constructor++;
            }
        }

        if(wins_in_period_for_this_constructor > 0){
            bool found = false;
            for(auto& entry : counts_in_period){ 
                if(entry.first == constructor){ 
                    entry.second += wins_in_period_for_this_constructor; 
                    found = true;
                    break;
                }
            }
            if(!found) {
                counts_in_period.push_back({constructor, wins_in_period_for_this_constructor});
            }
        }
    }

    if (counts_in_period.empty()) return nullptr;

    sort(counts_in_period.begin(), counts_in_period.end(), 
        [](const pair<Constructor*, int>& a, const pair<Constructor*, int>& b){
        if(a.second != b.second) return a.second > b.second; 
        return a.first->getName() < b.first->getName(); 
    });
    
    return counts_in_period[0].first; 
}

string F1APP::poleToWin() {
    if (this->app_circuit_stats.empty()) return "";

    string best_circuit_name = "";
    double max_ratio = -1.0;
    
    vector<pair<Circuit*, F1APPCircuitStats>> sorted_circuit_stats_for_query = this->app_circuit_stats;
    sort(sorted_circuit_stats_for_query.begin(), sorted_circuit_stats_for_query.end(), 
       [](const pair<Circuit*, F1APPCircuitStats>&a, const pair<Circuit*, F1APPCircuitStats>&b){
           if (!a.first || !b.first) return a.first < b.first; 
           return a.first->getName() < b.first->getName();
    });

    for (const auto& entry : sorted_circuit_stats_for_query) {
        Circuit* circuit = entry.first;
        const F1APPCircuitStats& stats = entry.second;
        if (!circuit || stats.total_races == 0) continue;

        double current_ratio = static_cast<double>(stats.pole_wins) / stats.total_races;

        if (current_ratio > max_ratio) {
            max_ratio = current_ratio;
            best_circuit_name = circuit->getName();
        } 
    }
    return best_circuit_name;
}

list<string> F1APP::pointsWidthoutWon(Circuit* cir) {
    list<string> result_driver_names;
    if (!cir || !this->drM_ref) return result_driver_names;

    const vector<pair<Driver*, vector<F1APPDriverCircuitPerformance>>>* driver_performances_on_circuit_ptr = nullptr;
    for(const auto& circuit_entry : this->app_circuit_driver_performances){
        if(circuit_entry.first == cir){
            driver_performances_on_circuit_ptr = &circuit_entry.second;
            break;
        }
    }

    if(!driver_performances_on_circuit_ptr) return result_driver_names; 

    const vector<pair<Driver*, vector<F1APPDriverCircuitPerformance>>>& driver_performances_on_circuit = *driver_performances_on_circuit_ptr;

    for (const auto& driver_perf_pair : driver_performances_on_circuit) {
        Driver* driver = driver_perf_pair.first;
        const vector<F1APPDriverCircuitPerformance>& performances = driver_perf_pair.second;

        if (!driver || performances.empty()) continue;

        int wins_on_circuit = 0;
        int finished_races_count = 0;
        int finished_with_points_count = 0;

        for (const auto& perf : performances) {
            if (perf.position == 1) wins_on_circuit++;
            if (perf.completed_race_inclusively) {
                finished_races_count++;
                if (perf.points_scored > 0) {
                    finished_with_points_count++;
                }
            }
        }

        if (wins_on_circuit == 0 && finished_races_count > 0 && finished_races_count == finished_with_points_count) {
            result_driver_names.push_back(driver->getName());
        }
    }

    result_driver_names.sort(); 
    return result_driver_names;
}

vector<pair<string,int>> F1APP::classificationBySeason(int season_year){ 
    vector<pair<string, int>> result_classification;

    const vector<pair<Driver*, int>>* points_for_season_ptr = nullptr;
    for(const auto& season_entry : this->app_season_driver_points){
        if(season_entry.first == season_year){
            points_for_season_ptr = &season_entry.second;
            break;
        }
    }

    if (!points_for_season_ptr) { 
        bool season_has_races_in_raw_data = false;
        if(this->raM_ref) { 
            for(Race* r_check : this->raM_ref->getListRaces()){
                if(r_check && r_check->getSeason() == season_year) {
                    season_has_races_in_raw_data = true;
                    break;
                }
            }
        }
         if(!season_has_races_in_raw_data && (season_year < 1950 || season_year > 2050) ) return {}; 
         if (!points_for_season_ptr) return {}; 
    }

    const vector<pair<Driver*, int>>& points_for_season = *points_for_season_ptr;

    for (const auto& driver_points_pair : points_for_season) {
        if (driver_points_pair.first) { 
             result_classification.push_back({driver_points_pair.first->getName(), driver_points_pair.second});
        }
    }

    sort(result_classification.begin(), result_classification.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second; 
        }
        return a.first < b.first;   
    });

    return result_classification;
}