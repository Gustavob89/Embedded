; Configuration Registers ===========================================
CONFIG OSC = HS;
CONFIG FCMEN = OFF; Fail-Safe Clock Monitor disabled
CONFIG IESO = ON; Internal/External Switch-Over enabled
CONFIG PWRTEN = OFF; Power-up Timer disabled
CONFIG BOREN = OFF; Brown-out Reset disabled
CONFIG WDTEN = OFF; Watchdog Timer disabled
CONFIG MCLRE = ON; MCLR Enable
CONFIG STVREN = OFF; Stack Overflow Reset disabled
CONFIG LVP = OFF; Low Voltage Programming disabled
CONFIG DEBUG = OFF; Background Debugger enableb
CONFIG CP0 = OFF; Code Protection Block 0 disabled
CONFIG CP1 = OFF; Code Protection Block 1 disabled
CONFIG CPB = OFF; Boot Block Code Protection disabled
CONFIG CPD = OFF;Data EEPROM Code Protection disabled
CONFIG WRT0 = OFF ; Write Protection Block 0 disabled
CONFIG WRT1 = OFF ; Write Protection Block 1 disabled
CONFIG WRTB = OFF; Boot Block Write Protection disabled
CONFIG WRTC = OFF; Configuration Register Write Protection disabled
CONFIG WRTD = OFF; Data EEPROM Write Protection disabled
CONFIG EBTR0 = OFF; Table Read Protection Block 0 disabled
CONFIG EBTR1 = OFF; Table Read Protection Block 1 disabled
CONFIG EBTRB = OFF; Boot Block Table Read Protection disabled


; Definitions =======================================================
#define INTERFACE_PORT PORTC
#define INTERFACE_PORT_TRIS TRISC
#define INPUT0 0
#define INPUT1 1
#define INPUT2 2
#define INPUT3 3
#define OUTPUT0 4
#define OUTPUT1 5
#define OUTPUT2 6
#define OUTPUT3 7


; Variables =========================================================
p_phase0 equ (0x00ff+0x0001)
p_phase1 equ (0x00ff+0x0002)
p_phase2 equ (0x00ff+0x0003)
p_sine_offset equ (0x00ff+0x0004)
p_button_buffer equ (0x00ff+0x0005)