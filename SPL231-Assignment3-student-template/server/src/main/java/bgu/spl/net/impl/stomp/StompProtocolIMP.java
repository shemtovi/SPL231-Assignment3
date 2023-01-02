package bgu.spl.net.impl.stomp;



import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.Connections;



public class StompProtocolIMP<T> implements StompMessagingProtocol<T>{

    private boolean shouldTerminate = false;
    int connectionId; 
    Connections<T> connections;

    @Override
    public void start(int connectionId, Connections<T> connections){
        this.connectionId = connectionId;
        this.connections = connections;
    }

    @Override
    public void process(T msg) {
        //check if framObject is valide

        //if connect and is legale we add to connection <username,conectionId>

        //anderstend tipe of massege

        //replay whit connections
        
    }

    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}