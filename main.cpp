#include <bits/stdc++.h>
#include "Vector3.h"
#include "planets.h"
#include <unistd.h>

#define TIMEDELAY 100000
float noIterations;
int inputdatatype,inputnumber;
float initialEnergy;
Vector3 initialMomentum;
std::vector<planet> bodies;



int main()
{
    std::cout<<"introdu numarul de ani siderali ";
    std::cin>>noIterations;
    noIterations*=12000;
    std::cout<<"apasa 1 pentru a simula date introduse de utilizator\napasa 2 urmat de numarul de corpuri pentru a simula date aleatorii\n";
    std::cin>>inputdatatype;
    if(inputdatatype==1)
    {
        in>>inputnumber;
        while(inputnumber--)
            readPlanet(bodies);
    }
    if(inputdatatype==2)
    {
        std::cin>>inputnumber;
        generatePlanets(bodies,inputnumber,100000,10000,500);
    }
    o<<inputnumber<<'\n';
    if(inputdatatype!=1 && inputdatatype!=2)
        exit(EXIT_SUCCESS);
    initialEnergy=totalEnergy(bodies);
    initialMomentum=totalMomentum(bodies);
    assignVector(initialMomentum,totalMomentum(bodies));
    //physics
    while(noIterations--)
        for(int i=0; i<bodies.size(); i++)
        {
            bodies[i].updatePhysics(bodies);
            if(int(noIterations)%100==0)
            bodies[i].outputPozition();

        }
    exit(EXIT_SUCCESS);
    return 0;
}
