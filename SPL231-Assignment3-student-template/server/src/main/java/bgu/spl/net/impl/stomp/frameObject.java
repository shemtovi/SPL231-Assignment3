package bgu.spl.net.impl.stomp;


import java.util.HashMap;
import java.util.Map;

public class frameObject {
    String commandLine;
    Map<String,String> headers = new HashMap<String,String>();
    String message;

    public frameObject(String commandLine, Map<String,String> map, String message){
        this.commandLine = commandLine;
        this.headers = map;
        this.message = message;
  
    }

    public String frameObjectToString(){
        String ans = "";
        if(commandLine != null)
            ans += commandLine +"\n";
        for(String field: headers.keySet()){
            if(field != null)
                ans = ans + field + ":" + headers.get(field) + "\n";
        }
        ans += "\n";
        if(message != null)
            ans += message + "\n";
        return ans;
    }


    static frameObject StringToframeObject(String str){
        String[] lines = str.split("\n");
        String command = lines[0];
        Map<String,String> map = new HashMap<String,String>();
        String message = "";
        boolean inHeaders = true;
        for(int i = 1; i< lines.length;i++){
            String line = lines[i];
            if(inHeaders && line.isEmpty()){
                inHeaders = false;
            }
            else if(inHeaders){
                int dotIndexs = line.indexOf(':');
                String key = line.substring(0, dotIndexs);
                String value = line.substring(dotIndexs +1);
                map.put(key, value);
            }
            else{
                message += line +"\n";
            }
        }
        return new frameObject(command,map,message);
    }


}
