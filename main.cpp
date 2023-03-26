#include <bits/stdc++.h>
#include "Vector3.h"
#include "planets.h"
#include <unistd.h>

#define TIMEDELAY 100000
int noIterations=10000;
float initialEnergy;
Vector3 initialMomentum;
std::vector<planet> bodies;



int main()
{
    generatePlanets(bodies,50,100000,10000,500);
    initialEnergy=totalEnergy(bodies);
    assignVector(initialMomentum,totalMomentum(bodies));
    std::cout<<initialEnergy<<" ";
    displayVector(initialMomentum);
    //physics
    while(noIterations--)
    {
        for(int i=0; i<bodies.size(); i++)
        {
            bodies[i].updatePhysics(bodies);

        }
        if(noIterations%10==0)
        {
            Vector3 momentum;
            momentum.assignValue(0,0,0);
            o<<std::fixed<<std::setprecision(10)<<totalEnergy(bodies)/initialEnergy<<' ';
            addVectors(momentum,rescale(totalMomentum(bodies),-1));
            addVectors(momentum,initialMomentum);
            saveWholeVector(momentum);
            o<<"\n";
        }
    }
    exit(EXIT_SUCCESS);
    return 0;
}

