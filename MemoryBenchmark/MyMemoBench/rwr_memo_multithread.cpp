#include <cstdint>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <pthread.h>
#include <random>
#include <chrono>
#define loop 100
#define array_size 134217728
static double src[array_size];
static double des[array_size];
using namespace std;

struct thread_data {
   int thread_id;
   int num_thread;
   int block_size; 
};

default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());     // provide seed
int random (int low, int high)
{
    uniform_int_distribution<int> uid {low,high};   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no
}

void * thread_worker(void *arg){

    struct thread_data *my_data;
    my_data = (struct thread_data *) arg;
    int thread_id = my_data->thread_id;
    int num_thread = my_data->num_thread;
    int block_size = my_data->block_size;
    int sec_len = array_size / num_thread;
    cout << "Thread " << my_data->thread_id <<" working..." << endl;

    for(int i = 0; i < loop; i++)
    {
        for(int j = (thread_id - 1) * (sec_len); j < (thread_id - 1) * sec_len + sec_len; j += block_size)
        {   
            int low = (thread_id - 1) * sec_len /block_size;
            int high = (thread_id - 1) * sec_len /block_size + sec_len / block_size - 1;
            int random_num = random(low, high);
            memcpy(&des[random_num * block_size], &src[random_num * block_size], block_size);
        }
    
    }
    cout << "Thread " << thread_id << " done." << endl;
}

int main(int argc, char **argv){

    if(argc >= 2){
        cout << "*****************************************************" << endl;
        cout << "Benchmarking random access..." << endl;
        cout << "*****************************************************" << endl;
        random_device rd;
        mt19937 e2(rd());
        uniform_real_distribution<> dist(10, 100);
        int num_thread = atoi(argv[1]);
        int block_size = atoi(argv[2]);
        pthread_t threads[num_thread];
        double x = round(dist(e2));
        fill(src, src + array_size, x);
        int i;
        int rc;
        struct timespec start, finish;
        double elapsed;

        struct thread_data td[num_thread];


        clock_gettime(CLOCK_MONOTONIC, &start);
        for(i = 1; i <= num_thread; i++){

            td[i].thread_id = i;
            td[i].num_thread = num_thread;
            td[i].block_size = block_size;
            rc = pthread_create(&threads[i], NULL, thread_worker, (void *)&td[i]);

                if (rc) {
                      cout << "Error:unable to create thread," << rc << endl;
                      exit(-1);
                   }
                 }

            for(i = 1; i <= num_thread; i++){

                 pthread_join(threads[i], NULL);

                 }
            clock_gettime(CLOCK_MONOTONIC, &finish);
            elapsed = (finish.tv_sec - start.tv_sec);
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            cout << "Total run time for this program is: " << elapsed << " seconds."<< endl;
            double throughput;
            double latency;
            throughput = 100 / elapsed;
            latency = elapsed * 1000000000 / 107374182400; 
            cout << "*********************************************************************************************************" << endl;
            cout << "This is a benchmark on " << num_thread << " threads " << "with " << block_size << " bytes of block size" << endl;
            cout << "*********************************************************************************************************" << endl;
            cout << "Measured throughput is: " << throughput << " Gb/sec" << endl;
            cout << "*********************************************************************************************************" << endl;
            cout << "Measured latency is: " << latency << " nanoseconds / byte. " << endl;
            cout << "*********************************************************************************************************" << endl;
    }

}