package ex00;

import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Program {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        Map<String, String> signatures = new HashMap<String, String>();
        signatures = readSignature();
        String inputFileName;
        byte[] buffer = new byte[8];

        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream("result.txt");
        } catch(IOException ex) {
            System.out.println(ex.getMessage());
        }

        while(!(inputFileName = scanner.nextLine()).equals("42")) {
            try(FileInputStream fis = new FileInputStream(inputFileName)) {
                boolean check = false;
                fis.read(buffer);
                String byteStr = "";
                for(byte b: buffer) {
                    byteStr += String.format("%02x", b).toUpperCase();
                }
                for (Map.Entry<String, String> tmp : signatures.entrySet()) {
                    if (byteStr.contains(tmp.getKey().toUpperCase())) {
                        System.out.println("PROCESSED");
                        fos.write(tmp.getValue().getBytes());
                        fos.write('\n');
                        check = true;
                    }
                }
                if(!check) {
                    System.out.println("UNDEFINED");
                }
            } catch(IOException ex) {
                System.out.println(ex.getMessage());
            }

        }
    }

    public static Map<String, String> readSignature() {
        Map<String, String> signatures = new HashMap<String, String>();
        String[] formSign;
        String tmp = "";
        try(FileInputStream fis = new FileInputStream("/home/enedinae/Desktop/JB_S21/Day02-1/src/ex00/signatures.txt")) {
            int i = 0;
            while((i = fis.read())!= -1) {
                if((char)i == '\n') {
                    formSign = tmp.split(",");
                    signatures.put(formSign[1].replace(" ", ""), formSign[0]);
                    tmp = "";
                    continue;
                }
                tmp += (char)i;
            }
        } catch(IOException ex) {
            System.out.println(ex.getMessage());
        }
        return signatures;
    }
}
