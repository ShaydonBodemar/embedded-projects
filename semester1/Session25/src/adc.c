//
// COMP-GENG 421 - Tom Lupfer
//
// Analog-to-Digital Converter (ADC) module
//

#include "main.h"
#include "adc.h"


void AdcInit(void)
{
	LL_ADC_REG_InitTypeDef AdcInitStruct;

	// Enable the GPIOA port clock
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	// Configure PA0 as ADC_IN0
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);

	// Enable the clock for ADC1
	LL_APB1_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	if (__LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE() == 0)
	{
		LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_ASYNC_DIV2);
	}
/*
	LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

	LL_ADC_REG_SetFlagEndOfConversion(ADC1, LL_ADC_REG_FLAG_EOC_SEQUENCE_CONV);

	LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
*/

	AdcInitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	AdcInitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	AdcInitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	AdcInitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	AdcInitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;

	LL_ADC_REG_Init(ADC1, &AdcInitStruct);

	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);

	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_48CYCLES);

	LL_ADC_Enable(ADC1);

	LL_ADC_REG_StartConversionSWStart(ADC1);
}


int AdcReadingGet(void)
{
//	LL_ADC_REG_StartConversionSWStart(ADC1);

//	while (!LL_ADC_IsActiveFlag_EOCS(ADC1))
		;

	return LL_ADC_REG_ReadConversionData12(ADC1);
}
