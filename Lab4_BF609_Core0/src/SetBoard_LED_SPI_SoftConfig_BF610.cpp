/*
 *  Software Switch Configuration for the ADSP-BF609-EZ-BOARD
 *
 *  Please see the SoftConfig documentation in CCES Help for detailed
 *  information on SoftConfig.
 *
 */

#include <drivers\twi\adi_twi.h>

/* TWI settings */
#define TWI_PRESCALE  (8u)
#define TWI_BITRATE   (100u)
#define TWI_DUTYCYCLE (50u)

#define BUFFER_SIZE (32u)

/* TWI hDevice handle */
static ADI_TWI_HANDLE hDevice;

/* TWI data buffer */
static uint8_t twiBuffer[BUFFER_SIZE];

/* TWI device memory */
static uint8_t deviceMemory[ADI_TWI_MEMORY_SIZE];

/* switch register structure */
typedef struct {
	uint8_t Register;
	uint8_t Value;
} SWITCH_CONFIG;

/* switch parameter structure */
typedef struct {
	uint32_t TWIDevice;
	uint16_t HardwareAddress;
	uint32_t NumConfigSettings;
	SWITCH_CONFIG *ConfigSettings;
} SOFT_SWITCH;

/* prototype */
// void SetBoardLED_ConfigSoftSwitches(void);

/* disable misra diagnostics as necessary */
#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_8_7:"Objects shall be defined at block scope")
#pragma diag(suppress:misra_rule_17_4:"Array indexing shall be the only allowed form of pointer arithmetic")
#endif /* _MISRA_RULES */

/* switch 0 register settings */
static SWITCH_CONFIG SwitchConfig0[] =
{
 // { 0x12u, 0x7u },  /* GPIOA switch settings */
  { 0x12u, 0xF },  /* GPIOA switch settings */   // Adjust CAN0RX_EN to fix Timer1 issue
  { 0x13u, 0xFCu }, /* GPIOB switch settings */
  { 0x0u, 0x0u },   /* Set IODIRA direction (all output) */
  { 0x1u, 0x0u },   /* Set IODIRB direction (all output) */
};
/* switch 1 register settings */
static SWITCH_CONFIG SwitchConfig1[] =
{
  { 0x12u, 0xAu },  /* GPIOA switch settings */
  { 0x13u, 0x0u },  /* GPIOB switch settings */
  { 0x0u, 0x0u },   /* Set IODIRA direction (all output) */
  { 0x1u, 0x0u },   /* Set IODIRB direction (all output) */
};

#if 0
/* switch 2 register settings */
static SWITCH_CONFIG SwitchConfig2[] =
{
  { 0x12u, 0xF0u },  /* GPIOA switch settings */
  { 0x13u, 0x3u },   /* GPIOB switch settings */
  { 0x0u, 0x6u },    /* Set IODIRA direction (bits 1 and 2 input, all others output) */
  { 0x1u, 0x0u },    /* Set IODIRB direction (all output) */
};
#else
static SWITCH_CONFIG SwitchConfig2[] =
{
  { 0x12u, 0x10u }, // { 0x12u, 0xF0u },  /* GPIOA switch settings */
  { 0x13u, 0x00u }, // { 0x13u, 0x3u },   /* GPIOB switch settings */
  { 0x0u, 0x6u },    /* Set IODIRA direction (bits 1 and 2 input, all others output) */
  { 0x1u, 0x0u },    /* Set IODIRB direction (all output) */
};

#endif
/* switch configuration */
static SOFT_SWITCH SoftSwitch[] =
{
  {
    0u,
    0x21u,
    sizeof(SwitchConfig0)/sizeof(SWITCH_CONFIG),
    SwitchConfig0
  },
  {
    0u,
    0x22u,
    sizeof(SwitchConfig1)/sizeof(SWITCH_CONFIG),
    SwitchConfig1
  },
  {
    0u,
    0x23u,
    sizeof(SwitchConfig2)/sizeof(SWITCH_CONFIG),
    SwitchConfig2
  },
};
     
#if defined(ADI_DEBUG)
#include <stdio.h>
#define CHECK_RESULT(result, message) \
	do { \
		if((result) != ADI_TWI_SUCCESS) \
		{ \
			printf((message)); \
			printf("\n"); \
		} \
	} while (0)  /* do-while-zero needed for Misra Rule 19.4 */
#else
#define CHECK_RESULT(result, message)
#endif
 
void SetBoardLED_SPI_ConfigSoftSwitches(void)
{
	uint32_t switchNum;
	uint32_t configNum;
	uint32_t settings;
	uint32_t switches;

	SOFT_SWITCH *ss;
	SWITCH_CONFIG *configReg;
	ADI_TWI_RESULT result;

	switches = (uint32_t)(sizeof(SoftSwitch)/sizeof(SOFT_SWITCH));
	for (switchNum=0u; switchNum<switches; switchNum++)
	{
		ss = &SoftSwitch[switchNum];

		result = adi_twi_Open(ss->TWIDevice, ADI_TWI_MASTER, 
    		deviceMemory, ADI_TWI_MEMORY_SIZE, &hDevice);
		CHECK_RESULT(result, "adi_twi_Open failed");

		result = adi_twi_SetHardwareAddress(hDevice, ss->HardwareAddress);
		CHECK_RESULT(result, "adi_twi_SetHardwareAddress failed");

		result = adi_twi_SetPrescale(hDevice, TWI_PRESCALE);
		CHECK_RESULT(result, "adi_twi_Prescale failed");

		result = adi_twi_SetBitRate(hDevice, TWI_BITRATE);
		CHECK_RESULT(result, "adi_twi_SetBitRate failed");

		result = adi_twi_SetDutyCycle(hDevice, TWI_DUTYCYCLE);
		CHECK_RESULT(result, "adi_twi_SetDutyCycle failed");
		
		/* switch register settings */
		for (configNum=0u; configNum<ss->NumConfigSettings; configNum++)
		{
			configReg = &ss->ConfigSettings[configNum];

			/* write register value */
			twiBuffer[0] = configReg->Register;
			twiBuffer[1] = configReg->Value;
			result = adi_twi_Write(hDevice, twiBuffer, (uint32_t)2, false);
			CHECK_RESULT(result, "adi_twi_Write failed");
		}

		result = adi_twi_Close(hDevice);
		CHECK_RESULT(result, "adi_twi_Close failed");
	}
}

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */
 
