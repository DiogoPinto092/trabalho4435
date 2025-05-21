#include <vector>
#include <string>
#include <list>
#include <queue>

#define N_STATUS 142

using namespace std;

const string vStauts[N_STATUS] = {"None","Finished","Disqualified","Accident","Collision","Engine","Gearbox","Transmission","Clutch","Hydraulics","Electrical","+1 Lap","+2 Laps","+3 Laps","+4 Laps","+5 Laps","+6 Laps","+7 Laps","+8 Laps","+9 Laps","Spun off","Radiator","Suspension","Brakes","Differential","Overheating","Mechanical","Tyre","Driver Seat","Puncture","Driveshaft","Retired","Fuel pressure","Front wing","Water pressure","Refuelling","Wheel","Throttle","Steering","Technical","Electronics","Broken wing","Heat shield fire","Exhaust","Oil leak","+11 Laps","Wheel rim","Water leak","Fuel pump","Track rod","+17 Laps","Oil pressure","+42 Laps","+13 Laps","Withdrew","+12 Laps","Engine fire","Engine misfire","+26 Laps","Tyre puncture","Out of fuel","Wheel nut","Not classified","Pneumatics","Handling","Rear wing","Fire","Wheel bearing","Physical","Fuel system","Oil line","Fuel rig","Launch control","Injured","Fuel","Power loss","Vibrations","107% Rule","Safety","Drivetrain","Ignition","Did not qualify","Injury","Chassis","Battery","Stalled","Halfshaft","Crankshaft","+10 Laps","Safety concerns","Not restarted","Alternator","Underweight","Safety belt","Oil pump","Fuel leak","Excluded","Did not prequalify","Injection","Distributor","Driver unwell","Turbo","CV joint","Water pump","Fatal accident","Spark plugs","Fuel pipe","Eye injury","Oil pipe","Axle","Water pipe","+14 Laps","+15 Laps","+25 Laps","+18 Laps","+22 Laps","+16 Laps","+24 Laps","+29 Laps","+23 Laps","+21 Laps","Magneto","+44 Laps","+30 Laps","+19 Laps","+46 Laps","Supercharger","+20 Laps","Collision damage","Power Unit","ERS","+49 Laps","+38 Laps","Brake duct","Seat","Damage","Debris","Illness","Undertray","Cooling system"};

/* CLASSES */

class Driver; /** @brief Class to represent a Driver. */
class Constructor; /** @brief Class to represent a Constructor. */
class DriverManagement; /** @brief Class to represent all drivers. */
class ConstructorManagement; /** @brief Class to represent all Constructor. */
class Circuits; /** @brief Class to represent a circuit */
class CircuitsManagement; /** @brief Class to represent all Circuits. */
class Race; /** @brief Class to represent a race */
class RaceManagement; /** @brief Class to represent all races. */
class RaceManagementTree; /** @brief Class to represent all races in a tree. */

/* STRUCTS */


/**/
struct DriCons {
    int begin; /** @brief year of begin. */
    int end;    /** @brief year of end. */
    Driver *driver;   /** @brief pointer to driver */
    /* --- Constructor --- */
    DriCons(int b,int e , Driver* dri): begin(b),end(e),driver(dri) {}

};

struct DriResult {
    Driver *drive;  /** @brief pointer to a driver*/
    Constructor *constructor; /** @brief pointer to a constructor*/
    int number; /** @brief number the driver used in that race*/
    int grid; /** @brief starting position*/
    int position; /** @brief final position*/
    int laps; /** @brief number of laps completed*/
    int status; /** @brief type of occurrence in the race (accident, flat tire, broken engine,...) */
    /* --- Constructor --- */
    DriResult(Driver *driv,Constructor *construct , int num, int gri, int posit, int lap, int sta): drive(driv), constructor(construct),number(num),grid(gri),position(posit),laps(lap),status(sta) {}
    bool operator<(const DriResult &dri) const;
};

struct Qualifying {
  Driver* driver; /** @brief pointer to driver */  
  double timeLap;/** @brief Lap time in seconds */

    bool operator>(const Qualifying& other) const; 
};

struct NodeRace {

    Race* race;  /** @brief pointer to race*/
    NodeRace* left; /** @brief pointer to the left node*/
    NodeRace* right; /** @brief pointer to the right node*/
    
      
    NodeRace(Race* race):race(race),left(nullptr),right(nullptr) {}; 
    ~NodeRace();
};

struct TransferData {
    Constructor *constructor; /** @brief pointer to a constructor*/
    int pointsDiff; /** @brief difference in points per GP between constructors*/
    int winsDiff; /** @brief difference in victories between constructors*/
    int numDrivers; /** @brief number of pilots transferred*/

    TransferData(Constructor* constructor, int pointsDiff, int winsDiff, int numDrivers):constructor(constructor),pointsDiff(pointsDiff),winsDiff(winsDiff),numDrivers(numDrivers) {}; 
};

struct SeasonData {
    Driver *driver; /** @brief pointer to a driver*/
    Constructor *constructor; /** @brief pointer to a constructor*/
    int points; /** @brief points of a sasson */
    int wins; /** @brief wins of a seasson*/
 

    SeasonData(Driver *driver,Constructor* constructor, int points, int wins):driver(driver),constructor(constructor),points(points),wins(wins) {}; 
};

class Driver {
    private:
        /* ATTRIBUTES */
        int driverId; /** @brief driver id */
        string code; /** @brief 3-letter alphabet code of driver */
        string name; /** @brief Name */
        vector<int> numbers; /** @brief All the numbers the driver used */
        string dateOfBirth ; /** @brief Date of birth */
        string nationality; /** @brief Nationality*/

    public:
        /* METHODS */

        /* --- Constructor --- */

        /** 
         *  @brief Constructor (parameterized) - Create an object of the class Driver.
         *  @param driverI driver Id.
         *  @param cod 3-letter alphabet code of driver.
         *  @param nam Name.
         *  @param numbe Vector with the numbers the driver used.
         *  @param dateOfBir Date of birth. 
         *  @param nationali Country.
         *  @note  Initialize each attribute with the corresponding argument.
         */
        Driver (int driverI, string cod, string nam, vector<int> numbe, string dateOfBir, string  nationali);
        Driver (int driverI, string cod, string nam, string dateOfBir, string  nationali);

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the driver Id.
         *  @return 'driverId' attribute.
         */
        int getDriverId() const;

        /** 
         *  @brief  Get the code of the driver.
         *  @return 'code' attribute.
         */
        string getCode() const;
        
          /** 
         *  @brief  Get the name of the driver.
         *  @return 'name' attribute.
         */
        string getName() const;


        /** 
         *  @brief  Get the number numbers the driver used.
         *  @return 'numbers' attribute.
         */
        vector<int> getNumbers() const;
        
        /** 
         *  @brief  Get the date of birth.
         *  @return 'dateOfBirth' attribute.
         */
        string getDateOfBirth() const;
        
        /** 
         *  @brief  Get the country.
         *  @return 'nationality' attribute.
         */
        string  getNationality() const;

         /* --- set Methods --- */
        /** 
         *  @brief  add a new number. The number must be from 1 to 199.
         *  @return 0 if 0 if inserted successfully, 1 if that number already existed and -1 if an error occurred..
         */
        int addNumber(int num);
        
        /* --- Other Methods --- */

        /** 
         *  @brief  Display the information of a Driver.
         *  @return void
         */
        void displayDriverInfo(ostream& os) const;


};

class Constructor {
    private:
        /* ATTRIBUTES */
        int constructorId; /** @brief Constructor Id. */
        string name; /** @brief Name of Constructor. */
        string nationality; /** @brief Country. */
        vector<DriCons*> Drivers; /** @brief Vector with all drivers who passed through the Constructor. */
       
    public:
        /* METHODS */

        /* --- Constructor --- */

        /** 
         *  @brief Constructor (parameterized) - Create an object of the class Constructor.
         *  @param constructorId Constructor Id.
         *  @param name Name of the ConstructorId.
         *  @param country Country of the ConstructorId.
         *  @note  Initialize each attribute with the corresponding argument.
         */
        Constructor(int constructorId, string name, string country);

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the constructor's constructorId.
         *  @return 'ConstructorId' attribute.
         */
        int getConstructorId() const;

        /** 
         *  @brief  Get the user's name.
         *  @return 'name' attribute.
         */
        string getName() const;

        /** 
         *  @brief  Get the user's country.
         *  @return 'country' attribute.
         */
        string getCountry() const;

        /** 
         *  @brief  Get the all drivers who passed through the Constructor.
         *  @return 'Drivers' attribute.
         */
        vector<DriCons*> getDrivers();


        /* --- Other Methods --- */



        int deleteDriver(int driveId);

        /** 
         *  @brief  Add a new driver or a new year to a DriCons that already exists.
         *  @param  driverId drive Id.
         *  @param  year year.
         *  @return 0 if the new drivers or a new year is added successfully | 1 if the new drivers or the new year already exists |
         *  @return -1 if the parameteres are invalid or drivers not exist
         *  @note Formula 1 started in 1950 and there are no future years
         */
        int addDriver(int driveId, int year, DriverManagement &driveManager);

      
};

class DriverManagement {
    private:
        /* ATTRIBUTES */
        vector<Driver*> vectorDrivers; /** @brief Vector with all the Drivess. */
    public:
        /* METHODS */

        /* --- Constructor --- */

        /** 
         *  @brief Constructor (default) - Create an object of the class DriverManagement.
         *  @note  Make sure the vector 'vectorDrivers' is empty.
         */
        DriverManagement();

        /** 
         *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorDrivers'.
         */
        ~DriverManagement();

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the vector with all the Drivers.
         *  @return 'vectorDrivers' attribute.
         */
        vector<Driver*> getVectorDrivers() const;

        /* --- Other Methods --- */

        /** 
         *  @brief  Add a new driver.
         *  @param  driver New driver to be added.
         *  @return 0 if the driver is added successfully | -1 if the parameter is invalid | 1 if the driver already exists in the vector
         */
        int driverInsert(Driver* driver);

        /** 
         *  @brief  Remove a driver.
         *  @param  driverId Driver Id of the driver to be removed.
         *  @return 0 if the driver is removed successfully | -1 if the driver does not exist in the vector
         */
        int driverDelete(int driverId);
};

class ConstructorManagement {
    private:
        /* ATTRIBUTES */
        vector<Constructor*> vectorConstructores; /** @brief Vector with all Constructores. */

    public:
        /* METHODS */

        /** 
         *  @brief Constructor (default) - Create an object of the class ConstructorManagement.
         *  @note  Make sure the vector 'vectorConstructores' is empty.
         */
        ConstructorManagement();

          /** 
         *  @brief Desconstructor (default) - Delete all the  object of the vector 'vectorConstructores'.
         */
        ~ConstructorManagement();

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the vector with all the constructores.
         *  @return 'vectorConstructores' attribute.
         */
        vector<Constructor*> getVectorConstructores() const;

        /* --- Other Methods --- */

        /** 
         *  @brief  Add a new constructorto the vector.
         *  @param  newUser Constructor to be added.
         * @return 0 if the constructor is added successfully | -1 if the parameter is invalid | 1 if the constructor already exists in the vector
         */
        int addConstrutor(Constructor* newConstructor);

        /** 
         *  @brief  Update the drivers in the constructors by reading a text file.
         *  @param  filename Filename of the text file containing the drivers in the constructors information.
         *  @param  manager Object with all the Drivers in the platform.
         *  @return 0 if successful | -1 if an error occurs
         *  @note   Each line of the file contains the required information in the following format: constructorId;driverId;year
         *  @note   Other functions implemented in this library can be used to implement this method.
         *  @note   Check:
         *  @note    -> driver exists  : NO  -ignore this line
         *  @note    -> constructor exists: NO  - ignore this line | YES - update the vetor
         */ 
        int updateConstructorDrivers(string filename, DriverManagement& manager);


        /** 
         *  @brief  List with the name of the drivers and the Construtors from a given year.
         *  @param  year  year.
         *  @param  vConstr  Parameter to pass the list of Construtors ordered in ascending order.
         *  @return vector with the name of the drivers ordered in ascending order
         *  @note Formula 1 started in 1950 and there are no future years
         */ 
        vector<string> DriversAndConstructorsOfOneYear(int year,vector<string> &vConstr);
};


class Circuit {
    /* ATTRIBUTES */
    int circuitId; /** @brief circuit id */
    string name; /** @brief Name */
    string location ; /** @brief location */
    string country; /** @brief country*/
    int alt; /** @brief altitude */

    public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
     *  @brief Constructor (parameterized) - Create an object of the class Circuit.
     *  @param circuitI circuit Id.
     *  @param nam Name.
     *  @param locat location. 
     *  @param countr Country.
     *  @param al altitude. 
     *  @note  Initialize each attribute with the corresponding argument.
     */
    Circuit (int circuitI, string nam, string locat, string  countr, int al);
  
    /* --- Get Methods --- */
    
    /** 
     *  @brief  Get the circuit Id.
     *  @return 'circuitId' attribute.
     */
    int getCircuitId() const;
    
      /** 
     *  @brief  Get the name of the circuit.
     *  @return 'name' attribute.
     */
    string getName() const;

    /** 
     *  @brief  Get the location.
     *  @return 'location' attribute.
     */
    string getLocation() const;
    
    /** 
     *  @brief  Get the country.
     *  @return 'country' attribute.
     */
    string  getCountry() const;

    /** 
     *  @brief  Get the altitude.
     *  @return 'alt' attribute.
     */
    int  getAlt() const;

     /* --- set Methods --- */
  
    
    /* --- Other Methods --- */

    /** 
     *  @brief  Display the information of a Circuit.
     *  @return void
     */
    void displayCircuitInfo(ostream& os) const;


};



class CircuitManagement {
    private:
        /* ATTRIBUTES */
        list<Circuit*> listCircuits; /** @brief List with all circuits. */
    public:
        /* METHODS */

        /* --- Constructor --- */

        /** 
         *  @brief Constructor (default) - Create an object of the class CircuitManagement.
         *  @note  Make sure the list 'listCircuits' is empty.
         */
        CircuitManagement();

        /** 
         *  @brief Desconstructor (default) - Delete all the  object of the list 'listCircuits'.
         */
        ~CircuitManagement();

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the list with all Circuits.
         *  @return 'listCircuits' attribute.
         */
        list<Circuit*> getListCircuits() const;

        /* --- Other Methods --- */

        /** 
         *  @brief  Add a new circuit.
         *  @param  circuit New circuit to be added.
         *  @return 0 if the circuit is added successfully | -1 if the parameter is invalid | 1 if the circuit already exists in the list
         */
        int circuitInsert(Circuit* circuit);

        /** 
         *  @brief  Remove a circuit.
         *  @param  circuitId circuit Id of the circuit to be removed.
         *  @return 0 if the circuit is removed successfully | -1 if the circuit does not exist in the list
         */
        int circuitDelete(int circuitId);
};


class Race {
    /* ATTRIBUTES */
    int raceId; /** @brief race id */
    int season; /** @brief year */
    int round ; /** @brief number of the Grand Prix */
    Circuit *circuit; /** @brief pointer to circuit*/
    string date; /** @brief Grand Prix date  */
    list<DriResult*> listRaceResults; /** @brief list with results by driver  */  

    public:
    /* METHODS */

    /* --- Constructor --- */

    /** 
     *  @brief Constructor (parameterized) - Create an object of the class Race.
     *  @param raceI race Id.
     *  @param seas season.
     *  @param roun round. 
     *  @param circui pointer to circuit.
     *  @param dat date. 
     *  @note  Initialize each attribute with the corresponding argument.
     */
    Race (int raceI, int seas, int roun, Circuit  *circui, string dat);

    /** 
    *  @brief Desconstructor (default) - Delete all the  object of the list 'listRaceResults'.
    */
    ~Race();
  
    /* --- Get Methods --- */
    
    /** 
     *  @brief  Get the race Id.
     *  @return 'raceId' attribute.
     */
    int getRaceId() const;
    
      /** 
     *  @brief  Get the season.
     *  @return 'season' attribute.
     */
    int getSeason() const;

    /** 
     *  @brief  Get the round.
     *  @return 'round' attribute.
     */
    int getRound() const;
    
    /** 
     *  @brief  Get the pointer to cirucit.
     *  @return 'circuit' attribute.
     */
    Circuit*  getCircuit() const;

    /** 
     *  @brief  Get the date of Grand Prix.
     *  @return 'date' attribute.
     */
    string  getDate() const;


    /** 
     *  @brief  Get the list of results.
     *  @return 'listRaceResults' attribute.
    */
   list<DriResult*>  getListRaceResults() const; 

     /* --- set Methods --- */
    
    
    /* --- Other Methods --- */
    /** 
         *  @brief  Add a new result from a driver.
         *  @param  driveR struct DriResult.
         *  @return 0 if the new result from a driver is added successfully | 1 if the drivers already exists in this race |
         *  @return -1 if the parameteres are invalid or drivers not exist
         */
        int addDriverResult(DriResult *driveR, DriverManagement &driManager);


    /** 
     *  @brief  Display the information of a Race.
     *  @return void
     */
    void displayRaceInfo(ostream& os) const;


};

class RaceManagement {
    private:
        /* ATTRIBUTES */
        list<Race*> listRaces; /** @brief List with all races. */
    public:
        /* METHODS */

        /* --- Constructor --- */

        /** 
         *  @brief Constructor (default) - Create an object of the class RaceManagement.
         *  @note  Make sure the list 'listRaces' is empty.
         */
        RaceManagement();

        /** 
         *  @brief Desconstructor (default) - Delete all the  object of the list 'listRaces'.
         */
        ~RaceManagement();

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the list with all races.
         *  @return 'listRaces' attribute.
         */
        list<Race*> getListRaces() const;

        /* --- Other Methods --- */

        /** 
         *  @brief  Add a new race.
         *  @param  circuit New race to be added.
         *  @return 0 if the race is added successfully | -1 if the parameter is invalid | 1 if the race already exists in the list
         */
        int raceInsert(Race* race);

        /** 
         *  @brief  Remove a race.
         *  @param  circuitId race Id of the circuit to be removed.
         *  @return 0 if the race is removed successfully | -1 if the race does not exist in the list
         */
        int raceDelete(int raceId);
        /** 
         *  @brief  Number of seasons with n races.
         *  @param  nRaces Number of races.
         *  @return Number of seasons with n races | -1 if nRaces is not valid
         */
        int numberRacePerSeason(int nRaces);

         /** 
         *  @brief  Grand prix of a given season.
         *  @param  year season.
         *  @return queue with the grand prix | -1 if year is not valid
         *  @note must be in order of the grand prix( round 1 , round 2,....), the first one out of the queue is the first grand prix
         */
        queue<string> seasonGrandPrix(int year);
        /**
         *  @brief  Update the results in the races by reading a text file.
         *  @param  filename Filename of the text file containing the results from all drivers.
         *  @param  driManager Object with all the Drivers in the platform.
         *  @param  consManager Object with all the Constructors in the platform.
         *  @return number of results inserts | -1 if an error occurs
         *  @note   Each line of the file contains the required information in the following format: raceId;driverId;constructorId;number;grid;position;laps;statusId
         *  @note   Other functions implemented in this library can be used to implement this method.
         *  @note   Check:
         *  @note    -> driver exists  : NO  -ignore this line
         *  @note    -> constructor exists: NO  - ignore this line
         *  @note    -> race exists: NO  - ignore this line | YES - update the vetor
         */ 
        int uploadFromFile(string filename, DriverManagement &driManager, ConstructorManagement &consManager);
        
        /** 
         *  @brief  determine which driver had a certain type of occurrence most often in races (accident, flat tyre, ...).
         *  @param  status  type of occurrence.
         *  @param  num  Parameter to pass the number of times.
         *  @return the name of the pilot with the most occasions in that occurrence(status) 
         *  @note the vector vStauts have all occurrence(status) possible.
         *  @note In the event of a tie, the one that is alphabetically ahead is selected.
         */ 
        string driverStatus(string status, int &num);
        
        /** 
         *  @brief  determines the total points and pole positions of a driver
         *  @param  driveI  driver Id.
         *  @param  drivManager  List of all drivers.
         *  @param  ngrids  Parameter to pass the number of poles positions.
         *  @return the total points of a driver. 
         *  @note the scoring system has varied over the years
         */ 
        int scoreCareer ( int driveI, DriverManagement &drivManager, int &ngrids);

        /** 
         *  @brief  determine which constructor had a certain number on the car the most times
         *  @param  number  number to search
         *  @param  drivManager  List of all drivers.
         *  @param  count  Parameter to pass the number of times a construtor ran with that number.
         *  @return the name of the construtor. Return a empty string if number is not valid (valid is between 1 to 199)
         */
        string moreTimesNumber(int number,int &count);

        /** 
         *  @brief  determine the starting grid using a priority_queue
         *  @param  vQ  vector with all times achieved in qualification
         *  @return the name of the construtor. 
         *  @note the vector has the times of all the laps that the drivers did in qualifying
         */
        priority_queue<Qualifying,vector<Qualifying>, greater<Qualifying>> startingGrid(vector<Qualifying> &vQ);
};

class RaceManagementTree {
    private:
        /* ATTRIBUTES */
        NodeRace* root; /** @brief pointer to the root of the tree. */

        /* METHODS */
        
        /** 
         *  @brief Auxiliary function to insert a nodeRace into the tree
         *  @param  root pointer to NodeRace.
         *  @param  newRace race pointer to be inserted.
         *  @return pointer to nodeRace
         */
        NodeRace* insertNode(NodeRace* root, Race* newRace);

        /** 
         *  @brief Auxiliary function to find the minimum node of a subtree 
         */
        NodeRace* findMinNode(NodeRace* node);

        /** 
         *  @brief Auxiliary function to delete a node from the tree 
         */
        NodeRace* deleteNode(NodeRace* root, int raceSeason, int round);

        /** 
         *  @brief Auxiliary function to print the nodes in order
         */
        void inorderTraversal(NodeRace* root);
    public:
        /* METHODS */

        /** 
         *  @brief Constructor (default) - Create an object of the class UserManagementList.
         *  @note  Make sure the root points to null.
         */
        RaceManagementTree(); 

        /** 
         *  @brief Desconstructor (default) - Delete all the nodes of the tree.
         */
        ~RaceManagementTree();

        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the first node (root).
         *  @return 'root' attribute.
         */
        NodeRace* getRoot() const;

        /* --- Other Methods --- */

        /** 
         *  @brief  Add a new race to the tree.
         *  @param  newRace Race to be added.
         *  @return void
         */
         void addRace(Race* newRace); 

        /** 
         *  @brief  Remove a race (given the season and grand prix round) from the tree.
         *  @param  raceSeason season to be remove.
         *  @param  round round to be remove.
         *  @return void
         */ 
        void remove(int raceSeason, int round);

         /** 
         *  @brief  Public method to print Race in order of raceId
         *  @return void
         */ 
        void inorder(); 
      
        /** 
         *  @brief  determines all the drivers who have won on a given circuit and the number of times they have won.
         *  @param  root  pointer to a noderace
         *  @param  circuitId  Circuit Id .
         *  @return a vector of a pairs containing the names of the drivers and the number of times they won. 
         *  @note the vector is sorted in descending order by the number of wins. In case of a tie, the classification is made in alphabetical order by the name of the driver.
         */
         vector<pair<string,int>> driverVictoriesGP(NodeRace* root,int circuitId);
        
         /** 
         *  @brief  determines which driver performed best in a given race in a given year
         *  @param  root  pointer to a noderace
         *  @param  season  year of the race to look for.
         *  @param  round  race number of the year
         *  @param  grid   Parameter to pass the position in the grid of the best performece
         *  @param  position   Parameter to pass the final position of the best performece
         *  @return name of the driver with the best performece
         *  @note The best performance is the one who has moved up the most places since the start
         *  @note If they have climbed the same number of places, the one who was best placed at the end of the race is chosen.
         */
         string bestPerformance(NodeRace* root,int season,int round, int &grid, int&position);

};

class ConstructorGraph {
    private:
        /* ATTRIBUTES */
        size_t totalConstructors; /** @brief Total number of nodes in the graph. */
        vector<Constructor*> constructorNodes; /** @brief Vector with the Constructor (nodes) in the graph. */
        vector<list<TransferData*>> network; /** @brief Adjacency list to represent connections between the Constructor (each list has TransferData elements). */

    public:
        /* METHODS */

        /* --- Constructor --- */

        /** 
         *  @brief Constructor (default) - Create an object of the class ConstructorGraph.
         *  @note  Initialize 'totalConstructors' with zero and make sure the vector is empty.
         */
        ConstructorGraph();
        
        /* --- Get Methods --- */
        
        /** 
         *  @brief  Get the total number of graph nodes.
         *  @return 'totalConstructors' attribute.
         */
        size_t getTotal() const;

        /** 
         *  @brief  Get the vector with all nodes.
         *  @return 'constructorNodes' attribute.
         */
        vector<Constructor*> getConstructorNodes() const;

        /** 
         *  @brief  Get the adjacency list.
         *  @return 'network' attribute.
         */
        vector<list<TransferData*>> getNetwork() const;

        /* --- Other Methods --- */

        /**
         *  @brief  Add a new node to the graph.
         *  @param  constructorPtr pointer to the Constructor object to be added
         *  @return 0 if the new node is added successfully | 1 if the node already exists | -1 if an error occurs
         *  @note   The total number of nodes must be updated, as well as the size of the adjacency list.
         */
        int addConstructorNode(Constructor* constructorPtr);

        /**
         *  @brief  Find the position of a constructor in the graph nodes' vector.
         *  @param  constructorPtr pointer to the onstructor object to be found
         *  @return Position of the node in the vector (0 to n-1, being n the vector size) | -1 if the node does not exist | -2 if an error occurs
         */
        int constructorPosition(Constructor* constructorPtr);

        /**
         *  @brief  Add a new Transf to a user.
         *  @param  ConstructorA node where the edge starts
         *  @param  Transf edge with the final constructor node
         *  @return 0 if the new edge is added successfully | 1 if the edge already exists | -1 if an error occurs
         *  @note   if a transfer already exists add to what is already there.
         *  @note   If neither ConstructorA nor ConstructorB(in the TransferData) are in the graph, they must be added first.
         */
	    int addTranfer(Constructor* ConstructorA, TransferData* Transf);

        /**
         *  @brief  Remove a Transfer.
         *  @param  ConstructorA node where the edge starts
         *  @param  ConstructorB node where the edge ends
         *  @return 0 if the edge is removed successfully | 1 if the edge does not exist | -1 if an error occurs
         *  @note   Remove the edge from A to B.
         *  @note   Check if ConstructorA and ConstructorB are in the graph.
         */
        int removeTransfer(Constructor* ConstructorA, Constructor* ConstructorB);

        void printGraph();
         /**
         *  @brief  Determine which constructor had the worst deficit of victories with drivers coming from constructor A.
         *  @param  constructorA pointer to the Constructor ( a node ) 
         *  @return The constructor width worst deficit of victories | NULL if an error occurs
         *  @note   If there are 2 or more constructor with the same number of deficit of victories, the constructor with the best points difference is selected
         *  @note   If the tie persists, the constructor whose name is alphabetically smaller is chosen.
         */
        Constructor* worstVictories(Constructor* constructorA);

           /**
         *  @brief  Determines the constructor that received the most drivers from a given constructor B.
         *  @param  constructorB pointer to the Constructor ( a node ) 
         *  @return Returns the name of the selected builder | NULL on error or if there are no pilot transfers to builder B
         *  @note   In the event of a tie in the total number of drivers, the constructor with the best points difference is selected
         *  @note   If the tie persists, the constructor with the best difference in victories is chosen.
         *  @note   If the tie persists, the constructor whose name is alphabetically smaller is chosen.
         */
        Constructor* moreDrivers(Constructor* constructorB);

         /**
         *  @brief  Determines construtors that have no connection to a given construtor. In other words, it identifies the constructors that did not receive pilots from constructor A nor sent pilots to that constructor.
         *  @param  constructorA pointer to the Constructor ( a node ) 
         *  @return   Returns an array with the names of these constructors, sorted alphabetically.
         *  @return   Returns NULL on error or if there are no pilot transfers to or from constructor A.
         */
        vector<string> noConnection ( Constructor* constructorA );

         /**
         *  @brief  Creates nodes and edges corresponding to pilot transfers in a given year.
         *  @param  year the year.
         *  @param  RaM the object width all races.
         *  @return Returns the total number of transfers identified in that year | -1 if the year is invalid.
         *  @note   Transfers are considered in year X if:
         *  @note   The driver was with one constructor in year X-1 and switched to another in year X;
         *  @note   There are no drivers who change constructors in the middle of a season
         */
        int updateTransfersOfYear(int year, RaceManagement &RaM);
};




class F1APP {
    private:
  
    
    
    public:
        /* --- Constructor --- */
        F1APP();
      


           /**
         *  @brief  Fill in the F1APP class by searching for information from the various classes available..
         *  @param  drM the object width all drivers.
         *  @param  coM the object width all constructors.
         *  @param  ciM the object width all circuits.
         *  @param  RaM the object width all races.
         */
        void updateF1APP(DriverManagement &drM, ConstructorManagement &coM, CircuitManagement &ciM, RaceManagement &raM);
       

           /**
         *  @brief  Determines the driver who has completed the greatest number of consecutive races without abandoning, in a given time interval (between YearA and YearB, inclusive).
         *  @param  yearA initial year(inclusive).
         *  @param  YearB final year(inclusive).
         *  @return Returns a pointer to the selected pilot | NULL if years are invalid.
         *  @note   In the event of a tie, the driver whose name is alphabetically lower is selected.
         */
        Driver* mostRaceFinish(int yearA, int yearB);

         /**
         *  @brief  Determines the constructor that has won the most races without starting in pole position, in a given time interval (between YearA and YearB, inclusive).
         *  @param  yearA initial year(inclusive).
         *  @param  YearB final year(inclusive).
         *  @return Returns a pointer to the selected constructor | NULL if years are invalid.
         *  @note   In case of a tie, the builder whose name is alphabetically smaller is selected.
         */
        Constructor * mostRaceNotPole(int yearA, int yearB);


           /**
         *  @brief  Determines the name of the circuit with the highest ratio between victories achieved from pole position and the number of races. .
         *  @return Returns the name of the selected circuit.
         *  @note   In the event of a tie, the circuit whose name is alphabetically smaller is selected.
         */
        string poleToWin();
    
           /**
         *  @brief  Identify drivers who, on a given circuit, have never won a race, but have scored points every time they finish.
         *  @param  cir the circuit 
         *  @return Return a list with the names of the pilots, sorted alphabetically in ascending order. | an empty list if the circuit is invalid
         *  @note   The scoring system is defined in Assignment 2.
         */
        list<string> pointsWidthoutWon(Circuit* cir);

           /**
         *  @brief  Creates the final drivers' world championship standings for a given season.
         *  @param  season the year.
         *  @return Returns a vector sorted by score, from highest to lowest, where each element is a pair composed of a pointer to the pilot and the respective score | an empty vector if the season is invalid..
         */
        vector<pair<string,int>> classificationBySeason(int season);
           
    };
    