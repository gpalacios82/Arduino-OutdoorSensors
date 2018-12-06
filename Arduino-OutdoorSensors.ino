// Incluimos librería para manejar el sensor de humedad y temperatura
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11 // Tipos de sensor: DHT_TYPE_11 DHT_TYPE_21 DHT_TYPE_22

// Definicion de puertos
int DHT_SENSOR_PIN = 2;
int LUX_SENSOR_PIN = A0;
int VOLTAJE_SENSOR_PIN = A1;

DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );


void setup( )
{
  Serial.begin( 9600 );
  pinMode(VOLTAJE_SENSOR_PIN, INPUT);
  pinMode(LUX_SENSOR_PIN, INPUT);
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

  // Leemos datos de luminosidad
  float LuxQty = analogRead(LUX_SENSOR_PIN);
  LuxQty = map(LuxQty, 0, 1023, 0, 100); 

  // Leemos datos de Voltaje
  float voltaje = 0.0048 * analogRead(VOLTAJE_SENSOR_PIN); 

  // Si hay datos de humedad y temperatura (que es lo principal), procedemos a enviarlo por puerto serie
  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.println( String("Temp:" + String(temperature) + "ºC;Humidity:" + String(humidity)) + "%;Luminosity:" + String(LuxQty) + "%;Voltaje:" + String(voltaje) + "V");
  }
  //delay(500);
}
