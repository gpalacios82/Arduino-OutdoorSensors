#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11 // DHT_TYPE_11 DHT_TYPE_21 DHT_TYPE_22

int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );


void setup( )
{
  Serial.begin( 9600);
}


static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}



void loop( )
{
  float temperature;
  float humidity;
  String sensacion1;
  String sensacion2;

  if( measure_environment( &temperature, &humidity ) == true )
  {
    if(temperature <= 15)
      sensacion1 = String("Uff, parece que hace bastante frío, hay " + String(temperature) + " grados.");
    else
      if(temperature >= 25)
        sensacion1 = String("Con " + String(temperature) + " grados, hoy parece que hace bastante calor.");
      else
        sensacion1 = String("Hay " + String(temperature) + " grados en la calle hoy.");

    if(humidity <= 30)
      sensacion2 = String("El ambiente es muy seco, hay una humedad del " + String(humidity) + " %.");   
    else
      if(humidity >= 70)
        sensacion2 = String("El ambiente es súper húmedo, hay un " + String(humidity) + " %.");   
      else
        sensacion2 = String("La humedad es del " + String(humidity) + "%.");   

    Serial.print( sensacion1 );
    Serial.print(' ');
    Serial.println( sensacion2 );
  }
}
