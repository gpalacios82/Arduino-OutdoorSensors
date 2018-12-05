#include <dht_nonblocking.h>
#include <LiquidCrystal.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11 // DHT_TYPE_11 DHT_TYPE_21 DHT_TYPE_22

int DHT_SENSOR_PIN = 2;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );


void setup( )
{
  Serial.begin( 9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Cargando datos...");

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
    Serial.println( String("Temperatura: " + String(temperature) + "º, Humedad: " + String(humidity) + "%") );
    Serial.println(" ");

    lcd.setCursor(0,0);
    lcd.print( String("Temp.: " + String(temperature) + " C        ") );
    lcd.setCursor(0, 1);
    lcd.print( String("Humedad: " + String(humidity) + " %          ") );
  }
}
