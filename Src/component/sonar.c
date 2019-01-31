/**
 * @author DAHOUX Sami
 * @date 2019/29/01
 * @brief Sonar management functions
 * @details This file define a framework for using LV-MaxSonar-EZ with STM32 Nucleo TIM2 at f = 1 MHz.
 *          -RX PIN : PB8, used to trig sonar echo
 *          -PW PIN : PB10, used to get sonar echo
 *          -SONAR_RX/PW_MAX_DURATION : Numbers of TIM2 tops
 *          -SCALE_FACTOR : us/cm conversion factor between PW high duration and range of detected object
 */
#define SONAR_RX_MAX_DURATION   1600 // ~20 us high
#define SONAR_PW_MAX_DURATION   2432000 // 38 ms
#define SONAR_READ_PERIOD       3136000 // 49 ms
#define SONAR_INIT_PERIOD       16000000 // 250ms

//#define SONAR_RX_MAX_DURATION   1 // 25 / 1000 // ~20 us high
//#define SONAR_PW_MAX_DURATION   38 // 38 ms
//#define SONAR_READ_PERIOD       49 // 49 ms
//#define SONAR_INIT_PERIOD       250 // 250ms

#define SCALE_FACTOR            57.87 // 147 us/inch

enum SONAR_STATE {
    INIT, RX, READ
};

// TEST VARIABLES

//static uint8_t sonar_rx_state;
//static uint8_t sonar_pw_state;

// High drive durations for RX and PW in TIM2 cycles
volatile static uint16_t sonar_rx_duration;
volatile static uint16_t sonar_pw_duration;
volatile static uint32_t init_duration;
volatile static uint32_t read_duration;

volatile static float sonar_distance; // in cmm

volatile uint8_t sonar_request = 0;

volatile static enum SONAR_STATE sonar_state;

void trig_sonar(void);
void init_sonar(void);
void gestion_sonar(void);

inline static void read_sonar(void) {
    sonar_pw_duration += HAL_GPIO_ReadPin(Echo_Sonar_GPIO_Port, Echo_Sonar_Pin) == GPIO_PIN_SET ? 1 : 0;
}

inline static void set_sonar_distance(void) {
    sonar_distance = (float) sonar_pw_duration / (float) SCALE_FACTOR;
}

void trig_sonar(void) {
    if (sonar_rx_duration == 0) {
        HAL_GPIO_WritePin(Trig_Sonar_GPIO_Port, Trig_Sonar_Pin, GPIO_PIN_SET);
    } else if (sonar_rx_duration > SONAR_RX_MAX_DURATION) {
        HAL_GPIO_WritePin(Trig_Sonar_GPIO_Port, Trig_Sonar_Pin, GPIO_PIN_RESET);
    }
    sonar_rx_duration += HAL_GPIO_ReadPin(Trig_Sonar_GPIO_Port, Trig_Sonar_Pin) == GPIO_PIN_SET ? 1 : 0;
}

/**
 * Call this function on main initialization to launch sonar.
 */
void init_sonar(void) {
    sonar_rx_duration = 0;
    sonar_pw_duration = 0;
    init_duration = 0;
    read_duration = 0;
    sonar_distance = 0;

    sonar_state = INIT;

    HAL_GPIO_WritePin(Trig_Sonar_GPIO_Port, Trig_Sonar_Pin, GPIO_PIN_RESET);
}

void gestion_sonar_do(void) {
    switch (sonar_state) {
        case INIT:
            init_duration++;
            if (init_duration > SONAR_INIT_PERIOD) {
            	low_battery = 1;
                init_duration = 0;
                sonar_state = RX;
            }

            break;

        case RX:
            trig_sonar();
            if (sonar_rx_duration > SONAR_RX_MAX_DURATION) {
                sonar_rx_duration = 0;
                sonar_state = READ;
            }
            break;

        case READ:
            read_sonar();
            read_duration++;
            if (read_duration + SONAR_RX_MAX_DURATION > SONAR_READ_PERIOD) {
                set_sonar_distance();
                sonar_pw_duration = 0;
                read_duration = 0;
                sonar_state = RX;
            }
            break;
    }
}

/**
 * Call this function on timer 2 callback to get sonar reading.
 */
void gestion_sonar(void) {
	gestion_sonar_do();
//	if (sonar_request) {
//		sonar_request = 0;
//	}
}
