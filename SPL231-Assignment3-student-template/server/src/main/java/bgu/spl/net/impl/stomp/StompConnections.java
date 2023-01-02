package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class StompConnections<T> implements Connections<T>{

Map<String,String> map;
Map<ConnectionHandler<T>,Integer> CH_userName;

//ueserName -> connectionId

//Ch -> userName

//connectionId -> CH

//cannel -> <connectionId,subscriptionId>

//


public void Connections(){
    map = new HashMap<String,String>();
}

    @Override
    public boolean send(int connectionId, T msg){
        return true;
    }

    @Override
    public void send(String channel, T msg){

    }

    @Override
    public void disconnect(int connectionId){
        
    }

    //geters
    public int getConnectionId(ConnectionHandler<T> connectionHandler){
        return CH_userName.get(connectionHandler);
    }

}
