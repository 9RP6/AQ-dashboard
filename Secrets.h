#define wm_user "Device_1" //SSID displayed when Device transmits its own wifi

// minimum & maximum vales of parameters for data obtained
int tempMax = 50, tempMin = 5;
int pressureMax = 1025, pressureMin = 950;
int humidityMax = 99, humidityMin = 5;
int altitudeMax = 500, altitudeMin = 0;
int gasResMax = 999, gasResMin = 0;

//tempError=1000
//pressureError=1100
//humidityError=1110
//altitudeError=1111
//gasResError=1001

//For AQI Calculations (https://pib.gov.in/newsite/printrelease.aspx?relid=110654)
//Good =1
//Satisfactory =2
//Moderately polluted = 3
//Poor = 4
//Very Poor =5
//Severe=6
