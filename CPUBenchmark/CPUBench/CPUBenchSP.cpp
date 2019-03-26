#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include<time.h>
using namespace std;

void * incrementSP(void *arg){
    
    float n = 0.12;
    float a = 0.23;
    float m = 0.01;
    float b = 0.33;
    float c = 0.35;
    float d = 0.32;
    float e = 0.37;
    float f = 0.34;
    float g = 0.38;
    
    long length = *((long *) arg);
    struct timespec start, finish;
    double elapsed;
    cout << "Size of the for loop for this SP thread is: " << length << endl;
    cout << "Benchmark running... Please wait...";
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(long i = 0; i < length; i++){
        
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        m = n + a + b + c + d + e + f + g;
        
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    cout << "Run time for this thread is: " << elapsed << " seconds."<< endl;
}


int main(int argc, char **argv){
    
    if (argc >= 2)
         {
             int numThread = atoi(argv[1]);
             long tri = 100000000000;
             int numArith = 393;
             long range = tri / numThread / numArith;
             
             pthread_t threads[numThread];
             int i;
             int rc;
             struct timespec start, finish;
             double elapsed;
             clock_gettime(CLOCK_MONOTONIC, &start);
             for(i = 0; i < numThread; i++){
                 
                 rc = pthread_create(&threads[i], NULL, &incrementSP, (void *)&range);
        
                 if (rc) {
                      cout << "Error:unable to create thread," << rc << endl;
                      exit(-1);
                   }
                 }
             
             for(i = 0; i < numThread; i++){
                 pthread_join(threads[i], NULL);
                 }
            clock_gettime(CLOCK_MONOTONIC, &finish);
            elapsed = (finish.tv_sec - start.tv_sec);
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            cout << "Total run time for this program is: " << elapsed << " seconds."<< endl;
            cout << "The processor speed is: " << tri / 1000000000 / elapsed << " GigaOPS." <<endl;
            }

}
