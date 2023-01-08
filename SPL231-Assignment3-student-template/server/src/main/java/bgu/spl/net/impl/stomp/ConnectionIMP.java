package bgu.spl.net.impl.stomp;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentSkipListSet;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class ConnectionIMP<T> implements Connections<T> {

    //CH
    public ConcurrentSkipListSet<ConnectionHandler<T>> CH = new ConcurrentSkipListSet<ConnectionHandler<T>>();
    //connectionId -> CH
    public ConcurrentHashMap<Integer,ConnectionHandler<T>> connectionIdConnectionHandler = new ConcurrentHashMap<Integer,ConnectionHandler<T>>();

    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler<T> Ch = connectionIdConnectionHandler.get(connectionId);
        if(Ch != null){
            Ch.send(msg);
            return true;
        }
        return false; 
    }

    @Override
    public void send(String channel, T msg) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void disconnect(int connectionId) {
        ConnectionHandler<T> Ch = connectionIdConnectionHandler.get(connectionId);
        CH.remove(Ch);
        connectionIdConnectionHandler.remove(connectionId);
        
    }

    
    
}
