String []data;
int []colours;
int noPlanets, counter=1;
void setup()
{
 data=loadStrings("output.txt");
 size(1000,1000);
 background(255);
 noPlanets=int(data[0]);
 print(noPlanets);
  colours=new int[200];
 for(int i=0;i<noPlanets;i++)
   colours[i]=int(random(254));
 noStroke();
}

void draw()
{
  
  if(counter+noPlanets<data.length)
  {
    background(255);
    display();
  }
}
void mousePressed()
{
 counter=1; 
  
}
void display()
{
  //x is a basic counter
  delay(50);
  for(int i=counter;i<counter+2*noPlanets;i+=2)
  {
   float x,y; 
   x=float(data[i]);
    y=float(data[i+1]);
   fill(colours[i%noPlanets],colours[(i+99)%noPlanets],colours[(i+101)%noPlanets]);
   circle(500+50*x,500+50*y,25);
  }
  counter+=2*noPlanets;
  println("muiegarda");
}
