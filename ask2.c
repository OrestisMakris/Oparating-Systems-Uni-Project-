// integral_seq.c numerical integration - sequential code
#include <stdio.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h> /* Needed for fork(), getpid () */
#include <sys/time.h>

struct mesg_buffer {
long mesg_type;
double mesg_data;
};
struct mesg_buffer message;


double get_wtime(void)
{
struct timeval t;
 gettimeofday(&t, NULL);
 return (double)t.tv_sec + (double)t.tv_usec*1.0e-6;
}

double f(double x)
{
return log(x)*sqrt(x);
}

// WolframAlpha: integral_1^4 log(x) sqrt(x) dx = 4/9 (4 log(64)-7)
// -> 4.28245881486164

int main(int argc, char *argv[])
{
double a = 1.0;
double b = 4.0;

unsigned long const n = 1e9;
long int size_of_procedure = ceil(n / argv[1]) ;

const double dx = (b-a)/n;
double S = 0;
double t0 = get_wtime();

for(unsigned long j=0 ; j < argv[1] ; j++){
 
 int pid = fork();

    if (pid > 0) {

        /*Key Generate
        key_t key;

        key = ftok("messafe_queue_key", '65')

       if ( key== -1){
        perror("ftok");
        exit(1);
       }

       // msgget creates a message queue
	   // and returns identifier
	   msgid = msgget(key, 0666 | IPC_CREAT )== -1
        perror("msgget");
        exit(1);
       }
        message.mesg_type = 1;
          
   
        // create the message queue and return identifier */


       for (unsigned long i = 0; i < n; i++) {
         double xi = a + (i + 0.5)*dx;
         
         S += f(xi);
        } 
        S *= dx;
    }
    else if (pid == 0) {
    
        exit(0);
    }
    else {
        perror("fork");
    }
} 


double t1 = get_wtime();
printf("Time=%lf seconds, Result=%.8f\n", t1-t0, S);

 return 0;
}