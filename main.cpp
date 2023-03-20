#include <bits/stdc++.h>
#include "Vector3.h"
#include "planets.h"
#include <unistd.h>

#define TIMEDELAY 100000
int noIterations=100000;
float initialEnergy;
std::vector<planet> bodies;



int main()
{
    generatePlanets(bodies,50,100000,10000,500);
    initialEnergy=totalEnergy(bodies);
    std::cout<<initialEnergy;
    //physics
    while(noIterations--)
    {
        for(int i=0; i<bodies.size(); i++)
        {
            bodies[i].updateacc(bodies);
            bodies[i].updatevel();
            bodies[i].updatepoz();
            if(noIterations%2500==0)
                o<<totalEnergy(bodies)/initialEnergy<<'\n';
        }
    }
    exit(EXIT_SUCCESS);
    return 0;
}

