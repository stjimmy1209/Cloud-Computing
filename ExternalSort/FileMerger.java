import java.io.*;
import java.util.HashSet;
import java.util.PriorityQueue;

public class FileMerger {


    static void mergeFile() throws IOException {


        System.out.println("Chunks being merged, please wait...");
        int chunkNum = ExternalSortMain.chunkNum;
        int readTimes = chunkNum;
        int sortBufferSize = (int)(ExternalSortMain.file.length() / 100 / chunkNum / chunkNum);

        String[][] linesToSort = new String[chunkNum][];
        String[] chunkLines = new String[sortBufferSize];

        for (int i = 0; i < readTimes; i++) {

            for (int j = 0; j < chunkNum; j++) {

                BufferedReader bufferedReader = new BufferedReader(new FileReader("sorted_part_" + (j + 1)));

                //System.out.println("This chunk has " + file.length() / 100 + " lines");

                HashSet<String> linesToDelete = new HashSet<>();

                for (int k = 0; k < sortBufferSize; k++) {

                    String line = bufferedReader.readLine();
                    chunkLines[k] = line;
                    linesToDelete.add(line);

                }
                //System.out.println("Number of lines to delete: " + linesToDelete.size());
                linesToSort[j] = chunkLines;
                shrinkFile("sorted_part_" + (j + 1), linesToDelete);
            }

            String[]sortedLines;
            sortedLines = KSortedArray.mergeKSortedArray(linesToSort);

            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("sorted_log", true));

            for (int j = 0; j < sortedLines.length; j++) {
                bufferedWriter.write(sortedLines[j] + "\r\n");
            }
            bufferedWriter.close();

        }



    }


    static void shrinkFile(String fileName, HashSet<String> linesToDelete){

        File inputFile = new File(fileName);
        File tempFile = new File("myTempFile.txt");

        try{

            BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName));
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("myTempFile.txt"));

            int fileLength = (int)(inputFile.length() / 100);
            String line;
            for (int i = 0; i < fileLength; i++) {
                line = bufferedReader.readLine();
                if (linesToDelete.contains(line)) continue;
                bufferedWriter.write(line + "\r\n");
            }
            bufferedWriter.close();

            tempFile.renameTo(inputFile);

        } catch (Exception e){
            e.printStackTrace();
        }

    }

}

class ArrayContainer implements Comparable<ArrayContainer> {
    String[] arr;
    int index;

    public ArrayContainer(String[] arr, int index) {
        this.arr = arr;
        this.index = index;
    }

    @Override
    public int compareTo(ArrayContainer o) {
        return this.arr[this.index].compareTo(o.arr[o.index]);
    }
}

class KSortedArray {

    public static String[] mergeKSortedArray(String[][] arr) {
        //PriorityQueue is heap in Java
        PriorityQueue<ArrayContainer> queue = new PriorityQueue<ArrayContainer>();
        int total=0;

        //add arrays to heap
        for (int i = 0; i < arr.length; i++) {
            queue.add(new ArrayContainer(arr[i], 0));
            total = total + arr[i].length;
        }

        int m=0;
        String result[] = new String[total];

        //while heap is not empty
        while(!queue.isEmpty()){
            ArrayContainer ac = queue.poll();
            result[m++]=ac.arr[ac.index];

            if(ac.index < ac.arr.length-1){
                queue.add(new ArrayContainer(ac.arr, ac.index+1));
            }
        }

        return result;
    }


}