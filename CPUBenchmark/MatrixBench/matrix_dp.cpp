#include<iostream>
#include <cstdlib>
#include <pthread.h>
#include<time.h>
#include<cmath>

using namespace std;

int thread_order = 0;

struct thread_data {
   int  thr_num;
   int matrix_size;
   double** matrixa;
   double** matrixb;
   double** matrixc;
};

void* thread_worker(void* arg) 
{ 
    int start = thread_order++; 
    struct thread_data *my_data;
    my_data = (struct thread_data *) arg;
    int MAX = my_data->matrix_size;
    // Each thread computes 1/thr_num th of matrix multiplication 
    for (int i = start * MAX / my_data->thr_num; i < (start + 1) * MAX / my_data->thr_num; i++)  
        for (int j = 0; j < MAX; j++)  
            for (int k = 0; k < MAX; k++)  
                my_data->matrixc[i][j] += my_data->matrixa[i][k] * my_data->matrixb[k][j]; 
} 
 
int main(int argc, char **argv){
    
    if(argc >= 2) {

    int num_thread = atoi(argv[1]);
    pthread_t threads[num_thread];
    //create the first matrix;
    int m,i,j,k;
    cout<<"Please enter side length of the matrices (has to be less than 16384):";
	cin>> m;
	double** a = new double*[m];
    for(int i = 0; i < m; i++)
    a[i] = new double[m];

    //create the second matrix;
    double** b = new double*[m];
    for(int i = 0; i < m; i++)
    b[i] = new double[m];

    //creat the last matrix;
    double** c = new double*[m];
    for(int i = 0; i < m; i++)
    c[i] = new double[m];
        
		for(i=0;i<m;i++){
            for(j=0;j<m;j++)
            {
                srand48(time(NULL));
                double r = drand48();
                a[i][j] = r;
            }
        }
        cout<<"Matrix1 has been initialized. \n";
			
		for(i=0;i<m;i++){
            for(j=0;j<m;j++)
            {
                srand48(time(NULL));
                double r = drand48();
				b[i][j] = r;
            }
        }
		cout<<"Matrix2 has been initialized. \n";

        int x;
        int rc;
        struct thread_data td[num_thread];
        struct timespec start, finish;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for(x = 0; x < num_thread; x++){

                td[x].thr_num = num_thread;
                td[x].matrixa = a;
                td[x].matrixb = b;
                td[x].matrixc = c;
                td[x].matrix_size = m;
                 rc = pthread_create(&threads[x], NULL, thread_worker, (void *)&td[x]);

                 if (rc) {
                      cout << "Error:unable to create thread," << rc << endl;
                      exit(-1);
                   }
        }
            
            for(x = 0; x < num_thread; x++)
            {
                 pthread_join(threads[x], NULL);
            }
            clock_gettime(CLOCK_MONOTONIC, &finish);
            elapsed = (finish.tv_sec - start.tv_sec);
            elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
            cout << "Total run time for this program is: " << elapsed << " seconds."<< endl;
            cout << "Processor speed is: " << pow(m, 3) / 1000000000 / elapsed << " GigaOPS." <<endl;
            delete []a;
            delete []b;
            delete []c;
    }
    
}
