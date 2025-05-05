#include "contiki.h"
#include <stdio.h>
#include "lib/random.h"
#include "weather_forecast.h"

#define FEATURE_COUNT 3

// temp, humidity, atmospheric pressure
static float features[FEATURE_COUNT];

// output vector (probabilities for each weather state)
static float outputs[5] = {0, 0, 0, 0, 0};

void geneate_weather_data(float min, float max) {
    for (int i = 0; i < FEATURE_COUNT; i++) {
        // Convert random_rand() (0 to RANDOM_RAND_MAX) into a float between 0 and 1
        float r = (float)random_rand() / RANDOM_RAND_MAX;
        features[i] = min + r * (max - min);
    }
}

PROCESS(weather_forecast_prediction, "Pisa Weather Forcast");
AUTOSTART_PROCESSES(&weather_forecast_prediction);

PROCESS_THREAD(weather_forecast_prediction, ev, data){
    static struct etimer timer;
    
    PROCESS_BEGIN();

    // Errors suppression to avoid compilation error
    printf("%p\n", eml_net_activation_function_strs); 
    printf("%p\n", eml_error_str); 
    // This is needed to avoid compiler error (warnings == errors)

    // Generate initial weather data
    geneate_weather_data(10.0f, 100.0f);
    
    /* Setup a periodic timer that expires after 10 seconds. */
    etimer_set(&timer, CLOCK_SECOND * 1);
    
    while(1) {

        eml_net_predict_proba(&weather_forecast, features, 3, outputs, 5);

        printf("%i, %i, %i, %i, %i\n", (int) 
            ((float) outputs[0]*100), (int) ((float) 
            outputs[1]*100), (int) 
            ((float)outputs[2]*100), 
            (int)((float)outputs[3]*100), 
            (int)((float)outputs[4]*100));

        
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
        etimer_reset(&timer);
    }
    
    PROCESS_END();
}
