#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "F1.hpp"

using namespace std;
vector<Qualifying> importQualifying (string filename, DriverManagement &manager);

int verifica_worstVictories(ConstructorGraph &consGraph)
{
    int er = 0;
    
    Constructor* res=consGraph.worstVictories(consGraph.getConstructorNodes()[0]);
   if (res!=nullptr) {
    if (res->getName()!="Toro Rosso")
    {
        cout << "...verifica_worstVictories(nó "<<consGraph.getConstructorNodes()[0]->getName()<<" ): Construtor (="<<res->getName()<<") e' diferente do esperado (=Toro Rosso) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_worstVictories(nó "<<consGraph.getConstructorNodes()[0]->getName()<<" ):  Construtor (="<<res->getName()<<") (ok)" << endl;
    }
   } else {
    cout << "...verifica_worstVictories: return null (ERRO)"<< endl ;
    er++;
   }
   
    return er;
}



int verifica_moreDrivers(ConstructorGraph &consGraph)
{
    int er = 0;
  

    Constructor* res=consGraph.moreDrivers(consGraph.getConstructorNodes()[2]);
    if (res!=nullptr) {
        if (res->getName()!="BMW Sauber")
        {
            cout << "...verifica_moreDrivers(nó "<<consGraph.getConstructorNodes()[2]->getName()<<" ): Construtor (="<<res->getName()<<") e' diferente do esperado (=BMW Sauber) (ERRO)"<< endl ;
               er++;
        }
        else {
            cout << "...verifica_moreDrivers(nó "<<consGraph.getConstructorNodes()[2]->getName()<<" ):  Construtor (="<<res->getName()<<") (ok)" << endl;
        }
       } else {
        cout << "...verifica_moreDrivers: return null (ERRO)"<< endl ;
        er++;
       }

    return er;
}
   




int verifica_noConnection(ConstructorGraph &consGraph)
{
    int er = 0;
  
    vector<string> res=consGraph.noConnection(consGraph.getConstructorNodes()[1]);
 
    string strtotal="";
  

    if (!res.empty()) {
        for (auto &s:res) {
  
            strtotal += s+"-";
            
    }
    strtotal.pop_back();
        if (strtotal!="Renault")
        {
            cout << "...verifica_noConnection(nó "<<consGraph.getConstructorNodes()[1]->getName()<<" ): vector (="<<strtotal<<") e' diferente do esperado (=Renault) (ERRO)"<< endl ;
               er++;
        }
        else {
            cout << "...verifica_noConnection(nó "<<consGraph.getConstructorNodes()[1]->getName()<<" ):  vetor  (="<<strtotal<<") (ok)" << endl;
        }
       } else {
        cout << "...verifica_noConnection: return vazio (ERRO)"<< endl ;
        er++;
       }

    return er;
}

int verifica_updateTransfersOfYear(ConstructorGraph &consGraph, RaceManagement &racManager)
{
    int er = 0;
    
    consGraph.updateTransfersOfYear(2009,racManager);
    

    int res=consGraph.getTotal();
    if (res!=4)
    {
        cout << "...verifica_updateTransfersOfYear( ano 2009):  Total de Construtores com transferências (="<<res<<") e' diferente do esperado (=4) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_updateTransfersOfYear( ano 2009):  Total de Construtores com transferências  (="<<res<<") (ok)" << endl;
    } 
    
auto nod=consGraph.getConstructorNodes();
    bool exist=false;
    int i=0;
    for (auto co:nod){
        if (co->getName()=="Brawn") {
            exist=true;
            break;
        }
        i++;
    }
    if(exist){
    string strtotal= (*(consGraph.getNetwork()[i].begin()))->constructor->getName()+":"+to_string((*(consGraph.getNetwork()[i].begin()))->pointsDiff)+":"+to_string((*(consGraph.getNetwork()[i].begin()))->winsDiff)+":"+to_string((*(consGraph.getNetwork()[i].begin()))->numDrivers);
    if (strtotal!="Honda:-165:-8:2")
    {
        cout << "...verifica_updateTransfersOfYear( ano 2009):  A Braw recebeu da (construtor:pontos:vitorias,numerode pilotos)(="<<strtotal<<") e' diferente do esperado (Honda:-153:-7:2) (ERRO)"<< endl ;
           er++;
    }
    else {
        cout << "...verifica_updateTransfersOfYear( ano 2009):  A Braw recebeu da  (construtor:pontos:vitorias,numerode pilotos)(="<<strtotal<<") (ok)" << endl;
    } 
}

    return er;
}


int verifica_mostRaceFinish(F1APP &f1)
{
    int er = 0;
    
   
    Driver *di=f1.mostRaceFinish(2004,2010);

    if (di!=nullptr) {
    if (di->getName()!="Nick Heidfeld")
    {
        cout << "...verifica_mostRaceFinish(2004-2010): Piloto (="<<di->getName()<<") e' diferente do esperado (=Nick Heidfeld) (ERRO)"<< endl ;
           er++;
    }
    else
        
        cout << "...verifica_mostRaceFinish(2004-2010): Piloto (="<<di->getName()<<") (ok)" << endl;
}
    else
    {
        cout << "...verifica_mostRaceFinish(2004-2010): return null (ERRO)"<< endl ;
        er++;
       }
    
    return er;
}


int verifica_pointsWidthoutWon(F1APP &f1,CircuitManagement &cirM)
{
    int er = 0;
    
   
    list<string> ls=f1.pointsWidthoutWon(*(cirM.getListCircuits().begin()));
    cout << (*(cirM.getListCircuits().begin()))->getCircuitId() <<endl;
    string strtotal="";
    if (!ls.empty()) {

        for (auto &s:ls) {
      
            strtotal += s+"-";
                
        }
        strtotal.pop_back();    
    if (strtotal!="Sébastien Bourdais-Sébastien Buemi")
    {
        cout << "...verifica_pointsWidthoutWon(Albert Park Grand Prix Circuit): Pilotos (="<<strtotal<<") e' diferente do esperado (=Sébastien Bourdais-Sébastien Buemi) (ERRO)"<< endl ;
           er++;
    }
    else
        
        cout << "...verifica_pointsWidthoutWon(Albert Park Grand Prix Circuit): Pilotos (="<<strtotal<<") (ok)" << endl;
}
    else
    {
        cout << "...verifica_pointsWidthoutWon(Albert Park Grand Prix Circuit): return null (ERRO)"<< endl ;
        er++;
       }
    
    return er;
}


int verifica_poleToWin(F1APP &f1)
{
    int er = 0;
    
   
    string ls=f1.poleToWin();
    string strtotal="";
    if (!ls.empty()) {

         
    if (ls!="Circuit de Barcelona-Catalunya")
    {
        cout << "...verifica_poleToWin(): Circuito (="<<ls<<") e' diferente do esperado (=Circuit de Barcelona-Catalunya) (ERRO)"<< endl ;
           er++;
    }
    else
        
        cout << "...verifica_poleToWin(): Circuito (="<<ls<<") (ok)" << endl;
}
    else
    {
        cout << "...verifica_poleToWin(): return vazio (ERRO)"<< endl ;
        er++;
       }
    
    return er;
}



int verifica_mostRaceNotPole(F1APP &f1)
{
    int er = 0;
    
   
    Constructor *cons=f1.mostRaceNotPole(2004,2010);
   
    if (cons!=nullptr) {

         
    if (cons->getName()!="Ferrari")
    {
        cout << "...verifica_mostRaceNotPole(2004-2010): Construtor (="<<cons->getName()<<") e' diferente do esperado (=Ferrari) (ERRO)"<< endl ;
           er++;
    }
    else
        
        cout << "...verifica_mostRaceNotPole(2004-2010): Construtor (="<<cons->getName()<<") (ok)" << endl;
}
    else
    {
        cout << "...verifica_mostRaceNotPole(2004-2010): return nulo (ERRO)"<< endl ;
        er++;
       }
    
    return er;
}


int verifica_classificationBySeason(F1APP &f1)
{
    int er = 0;
    
    vector<pair<string,int>> vres=f1.classificationBySeason(2005);
    string strtotal="";
    
    if (!vres.empty()) {
    for (auto v:vres){
            strtotal+=v.first+":"+to_string(v.second)+" pontos--";
          }
     strtotal.pop_back();    
     strtotal.pop_back();     
    if (strtotal!="Fernando Alonso:133 pontos--Kimi Räikkönen:112 pontos--Michael Schumacher:62 pontos--Juan Pablo Montoya:60 pontos--Giancarlo Fisichella:58 pontos--Ralf Schumacher:45 pontos--Jarno Trulli:43 pontos--Rubens Barrichello:38 pontos--Jenson Button:37 pontos--Mark Webber:36 pontos--Nick Heidfeld:28 pontos--David Coulthard:24 pontos--Felipe Massa:11 pontos--Christian Klien:9 pontos--Jacques Villeneuve:9 pontos--Tiago Monteiro:7 pontos--Alexander Wurz:6 pontos--Narain Karthikeyan:5 pontos--Christijan Albers:4 pontos--Pedro de la Rosa:4 pontos--Patrick Friesacher:3 pontos--Antônio Pizzonia:2 pontos--Takuma Sato:1 pontos--Vitantonio Liuzzi:1 pontos--Anthony Davidson:0 pontos--Ricardo Zonta:0 pontos--Robert Doornbos:0 pontos")
    {
        cout << "...verifica_classificationBySeason(2005): Classificação (="<<strtotal<<") e' diferente do esperado (=Fernando Alonso:133 pontos--Kimi Räikkönen:112 pontos--Michael Schumacher:62 pontos--Juan Pablo Montoya:60 pontos--Giancarlo Fisichella:58 pontos--Ralf Schumacher:45 pontos--Jarno Trulli:43 pontos--Rubens Barrichello:38 pontos--Jenson Button:37 pontos--Mark Webber:36 pontos--Nick Heidfeld:28 pontos--David Coulthard:24 pontos--Felipe Massa:11 pontos--Christian Klien:9 pontos--Jacques Villeneuve:9 pontos--Tiago Monteiro:7 pontos--Alexander Wurz:6 pontos--Narain Karthikeyan:5 pontos--Christijan Albers:4 pontos--Pedro de la Rosa:4 pontos--Patrick Friesacher:3 pontos--Antônio Pizzonia:2 pontos--Takuma Sato:1 pontos--Vitantonio Liuzzi:1 pontos--Anthony Davidson:0 pontos--Ricardo Zonta:0 pontos--Robert Doornbos:0 pontos) (ERRO)"<< endl ;
           er++;
    }
    else
        
        cout << "...verifica_classificationBySeason(2005): Classificação (="<<strtotal<<") (ok)" << endl;
}
    else
    {
        cout << "...verifica_classificationBySeason(2005): return vazio (ERRO)"<< endl ;
        er++;
       }
    
    return er;
}



int importDrivers (string filename, DriverManagement &manager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open allDrivers.txt file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Driver* driv;
    stringstream ss;
    int driveI;
    while (getline(file, line)) {
        
        string driId, cod, nam, dob,nat;
        
            
        ss.clear();
        ss << line; 
        driId.clear();
        
        getline(ss, driId, ';');
        
       
      
        driveI=stoi(driId);

       
        getline(ss, cod, ';');
        
        getline(ss, nam, ';');
        getline(ss, dob, ';');
        getline(ss, nat, ';');
        
     
     driv = new Driver(driveI, cod, nam, dob, nat);
       
       manager.driverInsert(driv);
        count++;
    }
   
    
    file.close();


    return count;

}


int importnumbers (string filename, DriverManagement &manager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open numbers.csv file." << endl;
        return -1;
    }

    string line;
    stringstream ss;
    vector<Driver*> vmanager=manager.getVectorDrivers();
    getline(file, line);
    int count=0;
    while (getline(file, line)) {
        
        string driId, n;
        int driveI,num;
          
      
        ss.clear();
        ss << line; 
        getline(ss, driId, ';');
        driveI=stoi(driId);
        getline(ss, n, ';');
        num=stoi(n);
    
        
        for (size_t i=0;i<vmanager.size();i++){
            if (vmanager[i]->getDriverId()==driveI) {
                vmanager[i]->addNumber(num);
            }
        }
    count++;
    }
   
    
    file.close();

  
    return 0;
}

int importConstructors (string filename, ConstructorManagement &manager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open allConstructors.txt file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Constructor* constr;
    stringstream ss;
    int constrI;
    string constrId, nam, nat;
    getline(file, line);
    while (getline(file, line)) {
        
        
        
            
        ss.clear();
        ss << line; 
        
        
        getline(ss, constrId, ';');
        
      
      
        constrI=stoi(constrId);

       
        getline(ss, nam, ';');
        
      
        getline(ss, nat, ';');
           
     
     constr = new Constructor(constrI, nam, nat);
       
       manager.addConstrutor(constr);
        count++;
    }
   
    
    file.close();


    return count;

}


int importCircuits (string filename, CircuitManagement &manager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open allCircuits.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Circuit* circ;
    stringstream ss;
    int circuitI,al;
    while (getline(file, line)) {
        
        string cird, nam, lat,coun,alt;
        
            
        ss.clear();
        ss << line; 
        cird.clear();
        
        getline(ss, cird, ';');
        
       
      
        circuitI=stoi(cird);
        
        getline(ss, nam, ';');
        getline(ss, lat, ';');
        getline(ss, coun, ';');
        getline(ss, alt, ';');
        al=stoi(alt);
     
        circ = new Circuit(circuitI, nam, alt, coun,al);
       
       manager.circuitInsert(circ);
        count++;
    }
   
    
    file.close();


    return count;

}


vector<Qualifying> importQualifying (string filename, DriverManagement &manager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open qualifying.csv file." << endl;
        return {};
    }
    vector<Qualifying> vq;
    string line;
    stringstream ss;
    vector<Driver*> vmanager=manager.getVectorDrivers();
  
 
    int count=0;
    while (getline(file, line)) {
        
        string driId, n;
        int driveI;
        double num;
          
      
        ss.clear();
        ss << line; 
        getline(ss, driId, ';');
        driveI=stoi(driId);
        getline(ss, n, ';');
        num=stod(n);
    
        
        for (size_t i=0;i<vmanager.size();i++){
            if (vmanager[i]->getDriverId()==driveI) {
                vq.push_back({vmanager[i],num});
                break;
            }
        }
    count++;
    }
   
    
    file.close();

  
    return vq;
}


int importRaces (string filename, RaceManagement &manager, CircuitManagement &cirManager) {

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open allRaces.csv file." << endl;
        return -1;
    }
    int count=0;
    string line;
   
    Race* rac;
    stringstream ss;
    int raceI,coun,seas,circuitI;
    Circuit* cir=NULL;
    list<Circuit*> lc=cirManager.getListCircuits();
  
    while (getline(file, line)) {
        
        string race,cird, cou, sea,dat;
        
            
        ss.clear();
        ss << line; 
        race.clear();
        
        getline(ss, race, ';');
        raceI=stoi(race);
        
        getline(ss, sea, ';');
        seas=stoi(sea);
        getline(ss, cou, ';');
        coun=stoi(cou);
        getline(ss, cird, ';');
        circuitI=stoi(cird);
        getline(ss, dat, ';');
        cir=NULL;
         for (auto it=lc.begin();it!=lc.end();it++) {
            if ((*it)->getCircuitId()==circuitI) {
                cir=*it;
            }

         }
         if (cir!=NULL) {
        rac = new Race(raceI,seas,coun,cir, dat);
       
        manager.raceInsert(rac);
        count++;
         }
    }
   
    
    file.close();


    return count;

}


int main()
{

     int errorCount = 0, error;

    cout << "INICIO DOS TESTES\n\n" << endl;
   
    DriverManagement driverManager;
    ConstructorManagement constrManager;
    CircuitManagement cirManager;
    RaceManagement racManager;
    RaceManagementTree racManagerTree;
    int a=importDrivers("alldrivers.csv",driverManager);
    cout <<"Importou: "<<a<<" drivers"<<endl;
    importnumbers("numbers.csv",driverManager);
    int b=importConstructors("allconstructors.csv",constrManager);
    cout <<"Importou: "<<b<<" constructors"<<endl;
    int c=importCircuits("allcircuits.csv",cirManager);
    cout <<"Importou: "<<c<<" cuircuits"<<endl;
    int d=importRaces("allraces.csv",racManager,cirManager);
    cout <<"Importou: "<<d<<" races"<<endl;
    int e=racManager.uploadFromFile("allresults.csv",driverManager, constrManager);
    cout <<"Importou: "<<e<<" resultados"<<endl<<endl;
   
 

    ConstructorGraph ConstGraphTest;
    for (int i=0;i<5 ; i++) {
        ConstGraphTest.addConstructorNode(constrManager.getVectorConstructores()[i]);
    }
    TransferData* td=new TransferData(constrManager.getVectorConstructores()[1],45,4,3);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[0],td);
    td=new TransferData(constrManager.getVectorConstructores()[2],-24,-2,2);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[0],td);
    td=new TransferData(constrManager.getVectorConstructores()[4],57,10,4);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[0],td);
    td=new TransferData(constrManager.getVectorConstructores()[0],-12,-1,1);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[1],td);
    td=new TransferData(constrManager.getVectorConstructores()[2],-47,0,3);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[1],td);
    td=new TransferData(constrManager.getVectorConstructores()[4],18,7,2);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[1],td);
    td=new TransferData(constrManager.getVectorConstructores()[0],-34,-6,2);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[2],td);
    td=new TransferData(constrManager.getVectorConstructores()[3],-6,1,2);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[2],td);
    td=new TransferData(constrManager.getVectorConstructores()[4],68,17,6);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[3],td);
    td=new TransferData(constrManager.getVectorConstructores()[0],-23,-7,4);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[3],td);
    td=new TransferData(constrManager.getVectorConstructores()[2],-68,-7,2);
    ConstGraphTest.addTranfer(constrManager.getVectorConstructores()[4],td);
    ConstGraphTest.printGraph();
    

    ConstructorGraph ConstGraph;

   F1APP f1;
   f1.updateF1APP(driverManager,constrManager,cirManager,racManager);



   

    error = verifica_worstVictories(ConstGraphTest);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_worstVictories\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_worstVictories passou\n\n" << endl;
    } 

    error = verifica_moreDrivers(ConstGraphTest);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_moreDrivers\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_moreDrivers passou\n\n" << endl;
    }  

 

    error = verifica_noConnection(ConstGraphTest);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_noConnection\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_noConnection passou\n\n" << endl;
    } 

  
    error = verifica_updateTransfersOfYear(ConstGraph,racManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_updateTransfersOfYear\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_updateTransfersOfYear passou\n\n" << endl;
    } 
 
  
    error = verifica_mostRaceFinish(f1);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_mostRaceFinish\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_mostRaceFinish passou\n\n" << endl;
    } 
    

    error = verifica_pointsWidthoutWon(f1,cirManager);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_pointsWidthoutWon\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_pointsWidthoutWon passou\n\n" << endl;
    } 
    
    error = verifica_poleToWin(f1);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_poleToWin\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_poleToWin passou\n\n" << endl;
    } 
    
    error = verifica_mostRaceNotPole(f1);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_mostRaceNotPole\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_mostRaceNotPole passou\n\n" << endl;
    } 
    
    error = verifica_classificationBySeason(f1);
    if (error)
    {
        cout << "ERRO: "<< error << " erros encontrados em verifica_classificationBySeason\n\n" <<  endl;
        errorCount += error;
    }
    else
    {
        cout << "OK: verifica_classificationBySeason passou\n\n" << endl;
    } 

    //Inicio do comentário


    DriverManagement driverManager1;
    ConstructorManagement constrManager1;
    CircuitManagement cirManager1;
    RaceManagement racManager1;
    
    int a1=importDrivers("alldrivers.csv",driverManager1);
    cout <<"Importou: "<<a1<<" drivers"<<endl;
    importnumbers("numbers.csv",driverManager1);
    int b1=importConstructors("allconstructors.csv",constrManager1);
    cout <<"Importou: "<<b1<<" constructors"<<endl;
    int c1=importCircuits("allcircuits.csv",cirManager1);
    cout <<"Importou: "<<c1<<" cuircuits"<<endl;
    int d1=importRaces("allraces1.csv",racManager1,cirManager1);
    cout <<"Importou: "<<d1<<" races"<<endl;
    int e1=racManager1.uploadFromFile("allresults1.csv",driverManager1, constrManager1);
    cout <<"Importou: "<<e1<<" resultados"<<endl<<endl;
    F1APP f1a;
    

    clock_t beg, end;
    double time;
    beg = clock();   
    //Upload to new class F1APP
    
   
    f1a.updateF1APP(driverManager1,constrManager1,cirManager1,racManager1);
    cout << "Fim do update" << endl;
    //Question 6 (65 times)
    
    for (int y=1950;y<2014;y++) {
    f1a.mostRaceFinish(y,y+10);
    }
    f1a.mostRaceFinish(1950,2014);
    cout << "fim question 6"<<endl;
    //Question 7 (65 times)
  
    for (int y=1950;y<2014;y++) {
    f1a.mostRaceNotPole(y,y+10);
    } 
    f1a.mostRaceNotPole(1950,2014);
    cout << "fim question 7"<<endl;
    //Question 8 (100 times)
  
    for (int y=1;y<101;y++) {
        f1a.poleToWin();
        }
    cout << "fim question 8"<<endl;    
    //Question 9 (77 times)
    auto cir1=cirManager1.getListCircuits();
    for (auto it=cir1.begin();it!=cir1.end();it++) {
        f1a.pointsWidthoutWon((*it));
        }
        cout << "fim question 9"<<endl;
    //Question 10 (144 times)
       auto cir=cirManager1.getListCircuits();
       for (int i=0;i<2;i++) {
       for (int y=1950;y<2025;y++)  {
           f1a.classificationBySeason(y);
        }
    }
        cout << "fim question 10"<<endl;
            

    //
    end = clock();
    time = (double)(end - beg) / CLOCKS_PER_SEC;
    cout << "Tempo : "<< time << endl;


    //Fim do comentário


     if (errorCount == 0)
        cout << "FIM DOS TESTES: Todos os testes passaram\n" << endl;
    else
        cout << "FIM DOS TESTES: Foram encontrados "<< errorCount << " ERROS no total\n" << endl;

    return 0;
}
