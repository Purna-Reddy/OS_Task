//This Problem is being implemented using Round-Robin Algorithm.
#include<stdio.h>
struct process{
	int pid;
	int arrivaltime;
	int bursttime;
	int completetime;
	int roundbacktime;
}f[100], s[100], m[100];//Creating objects for the struct Process

int n, fc=0, sc=0, mc=0;
int quanta; //Time quantum


void prmapping();
void roundrobin();
void display();

int main()
{
	
	
	printf("\n**>Enter time in 2400 hours format. example for 10:30 am enter 1030"
			"\n**>Enter Query arrival times in ascending order, i.e., in real time arrival manner\n"
			"\nAll Time units are in minutes. \n\n");
	input();
	prmapping();
	roundrobin();

			
		
}




void prmapping(){
	int isc=0, ifc= 0, min, flag;
	if( fc!=0  && sc!=0){
		while(isc<sc && ifc<fc){
			if(f[ifc].arrivaltime == s[isc].arrivaltime){
				m[mc] = f[ifc];
				mc++;
				ifc++;
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else if(f[ifc].arrivaltime < s[isc].arrivaltime){
				m[mc]= f[ifc];
				mc++;
				ifc++;
			}
			else if(f[ifc].arrivaltime > s[isc].arrivaltime){
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else;
		}
		if(mc != (fc+sc)){
			if(fc!=ifc){
				while(ifc!=fc){
					m[mc]= f[ifc];
					mc++;
					ifc++;
				}
			}
			else if(sc!=isc){
				while(isc!=sc){
					m[mc]= s[isc];
					mc++;
					isc++;
				}
			}
		}
	}
	else if(fc==0){
		while(isc!=sc){
			m[mc]= s[isc];
			mc++;
			isc++;
		}
	}
	else if(sc==0){
		while(ifc!=fc){
			m[mc]= f[ifc];
			mc++;
			ifc++;
		}
	}
	else {
		printf("\n No valid Jobs available\n");
	}
}


void roundrobin(){
	int time= m[0].arrivaltime, mark=0, cc=0, i, rc;
	while(time!=120 && cc!=mc){
		for(i=0; i<=mark; i++){
			if(m[i].roundbacktime > quanta){
				time += quanta;
				m[i].roundbacktime -= quanta;
			}
			else if(m[i].roundbacktime <=quanta && m[i].roundbacktime !=0){
				time += m[i].roundbacktime;
				m[i].roundbacktime =0;
				m[i].completetime = time;
				cc++;
			}
			else;
		}
		int start = mark+1;
		for(rc= start; rc<mc; rc++){
			if(m[rc].arrivaltime <= time){
				mark++;
			}
		}
	}	
}


void display(){
	int i=0, total=0, sum=0; 
	double avg;
	printf("\nSummary for the Execution\n");
	printf("\nQuery ID");
	printf("\tArrival Time");
	printf("\tRessolving Time");
	printf("\tCompletion Time");
	printf("\tTurn Around Time");
	printf("\tWaiting Time");
	for(i; i<mc; i++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		m[i].pid, (m[i].arrivaltime+1000), m[i].bursttime, (m[i].completetime+1000), (m[i].completetime-m[i].arrivaltime), ((m[i].completetime-m[i].arrivaltime)- m[i].bursttime));
		total= m[i].completetime;
		sum+= (m[i].completetime-m[i].arrivaltime);
	}
	avg = sum/mc;
	printf("\n\nTotal time Spent for all queries: %d", total);
	printf("\nAverage query time: %lf", avg);
	printf("\nProcess Execution Complete");
}

