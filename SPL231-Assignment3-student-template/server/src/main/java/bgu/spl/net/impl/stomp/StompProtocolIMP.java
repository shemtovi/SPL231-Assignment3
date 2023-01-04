package bgu.spl.net.impl.stomp;



import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import bgu.spl.net.api.StompMessagingProtocol;



public class StompProtocolIMP implements StompMessagingProtocol<frameObject>{

    private boolean shouldTerminate = false;
    int connectionId; 
    StompConnections connections;


    @Override
    public void start(int connectionId, StompConnections connections){
        this.connectionId = connectionId;
        this.connections = connections;
    }

    @Override
    public void process(frameObject msg) {
        //check if framObject is valide
        frameObject message = ((frameObject)msg);
        String commandLine =  message.commandLine;
        switch(commandLine){
            case("CONNECT"):
                connect(message);
                break;
            case("SEND"):
                send(message);
                break;
            case("SUBSCRIBE"):
                subscribe(message);
                break;
            case("UNSUBSCRIBE"):
                unsubscribe(message);
                break;
            case("DISCONNECT"):
                disconnect(message);
                break;      
            default:
                error(message,"invalid command");
                break;                          
        }
    }

    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }




    private void connect(frameObject message){
        String login = message.headers.get("login");
        String passcode = message.headers.get("passcode");
        if(message.headers.get("accept-version") != "1.2"
            ||message.headers.get("host") != "stomp.cs.bgu.ac.il"){
                error(message,"accept-version or host invalid");
            }
        else if(login == null || passcode == null){
            error(message,"login or passcode missing");
        }    
        else if(connections.managedToConnect(login,passcode,connectionId)){
            //new user join or old user
            //send a connect frame
            Map<String,String> headers = new HashMap<String,String>();
            headers.put("version", "1.2");
            frameObject connected = new frameObject("CONNECTED", headers, "");
            connections.send(connectionId, connected);
            receipt(message);
        }
        else{
            error(message,"passcode invalid or user alredy active");
        }    
    }


    private void send(frameObject message){
        String destination = message.headers.get("destination");
        if(destination == null)
            error(message, "malformed frame received - destination");
        else{
            ConcurrentHashMap<Integer,String> cannelCIdSId = connections.channelsMap.get(destination);
            if(cannelCIdSId == null){
                error(message, "destination doesnot exist");
            }
            else if(cannelCIdSId.get(connectionId) != null){
                //send a MESSAGE frame
                Map<String,String> headers = new HashMap<String,String>();
                headers.put("destination", destination);
                frameObject msg = new frameObject("MESSAGE", headers, message.body);
                connections.send(destination, msg);
                receipt(message);
            }
            else{
                error(message, "not subscribed to destination");
            }
        }
                            
    }
    private void subscribe(frameObject message){
        String destination = message.headers.get("destination");
        String id = message.headers.get("id");
        if(destination == null || id == null){
            error(message, "malformed frame received - destination/id");
        }
        else if(connections.subscribe(connectionId,id,destination)){
            //handle a SUBSCRIBE frame
            receipt(message);
        }
        else{
            error(message, "user alredy subscribed to destination");
        }

    }
    private void unsubscribe(frameObject message){
        String id = message.headers.get("id");
        if(id == null){
            error(message, "malformed frame received - id");
        }
        else if(connections.unsubscribe(id,connectionId)){
            //handle a UNSUBSCRIBE frame
            receipt(message);
        }
        else{
            error(message, "subscription ID dosent match");
        }

    }
    private void disconnect(frameObject message){
        String receipt = message.headers.get("receipt");
        if(receipt == null){
            error(message, "malformed frame received - receipt");
        }
        else{
            connections.disconnect(connectionId);
            receipt(message);
        }
        shouldTerminate = true;

    }
    private void error(frameObject message,String error){
        //TODO
        Map<String,String> headers = new HashMap<String,String>();
        headers.put("message", error);
        String receiptId = message.headers.get("receipt");
        if(receiptId != null)
            headers.put("receipt-id", receiptId);
        String errorMessage ="The message:\n-----\n" + message.frameObjectToString() +"\n-----";
        connections.send(connectionId, new frameObject("ERROR", headers,errorMessage));
        connections.disconnect(connectionId);
        shouldTerminate = true;
    }

    private void receipt(frameObject message){
        String receipt = message.headers.get("receipt");
        if(receipt != null){
            Map<String,String> headers = new HashMap<String,String>();
            headers.put("receipt", receipt);
            connections.send(connectionId, new frameObject("RECEIPT", headers, ""));
        }
    }
}