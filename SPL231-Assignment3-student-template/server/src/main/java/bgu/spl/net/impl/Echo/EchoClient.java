package bgu.spl.net.impl.Echo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class EchoClient {

    public static void main(String[] args) throws IOException {

        if (args.length == 0) {
            args = new String[]{"localhost", "CONNECT\n" +
                    "accept-version:1.2\n" +
                    "host:stomp.cs.bgu.ac.il\n" +
                    "login:mani\n" +
                    "passcode:films\n" + "\n" +
                    "\u0000"};
        }

        if (args.length < 2) {
            System.out.println("you must supply two arguments: host, message");
            System.exit(1);
        }


      

        //BufferedReader and BufferedWriter automatically using UTF-8 encoding
        try (Socket sock = new Socket(args[0], 7777);
                BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()))) {

            System.out.println("sending message to server");
            out.write(args[1]);
            out.newLine();
            out.flush();
                    
            System.out.println("awaiting response");
            String mesage = in.readLine();
            mesage  = mesage + "\n" + in.readLine();
            //mesage  = "\n" + in.readLine();        
           // while(line.length()>0 &&line.charAt(line.length()-1) !='\u0000'){

            //}
            System.out.println("message from server: " + mesage);
        }
    }
}
