#include <stdio.h>
#include <math.h>

#define CRAWL_RESOLUTION 0.5

float old_angle, offset=0;

/*******************************************
 * Calculates angle around  (0,0)
 * Handles singularity (0,0)
 * Handles all quadrants
 * *****************************************/
double get_angle(float x,float y)
	{	
		double angle;			
		      if(x==0.0 && y==0.0)	
					{
						angle=0.0+offset;  
					}
				else
					{
						if(x==0.0)x=0.00000000001;  //look for singularity and substitute with a number which is very small
						angle=atan2(y,x)*180/M_PI+offset;	// convert to degrees
					}
				
				// If angle becomes 90 degrees less then The tangent function has come full circle	
				if((old_angle>(angle+90))) 
					{
	//			    	printf("; *************old=%0.3f new=%0.3f angle+360=%0.2f x=%0.2f y=%0.2f \n",old_angle,angle,angle+360,x,y);
						offset+=360;
						angle+=360;
					}
			 old_angle=angle;

	return angle;
	}

/*************************************
 * crawls between two points at the resolution determined by CRAWL_RESOLUTION
 * Reevaluates Distance from Z=0
 * Reevaluates new Angle for axis A
 * the Z input is the X axis
 * ***********************************/
void crawl(float x1,float x2,float y1,float y2,float z)
{
	float difx=(x2-x1);
	float dify=(y2-y1);
	float newx,newy;
	float r,a;
	float xcrawl=0.0,ycrawl=0.0;

	int crawl_amount=hypot(difx,dify)/CRAWL_RESOLUTION; // distance between (x1,y1) and (x2,y2) / CRAWL_RESOLUTION
	
	xcrawl=difx/crawl_amount;  // x increment
	ycrawl=dify/crawl_amount;  //y increment
    
    
	newx=x1; // start with y1 and x1
	newy=y1;
	
	printf("\n");
	while(crawl_amount-->0)
		{
		 newx+=xcrawl;
		 newy+=ycrawl;	
		 r=hypot(newx,newy);  // calculate distance from center
		 a=get_angle(newx,newy); // calculate angle for axis A
//        printf("(%0.2f,%0.2f) (%0.2f,%0.2f) (%0.2f,%0.2f) angle=%0.3f oldangle=%0.2f\n",x1,y1,newx,newy,x2,y2,a,old_angle);
// printf("G1 X%0.1f Z%0.2f A%0.1f ;x=%0.2f y=%0.2f newx=%0.2f newy=%0.2f  \n",z,r,a,x1,y1,newx,newy); 
		printf("G1 X%0.1f Z%0.2f A%0.1f \n",z,r,a); 

		}
}

int main(int argc, char* argv[])
{
	char a[15];
	char b[15];
	char c[15];
	char d[15];
	char e[15];
    char line[256];
    float x, y, z,oldx=0.0,oldy=0.0;
	int gline=0;
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    FILE* fp = fopen(fileName, "r"); /* should check the result */

    while (     !feof(fp)) {
 	     fgets(line, sizeof(line), fp);
 	     sscanf(line,"%s %s %s %s %s",a,b,c,d,e);
   	    if(a[0]=='G' && b[0]=='Z' && c[0]=='X'  && d[0]=='Y') {
				if(c[0]=='X') {sscanf(c,"X%f",&x);}
				if(d[0]=='Y') {sscanf(d,"Y%f",&y);}
				if(b[0]=='Z') {sscanf(b,"Z%f",&z);}
                if (gline++!=0) crawl(oldx,x,oldy,y,z);  // skip first line
                oldx=x;
                oldy=y;
		} // endif line starts with G
    }  // endwhile

    fclose(fp);

    return 0;
}
