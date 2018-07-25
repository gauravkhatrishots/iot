#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include <unistd.h>


#define ADDRESS     "mqtt.mcs.mediatek.com:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "mcs/:DlHXP81j/:h36abSUVlALttWWI/:touchannel"
#define TOPIC1       "mcs/:DlHXP81j/:h36abSUVlALttWWI/:val"
#define PAYLOAD     ",touchannel,1"
#define QOS         2
#define TIMEOUT     10000L

int main(int argc, char* argv[])
{
	

    char *msg[4];
    int i=0;
    int j=2;
    msg[0]=",touchannel,1";
    msg[1]=",touchannel,0";
    msg[2]=",val,0";
    msg[3]=",val,1";
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    while(1){
    MQTTClient_connect(client, &conn_opts);

    pubmsg.payload = msg[i];
    i=(i+1)%2;
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n""on topic %s for client with ClientID: %s\n", (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
	sleep(10);    
    
    if (j==4)j=2;
    pubmsg.payload = msg[j];
    j=(j+1);
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
  
   MQTTClient_publishMessage(client, TOPIC1, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n""on topic %s for client with ClientID: %s\n", (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered token);
	sleep(10);    

    MQTTClient_disconnect(client, 10);
  
}
	
    MQTTClient_disconnect(client, 10);
    MQTTClient_destroy(&client);
    return rc;

}
