package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.stomp.StompConnections;
import bgu.spl.net.impl.stomp.StompProtocolIMP;
import bgu.spl.net.impl.stomp.frameObject;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.net.Socket;

public class BlockingConnectionHandler<T> implements Runnable, ConnectionHandler<T> {

    private final MessagingProtocol<T> protocol;
    private final MessageEncoderDecoder<T> encdec;
    private final Socket sock;
    private BufferedInputStream in;
    private BufferedOutputStream out;
    private volatile boolean connected = true;
    StompConnections<frameObject> connections;
    int connectionId;


    public BlockingConnectionHandler(Socket sock, MessageEncoderDecoder<T> reader, MessagingProtocol<T> protocol, StompConnections<frameObject> connections,int connectionId) {
        this.sock = sock;
        this.encdec = reader;
        this.protocol = protocol;
        this.connections = connections;
        this.connectionId = connectionId;
    }

    @Override
    public void run() {
        try (Socket sock = this.sock) { //just for automatic closing
           // int i = connections.getConnectionId(this);
           // ((StompProtocolIMP<frameObject>) protocol).start(connectionId,connections);
            int read;

            in = new BufferedInputStream(sock.getInputStream());
            out = new BufferedOutputStream(sock.getOutputStream());

            while (!protocol.shouldTerminate() && connected && (read = in.read()) >= 0) {
                T nextMessage = encdec.decodeNextByte((byte) read);
                if (nextMessage != null) {
                    protocol.process(nextMessage);        
                }
            }

        } catch (IOException ex) {
            ex.printStackTrace();
        }

    }

    @Override
    public void close() throws IOException {
        connected = false;
        sock.close();
    }

    @Override
    public void send(T msg)  {
        try{
            if (msg != null) {
                out.write(encdec.encode(msg));
                out.flush();
            }
        }catch(IOException ignore){} 
    }

    public MessagingProtocol<T> getProtocol(){
        return protocol;
    }

   /* public void start(Connections<frameObject> connections){
        int connectionId = connections.getConnectionsId();
        ((StompProtocolIMP) protocol).start(connectionId,connections);
    }*/
}
