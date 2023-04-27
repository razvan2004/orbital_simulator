std::ifstream in("planetdata.txt");
#define step 0.0001 //this parameter determines how often the algorithm computes the acceleration of the bodies. The lower it is, the more accurate the system becomes
// the error of the system is "usually" proportioal with

#define second 26e+5  // one time unit in this simulator is approxtimately one month in real time
#define meter 1000000 // one unit distance in this simulator is 10^6 m
#define G 4508.92  // the value of the Gravitational constant using this system of measurement
class planet
{
    //get data
public:
    //std::string name;
    Vector3 pozition;
    Vector3 velocity;
    Vector3 acceleration;
    float mass,ID;
    void planetCreation(float,Vector3,Vector3 );
    void updatePhysics(std::vector<planet>);
    void outputPozition(void);
    void outputVelocity(void);
};
//generates random objects with the parameters in a
//N is the number of planets
//rom is the range of the positive mass
//rop is the range of the position coordinates
//rov is the range of the velocities coordinates
void generatePlanets(std::vector<planet> &storage, int N,float rom, float rop, float rov)
{
    Vector3 aux,aux2;
    planet auxbody;
    float planetmass;
    while(N--)
    {
        srand(time(NULL)+N);
        planetmass=(rand()%int(rom));
        aux.assignValue(rand()%int(rop)*pow(-1,rand()%2),rand()%int(rop)*pow(-1,rand()%2),rand()%int(rop)*pow(-1,rand()%2));
        aux2.assignValue(rand()%int(rov)*pow(-1,rand()%2),rand()%int(rov)*pow(-1,rand()%2),rand()%int(rov)*pow(-1,rand()%2));
        auxbody.planetCreation(planetmass,aux,aux2);
        auxbody.ID=storage.size();
        storage.push_back(auxbody);
    }
}
void planet::outputPozition()
{
    o<<std::fixed<<pozition.x/1000<<"\n"<<std::fixed<<pozition.y/1000<<"\n";
}
void planet::outputVelocity()
{
    o<<std::fixed<<velocity.x/1000<<" "<<std::fixed<<velocity.y/1000<<'\n';
}

void readPlanet(std::vector<planet> &storage)
{
    float massaux;
    planet auxbody;
    Vector3 poz,vel;
    in>>massaux>>poz.x>>poz.y>>poz.z>>vel.x>>vel.y>>vel.z;
    auxbody.planetCreation(massaux,poz,vel);
    auxbody.ID=storage.size();
    storage.push_back(auxbody);
}
// the constructor
void planet::planetCreation(float mass0,Vector3 poz, Vector3 vel)
{
    mass=mass0;
    assignVector(pozition,poz);
    assignVector(velocity,vel);
    acceleration.assignValue(0,0,0);
}
// this function calculates the acceleration produced by each body on the target body
// is it found by simply applying Netwon's law of gravity
void planet::updatePhysics(std::vector <planet> storage)
{
    Vector3 previousAcc;
    assignVector(previousAcc,acceleration);
    acceleration.assignValue(0,0,0);
    Vector3 auxvec;
    for(int j=0; j<storage.size(); j++)
        if(j!=ID)
        {
            auxvec.assignValue(0,0,0);
            addVectors(auxvec,storage[j].pozition);
            addVectors(auxvec,rescale(pozition,-1));
            addVectors(acceleration,rescale(auxvec,G*storage[j].mass/pow(lengthModulus(auxvec),3)));
        }
    addVectors(previousAcc,acceleration);
    addVectors(pozition, rescale(velocity,step));
    addVectors(pozition, rescale(acceleration,step*step/2));
    addVectors(velocity, rescale(previousAcc,step));
}
float totalEnergy(std::vector<planet> storage)
{
    float energy=0;
    for(int i=0; i<storage.size(); i++)
        energy+=storage[i].mass*lengthModulus(storage[i].velocity)*lengthModulus(storage[i].velocity)/2;
    for(int i=0; i<storage.size(); i++)
        for(int j=i+1; j<storage.size(); j++)
        {
            Vector3 aux;
            aux.assignValue(0,0,0);
            addVectors(aux,storage[i].pozition);
            addVectors(aux,rescale(storage[j].pozition,-1));
            energy-=storage[i].mass*storage[j].mass*G*10000/lengthModulus(aux);
        }
    return energy;
}
//total momentum relative to the origin of the system
Vector3 totalMomentum(std::vector<planet> storage)
{
    Vector3 momentum;
    momentum.assignValue(0,0,0);
    for(int i=0;i<storage.size();i++)
        addVectors(momentum,vectorialProduct(storage[i].pozition,storage[i].velocity));
    return momentum;
}
