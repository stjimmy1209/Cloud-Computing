import java.io.*;


public class ExternalSortMain {

    static int chunkNum = 100;
    static int threadNum = chunkNum;
    static File file = new File("log1GB");
    static int bufferSize = (int)(file.length() / 100 / chunkNum);

    public static void main(String[] args) {

        int bufferNum = Runtime.getRuntime().availableProcessors();

        System.out.println("ThreadNum: " + threadNum);
        System.out.println("ChunkNum: " + chunkNum);
        System.out.println("BufferSize: " + bufferSize);


        Thread[] threads = new Thread[threadNum];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(new FileSplitter(i + 1, bufferSize));
        }

        long startTime = System.nanoTime();

        for (int i = 0; i < threads.length; i += bufferNum) {
            for (int j = i; j < i + bufferNum; j++) {
                threads[j].start();
            }
            for (int j = i; j < i + bufferNum; j++) {
                try {
                    threads[j].join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        try {
            FileMerger.mergeFile();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("External Sorting finished.");

        long endTime = System.nanoTime();
        System.out.println("****************************");
        System.out.println("Program run time: " + (endTime - startTime) / 1000 / 1000/ 1000 + " seconds");
        System.out.println("****************************");

        for (int i = 0; i < chunkNum; i++) {
            File file = new File("sorted_part_" + (i + 1));
            file.delete();
        }



    }



}
