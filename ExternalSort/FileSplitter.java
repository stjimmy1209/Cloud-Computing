import java.io.*;

public class FileSplitter implements Runnable {

    int id;
    int numLines;


    public FileSplitter(int id, int numLines) {
        this.id = id;
        this.numLines = numLines;
    }

    @Override
    public void run() {

        splitFile(id, numLines);

    }

    static void splitFile(int threadID, int bufferSize){

        String[]buffer = new String[bufferSize];

        try (BufferedReader br = new BufferedReader(new FileReader("log1GB"))) {
            for (int i = 0; i < bufferSize * (threadID - 1); i++)
                br.readLine();

            for (int i = 0; i < bufferSize; i++)
                buffer[i] = br.readLine();

        } catch (IOException e) {
            e.printStackTrace();
        }

        Sorter.mergeSort(buffer, 0, buffer.length - 1);

        File file = new File("sorted_part_" + threadID);
        int writeCount = 0;
        try{

            FileOutputStream fos = new FileOutputStream(file);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));

            for (String record : buffer) {
                bw.write(record + "\r\n");
                writeCount++;
                //bw.newLine();
            }
            System.out.println("Number of lines written in thread: " + threadID + " is: " + writeCount);
            bw.close();


        } catch (IOException e) {
            e.printStackTrace();
        }

    }


}
