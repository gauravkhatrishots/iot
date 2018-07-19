#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include <unistd.h>


#define ADDRESS     "mqtt.mcs.mediatek.com:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "mcs/:DMgqmj0R/:qGwsaFVwJQKIIILl/:temp"
#define TOPIC1       "mcs/:DMgqmj0R/:qGwsaFVwJQKIIILl/:humid"
#define TOPIC2       "mcs/:DMgqmj0R/:qGwsaFVwJQKIIILl/:pressure"

#define PAYLOAD     ",touchannel,1"
#define QOS         1
#define TIMEOUT     10000L

int main(int argc, char* argv[])
{
	char payloadtemp[20]={',','t','e','m','p',',','\0'};
	char payloadhumid[20]={',','h','u','m','i','d',',','\0'};
	char payloadpress[20]={',','p','r','e','s','s','u','r','e',',','\0'};
	int  temp,humid,press;
	

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
	strcpy(payloadtemp,",temp,");
	strcpy(payloadpress,",press,");
	strcpy(payloadhumid,",humid,");
        
	printf("enter temperature\n");
	scanf("%d",&temp);
	
	printf("enter pressure\n");
	scanf("%d",&press);

	printf("enter humidity\n");
	scanf("%d",&humid);
	
	int len=1;
	char *s;
	int num=temp;
  	while(temp/10!=0)
    	{
     	 len++;
      	temp=temp/10;
    	}
  	char a[len+1];
  	for(int i=len-1;i>=0;i--)
  	{
      	a[i]=(num%10)+48	;
      	num=num/10;
 	 }
  	a[len]='\0';
  	strcat(payloadtemp,a);
 	len=1;
	num=press;
  	while(press/10!=0)
    	{
     	 len++;
      	 press=press/10;
    	}
        for(int i=len-1;i>=0;i--)
   	{
        a[i]=(num%10)+48	;
  	num=num/10;
  	}
  	a[len]='\0';
  	strcat(payloadpress,a);
  	len=1;
	num=humid;
  	while(humid/10!=0)
    	{
     	len++;
      	humid=humid/10;
    	}
	for(int i=len-1;i>=0;i--)
  	{
      	a[i]=(num%10)+48	;
      	num=num/10;
  	}
 	a[len]='\0';
 
 	strcat(payloadhumid,a);
  	printf("presure  %s\n ",payloadpress);
 	printf("humidity %s\n ",payloadhumid);
  	printf("temperature  %s\n ",payloadtemp);


    pubmsg.payload = payloadtemp;
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n""on topic %s for client with ClientID: %s\n", (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    sleep(1);    
    
    pubmsg.payload = payloadhumid;
    
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
  
    MQTTClient_publishMessage(client, TOPIC1, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n""on topic %s for client with ClientID: %s\n", (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered \n",token);
   sleep(1);    

    pubmsg.payload = payloadpress;
    pubmsg.payloadlen = strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
  
    MQTTClient_publishMessage(client, TOPIC2, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n""on topic %s for client with ClientID: %s\n", (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n ",token);
  
}
	
    MQTTClient_disconnect(client, 10);
    MQTTClient_destroy(&client);
    return rc;

}
